package com.exam.exam_platform.controller;

import com.exam.exam_platform.common.ApiResponse;
import com.exam.exam_platform.dto.CreateExamPaperRequest;
import com.exam.exam_platform.dto.PublishExamRequest;
import com.exam.exam_platform.entity.Exam;
import com.exam.exam_platform.entity.GenerateExamRequest;
import com.exam.exam_platform.service.ExamService;
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
@RequestMapping("/api/exams")
@CrossOrigin
public class ExamController {
    private final ExamService examService;

    public ExamController(ExamService examService) {
        this.examService = examService;
    }

    @GetMapping
    public ApiResponse<List<Exam>> list(@RequestParam(required = false) Long createdBy,
                                        @RequestParam(required = false) String status) {
        return ApiResponse.success("查询成功", examService.list(createdBy, status));
    }

    @GetMapping("/{id}")
    public ApiResponse<Exam> detail(@PathVariable Long id) {
        try {
            return ApiResponse.success("查询成功", examService.findById(id));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/{id}/questions")
    public ApiResponse<List<Map<String, Object>>> preview(@PathVariable Long id) {
        try {
            return ApiResponse.success("查询成功", examService.preview(id));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @PostMapping("/papers")
    public ApiResponse<Exam> createPaper(@RequestBody CreateExamPaperRequest request) {
        try {
            return ApiResponse.success("试卷草稿已生成", examService.createPaper(request));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @PostMapping("/generate")
    public ApiResponse<Exam> generate(@RequestBody GenerateExamRequest request) {
        try {
            return ApiResponse.success("试卷草稿已生成", examService.generateByLegacyRequest(request));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @PostMapping("/{id}/copy")
    public ApiResponse<Exam> copy(@PathVariable Long id,
                                  @RequestParam(required = false) String title,
                                  @RequestParam(required = false) Long createdBy,
                                  @RequestParam(required = false) java.time.LocalDateTime startTime,
                                  @RequestParam(required = false) java.time.LocalDateTime endTime) {
        try {
            return ApiResponse.success("复制成功", examService.copyExam(id, title, createdBy, startTime, endTime));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @PostMapping("/publish")
    public ApiResponse<Void> publish(@RequestBody PublishExamRequest request) {
        try {
            examService.publish(request);
            return ApiResponse.success("发布成功", null);
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/published")
    public ApiResponse<List<Map<String, Object>>> published(@RequestParam(required = false) String className,
                                                            @RequestParam(required = false) String studentNo) {
        return ApiResponse.success("查询成功", examService.listPublished(className, studentNo));
    }

    @GetMapping("/dashboard")
    public ApiResponse<Map<String, Object>> dashboard(@RequestParam(required = false) Long teacherId) {
        return ApiResponse.success("查询成功", examService.dashboardStats(teacherId));
    }
}
