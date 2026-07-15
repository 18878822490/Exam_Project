package com.exam.exam_platform.controller;

import com.exam.exam_platform.common.ApiResponse;
import com.exam.exam_platform.dto.ReviewScoreRequest;
import com.exam.exam_platform.dto.SubmitExamRequest;
import com.exam.exam_platform.dto.WrongQuestionCorrectionRequest;
import com.exam.exam_platform.service.ScoreService;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/api/scores")
@CrossOrigin
public class ScoreController {
    private final ScoreService scoreService;

    public ScoreController(ScoreService scoreService) {
        this.scoreService = scoreService;
    }

    @PostMapping("/submit")
    public ApiResponse<Void> submit(@RequestBody SubmitExamRequest request) {
        try {
            scoreService.submitExam(request);
            return ApiResponse.success("提交成功", null);
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/answers")
    public ApiResponse<List<Map<String, Object>>> answers(@RequestParam Long examId,
                                                          @RequestParam(required = false) String status) {
        try {
            return ApiResponse.success("查询成功", scoreService.listAnswers(examId, status));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/answer-students")
    public ApiResponse<List<Map<String, Object>>> answerStudents(@RequestParam(required = false) Long examId,
                                                                 @RequestParam(required = false) String status) {
        return ApiResponse.success("查询成功", scoreService.listAnswerStudents(examId, status));
    }

    @GetMapping("/student-answers")
    public ApiResponse<List<Map<String, Object>>> studentAnswers(@RequestParam Long examId,
                                                                 @RequestParam String studentNo,
                                                                 @RequestParam(required = false) String status) {
        try {
            return ApiResponse.success("查询成功", scoreService.listStudentAnswers(examId, studentNo, status));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/review/exams")
    public ApiResponse<List<Map<String, Object>>> reviewExams(@RequestParam(required = false) Long teacherId) {
        return ApiResponse.success("查询成功", scoreService.listReviewExams(teacherId));
    }

    @GetMapping("/review/workbench")
    public ApiResponse<Map<String, Object>> reviewWorkbench(@RequestParam(required = false) Long teacherId,
                                                            @RequestParam(required = false) Long examId,
                                                            @RequestParam(required = false) String studentNo,
                                                            @RequestParam(required = false) String status) {
        return ApiResponse.success("查询成功", scoreService.reviewWorkbench(teacherId, examId, studentNo, status));
    }

    @GetMapping("/review/exams/{examId}/students")
    public ApiResponse<List<Map<String, Object>>> reviewStudents(@PathVariable Long examId,
                                                                 @RequestParam(required = false) String status) {
        try {
            return ApiResponse.success("查询成功", scoreService.listReviewStudents(examId, status));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/review/exams/{examId}/students/{studentNo}/answers")
    public ApiResponse<List<Map<String, Object>>> reviewStudentAnswers(@PathVariable Long examId,
                                                                       @PathVariable String studentNo,
                                                                       @RequestParam(required = false) String status) {
        try {
            return ApiResponse.success("查询成功", scoreService.listReviewStudentAnswers(examId, studentNo, status));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/student-history")
    public ApiResponse<List<Map<String, Object>>> studentHistory(@RequestParam String studentNo,
                                                                 @RequestParam(required = false) String subject) {
        try {
            return ApiResponse.success("查询成功", scoreService.studentHistory(studentNo, subject));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/class-trend")
    public ApiResponse<List<Map<String, Object>>> classTrend(@RequestParam(required = false) String className,
                                                             @RequestParam(required = false) String subject,
                                                             @RequestParam(required = false) Integer limit) {
        return ApiResponse.success("查询成功", scoreService.classAverageTrend(className, subject, limit));
    }

    @GetMapping("/class-analysis")
    public ApiResponse<Map<String, Object>> classAnalysis(@RequestParam(required = false) Long teacherId,
                                                          @RequestParam(required = false) Long examId,
                                                          @RequestParam(required = false) String className,
                                                          @RequestParam(required = false) String subject,
                                                          @RequestParam(required = false) Integer limit) {
        return ApiResponse.success("查询成功", scoreService.classAnalysis(teacherId, examId, className, subject, limit));
    }

    @PostMapping("/review")
    public ApiResponse<Void> review(@RequestBody ReviewScoreRequest request) {
        try {
            scoreService.review(request);
            return ApiResponse.success("评分已保存", null);
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/analysis")
    public ApiResponse<Map<String, Object>> analysis(@RequestParam Long examId,
                                                     @RequestParam(required = false) String className) {
        try {
            return ApiResponse.success("查询成功", scoreService.analysis(examId, className));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/report")
    public ApiResponse<Map<String, Object>> report(@RequestParam Long examId,
                                                   @RequestParam(required = false) String className,
                                                   @RequestParam(required = false) String studentNo) {
        try {
            return ApiResponse.success("查询成功", scoreService.report(examId, className, studentNo));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/print-report")
    public ApiResponse<Map<String, Object>> printReport(@RequestParam Long examId,
                                                        @RequestParam(required = false) String className,
                                                        @RequestParam(required = false) String reportType,
                                                        @RequestParam(required = false) List<String> studentNos) {
        try {
            return ApiResponse.success("查询成功", scoreService.printReport(examId, className, reportType, studentNos));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/wrong-questions")
    public ApiResponse<List<Map<String, Object>>> wrongQuestions(@RequestParam String studentNo) {
        try {
            return ApiResponse.success("查询成功", scoreService.wrongQuestions(studentNo));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @PostMapping("/wrong-questions/correction")
    public ApiResponse<Void> saveWrongQuestionCorrection(@RequestBody WrongQuestionCorrectionRequest request) {
        try {
            scoreService.saveWrongQuestionCorrection(request);
            return ApiResponse.success("订正记录已保存", null);
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }
}
