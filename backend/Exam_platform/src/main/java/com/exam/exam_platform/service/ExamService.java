package com.exam.exam_platform.service;

import com.exam.exam_platform.dto.CreateExamPaperRequest;
import com.exam.exam_platform.dto.PaperQuestionOrderRequest;
import com.exam.exam_platform.dto.PaperQuestionRequest;
import com.exam.exam_platform.dto.PublishExamRequest;
import com.exam.exam_platform.entity.Exam;
import com.exam.exam_platform.entity.GenerateExamRequest;
import com.exam.exam_platform.entity.Question;
import com.exam.exam_platform.mapper.ExamMapper;
import com.exam.exam_platform.mapper.QuestionMapper;
import jakarta.annotation.PostConstruct;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.time.LocalDateTime;

@Service
public class ExamService {
    private final ExamMapper examMapper;
    private final QuestionMapper questionMapper;
    private final OperationLogService operationLogService;

    public ExamService(ExamMapper examMapper,
                       QuestionMapper questionMapper,
                       OperationLogService operationLogService) {
        this.examMapper = examMapper;
        this.questionMapper = questionMapper;
        this.operationLogService = operationLogService;
    }

    @PostConstruct
    public void initializeSchema() {
        examMapper.initSchema();
    }

    public List<Exam> list(Long createdBy, String status) {
        return examMapper.list(createdBy, status);
    }

    public Exam findById(Long id) {
        Exam exam = examMapper.findById(id);
        if (exam == null) {
            throw new IllegalArgumentException("考试不存在");
        }
        return exam;
    }

    public List<Map<String, Object>> preview(Long examId) {
        findById(examId);
        return examMapper.listExamQuestions(examId);
    }

    @Transactional
    public Exam createPaper(CreateExamPaperRequest request) {
        String title = requireText(request.getTitle(), "考试名称不能为空");
        String subject = defaultText(request.getSubject(), "综合");
        Map<String, Integer> typeCounts = normalizeTypeCounts(request.getTypeCounts());
        List<Long> selectedQuestionIds = normalizeQuestionIds(request.getQuestionIds());
        if (typeCounts.isEmpty() && selectedQuestionIds.isEmpty()) {
            throw new IllegalArgumentException("至少选择一种题型数量");
        }

        Exam exam = new Exam();
        exam.setTitle(title);
        exam.setSubject(subject);
        exam.setStartTime(request.getStartTime());
        exam.setEndTime(request.getEndTime());
        exam.setDuration(request.getDuration() == null ? 120 : request.getDuration());
        exam.setStatus("草稿");
        exam.setTotalScore(0);
        exam.setCreatedBy(request.getCreatedBy());
        examMapper.insertExam(exam);

        int totalScore = 0;
        int sortNo = 1;
        if (!selectedQuestionIds.isEmpty()) {
            for (Long questionId : selectedQuestionIds) {
                Question question = questionMapper.findById(questionId);
                if (question == null) {
                    throw new IllegalArgumentException("题目不存在：" + questionId);
                }
                examMapper.insertExamQuestion(exam.getId(), question, sortNo++);
                totalScore += question.getScore() == null ? 0 : question.getScore();
            }
        } else {
            for (Map.Entry<String, Integer> entry : typeCounts.entrySet()) {
                List<Question> questions = questionMapper.randomQuestions(
                        subject,
                        entry.getKey(),
                        request.getDifficulty(),
                        request.getKnowledgePoint(),
                        entry.getValue()
                );
                if (questions.size() < entry.getValue()) {
                    throw new IllegalArgumentException(entry.getKey() + "可用题目不足，需要"
                            + entry.getValue() + "题，实际" + questions.size() + "题");
                }
                for (Question question : questions) {
                    examMapper.insertExamQuestion(exam.getId(), question, sortNo++);
                    totalScore += question.getScore() == null ? 0 : question.getScore();
                }
            }
        }

        exam.setTotalScore(totalScore);
        enforceMaxTotalScore(totalScore, request.getMaxTotalScore());
        examMapper.updateTotalScore(exam.getId(), totalScore);
        operationLogService.record(request.getCreatedBy(), "EXAM_CREATE", "生成试卷：" + title);
        return exam;
    }

