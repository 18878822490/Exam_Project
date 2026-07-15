package com.exam.exam_platform.controller;

import com.exam.exam_platform.common.ApiResponse;
import com.exam.exam_platform.entity.OperationLog;
import com.exam.exam_platform.service.OperationLogService;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/api/logs")
@CrossOrigin
public class OperationLogController {
    private final OperationLogService operationLogService;

    public OperationLogController(OperationLogService operationLogService) {
        this.operationLogService = operationLogService;
    }

    @GetMapping
    public ApiResponse<List<OperationLog>> list(@RequestParam(required = false) Long userId,
                                                @RequestParam(required = false) String action,
                                                @RequestParam(required = false) Integer limit) {
        return ApiResponse.success("查询成功", operationLogService.list(userId, action, limit));
    }

    @GetMapping("/dashboard")
    public ApiResponse<Map<String, Object>> dashboard(@RequestParam(required = false) Long userId,
                                                      @RequestParam(required = false) String action,
                                                      @RequestParam(required = false) Integer limit) {
        return ApiResponse.success("查询成功", operationLogService.dashboard(userId, action, limit));
    }
}
