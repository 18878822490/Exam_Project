package com.exam.exam_platform;

import com.exam.exam_platform.dto.SubmitExamRequest;
import com.exam.exam_platform.dto.ReviewScoreRequest;
import com.exam.exam_platform.entity.Exam;
import com.exam.exam_platform.entity.Question;
import com.exam.exam_platform.mapper.ExamMapper;
import com.exam.exam_platform.mapper.QuestionMapper;
import com.exam.exam_platform.dto.QuestionImportResult;
import com.exam.exam_platform.service.QuestionService;
import com.exam.exam_platform.service.ScoreService;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.mock.web.MockMultipartFile;
import org.springframework.transaction.annotation.Transactional;

import java.io.ByteArrayOutputStream;
import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.Map;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

@SpringBootTest
class ExamPlatformApplicationTests {

    @Autowired
    private QuestionMapper questionMapper;

    @Autowired
    private ExamMapper examMapper;

    @Autowired
    private ScoreService scoreService;

    @Autowired
    private QuestionService questionService;

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

    @Test
    @Transactional
    void backendXlsxImportStoresChoiceOptionsAndSkipsDuplicates() throws Exception {
        String subject = "CodexExcelImportTest";
        String content = "Java入口方法是？" + System.nanoTime();
        MockMultipartFile file = new MockMultipartFile(
                "file",
                "codex-question-import.xlsx",
                "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet",
                xlsxBytes(List.of(
                        List.of("科目", "题型", "题目内容", "选项A", "选项B", "选项C", "选项D", "标准答案", "解析", "难度", "知识点", "分值"),
                        List.of(subject, "单选题", content, "main", "run", "start", "init", "A", "main 方法是 Java 入口。", "基础", "Java基础", "2.0")
                ))
        );

        QuestionImportResult first = questionService.reserveExcelImport(file, 1L);
        Assertions.assertEquals("成功", first.getStatus());
        Assertions.assertEquals(1, first.getSuccessCount());
        Assertions.assertEquals(0, first.getFailedCount());

        List<Question> imported = questionService.list(subject, "单选题", null, null, content, null);
        Assertions.assertEquals(1, imported.size());
        Assertions.assertEquals("main", imported.get(0).getOptionA());
        Assertions.assertEquals("run", imported.get(0).getOptionB());
        Assertions.assertEquals(2, imported.get(0).getScore());

        QuestionImportResult second = questionService.reserveExcelImport(file, 1L);
        Assertions.assertEquals(0, second.getSuccessCount());
        Assertions.assertTrue(second.getMessage().contains("跳过重复题目 1 题"));
    }

    @Test
    @Transactional
    void publishedProgrammingExamFlowsFromStudentSubmissionToTeacherReview() {
        String className = "CodexReviewClass";
        String studentNo = "CodexReviewStudent";

        Question question = new Question();
        question.setSubject("CodexReviewSubject");
        question.setType("编程题");
        question.setContent("编写一个 main 方法输出 Hello。");
        question.setAnswer("public static void main(String[] args) { System.out.println(\"Hello\"); }");
        question.setAnalysis("主观编程题由教师评分。");
        question.setDifficulty("中等");
        question.setKnowledgePoint("Java基础");
        question.setScore(20);
        questionMapper.insert(question);

        Exam exam = new Exam();
        exam.setTitle("Codex Programming Review Flow");
        exam.setSubject("CodexReviewSubject");
        exam.setDuration(45);
        exam.setTotalScore(20);
        exam.setStatus("已发布");
        exam.setCreatedBy(1L);
        examMapper.insertExam(exam);
        examMapper.insertExamQuestion(exam.getId(), question, 1);
        examMapper.publish(exam.getId(), null, className, null, null, "已发布", 1L);

        List<Map<String, Object>> published = examMapper.listPublished(className, studentNo);
        Assertions.assertTrue(published.stream().anyMatch(row -> exam.getId().equals(((Number) row.get("exam_id")).longValue())));

        SubmitExamRequest submit = new SubmitExamRequest();
        submit.setExamId(exam.getId());
        submit.setStudentId(0L);
        submit.setStudentName("CodexReviewStudentName");
        submit.setStudentNo(studentNo);
        submit.setClassName(className);
        submit.setAnswers(Map.of(question.getId(), "public class Main { public static void main(String[] args){ System.out.println(\"Hello\"); }}"));
        scoreService.submitExam(submit);

        List<Map<String, Object>> pendingAnswers = scoreService.listStudentAnswers(exam.getId(), studentNo, "待批改");
        Assertions.assertEquals(1, pendingAnswers.size());
        Assertions.assertEquals("编程题", String.valueOf(pendingAnswers.get(0).get("type")));

        List<Map<String, Object>> reviewStudents = scoreService.listReviewStudents(exam.getId(), "待批改");
        Assertions.assertEquals(1, reviewStudents.size());
        Assertions.assertEquals(studentNo, String.valueOf(reviewStudents.get(0).get("student_no")));

        ReviewScoreRequest review = new ReviewScoreRequest();
        review.setAnswerId(((Number) pendingAnswers.get(0).get("id")).longValue());
        review.setTeacherId(1L);
        review.setScore(18.0);
        review.setComment("代码结构正确。");
        scoreService.review(review);

        Map<String, Object> report = scoreService.report(exam.getId(), className, studentNo);
        Assertions.assertEquals("已批改", String.valueOf(report.get("reviewStatus")));
        Assertions.assertEquals(18.0, ((Number) report.get("personalScore")).doubleValue(), 0.001);
        Assertions.assertEquals(0, ((Number) report.get("pendingCount")).intValue());
    }

    private byte[] xlsxBytes(List<List<String>> rows) throws Exception {
        StringBuilder sheet = new StringBuilder("""
                <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
                <worksheet xmlns="http://schemas.openxmlformats.org/spreadsheetml/2006/main"><sheetData>
                """);
        for (int row = 0; row < rows.size(); row++) {
            sheet.append("<row r=\"").append(row + 1).append("\">");
            for (int column = 0; column < rows.get(row).size(); column++) {
                String ref = columnName(column) + (row + 1);
                sheet.append("<c r=\"").append(ref).append("\" t=\"inlineStr\"><is><t>")
                        .append(xml(rows.get(row).get(column)))
                        .append("</t></is></c>");
            }
            sheet.append("</row>");
        }
        sheet.append("</sheetData></worksheet>");

        ByteArrayOutputStream bytes = new ByteArrayOutputStream();
        try (ZipOutputStream zip = new ZipOutputStream(bytes, StandardCharsets.UTF_8)) {
            zip.putNextEntry(new ZipEntry("xl/worksheets/sheet1.xml"));
            zip.write(sheet.toString().getBytes(StandardCharsets.UTF_8));
            zip.closeEntry();
        }
        return bytes.toByteArray();
    }

    private String columnName(int zeroBasedColumn) {
        StringBuilder name = new StringBuilder();
        int value = zeroBasedColumn + 1;
        while (value > 0) {
            int remainder = (value - 1) % 26;
            name.insert(0, (char) ('A' + remainder));
            value = (value - 1) / 26;
        }
        return name.toString();
    }

    private String xml(String value) {
        return value.replace("&", "&amp;")
                .replace("<", "&lt;")
                .replace(">", "&gt;")
                .replace("\"", "&quot;");
    }

}