    @Transactional
    public Exam generateByLegacyRequest(GenerateExamRequest request) {
        CreateExamPaperRequest createRequest = new CreateExamPaperRequest();
        createRequest.setTitle(request.getTitle());
        createRequest.setSubject("综合");
        createRequest.setDuration(request.getDuration());
        createRequest.setCreatedBy(request.getCreatedBy());
        createRequest.setMaxTotalScore(request.getMaxTotalScore());
        createRequest.setDifficulty(request.getDifficulty());
        createRequest.setKnowledgePoint(request.getKnowledgePoint());
        createRequest.setTypeCounts(Map.of("单选题", request.getQuestionCount() == null ? 10 : request.getQuestionCount()));
        return createPaper(createRequest);
    }

    @Transactional
    public Exam addQuestionToPaper(Long examId, PaperQuestionRequest request) {
        Exam exam = findEditablePaper(examId);
        if (request == null || request.getQuestionId() == null) {
            throw new IllegalArgumentException("题目ID不能为空");
        }
        Question question = requireQuestion(request.getQuestionId());
        int sortNo = request.getSortNo() == null || request.getSortNo() <= 0
                ? examMapper.nextQuestionSortNo(examId)
                : request.getSortNo();
        int score = resolveQuestionScore(question, request.getScore());
        Integer existingScore = examMapper.scoreForExamQuestion(examId, question.getId());
        int nextTotalScore = examMapper.totalScoreForExam(examId) - (existingScore == null ? 0 : existingScore) + score;
        enforceMaxTotalScore(nextTotalScore, request.getMaxTotalScore());
        examMapper.upsertExamQuestion(examId, question.getId(), sortNo, score);
        refreshTotalScore(examId);
        operationLogService.record(request.getUserId() == null ? exam.getCreatedBy() : request.getUserId(),
                "EXAM_QUESTION_ADD", "试卷ID：" + examId + " 添加题目ID：" + question.getId());
        return findById(examId);
    }

    @Transactional
    public Exam updatePaperQuestion(Long examId, Long questionId, PaperQuestionRequest request) {
        Exam exam = findEditablePaper(examId);
        Question question = requireQuestion(questionId);
        Integer currentSortNo = examMapper.sortNoForExamQuestion(examId, questionId);
        if (currentSortNo == null) {
            throw new IllegalArgumentException("试卷中不存在该题目");
        }
        int sortNo = request != null && request.getSortNo() != null && request.getSortNo() > 0
                ? request.getSortNo()
                : currentSortNo;
        int score = resolveQuestionScore(question, request == null ? null : request.getScore());
        if (!examMapper.updateExamQuestion(examId, questionId, sortNo, score)) {
            throw new IllegalArgumentException("试卷中不存在该题目");
        }
        int totalScore = refreshTotalScore(examId);
        enforceMaxTotalScore(totalScore, request == null ? null : request.getMaxTotalScore());
        operationLogService.record(request == null || request.getUserId() == null ? exam.getCreatedBy() : request.getUserId(),
                "EXAM_QUESTION_UPDATE", "试卷ID：" + examId + " 更新题目ID：" + questionId);
        return findById(examId);
    }

    @Transactional
    public Exam removeQuestionFromPaper(Long examId, Long questionId, Long userId) {
        Exam exam = findEditablePaper(examId);
        if (questionId == null) {
            throw new IllegalArgumentException("题目ID不能为空");
        }
        if (!examMapper.deleteExamQuestion(examId, questionId)) {
            throw new IllegalArgumentException("试卷中不存在该题目");
        }
        refreshTotalScore(examId);
        operationLogService.record(userId == null ? exam.getCreatedBy() : userId,
                "EXAM_QUESTION_REMOVE", "试卷ID：" + examId + " 移除题目ID：" + questionId);
        return findById(examId);
    }

