package com.exam.exam_platform.controller;

import com.exam.exam_platform.common.ApiResponse;
import com.exam.exam_platform.service.TeacherTodoService;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/api/teacher-todos")
@CrossOrigin
public class TeacherTodoController {
    private final TeacherTodoService teacherTodoService;

    public TeacherTodoController(TeacherTodoService teacherTodoService) {
        this.teacherTodoService = teacherTodoService;
    }

    @GetMapping
    public ApiResponse<List<Map<String, Object>>> list(@RequestParam Long teacherId) {
        try {
            return ApiResponse.success("教师待办列表", teacherTodoService.list(teacherId));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @PostMapping
    public ApiResponse<Long> create(@RequestBody Map<String, Object> payload) {
        try {
            return ApiResponse.success("待办已新增", teacherTodoService.create(payload));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @PutMapping("/{id}/status")
    public ApiResponse<Void> updateStatus(@PathVariable Long id,
                                          @RequestBody Map<String, Object> payload) {
        try {
            teacherTodoService.updateStatus(id, payload);
            return ApiResponse.success("待办状态已更新", null);
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }
}
