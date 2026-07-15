package com.exam.exam_platform.mapper;

import com.exam.exam_platform.entity.Question;
import org.springframework.dao.EmptyResultDataAccessException;
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
        normalizeLegacyProgrammingQuestionTypes();

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

    public boolean existsDuplicate(Question question) {
        Integer count = jdbcTemplate.queryForObject("""
                SELECT COUNT(*)
                FROM questions
                WHERE subject = ?
                  AND type = ?
                  AND TRIM(content) = ?
                  AND COALESCE(TRIM(answer), '') = ?
                """, Integer.class,
                question.getSubject(),
                question.getType(),
                question.getContent() == null ? "" : question.getContent().trim(),
                question.getAnswer() == null ? "" : question.getAnswer().trim());
        return count != null && count > 0;
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
            appendInFilter(sql, args, "subject", subjectAliases(subject));
        }
        if (hasText(type)) {
            List<String> aliases = typeAliases(type);
            sql.append(" AND (");
            appendInClause(sql, args, "type", aliases);
            sql.append(" OR ");
            appendInClause(sql, args, "content", aliases);
            sql.append(")");
        }
        if (hasText(difficulty)) {
            appendInFilter(sql, args, "difficulty", difficultyAliases(difficulty));
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
        StringBuilder sql = new StringBuilder("SELECT * FROM questions WHERE 1=1");
        List<Object> args = new ArrayList<>();
        if (hasText(type)) {
            List<String> typeValues = typeAliases(type);
            sql.append(" AND (");
            appendInClause(sql, args, "type", typeValues);
            sql.append(" OR ");
            appendInClause(sql, args, "content", typeValues);
            sql.append(")");
        }
        if (hasSpecificRandomSubject(subject)) {
            appendInFilter(sql, args, "subject", subjectAliases(subject));
        }
        if (hasText(difficulty)) {
            appendInFilter(sql, args, "difficulty", difficultyAliases(difficulty));
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

    public Map<String, Object> findImportLog(Long logId) {
        try {
            return jdbcTemplate.queryForMap("SELECT * FROM question_import_logs WHERE id = ? LIMIT 1", logId);
        } catch (EmptyResultDataAccessException exception) {
            return Map.of();
        }
    }

    public int countRollbackCandidates(Map<String, Object> log, int windowSeconds) {
        if (log == null || log.isEmpty()) {
            return 0;
        }
        Integer count = jdbcTemplate.queryForObject("""
                SELECT COUNT(*)
                FROM questions q
                WHERE q.created_by <=> ?
                  AND q.created_time BETWEEN DATE_SUB(?, INTERVAL ? SECOND) AND DATE_ADD(?, INTERVAL ? SECOND)
                  AND NOT EXISTS (SELECT 1 FROM exam_questions eq WHERE eq.question_id = q.id)
                  AND NOT EXISTS (SELECT 1 FROM student_answers sa WHERE sa.question_id = q.id)
                  AND NOT EXISTS (SELECT 1 FROM practice_answers pa WHERE pa.question_id = q.id)
                """, Integer.class,
                log.get("user_id"),
                log.get("created_time"),
                windowSeconds,
                log.get("created_time"),
                windowSeconds);
        return count == null ? 0 : count;
    }

    public int deleteRollbackCandidates(Map<String, Object> log, int windowSeconds) {
        if (log == null || log.isEmpty()) {
            return 0;
        }
        return jdbcTemplate.update("""
                DELETE q
                FROM questions q
                WHERE q.created_by <=> ?
                  AND q.created_time BETWEEN DATE_SUB(?, INTERVAL ? SECOND) AND DATE_ADD(?, INTERVAL ? SECOND)
                  AND NOT EXISTS (SELECT 1 FROM exam_questions eq WHERE eq.question_id = q.id)
                  AND NOT EXISTS (SELECT 1 FROM student_answers sa WHERE sa.question_id = q.id)
                  AND NOT EXISTS (SELECT 1 FROM practice_answers pa WHERE pa.question_id = q.id)
                """,
                log.get("user_id"),
                log.get("created_time"),
                windowSeconds,
                log.get("created_time"),
                windowSeconds);
    }

    public boolean markImportLogRolledBack(Long logId, int deletedCount) {
        return jdbcTemplate.update("""
                UPDATE question_import_logs
                SET status = '已撤回',
                    message = CONCAT(COALESCE(message, ''), '；已撤回删除 ', ?, ' 道题')
                WHERE id = ?
                """, deletedCount, logId) > 0;
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
        repairSwappedTypeAndContent(question);
        return question;
    }

    private void repairSwappedTypeAndContent(Question question) {
        String type = question.getType();
        String content = question.getContent();
        if (isKnownQuestionType(content) && !isKnownQuestionType(type) && hasText(type)) {
            question.setType(normalizeTypeValue(content));
            question.setContent(type);
        } else if (isKnownQuestionType(type)) {
            question.setType(normalizeTypeValue(type));
        }
    }

    private void appendInFilter(StringBuilder sql, List<Object> args, String column, List<String> values) {
        sql.append(" AND ");
        appendInClause(sql, args, column, values);
    }

    private void appendInClause(StringBuilder sql, List<Object> args, String column, List<String> values) {
        List<String> cleaned = distinctValues(values);
        if (cleaned.isEmpty()) {
            sql.append("1=1");
            return;
        }
        if (cleaned.size() == 1) {
            sql.append(column).append(" = ?");
            args.add(cleaned.get(0));
            return;
        }
        sql.append(column).append(" IN (");
        for (int i = 0; i < cleaned.size(); i++) {
            if (i > 0) {
                sql.append(", ");
            }
            sql.append("?");
            args.add(cleaned.get(i));
        }
        sql.append(")");
    }

    private List<String> subjectAliases(String subject) {
        String text = trimText(subject);
        String lower = text.toLowerCase();
        if ("高数".equals(text) || "高等数学".equals(text) || "数学".equals(text) || "math".equals(lower)) {
            return List.of("高数", "高等数学", "数学", "math");
        }
        if ("c++".equals(lower) || "cpp".equals(lower) || "c＋＋".equals(text)) {
            return List.of("C++", "cpp", "CPP", "C＋＋");
        }
        if ("java".equals(lower)) {
            return List.of("Java", "java", "JAVA");
        }
        if ("数据结构与算法".equals(text)) {
            return List.of("数据结构", "数据结构与算法");
        }
        if ("database".equals(lower) || "mysql".equals(lower)) {
            return List.of("数据库", "database", "MySQL", "mysql");
        }
        return List.of(text);
    }

    private List<String> typeAliases(String type) {
        String normalized = normalizeTypeValue(type);
        if ("单选题".equals(normalized)) {
            return List.of("单选题", "单选", "选择题", "single", "singleChoice", "singlechoice");
        }
        if ("多选题".equals(normalized)) {
            return List.of("多选题", "多选", "multiple", "multipleChoice", "multiplechoice", "multi");
        }
        if ("判断题".equals(normalized)) {
            return List.of("判断题", "判断", "judge", "truefalse", "true/false");
        }
        if ("填空题".equals(normalized)) {
            return List.of("填空题", "填空", "blank", "fill");
        }
        if ("编程题".equals(normalized)) {
            return List.of("编程题", "代码题", "程序题", "编程大题", "大题", "高数大题", "高数题", "数学大题",
                    "program", "coding", "code", "hard_math", "math");
        }
        return List.of(trimText(type));
    }

    private List<String> difficultyAliases(String difficulty) {
        String text = trimText(difficulty);
        String lower = text.toLowerCase();
        if ("基础".equals(text) || "简单".equals(text) || "easy".equals(lower)) {
            return List.of("基础", "简单", "easy");
        }
        if ("中等".equals(text) || "中".equals(text) || "medium".equals(lower) || "middle".equals(lower) || "normal".equals(lower)) {
            return List.of("中等", "中", "medium", "middle", "normal");
        }
        if ("困难".equals(text) || "难".equals(text) || "hard".equals(lower) || "difficult".equals(lower)) {
            return List.of("困难", "难", "hard", "difficult");
        }
        return List.of(text);
    }

    private String normalizeTypeValue(String type) {
        String text = trimText(type);
        String lower = text.toLowerCase();
        if ("single".equals(lower) || "singlechoice".equals(lower) || "单选".equals(text) || "选择题".equals(text)) {
            return "单选题";
        }
        if ("multiple".equals(lower) || "multiplechoice".equals(lower) || "multi".equals(lower) || "多选".equals(text)) {
            return "多选题";
        }
        if ("judge".equals(lower) || "truefalse".equals(lower) || "true/false".equals(lower) || "判断".equals(text)) {
            return "判断题";
        }
        if ("blank".equals(lower) || "fill".equals(lower) || "填空".equals(text)) {
            return "填空题";
        }
        if ("program".equals(lower)
                || "coding".equals(lower)
                || "code".equals(lower)
                || "hard_math".equals(lower)
                || "math".equals(lower)
                || "代码题".equals(text)
                || "程序题".equals(text)
                || "编程大题".equals(text)
                || "大题".equals(text)
                || "高数题".equals(text)
                || "高数大题".equals(text)
                || "数学大题".equals(text)) {
            return "编程题";
        }
        return text;
    }

    private boolean isKnownQuestionType(String type) {
        String normalized = normalizeTypeValue(type);
        return "单选题".equals(normalized)
                || "多选题".equals(normalized)
                || "判断题".equals(normalized)
                || "填空题".equals(normalized)
                || "编程题".equals(normalized);
    }

    private void normalizeLegacyProgrammingQuestionTypes() {
        jdbcTemplate.update("""
                UPDATE questions
                SET type = '编程题'
                WHERE type IN ('代码题', '程序题', '编程大题', '大题', '高数大题', '高数题', '数学大题')
                   OR LOWER(type) IN ('program', 'coding', 'code', 'hard_math', 'math')
                """);
    }

    private List<String> distinctValues(List<String> values) {
        List<String> result = new ArrayList<>();
        for (String value : values) {
            String text = trimText(value);
            if (!text.isEmpty() && !result.contains(text)) {
                result.add(text);
            }
        }
        return result;
    }

    private String trimText(String value) {
        return value == null ? "" : value.trim();
    }

    private Long readNullableLong(ResultSet rs, String column) throws SQLException {
        long value = rs.getLong(column);
        return rs.wasNull() ? null : value;
    }

    private boolean hasText(String value) {
        return value != null && !value.trim().isEmpty();
    }

    private boolean hasSpecificRandomSubject(String value) {
        if (!hasText(value)) {
            return false;
        }
        String text = value.trim();
        String lower = text.toLowerCase();
        return !"全部".equals(text)
                && !"全部科目".equals(text)
                && !"all".equals(lower);
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
