package com.exam.exam_platform.service;

import com.exam.exam_platform.dto.ReviewScoreRequest;
import com.exam.exam_platform.dto.SubmitExamRequest;
import com.exam.exam_platform.dto.WrongQuestionCorrectionRequest;
import com.exam.exam_platform.entity.Exam;
import com.exam.exam_platform.mapper.ExamMapper;
import com.exam.exam_platform.mapper.QuestionMapper;
import com.exam.exam_platform.mapper.ScoreMapper;
import jakarta.annotation.PostConstruct;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

@Service
public class ScoreService {
    private final ScoreMapper scoreMapper;
    private final QuestionMapper questionMapper;
    private final ExamMapper examMapper;
    private final OperationLogService operationLogService;

    public ScoreService(ScoreMapper scoreMapper,
                        QuestionMapper questionMapper,
                        ExamMapper examMapper,
                        OperationLogService operationLogService) {
        this.scoreMapper = scoreMapper;
        this.questionMapper = questionMapper;
        this.examMapper = examMapper;
        this.operationLogService = operationLogService;
    }

    @PostConstruct
    public void initializeSchema() {
        scoreMapper.initSchema();
    }

    @Transactional
    public void submitExam(SubmitExamRequest request) {
        if (request.getExamId() == null) {
            throw new IllegalArgumentException("考试ID不能为空");
        }
        if (request.getStudentNo() == null || request.getStudentNo().isBlank()) {
            throw new IllegalArgumentException("学生学号不能为空");
        }
        Map<Long, String> answerMap = request.getAnswers() == null ? Map.of() : request.getAnswers();
        List<Map<String, Object>> keys = scoreMapper.listExamAnswerKeys(request.getExamId());
        if (keys.isEmpty()) {
            throw new IllegalArgumentException("试卷题目为空，无法提交");
        }
        scoreMapper.deleteAnswersForStudentExam(request.getExamId(), request.getStudentNo());
        for (Map<String, Object> row : keys) {
            Long questionId = toLong(row.get("question_id"));
            String studentAnswer = trimToEmpty(answerMap.get(questionId));

            String type = String.valueOf(row.get("type"));
            String standardAnswer = row.get("standard_answer") == null ? "" : String.valueOf(row.get("standard_answer"));
            double questionScore = toDouble(row.get("score"));
            boolean objective = isObjective(type);
            Double score = objective
                    ? (sameAnswer(studentAnswer, standardAnswer, type) ? Double.valueOf(questionScore) : Double.valueOf(0.0))
                    : null;
            String status = objective ? "自动评分" : "待批改";

            scoreMapper.insertStudentAnswer(
                    request.getExamId(),
                    questionId,
                    request.getStudentId(),
                    request.getStudentName(),
                    request.getStudentNo(),
                    request.getClassName(),
                    studentAnswer,
                    score,
                    status
            );
        }

        scoreMapper.upsertTotalScore(
                request.getExamId(),
                request.getStudentId(),
                request.getStudentNo(),
                request.getStudentName(),
                request.getClassName()
        );
        operationLogService.record(request.getStudentId(), "EXAM_SUBMIT", "提交考试ID：" + request.getExamId());
    }

    public List<Map<String, Object>> listAnswers(Long examId, String status) {
        if (examId == null) {
            throw new IllegalArgumentException("考试ID不能为空");
        }
        return scoreMapper.listAnswers(examId, status);
    }

    public List<Map<String, Object>> listAnswerStudents(Long examId, String status) {
        return scoreMapper.listAnswerStudents(examId, status);
    }

    public List<Map<String, Object>> listStudentAnswers(Long examId, String studentNo, String status) {
        if (examId == null) {
            throw new IllegalArgumentException("考试ID不能为空");
        }
        if (studentNo == null || studentNo.isBlank()) {
            throw new IllegalArgumentException("学生学号不能为空");
        }
        return scoreMapper.listStudentAnswers(examId, studentNo.trim(), status);
    }

    public List<Map<String, Object>> listReviewExams(Long teacherId) {
        return scoreMapper.listReviewExams(teacherId);
    }

    public List<Map<String, Object>> listReviewStudents(Long examId, String status) {
        if (examId == null) {
            throw new IllegalArgumentException("考试ID不能为空");
        }
        return scoreMapper.listReviewStudents(examId, status);
    }

    public List<Map<String, Object>> listReviewStudentAnswers(Long examId, String studentNo, String status) {
        return listStudentAnswers(examId, studentNo, status);
    }

