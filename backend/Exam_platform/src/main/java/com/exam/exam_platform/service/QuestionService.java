package com.exam.exam_platform.service;

import com.exam.exam_platform.dto.BatchQuestionImportRequest;
import com.exam.exam_platform.dto.PracticeAnswerRequest;
import com.exam.exam_platform.dto.QuestionImportLogRequest;
import com.exam.exam_platform.dto.QuestionImportResult;
import com.exam.exam_platform.entity.Question;
import com.exam.exam_platform.mapper.QuestionMapper;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import jakarta.annotation.PostConstruct;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.multipart.MultipartFile;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import java.net.URI;
import java.net.ProxySelector;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Base64;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

@Service
public class QuestionService {
    private final QuestionMapper questionMapper;
    private final OperationLogService operationLogService;
    private final ObjectMapper objectMapper;
    private final HttpClient httpClient;

    @Value("${openai.api-key:}")
    private String configuredOpenAiApiKey;

    @Value("${openai.responses-url:https://api.openai.com/v1/responses}")
    private String configuredResponsesUrl;

    @Value("${openai.vision-model:gpt-4o-mini}")
    private String configuredVisionModel;

    @Value("${openai.timeout-seconds:60}")
    private long configuredTimeoutSeconds;

    public QuestionService(QuestionMapper questionMapper, OperationLogService operationLogService) {
        this.questionMapper = questionMapper;
        this.operationLogService = operationLogService;
        this.objectMapper = new ObjectMapper();
        HttpClient.Builder httpClientBuilder = HttpClient.newBuilder()
                .connectTimeout(Duration.ofSeconds(20));
        ProxySelector proxySelector = openAiProxySelector();
        if (proxySelector != null) {
            httpClientBuilder.proxy(proxySelector);
        }
        this.httpClient = httpClientBuilder.build();
    }

    @PostConstruct
    public void initializeSchema() {
        questionMapper.initSchema();
    }

    public List<Question> list(String subject,
                               String type,
                               String difficulty,
                               String knowledgePoint,
                               String keyword,
                               Long createdBy) {
        return questionMapper.list(subject, type, difficulty, knowledgePoint, keyword, createdBy);
    }

    public List<Map<String, Object>> subjectPracticeStats(String studentNo) {
        return questionMapper.subjectPracticeStats(studentNo);
    }

    public List<Question> randomQuestions(String subject,
                                          String type,
                                          String difficulty,
                                          String knowledgePoint,
                                          Integer count) {
        int safeCount = count == null ? 10 : count;
        safeCount = Math.max(1, Math.min(safeCount, 100));
        return questionMapper.randomQuestions(subject, type, difficulty, knowledgePoint, safeCount);
    }

    @Transactional
    public void recordPracticeAnswer(PracticeAnswerRequest request) {
        if (request.getQuestionId() == null) {
            throw new IllegalArgumentException("题目ID不能为空");
        }
        if (request.getStudentNo() == null || request.getStudentNo().isBlank()) {
            throw new IllegalArgumentException("学生学号不能为空");
        }
        String answer = request.getAnswer() == null ? "" : request.getAnswer().trim();
        if (answer.isBlank()) {
            throw new IllegalArgumentException("答案不能为空");
        }
        Question question = questionMapper.findById(request.getQuestionId());
        if (question == null) {
            throw new IllegalArgumentException("题目不存在");
        }
        boolean correct = resolvePracticeCorrectness(question, answer, request.getCorrect());
        boolean saved = questionMapper.recordPracticeAnswer(
                request.getStudentId(),
                request.getStudentName(),
                request.getStudentNo().trim(),
                request.getQuestionId(),
                answer,
                correct,
                request.getPracticeMode()
        );
        if (!saved) {
            throw new IllegalArgumentException("练习记录保存失败");
        }
    }

    public Question findById(Long id) {
        Question question = questionMapper.findById(id);
        if (question == null) {
            throw new IllegalArgumentException("题目不存在");
        }
        return question;
    }

    @Transactional
    public Question create(Question question) {
        normalizeQuestion(question);
        questionMapper.insert(question);
        operationLogService.record(question.getCreatedBy(), "QUESTION_CREATE", "新增题目：" + question.getContent());
        return question;
    }

    @Transactional
    public Question update(Long id, Question question) {
        normalizeQuestion(question);
        if (!questionMapper.update(id, question)) {
            throw new IllegalArgumentException("题目不存在");
        }
        question.setId(id);
        operationLogService.record(question.getCreatedBy(), "QUESTION_UPDATE", "修改题目ID：" + id);
        return question;
    }

    @Transactional
    public void delete(Long id, Long userId) {
        if (!questionMapper.delete(id)) {
            throw new IllegalArgumentException("题目不存在");
        }
        operationLogService.record(userId, "QUESTION_DELETE", "删除题目ID：" + id);
    }