    @Transactional
    public Exam reorderPaperQuestions(Long examId, PaperQuestionOrderRequest request) {
        Exam exam = findEditablePaper(examId);
        List<PaperQuestionOrderRequest.Item> items = normalizePaperItems(request);
        if (items.isEmpty()) {
            throw new IllegalArgumentException("题目顺序不能为空");
        }
        int sortNo = 1;
        for (PaperQuestionOrderRequest.Item item : items) {
            Question question = requireQuestion(item.getQuestionId());
            int score = resolveQuestionScore(question, item.getScore());
            int nextSortNo = item.getSortNo() == null || item.getSortNo() <= 0 ? sortNo : item.getSortNo();
            if (!examMapper.updateExamQuestion(examId, question.getId(), nextSortNo, score)) {
                throw new IllegalArgumentException("试卷中不存在题目：" + question.getId());
            }
            sortNo++;
        }
        int totalScore = refreshTotalScore(examId);
        enforceMaxTotalScore(totalScore, request == null ? null : request.getMaxTotalScore());
        operationLogService.record(request == null || request.getUserId() == null ? exam.getCreatedBy() : request.getUserId(),
                "EXAM_QUESTION_REORDER", "试卷ID：" + examId + " 调整题目顺序");
        return findById(examId);
    }

    @Transactional
    public Exam replacePaperQuestions(Long examId, PaperQuestionOrderRequest request) {
        Exam exam = findEditablePaper(examId);
        List<PaperQuestionOrderRequest.Item> items = normalizePaperItems(request);
        if (items.isEmpty()) {
            throw new IllegalArgumentException("试卷题目不能为空");
        }
        int totalScore = 0;
        for (PaperQuestionOrderRequest.Item item : items) {
            Question question = requireQuestion(item.getQuestionId());
            totalScore += resolveQuestionScore(question, item.getScore());
        }
        enforceMaxTotalScore(totalScore, request == null ? null : request.getMaxTotalScore());
        examMapper.deleteExamQuestions(examId);
        int sortNo = 1;
        for (PaperQuestionOrderRequest.Item item : items) {
            Question question = requireQuestion(item.getQuestionId());
            int score = resolveQuestionScore(question, item.getScore());
            int nextSortNo = item.getSortNo() == null || item.getSortNo() <= 0 ? sortNo : item.getSortNo();
            examMapper.upsertExamQuestion(examId, question.getId(), nextSortNo, score);
            sortNo++;
        }
        examMapper.updateTotalScore(examId, totalScore);
        operationLogService.record(request == null || request.getUserId() == null ? exam.getCreatedBy() : request.getUserId(),
                "EXAM_QUESTION_REPLACE", "试卷ID：" + examId + " 保存题目列表");
        return findById(examId);
    }

    @Transactional
    public Exam copyExam(Long examId, String title, Long createdBy) {
        return copyExam(examId, title, createdBy, null, null);
    }

    @Transactional
    public Exam copyExam(Long examId, String title, Long createdBy, LocalDateTime startTime, LocalDateTime endTime) {
        Long copiedId = examMapper.copyExam(examId, title, createdBy, startTime, endTime);
        if (copiedId == null) {
            throw new IllegalArgumentException("原考试不存在");
        }
        operationLogService.record(createdBy, "EXAM_COPY", "复制考试ID：" + examId);
        return findById(copiedId);
    }

    @Transactional
    public void publish(PublishExamRequest request) {
        Exam exam = findById(request.getExamId());
        if (examMapper.countExamQuestions(exam.getId()) == 0) {
            throw new IllegalArgumentException("试卷中还没有题目，不能发布");
        }
        if (request.getStartTime() != null
                && request.getEndTime() != null
                && !request.getEndTime().isAfter(request.getStartTime())) {
            throw new IllegalArgumentException("考试结束时间必须晚于开始时间");
        }
        String status = request.getStatus() == null || request.getStatus().isBlank() ? "已发布" : request.getStatus();

        int publishedCount = 0;
        if (request.getClassIds() != null) {
            for (Long classId : request.getClassIds()) {
                examMapper.publish(exam.getId(), classId, null, request.getStartTime(), request.getEndTime(), status, request.getCreatedBy());
                publishedCount++;
            }
        }
        if (request.getClassNames() != null) {
            for (String className : request.getClassNames()) {
                if (className != null && !className.isBlank()) {
                    examMapper.publish(exam.getId(), null, className.trim(), request.getStartTime(), request.getEndTime(), status, request.getCreatedBy());
                    publishedCount++;
                }
            }
        }
        if (publishedCount == 0) {
            throw new IllegalArgumentException("请选择目标班级");
        }

        examMapper.updateStatus(exam.getId(), status);
        operationLogService.record(request.getCreatedBy(), "EXAM_PUBLISH", "发布考试：" + exam.getTitle());
    }