    public Map<String, Object> reviewWorkbench(Long teacherId, Long examId, String studentNo, String status) {
        List<Map<String, Object>> exams = listReviewExams(teacherId);
        Map<String, Object> selectedExam = selectExam(exams, examId);
        Map<String, Object> result = new LinkedHashMap<>();
        result.put("exams", exams);

        if (selectedExam.isEmpty()) {
            result.put("exam", Map.of());
            result.put("students", List.of());
            result.put("currentStudent", Map.of());
            result.put("answers", List.of());
            result.put("pendingAnswers", List.of());
            result.put("progress", emptyReviewProgress());
            return result;
        }

        Long selectedExamId = toLong(selectedExam.get("id"));
        List<Map<String, Object>> students = listReviewStudents(selectedExamId, status);
        Map<String, Object> currentStudent = selectStudent(students, studentNo);
        List<Map<String, Object>> answers = currentStudent.isEmpty()
                ? List.of()
                : listReviewStudentAnswers(selectedExamId, String.valueOf(currentStudent.get("student_no")), null);
        List<Map<String, Object>> pendingAnswers = currentStudent.isEmpty()
                ? List.of()
                : listReviewStudentAnswers(selectedExamId, String.valueOf(currentStudent.get("student_no")), "待批改");

        result.put("exam", selectedExam);
        result.put("students", students);
        result.put("currentStudent", currentStudent);
        result.put("answers", answers);
        result.put("pendingAnswers", pendingAnswers);
        result.put("progress", reviewProgress(selectedExam, students));
        return result;
    }

    public List<Map<String, Object>> studentHistory(String studentNo, String subject) {
        if (studentNo == null || studentNo.isBlank()) {
            throw new IllegalArgumentException("学生学号不能为空");
        }
        return scoreMapper.studentHistory(studentNo.trim(), subject);
    }

    public List<Map<String, Object>> classAverageTrend(String className, String subject, Integer limit) {
        return scoreMapper.classAverageTrend(className, subject, limit);
    }

    public Map<String, Object> classAnalysis(Long teacherId,
                                             Long examId,
                                             String className,
                                             String subject,
                                             Integer limit) {
        List<Map<String, Object>> availableExams = scoreMapper.listScoreExams(teacherId, className, subject, limit);
        Long selectedExamId = examId;
        if ((selectedExamId == null || selectedExamId <= 0) && !availableExams.isEmpty()) {
            selectedExamId = toLong(availableExams.get(0).get("id"));
        }

        Map<String, Object> result = new LinkedHashMap<>();
        result.put("availableExams", availableExams);
        result.put("className", className);
        result.put("subject", subject);
        result.put("trend", classAverageTrend(className, subject, limit));

        if (selectedExamId == null || selectedExamId <= 0) {
            result.put("exam", Map.of());
            result.put("summary", emptyScoreSummary());
            result.put("distribution", List.of());
            result.put("levelDistribution", List.of());
            result.put("scores", List.of());
            result.put("questionAnalysis", List.of());
            return result;
        }

        Exam exam = examMapper.findById(selectedExamId);
        Map<String, Object> analysis = analysis(selectedExamId, className);
        result.put("exam", exam == null ? Map.of("id", selectedExamId) : exam);
        result.put("summary", analysis.get("summary"));
        result.put("distribution", analysis.get("distribution"));
        result.put("scores", analysis.get("scores"));
        result.put("questionAnalysis", analysis.get("questionAnalysis"));
        result.put("levelDistribution", buildLevelDistribution(castList(analysis.get("scores"))));
        return result;
    }

    @Transactional
    public void review(ReviewScoreRequest request) {
        if (request.getAnswerId() == null) {
            throw new IllegalArgumentException("答卷ID不能为空");
        }
        if (request.getScore() == null || request.getScore() < 0) {
            throw new IllegalArgumentException("评分不能为空");
        }
        Map<String, Object> answer = scoreMapper.findAnswerById(request.getAnswerId());
        if (answer == null) {
            throw new IllegalArgumentException("答卷不存在");
        }
        String questionType = String.valueOf(answer.getOrDefault("type", ""));
        if (isObjective(questionType)) {
            throw new IllegalArgumentException("选择题、判断题和填空题已由系统自动评分，只有编程题等主观题需要教师手动批改");
        }
        Double maxScore = toNullableDouble(answer.get("question_score"));
        if (maxScore != null && request.getScore() > maxScore) {
            throw new IllegalArgumentException("评分不能超过本题满分：" + maxScore);
        }

        scoreMapper.updateReviewScore(request.getAnswerId(), request.getScore(), request.getComment());
        scoreMapper.upsertTotalScore(
                toLong(answer.get("exam_id")),
                toLong(answer.get("student_id")),
                String.valueOf(answer.get("student_no")),
                answer.get("student_name") == null ? null : String.valueOf(answer.get("student_name")),
                answer.get("class_name") == null ? null : String.valueOf(answer.get("class_name"))
        );
        operationLogService.record(request.getTeacherId(), "EXAM_REVIEW", "批改答卷ID：" + request.getAnswerId());
    }