    @Transactional
    public QuestionImportResult importCsv(MultipartFile file, Long userId) {
        if (file == null || file.isEmpty()) {
            return logImport(userId, "CSV", "", 0, 0, 0, "失败", "上传文件为空");
        }

        int total = 0;
        int success = 0;
        int failed = 0;
        int skipped = 0;
        List<String> errors = new ArrayList<>();

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(file.getInputStream(), StandardCharsets.UTF_8))) {
            String line;
            Map<String, Integer> header = null;
            while ((line = reader.readLine()) != null) {
                if (line.trim().isEmpty()) {
                    continue;
                }
                List<String> fields = parseCsvLine(line);
                if (header == null && looksLikeHeader(fields)) {
                    header = buildHeader(fields);
                    continue;
                }
                total++;
                try {
                    Question question = header == null ? questionFromDefaultColumns(fields, userId) : questionFromHeader(fields, header, userId);
                    normalizeQuestion(question);
                    if (insertImportedQuestionIfNew(question)) {
                        success++;
                    } else {
                        skipped++;
                    }
                } catch (RuntimeException exception) {
                    failed++;
                    if (errors.size() < 5) {
                        errors.add("第" + total + "行：" + exception.getMessage());
                    }
                }
            }
        } catch (IOException exception) {
            return logImport(userId, "CSV", file.getOriginalFilename(), total, success, failed + 1, "失败", exception.getMessage());
        }

        String status = failed == 0 ? "成功" : (success > 0 || skipped > 0 ? "部分成功" : "失败");
        String message = importResultMessage("导入完成", errors, skipped);
        operationLogService.record(userId, "QUESTION_IMPORT_CSV",
                "CSV导入题库：" + file.getOriginalFilename() + "，成功" + success + "题，跳过重复" + skipped + "题");
        return logImport(userId, "CSV", file.getOriginalFilename(), total, success, failed, status, message);
    }

    @Transactional
    public QuestionImportResult reserveExcelImport(MultipartFile file, Long userId) {
        String fileName = file == null ? "" : file.getOriginalFilename();
        if (file == null || file.isEmpty()) {
            return logImport(userId, "Excel", fileName, 0, 0, 0, "失败", "上传文件为空");
        }
        if (!fileName.toLowerCase(Locale.ROOT).endsWith(".xlsx")) {
            return logImport(userId, "Excel", fileName, 0, 0, 1, "失败",
                    "后端原生导入暂只支持 .xlsx，请将 .xls 另存为 .xlsx 后再导入。");
        }

        try {
            List<Question> questions = parseXlsxQuestions(file, userId);
            if (questions.isEmpty()) {
                return logImport(userId, "Excel", fileName, 0, 0, 0, "失败",
                        "Excel未识别到题目。请确认表头包含：科目、题型、题目内容、标准答案。");
            }
            return importQuestionList("Excel", fileName, userId, questions);
        } catch (RuntimeException | IOException exception) {
            operationLogService.record(userId, "QUESTION_IMPORT_EXCEL_FAILED", "Excel导入失败：" + fileName);
            return logImport(userId, "Excel", fileName, 0, 0, 1, "失败", exception.getMessage());
        }
    }

    @Transactional
    public QuestionImportResult importParsedQuestions(BatchQuestionImportRequest request) {
        if (request == null || request.getQuestions() == null || request.getQuestions().isEmpty()) {
            return logImport(null, "Excel", "", 0, 0, 0, "失败", "题目列表为空");
        }

        return importQuestionList(defaultIfBlank(request.getImportType(), "Excel"),
                defaultIfBlank(request.getFileName(), ""),
                request.getUserId(),
                request.getQuestions());
    }

    private QuestionImportResult importQuestionList(String importType,
                                                    String fileName,
                                                    Long userId,
                                                    List<Question> questions) {
        int total = questions.size();
        int success = 0;
        int failed = 0;
        int skipped = 0;
        List<String> errors = new ArrayList<>();

        for (int i = 0; i < questions.size(); i++) {
            Question question = questions.get(i);
            try {
                if (question.getCreatedBy() == null) {
                    question.setCreatedBy(userId);
                }
                normalizeQuestion(question);
                if (insertImportedQuestionIfNew(question)) {
                    success++;
                } else {
                    skipped++;
                }
            } catch (RuntimeException exception) {
                failed++;
                if (errors.size() < 8) {
                    errors.add("第" + (i + 1) + "行：" + exception.getMessage());
                }
            }
        }

        String status = failed == 0 ? "成功" : (success > 0 || skipped > 0 ? "部分成功" : "失败");
        String message = importResultMessage("批量导入完成", errors, skipped);
        operationLogService.record(userId, "QUESTION_IMPORT_" + importType.toUpperCase(Locale.ROOT),
                importType + "批量导入题库：" + fileName + "，成功" + success + "题，跳过重复" + skipped + "题");
        return logImport(userId, importType, fileName, total, success, failed, status, message);
    }

    @Transactional
    public QuestionImportResult importOcr(MultipartFile file, String imageName, Long userId) {
        String fileName = file != null && file.getOriginalFilename() != null
                ? file.getOriginalFilename()
                : defaultIfBlank(imageName, "");
        if (file == null || file.isEmpty()) {
            return logImport(userId, "OCR", fileName, 0, 0, 0, "失败", "上传图片为空");
        }

        String apiKey = defaultIfBlank(System.getenv("OPENAI_API_KEY"), configuredOpenAiApiKey);
        if (apiKey == null || apiKey.isBlank()) {
            operationLogService.record(userId, "QUESTION_IMPORT_OCR_FAILED", "OCR导入失败：" + fileName);
            return logImport(userId, "OCR", fileName, 1, 0, 1, "失败",
                    "未配置 OPENAI_API_KEY，无法调用图片识别服务。");
        }

        try {
            List<Question> questions = recognizeQuestionsFromImage(file, apiKey);
            if (questions.isEmpty()) {
                operationLogService.record(userId, "QUESTION_IMPORT_OCR_FAILED", "OCR未识别到题目：" + fileName);
                return logImport(userId, "OCR", fileName, 1, 0, 1, "失败", "未从图片中识别到可入库题目。");
            }

            int success = 0;
            int failed = 0;
            int skipped = 0;
            List<String> errors = new ArrayList<>();
            for (int i = 0; i < questions.size(); i++) {
                Question question = questions.get(i);
                try {
                    question.setCreatedBy(userId);
                    normalizeQuestion(question);
                    if (insertImportedQuestionIfNew(question)) {
                        success++;
                    } else {
                        skipped++;
                    }
                } catch (RuntimeException exception) {
                    failed++;
                    if (errors.size() < 8) {
                        errors.add("第" + (i + 1) + "题：" + exception.getMessage());
                    }
                }
            }

            String status = failed == 0 ? "成功" : (success > 0 || skipped > 0 ? "部分成功" : "失败");
            String message = importResultMessage("OCR识别导入完成", errors, skipped);
            operationLogService.record(userId, "QUESTION_IMPORT_OCR",
                    "OCR识别导入题库：" + fileName + "，成功" + success + "题，跳过重复" + skipped + "题");
            return logImport(userId, "OCR", fileName, questions.size(), success, failed, status, message);
        } catch (RuntimeException exception) {
            operationLogService.record(userId, "QUESTION_IMPORT_OCR_FAILED", "OCR导入失败：" + fileName);
            return logImport(userId, "OCR", fileName, 1, 0, 1, "失败", exception.getMessage());
        }
    }

    public List<Map<String, Object>> listImportLogs(Long userId, Integer limit) {
        return questionMapper.listImportLogs(userId, limit == null ? 50 : limit);
    }

    public Map<String, Object> previewImportRollback(Long logId) {
        if (logId == null) {
            throw new IllegalArgumentException("导入日志ID不能为空");
        }
        Map<String, Object> log = questionMapper.findImportLog(logId);
        if (log.isEmpty()) {
            throw new IllegalArgumentException("导入日志不存在");
        }
        int matchedCount = questionMapper.countRollbackCandidates(log, 30);
        Map<String, Object> result = new HashMap<>();
        result.put("logId", logId);
        result.put("importType", log.get("import_type"));
        result.put("fileName", log.get("file_name"));
        result.put("successCount", log.get("success_count"));
        result.put("matchedCount", matchedCount);
        result.put("status", log.get("status"));
        result.put("canRollback", canRollback(log, matchedCount));
        result.put("message", rollbackMessage(log, matchedCount));
        return result;
    }

    @Transactional
    public Map<String, Object> rollbackImport(Long logId) {
        if (logId == null) {
            throw new IllegalArgumentException("导入日志ID不能为空");
        }
        Map<String, Object> log = questionMapper.findImportLog(logId);
        if (log.isEmpty()) {
            throw new IllegalArgumentException("导入日志不存在");
        }
        int matchedCount = questionMapper.countRollbackCandidates(log, 30);
        if (!canRollback(log, matchedCount)) {
            throw new IllegalArgumentException(rollbackMessage(log, matchedCount));
        }
        int deletedCount = questionMapper.deleteRollbackCandidates(log, 30);
        questionMapper.markImportLogRolledBack(logId, deletedCount);
        Long userId = longValue(log.get("user_id"));
        operationLogService.record(userId, "QUESTION_IMPORT_ROLLBACK",
                "撤回题库导入：" + log.get("file_name") + "，删除" + deletedCount + "题");
        Map<String, Object> result = new HashMap<>(previewImportRollback(logId));
        result.put("deletedCount", deletedCount);
        result.put("canRollback", false);
        result.put("message", "已撤回删除 " + deletedCount + " 道题");
        return result;
    }

    public QuestionImportResult recordImportLog(QuestionImportLogRequest request) {
        if (request == null) {
            return logImport(null, "未知", "", 0, 0, 0, "失败", "导入日志参数为空");
        }
        return logImport(request.getUserId(),
                defaultIfBlank(request.getImportType(), "未知"),
                defaultIfBlank(request.getFileName(), ""),
                request.getTotalCount() == null ? 0 : Math.max(0, request.getTotalCount()),
                request.getSuccessCount() == null ? 0 : Math.max(0, request.getSuccessCount()),
                request.getFailedCount() == null ? 0 : Math.max(0, request.getFailedCount()),
                defaultIfBlank(request.getStatus(), "已记录"),
                defaultIfBlank(request.getMessage(), ""));
    }

    public int scoreForType(String type) {
        if ("单选题".equals(type)) return 3;
        if ("多选题".equals(type)) return 5;
        if ("判断题".equals(type)) return 3;
        if ("填空题".equals(type)) return 2;
        if ("编程题".equals(normalizeQuestionType(type))) return 15;
        return 3;
    }

    private boolean insertImportedQuestionIfNew(Question question) {
        if (questionMapper.existsDuplicate(question)) {
            return false;
        }
        questionMapper.insert(question);
        return true;
    }

    private boolean resolvePracticeCorrectness(Question question, String answer, Boolean clientCorrect) {
        String type = normalizeQuestionType(question.getType());
        if (isObjectiveType(type)) {
            return sameAnswer(answer, question.getAnswer(), type);
        }
        return Boolean.TRUE.equals(clientCorrect);
    }

    private boolean isObjectiveType(String type) {
        return "单选题".equals(type)
                || "多选题".equals(type)
                || "判断题".equals(type)
                || "填空题".equals(type);
    }

    private boolean sameAnswer(String left, String right, String type) {
        if ("单选题".equals(type) || "多选题".equals(type)) {
            return normalizeChoiceAnswer(left).equals(normalizeChoiceAnswer(right));
        }
        if ("判断题".equals(type)) {
            return normalizeJudgementAnswer(left).equals(normalizeJudgementAnswer(right));
        }
        return normalizeAnswer(left).equals(normalizeAnswer(right));
    }

    private String normalizeChoiceAnswer(String value) {
        String cleaned = normalizeAnswer(value)
                .replace(",", "")
                .replace(";", "")
                .replace("、", "")
                .replace("|", "")
                .replace(".", "")
                .replace("．", "");
        StringBuilder normalized = new StringBuilder();
        for (char option = 'A'; option <= 'Z'; option++) {
            if (cleaned.indexOf(option) >= 0) {
                normalized.append(option);
            }
        }
        return normalized.length() == 0 ? cleaned : normalized.toString();
    }

    private String normalizeJudgementAnswer(String value) {
        String cleaned = normalizeAnswer(value)
                .replace(".", "")
                .replace("．", "");
        return switch (cleaned) {
            case "TRUE", "T", "YES", "Y", "对", "正确", "√", "✓" -> "TRUE";
            case "FALSE", "F", "NO", "N", "错", "错误", "×", "✕", "X" -> "FALSE";
            default -> cleaned;
        };
    }

    private String normalizeAnswer(String value) {
        return value == null
                ? ""
                : value.trim()
                .replace("，", ",")
                .replace("；", ";")
                .replace(" ", "")
                .toUpperCase(Locale.ROOT);
    }

    private String importResultMessage(String successMessage, List<String> errors, int skipped) {
        List<String> parts = new ArrayList<>();
        if (errors == null || errors.isEmpty()) {
            parts.add(successMessage);
        } else {
            parts.add(String.join("；", errors));
        }
        if (skipped > 0) {
            parts.add("跳过重复题目 " + skipped + " 题");
        }
        return String.join("；", parts);
    }

    private QuestionImportResult logImport(Long userId,
                                           String type,
                                           String fileName,
                                           int total,
                                           int success,
                                           int failed,
                                           String status,
                                           String message) {
        Long logId = questionMapper.insertImportLog(userId, type, fileName, total, success, failed, status, message);
        return new QuestionImportResult(logId, type, fileName, total, success, failed, status, message);
    }

    private List<Question> parseXlsxQuestions(MultipartFile file, Long userId) throws IOException {
        Map<String, byte[]> entries = readZipEntries(file);
        byte[] sheetBytes = firstWorksheet(entries);
        if (sheetBytes == null) {
            throw new IllegalArgumentException("Excel工作表为空或格式不正确");
        }

        List<String> sharedStrings = parseSharedStrings(entries.get("xl/sharedStrings.xml"));
        List<List<String>> rows = parseSheetRows(sheetBytes, sharedStrings);
        if (rows.isEmpty()) {
            return List.of();
        }

        Map<String, Integer> header = null;
        int headerRowIndex = -1;
        int scanLimit = Math.min(rows.size(), 10);
        for (int i = 0; i < scanLimit; i++) {
            List<String> row = rows.get(i);
            if (looksLikeHeader(row)) {
                header = buildHeader(row);
                headerRowIndex = i;
                break;
            }
        }

        List<Question> questions = new ArrayList<>();
        for (int i = headerRowIndex >= 0 ? headerRowIndex + 1 : 0; i < rows.size(); i++) {
            List<String> row = rows.get(i);
            if (row.stream().allMatch(value -> value == null || value.isBlank())) {
                continue;
            }
            Question question = header == null
                    ? questionFromDefaultColumns(row, userId)
                    : questionFromHeader(row, header, userId);
            if (question.getType() != null && !question.getType().isBlank()
                    && question.getContent() != null && !question.getContent().isBlank()) {
                questions.add(question);
            }
        }
        return questions;
    }

    private Map<String, byte[]> readZipEntries(MultipartFile file) throws IOException {
        Map<String, byte[]> entries = new HashMap<>();
        try (ZipInputStream zipInputStream = new ZipInputStream(file.getInputStream())) {
            ZipEntry entry;
            while ((entry = zipInputStream.getNextEntry()) != null) {
                if (entry.isDirectory()) {
                    continue;
                }
                String name = entry.getName();
                if (!name.startsWith("xl/")) {
                    continue;
                }
                ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
                zipInputStream.transferTo(outputStream);
                entries.put(name, outputStream.toByteArray());
            }
        }
        return entries;
    }

    private byte[] firstWorksheet(Map<String, byte[]> entries) {
        byte[] first = entries.get("xl/worksheets/sheet1.xml");
        if (first != null) {
            return first;
        }
        return entries.entrySet().stream()
                .filter(entry -> entry.getKey().startsWith("xl/worksheets/sheet")
                        && entry.getKey().endsWith(".xml"))
                .sorted(Map.Entry.comparingByKey())
                .map(Map.Entry::getValue)
                .findFirst()
                .orElse(null);
    }

    private List<String> parseSharedStrings(byte[] bytes) {
        if (bytes == null || bytes.length == 0) {
            return List.of();
        }
        Document document = parseXml(bytes);
        NodeList items = document.getElementsByTagName("si");
        List<String> sharedStrings = new ArrayList<>();
        for (int i = 0; i < items.getLength(); i++) {
            Node item = items.item(i);
            NodeList textNodes = ((org.w3c.dom.Element) item).getElementsByTagName("t");
            StringBuilder text = new StringBuilder();
            for (int j = 0; j < textNodes.getLength(); j++) {
                text.append(textNodes.item(j).getTextContent());
            }
            sharedStrings.add(text.toString());
        }
        return sharedStrings;
    }

    private List<List<String>> parseSheetRows(byte[] sheetBytes, List<String> sharedStrings) {
        Document document = parseXml(sheetBytes);
        NodeList rowNodes = document.getElementsByTagName("row");
        List<List<String>> rows = new ArrayList<>();
        for (int i = 0; i < rowNodes.getLength(); i++) {
            org.w3c.dom.Element rowElement = (org.w3c.dom.Element) rowNodes.item(i);
            NodeList cellNodes = rowElement.getElementsByTagName("c");
            List<String> values = new ArrayList<>();
            for (int j = 0; j < cellNodes.getLength(); j++) {
                org.w3c.dom.Element cell = (org.w3c.dom.Element) cellNodes.item(j);
                int columnIndex = columnIndex(cell.getAttribute("r"));
                while (values.size() <= columnIndex) {
                    values.add("");
                }
                values.set(columnIndex, cellValue(cell, sharedStrings));
            }
            rows.add(values);
        }
        return rows;
    }

    private Document parseXml(byte[] bytes) {
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            factory.setFeature("http://apache.org/xml/features/disallow-doctype-decl", true);
            factory.setFeature("http://xml.org/sax/features/external-general-entities", false);
            factory.setFeature("http://xml.org/sax/features/external-parameter-entities", false);
            factory.setXIncludeAware(false);
            factory.setExpandEntityReferences(false);
            return factory.newDocumentBuilder().parse(new ByteArrayInputStream(bytes));
        } catch (Exception exception) {
            throw new IllegalArgumentException("Excel XML解析失败：" + exception.getMessage(), exception);
        }
    }

    private String cellValue(org.w3c.dom.Element cell, List<String> sharedStrings) {
        String type = cell.getAttribute("t");
        if ("inlineStr".equals(type)) {
            NodeList textNodes = cell.getElementsByTagName("t");
            return textNodes.getLength() == 0 ? "" : textNodes.item(0).getTextContent().trim();
        }

        NodeList values = cell.getElementsByTagName("v");
        if (values.getLength() == 0) {
            return "";
        }
        String raw = values.item(0).getTextContent().trim();
        if ("s".equals(type)) {
            try {
                int index = Integer.parseInt(raw);
                return index >= 0 && index < sharedStrings.size() ? sharedStrings.get(index).trim() : "";
            } catch (NumberFormatException exception) {
                return "";
            }
        }
        return raw;
    }

    private int columnIndex(String cellRef) {
        if (cellRef == null || cellRef.isBlank()) {
            return 0;
        }
        int index = 0;
        for (int i = 0; i < cellRef.length(); i++) {
            char ch = Character.toUpperCase(cellRef.charAt(i));
            if (ch < 'A' || ch > 'Z') {
                break;
            }
            index = index * 26 + (ch - 'A' + 1);
        }
        return Math.max(0, index - 1);
    }

    private boolean canRollback(Map<String, Object> log, int matchedCount) {
        if ("已撤回".equals(String.valueOf(log.get("status")))) {
            return false;
        }
        int successCount = intValue(log.get("success_count"));
        return successCount > 0 && matchedCount == successCount;
    }

    private String rollbackMessage(Map<String, Object> log, int matchedCount) {
        if ("已撤回".equals(String.valueOf(log.get("status")))) {
            return "这次导入已经撤回过，不能重复删除";
        }
        int successCount = intValue(log.get("success_count"));
        if (successCount <= 0) {
            return "这次导入没有成功入库的题目，无需撤回";
        }
        if (matchedCount != successCount) {
            return "可安全匹配到 " + matchedCount + " 道题，与日志成功数 " + successCount + " 不一致，为避免误删请手动核对";
        }
        return "可撤回删除 " + matchedCount + " 道题";
    }

    private int intValue(Object value) {
        if (value instanceof Number number) {
            return number.intValue();
        }
        try {
            return Integer.parseInt(String.valueOf(value));
        } catch (NumberFormatException exception) {
            return 0;
        }
    }

    private Long longValue(Object value) {
        if (value instanceof Number number) {
            return number.longValue();
        }
        try {
            return Long.parseLong(String.valueOf(value));
        } catch (NumberFormatException exception) {
            return null;
        }
    }

    private List<Question> recognizeQuestionsFromImage(MultipartFile file, String apiKey) {
        try {
            String mimeType = defaultIfBlank(file.getContentType(), "image/png");
            String encoded = Base64.getEncoder().encodeToString(file.getBytes());
            String model = defaultIfBlank(System.getenv("OPENAI_VISION_MODEL"),
                    defaultIfBlank(configuredVisionModel, "gpt-4o-mini"));
            URI endpoint = URI.create(openAiResponsesEndpoint());

            Map<String, Object> payload = Map.of(
                    "model", model,
                    "input", List.of(Map.of(
                            "role", "user",
                            "content", List.of(
                                    Map.of(
                                            "type", "input_text",
                                            "text", """
                                                    你是在线考试平台的题目录入助手。请从图片中识别所有题目，并输出严格 JSON。
                                                    字段要求：subject,type,content,optionA,optionB,optionC,optionD,answer,analysis,difficulty,knowledgePoint,score。
                                                    如果图片没有选项，则 optionA 到 optionD 输出空字符串。
                                                    type 只能使用：单选题、多选题、填空题、编程题。
                                                    difficulty 只能使用：基础、中等、困难。
                                                    不确定答案或解析时输出空字符串，不要编造。
                                                    """
                                    ),
                                    Map.of(
                                            "type", "input_image",
                                            "image_url", "data:" + mimeType + ";base64," + encoded
                                    )
                            )
                    )),
                    "text", Map.of(
                            "format", Map.of(
                                    "type", "json_schema",
                                    "name", "question_ocr_result",
                                    "strict", true,
                                    "schema", questionOcrSchema()
                            )
                    )
            );

            HttpRequest request = HttpRequest.newBuilder()
                    .uri(endpoint)
                    .timeout(Duration.ofSeconds(openAiTimeoutSeconds()))
                    .header("Authorization", "Bearer " + apiKey.trim())
                    .header("Content-Type", "application/json")
                    .POST(HttpRequest.BodyPublishers.ofString(objectMapper.writeValueAsString(payload), StandardCharsets.UTF_8))
                    .build();
            HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString(StandardCharsets.UTF_8));
            if (response.statusCode() < 200 || response.statusCode() >= 300) {
                throw new IllegalArgumentException("OCR识别服务返回异常：" + response.statusCode() + " " + response.body());
            }

            String outputText = extractOutputText(objectMapper.readTree(response.body()));
            if (outputText.isBlank()) {
                throw new IllegalArgumentException("OCR识别服务未返回结构化结果");
            }
            return parseOcrQuestions(outputText);
        } catch (IOException exception) {
            throw new IllegalArgumentException("OCR识别失败：" + exceptionSummary(exception), exception);
        } catch (InterruptedException exception) {
            Thread.currentThread().interrupt();
            throw new IllegalArgumentException("OCR识别被中断", exception);
        }
    }

    private String openAiResponsesEndpoint() {
        String endpoint = defaultIfBlank(System.getenv("OPENAI_RESPONSES_URL"),
                defaultIfBlank(configuredResponsesUrl, null));
        if (endpoint != null) {
            return endpoint;
        }
        String baseUrl = defaultIfBlank(System.getenv("OPENAI_BASE_URL"), "https://api.openai.com/v1");
        while (baseUrl.endsWith("/")) {
            baseUrl = baseUrl.substring(0, baseUrl.length() - 1);
        }
        return baseUrl.endsWith("/responses") ? baseUrl : baseUrl + "/responses";
    }

    private ProxySelector openAiProxySelector() {
        String proxy = defaultIfBlank(System.getenv("OPENAI_PROXY"), null);
        proxy = proxy == null ? defaultIfBlank(System.getenv("HTTPS_PROXY"), null) : proxy;
        proxy = proxy == null ? defaultIfBlank(System.getenv("HTTP_PROXY"), null) : proxy;
        if (proxy == null) {
            return null;
        }

        try {
            URI proxyUri = URI.create(proxy.contains("://") ? proxy : "http://" + proxy);
            if (proxyUri.getHost() == null || proxyUri.getPort() <= 0) {
                return null;
            }
            return ProxySelector.of(new InetSocketAddress(proxyUri.getHost(), proxyUri.getPort()));
        } catch (IllegalArgumentException exception) {
            return null;
        }
    }

    private long openAiTimeoutSeconds() {
        String raw = defaultIfBlank(System.getenv("OPENAI_TIMEOUT_SECONDS"), String.valueOf(configuredTimeoutSeconds));
        try {
            return Math.max(10L, Long.parseLong(raw));
        } catch (NumberFormatException exception) {
            return 60L;
        }
    }

    private String exceptionSummary(Throwable exception) {
        if (exception == null) {
            return "未知网络异常";
        }
        String message = exception.getMessage();
        Throwable cause = exception.getCause();
        if ((message == null || message.isBlank()) && cause != null) {
            message = cause.getMessage();
        }
        if (message == null || message.isBlank()) {
            message = exception.getClass().getSimpleName();
        } else {
            message = exception.getClass().getSimpleName() + " - " + message;
        }
        return message;
    }

    private Map<String, Object> questionOcrSchema() {
        Map<String, Object> questionSchema = Map.of(
                "type", "object",
                "additionalProperties", false,
                "required", List.of("subject", "type", "content", "optionA", "optionB", "optionC",
                        "optionD", "answer", "analysis", "difficulty", "knowledgePoint", "score"),
                "properties", Map.ofEntries(
                        Map.entry("subject", Map.of("type", "string")),
                        Map.entry("type", Map.of("type", "string")),
                        Map.entry("content", Map.of("type", "string")),
                        Map.entry("optionA", Map.of("type", "string")),
                        Map.entry("optionB", Map.of("type", "string")),
                        Map.entry("optionC", Map.of("type", "string")),
                        Map.entry("optionD", Map.of("type", "string")),
                        Map.entry("answer", Map.of("type", "string")),
                        Map.entry("analysis", Map.of("type", "string")),
                        Map.entry("difficulty", Map.of("type", "string")),
                        Map.entry("knowledgePoint", Map.of("type", "string")),
                        Map.entry("score", Map.of("type", "integer"))
                )
        );
        return Map.of(
                "type", "object",
                "additionalProperties", false,
                "required", List.of("questions"),
                "properties", Map.of(
                        "questions", Map.of(
                                "type", "array",
                                "items", questionSchema
                        )
                )
        );
    }

    private String extractOutputText(JsonNode root) {
        JsonNode direct = root.path("output_text");
        if (direct.isTextual()) {
            return direct.asText();
        }
        JsonNode output = root.path("output");
        if (output.isArray()) {
            for (JsonNode item : output) {
                JsonNode content = item.path("content");
                if (!content.isArray()) {
                    continue;
                }
                for (JsonNode part : content) {
                    String type = part.path("type").asText();
                    if ("output_text".equals(type) && part.path("text").isTextual()) {
                        return part.path("text").asText();
                    }
                }
            }
        }
        return "";
    }

    private List<Question> parseOcrQuestions(String outputText) throws IOException {
        JsonNode questionsNode = objectMapper.readTree(outputText).path("questions");
        List<Question> questions = new ArrayList<>();
        if (!questionsNode.isArray()) {
            return questions;
        }
        for (JsonNode node : questionsNode) {
            Question question = new Question();
            question.setSubject(node.path("subject").asText(""));
            question.setType(node.path("type").asText(""));
            question.setContent(node.path("content").asText(""));
            question.setOptionA(node.path("optionA").asText(""));
            question.setOptionB(node.path("optionB").asText(""));
            question.setOptionC(node.path("optionC").asText(""));
            question.setOptionD(node.path("optionD").asText(""));
            question.setAnswer(node.path("answer").asText(""));
            question.setAnalysis(node.path("analysis").asText(""));
            question.setDifficulty(node.path("difficulty").asText(""));
            question.setKnowledgePoint(node.path("knowledgePoint").asText(""));
            if (node.path("score").canConvertToInt()) {
                question.setScore(node.path("score").asInt());
            }
            questions.add(question);
        }
        return questions;
    }

    private void normalizeQuestion(Question question) {
        if (question.getSubject() == null || question.getSubject().isBlank()) {
            question.setSubject("综合");
        } else {
            question.setSubject(question.getSubject().trim());
        }
        question.setType(normalizeQuestionType(requireText(question.getType(), "题型不能为空")));
        question.setContent(requireText(question.getContent(), "题目内容不能为空"));
        if (question.getScore() == null || question.getScore() <= 0) {
            question.setScore(scoreForType(question.getType()));
        }
        question.setDifficulty(normalizeDifficulty(question.getDifficulty()));
    }

    private String normalizeQuestionType(String type) {
        String text = defaultIfBlank(type, "");
        String lower = text.toLowerCase(Locale.ROOT);
        if ("single".equals(lower) || "singlechoice".equals(lower) || "单选".equals(text) || "选择题".equals(text)) {
            return "单选题";
        }
        if ("multiple".equals(lower) || "multiplechoice".equals(lower) || "multi".equals(lower) || "多选".equals(text)) {
            return "多选题";
        }
        if ("judge".equals(lower) || "truefalse".equals(lower) || "true/false".equals(lower) || "判断".equals(text)) {
            return "判断题";
        }
        if ("blank".equals(lower) || "fill".equals(lower) || "填空".equals(text)) {
            return "填空题";
        }
        if ("program".equals(lower)
                || "coding".equals(lower)
                || "code".equals(lower)
                || "hard_math".equals(lower)
                || "math".equals(lower)
                || "代码题".equals(text)
                || "程序题".equals(text)
                || "编程大题".equals(text)
                || "大题".equals(text)
                || "高数题".equals(text)
                || "高数大题".equals(text)
                || "数学大题".equals(text)) {
            return "编程题";
        }
        return text;
    }

    private String normalizeDifficulty(String difficulty) {
        String text = defaultIfBlank(difficulty, "基础");
        String lower = text.toLowerCase(Locale.ROOT);
        if ("easy".equals(lower) || "简单".equals(text)) {
            return "基础";
        }
        if ("medium".equals(lower) || "normal".equals(lower) || "middle".equals(lower) || "中".equals(text)) {
            return "中等";
        }
        if ("hard".equals(lower) || "difficult".equals(lower) || "难".equals(text)) {
            return "困难";
        }
        return text;
    }

    private Question questionFromDefaultColumns(List<String> fields, Long userId) {
        if (fields.size() < 3) {
            throw new IllegalArgumentException("至少需要 type,content,answer 三列，可选第一列 subject");
        }
        Question question = new Question();
        int offset = looksLikeQuestionType(valueAt(fields, 0, ""))
                || !looksLikeQuestionType(valueAt(fields, 1, ""))
                ? 0
                : 1;
        question.setSubject(offset == 1 ? valueAt(fields, 0, "综合") : "综合");
        question.setType(valueAt(fields, offset));
        question.setContent(valueAt(fields, offset + 1));
        if (fields.size() - offset >= 7) {
            question.setOptionA(valueAt(fields, offset + 2, null));
            question.setOptionB(valueAt(fields, offset + 3, null));
            question.setOptionC(valueAt(fields, offset + 4, null));
            question.setOptionD(valueAt(fields, offset + 5, null));
            question.setAnswer(valueAt(fields, offset + 6));
            question.setDifficulty(valueAt(fields, offset + 7, "基础"));
            question.setKnowledgePoint(valueAt(fields, offset + 8, null));
            question.setAnalysis(valueAt(fields, offset + 9, null));
            question.setScore(parseScore(valueAt(fields, offset + 10, null)));
        } else {
            question.setAnswer(valueAt(fields, offset + 2));
            question.setDifficulty(valueAt(fields, offset + 3, "基础"));
            question.setKnowledgePoint(valueAt(fields, offset + 4, null));
            question.setAnalysis(valueAt(fields, offset + 5, null));
            question.setScore(parseScore(valueAt(fields, offset + 6, null)));
        }
        question.setCreatedBy(userId);
        return question;
    }

    private Question questionFromHeader(List<String> fields, Map<String, Integer> header, Long userId) {
        Question question = new Question();
        question.setSubject(defaultIfBlank(valueByHeader(fields, header, "subject", "科目", "课程", "学科"), "综合"));
        question.setType(valueByHeader(fields, header, "type", "题型", "题目类型", "类型"));
        question.setContent(valueByHeader(fields, header, "content", "题目", "题干", "题目内容", "题干内容"));
        question.setOptionA(valueByHeader(fields, header, "optiona", "option_a", "选项a", "a", "A选项"));
        question.setOptionB(valueByHeader(fields, header, "optionb", "option_b", "选项b", "b", "B选项"));
        question.setOptionC(valueByHeader(fields, header, "optionc", "option_c", "选项c", "c", "C选项"));
        question.setOptionD(valueByHeader(fields, header, "optiond", "option_d", "选项d", "d", "D选项"));
        question.setAnswer(valueByHeader(fields, header, "answer", "答案", "标准答案", "参考答案"));
        question.setAnalysis(valueByHeader(fields, header, "analysis", "解析", "答案解析"));
        question.setDifficulty(defaultIfBlank(valueByHeader(fields, header, "difficulty", "难度"), "基础"));
        question.setKnowledgePoint(valueByHeader(fields, header, "knowledgepoint", "knowledge_point", "知识点", "考点"));
        question.setCreatedBy(userId);
        question.setScore(parseScore(valueByHeader(fields, header, "score", "分值", "题目分值", "满分")));
        return question;
    }

    private boolean looksLikeHeader(List<String> fields) {
        return fields.stream()
                .map(value -> value.trim().toLowerCase(Locale.ROOT).replace("_", ""))
                .anyMatch(value -> value.equals("subject") || value.equals("科目")
                        || value.equals("type") || value.equals("题型") || value.equals("题目类型") || value.equals("类型")
                        || value.equals("content") || value.equals("题目") || value.equals("题干") || value.equals("题目内容")
                        || value.equals("optiona") || value.equals("选项a") || value.equals("a")
                        || value.equals("answer") || value.equals("答案") || value.equals("标准答案")
                        || value.equals("difficulty") || value.equals("难度")
                        || value.equals("knowledgepoint") || value.equals("知识点"));
    }

    private Map<String, Integer> buildHeader(List<String> fields) {
        Map<String, Integer> header = new HashMap<>();
        for (int i = 0; i < fields.size(); i++) {
            header.put(fields.get(i).trim().toLowerCase(Locale.ROOT).replace("_", ""), i);
        }
        return header;
    }

    private String valueByHeader(List<String> fields, Map<String, Integer> header, String... names) {
        for (String name : names) {
            Integer index = header.get(name.toLowerCase(Locale.ROOT).replace("_", ""));
            if (index != null) {
                return valueAt(fields, index, null);
            }
        }
        return null;
    }

    private List<String> parseCsvLine(String line) {
        List<String> fields = new ArrayList<>();
        StringBuilder current = new StringBuilder();
        boolean quoted = false;
        for (int i = 0; i < line.length(); i++) {
            char ch = line.charAt(i);
            if (ch == '"') {
                if (quoted && i + 1 < line.length() && line.charAt(i + 1) == '"') {
                    current.append('"');
                    i++;
                } else {
                    quoted = !quoted;
                }
            } else if (ch == ',' && !quoted) {
                fields.add(current.toString().trim());
                current.setLength(0);
            } else {
                current.append(ch);
            }
        }
        fields.add(current.toString().trim());
        return fields;
    }

    private String valueAt(List<String> values, int index) {
        return valueAt(values, index, null);
    }

    private String valueAt(List<String> values, int index, String fallback) {
        if (index < 0 || index >= values.size()) {
            return fallback;
        }
        return defaultIfBlank(values.get(index), fallback);
    }

    private Integer parseScore(String value) {
        String text = defaultIfBlank(value, null);
        if (text == null) {
            return null;
        }
        try {
            return (int) Math.round(Double.parseDouble(text.trim()));
        } catch (NumberFormatException exception) {
            throw new IllegalArgumentException("分值格式不正确：" + text);
        }
    }

    private String requireText(String value, String message) {
        if (value == null || value.trim().isEmpty()) {
            throw new IllegalArgumentException(message);
        }
        return value.trim();
    }

    private String defaultIfBlank(String value, String fallback) {
        return value == null || value.trim().isEmpty() ? fallback : value.trim();
    }

    private boolean looksLikeQuestionType(String value) {
        String text = defaultIfBlank(value, "");
        String lower = text.toLowerCase(Locale.ROOT);
        return "单选题".equals(text)
                || "单选".equals(text)
                || "选择题".equals(text)
                || "single".equals(lower)
                || "多选题".equals(text)
                || "多选".equals(text)
                || "multiple".equals(lower)
                || "填空题".equals(text)
                || "填空".equals(text)
                || "blank".equals(lower)
                || "判断题".equals(text)
                || "判断".equals(text)
                || "大题".equals(text)
                || "高数题".equals(text)
                || "高数大题".equals(text)
                || "数学大题".equals(text)
                || "编程题".equals(text)
                || "代码题".equals(text)
                || "程序题".equals(text)
                || "编程大题".equals(text);
    }
}
