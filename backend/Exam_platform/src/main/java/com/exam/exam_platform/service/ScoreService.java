package com.exam.exam_platform.service;

import com.exam.exam_platform.dto.ReviewScoreRequest;
import com.exam.exam_platform.dto.SubmitExamRequest;
import com.exam.exam_platform.dto.WrongQuestionCorrectionRequest;
import com.exam.exam_platform.mapper.QuestionMapper;
import com.exam.exam_platform.mapper.ScoreMapper;
import jakarta.annotation.PostConstruct;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

@Service
public class ScoreService {
    private final ScoreMapper scoreMapper;
    private final QuestionMapper questionMapper;
    private final OperationLogService operationLogService;

    public ScoreService(ScoreMapper scoreMapper, QuestionMapper questionMapper, OperationLogService operationLogService) {
        this.scoreMapper = scoreMapper;
        this.questionMapper = questionMapper;
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
        if (request.getAnswers() == null || request.getAnswers().isEmpty()) {
            throw new IllegalArgumentException("答案不能为空");
        }

        Map<Long, String> answerMap = request.getAnswers();
        List<Map<String, Object>> keys = scoreMapper.listExamAnswerKeys(request.getExamId());
        scoreMapper.deleteAnswersForStudentExam(request.getExamId(), request.getStudentNo());
        for (Map<String, Object> row : keys) {
            Long questionId = toLong(row.get("question_id"));
            String studentAnswer = answerMap.get(questionId);
            if (studentAnswer == null) {
                continue;
            }

            String type = String.valueOf(row.get("type"));
            String standardAnswer = row.get("standard_answer") == null ? "" : String.valueOf(row.get("standard_answer"));
            double questionScore = toDouble(row.get("score"));
            boolean objective = isObjective(type);
            Double score = objective
                    ? (sameAnswer(studentAnswer, standardAnswer) ? Double.valueOf(questionScore) : Double.valueOf(0.0))
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

    public List<Map<String, Object>> studentHistory(String studentNo, String subject) {
        if (studentNo == null || studentNo.isBlank()) {
            throw new IllegalArgumentException("学生学号不能为空");
        }
        return scoreMapper.studentHistory(studentNo.trim(), subject);
    }

    public List<Map<String, Object>> classAverageTrend(String className, String subject, Integer limit) {
        return scoreMapper.classAverageTrend(className, subject, limit);
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
        result.put("questionAnalysis", scoreMapper.questionAnalysis(examId));
        result.put("scores", scoreMapper.listScores(examId, className));
        return result;
    }

    public Map<String, Object> report(Long examId, String className, String studentNo) {
        Map<String, Object> report = analysis(examId, className);
        report.put("examId", examId);
        report.put("className", className);
        if (studentNo != null && !studentNo.isBlank()) {
            String normalizedStudentNo = studentNo.trim();
            Map<String, Object> personalScore = scoreMapper.personalScore(examId, normalizedStudentNo);
            report.put("studentNo", normalizedStudentNo);
            report.put("personal", personalScore);
            report.put("personalScore", personalScore.getOrDefault("total_score", 0));
            report.put("fullScore", personalScore.getOrDefault("full_score", 0));
            report.put("typeBreakdown", scoreMapper.typeBreakdown(examId, normalizedStudentNo));
            report.put("weakKnowledgePoints", scoreMapper.weakKnowledgePoints(examId, normalizedStudentNo));
            List<Map<String, Object>> answerDetails = scoreMapper.personalAnswerDetails(examId, normalizedStudentNo);
            report.put("deductionDetails", answerDetails);
            report.put("answerDetails", answerDetails);
            report.put("personalAnswers", answerDetails);
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
        return "单选题".equals(type) || "多选题".equals(type) || "填空题".equals(type);
    }

    private boolean sameAnswer(String left, String right) {
        return normalizeAnswer(left).equals(normalizeAnswer(right));
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
}
