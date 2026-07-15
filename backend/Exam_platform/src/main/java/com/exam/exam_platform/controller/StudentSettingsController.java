package com.exam.exam_platform.controller;

import com.exam.exam_platform.common.ApiResponse;
import com.exam.exam_platform.service.StudentSettingsService;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

@RestController
@RequestMapping("/api/student-settings")
@CrossOrigin
public class StudentSettingsController {
    private final StudentSettingsService studentSettingsService;

    public StudentSettingsController(StudentSettingsService studentSettingsService) {
        this.studentSettingsService = studentSettingsService;
    }

    @GetMapping
    public ApiResponse<Map<String, Object>> detail(@RequestParam Long studentId) {
        try {
            return ApiResponse.success("查询成功", studentSettingsService.getSettings(studentId));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @PutMapping
    public ApiResponse<Map<String, Object>> save(@RequestParam Long studentId,
                                                 @RequestBody Map<String, Object> payload) {
        try {
            return ApiResponse.success("设置已保存", studentSettingsService.saveSettings(studentId, payload));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }
}
