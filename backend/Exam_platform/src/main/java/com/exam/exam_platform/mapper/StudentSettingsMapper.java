package com.exam.exam_platform.mapper;

import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Map;

@Repository
public class StudentSettingsMapper {
    private final JdbcTemplate jdbcTemplate;

    public StudentSettingsMapper(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public void initSchema() {
        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS student_settings (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    student_id BIGINT NOT NULL,
                    setting_key VARCHAR(80) NOT NULL,
                    setting_value VARCHAR(255) NOT NULL,
                    updated_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
                    UNIQUE KEY uk_student_settings_key (student_id, setting_key),
                    INDEX idx_student_settings_student (student_id)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);
    }

    public List<Map<String, Object>> listByStudent(Long studentId) {
        return jdbcTemplate.queryForList("""
                SELECT setting_key, setting_value, updated_time
                FROM student_settings
                WHERE student_id = ?
                """, studentId);
    }

    public void upsert(Long studentId, String key, String value) {
        jdbcTemplate.update("""
                INSERT INTO student_settings (student_id, setting_key, setting_value, updated_time)
                VALUES (?, ?, ?, NOW())
                ON DUPLICATE KEY UPDATE setting_value = VALUES(setting_value), updated_time = NOW()
                """, studentId, key, value);
    }
}
