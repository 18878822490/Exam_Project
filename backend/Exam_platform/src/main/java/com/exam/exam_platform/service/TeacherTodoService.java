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
        String status = normalizeStatus(requireText(stringValue(payload, "status", null), "状态不能为空"));
        if (!teacherTodoMapper.updateStatus(id, teacherId, status)) {
            throw new IllegalArgumentException("待办不存在或无权修改");
        }
        operationLogService.record(teacherId, "TEACHER_TODO_STATUS", "更新待办状态：" + id + " -> " + displayStatus(status));
    }

    private String normalizeStatus(String status) {
        String text = status == null ? "" : status.trim();
        String lower = text.toLowerCase(java.util.Locale.ROOT);
        if ("done".equals(lower) || "completed".equals(lower) || "已完成".equals(text)) {
            return "DONE";
        }
        if ("deleted".equals(lower) || "delete".equals(lower) || "removed".equals(lower) || "已删除".equals(text)) {
            return "DELETED";
        }
        if ("in_progress".equals(lower) || "progress".equals(lower) || "批改中".equals(text)) {
            return "IN_PROGRESS";
        }
        if ("pending".equals(lower) || "todo".equals(lower) || "待处理".equals(text)) {
            return "PENDING";
        }
        throw new IllegalArgumentException("状态不支持");
    }

    private String displayStatus(String status) {
        return switch (status) {
            case "DONE" -> "已完成";
            case "DELETED" -> "已删除";
            case "IN_PROGRESS" -> "批改中";
            default -> "待处理";
        };
    }

    private LocalDateTime parseDateTime(String value) {
        String text = value.trim().replace('T', ' ');
        DateTimeFormatter[] formatters = {
                DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"),
                DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm")
        };
        for (DateTimeFormatter formatter : formatters) {
            try {
                return LocalDateTime.parse(text, formatter);
            } catch (Exception ignored) {
                // Try the next supported UI/API time format.
            }
        }
        try {
            return LocalDateTime.parse(value.trim());
        } catch (Exception exception) {
            throw new IllegalArgumentException("提醒时间格式不正确，请使用 yyyy-MM-dd HH:mm");
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