    public List<Map<String, Object>> listPublished(String className, String studentNo) {
        return examMapper.listPublished(className, studentNo);
    }

    public Map<String, Object> dashboardStats(Long teacherId) {
        return examMapper.dashboardStats(teacherId);
    }

    private Exam findEditablePaper(Long examId) {
        Exam exam = findById(examId);
        if (examMapper.hasSubmittedAnswers(examId)) {
            throw new IllegalArgumentException("已有学生提交答卷，不能再修改试卷题目");
        }
        return exam;
    }

    private Question requireQuestion(Long questionId) {
        if (questionId == null || questionId <= 0) {
            throw new IllegalArgumentException("题目ID不能为空");
        }
        Question question = questionMapper.findById(questionId);
        if (question == null) {
            throw new IllegalArgumentException("题目不存在：" + questionId);
        }
        return question;
    }

    private int resolveQuestionScore(Question question, Integer requestScore) {
        if (requestScore != null && requestScore > 0) {
            return requestScore;
        }
        return question.getScore() == null || question.getScore() <= 0 ? 1 : question.getScore();
    }

    private int refreshTotalScore(Long examId) {
        int totalScore = examMapper.totalScoreForExam(examId);
        examMapper.updateTotalScore(examId, totalScore);
        return totalScore;
    }

    private void enforceMaxTotalScore(int totalScore, Integer maxTotalScore) {
        if (maxTotalScore != null && maxTotalScore > 0 && totalScore > maxTotalScore) {
            throw new IllegalArgumentException("试卷总分 " + totalScore + " 已超过设定满分 " + maxTotalScore);
        }
    }

    private List<PaperQuestionOrderRequest.Item> normalizePaperItems(PaperQuestionOrderRequest request) {
        if (request == null) {
            return List.of();
        }
        if (request.getQuestions() != null && !request.getQuestions().isEmpty()) {
            Map<Long, PaperQuestionOrderRequest.Item> deduped = new LinkedHashMap<>();
            for (PaperQuestionOrderRequest.Item item : request.getQuestions()) {
                if (item != null && item.getQuestionId() != null && item.getQuestionId() > 0) {
                    deduped.putIfAbsent(item.getQuestionId(), item);
                }
            }
            return List.copyOf(deduped.values());
        }
        if (request.getQuestionIds() == null || request.getQuestionIds().isEmpty()) {
            return List.of();
        }
        return request.getQuestionIds().stream()
                .filter(id -> id != null && id > 0)
                .map(id -> {
                    PaperQuestionOrderRequest.Item item = new PaperQuestionOrderRequest.Item();
                    item.setQuestionId(id);
                    return item;
                })
                .toList();
    }

    private Map<String, Integer> normalizeTypeCounts(Map<String, Integer> source) {
        Map<String, Integer> result = new LinkedHashMap<>();
        if (source == null) {
            return result;
        }
        for (Map.Entry<String, Integer> entry : source.entrySet()) {
            if (entry.getKey() != null && entry.getValue() != null && entry.getValue() > 0) {
                result.put(entry.getKey().trim(), entry.getValue());
            }
        }
        return result;
    }

    private List<Long> normalizeQuestionIds(List<Long> source) {
        if (source == null || source.isEmpty()) {
            return List.of();
        }
        Set<Long> deduped = new LinkedHashSet<>();
        for (Long id : source) {
            if (id != null && id > 0) {
                deduped.add(id);
            }
        }
        return List.copyOf(deduped);
    }

    private String requireText(String value, String message) {
        if (value == null || value.trim().isEmpty()) {
            throw new IllegalArgumentException(message);
        }
        return value.trim();
    }

    private String defaultText(String value, String fallback) {
        return value == null || value.trim().isEmpty() ? fallback : value.trim();
    }
}
