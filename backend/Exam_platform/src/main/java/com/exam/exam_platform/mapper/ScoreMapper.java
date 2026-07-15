package com.exam.exam_platform.mapper;

import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Map;

@Repository
public class ScoreMapper {
    private final JdbcTemplate jdbcTemplate;

    public ScoreMapper(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public void initSchema() {
        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS student_answers (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    exam_id BIGINT NOT NULL,
                    question_id BIGINT NOT NULL,
                    student_id BIGINT,
                    student_name VARCHAR(64),
                    student_no VARCHAR(32) NOT NULL,
                    class_name VARCHAR(64),
                    answer TEXT,
                    score DECIMAL(6,2),
                    review_status VARCHAR(32) NOT NULL DEFAULT '待批改',
                    comment TEXT,
                    created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
                    reviewed_time DATETIME,
                    INDEX idx_student_answers_exam (exam_id),
                    INDEX idx_student_answers_student (student_no),
                    INDEX idx_student_answers_status (review_status)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);
        ensureColumn("student_answers", "class_name", "VARCHAR(64)");
        ensureColumn("student_answers", "reviewed_time", "DATETIME");
        ensureColumn("student_answers", "correction_answer", "TEXT");
        ensureColumn("student_answers", "correction_reason", "TEXT");
        ensureColumn("student_answers", "correction_summary", "TEXT");
        ensureColumn("student_answers", "correction_status", "VARCHAR(32) NOT NULL DEFAULT '未订正'");
        ensureColumn("student_answers", "corrected_time", "DATETIME");

        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS scores (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    exam_id BIGINT NOT NULL,
                    student_id BIGINT,
                    student_no VARCHAR(32) NOT NULL,
                    student_name VARCHAR(64),
                    class_name VARCHAR(64),
                    total_score DECIMAL(6,2) NOT NULL DEFAULT 0,
                    created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
                    updated_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
                    UNIQUE KEY uk_score_exam_student (exam_id, student_no),
                    INDEX idx_scores_class (class_name)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);
    }

    public List<Map<String, Object>> listExamAnswerKeys(Long examId) {
        return jdbcTemplate.queryForList("""
                SELECT q.id AS question_id, q.type, q.answer AS standard_answer, eq.score
                FROM exam_questions eq
                INNER JOIN questions q ON q.id = eq.question_id
                WHERE eq.exam_id = ?
                ORDER BY eq.sort_no, eq.id
                """, examId);
    }

    public void deleteAnswersForStudentExam(Long examId, String studentNo) {
        jdbcTemplate.update(
                "DELETE FROM student_answers WHERE exam_id = ? AND student_no = ?",
                examId,
                studentNo
        );
    }

    public void insertStudentAnswer(Long examId,
                                    Long questionId,
                                    Long studentId,
                                    String studentName,
                                    String studentNo,
                                    String className,
                                    String answer,
                                    Double score,
                                    String reviewStatus) {
        jdbcTemplate.update("""
                INSERT INTO student_answers (
                    exam_id, question_id, student_id, student_name, student_no,
                    class_name, answer, score, review_status, created_time
                ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, NOW())
                """,
                examId, questionId, studentId, studentName, studentNo, className, answer, score, reviewStatus);
    }

    public List<Map<String, Object>> listAnswers(Long examId, String status) {
        if (status == null || status.isBlank()) {
            return jdbcTemplate.queryForList("""
                    SELECT sa.*, q.subject,
                           CASE
                               WHEN q.type IN ('单选题', '单选', '选择题') OR LOWER(q.type) IN ('single', 'singlechoice') THEN '单选题'
                               WHEN q.type IN ('多选题', '多选') OR LOWER(q.type) IN ('multiple', 'multiplechoice', 'multi') THEN '多选题'
                               WHEN q.type IN ('判断题', '判断') OR LOWER(q.type) IN ('judge', 'truefalse', 'true/false') THEN '判断题'
                               WHEN q.type IN ('填空题', '填空') OR LOWER(q.type) IN ('blank', 'fill') THEN '填空题'
                               WHEN q.type IN ('编程题', '代码题') OR LOWER(q.type) IN ('program', 'coding', 'code') THEN '编程题'
                               WHEN q.type IN ('高数大题', '高数题', '数学大题') OR LOWER(q.type) = 'math' THEN '编程题'
                               ELSE q.type
                           END AS type,
                           q.content, q.answer AS standard_answer,
                           q.analysis, q.knowledge_point, eq.sort_no, eq.score AS question_score
                    FROM student_answers sa
                    INNER JOIN questions q ON q.id = sa.question_id
                    LEFT JOIN exam_questions eq ON eq.exam_id = sa.exam_id AND eq.question_id = sa.question_id
                    WHERE sa.exam_id = ?
                    ORDER BY sa.student_no, eq.sort_no, sa.id
                    """, examId);
        }
        return jdbcTemplate.queryForList("""
                SELECT sa.*, q.subject,
                       CASE
                           WHEN q.type IN ('单选题', '单选', '选择题') OR LOWER(q.type) IN ('single', 'singlechoice') THEN '单选题'
                           WHEN q.type IN ('多选题', '多选') OR LOWER(q.type) IN ('multiple', 'multiplechoice', 'multi') THEN '多选题'
                           WHEN q.type IN ('判断题', '判断') OR LOWER(q.type) IN ('judge', 'truefalse', 'true/false') THEN '判断题'
                           WHEN q.type IN ('填空题', '填空') OR LOWER(q.type) IN ('blank', 'fill') THEN '填空题'
                           WHEN q.type IN ('编程题', '代码题') OR LOWER(q.type) IN ('program', 'coding', 'code') THEN '编程题'
                           WHEN q.type IN ('高数大题', '高数题', '数学大题') OR LOWER(q.type) = 'math' THEN '编程题'
                           ELSE q.type
                       END AS type,
                       q.content, q.answer AS standard_answer,
                       q.analysis, q.knowledge_point, eq.sort_no, eq.score AS question_score
                FROM student_answers sa
                INNER JOIN questions q ON q.id = sa.question_id
                LEFT JOIN exam_questions eq ON eq.exam_id = sa.exam_id AND eq.question_id = sa.question_id
                WHERE sa.exam_id = ? AND sa.review_status = ?
                ORDER BY sa.student_no, eq.sort_no, sa.id
                """, examId, status);
    }

    public List<Map<String, Object>> listAnswerStudents(Long examId, String status) {
        StringBuilder sql = new StringBuilder("""
                SELECT sa.exam_id,
                       e.title AS exam_title,
                       e.subject,
                       sa.student_id,
                       sa.student_name,
                       sa.student_no,
                       sa.class_name,
                       COUNT(*) AS answer_count,
                       SUM(CASE WHEN sa.review_status = '待批改' THEN 1 ELSE 0 END) AS pending_count,
                       CASE WHEN SUM(CASE WHEN sa.review_status = '待批改' THEN 1 ELSE 0 END) = 0
                            THEN '已批改' ELSE '待批改' END AS review_status,
                       COALESCE(MAX(sc.total_score), SUM(COALESCE(sa.score, 0))) AS score
                FROM student_answers sa
                INNER JOIN exams e ON e.id = sa.exam_id
                LEFT JOIN scores sc ON sc.exam_id = sa.exam_id AND sc.student_no = sa.student_no
                WHERE 1=1
                """);
        List<Object> args = new java.util.ArrayList<>();
        if (examId != null) {
            sql.append(" AND sa.exam_id = ? ");
            args.add(examId);
        }
        sql.append("""
                GROUP BY sa.exam_id, e.title, e.subject, sa.student_id, sa.student_name, sa.student_no, sa.class_name
                """);
        if ("待批改".equals(status)) {
            sql.append(" HAVING SUM(CASE WHEN sa.review_status = '待批改' THEN 1 ELSE 0 END) > 0");
        } else if ("已批改".equals(status)) {
            sql.append(" HAVING SUM(CASE WHEN sa.review_status = '待批改' THEN 1 ELSE 0 END) = 0");
        }
        sql.append(" ORDER BY sa.exam_id DESC, pending_count DESC, sa.student_no");
        return jdbcTemplate.queryForList(sql.toString(), args.toArray());
    }

    public List<Map<String, Object>> listReviewExams(Long teacherId) {
        StringBuilder sql = new StringBuilder("""
                SELECT e.id,
                       e.title,
                       e.subject,
                       COALESCE(MIN(COALESCE(ep.start_time, e.start_time)), e.start_time) AS start_time,
                       COALESCE(MAX(COALESCE(ep.end_time, e.end_time)), e.end_time) AS end_time,
                       DATE_FORMAT(COALESCE(MIN(COALESCE(ep.start_time, e.start_time)), e.start_time, e.created_time), '%Y-%m-%d') AS exam_date,
                       e.total_score,
                       e.status,
                       COALESCE((SELECT COUNT(DISTINCT sa.student_no)
                                 FROM student_answers sa
                                 WHERE sa.exam_id = e.id), 0) AS submitted_count,
                       COALESCE((SELECT COUNT(DISTINCT sa.student_no)
                                 FROM student_answers sa
                                 WHERE sa.exam_id = e.id
                                   AND NOT EXISTS (
                                       SELECT 1
                                       FROM student_answers pending
                                       WHERE pending.exam_id = sa.exam_id
                                         AND pending.student_no = sa.student_no
                                         AND pending.review_status = '待批改'
                                   )), 0) AS completed_count,
                       COALESCE((SELECT COUNT(DISTINCT sa.student_no)
                                 FROM student_answers sa
                                 WHERE sa.exam_id = e.id
                                   AND EXISTS (
                                       SELECT 1
                                       FROM student_answers pending
                                       WHERE pending.exam_id = sa.exam_id
                                         AND pending.student_no = sa.student_no
                                         AND pending.review_status = '待批改'
                                   )), 0) AS pending_student_count,
                       COALESCE((SELECT COUNT(*)
                                 FROM student_answers sa
                                 WHERE sa.exam_id = e.id AND sa.review_status = '待批改'), 0) AS pending_answer_count,
                       ROUND(COALESCE((SELECT AVG(sc.total_score)
                                       FROM scores sc
                                       WHERE sc.exam_id = e.id
                                         AND NOT EXISTS (
                                             SELECT 1
                                             FROM student_answers pending
                                             WHERE pending.exam_id = sc.exam_id
                                               AND pending.student_no = sc.student_no
                                               AND pending.review_status = '待批改'
                                         )), 0), 1) AS average_score,
                       CASE
                           WHEN COALESCE((SELECT COUNT(DISTINCT sa.student_no)
                                          FROM student_answers sa
                                          WHERE sa.exam_id = e.id), 0) = 0 THEN '暂无提交'
                           WHEN COALESCE((SELECT COUNT(*)
                                          FROM student_answers sa
                                          WHERE sa.exam_id = e.id AND sa.review_status = '待批改'), 0) = 0 THEN '已批改'
                           ELSE '待批改'
                       END AS review_status
                FROM exams e
                LEFT JOIN exam_publish ep ON ep.exam_id = e.id
                WHERE 1=1
                """);
        List<Object> args = new java.util.ArrayList<>();
        if (teacherId != null) {
            sql.append(" AND e.created_by = ? ");
            args.add(teacherId);
        }
        sql.append("""
                GROUP BY e.id, e.title, e.subject, e.start_time, e.end_time, e.total_score, e.status, e.created_time
                ORDER BY pending_answer_count DESC, submitted_count DESC, e.id DESC
                """);
        return jdbcTemplate.queryForList(sql.toString(), args.toArray());
    }

    public List<Map<String, Object>> listReviewStudents(Long examId, String status) {
        StringBuilder sql = new StringBuilder("""
                SELECT review.*,
                       CASE
                           WHEN review.pending_count = 0 THEN '已批改'
                           WHEN review.pending_count = review.answer_count THEN '待批改'
                           ELSE '批改中'
                       END AS review_status
                FROM (
                    SELECT sa.exam_id,
                           e.title AS exam_title,
                           e.subject,
                           sa.student_id,
                           sa.student_name,
                           sa.student_no,
                           sa.class_name,
                           COUNT(*) AS answer_count,
                           SUM(CASE WHEN sa.review_status = '待批改' THEN 1 ELSE 0 END) AS pending_count,
                           COALESCE(MAX(sc.total_score), SUM(COALESCE(sa.score, 0))) AS score
                    FROM student_answers sa
                    INNER JOIN exams e ON e.id = sa.exam_id
                    LEFT JOIN scores sc ON sc.exam_id = sa.exam_id AND sc.student_no = sa.student_no
                    WHERE sa.exam_id = ?
                    GROUP BY sa.exam_id, e.title, e.subject, sa.student_id, sa.student_name, sa.student_no, sa.class_name
                ) review
                WHERE 1=1
                """);
        List<Object> args = new java.util.ArrayList<>();
        args.add(examId);
        if (status != null && !status.isBlank()) {
            sql.append("""
                    AND CASE
                            WHEN review.pending_count = 0 THEN '已批改'
                            WHEN review.pending_count = review.answer_count THEN '待批改'
                            ELSE '批改中'
                        END = ?
                    """);
            args.add(status.trim());
        }
        sql.append(" ORDER BY review.pending_count DESC, review.student_no");
        return jdbcTemplate.queryForList(sql.toString(), args.toArray());
    }

    public List<Map<String, Object>> listStudentAnswers(Long examId, String studentNo, String status) {
        StringBuilder sql = new StringBuilder("""
                SELECT sa.*, q.subject,
                       CASE
                           WHEN q.type IN ('单选题', '单选', '选择题') OR LOWER(q.type) IN ('single', 'singlechoice') THEN '单选题'
                           WHEN q.type IN ('多选题', '多选') OR LOWER(q.type) IN ('multiple', 'multiplechoice', 'multi') THEN '多选题'
                           WHEN q.type IN ('判断题', '判断') OR LOWER(q.type) IN ('judge', 'truefalse', 'true/false') THEN '判断题'
                           WHEN q.type IN ('填空题', '填空') OR LOWER(q.type) IN ('blank', 'fill') THEN '填空题'
                           WHEN q.type IN ('编程题', '代码题') OR LOWER(q.type) IN ('program', 'coding', 'code') THEN '编程题'
                           WHEN q.type IN ('高数大题', '高数题', '数学大题') OR LOWER(q.type) = 'math' THEN '编程题'
                           ELSE q.type
                       END AS type,
                       q.content, q.answer AS standard_answer,
                       q.analysis, q.knowledge_point, eq.sort_no, eq.score AS question_score,
                       CASE
                           WHEN q.type IN ('单选题', '多选题', '判断题', '填空题', '单选', '多选', '判断', '填空', '选择题')
                             OR LOWER(q.type) IN ('single', 'singlechoice', 'multiple', 'multiplechoice', 'multi', 'judge', 'truefalse', 'true/false', 'blank', 'fill')
                           THEN 1 ELSE 0
                       END AS is_objective
                FROM student_answers sa
                INNER JOIN questions q ON q.id = sa.question_id
                LEFT JOIN exam_questions eq ON eq.exam_id = sa.exam_id AND eq.question_id = sa.question_id
                WHERE sa.exam_id = ? AND sa.student_no = ?
                """);
        List<Object> args = new java.util.ArrayList<>();
        args.add(examId);
        args.add(studentNo);
        if (status != null && !status.isBlank()) {
            sql.append(" AND sa.review_status = ?");
            args.add(status.trim());
        }
        sql.append(" ORDER BY eq.sort_no, sa.id");
        return jdbcTemplate.queryForList(sql.toString(), args.toArray());
    }

    public Map<String, Object> findAnswerById(Long answerId) {
        List<Map<String, Object>> rows = jdbcTemplate.queryForList("""
                SELECT sa.*, eq.score AS question_score, q.type
                FROM student_answers sa
                LEFT JOIN exam_questions eq ON eq.exam_id = sa.exam_id AND eq.question_id = sa.question_id
                LEFT JOIN questions q ON q.id = sa.question_id
                WHERE sa.id = ?
                LIMIT 1
                """, answerId);
        return rows.isEmpty() ? null : rows.get(0);
    }

    public boolean updateReviewScore(Long answerId, Double score, String comment) {
        return jdbcTemplate.update("""
                UPDATE student_answers
                SET score = ?, comment = ?, review_status = '已批改', reviewed_time = NOW()
                WHERE id = ?
                """, score, comment, answerId) > 0;
    }

    public boolean saveWrongQuestionCorrection(Long answerId,
                                               String studentNo,
                                               String correctionAnswer,
                                               String errorReason,
                                               String knowledgeSummary) {
        return jdbcTemplate.update("""
                UPDATE student_answers
                SET correction_answer = ?,
                    correction_reason = ?,
                    correction_summary = ?,
                    correction_status = '已订正',
                    corrected_time = NOW()
                WHERE id = ? AND student_no = ?
                """, correctionAnswer, errorReason, knowledgeSummary, answerId, studentNo) > 0;
    }

    public void upsertTotalScore(Long examId, Long studentId, String studentNo, String studentName, String className) {
        Double total = jdbcTemplate.queryForObject("""
                SELECT COALESCE(SUM(score), 0)
                FROM student_answers
                WHERE exam_id = ? AND student_no = ?
                """, Double.class, examId, studentNo);
        jdbcTemplate.update("""
                INSERT INTO scores (exam_id, student_id, student_no, student_name, class_name, total_score, created_time, updated_time)
                VALUES (?, ?, ?, ?, ?, ?, NOW(), NOW())
                ON DUPLICATE KEY UPDATE
                    student_id = VALUES(student_id),
                    student_name = VALUES(student_name),
                    class_name = VALUES(class_name),
                    total_score = VALUES(total_score),
                    updated_time = NOW()
                """, examId, studentId, studentNo, studentName, className, total == null ? 0 : total);
    }

    public List<Map<String, Object>> listScores(Long examId, String className) {
        if (className == null || className.isBlank()) {
            return jdbcTemplate.queryForList("""
                    SELECT *
                    FROM scores
                    WHERE exam_id = ?
                      AND NOT EXISTS (
                          SELECT 1
                          FROM student_answers pending
                          WHERE pending.exam_id = scores.exam_id
                            AND pending.student_no = scores.student_no
                            AND pending.review_status = '待批改'
                      )
                    ORDER BY total_score DESC
                    """, examId);
        }
        return jdbcTemplate.queryForList(
                """
                SELECT *
                FROM scores
                WHERE exam_id = ?
                  AND class_name = ?
                  AND NOT EXISTS (
                      SELECT 1
                      FROM student_answers pending
                      WHERE pending.exam_id = scores.exam_id
                        AND pending.student_no = scores.student_no
                        AND pending.review_status = '待批改'
                  )
                ORDER BY total_score DESC
                """,
                examId,
                className
        );
    }

    public List<Map<String, Object>> studentHistory(String studentNo, String subject) {
        StringBuilder sql = new StringBuilder("""
                SELECT sc.exam_id,
                       e.title AS exam_title,
                       e.subject,
                       e.total_score AS full_score,
                       sc.total_score,
                       sc.student_no,
                       sc.student_name,
                       sc.class_name,
                       DATE_FORMAT(COALESCE(e.start_time, sc.updated_time, sc.created_time), '%Y-%m-%d') AS exam_date,
                       DATE_FORMAT(COALESCE(e.start_time, sc.updated_time, sc.created_time), '%m/%d') AS trend_label,
                       ROUND((
                           SELECT COALESCE(AVG(peer.total_score), 0)
                           FROM scores peer
                           WHERE peer.exam_id = sc.exam_id
                             AND (COALESCE(sc.class_name, '') = '' OR peer.class_name = sc.class_name)
                             AND NOT EXISTS (
                                 SELECT 1
                                 FROM student_answers pending
                                 WHERE pending.exam_id = peer.exam_id
                                   AND pending.student_no = peer.student_no
                                   AND pending.review_status = '待批改'
                             )
                       ), 1) AS class_average,
                       (
                           SELECT COUNT(*) + 1
                           FROM scores peer
                           WHERE peer.exam_id = sc.exam_id
                             AND (COALESCE(sc.class_name, '') = '' OR peer.class_name = sc.class_name)
                             AND peer.total_score > sc.total_score
                             AND NOT EXISTS (
                                 SELECT 1
                                 FROM student_answers pending
                                 WHERE pending.exam_id = peer.exam_id
                                   AND pending.student_no = peer.student_no
                                   AND pending.review_status = '待批改'
                             )
                       ) AS class_rank,
                       (
                           SELECT COUNT(*)
                           FROM scores peer
                           WHERE peer.exam_id = sc.exam_id
                             AND (COALESCE(sc.class_name, '') = '' OR peer.class_name = sc.class_name)
                             AND NOT EXISTS (
                                 SELECT 1
                                 FROM student_answers pending
                                 WHERE pending.exam_id = peer.exam_id
                                   AND pending.student_no = peer.student_no
                                   AND pending.review_status = '待批改'
                             )
                       ) AS class_student_count
                FROM scores sc
                INNER JOIN exams e ON e.id = sc.exam_id
                WHERE sc.student_no = ?
                  AND NOT EXISTS (
                      SELECT 1
                      FROM student_answers pending
                      WHERE pending.exam_id = sc.exam_id
                        AND pending.student_no = sc.student_no
                        AND pending.review_status = '待批改'
                  )
                """);
        List<Object> args = new java.util.ArrayList<>();
        args.add(studentNo);
        if (subject != null && !subject.isBlank() && !"全部科目".equals(subject.trim())) {
            sql.append(" AND e.subject = ?");
            args.add(subject.trim());
        }
        sql.append(" ORDER BY COALESCE(e.start_time, sc.updated_time, sc.created_time), sc.exam_id");
        return jdbcTemplate.queryForList(sql.toString(), args.toArray());
    }

    public List<Map<String, Object>> classAverageTrend(String className, String subject, Integer limit) {
        StringBuilder sql = new StringBuilder("""
                SELECT trend.exam_id,
                       trend.exam_title,
                       trend.subject,
                       trend.exam_date,
                       trend.trend_label,
                       trend.average_score,
                       trend.student_count
                FROM (
                    SELECT e.id AS exam_id,
                           e.title AS exam_title,
                           e.subject,
                           DATE_FORMAT(COALESCE(e.start_time, MAX(sc.updated_time), MAX(sc.created_time)), '%Y-%m-%d') AS exam_date,
                           DATE_FORMAT(COALESCE(e.start_time, MAX(sc.updated_time), MAX(sc.created_time)), '%m/%d') AS trend_label,
                           ROUND(AVG(sc.total_score), 1) AS average_score,
                           COUNT(*) AS student_count,
                           COALESCE(e.start_time, MAX(sc.updated_time), MAX(sc.created_time)) AS sort_time
                    FROM scores sc
                    INNER JOIN exams e ON e.id = sc.exam_id
                    WHERE 1=1
                      AND NOT EXISTS (
                          SELECT 1
                          FROM student_answers pending
                          WHERE pending.exam_id = sc.exam_id
                            AND pending.student_no = sc.student_no
                            AND pending.review_status = '待批改'
                      )
                """);
        List<Object> args = new java.util.ArrayList<>();
        if (className != null && !className.isBlank()) {
            sql.append(" AND sc.class_name = ?");
            args.add(className.trim());
        }
        if (subject != null && !subject.isBlank() && !"全部科目".equals(subject.trim())) {
            sql.append(" AND e.subject = ?");
            args.add(subject.trim());
        }
        sql.append("""
                    GROUP BY e.id, e.title, e.subject, e.start_time
                    ORDER BY sort_time DESC, e.id DESC
                    LIMIT ?
                ) trend
                ORDER BY trend.sort_time ASC, trend.exam_id ASC
                """);
        args.add(Math.max(1, Math.min(limit == null ? 7 : limit, 20)));
        return jdbcTemplate.queryForList(sql.toString(), args.toArray());
    }

    public List<Map<String, Object>> listScoreExams(Long teacherId, String className, String subject, Integer limit) {
        StringBuilder sql = new StringBuilder("""
                SELECT e.id,
                       e.title,
                       e.subject,
                       e.total_score,
                       COALESCE(MIN(COALESCE(ep.start_time, e.start_time)), e.start_time) AS start_time,
                       COALESCE(MAX(COALESCE(ep.end_time, e.end_time)), e.end_time) AS end_time,
                       DATE_FORMAT(COALESCE(MIN(COALESCE(ep.start_time, e.start_time)), e.start_time, e.created_time), '%Y-%m-%d') AS exam_date,
                       COALESCE((SELECT GROUP_CONCAT(DISTINCT COALESCE(ep2.class_name, c2.name) ORDER BY COALESCE(ep2.class_name, c2.name) SEPARATOR '、')
                                 FROM exam_publish ep2
                                 LEFT JOIN exam_classes c2 ON c2.id = ep2.class_id
                                 WHERE ep2.exam_id = e.id), '') AS class_names,
                       COUNT(DISTINCT sc.student_no) AS student_count,
                       ROUND(COALESCE(AVG(sc.total_score), 0), 1) AS average_score,
                       COALESCE(MAX(sc.updated_time), e.created_time) AS score_time
                FROM exams e
                LEFT JOIN exam_publish ep ON ep.exam_id = e.id
                LEFT JOIN scores sc ON sc.exam_id = e.id
                    AND NOT EXISTS (
                        SELECT 1
                        FROM student_answers pending
                        WHERE pending.exam_id = sc.exam_id
                          AND pending.student_no = sc.student_no
                          AND pending.review_status = '待批改'
                    )
                WHERE EXISTS (
                    SELECT 1
                    FROM scores sx
                    WHERE sx.exam_id = e.id
                      AND NOT EXISTS (
                          SELECT 1
                          FROM student_answers pending
                          WHERE pending.exam_id = sx.exam_id
                            AND pending.student_no = sx.student_no
                            AND pending.review_status = '待批改'
                      )
                )
                """);
        List<Object> args = new java.util.ArrayList<>();
        if (teacherId != null) {
            sql.append(" AND e.created_by = ?");
            args.add(teacherId);
        }
        if (className != null && !className.isBlank()) {
            sql.append("""
                    AND EXISTS (
                        SELECT 1
                        FROM scores class_score
                        WHERE class_score.exam_id = e.id
                          AND class_score.class_name = ?
                          AND NOT EXISTS (
                              SELECT 1
                              FROM student_answers pending
                              WHERE pending.exam_id = class_score.exam_id
                                AND pending.student_no = class_score.student_no
                                AND pending.review_status = '待批改'
                          )
                    )
                    """);
            args.add(className.trim());
        }
        if (subject != null && !subject.isBlank() && !"全部科目".equals(subject.trim())) {
            sql.append(" AND e.subject = ?");
            args.add(subject.trim());
        }
        sql.append("""
                GROUP BY e.id, e.title, e.subject, e.total_score, e.start_time, e.end_time, e.created_time
                ORDER BY COALESCE(e.start_time, score_time, e.created_time) DESC, e.id DESC
                LIMIT ?
                """);
        args.add(Math.max(1, Math.min(limit == null ? 50 : limit, 200)));
        return jdbcTemplate.queryForList(sql.toString(), args.toArray());
    }

    public Map<String, Object> scoreSummary(Long examId, String className) {
        if (className == null || className.isBlank()) {
            return jdbcTemplate.queryForMap("""
                    SELECT
                        COALESCE(AVG(total_score), 0) AS average_score,
                        COALESCE(MAX(total_score), 0) AS highest_score,
                        COALESCE(MIN(total_score), 0) AS lowest_score,
                        COUNT(*) AS student_count,
                        COALESCE(SUM(CASE WHEN total_score >= 60 THEN 1 ELSE 0 END) / NULLIF(COUNT(*), 0) * 100, 0) AS pass_rate,
                        COALESCE(SUM(CASE WHEN total_score >= 90 THEN 1 ELSE 0 END) / NULLIF(COUNT(*), 0) * 100, 0) AS excellent_rate
                    FROM scores
                    WHERE exam_id = ?
                      AND NOT EXISTS (
                          SELECT 1
                          FROM student_answers pending
                          WHERE pending.exam_id = scores.exam_id
                            AND pending.student_no = scores.student_no
                            AND pending.review_status = '待批改'
                      )
                    """, examId);
        }
        return jdbcTemplate.queryForMap("""
                SELECT
                    COALESCE(AVG(total_score), 0) AS average_score,
                    COALESCE(MAX(total_score), 0) AS highest_score,
                    COALESCE(MIN(total_score), 0) AS lowest_score,
                    COUNT(*) AS student_count,
                    COALESCE(SUM(CASE WHEN total_score >= 60 THEN 1 ELSE 0 END) / NULLIF(COUNT(*), 0) * 100, 0) AS pass_rate,
                    COALESCE(SUM(CASE WHEN total_score >= 90 THEN 1 ELSE 0 END) / NULLIF(COUNT(*), 0) * 100, 0) AS excellent_rate
                FROM scores
                WHERE exam_id = ? AND class_name = ?
                  AND NOT EXISTS (
                      SELECT 1
                      FROM student_answers pending
                      WHERE pending.exam_id = scores.exam_id
                        AND pending.student_no = scores.student_no
                        AND pending.review_status = '待批改'
                  )
                """, examId, className);
    }

    public List<Map<String, Object>> scoreDistribution(Long examId, String className) {
        String classFilter = className == null || className.isBlank() ? "" : " AND class_name = ?";
        Object[] args = classFilter.isEmpty() ? new Object[]{examId} : new Object[]{examId, className};
        String completedFilter = """
                 AND NOT EXISTS (
                     SELECT 1
                     FROM student_answers pending
                     WHERE pending.exam_id = scores.exam_id
                       AND pending.student_no = scores.student_no
                       AND pending.review_status = '待批改'
                 )
                """;
        return jdbcTemplate.queryForList("""
                SELECT '90-100' AS label, COUNT(*) AS value FROM scores WHERE exam_id = ? %s %s AND total_score >= 90
                UNION ALL
                SELECT '80-90' AS label, COUNT(*) AS value FROM scores WHERE exam_id = ? %s %s AND total_score >= 80 AND total_score < 90
                UNION ALL
                SELECT '70-80' AS label, COUNT(*) AS value FROM scores WHERE exam_id = ? %s %s AND total_score >= 70 AND total_score < 80
                UNION ALL
                SELECT '60-70' AS label, COUNT(*) AS value FROM scores WHERE exam_id = ? %s %s AND total_score >= 60 AND total_score < 70
                UNION ALL
                SELECT '60以下' AS label, COUNT(*) AS value FROM scores WHERE exam_id = ? %s %s AND total_score < 60
                """.formatted(classFilter, completedFilter, classFilter, completedFilter, classFilter, completedFilter,
                        classFilter, completedFilter, classFilter, completedFilter),
                expandDistributionArgs(args));
    }

    public List<Map<String, Object>> questionAnalysis(Long examId, String className) {
        StringBuilder sql = new StringBuilder("""
                SELECT q.id AS question_id,
                       eq.sort_no AS number,
                       CASE
                           WHEN q.type IN ('单选题', '单选', '选择题') OR LOWER(q.type) IN ('single', 'singlechoice') THEN '单选题'
                           WHEN q.type IN ('多选题', '多选') OR LOWER(q.type) IN ('multiple', 'multiplechoice', 'multi') THEN '多选题'
                           WHEN q.type IN ('判断题', '判断') OR LOWER(q.type) IN ('judge', 'truefalse', 'true/false') THEN '判断题'
                           WHEN q.type IN ('填空题', '填空') OR LOWER(q.type) IN ('blank', 'fill') THEN '填空题'
                           WHEN q.type IN ('编程题', '代码题') OR LOWER(q.type) IN ('program', 'coding', 'code') THEN '编程题'
                           WHEN q.type IN ('高数大题', '高数题', '数学大题') OR LOWER(q.type) = 'math' THEN '编程题'
                           ELSE q.type
                       END AS type,
                       eq.score AS full_score,
                       COALESCE(AVG(sa.score), 0) AS average_score,
                       CASE WHEN COALESCE(AVG(sa.score), 0) < eq.score * 0.6 THEN 1 ELSE 0 END AS low_score
                FROM exam_questions eq
                INNER JOIN questions q ON q.id = eq.question_id
                LEFT JOIN student_answers sa ON sa.exam_id = eq.exam_id AND sa.question_id = eq.question_id
                    AND NOT EXISTS (
                        SELECT 1
                        FROM student_answers pending
                        WHERE pending.exam_id = sa.exam_id
                          AND pending.student_no = sa.student_no
                          AND pending.review_status = '待批改'
                    )
                """);
        List<Object> args = new java.util.ArrayList<>();
        if (className != null && !className.isBlank()) {
            sql.append(" AND sa.class_name = ?");
            args.add(className.trim());
        }
        sql.append("""
                WHERE eq.exam_id = ?
                GROUP BY q.id, eq.sort_no, q.type, eq.score
                ORDER BY average_score ASC, eq.sort_no ASC
                """);
        args.add(examId);
        return jdbcTemplate.queryForList(sql.toString(), args.toArray());
    }

    public Map<String, Object> personalScore(Long examId, String studentNo) {
        List<Map<String, Object>> rows = jdbcTemplate.queryForList("""
                SELECT sc.*, e.total_score AS full_score, e.title AS exam_title, e.subject
                FROM scores sc
                INNER JOIN exams e ON e.id = sc.exam_id
                WHERE sc.exam_id = ? AND sc.student_no = ?
                LIMIT 1
                """, examId, studentNo);
        if (!rows.isEmpty()) {
            return rows.get(0);
        }
        rows = jdbcTemplate.queryForList("""
                SELECT sa.exam_id, sa.student_id, sa.student_no, sa.student_name, sa.class_name,
                       COALESCE(SUM(sa.score), 0) AS total_score,
                       e.total_score AS full_score, e.title AS exam_title, e.subject
                FROM student_answers sa
                INNER JOIN exams e ON e.id = sa.exam_id
                WHERE sa.exam_id = ? AND sa.student_no = ?
                GROUP BY sa.exam_id, sa.student_id, sa.student_no, sa.student_name, sa.class_name,
                         e.total_score, e.title, e.subject
                LIMIT 1
                """, examId, studentNo);
        return rows.isEmpty() ? Map.of() : rows.get(0);
    }

    public Map<String, Object> studentReviewSummary(Long examId, String studentNo) {
        List<Map<String, Object>> rows = jdbcTemplate.queryForList("""
                SELECT COUNT(*) AS answer_count,
                       COALESCE(SUM(CASE WHEN review_status = '待批改' THEN 1 ELSE 0 END), 0) AS pending_count,
                       CASE
                           WHEN COUNT(*) = 0 THEN '暂无提交'
                           WHEN COALESCE(SUM(CASE WHEN review_status = '待批改' THEN 1 ELSE 0 END), 0) = 0 THEN '已批改'
                           WHEN COALESCE(SUM(CASE WHEN review_status = '待批改' THEN 1 ELSE 0 END), 0) = COUNT(*) THEN '待批改'
                           ELSE '批改中'
                       END AS review_status
                FROM student_answers
                WHERE exam_id = ? AND student_no = ?
                """, examId, studentNo);
        return rows.isEmpty() ? Map.of("answer_count", 0, "pending_count", 0, "review_status", "暂无提交") : rows.get(0);
    }

    public List<Map<String, Object>> typeBreakdown(Long examId, String studentNo) {
        return jdbcTemplate.queryForList("""
                SELECT CASE
                           WHEN q.type IN ('单选题', '单选', '选择题') OR LOWER(q.type) IN ('single', 'singlechoice') THEN '单选题'
                           WHEN q.type IN ('多选题', '多选') OR LOWER(q.type) IN ('multiple', 'multiplechoice', 'multi') THEN '多选题'
                           WHEN q.type IN ('判断题', '判断') OR LOWER(q.type) IN ('judge', 'truefalse', 'true/false') THEN '判断题'
                           WHEN q.type IN ('填空题', '填空') OR LOWER(q.type) IN ('blank', 'fill') THEN '填空题'
                           WHEN q.type IN ('编程题', '代码题') OR LOWER(q.type) IN ('program', 'coding', 'code') THEN '编程题'
                           WHEN q.type IN ('高数大题', '高数题', '数学大题') OR LOWER(q.type) = 'math' THEN '编程题'
                           ELSE q.type
                       END AS type,
                       COALESCE(SUM(eq.score), 0) AS full_score,
                       COALESCE(SUM(COALESCE(sa.score, 0)), 0) AS score,
                       GREATEST(COALESCE(SUM(eq.score), 0) - COALESCE(SUM(COALESCE(sa.score, 0)), 0), 0) AS deduction
                FROM exam_questions eq
                INNER JOIN questions q ON q.id = eq.question_id
                LEFT JOIN student_answers sa
                       ON sa.exam_id = eq.exam_id
                      AND sa.question_id = eq.question_id
                      AND sa.student_no = ?
                WHERE eq.exam_id = ?
                GROUP BY CASE
                             WHEN q.type IN ('单选题', '单选', '选择题') OR LOWER(q.type) IN ('single', 'singlechoice') THEN '单选题'
                             WHEN q.type IN ('多选题', '多选') OR LOWER(q.type) IN ('multiple', 'multiplechoice', 'multi') THEN '多选题'
                             WHEN q.type IN ('判断题', '判断') OR LOWER(q.type) IN ('judge', 'truefalse', 'true/false') THEN '判断题'
                             WHEN q.type IN ('填空题', '填空') OR LOWER(q.type) IN ('blank', 'fill') THEN '填空题'
                             WHEN q.type IN ('编程题', '代码题') OR LOWER(q.type) IN ('program', 'coding', 'code') THEN '编程题'
                             WHEN q.type IN ('高数大题', '高数题', '数学大题') OR LOWER(q.type) = 'math' THEN '编程题'
                             ELSE q.type
                         END
                ORDER BY MIN(eq.sort_no)
                """, studentNo, examId);
    }

    public List<Map<String, Object>> weakKnowledgePoints(Long examId, String studentNo) {
        return jdbcTemplate.queryForList("""
                SELECT COALESCE(NULLIF(q.knowledge_point, ''), '未归类知识点') AS name,
                       COALESCE(SUM(eq.score), 0) AS full_score,
                       COALESCE(SUM(COALESCE(sa.score, 0)), 0) AS score,
                       GREATEST(COALESCE(SUM(eq.score), 0) - COALESCE(SUM(COALESCE(sa.score, 0)), 0), 0) AS lost,
                       ROUND(COALESCE(SUM(COALESCE(sa.score, 0)) / NULLIF(SUM(eq.score), 0) * 100, 0), 1) AS mastery
                FROM exam_questions eq
                INNER JOIN questions q ON q.id = eq.question_id
                LEFT JOIN student_answers sa
                       ON sa.exam_id = eq.exam_id
                      AND sa.question_id = eq.question_id
                      AND sa.student_no = ?
                WHERE eq.exam_id = ?
                GROUP BY COALESCE(NULLIF(q.knowledge_point, ''), '未归类知识点')
                HAVING lost > 0
                ORDER BY lost DESC
                LIMIT 8
                """, studentNo, examId);
    }

    public List<Map<String, Object>> personalAnswerDetails(Long examId, String studentNo) {
        return jdbcTemplate.queryForList("""
                SELECT eq.sort_no AS question_index,
                       q.id AS question_id,
                       q.subject,
                       CASE
                           WHEN q.type IN ('单选题', '单选', '选择题') OR LOWER(q.type) IN ('single', 'singlechoice') THEN '单选题'
                           WHEN q.type IN ('多选题', '多选') OR LOWER(q.type) IN ('multiple', 'multiplechoice', 'multi') THEN '多选题'
                           WHEN q.type IN ('判断题', '判断') OR LOWER(q.type) IN ('judge', 'truefalse', 'true/false') THEN '判断题'
                           WHEN q.type IN ('填空题', '填空') OR LOWER(q.type) IN ('blank', 'fill') THEN '填空题'
                           WHEN q.type IN ('编程题', '代码题') OR LOWER(q.type) IN ('program', 'coding', 'code') THEN '编程题'
                           WHEN q.type IN ('高数大题', '高数题', '数学大题') OR LOWER(q.type) = 'math' THEN '编程题'
                           ELSE q.type
                       END AS type,
                       q.content,
                       q.answer AS standard_answer,
                       q.analysis,
                       q.knowledge_point,
                       eq.score AS full_score,
                       sa.id AS answer_id,
                       sa.answer,
                       COALESCE(sa.score, 0) AS score,
                       GREATEST(eq.score - COALESCE(sa.score, 0), 0) AS deduction,
                       sa.review_status,
                       sa.comment
                FROM exam_questions eq
                INNER JOIN questions q ON q.id = eq.question_id
                LEFT JOIN student_answers sa
                       ON sa.exam_id = eq.exam_id
                      AND sa.question_id = eq.question_id
                      AND sa.student_no = ?
                WHERE eq.exam_id = ?
                ORDER BY eq.sort_no, q.id
                """, studentNo, examId);
    }

    public List<Map<String, Object>> wrongQuestions(String studentNo) {
        return jdbcTemplate.queryForList("""
                SELECT sa.id AS answer_id,
                       sa.exam_id,
                       e.title AS exam_title,
                       'exam' AS source_type,
                       q.id AS question_id,
                       q.subject,
                       CASE
                           WHEN q.type IN ('单选题', '单选', '选择题') OR LOWER(q.type) IN ('single', 'singlechoice') THEN '单选题'
                           WHEN q.type IN ('多选题', '多选') OR LOWER(q.type) IN ('multiple', 'multiplechoice', 'multi') THEN '多选题'
                           WHEN q.type IN ('判断题', '判断') OR LOWER(q.type) IN ('judge', 'truefalse', 'true/false') THEN '判断题'
                           WHEN q.type IN ('填空题', '填空') OR LOWER(q.type) IN ('blank', 'fill') THEN '填空题'
                           WHEN q.type IN ('编程题', '代码题') OR LOWER(q.type) IN ('program', 'coding', 'code') THEN '编程题'
                           WHEN q.type IN ('高数大题', '高数题', '数学大题') OR LOWER(q.type) = 'math' THEN '编程题'
                           ELSE q.type
                       END AS type,
                       q.content,
                       q.option_a,
                       q.option_b,
                       q.option_c,
                       q.option_d,
                       q.answer AS standard_answer,
                       q.analysis,
                       q.knowledge_point,
                       q.difficulty,
                       COALESCE(eq.score, q.score, 0) AS full_score,
                       COALESCE(sa.score, 0) AS score,
                       GREATEST(COALESCE(eq.score, q.score, 0) - COALESCE(sa.score, 0), 0) AS deduction,
                       sa.answer AS wrong_answer,
                       sa.comment,
                       sa.review_status,
                       sa.correction_answer,
                       sa.correction_reason,
                       sa.correction_summary,
                       sa.correction_status,
                       sa.corrected_time,
                       sa.created_time
                FROM student_answers sa
                INNER JOIN questions q ON q.id = sa.question_id
                LEFT JOIN exams e ON e.id = sa.exam_id
                LEFT JOIN exam_questions eq ON eq.exam_id = sa.exam_id AND eq.question_id = sa.question_id
                WHERE sa.student_no = ?
                  AND sa.score IS NOT NULL
                  AND COALESCE(sa.score, 0) < COALESCE(eq.score, q.score, 0)
                ORDER BY sa.created_time DESC, sa.id DESC
                """, studentNo);
    }

    private Object[] expandDistributionArgs(Object[] baseArgs) {
        Object[] args = new Object[baseArgs.length * 5];
        for (int i = 0; i < 5; i++) {
            System.arraycopy(baseArgs, 0, args, i * baseArgs.length, baseArgs.length);
        }
        return args;
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
