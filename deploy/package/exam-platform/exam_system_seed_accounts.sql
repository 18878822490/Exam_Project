USE exam_system;
SET NAMES utf8mb4;

START TRANSACTION;

INSERT INTO exam_classes (name, major)
VALUES
    ('软工01', '软件工程'),
    ('软工02', '软件工程'),
    ('软工03', '软件工程'),
    ('计科01', '计算机科学与技术'),
    ('信网01', '信息网络'),
    ('大数据01班', '大数据')
ON DUPLICATE KEY UPDATE
    major = VALUES(major);

INSERT INTO teachers (username, password, name, subject, phone)
VALUES
    ('teacher_java', '123456', 'Java老师', 'Java', '13800001001'),
    ('teacher_database', '123456', '数据库老师', '数据库', '13800001002'),
    ('teacher_cpp', '123456', 'C++老师', 'C++', '13800001003'),
    ('teacher_math', '123456', '高数老师', '高数', '13800001004'),
    ('teacher_datastructure', '123456', '数据结构老师', '数据结构', '13800001005'),
    ('teacher_os', '123456', '操作系统老师', '操作系统', '13800001006'),
    ('teacher_network', '123456', '计算机网络老师', '计算机网络', '13800001007'),
    ('teacher_web', '123456', 'Web前端老师', 'Web前端', '13800001008'),
    ('teacher_python', '123456', 'Python老师', 'Python', '13800001009'),
    ('teacher_ai', '123456', '人工智能老师', '人工智能', '13800001010'),
    ('teacher_bigdata', '123456', '大数据老师', '大数据', '13800001011'),
    ('teacher_english', '123456', '英语老师', '英语', '13800001012')
ON DUPLICATE KEY UPDATE
    password = VALUES(password),
    name = VALUES(name),
    subject = VALUES(subject),
    phone = VALUES(phone);

INSERT INTO admins (username, password, name, phone)
VALUES
    ('admin_root', '123456', '系统管理员', '13900002001'),
    ('admin_exam', '123456', '考务管理员', '13900002002'),
    ('admin_data', '123456', '数据管理员', '13900002003')
ON DUPLICATE KEY UPDATE
    password = VALUES(password),
    name = VALUES(name),
    phone = VALUES(phone);

INSERT INTO students (username, password, name, student_no, major, class_id, class_name)
SELECT
    CONCAT('stu_se01_', LPAD(seq.n, 2, '0')),
    '123456',
    CONCAT('软工01学生', LPAD(seq.n, 2, '0')),
    CONCAT('SE01', LPAD(seq.n, 3, '0')),
    '软件工程',
    c.id,
    c.name
FROM exam_classes c
JOIN (
    SELECT 1 n UNION ALL SELECT 2 UNION ALL SELECT 3 UNION ALL SELECT 4 UNION ALL SELECT 5 UNION ALL SELECT 6 UNION ALL SELECT 7
    UNION ALL SELECT 8 UNION ALL SELECT 9 UNION ALL SELECT 10 UNION ALL SELECT 11 UNION ALL SELECT 12 UNION ALL SELECT 13 UNION ALL SELECT 14
    UNION ALL SELECT 15 UNION ALL SELECT 16 UNION ALL SELECT 17 UNION ALL SELECT 18 UNION ALL SELECT 19 UNION ALL SELECT 20 UNION ALL SELECT 21
    UNION ALL SELECT 22 UNION ALL SELECT 23 UNION ALL SELECT 24 UNION ALL SELECT 25 UNION ALL SELECT 26 UNION ALL SELECT 27 UNION ALL SELECT 28
) seq
WHERE c.name = '软工01'
ON DUPLICATE KEY UPDATE
    password = VALUES(password),
    name = VALUES(name),
    student_no = VALUES(student_no),
    major = VALUES(major),
    class_id = VALUES(class_id),
    class_name = VALUES(class_name);

