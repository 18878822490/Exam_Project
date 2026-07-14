package com.exam.exam_platform.controller;

import com.exam.exam_platform.common.ApiResponse;
import com.exam.exam_platform.dto.BatchQuestionImportRequest;
import com.exam.exam_platform.dto.PracticeAnswerRequest;
import com.exam.exam_platform.dto.QuestionImportLogRequest;
import com.exam.exam_platform.dto.QuestionImportResult;
import com.exam.exam_platform.entity.Question;
import com.exam.exam_platform.service.QuestionService;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/api/questions")
@CrossOrigin
public class QuestionController {
    private final QuestionService questionService;

    public QuestionController(QuestionService questionService) {
        this.questionService = questionService;
    }

    @GetMapping
    public ApiResponse<List<Question>> list(@RequestParam(required = false) String subject,
                                            @RequestParam(required = false) String type,
                                            @RequestParam(required = false) String difficulty,
                                            @RequestParam(required = false) String knowledgePoint,
                                            @RequestParam(required = false) String keyword,
                                            @RequestParam(required = false) Long createdBy) {
        return ApiResponse.success("查询成功", questionService.list(subject, type, difficulty, knowledgePoint, keyword, createdBy));
    }

    @GetMapping("/subject-stats")
    public ApiResponse<List<Map<String, Object>>> subjectStats(@RequestParam(required = false) String studentNo) {
        return ApiResponse.success("查询成功", questionService.subjectPracticeStats(studentNo));
    }

    @PostMapping("/practice-record")
    public ApiResponse<Void> recordPracticeAnswer(@RequestBody PracticeAnswerRequest request) {
        try {
            questionService.recordPracticeAnswer(request);
            return ApiResponse.success("练习记录已保存", null);
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/{id}")
    public ApiResponse<Question> detail(@PathVariable Long id) {
        try {
            return ApiResponse.success("查询成功", questionService.findById(id));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @PostMapping
    public ApiResponse<Question> create(@RequestBody Question question) {
        try {
            return ApiResponse.success("新增成功", questionService.create(question));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @PutMapping("/{id}")
    public ApiResponse<Question> update(@PathVariable Long id, @RequestBody Question question) {
        try {
            return ApiResponse.success("修改成功", questionService.update(id, question));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @DeleteMapping("/{id}")
    public ApiResponse<Void> delete(@PathVariable Long id, @RequestParam(required = false) Long userId) {
        try {
            questionService.delete(id, userId);
            return ApiResponse.success("删除成功", null);
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @PostMapping("/import/csv")
    public ApiResponse<QuestionImportResult> importCsv(@RequestParam MultipartFile file,
                                                       @RequestParam(required = false) Long userId) {
        return ApiResponse.success("导入完成", questionService.importCsv(file, userId));
    }

    @PostMapping("/import/excel")
    public ApiResponse<QuestionImportResult> importExcel(@RequestParam MultipartFile file,
                                                         @RequestParam(required = false) Long userId) {
        return ApiResponse.success("已记录Excel导入任务", questionService.reserveExcelImport(file, userId));
    }

    @PostMapping("/import/excel/parsed")
    public ApiResponse<QuestionImportResult> importParsedExcel(@RequestBody BatchQuestionImportRequest request) {
        return ApiResponse.success("Excel题库导入完成", questionService.importParsedQuestions(request));
    }

    @PostMapping("/import/batch")
    public ApiResponse<QuestionImportResult> importBatch(@RequestBody BatchQuestionImportRequest request) {
        return ApiResponse.success("题库批量导入完成", questionService.importParsedQuestions(request));
    }

    @PostMapping("/import/ocr")
    public ApiResponse<QuestionImportResult> importOcr(@RequestParam(required = false) MultipartFile file,
                                                       @RequestParam(required = false) String imageName,
                                                       @RequestParam(required = false) Long userId) {
        QuestionImportResult result = questionService.importOcr(file, imageName, userId);
        boolean success = !"失败".equals(result.getStatus());
        return new ApiResponse<>(success,
                success ? "OCR识别导入完成" : result.getMessage(),
                result);
    }

    @GetMapping("/import/logs")
    public ApiResponse<List<Map<String, Object>>> importLogs(@RequestParam(required = false) Long userId,
                                                             @RequestParam(required = false) Integer limit) {
        return ApiResponse.success("查询成功", questionService.listImportLogs(userId, limit));
    }

    @PostMapping("/import/logs")
    public ApiResponse<QuestionImportResult> recordImportLog(@RequestBody QuestionImportLogRequest request) {
        return ApiResponse.success("导入日志已记录", questionService.recordImportLog(request));
    }

    @GetMapping("/import/logs/{id}/rollback-preview")
    public ApiResponse<Map<String, Object>> rollbackPreview(@PathVariable Long id) {
        try {
            return ApiResponse.success("查询成功", questionService.previewImportRollback(id));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @DeleteMapping("/import/logs/{id}/questions")
    public ApiResponse<Map<String, Object>> rollbackImport(@PathVariable Long id) {
        try {
            return ApiResponse.success("撤回成功", questionService.rollbackImport(id));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }
}
