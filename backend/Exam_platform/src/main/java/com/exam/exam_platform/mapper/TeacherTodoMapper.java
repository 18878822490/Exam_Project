package com.exam.exam_platform.mapper;

import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Map;

@Repository
public class TeacherTodoMapper {
    private final JdbcTemplate jdbcTemplate;

    public TeacherTodoMapper(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public void initSchema() {
        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS teacher_todos (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    teacher_id BIGINT NOT NULL,
                    title VARCHAR(255) NOT NULL,
                    type VARCHAR(64) NOT NULL,
                    remind_time DATETIME NOT NULL,
                    status VARCHAR(32) NOT NULL DEFAULT 'PENDING',
                    created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
                    updated_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
                    INDEX idx_teacher_todos_teacher (teacher_id),
                    INDEX idx_teacher_todos_remind_time (remind_time),
                    INDEX idx_teacher_todos_status (status)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);
    }

    public List<Map<String, Object>> listByTeacher(Long teacherId) {
        return jdbcTemplate.queryForList("""
                SELECT id, teacher_id, title, type, remind_time,
                       CASE status
                           WHEN 'PENDING' THEN '待处理'
                           WHEN 'IN_PROGRESS' THEN '批改中'
                           ELSE status
                       END AS status,
                       created_time, updated_time
                FROM teacher_todos
                WHERE teacher_id = ? AND status IN ('PENDING', 'IN_PROGRESS', '待处理', '批改中')
                ORDER BY
                    CASE WHEN remind_time >= NOW() THEN 0 ELSE 1 END,
                    CASE WHEN remind_time >= NOW() THEN remind_time END ASC,
                    remind_time DESC,
                    id DESC
                """, teacherId);
    }

    public Long insert(Long teacherId, String title, String type, LocalDateTime remindTime) {
        org.springframework.jdbc.support.GeneratedKeyHolder keyHolder = new org.springframework.jdbc.support.GeneratedKeyHolder();
        jdbcTemplate.update(connection -> {
            java.sql.PreparedStatement statement = connection.prepareStatement("""
                    INSERT INTO teacher_todos (teacher_id, title, type, remind_time, status, created_time, updated_time)
                    VALUES (?, ?, ?, ?, 'PENDING', NOW(), NOW())
                    """, java.sql.Statement.RETURN_GENERATED_KEYS);
            statement.setObject(1, teacherId);
            statement.setString(2, title);
            statement.setString(3, type);
            statement.setObject(4, remindTime);
            return statement;
        }, keyHolder);
        return java.util.Objects.requireNonNull(keyHolder.getKey()).longValue();
    }

    public boolean updateStatus(Long id, Long teacherId, String status) {
        return jdbcTemplate.update("""
                UPDATE teacher_todos
                SET status = ?, updated_time = NOW()
                WHERE id = ? AND teacher_id = ?
                """, status, id, teacherId) > 0;
    }
}
