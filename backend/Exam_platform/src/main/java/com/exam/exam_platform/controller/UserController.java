package com.exam.exam_platform.controller;

import com.exam.exam_platform.common.ApiResponse;
import com.exam.exam_platform.dto.RegisterRequest;
import com.exam.exam_platform.service.UserService;
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
@RequestMapping("/api/users")
@CrossOrigin
public class UserController {
    private final UserService userService;

    public UserController(UserService userService) {
        this.userService = userService;
    }

    @GetMapping("/classes")
    public ApiResponse<List<String>> classes() {
        return ApiResponse.success("班级列表", userService.listClasses());
    }

    @GetMapping("/teacher-classes")
    public ApiResponse<List<Map<String, Object>>> teacherClasses(@RequestParam(required = false) Long teacherId) {
        return ApiResponse.success("教师班级列表", userService.listTeacherClasses(teacherId));
    }

    @GetMapping("/teachers/{id}")
    public ApiResponse<Map<String, Object>> teacher(@PathVariable Long id) {
        try {
            return ApiResponse.success("教师信息", userService.findTeacherById(id));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/teachers")
    public ApiResponse<List<Map<String, Object>>> teachers(@RequestParam(required = false) String keyword,
                                                           @RequestParam(required = false) Integer limit) {
        return ApiResponse.success("教师列表", userService.listTeachersForAdmin(keyword, limit));
    }

    @GetMapping("/teachers/admin-stats")
    public ApiResponse<Map<String, Object>> teacherAdminStats() {
        return ApiResponse.success("教师管理统计", userService.teacherAdminStats());
    }

    @GetMapping("/students/{id}")
    public ApiResponse<Map<String, Object>> student(@PathVariable Long id) {
        try {
            return ApiResponse.success("学生信息", userService.findStudentById(id));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/students")
    public ApiResponse<List<Map<String, Object>>> students(@RequestParam(required = false) String keyword,
                                                           @RequestParam(required = false) String className,
                                                           @RequestParam(required = false) Integer limit) {
        return ApiResponse.success("学生列表", userService.listStudentsForAdmin(keyword, className, limit));
    }

    @GetMapping("/students/admin-stats")
    public ApiResponse<Map<String, Object>> studentAdminStats() {
        return ApiResponse.success("学生管理统计", userService.studentAdminStats());
    }

    @PostMapping("/students")
    public ApiResponse<Map<String, Object>> createStudent(@RequestBody RegisterRequest request) {
        try {
            return ApiResponse.success("学生已新增", userService.createStudentForAdmin(request));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @PutMapping("/students/{id}")
    public ApiResponse<Map<String, Object>> updateStudent(@PathVariable Long id,
                                                          @RequestBody Map<String, Object> payload) {
        try {
            return ApiResponse.success("学生信息已更新", userService.updateStudentProfile(id, payload));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @PutMapping("/teachers/{id}")
    public ApiResponse<Map<String, Object>> updateTeacher(@PathVariable Long id,
                                                          @RequestBody Map<String, Object> payload) {
        try {
            return ApiResponse.success("教师信息已更新", userService.updateTeacherProfile(id, payload));
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @PostMapping("/{role}/{id}/password")
    public ApiResponse<Void> changePassword(@PathVariable String role,
                                            @PathVariable Long id,
                                            @RequestBody Map<String, Object> payload) {
        try {
            userService.changePassword(role, id, payload);
            return ApiResponse.success("密码已修改", null);
        } catch (IllegalArgumentException exception) {
            return ApiResponse.fail(exception.getMessage());
        }
    }

    @GetMapping("/classes/{className}/students")
    public ApiResponse<List<Map<String, Object>>> classStudents(@PathVariable String className) {
        return ApiResponse.success("班级学生列表", userService.listStudentsByClassName(className));
    }
}
