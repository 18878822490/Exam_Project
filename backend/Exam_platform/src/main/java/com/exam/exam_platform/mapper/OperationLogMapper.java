package com.exam.exam_platform.mapper;

import com.exam.exam_platform.entity.OperationLog;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.support.GeneratedKeyHolder;
import org.springframework.jdbc.support.KeyHolder;
import org.springframework.stereotype.Repository;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Objects;

@Repository
public class OperationLogMapper {
    private final JdbcTemplate jdbcTemplate;

    public OperationLogMapper(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public void initSchema() {
        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS operation_logs (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    user_id BIGINT,
                    action VARCHAR(64) NOT NULL,
                    detail TEXT,
                    created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
                    INDEX idx_operation_logs_user (user_id),
                    INDEX idx_operation_logs_action (action)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);
    }

    public Long insert(OperationLog log) {
        KeyHolder keyHolder = new GeneratedKeyHolder();
        jdbcTemplate.update(connection -> {
            PreparedStatement statement = connection.prepareStatement("""
                    INSERT INTO operation_logs (user_id, action, detail, created_time)
                    VALUES (?, ?, ?, NOW())
                    """, Statement.RETURN_GENERATED_KEYS);
            statement.setObject(1, log.getUserId());
            statement.setString(2, log.getAction());
            statement.setString(3, log.getDetail());
            return statement;
        }, keyHolder);
        Long id = Objects.requireNonNull(keyHolder.getKey()).longValue();
        log.setId(id);
        return id;
    }

    public List<OperationLog> list(Long userId, String action, int limit) {
        StringBuilder sql = new StringBuilder("SELECT * FROM operation_logs WHERE 1=1");
        List<Object> args = new ArrayList<>();
        if (userId != null) {
            sql.append(" AND user_id = ?");
            args.add(userId);
        }
        if (action != null && !action.isBlank()) {
            sql.append(" AND action = ?");
            args.add(action.trim());
        }
        sql.append(" ORDER BY id DESC LIMIT ?");
        args.add(Math.max(1, Math.min(limit, 200)));
        return jdbcTemplate.query(sql.toString(), this::mapLog, args.toArray());
    }

    public List<Map<String, Object>> listRows(Long userId, String action, int limit) {
        StringBuilder sql = new StringBuilder("""
                SELECT id, user_id, action, detail,
                       DATE_FORMAT(created_time, '%Y-%m-%d %H:%i:%s') AS created_time
                FROM operation_logs
                WHERE 1=1
                """);
        List<Object> args = new ArrayList<>();
        if (userId != null) {
            sql.append(" AND user_id = ?");
            args.add(userId);
        }
        if (action != null && !action.isBlank()) {
            sql.append(" AND action = ?");
            args.add(action.trim());
        }
        sql.append(" ORDER BY id DESC LIMIT ?");
        args.add(Math.max(1, Math.min(limit, 500)));
        return jdbcTemplate.queryForList(sql.toString(), args.toArray());
    }

    public Map<String, Object> stats() {
        return jdbcTemplate.queryForMap("""
                SELECT COUNT(*) AS total_count,
                       COALESCE(SUM(CASE WHEN DATE(created_time) = CURDATE() THEN 1 ELSE 0 END), 0) AS today_count,
                       COALESCE(SUM(CASE WHEN action LIKE 'USER_REGISTER_%' THEN 1 ELSE 0 END), 0) AS register_count,
                       COALESCE(SUM(CASE WHEN action LIKE 'EXAM_%' THEN 1 ELSE 0 END), 0) AS exam_count,
                       COALESCE(SUM(CASE WHEN action LIKE '%REVIEW%' THEN 1 ELSE 0 END), 0) AS review_count,
                       COALESCE(SUM(CASE WHEN action LIKE 'QUESTION_IMPORT%' THEN 1 ELSE 0 END), 0) AS import_count
                FROM operation_logs
                """);
    }

    private OperationLog mapLog(ResultSet rs, int rowNum) throws SQLException {
        OperationLog log = new OperationLog();
        log.setId(rs.getLong("id"));
        log.setUserId(readNullableLong(rs, "user_id"));
        log.setAction(rs.getString("action"));
        log.setDetail(rs.getString("detail"));
        Timestamp createdTime = rs.getTimestamp("created_time");
        if (createdTime != null) {
            log.setCreatedTime(createdTime.toLocalDateTime());
        }
        return log;
    }

    private Long readNullableLong(ResultSet rs, String column) throws SQLException {
        long value = rs.getLong(column);
        return rs.wasNull() ? null : value;
    }
}
