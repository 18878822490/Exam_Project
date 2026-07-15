package com.exam.exam_platform.service;

import com.exam.exam_platform.mapper.TeacherSettingsMapper;
import jakarta.annotation.PostConstruct;
import org.springframework.stereotype.Service;

import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

@Service
public class TeacherSettingsService {
    private final TeacherSettingsMapper teacherSettingsMapper;
    private final OperationLogService operationLogService;

    public TeacherSettingsService(TeacherSettingsMapper teacherSettingsMapper,
                                  OperationLogService operationLogService) {
        this.teacherSettingsMapper = teacherSettingsMapper;
        this.operationLogService = operationLogService;
    }

    @PostConstruct
    public void initializeSchema() {
        teacherSettingsMapper.initSchema();
    }

    public Map<String, Object> getSettings(Long teacherId) {
        validateTeacherId(teacherId);
        Map<String, Object> settings = defaults();
        List<Map<String, Object>> rows = teacherSettingsMapper.listByTeacher(teacherId);
        for (Map<String, Object> row : rows) {
            String key = String.valueOf(row.getOrDefault("setting_key", "")).trim();
            if (!settings.containsKey(key)) {
                continue;
            }
            settings.put(key, parseValue(row.get("setting_value"), booleanDefault(settings.get(key))));
        }
        return settings;
    }

    public Map<String, Object> saveSettings(Long teacherId, Map<String, Object> payload) {
        validateTeacherId(teacherId);
        if (payload == null || payload.isEmpty()) {
            throw new IllegalArgumentException("设置内容不能为空");
        }

        Map<String, Object> current = getSettings(teacherId);
        Map<String, Object> defaults = defaults();
        for (Map.Entry<String, Object> entry : payload.entrySet()) {
            String key = entry.getKey();
            if (!defaults.containsKey(key)) {
                continue;
            }
            boolean value = parseValue(entry.getValue(), booleanDefault(defaults.get(key)));
            teacherSettingsMapper.upsert(teacherId, key, String.valueOf(value));
            current.put(key, value);
        }
        operationLogService.record(teacherId, "TEACHER_SETTINGS_UPDATE", "更新教师端系统设置");
        return current;
    }

    private void validateTeacherId(Long teacherId) {
        if (teacherId == null || teacherId <= 0) {
            throw new IllegalArgumentException("教师ID不能为空");
        }
    }

    private Map<String, Object> defaults() {
        Map<String, Object> defaults = new LinkedHashMap<>();
        defaults.put("todoReminders", true);
        defaults.put("autoSaveDraft", true);
        defaults.put("compactTopBar", false);
        defaults.put("publishNoDuplicate", true);
        defaults.put("publishSortByChapter", false);
        defaults.put("publishShuffleOptions", true);
        defaults.put("publishShowAnswers", false);
        return defaults;
    }

    private boolean booleanDefault(Object value) {
        return value instanceof Boolean booleanValue && booleanValue;
    }

    private boolean parseValue(Object value, boolean fallback) {
        if (value == null) {
            return fallback;
        }
        if (value instanceof Boolean booleanValue) {
            return booleanValue;
        }
        if (value instanceof Number number) {
            return number.intValue() != 0;
        }
        String text = String.valueOf(value).trim().toLowerCase(Locale.ROOT);
        if (text.isEmpty()) {
            return fallback;
        }
        if ("true".equals(text) || "1".equals(text) || "on".equals(text)
                || "yes".equals(text) || "开启".equals(text) || "是".equals(text)) {
            return true;
        }
        if ("false".equals(text) || "0".equals(text) || "off".equals(text)
                || "no".equals(text) || "关闭".equals(text) || "否".equals(text)) {
            return false;
        }
        return fallback;
    }
}
