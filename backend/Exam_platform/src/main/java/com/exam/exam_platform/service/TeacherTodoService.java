package com.exam.exam_platform.service;

import com.exam.exam_platform.mapper.TeacherTodoMapper;
import jakarta.annotation.PostConstruct;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Map;

@Service
public class TeacherTodoService {
    private final TeacherTodoMapper teacherTodoMapper;
    private final OperationLogService operationLogService;

    public TeacherTodoService(TeacherTodoMapper teacherTodoMapper,
                              OperationLogService operationLogService) {
        this.teacherTodoMapper = teacherTodoMapper;
        this.operationLogService = operationLogService;
    }

    @PostConstruct
    public void initializeSchema() {
        teacherTodoMapper.initSchema();
    }

    public List<Map<String, Object>> list(Long teacherId) {
        if (teacherId == null || teacherId <= 0) {
            throw new IllegalArgumentException("教师ID不能为空");
        }
        return teacherTodoMapper.listByTeacher(teacherId);
    }

    public Long create(Map<String, Object> payload) {
        Long teacherId = longValue(payload, "teacherId", payload == null ? null : payload.get("teacher_id"));
        if (teacherId == null || teacherId <= 0) {
            throw new IllegalArgumentException("教师ID不能为空");
        }
        String title = requireText(stringValue(payload, "title", null), "待办内容不能为空");
        String type = requireText(stringValue(payload, "type", "待办提醒"), "待办类型不能为空");
        LocalDateTime remindTime = parseDateTime(requireText(stringValue(payload, "remindTime",
                payload == null ? null : payload.get("remind_time")), "提醒时间不能为空"));

        Long id = teacherTodoMapper.insert(teacherId, title, type, remindTime);
        operationLogService.record(teacherId, "TEACHER_TODO_CREATE", "新增待办：" + title);
        return id;
    }

    public void updateStatus(Long id, Map<String, Object> payload) {
        if (id == null || id <= 0) {
            throw new IllegalArgumentException("待办ID不能为空");
        }
        Long teacherId = longValue(payload, "teacherId", payload == null ? null : payload.get("teacher_id"));
        if (teacherId == null || teacherId <= 0) {
            throw new IllegalArgumentException("教师ID不能为空");
        }
        String status = requireText(stringValue(payload, "status", null), "状态不能为空");
        if (!teacherTodoMapper.updateStatus(id, teacherId, status)) {
            throw new IllegalArgumentException("待办不存在或无权修改");
        }
        operationLogService.record(teacherId, "TEACHER_TODO_STATUS", "更新待办状态：" + id + " -> " + status);
    }

    private LocalDateTime parseDateTime(String value) {
        String text = value.trim();
        try {
            return LocalDateTime.parse(text);
        } catch (Exception ignored) {
            return LocalDateTime.parse(text, DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm"));
        }
    }

    private Long longValue(Map<String, Object> payload, String key, Object fallback) {
        Object value = payload != null && payload.containsKey(key) ? payload.get(key) : fallback;
        if (value == null) {
            return null;
        }
        if (value instanceof Number number) {
            return number.longValue();
        }
        String text = String.valueOf(value).trim();
        return text.isEmpty() ? null : Long.parseLong(text);
    }

    private String stringValue(Map<String, Object> payload, String key, Object fallback) {
        Object value = payload != null && payload.containsKey(key) ? payload.get(key) : fallback;
        return value == null ? "" : String.valueOf(value).trim();
    }

    private String requireText(String value, String message) {
        if (value == null || value.trim().isEmpty()) {
            throw new IllegalArgumentException(message);
        }
        return value.trim();
    }
}
