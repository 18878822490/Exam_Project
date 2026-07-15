package com.exam.exam_platform.mapper;

import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Map;

@Repository
public class TeacherSettingsMapper {
    private final JdbcTemplate jdbcTemplate;

    public TeacherSettingsMapper(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public void initSchema() {
        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS teacher_settings (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    teacher_id BIGINT NOT NULL,
                    setting_key VARCHAR(80) NOT NULL,
                    setting_value VARCHAR(255) NOT NULL,
                    updated_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
                    UNIQUE KEY uk_teacher_settings_key (teacher_id, setting_key),
                    INDEX idx_teacher_settings_teacher (teacher_id)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);
    }

    public List<Map<String, Object>> listByTeacher(Long teacherId) {
        return jdbcTemplate.queryForList("""
                SELECT setting_key, setting_value, updated_time
                FROM teacher_settings
                WHERE teacher_id = ?
                """, teacherId);
    }

    public void upsert(Long teacherId, String key, String value) {
        jdbcTemplate.update("""
                INSERT INTO teacher_settings (teacher_id, setting_key, setting_value, updated_time)
                VALUES (?, ?, ?, NOW())
                ON DUPLICATE KEY UPDATE setting_value = VALUES(setting_value), updated_time = NOW()
                """, teacherId, key, value);
    }
}