INSERT INTO students (username, password, name, student_no, major, class_id, class_name)
SELECT
    CONCAT('stu_se02_', LPAD(seq.n, 2, '0')),
    '123456',
    CONCAT('软工02学生', LPAD(seq.n, 2, '0')),
    CONCAT('SE02', LPAD(seq.n, 3, '0')),
    '软件工程',
    c.id,
    c.name
FROM exam_classes c
JOIN (
    SELECT 1 n UNION ALL SELECT 2 UNION ALL SELECT 3 UNION ALL SELECT 4 UNION ALL SELECT 5 UNION ALL SELECT 6 UNION ALL SELECT 7
    UNION ALL SELECT 8 UNION ALL SELECT 9 UNION ALL SELECT 10 UNION ALL SELECT 11 UNION ALL SELECT 12 UNION ALL SELECT 13 UNION ALL SELECT 14
    UNION ALL SELECT 15 UNION ALL SELECT 16 UNION ALL SELECT 17 UNION ALL SELECT 18 UNION ALL SELECT 19 UNION ALL SELECT 20 UNION ALL SELECT 21
    UNION ALL SELECT 22 UNION ALL SELECT 23 UNION ALL SELECT 24 UNION ALL SELECT 25 UNION ALL SELECT 26 UNION ALL SELECT 27 UNION ALL SELECT 28
) seq
WHERE c.name = '软工02'
ON DUPLICATE KEY UPDATE
    password = VALUES(password),
    name = VALUES(name),
    student_no = VALUES(student_no),
    major = VALUES(major),
    class_id = VALUES(class_id),
    class_name = VALUES(class_name);

INSERT INTO students (username, password, name, student_no, major, class_id, class_name)
SELECT
    CONCAT('stu_se03_', LPAD(seq.n, 2, '0')),
    '123456',
    CONCAT('软工03学生', LPAD(seq.n, 2, '0')),
    CONCAT('SE03', LPAD(seq.n, 3, '0')),
    '软件工程',
    c.id,
    c.name
FROM exam_classes c
JOIN (
    SELECT 1 n UNION ALL SELECT 2 UNION ALL SELECT 3 UNION ALL SELECT 4 UNION ALL SELECT 5 UNION ALL SELECT 6 UNION ALL SELECT 7
    UNION ALL SELECT 8 UNION ALL SELECT 9 UNION ALL SELECT 10 UNION ALL SELECT 11 UNION ALL SELECT 12 UNION ALL SELECT 13 UNION ALL SELECT 14
    UNION ALL SELECT 15 UNION ALL SELECT 16 UNION ALL SELECT 17 UNION ALL SELECT 18 UNION ALL SELECT 19 UNION ALL SELECT 20 UNION ALL SELECT 21
    UNION ALL SELECT 22 UNION ALL SELECT 23 UNION ALL SELECT 24 UNION ALL SELECT 25 UNION ALL SELECT 26 UNION ALL SELECT 27 UNION ALL SELECT 28
) seq
WHERE c.name = '软工03'
ON DUPLICATE KEY UPDATE
    password = VALUES(password),
    name = VALUES(name),
    student_no = VALUES(student_no),
    major = VALUES(major),
    class_id = VALUES(class_id),
    class_name = VALUES(class_name);

INSERT INTO students (username, password, name, student_no, major, class_id, class_name)
SELECT
    CONCAT('stu_cs01_', LPAD(seq.n, 2, '0')),
    '123456',
    CONCAT('计科01学生', LPAD(seq.n, 2, '0')),
    CONCAT('CS01', LPAD(seq.n, 3, '0')),
    '计算机科学与技术',
    c.id,
    c.name
