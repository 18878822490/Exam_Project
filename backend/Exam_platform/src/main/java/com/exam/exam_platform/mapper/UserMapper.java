package com.exam.exam_platform.mapper;

import com.exam.exam_platform.entity.Admin;
import com.exam.exam_platform.entity.Student;
import com.exam.exam_platform.entity.Teacher;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.PreparedStatementCreator;
import org.springframework.jdbc.support.GeneratedKeyHolder;
import org.springframework.jdbc.support.KeyHolder;
import org.springframework.stereotype.Repository;

import java.sql.PreparedStatement;
import java.sql.Statement;
import java.util.List;
import java.util.Map;
import java.util.Objects;

@Repository
public class UserMapper {
    private final JdbcTemplate jdbcTemplate;

    public UserMapper(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public void initSchema() {
        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS exam_classes (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    name VARCHAR(64) NOT NULL UNIQUE,
                    major VARCHAR(64),
                    created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
                    INDEX idx_exam_classes_major (major)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);
        ensureColumn("exam_classes", "major", "VARCHAR(64)");

        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS students (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    username VARCHAR(64) NOT NULL UNIQUE,
                    password VARCHAR(128) NOT NULL,
                    name VARCHAR(64),
                    student_no VARCHAR(64),
                    major VARCHAR(64),
                    class_id BIGINT,
                    class_name VARCHAR(64),
                    created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
                    INDEX idx_students_class (class_id),
                    INDEX idx_students_class_name (class_name),
                    CONSTRAINT fk_students_class FOREIGN KEY (class_id) REFERENCES exam_classes(id)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);
        ensureColumn("students", "student_no", "VARCHAR(64)");
        ensureColumn("students", "major", "VARCHAR(64)");
        ensureColumn("students", "class_name", "VARCHAR(64)");

        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS teachers (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    username VARCHAR(64) NOT NULL UNIQUE,
                    password VARCHAR(128) NOT NULL,
                    name VARCHAR(64),
                    subject VARCHAR(64),
                    phone VARCHAR(64),
                    created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
                    INDEX idx_teachers_subject (subject)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);
        ensureColumn("teachers", "subject", "VARCHAR(64)");
        ensureColumn("teachers", "phone", "VARCHAR(64)");
        ensureColumn("teachers", "email", "VARCHAR(128)");

        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS admins (
                    id BIGINT PRIMARY KEY AUTO_INCREMENT,
                    username VARCHAR(64) NOT NULL UNIQUE,
                    password VARCHAR(128) NOT NULL,
                    name VARCHAR(64),
                    phone VARCHAR(64),
                    created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);
        ensureColumn("admins", "phone", "VARCHAR(64)");

        jdbcTemplate.execute("""
                CREATE TABLE IF NOT EXISTS teacher_classes (
                    teacher_id BIGINT NOT NULL,
                    class_id BIGINT NOT NULL,
                    created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
                    PRIMARY KEY (teacher_id, class_id),
                    INDEX idx_teacher_classes_class (class_id)
                ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
                """);
        dropOldTeacherClassForeignKeys();
    }

    public void ensureDefaultClasses(Map<String, List<String>> classesByMajor) {
        classesByMajor.forEach((major, classNames) -> {
            for (String className : classNames) {
                jdbcTemplate.update("""
                        INSERT INTO exam_classes (name, major)
                        VALUES (?, ?)
                        ON DUPLICATE KEY UPDATE major = VALUES(major)
                        """, className, major);
            }
        });
    }

    public boolean existsByUsername(String username) {
        Integer count = jdbcTemplate.queryForObject("""
                SELECT SUM(total) FROM (
                    SELECT COUNT(*) AS total FROM students WHERE username = ?
                    UNION ALL
                    SELECT COUNT(*) AS total FROM teachers WHERE username = ?
                    UNION ALL
                    SELECT COUNT(*) AS total FROM admins WHERE username = ?
                ) account_counts
                """, Integer.class, username, username, username);
        return count != null && count > 0;
    }

    public boolean existsByStudentNo(String studentNo) {
        Integer count = jdbcTemplate.queryForObject(
                "SELECT COUNT(*) FROM students WHERE student_no = ?",
                Integer.class,
                studentNo
        );
        return count != null && count > 0;
    }

    public boolean existsByStudentNoExceptId(String studentNo, Long id) {
        Integer count = jdbcTemplate.queryForObject(
                "SELECT COUNT(*) FROM students WHERE student_no = ? AND id <> ?",
                Integer.class,
                studentNo,
                id
        );
        return count != null && count > 0;
    }

    public Long insertStudent(Student student) {
        KeyHolder keyHolder = new GeneratedKeyHolder();
        PreparedStatementCreator creator = connection -> {
            PreparedStatement statement = connection.prepareStatement("""
                    INSERT INTO students (username, password, name, student_no, major, class_id, class_name, created_time)
                    VALUES (?, ?, ?, ?, ?, ?, ?, NOW())
                    """, Statement.RETURN_GENERATED_KEYS);
            statement.setString(1, student.getUsername());
            statement.setString(2, student.getPassword());
            statement.setString(3, student.getName());
            statement.setString(4, student.getStudentNo());
            statement.setString(5, student.getMajor());
            statement.setObject(6, student.getClassId());
            statement.setString(7, student.getClassName());
            return statement;
        };
        jdbcTemplate.update(creator, keyHolder);
        Long id = Objects.requireNonNull(keyHolder.getKey()).longValue();
        student.setId(id);
        return id;
    }

    public Long insertTeacher(Teacher teacher) {
        KeyHolder keyHolder = new GeneratedKeyHolder();
        PreparedStatementCreator creator = connection -> {
            PreparedStatement statement = connection.prepareStatement("""
                    INSERT INTO teachers (username, password, name, subject, phone, created_time)
                    VALUES (?, ?, ?, ?, ?, NOW())
                    """, Statement.RETURN_GENERATED_KEYS);
            statement.setString(1, teacher.getUsername());
            statement.setString(2, teacher.getPassword());
            statement.setString(3, teacher.getName());
            statement.setString(4, teacher.getSubject());
            statement.setString(5, teacher.getPhone());
            return statement;
        };
        jdbcTemplate.update(creator, keyHolder);
        Long id = Objects.requireNonNull(keyHolder.getKey()).longValue();
        teacher.setId(id);
        return id;
    }

    public Long insertAdmin(Admin admin) {
        KeyHolder keyHolder = new GeneratedKeyHolder();
        PreparedStatementCreator creator = connection -> {
            PreparedStatement statement = connection.prepareStatement("""
                    INSERT INTO admins (username, password, name, phone, created_time)
                    VALUES (?, ?, ?, ?, NOW())
                    """, Statement.RETURN_GENERATED_KEYS);
            statement.setString(1, admin.getUsername());
            statement.setString(2, admin.getPassword());
            statement.setString(3, admin.getName());
            statement.setString(4, admin.getPhone());
            return statement;
        };
        jdbcTemplate.update(creator, keyHolder);
        Long id = Objects.requireNonNull(keyHolder.getKey()).longValue();
        admin.setId(id);
        return id;
    }

    public AccountRecord findByUsernameAndPassword(String username, String password) {
        List<AccountRecord> accounts = jdbcTemplate.query("""
                SELECT id, username, 'STUDENT' AS role, name, student_no, class_id, class_name, major, NULL AS subject
                FROM students
                WHERE username = ? AND password = ?
                UNION ALL
                SELECT id, username, 'TEACHER' AS role, name, NULL AS student_no, NULL AS class_id, NULL AS class_name, NULL AS major, subject
                FROM teachers
                WHERE username = ? AND password = ?
                UNION ALL
                SELECT id, username, 'ADMIN' AS role, name, NULL AS student_no, NULL AS class_id, NULL AS class_name, NULL AS major, NULL AS subject
                FROM admins
                WHERE username = ? AND password = ?
                LIMIT 1
                """, (rs, rowNum) -> new AccountRecord(
                        rs.getLong("id"),
                        rs.getString("username"),
                        rs.getString("role"),
                        rs.getString("name"),
                        rs.getString("student_no"),
                        readNullableLong(rs, "class_id"),
                        rs.getString("class_name"),
                        rs.getString("major"),
                        rs.getString("subject")
                ), username, password, username, password, username, password);
        return accounts.isEmpty() ? null : accounts.get(0);
    }

    public Long findClassIdByName(String className) {
        List<Long> ids = jdbcTemplate.query(
                "SELECT id FROM exam_classes WHERE name = ? LIMIT 1",
                (rs, rowNum) -> rs.getLong("id"),
                className
        );
        return ids.isEmpty() ? null : ids.get(0);
    }

    public Long insertClass(String className, String major) {
        KeyHolder keyHolder = new GeneratedKeyHolder();
        jdbcTemplate.update(connection -> {
            PreparedStatement statement = connection.prepareStatement(
                    "INSERT INTO exam_classes (name, major) VALUES (?, ?)",
                    Statement.RETURN_GENERATED_KEYS
            );
            statement.setString(1, className);
            statement.setString(2, major);
            return statement;
        }, keyHolder);
        return Objects.requireNonNull(keyHolder.getKey()).longValue();
    }

    public String findClassNameById(Long classId) {
        if (classId == null) {
            return null;
        }
        List<String> names = jdbcTemplate.query(
                "SELECT name FROM exam_classes WHERE id = ? LIMIT 1",
                (rs, rowNum) -> rs.getString("name"),
                classId
        );
        return names.isEmpty() ? null : names.get(0);
    }

    public String findClassMajorByName(String className) {
        List<String> majors = jdbcTemplate.query(
                "SELECT major FROM exam_classes WHERE name = ? LIMIT 1",
                (rs, rowNum) -> rs.getString("major"),
                className
        );
        return majors.isEmpty() ? null : majors.get(0);
    }

    public void bindTeacherClass(Long teacherId, Long classId) {
        jdbcTemplate.update(
                "INSERT IGNORE INTO teacher_classes (teacher_id, class_id) VALUES (?, ?)",
                teacherId,
                classId
        );
    }

    public List<String> findTeacherClassNames(Long teacherId) {
        return jdbcTemplate.query("""
                SELECT c.name
                FROM exam_classes c
                INNER JOIN teacher_classes tc ON tc.class_id = c.id
                WHERE tc.teacher_id = ?
                ORDER BY c.id
                """, (rs, rowNum) -> rs.getString("name"), teacherId);
    }

    public List<String> listClassNames() {
        return jdbcTemplate.query(
                "SELECT name FROM exam_classes ORDER BY id",
                (rs, rowNum) -> rs.getString("name")
        );
    }

    public List<Map<String, Object>> listTeacherClasses(Long teacherId) {
        if (teacherId == null) {
            return jdbcTemplate.queryForList("""
                    SELECT c.id, c.name, c.major, COUNT(s.id) AS student_count
                    FROM exam_classes c
                    LEFT JOIN students s ON s.class_id = c.id
                    GROUP BY c.id, c.name, c.major
                    ORDER BY c.id
                    """);
        }
        return jdbcTemplate.queryForList("""
                SELECT c.id, c.name, c.major, COUNT(s.id) AS student_count
                FROM exam_classes c
                INNER JOIN teacher_classes tc ON tc.class_id = c.id
                LEFT JOIN students s ON s.class_id = c.id
                WHERE tc.teacher_id = ?
                GROUP BY c.id, c.name, c.major
                ORDER BY c.id
                """, teacherId);
    }

    public List<Map<String, Object>> listStudentsByClassName(String className) {
        return jdbcTemplate.queryForList("""
                SELECT id, username, student_no, name, major, class_name
                FROM students
                WHERE class_name = ?
                ORDER BY id
                """, className);
    }

    public List<Map<String, Object>> listStudentsForAdmin(String keyword, String className, Integer limit) {
        StringBuilder sql = new StringBuilder("""
                SELECT s.id, s.username, s.student_no, s.name, s.major, s.class_id, s.class_name, s.created_time,
                       (SELECT COUNT(DISTINCT sc.exam_id)
                        FROM scores sc
                        WHERE sc.student_no = s.student_no) AS exam_count,
                       (SELECT COALESCE(AVG(sc.total_score), 0)
                        FROM scores sc
                        WHERE sc.student_no = s.student_no) AS average_score,
                       (SELECT COUNT(DISTINCT ep.exam_id)
                        FROM exam_publish ep
                        INNER JOIN exams e ON e.id = ep.exam_id
                        WHERE ep.class_name = s.class_name
                          AND COALESCE(ep.end_time, e.end_time) < NOW()
                          AND NOT EXISTS (
                              SELECT 1 FROM scores sc
                              WHERE sc.exam_id = ep.exam_id AND sc.student_no = s.student_no
                          )) AS absent_count
                FROM students s
                WHERE 1=1
                """);
        java.util.List<Object> args = new java.util.ArrayList<>();
        if (keyword != null && !keyword.isBlank()) {
            sql.append("""
                    AND (
                        s.username LIKE ?
                        OR s.name LIKE ?
                        OR s.student_no LIKE ?
                        OR s.major LIKE ?
                        OR s.class_name LIKE ?
                    )
                    """);
            String like = "%" + keyword.trim() + "%";
            args.add(like);
            args.add(like);
            args.add(like);
            args.add(like);
            args.add(like);
        }
        if (className != null && !className.isBlank()) {
            sql.append(" AND s.class_name = ?");
            args.add(className.trim());
        }
        sql.append(" ORDER BY s.created_time DESC, s.id DESC LIMIT ?");
        args.add(Math.max(1, Math.min(limit == null ? 200 : limit, 500)));
        return jdbcTemplate.queryForList(sql.toString(), args.toArray());
    }

    public Map<String, Object> studentAdminStats() {
        Map<String, Object> stats = new java.util.LinkedHashMap<>();
        Map<String, Object> studentCounts = jdbcTemplate.queryForMap("""
                SELECT COUNT(*) AS total_count,
                       COALESCE(SUM(CASE WHEN DATE(created_time) = CURDATE() THEN 1 ELSE 0 END), 0) AS today_new
                FROM students
                """);
        Integer scoredStudents = jdbcTemplate.queryForObject(
                "SELECT COUNT(DISTINCT student_no) FROM scores",
                Integer.class
        );
        Number total = (Number) studentCounts.getOrDefault("total_count", 0);
        int totalCount = total == null ? 0 : total.intValue();
        int referenced = scoredStudents == null ? 0 : scoredStudents;
        int referenceRate = totalCount == 0 ? 0 : Math.round(referenced * 100f / totalCount);
        stats.put("total_count", totalCount);
        stats.put("today_new", ((Number) studentCounts.getOrDefault("today_new", 0)).intValue());
        stats.put("pending_review", 0);
        stats.put("reference_rate", referenceRate + "%");
        return stats;
    }

    public List<Map<String, Object>> listTeachersForAdmin(String keyword, Integer limit) {
        StringBuilder sql = new StringBuilder("""
                SELECT t.id, t.username, t.name, t.subject, t.phone, t.email, t.created_time,
                       COALESCE(GROUP_CONCAT(DISTINCT c.name ORDER BY c.id SEPARATOR '、'), '') AS class_names,
                       COUNT(DISTINCT e.id) AS exam_count,
                       COALESCE(SUM(CASE WHEN sa.review_status = '待批改' THEN 1 ELSE 0 END), 0) AS pending_review_count
                FROM teachers t
                LEFT JOIN teacher_classes tc ON tc.teacher_id = t.id
                LEFT JOIN exam_classes c ON c.id = tc.class_id
                LEFT JOIN exams e ON e.created_by = t.id
                LEFT JOIN student_answers sa ON sa.exam_id = e.id
                WHERE 1=1
                """);
        java.util.List<Object> args = new java.util.ArrayList<>();
        if (keyword != null && !keyword.isBlank()) {
            sql.append("""
                    AND (
                        t.username LIKE ?
                        OR t.name LIKE ?
                        OR t.subject LIKE ?
                        OR t.phone LIKE ?
                    )
                    """);
            String like = "%" + keyword.trim() + "%";
            args.add(like);
            args.add(like);
            args.add(like);
            args.add(like);
        }
        sql.append("""
                GROUP BY t.id, t.username, t.name, t.subject, t.phone, t.email, t.created_time
                ORDER BY t.created_time DESC, t.id DESC
                LIMIT ?
                """);
        args.add(Math.max(1, Math.min(limit == null ? 200 : limit, 500)));
        return jdbcTemplate.queryForList(sql.toString(), args.toArray());
    }

    public Map<String, Object> teacherAdminStats() {
        Map<String, Object> stats = new java.util.LinkedHashMap<>();
        Map<String, Object> teacherCounts = jdbcTemplate.queryForMap("""
                SELECT COUNT(*) AS total_count,
                       COALESCE(SUM(CASE WHEN DATE(created_time) = CURDATE() THEN 1 ELSE 0 END), 0) AS today_new
                FROM teachers
                """);
        Integer teachersWithExam = jdbcTemplate.queryForObject(
                "SELECT COUNT(DISTINCT created_by) FROM exams WHERE created_by IS NOT NULL",
                Integer.class
        );
        int totalCount = ((Number) teacherCounts.getOrDefault("total_count", 0)).intValue();
        int activeCount = teachersWithExam == null ? 0 : teachersWithExam;
        int activeRate = totalCount == 0 ? 0 : Math.round(activeCount * 100f / totalCount);
        stats.put("total_count", totalCount);
        stats.put("today_new", ((Number) teacherCounts.getOrDefault("today_new", 0)).intValue());
        stats.put("pending_review", 0);
        stats.put("active_rate", activeRate + "%");
        return stats;
    }

    public Map<String, Object> findTeacherById(Long teacherId) {
        List<Map<String, Object>> rows = jdbcTemplate.queryForList("""
                SELECT t.id, t.username, t.name, t.subject, t.phone, t.email, t.created_time,
                       COALESCE(GROUP_CONCAT(c.name ORDER BY c.id SEPARATOR '、'), '') AS class_names
                FROM teachers t
                LEFT JOIN teacher_classes tc ON tc.teacher_id = t.id
                LEFT JOIN exam_classes c ON c.id = tc.class_id
                WHERE t.id = ?
                GROUP BY t.id, t.username, t.name, t.subject, t.phone, t.created_time
                LIMIT 1
                """, teacherId);
        return rows.isEmpty() ? null : rows.get(0);
    }

    public Map<String, Object> findStudentById(Long studentId) {
        List<Map<String, Object>> rows = jdbcTemplate.queryForList("""
                SELECT id, username, name, student_no, major, class_id, class_name, created_time
                FROM students
                WHERE id = ?
                LIMIT 1
                """, studentId);
        return rows.isEmpty() ? null : rows.get(0);
    }

    public boolean updateStudentProfile(Long id, String name, String studentNo, String major, Long classId, String className) {
        return jdbcTemplate.update("""
                UPDATE students
                SET name = ?, student_no = ?, major = ?, class_id = ?, class_name = ?
                WHERE id = ?
                """, name, studentNo, major, classId, className, id) > 0;
    }

    public boolean updateTeacherProfile(Long id, String name, String subject, String phone, String email) {
        return jdbcTemplate.update("""
                UPDATE teachers
                SET name = ?, subject = ?, phone = ?, email = ?
                WHERE id = ?
                """, name, subject, phone, email, id) > 0;
    }

    public boolean updatePassword(String tableName, Long id, String oldPassword, String newPassword) {
        return jdbcTemplate.update(
                "UPDATE " + tableName + " SET password = ? WHERE id = ? AND password = ?",
                newPassword,
                id,
                oldPassword
        ) > 0;
    }

    private Long readNullableLong(java.sql.ResultSet rs, String column) throws java.sql.SQLException {
        long value = rs.getLong(column);
        return rs.wasNull() ? null : value;
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

    private void dropOldTeacherClassForeignKeys() {
        List<String> constraintNames = jdbcTemplate.query("""
                SELECT CONSTRAINT_NAME
                FROM information_schema.KEY_COLUMN_USAGE
                WHERE table_schema = DATABASE()
                  AND table_name = 'teacher_classes'
                  AND referenced_table_name = 'users'
        """, (rs, rowNum) -> rs.getString("CONSTRAINT_NAME"));
        for (String constraintName : constraintNames) {
            String escaped = constraintName.replace("`", "``");
            jdbcTemplate.execute("ALTER TABLE teacher_classes DROP FOREIGN KEY `" + escaped + "`");
        }
    }

    public record AccountRecord(Long id,
                                String username,
                                String role,
                                String name,
                                String studentNo,
                                Long classId,
                                String className,
                                String major,
                                String subject) {
    }
}
