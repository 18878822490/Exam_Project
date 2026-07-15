package com.exam.exam_platform.mapper;

import com.exam.exam_platform.entity.Exam;
import com.exam.exam_platform.entity.ExamQuestion;
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
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;

@Repository
public class ExamMapper {
    private final JdbcTemplate jdbcTemplate;

    public ExamMapper(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public void initSchema() {
        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS exams (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    title VARCHAR(128) NOT NULL,
                    subject VARCHAR(64) NOT NULL DEFAULT '综合',
                    start_time DATETIME,
                    end_time DATETIME,
                    duration INT,
                    total_score INT NOT NULL DEFAULT 0,
                    status VARCHAR(32) NOT NULL DEFAULT '草稿',
                    created_by BIGINT,
                    created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
                    INDEX idx_exams_status (status),
                    INDEX idx_exams_subject (subject),
                    INDEX idx_exams_created_by (created_by)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);
        ensureColumn("exams", "subject", "VARCHAR(64) NOT NULL DEFAULT '综合'");
        ensureColumn("exams", "start_time", "DATETIME");
        ensureColumn("exams", "end_time", "DATETIME");

        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS exam_questions (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    exam_id BIGINT NOT NULL,
                    question_id BIGINT NOT NULL,
                    sort_no INT NOT NULL,
                    score INT NOT NULL,
                    UNIQUE KEY uk_exam_question (exam_id, question_id),
                    INDEX idx_exam_questions_exam (exam_id)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);

        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS exam_publish (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    exam_id BIGINT NOT NULL,
                    class_id BIGINT,
                    class_name VARCHAR(64),
                    start_time DATETIME,
                    end_time DATETIME,
                    status VARCHAR(32) NOT NULL DEFAULT '已发布',
                    created_by BIGINT,
                    created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
                    INDEX idx_exam_publish_exam (exam_id),
                    INDEX idx_exam_publish_class (class_id, class_name)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);
    }

    public Long insertExam(Exam exam) {
        KeyHolder keyHolder = new GeneratedKeyHolder();
        jdbcTemplate.update(connection -> {
            PreparedStatement statement = connection.prepareStatement("""
                    INSERT INTO exams (title, subject, start_time, end_time, duration, total_score, status, created_by, created_time)
                    VALUES (?, ?, ?, ?, ?, ?, ?, ?, NOW())
                    """, Statement.RETURN_GENERATED_KEYS);
            statement.setString(1, exam.getTitle());
            statement.setString(2, defaultText(exam.getSubject(), "综合"));
            statement.setObject(3, exam.getStartTime());
            statement.setObject(4, exam.getEndTime());
            statement.setObject(5, exam.getDuration());
            statement.setObject(6, exam.getTotalScore() == null ? 0 : exam.getTotalScore());
            statement.setString(7, exam.getStatus());
            statement.setObject(8, exam.getCreatedBy());
            return statement;
        }, keyHolder);
        Long id = Objects.requireNonNull(keyHolder.getKey()).longValue();
        exam.setId(id);
        return id;
    }

    public void insertExamQuestion(Long examId, Question question, int sortNo) {
        jdbcTemplate.update("""
                INSERT IGNORE INTO exam_questions (exam_id, question_id, sort_no, score)
                VALUES (?, ?, ?, ?)
                """, examId, question.getId(), sortNo, question.getScore());
    }

    public void upsertExamQuestion(Long examId, Long questionId, int sortNo, int score) {
        jdbcTemplate.update("""
                INSERT INTO exam_questions (exam_id, question_id, sort_no, score)
                VALUES (?, ?, ?, ?)
                ON DUPLICATE KEY UPDATE sort_no = VALUES(sort_no), score = VALUES(score)
                """, examId, questionId, sortNo, score);
    }

    public boolean updateExamQuestion(Long examId, Long questionId, int sortNo, int score) {
        return jdbcTemplate.update("""
                UPDATE exam_questions
                SET sort_no = ?, score = ?
                WHERE exam_id = ? AND question_id = ?
                """, sortNo, score, examId, questionId) > 0;
    }

    public boolean deleteExamQuestion(Long examId, Long questionId) {
        return jdbcTemplate.update(
                "DELETE FROM exam_questions WHERE exam_id = ? AND question_id = ?",
                examId,
                questionId
        ) > 0;
    }

    public void deleteExamQuestions(Long examId) {
        jdbcTemplate.update("DELETE FROM exam_questions WHERE exam_id = ?", examId);
    }

    public int nextQuestionSortNo(Long examId) {
        Integer value = jdbcTemplate.queryForObject(
                "SELECT COALESCE(MAX(sort_no), 0) + 1 FROM exam_questions WHERE exam_id = ?",
                Integer.class,
                examId
        );
        return value == null ? 1 : value;
    }

    public int totalScoreForExam(Long examId) {
        Integer value = jdbcTemplate.queryForObject(
                "SELECT COALESCE(SUM(score), 0) FROM exam_questions WHERE exam_id = ?",
                Integer.class,
                examId
        );
        return value == null ? 0 : value;
    }

    public Integer scoreForExamQuestion(Long examId, Long questionId) {
        List<Integer> rows = jdbcTemplate.queryForList(
                "SELECT score FROM exam_questions WHERE exam_id = ? AND question_id = ? LIMIT 1",
                Integer.class,
                examId,
                questionId
        );
        return rows.isEmpty() ? null : rows.get(0);
    }

    public Integer sortNoForExamQuestion(Long examId, Long questionId) {
        List<Integer> rows = jdbcTemplate.queryForList(
                "SELECT sort_no FROM exam_questions WHERE exam_id = ? AND question_id = ? LIMIT 1",
                Integer.class,
                examId,
                questionId
        );
        return rows.isEmpty() ? null : rows.get(0);
    }

    public int countExamQuestions(Long examId) {
        Integer count = jdbcTemplate.queryForObject(
                "SELECT COUNT(*) FROM exam_questions WHERE exam_id = ?",
                Integer.class,
                examId
        );
        return count == null ? 0 : count;
    }

    public void updateTotalScore(Long examId, int totalScore) {
        jdbcTemplate.update("UPDATE exams SET total_score = ? WHERE id = ?", totalScore, examId);
    }

    public boolean hasSubmittedAnswers(Long examId) {
        Integer count = jdbcTemplate.queryForObject(
                "SELECT COUNT(*) FROM student_answers WHERE exam_id = ?",
                Integer.class,
                examId
        );
        return count != null && count > 0;
    }

    public boolean updateStatus(Long examId, String status) {
        return jdbcTemplate.update("UPDATE exams SET status = ? WHERE id = ?", status, examId) > 0;
    }

    public Exam findById(Long id) {
        List<Exam> exams = jdbcTemplate.query(
                "SELECT * FROM exams WHERE id = ? LIMIT 1",
                this::mapExam,
                id
        );
        return exams.isEmpty() ? null : exams.get(0);
    }

    public List<Exam> list(Long createdBy, String status) {
        StringBuilder sql = new StringBuilder("""
                SELECT e.*,
                       COALESCE(MIN(COALESCE(ep.start_time, e.start_time)), e.start_time) AS effective_start_time,
                       COALESCE(MAX(COALESCE(ep.end_time, e.end_time)), e.end_time) AS effective_end_time,
                       COALESCE((SELECT GROUP_CONCAT(DISTINCT ep.class_name ORDER BY ep.class_name SEPARATOR '、')
                                 FROM exam_publish ep WHERE ep.exam_id = e.id), '') AS class_names,
                       COUNT(DISTINCT ep.id) AS published_count,
                       (SELECT COUNT(DISTINCT s.student_no)
                        FROM students s
                        WHERE EXISTS (
                            SELECT 1
                            FROM exam_publish target
                            WHERE target.exam_id = e.id
                              AND (
                                  (target.class_id IS NOT NULL AND s.class_id = target.class_id)
                                  OR (target.class_name IS NOT NULL AND target.class_name <> '' AND s.class_name = target.class_name)
                              )
                        )) AS target_student_count,
                       (SELECT COUNT(DISTINCT sa.student_no)
                        FROM student_answers sa WHERE sa.exam_id = e.id) AS participants,
                       (SELECT COUNT(*)
                        FROM student_answers sa
                        WHERE sa.exam_id = e.id AND sa.review_status = '待批改') AS pending_review_count,
                       (SELECT COUNT(DISTINCT sa.student_no)
                        FROM student_answers sa
                        WHERE sa.exam_id = e.id
                          AND NOT EXISTS (
                              SELECT 1
                              FROM student_answers pending
                              WHERE pending.exam_id = e.id
                                AND pending.student_no = sa.student_no
                                AND pending.review_status = '待批改'
                          )) AS reviewed_students,
                       (SELECT COALESCE(AVG(sc.total_score), 0)
                        FROM scores sc WHERE sc.exam_id = e.id) AS average
                FROM exams e
                LEFT JOIN exam_publish ep ON ep.exam_id = e.id
                WHERE 1=1
                """);
        List<Object> args = new ArrayList<>();
        if (createdBy != null) {
            sql.append(" AND e.created_by = ?");
            args.add(createdBy);
        }
        if (status != null && !status.isBlank()) {
            sql.append(" AND e.status = ?");
            args.add(status.trim());
        }
        sql.append(" GROUP BY e.id ORDER BY e.id DESC");
        return jdbcTemplate.query(sql.toString(), this::mapExam, args.toArray());
    }

    public List<Map<String, Object>> listExamQuestions(Long examId) {
        return jdbcTemplate.queryForList("""
                SELECT eq.id AS exam_question_id, eq.sort_no, eq.score AS paper_score,
                       q.id AS question_id, q.subject, q.type, q.content, q.option_a, q.option_b,
                       q.option_c, q.option_d, q.answer, q.analysis, q.difficulty, q.knowledge_point
                FROM exam_questions eq
                INNER JOIN questions q ON q.id = eq.question_id
                WHERE eq.exam_id = ?
                ORDER BY eq.sort_no, eq.id
                """, examId);
    }

    public Long copyExam(Long sourceExamId, String title, Long createdBy) {
        return copyExam(sourceExamId, title, createdBy, null, null);
    }

    public Long copyExam(Long sourceExamId, String title, Long createdBy, LocalDateTime startTime, LocalDateTime endTime) {
        Exam source = findById(sourceExamId);
        if (source == null) {
            return null;
        }
        Exam target = new Exam();
        target.setTitle(title == null || title.isBlank() ? source.getTitle() + " 副本" : title.trim());
        target.setSubject(source.getSubject());
        target.setStartTime(startTime == null ? source.getStartTime() : startTime);
        target.setEndTime(endTime == null ? source.getEndTime() : endTime);
        target.setDuration(source.getDuration());
        target.setTotalScore(source.getTotalScore());
        target.setStatus("草稿");
        target.setCreatedBy(createdBy == null ? source.getCreatedBy() : createdBy);
        Long targetId = insertExam(target);

        jdbcTemplate.update("""
                INSERT INTO exam_questions (exam_id, question_id, sort_no, score)
                SELECT ?, question_id, sort_no, score FROM exam_questions WHERE exam_id = ?
                """, targetId, sourceExamId);
        return targetId;
    }

    public void publish(Long examId,
                        Long classId,
                        String className,
                        LocalDateTime startTime,
                        LocalDateTime endTime,
                        String status,
                        Long createdBy) {
        jdbcTemplate.update("""
                DELETE FROM exam_publish
                WHERE exam_id = ?
                  AND (
                      (? IS NOT NULL AND class_id = ?)
                      OR (? IS NOT NULL AND ? <> '' AND class_name = ?)
                  )
                """, examId, classId, classId, className, className, className);
        jdbcTemplate.update("""
                INSERT INTO exam_publish (
                    exam_id, class_id, class_name, start_time, end_time, status, created_by, created_time
                ) VALUES (?, ?, ?, ?, ?, ?, ?, NOW())
                """,
                examId,
                classId,
                className,
                startTime,
                endTime,
                status == null || status.isBlank() ? "已发布" : status,
                createdBy);
    }

    public List<Map<String, Object>> listPublished(String className, String studentNo) {
        String normalizedStudentNo = studentNo == null || studentNo.isBlank() ? null : studentNo.trim();
        if (className == null || className.isBlank()) {
            return jdbcTemplate.queryForList("""
                    SELECT ep.id AS publish_id, ep.exam_id, ep.class_id, COALESCE(ep.class_name, c.name) AS class_name,
                           COALESCE(ep.start_time, e.start_time) AS start_time,
                           COALESCE(ep.end_time, e.end_time) AS end_time,
                           CASE
                               WHEN ? IS NOT NULL AND EXISTS (
                                   SELECT 1
                                   FROM student_answers pending
                                   WHERE pending.exam_id = e.id
                                     AND pending.student_no = ?
                                     AND pending.review_status = '待批改'
                               ) THEN '待批改'
                               WHEN ? IS NOT NULL AND EXISTS (
                                   SELECT 1 FROM scores sc WHERE sc.exam_id = e.id AND sc.student_no = ?
                               ) THEN '已完成'
                               WHEN COALESCE(ep.start_time, e.start_time) IS NOT NULL
                                    AND NOW() < COALESCE(ep.start_time, e.start_time) THEN '未开始'
                               ELSE '已发布'
                           END AS status,
                           COALESCE((SELECT COUNT(*)
                                     FROM student_answers sa
                                     WHERE sa.exam_id = e.id AND sa.student_no = ?), 0) AS answer_count,
                           COALESCE((SELECT COUNT(*)
                                     FROM student_answers sa
                                     WHERE sa.exam_id = e.id
                                       AND sa.student_no = ?
                                       AND sa.review_status = '待批改'), 0) AS pending_review_count,
                           COALESCE((SELECT COUNT(*)
                                     FROM students s
                                     WHERE (ep.class_id IS NOT NULL AND s.class_id = ep.class_id)
                                        OR (ep.class_name IS NOT NULL AND ep.class_name <> '' AND s.class_name = ep.class_name)), 0)
                                     AS target_student_count,
                           COALESCE((SELECT COUNT(DISTINCT sa.student_no)
                                     FROM student_answers sa
                                     WHERE sa.exam_id = e.id
                                       AND (COALESCE(ep.class_name, c.name) IS NULL
                                            OR COALESCE(ep.class_name, c.name) = ''
                                            OR sa.class_name = COALESCE(ep.class_name, c.name))), 0)
                                     AS submitted_count,
                           COALESCE((SELECT COUNT(DISTINCT sa.student_no)
                                     FROM student_answers sa
                                     WHERE sa.exam_id = e.id
                                       AND (COALESCE(ep.class_name, c.name) IS NULL
                                            OR COALESCE(ep.class_name, c.name) = ''
                                            OR sa.class_name = COALESCE(ep.class_name, c.name))
                                       AND NOT EXISTS (
                                           SELECT 1
                                           FROM student_answers pending
                                           WHERE pending.exam_id = sa.exam_id
                                             AND pending.student_no = sa.student_no
                                             AND pending.review_status = '待批改'
                                       )), 0) AS reviewed_student_count,
                           (SELECT sc.total_score
                            FROM scores sc
                            WHERE sc.exam_id = e.id AND sc.student_no = ?
                            LIMIT 1) AS student_score,
                           ep.status AS publish_status,
                           ep.created_by AS publish_created_by, ep.created_time AS publish_created_time,
                           e.id, e.title, e.subject, e.duration, e.total_score, e.status AS exam_status,
                           e.created_by, e.created_time
                    FROM exam_publish ep
                    INNER JOIN exams e ON e.id = ep.exam_id
                    LEFT JOIN exam_classes c ON c.id = ep.class_id
                    ORDER BY ep.id DESC
                    """, normalizedStudentNo, normalizedStudentNo, normalizedStudentNo, normalizedStudentNo,
                    normalizedStudentNo, normalizedStudentNo, normalizedStudentNo);
        }
        return jdbcTemplate.queryForList("""
                SELECT ep.id AS publish_id, ep.exam_id, ep.class_id, COALESCE(ep.class_name, c.name) AS class_name,
                       COALESCE(ep.start_time, e.start_time) AS start_time,
                       COALESCE(ep.end_time, e.end_time) AS end_time,
                       CASE
                           WHEN ? IS NOT NULL AND EXISTS (
                               SELECT 1
                               FROM student_answers pending
                               WHERE pending.exam_id = e.id
                                 AND pending.student_no = ?
                                 AND pending.review_status = '待批改'
                           ) THEN '待批改'
                           WHEN ? IS NOT NULL AND EXISTS (
                               SELECT 1 FROM scores sc WHERE sc.exam_id = e.id AND sc.student_no = ?
                           ) THEN '已完成'
                           WHEN COALESCE(ep.start_time, e.start_time) IS NOT NULL
                                AND NOW() < COALESCE(ep.start_time, e.start_time) THEN '未开始'
                           ELSE '已发布'
                       END AS status,
                       COALESCE((SELECT COUNT(*)
                                 FROM student_answers sa
                                 WHERE sa.exam_id = e.id AND sa.student_no = ?), 0) AS answer_count,
                       COALESCE((SELECT COUNT(*)
                                 FROM student_answers sa
                                 WHERE sa.exam_id = e.id
                                   AND sa.student_no = ?
                                   AND sa.review_status = '待批改'), 0) AS pending_review_count,
                       COALESCE((SELECT COUNT(*)
                                 FROM students s
                                 WHERE (ep.class_id IS NOT NULL AND s.class_id = ep.class_id)
                                    OR (ep.class_name IS NOT NULL AND ep.class_name <> '' AND s.class_name = ep.class_name)), 0)
                                 AS target_student_count,
                       COALESCE((SELECT COUNT(DISTINCT sa.student_no)
                                 FROM student_answers sa
                                 WHERE sa.exam_id = e.id
                                   AND (COALESCE(ep.class_name, c.name) IS NULL
                                        OR COALESCE(ep.class_name, c.name) = ''
                                        OR sa.class_name = COALESCE(ep.class_name, c.name))), 0)
                                 AS submitted_count,
                       COALESCE((SELECT COUNT(DISTINCT sa.student_no)
                                 FROM student_answers sa
                                 WHERE sa.exam_id = e.id
                                   AND (COALESCE(ep.class_name, c.name) IS NULL
                                        OR COALESCE(ep.class_name, c.name) = ''
                                        OR sa.class_name = COALESCE(ep.class_name, c.name))
                                   AND NOT EXISTS (
                                       SELECT 1
                                       FROM student_answers pending
                                       WHERE pending.exam_id = sa.exam_id
                                         AND pending.student_no = sa.student_no
                                         AND pending.review_status = '待批改'
                                   )), 0) AS reviewed_student_count,
                       (SELECT sc.total_score
                        FROM scores sc
                        WHERE sc.exam_id = e.id AND sc.student_no = ?
                        LIMIT 1) AS student_score,
                       ep.status AS publish_status,
                       ep.created_by AS publish_created_by, ep.created_time AS publish_created_time,
                       e.id, e.title, e.subject, e.duration, e.total_score, e.status AS exam_status,
                       e.created_by, e.created_time
                FROM exam_publish ep
                INNER JOIN exams e ON e.id = ep.exam_id
                LEFT JOIN exam_classes c ON c.id = ep.class_id
                WHERE ep.class_name = ? OR c.name = ?
                ORDER BY ep.id DESC
                """, normalizedStudentNo, normalizedStudentNo, normalizedStudentNo, normalizedStudentNo,
                normalizedStudentNo, normalizedStudentNo, normalizedStudentNo, className, className);
    }

    public Map<String, Object> dashboardStats(Long teacherId) {
        Map<String, Object> stats = new LinkedHashMap<>();
        Integer questionCount = countValue("SELECT COUNT(*) FROM questions");
        Integer classCount = teacherId == null
                ? countValue("SELECT COUNT(*) FROM exam_classes")
                : countValue("SELECT COUNT(*) FROM teacher_classes WHERE teacher_id = ?", teacherId);
        Integer studentCount = teacherId == null
                ? countValue("SELECT COUNT(*) FROM students")
                : countValue("""
                        SELECT COUNT(DISTINCT s.id)
                        FROM students s
                        INNER JOIN teacher_classes tc ON tc.class_id = s.class_id
                        WHERE tc.teacher_id = ?
                        """, teacherId);
        Integer examCount = teacherId == null
                ? countValue("SELECT COUNT(*) FROM exams")
                : countValue("SELECT COUNT(*) FROM exams WHERE created_by = ?", teacherId);
        Integer pendingCount = countValue("SELECT COUNT(*) FROM student_answers WHERE review_status = '待批改'");
        int questionAdds = countValue("""
                SELECT COUNT(*)
                FROM operation_logs
                WHERE action = 'QUESTION_CREATE' AND DATE(created_time) = CURDATE()
                """) + countValue("""
                SELECT COALESCE(SUM(success_count), 0)
                FROM question_import_logs
                WHERE DATE(created_time) = CURDATE()
                """);
        if (questionAdds == 0) {
            questionAdds = countValue("SELECT COUNT(*) FROM questions WHERE DATE(created_time) = CURDATE()");
        }
        int questionDelta = questionAdds
                - countValue("SELECT COUNT(*) FROM operation_logs WHERE action = 'QUESTION_DELETE' AND DATE(created_time) = CURDATE()");
        int examAdds = teacherId == null
                ? countValue("""
                        SELECT COUNT(*)
                        FROM operation_logs
                        WHERE action IN ('EXAM_CREATE', 'EXAM_COPY') AND DATE(created_time) = CURDATE()
                        """)
                : countValue("""
                        SELECT COUNT(*)
                        FROM operation_logs
                        WHERE user_id = ? AND action IN ('EXAM_CREATE', 'EXAM_COPY') AND DATE(created_time) = CURDATE()
                        """, teacherId);
        if (examAdds == 0) {
            examAdds = teacherId == null
                    ? countValue("SELECT COUNT(*) FROM exams WHERE DATE(created_time) = CURDATE()")
                    : countValue("SELECT COUNT(*) FROM exams WHERE created_by = ? AND DATE(created_time) = CURDATE()", teacherId);
        }
        int examDelta = teacherId == null
                ? examAdds - countValue("SELECT COUNT(*) FROM operation_logs WHERE action = 'EXAM_DELETE' AND DATE(created_time) = CURDATE()")
                : examAdds - countValue("SELECT COUNT(*) FROM operation_logs WHERE user_id = ? AND action = 'EXAM_DELETE' AND DATE(created_time) = CURDATE()", teacherId);
        int studentDelta = teacherId == null
                ? countValue("SELECT COUNT(*) FROM students WHERE DATE(created_time) = CURDATE()")
                : countValue("""
                        SELECT COUNT(DISTINCT s.id)
                        FROM students s
                        INNER JOIN teacher_classes tc ON tc.class_id = s.class_id
                        WHERE tc.teacher_id = ? AND DATE(s.created_time) = CURDATE()
                        """, teacherId);
        double averageDelta = teacherId == null
                ? averageForDate("CURDATE()") - averageForDate("DATE_SUB(CURDATE(), INTERVAL 1 DAY)")
                : averageForDateByTeacher("CURDATE()", teacherId) - averageForDateByTeacher("DATE_SUB(CURDATE(), INTERVAL 1 DAY)", teacherId);
        stats.put("questionCount", questionCount == null ? 0 : questionCount);
        stats.put("classCount", classCount == null ? 0 : classCount);
        stats.put("studentCount", studentCount == null ? 0 : studentCount);
        stats.put("examCount", examCount == null ? 0 : examCount);
        stats.put("pendingCount", pendingCount == null ? 0 : pendingCount);
        stats.put("questionDelta", questionDelta);
        stats.put("examDelta", examDelta);
        stats.put("studentDelta", studentDelta);
        stats.put("averageDelta", Math.round(averageDelta * 10.0) / 10.0);
        return stats;
    }

    private Integer countValue(String sql, Object... args) {
        Integer value = jdbcTemplate.queryForObject(sql, Integer.class, args);
        return value == null ? 0 : value;
    }

    private double averageForDate(String dateExpression) {
        Double value = jdbcTemplate.queryForObject("""
                SELECT COALESCE(AVG(total_score), 0)
                FROM scores
                WHERE DATE(updated_time) = %s
                """.formatted(dateExpression), Double.class);
        return value == null ? 0 : value;
    }

    private double averageForDateByTeacher(String dateExpression, Long teacherId) {
        Double value = jdbcTemplate.queryForObject("""
                SELECT COALESCE(AVG(sc.total_score), 0)
                FROM scores sc
                INNER JOIN exam_classes c ON c.name = sc.class_name
                INNER JOIN teacher_classes tc ON tc.class_id = c.id
                WHERE tc.teacher_id = ? AND DATE(sc.updated_time) = %s
                """.formatted(dateExpression), Double.class, teacherId);
        return value == null ? 0 : value;
    }

    private Exam mapExam(ResultSet rs, int rowNum) throws SQLException {
        Exam exam = new Exam();
        exam.setId(rs.getLong("id"));
        exam.setTitle(rs.getString("title"));
        exam.setSubject(rs.getString("subject"));
        Timestamp startTime = hasColumn(rs, "effective_start_time") && rs.getTimestamp("effective_start_time") != null
                ? rs.getTimestamp("effective_start_time")
                : rs.getTimestamp("start_time");
        if (startTime != null) {
            exam.setStartTime(startTime.toLocalDateTime());
        }
        Timestamp endTime = hasColumn(rs, "effective_end_time") && rs.getTimestamp("effective_end_time") != null
                ? rs.getTimestamp("effective_end_time")
                : rs.getTimestamp("end_time");
        if (endTime != null) {
            exam.setEndTime(endTime.toLocalDateTime());
        }
        exam.setDuration(readNullableInteger(rs, "duration"));
        exam.setTotalScore(rs.getInt("total_score"));
        exam.setStatus(rs.getString("status"));
        exam.setCreatedBy(readNullableLong(rs, "created_by"));
        Timestamp createdTime = rs.getTimestamp("created_time");
        if (createdTime != null) {
            exam.setCreatedTime(createdTime.toLocalDateTime());
        }
        if (hasColumn(rs, "class_names")) {
            exam.setClassName(rs.getString("class_names"));
        }
        if (hasColumn(rs, "participants")) {
            exam.setParticipants(readNullableInteger(rs, "participants"));
        }
        if (hasColumn(rs, "published_count")) {
            exam.setPublishedCount(readNullableInteger(rs, "published_count"));
        }
        if (hasColumn(rs, "target_student_count")) {
            exam.setTargetStudentCount(readNullableInteger(rs, "target_student_count"));
        }
        if (hasColumn(rs, "pending_review_count")) {
            exam.setPendingReviewCount(readNullableInteger(rs, "pending_review_count"));
        }
        if (hasColumn(rs, "reviewed_students")) {
            exam.setReviewedStudents(readNullableInteger(rs, "reviewed_students"));
        }
        if (hasColumn(rs, "average")) {
            double average = rs.getDouble("average");
            exam.setAverage(rs.wasNull() ? null : average);
        }
        exam.setFlowStatus(resolveFlowStatus(exam));
        return exam;
    }

    private String resolveFlowStatus(Exam exam) {
        String status = defaultText(exam.getStatus(), "草稿");
        int publishedCount = exam.getPublishedCount() == null ? 0 : exam.getPublishedCount();
        if ("草稿".equals(status) || publishedCount == 0) {
            return "草稿";
        }

        LocalDateTime now = LocalDateTime.now();
        LocalDateTime startTime = exam.getStartTime();
        LocalDateTime endTime = exam.getEndTime();
        int pendingReviewCount = exam.getPendingReviewCount() == null ? 0 : exam.getPendingReviewCount();

        if (startTime != null && now.isBefore(startTime)) {
            return "未开始";
        }
        if (endTime != null && now.isAfter(endTime)) {
            return pendingReviewCount > 0 ? "待批改" : "已完成";
        }
        if (startTime != null && endTime != null && !now.isBefore(startTime) && !now.isAfter(endTime)) {
            return "进行中";
        }
        if (startTime == null && endTime == null) {
            return status;
        }
        if (startTime != null && !now.isBefore(startTime)) {
            return "进行中";
        }
        return status;
    }

    private Long readNullableLong(ResultSet rs, String column) throws SQLException {
        long value = rs.getLong(column);
        return rs.wasNull() ? null : value;
    }

    private Integer readNullableInteger(ResultSet rs, String column) throws SQLException {
        int value = rs.getInt(column);
        return rs.wasNull() ? null : value;
    }

    private boolean hasColumn(ResultSet rs, String column) throws SQLException {
        for (int i = 1; i <= rs.getMetaData().getColumnCount(); i++) {
            if (column.equalsIgnoreCase(rs.getMetaData().getColumnLabel(i))) {
                return true;
            }
        }
        return false;
    }

    private String defaultText(String value, String fallback) {
        return value == null || value.isBlank() ? fallback : value.trim();
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