FROM exam_classes c
JOIN (
    SELECT 1 n UNION ALL SELECT 2 UNION ALL SELECT 3 UNION ALL SELECT 4 UNION ALL SELECT 5 UNION ALL SELECT 6 UNION ALL SELECT 7
    UNION ALL SELECT 8 UNION ALL SELECT 9 UNION ALL SELECT 10 UNION ALL SELECT 11 UNION ALL SELECT 12 UNION ALL SELECT 13 UNION ALL SELECT 14
    UNION ALL SELECT 15 UNION ALL SELECT 16 UNION ALL SELECT 17 UNION ALL SELECT 18 UNION ALL SELECT 19 UNION ALL SELECT 20 UNION ALL SELECT 21
    UNION ALL SELECT 22 UNION ALL SELECT 23 UNION ALL SELECT 24 UNION ALL SELECT 25 UNION ALL SELECT 26 UNION ALL SELECT 27 UNION ALL SELECT 28
) seq
WHERE c.name = '计科01'
ON DUPLICATE KEY UPDATE
    password = VALUES(password),
    name = VALUES(name),
    student_no = VALUES(student_no),
    major = VALUES(major),
    class_id = VALUES(class_id),
    class_name = VALUES(class_name);

INSERT INTO students (username, password, name, student_no, major, class_id, class_name)
SELECT
    CONCAT('stu_nw01_', LPAD(seq.n, 2, '0')),
    '123456',
    CONCAT('信网01学生', LPAD(seq.n, 2, '0')),
    CONCAT('NW01', LPAD(seq.n, 3, '0')),
    '信息网络',
    c.id,
    c.name
FROM exam_classes c
JOIN (
    SELECT 1 n UNION ALL SELECT 2 UNION ALL SELECT 3 UNION ALL SELECT 4 UNION ALL SELECT 5 UNION ALL SELECT 6 UNION ALL SELECT 7
    UNION ALL SELECT 8 UNION ALL SELECT 9 UNION ALL SELECT 10 UNION ALL SELECT 11 UNION ALL SELECT 12 UNION ALL SELECT 13 UNION ALL SELECT 14
    UNION ALL SELECT 15 UNION ALL SELECT 16 UNION ALL SELECT 17 UNION ALL SELECT 18 UNION ALL SELECT 19 UNION ALL SELECT 20 UNION ALL SELECT 21
    UNION ALL SELECT 22 UNION ALL SELECT 23 UNION ALL SELECT 24 UNION ALL SELECT 25 UNION ALL SELECT 26 UNION ALL SELECT 27 UNION ALL SELECT 28
) seq
WHERE c.name = '信网01'
ON DUPLICATE KEY UPDATE
    password = VALUES(password),
    name = VALUES(name),
    student_no = VALUES(student_no),
    major = VALUES(major),
    class_id = VALUES(class_id),
    class_name = VALUES(class_name);

INSERT INTO students (username, password, name, student_no, major, class_id, class_name)
SELECT
    CONCAT('stu_bd01_', LPAD(seq.n, 2, '0')),
    '123456',
    CONCAT('大数据01班学生', LPAD(seq.n, 2, '0')),
    CONCAT('BD01', LPAD(seq.n, 3, '0')),
    '大数据',
    c.id,
    c.name
FROM exam_classes c
JOIN (
    SELECT 1 n UNION ALL SELECT 2 UNION ALL SELECT 3 UNION ALL SELECT 4 UNION ALL SELECT 5 UNION ALL SELECT 6 UNION ALL SELECT 7
    UNION ALL SELECT 8 UNION ALL SELECT 9 UNION ALL SELECT 10 UNION ALL SELECT 11 UNION ALL SELECT 12 UNION ALL SELECT 13 UNION ALL SELECT 14
    UNION ALL SELECT 15 UNION ALL SELECT 16 UNION ALL SELECT 17 UNION ALL SELECT 18 UNION ALL SELECT 19 UNION ALL SELECT 20 UNION ALL SELECT 21
    UNION ALL SELECT 22 UNION ALL SELECT 23 UNION ALL SELECT 24 UNION ALL SELECT 25 UNION ALL SELECT 26 UNION ALL SELECT 27 UNION ALL SELECT 28
) seq
WHERE c.name = '大数据01班'
ON DUPLICATE KEY UPDATE
    password = VALUES(password),
    name = VALUES(name),
    student_no = VALUES(student_no),
    major = VALUES(major),
    class_id = VALUES(class_id),
    class_name = VALUES(class_name);

