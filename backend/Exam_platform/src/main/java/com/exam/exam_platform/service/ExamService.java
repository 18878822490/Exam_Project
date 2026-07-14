package com.exam.exam_platform.service;

import com.exam.exam_platform.dto.CreateExamPaperRequest;
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
import java.util.List;
import java.util.Map;

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
        if (typeCounts.isEmpty()) {
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
        for (Map.Entry<String, Integer> entry : typeCounts.entrySet()) {
            List<Question> questions = questionMapper.randomQuestions(
                    subject,
                    entry.getKey(),
                    request.getDifficulty(),
                    request.getKnowledgePoint(),
                    entry.getValue()
            );
            for (Question question : questions) {
                examMapper.insertExamQuestion(exam.getId(), question, sortNo++);
                totalScore += question.getScore();
            }
        }

        exam.setTotalScore(totalScore);
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
        createRequest.setDifficulty(request.getDifficulty());
        createRequest.setKnowledgePoint(request.getKnowledgePoint());
        createRequest.setTypeCounts(Map.of("单选题", request.getQuestionCount() == null ? 10 : request.getQuestionCount()));
        return createPaper(createRequest);
    }

    @Transactional
    public Exam copyExam(Long examId, String title, Long createdBy) {
        Long copiedId = examMapper.copyExam(examId, title, createdBy);
        if (copiedId == null) {
            throw new IllegalArgumentException("原考试不存在");
        }
        operationLogService.record(createdBy, "EXAM_COPY", "复制考试ID：" + examId);
        return findById(copiedId);
    }

    @Transactional
    public void publish(PublishExamRequest request) {
        Exam exam = findById(request.getExamId());
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

    public List<Map<String, Object>> listPublished(String className) {
        return examMapper.listPublished(className);
    }

    public Map<String, Object> dashboardStats(Long teacherId) {
        return examMapper.dashboardStats(teacherId);
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