    public Map<String, Object> analysis(Long examId, String className) {
        if (examId == null) {
            throw new IllegalArgumentException("考试ID不能为空");
        }
        Map<String, Object> result = new LinkedHashMap<>();
        result.put("summary", scoreMapper.scoreSummary(examId, className));
        result.put("distribution", scoreMapper.scoreDistribution(examId, className));
        result.put("questionAnalysis", scoreMapper.questionAnalysis(examId, className));
        List<Map<String, Object>> scores = scoreMapper.listScores(examId, className);
        result.put("scores", scores);
        result.put("levelDistribution", buildLevelDistribution(scores));
        return result;
    }

    public Map<String, Object> report(Long examId, String className, String studentNo) {
        String normalizedStudentNo = studentNo == null || studentNo.isBlank() ? null : studentNo.trim();
        Map<String, Object> personalScore = normalizedStudentNo == null
                ? Map.of()
                : scoreMapper.personalScore(examId, normalizedStudentNo);
        String effectiveClassName = className;
        if ((effectiveClassName == null || effectiveClassName.isBlank()) && !personalScore.isEmpty()) {
            Object personalClassName = personalScore.get("class_name");
            if (personalClassName != null && !String.valueOf(personalClassName).isBlank()) {
                effectiveClassName = String.valueOf(personalClassName);
            }
        }

        Map<String, Object> report = analysis(examId, effectiveClassName);
        report.put("examId", examId);
        report.put("className", effectiveClassName);
        if (normalizedStudentNo != null) {
            Map<String, Object> reviewSummary = scoreMapper.studentReviewSummary(examId, normalizedStudentNo);
            report.put("studentNo", normalizedStudentNo);
            report.put("personal", personalScore);
            report.put("personalScore", personalScore.getOrDefault("total_score", 0));
            report.put("fullScore", personalScore.getOrDefault("full_score", 0));
            report.put("reviewStatus", reviewSummary.getOrDefault("review_status", "暂无提交"));
            report.put("pendingCount", reviewSummary.getOrDefault("pending_count", 0));
            report.put("answerCount", reviewSummary.getOrDefault("answer_count", 0));
            report.put("typeBreakdown", scoreMapper.typeBreakdown(examId, normalizedStudentNo));
            report.put("weakKnowledgePoints", scoreMapper.weakKnowledgePoints(examId, normalizedStudentNo));
            List<Map<String, Object>> answerDetails = scoreMapper.personalAnswerDetails(examId, normalizedStudentNo);
            report.put("deductionDetails", answerDetails);
            report.put("answerDetails", answerDetails);
            report.put("personalAnswers", answerDetails);
        }
        return report;
    }

    public Map<String, Object> printReport(Long examId,
                                           String className,
                                           String reportType,
                                           List<String> studentNos) {
        if (examId == null) {
            throw new IllegalArgumentException("考试ID不能为空");
        }
        List<String> normalizedStudentNos = normalizeStudentNos(studentNos);
        String personalStudentNo = null;
        if (normalizedStudentNos.size() == 1) {
            personalStudentNo = normalizedStudentNos.get(0);
        }
        Map<String, Object> report = report(examId, className, personalStudentNo);
        report.put("reportType", reportType == null || reportType.isBlank() ? "班级成绩总表" : reportType.trim());
        report.put("generatedTime", LocalDateTime.now());
        report.put("selectedStudentNos", normalizedStudentNos);
        if (!normalizedStudentNos.isEmpty()) {
            report.put("scores", filterScoresByStudentNos(castList(report.get("scores")), normalizedStudentNos));
        }
        return report;
    }

    public List<Map<String, Object>> wrongQuestions(String studentNo) {
        if (studentNo == null || studentNo.isBlank()) {
            throw new IllegalArgumentException("学生学号不能为空");
        }
        List<Map<String, Object>> rows = new java.util.ArrayList<>();
        rows.addAll(scoreMapper.wrongQuestions(studentNo.trim()));
        rows.addAll(questionMapper.wrongPracticeQuestions(studentNo.trim()));
        rows.sort((left, right) -> String.valueOf(right.get("created_time")).compareTo(String.valueOf(left.get("created_time"))));
        return rows;
    }