INSERT IGNORE INTO teacher_classes (teacher_id, class_id)
SELECT t.id, c.id FROM teachers t JOIN exam_classes c
WHERE t.username = 'teacher_java' AND c.name IN ('软工01', '软工02', '软工03', '计科01');

INSERT IGNORE INTO teacher_classes (teacher_id, class_id)
SELECT t.id, c.id FROM teachers t JOIN exam_classes c
WHERE t.username = 'teacher_database' AND c.name IN ('软工01', '软工02', '计科01', '大数据01班');

INSERT IGNORE INTO teacher_classes (teacher_id, class_id)
SELECT t.id, c.id FROM teachers t JOIN exam_classes c
WHERE t.username = 'teacher_cpp' AND c.name IN ('软工02', '软工03', '计科01');

INSERT IGNORE INTO teacher_classes (teacher_id, class_id)
SELECT t.id, c.id FROM teachers t JOIN exam_classes c
WHERE t.username = 'teacher_math' AND c.name IN ('软工01', '软工02', '软工03', '计科01', '信网01', '大数据01班');

INSERT IGNORE INTO teacher_classes (teacher_id, class_id)
SELECT t.id, c.id FROM teachers t JOIN exam_classes c
WHERE t.username = 'teacher_datastructure' AND c.name IN ('软工01', '软工02', '软工03', '计科01');

INSERT IGNORE INTO teacher_classes (teacher_id, class_id)
SELECT t.id, c.id FROM teachers t JOIN exam_classes c
WHERE t.username = 'teacher_os' AND c.name IN ('软工03', '计科01');

INSERT IGNORE INTO teacher_classes (teacher_id, class_id)
SELECT t.id, c.id FROM teachers t JOIN exam_classes c
WHERE t.username = 'teacher_network' AND c.name IN ('计科01', '信网01');

INSERT IGNORE INTO teacher_classes (teacher_id, class_id)
SELECT t.id, c.id FROM teachers t JOIN exam_classes c
WHERE t.username = 'teacher_web' AND c.name IN ('软工01', '软工02', '信网01');

INSERT IGNORE INTO teacher_classes (teacher_id, class_id)
SELECT t.id, c.id FROM teachers t JOIN exam_classes c
WHERE t.username = 'teacher_python' AND c.name IN ('软工03', '大数据01班');

INSERT IGNORE INTO teacher_classes (teacher_id, class_id)
SELECT t.id, c.id FROM teachers t JOIN exam_classes c
WHERE t.username = 'teacher_ai' AND c.name IN ('计科01', '大数据01班');

INSERT IGNORE INTO teacher_classes (teacher_id, class_id)
SELECT t.id, c.id FROM teachers t JOIN exam_classes c
WHERE t.username = 'teacher_bigdata' AND c.name IN ('软工02', '大数据01班');

INSERT IGNORE INTO teacher_classes (teacher_id, class_id)
SELECT t.id, c.id FROM teachers t JOIN exam_classes c
WHERE t.username = 'teacher_english' AND c.name IN ('软工01', '软工02', '软工03', '计科01', '信网01', '大数据01班');

COMMIT;

SELECT '班级数' AS item, COUNT(*) AS total FROM exam_classes
UNION ALL SELECT '学生数', COUNT(*) FROM students
UNION ALL SELECT '教师数', COUNT(*) FROM teachers
UNION ALL SELECT '管理员数', COUNT(*) FROM admins
UNION ALL SELECT '教师班级关系数', COUNT(*) FROM teacher_classes;
