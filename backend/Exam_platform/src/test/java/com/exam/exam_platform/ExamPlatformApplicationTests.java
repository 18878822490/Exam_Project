package com.exam.exam_platform;

import com.exam.exam_platform.dto.SubmitExamRequest;
import com.exam.exam_platform.entity.Exam;
import com.exam.exam_platform.entity.Question;
import com.exam.exam_platform.mapper.ExamMapper;
import com.exam.exam_platform.mapper.QuestionMapper;
import com.exam.exam_platform.service.ScoreService;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Map;

@SpringBootTest
class ExamPlatformApplicationTests {

    @Autowired
    private QuestionMapper questionMapper;

    @Autowired
    private ExamMapper examMapper;

    @Autowired
    private ScoreService scoreService;

    @Test
    void contextLoads() {
    }

    @Test
    @Transactional
    void submitExamAutoScoresImportedSingleAlias() {
        Question question = new Question();
        question.setSubject("CodexAutoScoreTest");
        question.setType("single");
        question.setContent("HTTP 默认端口是？");
        question.setOptionA("80");
        question.setOptionB("443");
        question.setAnswer("A");
        question.setAnalysis("HTTP 默认使用 80 端口。");
        question.setDifficulty("基础");
        question.setKnowledgePoint("计算机网络");
        question.setScore(10);
        questionMapper.insert(question);

        Exam exam = new Exam();
        exam.setTitle("Codex Auto Score Alias Test");
        exam.setSubject("CodexAutoScoreTest");
        exam.setDuration(30);
        exam.setTotalScore(10);
        exam.setStatus("已发布");
        examMapper.insertExam(exam);
        examMapper.insertExamQuestion(exam.getId(), question, 1);

        SubmitExamRequest request = new SubmitExamRequest();
        request.setExamId(exam.getId());
        request.setStudentId(0L);
        request.setStudentName("CodexTestStudent");
        request.setStudentNo("CodexAutoScoreStudent");
        request.setClassName("CodexTestClass");
        request.setAnswers(Map.of(question.getId(), "A"));

        scoreService.submitExam(request);

        List<Map<String, Object>> answers = scoreService.listStudentAnswers(
                exam.getId(),
                "CodexAutoScoreStudent",
                null
        );
        Assertions.assertEquals(1, answers.size());
        Assertions.assertEquals("单选题", String.valueOf(answers.get(0).get("type")));
        Assertions.assertEquals("自动评分", String.valueOf(answers.get(0).get("review_status")));
        Assertions.assertEquals(10.0, ((Number) answers.get(0).get("score")).doubleValue(), 0.001);
        Assertions.assertEquals(1, ((Number) answers.get(0).get("is_objective")).intValue());

        Map<String, Object> report = scoreService.report(exam.getId(), "CodexTestClass", "CodexAutoScoreStudent");
        List<Map<String, Object>> typeBreakdown = (List<Map<String, Object>>) report.get("typeBreakdown");
        Assertions.assertEquals("单选题", String.valueOf(typeBreakdown.get(0).get("type")));
        List<Map<String, Object>> answerDetails = (List<Map<String, Object>>) report.get("answerDetails");
        Assertions.assertEquals("单选题", String.valueOf(answerDetails.get(0).get("type")));
    }

    @Test
    @Transactional
    void submitExamAutoScoresImportedMultipleAliasWithSeparatedAnswer() {
        Question question = new Question();
        question.setSubject("CodexAutoScoreTest");
        question.setType("multiple");
        question.setContent("下列属于关系型数据库的是？");
        question.setOptionA("MySQL");
        question.setOptionB("Redis");
        question.setOptionC("PostgreSQL");
        question.setOptionD("MongoDB");
        question.setAnswer("A,C");
        question.setAnalysis("MySQL 与 PostgreSQL 属于关系型数据库。");
        question.setDifficulty("基础");
        question.setKnowledgePoint("数据库");
        question.setScore(12);
        questionMapper.insert(question);

        Exam exam = new Exam();
        exam.setTitle("Codex Auto Score Multiple Alias Test");
        exam.setSubject("CodexAutoScoreTest");
        exam.setDuration(30);
        exam.setTotalScore(12);
        exam.setStatus("已发布");
        examMapper.insertExam(exam);
        examMapper.insertExamQuestion(exam.getId(), question, 1);

        SubmitExamRequest request = new SubmitExamRequest();
        request.setExamId(exam.getId());
        request.setStudentId(0L);
        request.setStudentName("CodexTestStudent");
        request.setStudentNo("CodexAutoScoreStudent");
        request.setClassName("CodexTestClass");
        request.setAnswers(Map.of(question.getId(), "CA"));

        scoreService.submitExam(request);

        List<Map<String, Object>> answers = scoreService.listStudentAnswers(
                exam.getId(),
                "CodexAutoScoreStudent",
                null
        );
        Assertions.assertEquals(1, answers.size());
        Assertions.assertEquals("多选题", String.valueOf(answers.get(0).get("type")));
        Assertions.assertEquals("自动评分", String.valueOf(answers.get(0).get("review_status")));
        Assertions.assertEquals(12.0, ((Number) answers.get(0).get("score")).doubleValue(), 0.001);
        Assertions.assertEquals(1, ((Number) answers.get(0).get("is_objective")).intValue());

        Map<String, Object> report = scoreService.report(exam.getId(), "CodexTestClass", "CodexAutoScoreStudent");
        List<Map<String, Object>> typeBreakdown = (List<Map<String, Object>>) report.get("typeBreakdown");
        Assertions.assertEquals("多选题", String.valueOf(typeBreakdown.get(0).get("type")));
        List<Map<String, Object>> answerDetails = (List<Map<String, Object>>) report.get("answerDetails");
        Assertions.assertEquals("多选题", String.valueOf(answerDetails.get(0).get("type")));
    }

}