    @Transactional
    public void saveWrongQuestionCorrection(WrongQuestionCorrectionRequest request) {
        if (request.getAnswerId() == null) {
            throw new IllegalArgumentException("答题记录ID不能为空");
        }
        if (request.getStudentNo() == null || request.getStudentNo().isBlank()) {
            throw new IllegalArgumentException("学生学号不能为空");
        }
        String correctionAnswer = trimToEmpty(request.getCorrectionAnswer());
        String errorReason = trimToEmpty(request.getErrorReason());
        String knowledgeSummary = trimToEmpty(request.getKnowledgeSummary());
        if (correctionAnswer.isBlank() && errorReason.isBlank() && knowledgeSummary.isBlank()) {
            throw new IllegalArgumentException("请填写订正答案、错误原因或知识点总结");
        }

        boolean practiceSource = "practice".equalsIgnoreCase(trimToEmpty(request.getSourceType()));
        boolean updated = practiceSource
                ? questionMapper.savePracticeCorrection(
                        request.getAnswerId(),
                        request.getStudentNo().trim(),
                        correctionAnswer,
                        errorReason,
                        knowledgeSummary
                )
                : scoreMapper.saveWrongQuestionCorrection(
                        request.getAnswerId(),
                        request.getStudentNo().trim(),
                        correctionAnswer,
                        errorReason,
                        knowledgeSummary
                );
        if (!updated) {
            throw new IllegalArgumentException("错题记录不存在或不属于当前学生");
        }
        operationLogService.record(null, "WRONG_QUESTION_CORRECTION", "学生订正答题记录ID：" + request.getAnswerId());
    }

    private boolean isObjective(String type) {
        String normalized = normalizeQuestionType(type);
        return "单选题".equals(normalized)
                || "多选题".equals(normalized)
                || "判断题".equals(normalized)
                || "填空题".equals(normalized);
    }

    private String normalizeQuestionType(String type) {
        String text = trimToEmpty(type);
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
        if ("program".equals(lower) || "coding".equals(lower) || "code".equals(lower) || "代码题".equals(text)) {
            return "编程题";
        }
        if ("math".equals(lower) || "高数题".equals(text) || "数学大题".equals(text) || "高数大题".equals(text)) {
            return "编程题";
        }
        return text;
    }

    private Map<String, Object> selectExam(List<Map<String, Object>> exams, Long examId) {
        if (exams == null || exams.isEmpty()) {
            return Map.of();
        }
        if (examId != null && examId > 0) {
            for (Map<String, Object> exam : exams) {
                if (examId.equals(toLong(exam.get("id")))) {
                    return exam;
                }
            }
        }
        for (Map<String, Object> exam : exams) {
            if (toInt(exam.get("pending_answer_count")) > 0 || toInt(exam.get("submitted_count")) > 0) {
                return exam;
            }
        }
        return exams.get(0);
    }

    private Map<String, Object> selectStudent(List<Map<String, Object>> students, String studentNo) {
        if (students == null || students.isEmpty()) {
            return Map.of();
        }
        if (studentNo != null && !studentNo.isBlank()) {
            String target = studentNo.trim();
            for (Map<String, Object> student : students) {
                if (target.equals(String.valueOf(student.get("student_no")))) {
                    return student;
                }
            }
        }
        for (Map<String, Object> student : students) {
            if (toInt(student.get("pending_count")) > 0) {
                return student;
            }
        }
        return students.get(0);
    }

    private Map<String, Object> reviewProgress(Map<String, Object> exam, List<Map<String, Object>> students) {
        int totalStudents = students == null ? 0 : students.size();
        int completedStudents = 0;
        int pendingStudents = 0;
        if (students != null) {
            for (Map<String, Object> student : students) {
                int pendingCount = toInt(student.get("pending_count"));
                if (pendingCount == 0) {
                    completedStudents++;
                } else {
                    pendingStudents++;
                }
            }
        }
        Map<String, Object> progress = new LinkedHashMap<>();
        progress.put("submittedCount", toInt(exam.get("submitted_count")));
        progress.put("completedCount", completedStudents);
        progress.put("totalStudents", totalStudents);
        progress.put("pendingStudents", pendingStudents);
        progress.put("pendingAnswerCount", toInt(exam.get("pending_answer_count")));
        progress.put("averageScore", exam.getOrDefault("average_score", 0));
        progress.put("percent", totalStudents == 0 ? 0 : Math.round(completedStudents * 1000.0 / totalStudents) / 10.0);
        return progress;
    }

    private Map<String, Object> emptyReviewProgress() {
        Map<String, Object> progress = new LinkedHashMap<>();
        progress.put("submittedCount", 0);
        progress.put("completedCount", 0);
        progress.put("totalStudents", 0);
        progress.put("pendingStudents", 0);
        progress.put("pendingAnswerCount", 0);
        progress.put("averageScore", 0);
        progress.put("percent", 0);
        return progress;
    }

