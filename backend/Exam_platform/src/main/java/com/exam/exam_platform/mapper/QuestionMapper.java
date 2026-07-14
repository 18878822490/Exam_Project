package com.exam.exam_platform.mapper;

import com.exam.exam_platform.entity.Question;
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
public class QuestionMapper {
    private final JdbcTemplate jdbcTemplate;

    public QuestionMapper(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public void initSchema() {
        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS questions (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    subject VARCHAR(64) NOT NULL DEFAULT '综合',
                    type VARCHAR(32) NOT NULL,
                    content TEXT NOT NULL,
                    option_a TEXT,
                    option_b TEXT,
                    option_c TEXT,
                    option_d TEXT,
                    answer TEXT,
                    analysis TEXT,
                    difficulty VARCHAR(32),
                    knowledge_point VARCHAR(128),
                    score INT NOT NULL,
                    created_by BIGINT,
                    created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
                    INDEX idx_questions_subject (subject),
                    INDEX idx_questions_type (type),
                    INDEX idx_questions_difficulty (difficulty),
                    INDEX idx_questions_knowledge (knowledge_point),
                    INDEX idx_questions_created_by (created_by)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);
        ensureColumn("questions", "subject", "VARCHAR(64) NOT NULL DEFAULT '综合'");
        ensureColumn("questions", "option_a", "TEXT");
        ensureColumn("questions", "option_b", "TEXT");
        ensureColumn("questions", "option_c", "TEXT");
        ensureColumn("questions", "option_d", "TEXT");
        ensureColumn("questions", "analysis", "TEXT");
        ensureColumn("questions", "knowledge_point", "VARCHAR(128)");
        ensureColumn("questions", "created_by", "BIGINT");
        ensureColumn("questions", "created_time", "DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP");

        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS question_import_logs (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    user_id BIGINT,
                    import_type VARCHAR(32) NOT NULL,
                    file_name VARCHAR(255),
                    total_count INT NOT NULL DEFAULT 0,
                    success_count INT NOT NULL DEFAULT 0,
                    failed_count INT NOT NULL DEFAULT 0,
                    status VARCHAR(32) NOT NULL,
                    message TEXT,
                    created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
                    INDEX idx_question_import_logs_user (user_id),
                    INDEX idx_question_import_logs_type (import_type)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);

        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS practice_answers (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    student_id BIGINT,
                    student_name VARCHAR(64),
                    student_no VARCHAR(32) NOT NULL,
                    question_id BIGINT NOT NULL,
                    answer TEXT,
                    is_correct TINYINT(1) NOT NULL DEFAULT 0,
                    practice_mode VARCHAR(32) NOT NULL DEFAULT '题库练习',
                    correction_answer TEXT,
                    correction_reason TEXT,
                    correction_summary TEXT,
                    correction_status VARCHAR(32) NOT NULL DEFAULT '未订正',
                    corrected_time DATETIME,
                    created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
                    INDEX idx_practice_answers_student (student_no),
                    INDEX idx_practice_answers_question (question_id),
                    INDEX idx_practice_answers_mode (practice_mode)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);
        ensureColumn("practice_answers", "correction_answer", "TEXT");
        ensureColumn("practice_answers", "correction_reason", "TEXT");
        ensureColumn("practice_answers", "correction_summary", "TEXT");
        ensureColumn("practice_answers", "correction_status", "VARCHAR(32) NOT NULL DEFAULT '未订正'");
        ensureColumn("practice_answers", "corrected_time", "DATETIME");
    }

    public Long insert(Question question) {
        KeyHolder keyHolder = new GeneratedKeyHolder();
        jdbcTemplate.update(connection -> {
            PreparedStatement statement = connection.prepareStatement("""
                    INSERT INTO questions (
                        subject, type, content, option_a, option_b, option_c, option_d,
                        answer, analysis, difficulty, knowledge_point, score, created_by, created_time
                    ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NOW())
                    """, Statement.RETURN_GENERATED_KEYS);
            bindQuestion(statement, question, false);
            return statement;
        }, keyHolder);
        Long id = Objects.requireNonNull(keyHolder.getKey()).longValue();
        question.setId(id);
        return id;
    }

    public boolean update(Long id, Question question) {
        int rows = jdbcTemplate.update("""
                UPDATE questions
                SET subject = ?, type = ?, content = ?, option_a = ?, option_b = ?, option_c = ?, option_d = ?,
                    answer = ?, analysis = ?, difficulty = ?, knowledge_point = ?, score = ?, created_by = ?
                WHERE id = ?
                """, ps -> {
            bindQuestion(ps, question, true);
            ps.setLong(14, id);
        });
        return rows > 0;
    }

    public boolean delete(Long id) {
        return jdbcTemplate.update("DELETE FROM questions WHERE id = ?", id) > 0;
    }

    public Question findById(Long id) {
        List<Question> questions = jdbcTemplate.query(
                "SELECT * FROM questions WHERE id = ? LIMIT 1",
                this::mapQuestion,
                id
        );
        return questions.isEmpty() ? null : questions.get(0);
    }

    public List<Question> list(String subject,
                               String type,
                               String difficulty,
                               String knowledgePoint,
                               String keyword,
                               Long createdBy) {
        StringBuilder sql = new StringBuilder("SELECT * FROM questions WHERE 1=1");
        List<Object> args = new ArrayList<>();
        if (hasText(subject)) {
            sql.append(" AND subject = ?");
            args.add(subject.trim());
        }
        if (hasText(type)) {
            String trimmedType = type.trim();
            if ("编程题".equals(trimmedType) || "代码题".equals(trimmedType)) {
                sql.append(" AND (type = ? OR type = ?)");
                args.add("编程题");
                args.add("代码题");
            } else {
                sql.append(" AND type = ?");
                args.add(trimmedType);
            }
        }
        if (hasText(difficulty)) {
            sql.append(" AND difficulty = ?");
            args.add(difficulty.trim());
        }
        if (hasText(knowledgePoint)) {
            sql.append(" AND knowledge_point LIKE ?");
            args.add("%" + knowledgePoint.trim() + "%");
        }
        if (hasText(keyword)) {
            sql.append("""
                    AND (
                        content LIKE ?
                        OR answer LIKE ?
                        OR analysis LIKE ?
                        OR knowledge_point LIKE ?
                    )
                    """);
            String likeKeyword = "%" + keyword.trim() + "%";
            args.add(likeKeyword);
            args.add(likeKeyword);
            args.add(likeKeyword);
            args.add(likeKeyword);
        }
        if (createdBy != null) {
            sql.append(" AND created_by = ?");
            args.add(createdBy);
        }
        sql.append(" ORDER BY id DESC");
        return jdbcTemplate.query(sql.toString(), this::mapQuestion, args.toArray());
    }

    public List<Question> randomQuestions(String subject, String type, String difficulty, String knowledgePoint, int count) {
        StringBuilder sql = new StringBuilder("SELECT * FROM questions WHERE type = ?");
        List<Object> args = new ArrayList<>();
        args.add(type);
        if (hasText(subject)) {
            sql.append(" AND subject = ?");
            args.add(subject.trim());
        }
        if (hasText(difficulty)) {
            sql.append(" AND difficulty = ?");
            args.add(difficulty.trim());
        }
        if (hasText(knowledgePoint)) {
            sql.append(" AND knowledge_point LIKE ?");
            args.add("%" + knowledgePoint.trim() + "%");
        }
        sql.append(" ORDER BY RAND() LIMIT ?");
        args.add(Math.max(0, count));
        return jdbcTemplate.query(sql.toString(), this::mapQuestion, args.toArray());
    }

    public List<Map<String, Object>> subjectPracticeStats(String studentNo) {
        return jdbcTemplate.queryForList("""
                SELECT subject,
                       COUNT(*) AS total_count,
                       SUM(practiced) AS practiced_count,
                       ROUND(COALESCE(SUM(practiced) / NULLIF(COUNT(*), 0) * 100, 0), 0) AS progress,
                       ROUND(COALESCE(SUM(correct) / NULLIF(SUM(practiced), 0) * 100, 0), 0) AS accuracy,
                       ROUND(COALESCE(SUM(CASE WHEN difficulty = '基础' THEN 1 ELSE 0 END) / NULLIF(COUNT(*), 0) * 100, 0), 0) AS easy,
                       ROUND(COALESCE(SUM(CASE WHEN difficulty = '困难' THEN 1 ELSE 0 END) / NULLIF(COUNT(*), 0) * 100, 0), 0) AS hard,
                       ROUND(COALESCE(SUM(CASE WHEN difficulty IS NULL OR difficulty = '' OR difficulty NOT IN ('基础', '困难') THEN 1 ELSE 0 END) / NULLIF(COUNT(*), 0) * 100, 0), 0) AS middle
                FROM (
                    SELECT q.id,
                           q.subject,
                           q.difficulty,
                           MAX(CASE WHEN sa.id IS NULL AND pa.id IS NULL THEN 0 ELSE 1 END) AS practiced,
                           MAX(CASE WHEN (sa.score IS NOT NULL
                                      AND COALESCE(sa.score, 0) >= COALESCE(eq.score, q.score, 0))
                                     OR pa.is_correct = 1
                                    THEN 1 ELSE 0 END) AS correct
                    FROM questions q
                    LEFT JOIN student_answers sa
                           ON sa.question_id = q.id
                          AND sa.student_no = ?
                    LEFT JOIN exam_questions eq
                           ON eq.exam_id = sa.exam_id
                          AND eq.question_id = sa.question_id
                    LEFT JOIN practice_answers pa
                           ON pa.question_id = q.id
                          AND pa.student_no = ?
                    GROUP BY q.id, q.subject, q.difficulty
                ) question_stats
                GROUP BY subject
                ORDER BY subject
                """, studentNo == null ? "" : studentNo.trim(), studentNo == null ? "" : studentNo.trim());
    }

    public boolean recordPracticeAnswer(Long studentId,
                                        String studentName,
                                        String studentNo,
                                        Long questionId,
                                        String answer,
                                        boolean correct,
                                        String practiceMode) {
        return jdbcTemplate.update("""
                INSERT INTO practice_answers (
                    student_id, student_name, student_no, question_id,
                    answer, is_correct, practice_mode, created_time
                ) VALUES (?, ?, ?, ?, ?, ?, ?, NOW())
                """,
                studentId,
                studentName,
                studentNo,
                questionId,
                answer,
                correct ? 1 : 0,
                practiceMode == null || practiceMode.isBlank() ? "题库练习" : practiceMode.trim()) > 0;
    }

    public List<Map<String, Object>> wrongPracticeQuestions(String studentNo) {
        return jdbcTemplate.queryForList("""
                SELECT pa.id AS answer_id,
                       NULL AS exam_id,
                       pa.practice_mode AS exam_title,
                       'practice' AS source_type,
                       q.id AS question_id,
                       q.subject,
                       q.type,
                       q.content,
                       q.option_a,
                       q.option_b,
                       q.option_c,
                       q.option_d,
                       q.answer AS standard_answer,
                       q.analysis,
                       q.knowledge_point,
                       q.difficulty,
                       COALESCE(q.score, 0) AS full_score,
                       0 AS score,
                       COALESCE(q.score, 0) AS deduction,
                       pa.answer AS wrong_answer,
                       NULL AS comment,
                       '练习错题' AS review_status,
                       pa.correction_answer,
                       pa.correction_reason,
                       pa.correction_summary,
                       pa.correction_status,
                       pa.corrected_time,
                       pa.created_time
                FROM practice_answers pa
                INNER JOIN questions q ON q.id = pa.question_id
                WHERE pa.student_no = ?
                  AND pa.is_correct = 0
                ORDER BY pa.created_time DESC, pa.id DESC
                """, studentNo);
    }

    public boolean savePracticeCorrection(Long answerId,
                                          String studentNo,
                                          String correctionAnswer,
                                          String errorReason,
                                          String knowledgeSummary) {
        return jdbcTemplate.update("""
                UPDATE practice_answers
                SET correction_answer = ?,
                    correction_reason = ?,
                    correction_summary = ?,
                    correction_status = '已订正',
                    corrected_time = NOW()
                WHERE id = ? AND student_no = ?
                """, correctionAnswer, errorReason, knowledgeSummary, answerId, studentNo) > 0;
    }

    public Long insertImportLog(Long userId,
                                String importType,
                                String fileName,
                                int totalCount,
                                int successCount,
                                int failedCount,
                                String status,
                                String message) {
        KeyHolder keyHolder = new GeneratedKeyHolder();
        jdbcTemplate.update(connection -> {
            PreparedStatement statement = connection.prepareStatement("""
                    INSERT INTO question_import_logs (
                        user_id, import_type, file_name, total_count, success_count,
                        failed_count, status, message, created_time
                    ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, NOW())
                    """, Statement.RETURN_GENERATED_KEYS);
            statement.setObject(1, userId);
            statement.setString(2, importType);
            statement.setString(3, fileName);
            statement.setInt(4, totalCount);
            statement.setInt(5, successCount);
            statement.setInt(6, failedCount);
            statement.setString(7, status);
            statement.setString(8, message);
            return statement;
        }, keyHolder);
        return Objects.requireNonNull(keyHolder.getKey()).longValue();
    }

    public List<Map<String, Object>> listImportLogs(Long userId, int limit) {
        if (userId == null) {
            return jdbcTemplate.queryForList(
                    "SELECT * FROM question_import_logs ORDER BY id DESC LIMIT ?",
                    Math.max(1, Math.min(limit, 200))
            );
        }
        return jdbcTemplate.queryForList(
                "SELECT * FROM question_import_logs WHERE user_id = ? ORDER BY id DESC LIMIT ?",
                userId,
                Math.max(1, Math.min(limit, 200))
        );
    }

    private void bindQuestion(PreparedStatement statement, Question question, boolean update) throws SQLException {
        statement.setString(1, question.getSubject());
        statement.setString(2, question.getType());
        statement.setString(3, question.getContent());
        statement.setString(4, question.getOptionA());
        statement.setString(5, question.getOptionB());
        statement.setString(6, question.getOptionC());
        statement.setString(7, question.getOptionD());
        statement.setString(8, question.getAnswer());
        statement.setString(9, question.getAnalysis());
        statement.setString(10, question.getDifficulty());
        statement.setString(11, question.getKnowledgePoint());
        statement.setInt(12, question.getScore());
        statement.setObject(13, question.getCreatedBy());
    }

    private Question mapQuestion(ResultSet rs, int rowNum) throws SQLException {
        Question question = new Question();
        question.setId(rs.getLong("id"));
        question.setSubject(rs.getString("subject"));
        question.setType(rs.getString("type"));
        question.setContent(rs.getString("content"));
        question.setOptionA(rs.getString("option_a"));
        question.setOptionB(rs.getString("option_b"));
        question.setOptionC(rs.getString("option_c"));
        question.setOptionD(rs.getString("option_d"));
        question.setAnswer(rs.getString("answer"));
        question.setAnalysis(rs.getString("analysis"));
        question.setDifficulty(rs.getString("difficulty"));
        question.setKnowledgePoint(rs.getString("knowledge_point"));
        question.setScore(rs.getInt("score"));
        question.setCreatedBy(readNullableLong(rs, "created_by"));
        Timestamp createdTime = rs.getTimestamp("created_time");
        if (createdTime != null) {
            question.setCreatedTime(createdTime.toLocalDateTime());
        }
        return question;
    }

    private Long readNullableLong(ResultSet rs, String column) throws SQLException {
        long value = rs.getLong(column);
        return rs.wasNull() ? null : value;
    }

    private boolean hasText(String value) {
        return value != null && !value.trim().isEmpty();
    }

    private void ensureColumn(String tableName, String columnName, String definition) {
        Integer count = jdbcTemplate.queryForObject("""
                SELECT COUNT(*)
                FROM information_schema.columns
                WHERE table_schema = DATABASE()
                  AND table_name = ?
                  AND column_name = ?
                """, Integer.class, tableName, columnName);
        if (count == null || count == 0) {
            jdbcTemplate.execute("ALTER TABLE " + tableName + " ADD COLUMN " + columnName + " " + definition);
        }
    }
}
