package com.exam.exam_platform.controller;

import com.exam.exam_platform.common.ApiResponse;
import com.exam.exam_platform.service.TeacherSettingsService;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

@RestController
@RequestMapping("/api/teacher-settings")
@CrossOrigin
public class TeacherSettingsController {
    private final TeacherSettingsService teacherSettingsService;

    public TeacherSettingsController(TeacherSettingsService teacherSettingsService) {
        this.teacherSettingsService = teacherSettingsService;
    }

    @GetMapping
    public ApiResponse<Map<String, Object>> detail(@RequestParam Long teacherId) {
        try {
            return ApiResponse.success("查询成功", teacherSettingsService.getSettings(teacherId));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @PutMapping
    public ApiResponse<Map<String, Object>> save(@RequestParam Long teacherId,
                                                 @RequestBody Map<String, Object> payload) {
        try {
            return ApiResponse.success("设置已保存", teacherSettingsService.saveSettings(teacherId, payload));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }
}