    private Map<String, Object> emptyScoreSummary() {
        Map<String, Object> summary = new LinkedHashMap<>();
        summary.put("average_score", 0);
        summary.put("highest_score", 0);
        summary.put("lowest_score", 0);
        summary.put("student_count", 0);
        summary.put("pass_rate", 0);
        summary.put("excellent_rate", 0);
        return summary;
    }

    private List<Map<String, Object>> buildLevelDistribution(List<Map<String, Object>> scores) {
        int excellent = 0;
        int good = 0;
        int medium = 0;
        int pass = 0;
        int fail = 0;
        for (Map<String, Object> row : scores) {
            double score = toDouble(row.getOrDefault("total_score", row.get("score")));
            if (score >= 90) {
                excellent++;
            } else if (score >= 80) {
                good++;
            } else if (score >= 70) {
                medium++;
            } else if (score >= 60) {
                pass++;
            } else {
                fail++;
            }
        }
        List<Map<String, Object>> levels = new ArrayList<>();
        levels.add(levelRow("优秀", excellent));
        levels.add(levelRow("良好", good));
        levels.add(levelRow("中等", medium));
        levels.add(levelRow("及格", pass));
        levels.add(levelRow("不及格", fail));
        return levels;
    }

    private Map<String, Object> levelRow(String label, int value) {
        Map<String, Object> row = new LinkedHashMap<>();
        row.put("label", label);
        row.put("value", value);
        return row;
    }

    private List<Map<String, Object>> filterScoresByStudentNos(List<Map<String, Object>> scores, List<String> studentNos) {
        List<String> normalized = normalizeStudentNos(studentNos);
        if (normalized.isEmpty()) {
            return scores;
        }
        List<Map<String, Object>> filtered = new ArrayList<>();
        for (Map<String, Object> row : scores) {
            String studentNo = String.valueOf(row.getOrDefault("student_no", row.get("studentNo")));
            if (normalized.contains(studentNo)) {
                filtered.add(row);
            }
        }
        return filtered;
    }

    private List<String> normalizeStudentNos(List<String> studentNos) {
        if (studentNos == null || studentNos.isEmpty()) {
            return List.of();
        }
        List<String> normalized = new ArrayList<>();
        for (String value : studentNos) {
            if (value == null || value.isBlank()) {
                continue;
            }
            for (String part : value.split("[,，;；\\s]+")) {
                String item = part.trim();
                if (!item.isEmpty() && !normalized.contains(item)) {
                    normalized.add(item);
                }
            }
        }
        return normalized;
    }

    @SuppressWarnings("unchecked")
    private List<Map<String, Object>> castList(Object value) {
        return value instanceof List<?> list ? (List<Map<String, Object>>) list : List.of();
    }

    private boolean sameAnswer(String left, String right, String type) {
        String normalizedType = normalizeQuestionType(type);
        if ("多选题".equals(normalizedType)) {
            return normalizeChoiceAnswer(left).equals(normalizeChoiceAnswer(right));
        }
        if ("单选题".equals(normalizedType)) {
            return normalizeChoiceAnswer(left).equals(normalizeChoiceAnswer(right));
        }
        if ("判断题".equals(normalizedType)) {
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

    private String trimToEmpty(String value) {
        return value == null ? "" : value.trim();
    }

    private Long toLong(Object value) {
        if (value == null) {
            return null;
        }
        if (value instanceof Number number) {
            return number.longValue();
        }
        return Long.parseLong(String.valueOf(value));
    }

    private double toDouble(Object value) {
        if (value == null) {
            return 0;
        }
        if (value instanceof BigDecimal decimal) {
            return decimal.doubleValue();
        }
        if (value instanceof Number number) {
            return number.doubleValue();
        }
        return Double.parseDouble(String.valueOf(value));
    }

    private Double toNullableDouble(Object value) {
        if (value == null) {
            return null;
        }
        if (value instanceof BigDecimal decimal) {
            return decimal.doubleValue();
        }
        if (value instanceof Number number) {
            return number.doubleValue();
        }
        String text = String.valueOf(value).trim();
        return text.isEmpty() ? null : Double.parseDouble(text);
    }

    private int toInt(Object value) {
        if (value == null) {
            return 0;
        }
        if (value instanceof Number number) {
            return number.intValue();
        }
        String text = String.valueOf(value).trim();
        return text.isEmpty() ? 0 : Integer.parseInt(text);
    }
}
