CREATE DATABASE IF NOT EXISTS exam_system
  CHARACTER SET utf8mb4
  COLLATE utf8mb4_unicode_ci;

USE exam_system;

CREATE TABLE IF NOT EXISTS exam_classes (
  id BIGINT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(64) NOT NULL UNIQUE,
  created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS users (
  id BIGINT PRIMARY KEY AUTO_INCREMENT,
  username VARCHAR(64) NOT NULL UNIQUE,
  password VARCHAR(128) NOT NULL,
  role VARCHAR(20) NOT NULL,
  name VARCHAR(64),
  class_id BIGINT,
  teacher_id BIGINT,
  subject VARCHAR(64),
  theme VARCHAR(32),
  created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  INDEX idx_users_role (role),
  INDEX idx_users_class (class_id),
  INDEX idx_users_teacher (teacher_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS teacher_classes (
  teacher_id BIGINT NOT NULL,
  class_id BIGINT NOT NULL,
  created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (teacher_id, class_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS subjects (
  id BIGINT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(64) NOT NULL UNIQUE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS questions (
  id BIGINT PRIMARY KEY AUTO_INCREMENT,
  subject VARCHAR(64) NOT NULL,
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
  INDEX idx_questions_subject_type (subject, type)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS exam_papers (
  id BIGINT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(128) NOT NULL,
  subject VARCHAR(64) NOT NULL,
  start_time DATETIME,
  end_time DATETIME,
  total_score INT NOT NULL DEFAULT 0,
  status VARCHAR(32) NOT NULL DEFAULT '草稿',
  created_by BIGINT,
  created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  INDEX idx_exam_papers_status (status)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS exam_paper_questions (
  paper_id BIGINT NOT NULL,
  question_id BIGINT NOT NULL,
  score INT NOT NULL,
  sort_no INT NOT NULL DEFAULT 0,
  PRIMARY KEY (paper_id, question_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS exam_publishes (
  id BIGINT PRIMARY KEY AUTO_INCREMENT,
  paper_id BIGINT NOT NULL,
  class_name VARCHAR(64) NOT NULL,
  start_time DATETIME,
  end_time DATETIME,
  status VARCHAR(32) NOT NULL DEFAULT '已发布',
  created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  INDEX idx_exam_publishes_paper (paper_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS student_answers (
  id BIGINT PRIMARY KEY AUTO_INCREMENT,
  paper_id BIGINT NOT NULL,
  student_name VARCHAR(64) NOT NULL,
  student_no VARCHAR(32) NOT NULL,
  question_id BIGINT,
  answer TEXT,
  score DECIMAL(6,2),
  review_status VARCHAR(32) NOT NULL DEFAULT '待批改',
  comment TEXT,
  created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  INDEX idx_student_answers_status (review_status)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS scores (
  id BIGINT PRIMARY KEY AUTO_INCREMENT,
  paper_id BIGINT NOT NULL,
  student_no VARCHAR(32) NOT NULL,
  total_score DECIMAL(6,2) NOT NULL,
  class_name VARCHAR(64) NOT NULL,
  created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  INDEX idx_scores_paper_class (paper_id, class_name)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

INSERT IGNORE INTO exam_classes(name) VALUES
('软件工程2501班'),
('软件工程2502班'),
('计算机科学与技术2501班'),
('信息网络2501班'),
('大数据2501班');

INSERT IGNORE INTO subjects(name) VALUES
('Java'), ('C++'), ('高数'), ('数据结构'), ('数据库');

INSERT IGNORE INTO users(username, password, role, name, subject) VALUES
('teacher_math', '123456', 'TEACHER', '高数老师', '高数'),
('teacher_java', '123456', 'TEACHER', 'Java老师', 'Java'),
('teacher_cpp', '123456', 'TEACHER', 'C++老师', 'C++');

INSERT IGNORE INTO teacher_classes(teacher_id, class_id)
SELECT u.id, c.id FROM users u JOIN exam_classes c
WHERE u.username = 'teacher_java'
  AND c.name IN ('软件工程2501班', '软件工程2502班', '计算机科学与技术2501班');

DROP PROCEDURE IF EXISTS seed_exam_students;
DELIMITER //
CREATE PROCEDURE seed_exam_students()
BEGIN
  DECLARE i INT DEFAULT 1;
  DECLARE class2501 BIGINT DEFAULT 0;
  DECLARE class2502 BIGINT DEFAULT 0;
  DECLARE teacherJava BIGINT DEFAULT 0;

  SELECT id INTO class2501 FROM exam_classes WHERE name = '软件工程2501班' LIMIT 1;
  SELECT id INTO class2502 FROM exam_classes WHERE name = '软件工程2502班' LIMIT 1;
  SELECT id INTO teacherJava FROM users WHERE username = 'teacher_java' LIMIT 1;

  WHILE i <= 28 DO
    INSERT IGNORE INTO users(username, password, role, name, class_id, teacher_id)
    VALUES (
      CONCAT('student_251', LPAD(i, 3, '0')),
      '123456',
      'STUDENT',
      CONCAT('软件2501学生', LPAD(i, 2, '0')),
      class2501,
      teacherJava
    );

    INSERT IGNORE INTO users(username, password, role, name, class_id, teacher_id)
    VALUES (
      CONCAT('student_252', LPAD(i, 3, '0')),
      '123456',
      'STUDENT',
      CONCAT('软件2502学生', LPAD(i, 2, '0')),
      class2502,
      teacherJava
    );

    SET i = i + 1;
  END WHILE;
END//
DELIMITER ;

CALL seed_exam_students();
DROP PROCEDURE IF EXISTS seed_exam_students;

INSERT IGNORE INTO questions(subject, type, content, answer, score, difficulty) VALUES
('Java', '单选题', 'Java虚拟机的缩写是？', 'JVM', 3, '基础'),
('Java', '多选题', '以下属于Java集合框架的是？', 'List;Map;Set', 5, '基础'),
('Java', '填空题', 'Java源文件扩展名是____。', '.java', 2, '基础'),
('高数', '高数大题', '求函数f(x)=x^2在[0,2]上的定积分。', '8/3', 10, '中等'),
('C++', '代码题', '编写函数判断一个整数是否为素数。', 'trial division', 15, '中等'),
('Java', '单选题', 'String是否不可变？', '是', 3, '基础'),
('Java', '代码题', '使用Java实现冒泡排序。', 'bubble sort', 15, '中等');

INSERT INTO exam_papers(name, subject, start_time, end_time, total_score, status)
SELECT 'Java期末考试', 'Java', '2026-06-20 09:00:00', '2026-06-20 11:00:00', 0, '草稿'
WHERE NOT EXISTS (SELECT 1 FROM exam_papers WHERE name = 'Java期末考试');

UPDATE exam_papers p
SET total_score = (
  SELECT COALESCE(SUM(q.score), 0)
  FROM questions q
  WHERE q.subject = 'Java'
    AND q.type IN ('单选题', '多选题', '填空题', '代码题')
)
WHERE p.name = 'Java期末考试';

SET @paper_sort_no := 0;
INSERT IGNORE INTO exam_paper_questions(paper_id, question_id, score, sort_no)
SELECT p.id, q.id, q.score, (@paper_sort_no := @paper_sort_no + 1)
FROM exam_papers p
JOIN questions q ON q.subject = p.subject
WHERE p.name = 'Java期末考试'
  AND q.type IN ('单选题', '多选题', '填空题', '代码题');

INSERT INTO exam_publishes(paper_id, class_name, start_time, end_time, status)
SELECT p.id, '软件工程2501班', '2026-06-20 09:00:00', '2026-06-20 11:00:00', '已发布'
FROM exam_papers p
WHERE p.name = 'Java期末考试'
  AND NOT EXISTS (
    SELECT 1 FROM exam_publishes ep
    WHERE ep.paper_id = p.id AND ep.class_name = '软件工程2501班'
  );

UPDATE exam_papers SET status = '已发布' WHERE name = 'Java期末考试';
