#include "TeacherDataRepository.h"

#include "AppConfig.h"

#include <QDateTime>
#include <QEventLoop>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSet>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTextStream>
#include <QTimer>
#include <QUrl>
#include <QUrlQuery>

namespace {
QString mysqlDateTime(const QDateTime &value)
{
    return value.isValid()
            ? value.toString(QStringLiteral("yyyy-MM-dd HH:mm:ss"))
            : QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd HH:mm:ss"));
}

QString variantString(const QVariant &value, const QString &fallback = QString())
{
    const QString text = value.toString().trimmed();
    return text.isEmpty() ? fallback : text;
}

QJsonObject requestJson(const QString &method, const QString &path, const QJsonObject &payload = {}, const QUrlQuery &query = {})
{
    QUrl url(AppConfig::apiUrl(path));
    if (!query.toString().isEmpty()) {
        url.setQuery(query);
    }

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
    request.setTransferTimeout(6000);

    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply *reply = nullptr;
    const QByteArray body = QJsonDocument(payload).toJson(QJsonDocument::Compact);

    if (method == QStringLiteral("POST")) {
        reply = manager.post(request, body);
    } else if (method == QStringLiteral("PUT")) {
        reply = manager.put(request, body);
    } else if (method == QStringLiteral("DELETE")) {
        reply = manager.deleteResource(request);
    } else {
        reply = manager.get(request);
    }

    QTimer timeout;
    timeout.setSingleShot(true);
    QObject::connect(&timeout, &QTimer::timeout, [&reply]() {
        if (reply != nullptr && reply->isRunning()) {
            reply->abort();
        }
    });
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    timeout.start(6000);
    loop.exec();
    timeout.stop();

    const QByteArray responseBody = reply->readAll();
    const bool ok = reply->error() == QNetworkReply::NoError;
    reply->deleteLater();
    if (!ok) {
        return {};
    }

    const QJsonDocument document = QJsonDocument::fromJson(responseBody);
    return document.isObject() ? document.object() : QJsonObject{};
}

QVariantList responseList(const QJsonObject &response)
{
    if (!response.value(QStringLiteral("success")).toBool()) {
        return {};
    }
    return response.value(QStringLiteral("data")).toArray().toVariantList();
}

QVariantMap responseMap(const QJsonObject &response)
{
    if (!response.value(QStringLiteral("success")).toBool()) {
        return {};
    }
    return response.value(QStringLiteral("data")).toObject().toVariantMap();
}

QString isoDateTime(const QDateTime &value)
{
    return value.isValid()
            ? value.toString(Qt::ISODate)
            : QDateTime::currentDateTime().toString(Qt::ISODate);
}

bool isObjectiveQuestion(const QString &type)
{
    return type == QStringLiteral("单选题")
            || type == QStringLiteral("多选题")
            || type == QStringLiteral("判断题")
            || type == QStringLiteral("填空题");
}

QString sectionTitleForType(const QString &type)
{
    return isObjectiveQuestion(type)
            ? QStringLiteral("第一部分 客观题")
            : QStringLiteral("第二部分 主观题");
}
}

TeacherDataRepository::TeacherDataRepository(qint64 teacherId, QObject *parent)
    : QObject(parent)
    , network(new QNetworkAccessManager(this))
    , teacherId(teacherId)
{
}

TeacherDataRepository::~TeacherDataRepository()
{
    const QString connectionName = db.connectionName();
    if (db.isOpen()) {
        db.close();
    }
    db = QSqlDatabase();
    if (!connectionName.isEmpty()) {
        QSqlDatabase::removeDatabase(connectionName);
    }
}

bool TeacherDataRepository::initialize()
{
    return true;
}

QString TeacherDataRepository::lastError() const
{
    return errorMessage;
}

bool TeacherDataRepository::openDatabase()
{
    const QString connectionName = QStringLiteral("teacher_mysql_connection");
    if (QSqlDatabase::contains(connectionName)) {
        db = QSqlDatabase::database(connectionName);
    } else {
        db = QSqlDatabase::addDatabase(QStringLiteral("QMYSQL"), connectionName);
        db.setHostName(QStringLiteral("127.0.0.1"));
        db.setPort(3306);
        db.setDatabaseName(QStringLiteral("exam_system"));
        db.setUserName(QStringLiteral("root"));
        db.setPassword(QStringLiteral("qxy080810"));
        db.setConnectOptions(QStringLiteral("MYSQL_OPT_RECONNECT=1"));
    }

    if (!db.open()) {
        errorMessage = QStringLiteral("无法连接 MySQL exam_system：") + db.lastError().text()
                + QStringLiteral("。请确认 MySQL 已启动，并且 Qt 安装目录有 qsqlmysql 驱动。");
        return false;
    }
    return true;
}

bool TeacherDataRepository::createSchema()
{
    const QStringList statements = {
        "CREATE TABLE IF NOT EXISTS exam_classes ("
        "id BIGINT PRIMARY KEY AUTO_INCREMENT,"
        "name VARCHAR(64) NOT NULL UNIQUE,"
        "major VARCHAR(64),"
        "created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4",

        "CREATE TABLE IF NOT EXISTS students ("
        "id BIGINT PRIMARY KEY AUTO_INCREMENT,"
        "username VARCHAR(64) NOT NULL UNIQUE,"
        "password VARCHAR(128) NOT NULL,"
        "name VARCHAR(64),"
        "student_no VARCHAR(64),"
        "major VARCHAR(64),"
        "class_id BIGINT,"
        "class_name VARCHAR(64),"
        "created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "INDEX idx_students_class (class_id),"
        "INDEX idx_students_class_name (class_name)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4",

        "CREATE TABLE IF NOT EXISTS teachers ("
        "id BIGINT PRIMARY KEY AUTO_INCREMENT,"
        "username VARCHAR(64) NOT NULL UNIQUE,"
        "password VARCHAR(128) NOT NULL,"
        "name VARCHAR(64),"
        "subject VARCHAR(64),"
        "phone VARCHAR(64),"
        "created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4",

        "CREATE TABLE IF NOT EXISTS admins ("
        "id BIGINT PRIMARY KEY AUTO_INCREMENT,"
        "username VARCHAR(64) NOT NULL UNIQUE,"
        "password VARCHAR(128) NOT NULL,"
        "name VARCHAR(64),"
        "phone VARCHAR(64),"
        "created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4",

        "CREATE TABLE IF NOT EXISTS teacher_classes ("
        "teacher_id BIGINT NOT NULL,"
        "class_id BIGINT NOT NULL,"
        "created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "PRIMARY KEY (teacher_id, class_id)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4",

        "CREATE TABLE IF NOT EXISTS subjects ("
        "id BIGINT PRIMARY KEY AUTO_INCREMENT,"
        "name VARCHAR(64) NOT NULL UNIQUE"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4",

        "CREATE TABLE IF NOT EXISTS questions ("
        "id BIGINT PRIMARY KEY AUTO_INCREMENT,"
        "subject VARCHAR(64) NOT NULL,"
        "type VARCHAR(32) NOT NULL,"
        "content TEXT NOT NULL,"
        "option_a TEXT,"
        "option_b TEXT,"
        "option_c TEXT,"
        "option_d TEXT,"
        "answer TEXT,"
        "analysis TEXT,"
        "difficulty VARCHAR(32),"
        "knowledge_point VARCHAR(128),"
        "score INT NOT NULL,"
        "created_by BIGINT,"
        "created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "INDEX idx_questions_subject_type (subject, type)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4",

        "CREATE TABLE IF NOT EXISTS exam_papers ("
        "id BIGINT PRIMARY KEY AUTO_INCREMENT,"
        "name VARCHAR(128) NOT NULL,"
        "subject VARCHAR(64) NOT NULL,"
        "start_time DATETIME,"
        "end_time DATETIME,"
        "total_score INT NOT NULL DEFAULT 0,"
        "status VARCHAR(32) NOT NULL DEFAULT '草稿',"
        "created_by BIGINT,"
        "created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "INDEX idx_exam_papers_status (status)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4",

        "CREATE TABLE IF NOT EXISTS exam_paper_questions ("
        "paper_id BIGINT NOT NULL,"
        "question_id BIGINT NOT NULL,"
        "score INT NOT NULL,"
        "sort_no INT NOT NULL DEFAULT 0,"
        "PRIMARY KEY (paper_id, question_id)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4",

        "CREATE TABLE IF NOT EXISTS exam_publishes ("
        "id BIGINT PRIMARY KEY AUTO_INCREMENT,"
        "paper_id BIGINT NOT NULL,"
        "class_name VARCHAR(64) NOT NULL,"
        "start_time DATETIME,"
        "end_time DATETIME,"
        "status VARCHAR(32) NOT NULL DEFAULT '已发布',"
        "created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "INDEX idx_exam_publishes_paper (paper_id)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4",

        "CREATE TABLE IF NOT EXISTS student_answers ("
        "id BIGINT PRIMARY KEY AUTO_INCREMENT,"
        "paper_id BIGINT NOT NULL,"
        "student_name VARCHAR(64) NOT NULL,"
        "student_no VARCHAR(32) NOT NULL,"
        "question_id BIGINT,"
        "answer TEXT,"
        "score DECIMAL(6,2),"
        "review_status VARCHAR(32) NOT NULL DEFAULT '待批改',"
        "comment TEXT,"
        "created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "INDEX idx_student_answers_status (review_status)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4",

        "CREATE TABLE IF NOT EXISTS scores ("
        "id BIGINT PRIMARY KEY AUTO_INCREMENT,"
        "paper_id BIGINT NOT NULL,"
        "student_no VARCHAR(32) NOT NULL,"
        "total_score DECIMAL(6,2) NOT NULL,"
        "class_name VARCHAR(64) NOT NULL,"
        "created_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "INDEX idx_scores_paper_class (paper_id, class_name)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4"
    };

    QSqlQuery query(db);
    for (const QString &statement : statements) {
        if (!query.exec(statement)) {
            errorMessage = query.lastError().text();
            return false;
        }
    }
    if (!ensureColumn(QStringLiteral("exam_classes"), QStringLiteral("major"), QStringLiteral("VARCHAR(64)"))
            || !ensureColumn(QStringLiteral("students"), QStringLiteral("student_no"), QStringLiteral("VARCHAR(64)"))
            || !ensureColumn(QStringLiteral("students"), QStringLiteral("major"), QStringLiteral("VARCHAR(64)"))
            || !ensureColumn(QStringLiteral("students"), QStringLiteral("class_name"), QStringLiteral("VARCHAR(64)"))
            || !ensureColumn(QStringLiteral("teachers"), QStringLiteral("subject"), QStringLiteral("VARCHAR(64)"))
            || !ensureColumn(QStringLiteral("teachers"), QStringLiteral("phone"), QStringLiteral("VARCHAR(64)"))
            || !ensureColumn(QStringLiteral("admins"), QStringLiteral("phone"), QStringLiteral("VARCHAR(64)"))) {
        return false;
    }
    dropOldTeacherClassForeignKeys();
    return true;
}

bool TeacherDataRepository::ensureColumn(const QString &tableName,
                                         const QString &columnName,
                                         const QString &definition)
{
    QSqlQuery check(db);
    check.prepare("SELECT COUNT(*) "
                  "FROM information_schema.columns "
                  "WHERE table_schema = DATABASE() AND table_name = ? AND column_name = ?");
    check.addBindValue(tableName);
    check.addBindValue(columnName);
    if (!check.exec() || !check.next()) {
        errorMessage = check.lastError().text();
        return false;
    }
    if (check.value(0).toInt() > 0) {
        return true;
    }

    QSqlQuery alter(db);
    const QString sql = QStringLiteral("ALTER TABLE %1 ADD COLUMN %2 %3")
            .arg(tableName, columnName, definition);
    if (!alter.exec(sql)) {
        errorMessage = alter.lastError().text();
        return false;
    }
    return true;
}

void TeacherDataRepository::dropOldTeacherClassForeignKeys()
{
    QSqlQuery query(db);
    query.prepare("SELECT CONSTRAINT_NAME "
                  "FROM information_schema.KEY_COLUMN_USAGE "
                  "WHERE table_schema = DATABASE() "
                  "AND table_name = 'teacher_classes' "
                  "AND referenced_table_name = 'users'");
    if (!query.exec()) {
        return;
    }

    QStringList constraints;
    while (query.next()) {
        constraints.append(query.value(0).toString());
    }
    for (QString constraint : constraints) {
        constraint.replace(QStringLiteral("`"), QStringLiteral("``"));
        QSqlQuery alter(db);
        alter.exec(QStringLiteral("ALTER TABLE teacher_classes DROP FOREIGN KEY `%1`").arg(constraint));
    }
}

void TeacherDataRepository::seedData()
{
    QSqlQuery query(db);
    const QList<QVariantMap> classRows = {
        {{"name", QStringLiteral("软工01")}, {"major", QStringLiteral("软件工程")}},
        {{"name", QStringLiteral("软工02")}, {"major", QStringLiteral("软件工程")}},
        {{"name", QStringLiteral("软工03")}, {"major", QStringLiteral("软件工程")}},
        {{"name", QStringLiteral("计科01")}, {"major", QStringLiteral("计算机科学与技术")}},
        {{"name", QStringLiteral("信网01")}, {"major", QStringLiteral("信息网络")}},
        {{"name", QStringLiteral("大数据01班")}, {"major", QStringLiteral("大数据")}}
    };
    QStringList classNames;
    for (const QVariantMap &classRow : classRows) {
        const QString className = classRow.value(QStringLiteral("name")).toString();
        classNames.append(className);
        QSqlQuery insertClass(db);
        insertClass.prepare("INSERT INTO exam_classes(name,major) VALUES(?,?) "
                            "ON DUPLICATE KEY UPDATE major=VALUES(major)");
        insertClass.addBindValue(className);
        insertClass.addBindValue(classRow.value(QStringLiteral("major")));
        insertClass.exec();
    }

    for (const QString &subject : {QStringLiteral("Java"), QStringLiteral("C++"), QStringLiteral("高数"),
                                  QStringLiteral("数据结构"), QStringLiteral("数据库")}) {
        QSqlQuery insertSubject(db);
        insertSubject.prepare("INSERT IGNORE INTO subjects(name) VALUES(?)");
        insertSubject.addBindValue(subject);
        insertSubject.exec();
    }

    QSqlQuery teacherCount(db);
    teacherCount.exec("SELECT COUNT(*) FROM teachers");
    if (teacherCount.next() && teacherCount.value(0).toInt() == 0) {
        const QList<QVariantMap> teachers = {
            {{"username", "teacher_math"}, {"name", "高数老师"}, {"subject", "高数"}},
            {{"username", "teacher_java"}, {"name", "Java老师"}, {"subject", "Java"}},
            {{"username", "teacher_cpp"}, {"name", "C++老师"}, {"subject", "C++"}}
        };
        for (const QVariantMap &teacher : teachers) {
            QSqlQuery insertTeacher(db);
            insertTeacher.prepare("INSERT INTO teachers(username,password,name,subject,created_time) VALUES(?,?,?,?,NOW())");
            insertTeacher.addBindValue(teacher.value("username"));
            insertTeacher.addBindValue(QStringLiteral("123456"));
            insertTeacher.addBindValue(teacher.value("name"));
            insertTeacher.addBindValue(teacher.value("subject"));
            insertTeacher.exec();
        }
    }

    QList<qlonglong> teacherIds;
    QSqlQuery teacherIdQuery(db);
    teacherIdQuery.exec("SELECT id FROM teachers ORDER BY id");
    while (teacherIdQuery.next()) {
        teacherIds.append(teacherIdQuery.value(0).toLongLong());
    }
    for (const QString &className : classNames) {
        QSqlQuery classQuery(db);
        classQuery.prepare("SELECT id FROM exam_classes WHERE name=?");
        classQuery.addBindValue(className);
        classQuery.exec();
        if (classQuery.next()) {
            for (qlonglong id : teacherIds) {
                QSqlQuery bind(db);
                bind.prepare("INSERT IGNORE INTO teacher_classes(teacher_id,class_id) VALUES(?,?)");
                bind.addBindValue(id);
                bind.addBindValue(classQuery.value(0));
                bind.exec();
            }
        }
    }

    QSqlQuery studentCount(db);
    studentCount.exec("SELECT COUNT(*) FROM students");
    if (studentCount.next() && studentCount.value(0).toInt() == 0) {
        int serial = 1;
        const QStringList seedClasses = {QStringLiteral("软工01"), QStringLiteral("软工02")};
        for (int classIndex = 0; classIndex < seedClasses.size(); ++classIndex) {
            QSqlQuery classQuery(db);
            classQuery.prepare("SELECT id, major FROM exam_classes WHERE name=?");
            classQuery.addBindValue(seedClasses.at(classIndex));
            classQuery.exec();
            qlonglong classId = 0;
            QString major;
            if (classQuery.next()) {
                classId = classQuery.value(0).toLongLong();
                major = classQuery.value(1).toString();
            }
            for (int i = 1; i <= 28; ++i) {
                const QString studentNo = QStringLiteral("25%1%2").arg(classIndex + 1).arg(i, 3, 10, QLatin1Char('0'));
                QSqlQuery insertStudent(db);
                insertStudent.prepare("INSERT INTO students(username,password,name,student_no,major,class_id,class_name,created_time) "
                                      "VALUES(?,?,?,?,?,?,?,NOW())");
                insertStudent.addBindValue(QStringLiteral("student_%1").arg(studentNo));
                insertStudent.addBindValue(QStringLiteral("123456"));
                insertStudent.addBindValue(QStringLiteral("学生%1").arg(serial++, 2, 10, QLatin1Char('0')));
                insertStudent.addBindValue(studentNo);
                insertStudent.addBindValue(major);
                insertStudent.addBindValue(classId);
                insertStudent.addBindValue(seedClasses.at(classIndex));
                insertStudent.exec();
            }
        }
    }

    QSqlQuery questionCount(db);
    questionCount.exec("SELECT COUNT(*) FROM questions");
    if (questionCount.next() && questionCount.value(0).toInt() == 0) {
        const QList<QVariantMap> seedQuestions = {
            {{"subject", "Java"}, {"type", "单选题"}, {"content", "Java虚拟机的缩写是？"}, {"answer", "JVM"}, {"difficulty", "基础"}},
            {{"subject", "Java"}, {"type", "多选题"}, {"content", "以下属于Java集合框架的是？"}, {"answer", "List;Map;Set"}, {"difficulty", "基础"}},
            {{"subject", "Java"}, {"type", "填空题"}, {"content", "Java源文件扩展名是____。"}, {"answer", ".java"}, {"difficulty", "基础"}},
            {{"subject", "高数"}, {"type", "高数大题"}, {"content", "求函数f(x)=x^2在[0,2]上的定积分。"}, {"answer", "8/3"}, {"difficulty", "中等"}},
            {{"subject", "C++"}, {"type", "代码题"}, {"content", "编写函数判断一个整数是否为素数。"}, {"answer", "trial division"}, {"difficulty", "中等"}},
            {{"subject", "Java"}, {"type", "单选题"}, {"content", "String是否不可变？"}, {"answer", "是"}, {"difficulty", "基础"}},
            {{"subject", "Java"}, {"type", "代码题"}, {"content", "使用Java实现冒泡排序。"}, {"answer", "bubble sort"}, {"difficulty", "中等"}}
        };
        for (const QVariantMap &question : seedQuestions) {
            addQuestion(question);
        }
    }

    QSqlQuery paperCount(db);
    paperCount.exec("SELECT COUNT(*) FROM exam_papers");
    if (paperCount.next() && paperCount.value(0).toInt() == 0) {
        const QDateTime start = QDateTime::fromString(QStringLiteral("2026-06-20 09:00"), QStringLiteral("yyyy-MM-dd HH:mm"));
        const QDateTime end = QDateTime::fromString(QStringLiteral("2026-06-20 11:00"), QStringLiteral("yyyy-MM-dd HH:mm"));
        const int paperId = createDraftPaper(QStringLiteral("Java期末考试"), QStringLiteral("Java"), start, end,
                                             QVariantMap{{"单选题", 2}, {"多选题", 1}, {"填空题", 1}, {"高数大题", 0}, {"代码题", 1}});
        publishExam(paperId, {QStringLiteral("软工01")}, start, end);

        const QList<QStringList> answers = {
            {"林一", "251001", "待批改"},
            {"陈可", "251002", "已批改"},
            {"周宁", "251003", "待批改"},
            {"李明", "251004", "已批改"}
        };
        for (const QStringList &answer : answers) {
            QSqlQuery insertAnswer(db);
            insertAnswer.prepare("INSERT INTO student_answers(paper_id, student_name, student_no, question_id, answer, score, review_status, comment) "
                                 "VALUES(?,?,?,?,?,?,?,?)");
            insertAnswer.addBindValue(paperId);
            insertAnswer.addBindValue(answer.at(0));
            insertAnswer.addBindValue(answer.at(1));
            insertAnswer.addBindValue(QVariant());
            insertAnswer.addBindValue(QStringLiteral("学生答案示例"));
            insertAnswer.addBindValue(answer.at(2) == QStringLiteral("已批改") ? QVariant(88.0) : QVariant());
            insertAnswer.addBindValue(answer.at(2));
            insertAnswer.addBindValue(QString());
            insertAnswer.exec();
        }

        QSqlQuery score(db);
        score.exec("INSERT INTO scores(paper_id, student_no, total_score, class_name) VALUES"
                   "(1,'251001',86.5,'软工01'),(1,'251002',92,'软工01'),"
                   "(1,'251003',74,'软工01'),(1,'251004',88,'软工01')");
    }
}

QVariantMap TeacherDataRepository::dashboardStats() const
{
    QUrlQuery params;
    if (teacherId > 0) {
        params.addQueryItem(QStringLiteral("teacherId"), QString::number(teacherId));
    }
    QVariantMap map = responseMap(requestJson(QStringLiteral("GET"), QStringLiteral("/exams/dashboard"), {}, params));
    if (map.isEmpty()) {
        map = {{"classCount", 0}, {"studentCount", 0}, {"examCount", 0}, {"pendingCount", 0}};
    }
    return map;
}

QVariantMap TeacherDataRepository::getTeacherProfile() const
{
    QVariantMap profile;
    if (teacherId > 0) {
        profile = responseMap(requestJson(QStringLiteral("GET"), QStringLiteral("/users/teachers/%1").arg(teacherId)));
    }

    if (profile.isEmpty() && db.isOpen() && teacherId > 0) {
        QSqlQuery query(db);
        query.prepare(QStringLiteral("SELECT id, username, name, subject, phone, email FROM teachers WHERE id = ?"));
        query.addBindValue(teacherId);
        if (query.exec() && query.next()) {
            profile.insert(QStringLiteral("id"), query.value(QStringLiteral("id")));
            profile.insert(QStringLiteral("username"), query.value(QStringLiteral("username")));
            profile.insert(QStringLiteral("name"), query.value(QStringLiteral("name")));
            profile.insert(QStringLiteral("subject"), query.value(QStringLiteral("subject")));
            profile.insert(QStringLiteral("phone"), query.value(QStringLiteral("phone")));
            profile.insert(QStringLiteral("email"), query.value(QStringLiteral("email")));
        }
    }

    profile.insert(QStringLiteral("role"), QStringLiteral("教师"));
    profile.insert(QStringLiteral("name"), variantString(profile.value(QStringLiteral("name")), QStringLiteral("教师")));
    profile.insert(QStringLiteral("subject"), variantString(profile.value(QStringLiteral("subject")), QStringLiteral("教师端")));
    return profile;
}

bool TeacherDataRepository::updateTeacherProfile(const QVariantMap &profileData)
{
    if (teacherId <= 0) {
        errorMessage = QStringLiteral("教师账号未登录");
        return false;
    }

    QJsonObject payload;
    payload.insert(QStringLiteral("name"), variantString(profileData.value(QStringLiteral("name"))));
    payload.insert(QStringLiteral("subject"), variantString(profileData.value(QStringLiteral("subject"))));
    payload.insert(QStringLiteral("phone"), variantString(profileData.value(QStringLiteral("phone"))));
    payload.insert(QStringLiteral("email"), variantString(profileData.value(QStringLiteral("email"))));

    const QJsonObject response = requestJson(QStringLiteral("PUT"),
                                             QStringLiteral("/users/teachers/%1").arg(teacherId),
                                             payload);
    const bool ok = response.value(QStringLiteral("success")).toBool();
    if (!ok) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("保存教师资料失败"));
    } else {
        errorMessage.clear();
    }
    return ok;
}

bool TeacherDataRepository::changePassword(const QString &oldPassword, const QString &newPassword)
{
    if (teacherId <= 0) {
        errorMessage = QStringLiteral("教师账号未登录");
        return false;
    }
    if (oldPassword.isEmpty()) {
        errorMessage = QStringLiteral("请输入原密码");
        return false;
    }
    if (newPassword.size() < 6) {
        errorMessage = QStringLiteral("新密码至少 6 位");
        return false;
    }

    QJsonObject payload;
    payload.insert(QStringLiteral("oldPassword"), oldPassword);
    payload.insert(QStringLiteral("newPassword"), newPassword);

    const QJsonObject response = requestJson(QStringLiteral("POST"),
                                             QStringLiteral("/users/TEACHER/%1/password").arg(teacherId),
                                             payload);
    const bool ok = response.value(QStringLiteral("success")).toBool();
    if (!ok) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("修改密码失败"));
    } else {
        errorMessage.clear();
    }
    return ok;
}

QVariantList TeacherDataRepository::getTeacherClasses() const
{
    QVariantList list;
    QUrlQuery params;
    if (teacherId > 0) {
        params.addQueryItem(QStringLiteral("teacherId"), QString::number(teacherId));
    }
    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/users/teacher-classes"), {}, params));
    for (const QVariant &rowValue : rows) {
        const QVariantMap row = rowValue.toMap();
        list.append(QVariantMap{{"id", row.value(QStringLiteral("id"))},
                                {"name", row.value(QStringLiteral("name"))},
                                {"major", row.value(QStringLiteral("major"))},
                                {"students", row.value(QStringLiteral("student_count"), row.value(QStringLiteral("studentCount"), 0))},
                                {"examCount", row.value(QStringLiteral("exam_count"), row.value(QStringLiteral("examCount"), 0))},
                                {"average", row.value(QStringLiteral("average"), 0)},
                                {"best", row.value(QStringLiteral("best"), 0)}});
    }
    return list;
}

QVariantList TeacherDataRepository::getClassStudents(const QString &className) const
{
    QVariantList list;
    const QString encodedClassName = QString::fromUtf8(QUrl::toPercentEncoding(className));
    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/users/classes/%1/students").arg(encodedClassName)));
    for (const QVariant &rowValue : rows) {
        const QVariantMap row = rowValue.toMap();
        list.append(QVariantMap{{"id", row.value(QStringLiteral("id"))},
                                {"username", row.value(QStringLiteral("username"))},
                                {"studentNo", row.value(QStringLiteral("student_no"), row.value(QStringLiteral("studentNo")))},
                                {"name", row.value(QStringLiteral("name"))},
                                {"major", row.value(QStringLiteral("major"))},
                                {"className", row.value(QStringLiteral("class_name"), row.value(QStringLiteral("className")))}});
    }
    return list;
}

QVariantList TeacherDataRepository::getExamList() const
{
    QVariantList list;
    QUrlQuery params;
    if (teacherId > 0) {
        params.addQueryItem(QStringLiteral("createdBy"), QString::number(teacherId));
    }
    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/exams"), {}, params));
    for (const QVariant &rowValue : rows) {
        const QVariantMap row = rowValue.toMap();
        const QString createdTime = row.value(QStringLiteral("createdTime"), row.value(QStringLiteral("created_time"))).toString();
        const QString startTime = row.value(QStringLiteral("startTime"), row.value(QStringLiteral("start_time"), createdTime)).toString();
        const QString endTime = row.value(QStringLiteral("endTime"), row.value(QStringLiteral("end_time"))).toString();
        list.append(QVariantMap{{"id", row.value(QStringLiteral("id"))},
                                {"name", row.value(QStringLiteral("title"))},
                                {"subject", row.value(QStringLiteral("subject"), QString())},
                                {"startTime", startTime},
                                {"endTime", endTime},
                                {"totalScore", row.value(QStringLiteral("totalScore"), row.value(QStringLiteral("total_score"), 0))},
                                {"status", row.value(QStringLiteral("flowStatus"), row.value(QStringLiteral("status")))},
                                {"originalStatus", row.value(QStringLiteral("status"))},
                                {"date", startTime.left(10).isEmpty() ? createdTime.left(10) : startTime.left(10)},
                                {"className", row.value(QStringLiteral("className"), row.value(QStringLiteral("class_name")))},
                                {"participants", row.value(QStringLiteral("participants"), 0)},
                                {"publishedCount", row.value(QStringLiteral("publishedCount"), row.value(QStringLiteral("published_count"), 0))},
                                {"targetStudentCount", row.value(QStringLiteral("targetStudentCount"), row.value(QStringLiteral("target_student_count"), 0))},
                                {"pendingReviewCount", row.value(QStringLiteral("pendingReviewCount"), row.value(QStringLiteral("pending_review_count"), 0))},
                                {"reviewedStudents", row.value(QStringLiteral("reviewedStudents"), row.value(QStringLiteral("reviewed_students"), 0))},
                                {"average", row.value(QStringLiteral("average"), 0)}});
    }
    return list;
}

QVariantList TeacherDataRepository::getQuestions() const
{
    return searchQuestions(QString(), QString(), QString());
}

QVariantList TeacherDataRepository::searchQuestions(const QString &keyword,
                                                    const QString &type,
                                                    const QString &difficulty) const
{
    return searchQuestionsAdvanced(keyword, QString(), type, difficulty, QString());
}

QVariantList TeacherDataRepository::searchQuestionsAdvanced(const QString &keyword,
                                                            const QString &subject,
                                                            const QString &type,
                                                            const QString &difficulty,
                                                            const QString &knowledgePoint) const
{
    QVariantList list;
    auto cleanFilter = [](QString value, const QString &prefix) {
        value = value.trimmed();
        if (!prefix.isEmpty() && value.startsWith(prefix)) {
            value = value.mid(prefix.size()).trimmed();
        }
        return value.contains(QStringLiteral("全部")) ? QString() : value;
    };

    QUrlQuery params;
    const QString cleanKeyword = keyword.trimmed();
    const QString cleanSubject = cleanFilter(subject, QStringLiteral("科目："));
    const QString cleanType = cleanFilter(type, QStringLiteral("题型："));
    const QString cleanDifficulty = cleanFilter(difficulty, QStringLiteral("难度："));
    const QString cleanKnowledgePoint = knowledgePoint.trimmed();
    if (!cleanKeyword.isEmpty()) {
        params.addQueryItem(QStringLiteral("keyword"), cleanKeyword);
    }
    if (!cleanSubject.isEmpty()) {
        params.addQueryItem(QStringLiteral("subject"), cleanSubject);
    }
    if (!cleanType.isEmpty()) {
        params.addQueryItem(QStringLiteral("type"), cleanType);
    }
    if (!cleanDifficulty.isEmpty()) {
        params.addQueryItem(QStringLiteral("difficulty"), cleanDifficulty);
    }
    if (!cleanKnowledgePoint.isEmpty()) {
        params.addQueryItem(QStringLiteral("knowledgePoint"), cleanKnowledgePoint);
    }

    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/questions"), {}, params));
    for (const QVariant &rowValue : rows) {
        const QVariantMap row = rowValue.toMap();
        list.append(QVariantMap{{"id", row.value(QStringLiteral("id"))},
                                {"subject", row.value(QStringLiteral("subject"), QStringLiteral("Java"))},
                                {"type", row.value(QStringLiteral("type"))},
                                {"content", row.value(QStringLiteral("content"))},
                                {"optionA", row.value(QStringLiteral("optionA"), row.value(QStringLiteral("option_a")))},
                                {"optionB", row.value(QStringLiteral("optionB"), row.value(QStringLiteral("option_b")))},
                                {"optionC", row.value(QStringLiteral("optionC"), row.value(QStringLiteral("option_c")))},
                                {"optionD", row.value(QStringLiteral("optionD"), row.value(QStringLiteral("option_d")))},
                                {"answer", row.value(QStringLiteral("answer"))},
                                {"analysis", row.value(QStringLiteral("analysis"))},
                                {"knowledgePoint", row.value(QStringLiteral("knowledgePoint"), row.value(QStringLiteral("knowledge_point")))},
                                {"score", row.value(QStringLiteral("score"))},
                                {"difficulty", row.value(QStringLiteral("difficulty"))}});
    }
    return list;
}

QVariantList TeacherDataRepository::getQuestionAnalysis() const
{
    const QVariantList exams = getExamList();
    if (exams.isEmpty()) {
        return {};
    }
    QUrlQuery params;
    params.addQueryItem(QStringLiteral("examId"), QString::number(exams.first().toMap().value(QStringLiteral("id")).toInt()));
    QVariantMap analysisMap = responseMap(requestJson(QStringLiteral("GET"), QStringLiteral("/scores/analysis"), {}, params));
    QVariantList rows = analysisMap.value(QStringLiteral("questionAnalysis")).toList();
    QVariantList list;
    int index = 1;
    for (const QVariant &rowValue : rows) {
        QVariantMap row = rowValue.toMap();
        list.append(QVariantMap{{"index", QStringLiteral("第%1题").arg(index++)},
                                {"type", row.value(QStringLiteral("type"))},
                                {"full", row.value(QStringLiteral("full_score"), row.value(QStringLiteral("full"), 0))},
                                {"average", row.value(QStringLiteral("average_score"), row.value(QStringLiteral("average"), 0))},
                                {"low", row.value(QStringLiteral("low_score"), row.value(QStringLiteral("low"), 0)).toInt() != 0}});
    }
    return list;
}

QVariantMap TeacherDataRepository::getScoreStatistics() const
{
    const QVariantList exams = getExamList();
    if (exams.isEmpty()) {
        return {{"trend", QVariantList{}}, {"distribution", QVariantList{}}, {"passRate", 0}, {"average", 0}};
    }
    QVariantList trend;
    for (int i = qMin(exams.size(), 6) - 1; i >= 0; --i) {
        const QVariantMap exam = exams.at(i).toMap();
        trend.append(QVariantMap{{"label", exam.value(QStringLiteral("name")).toString()},
                                 {"value", exam.value(QStringLiteral("average"), 0)}});
    }
    QUrlQuery params;
    params.addQueryItem(QStringLiteral("examId"), QString::number(exams.first().toMap().value(QStringLiteral("id")).toInt()));
    QVariantMap analysisMap = responseMap(requestJson(QStringLiteral("GET"), QStringLiteral("/scores/analysis"), {}, params));
    QVariantMap summary = analysisMap.value(QStringLiteral("summary")).toMap();
    return {
        {"trend", trend},
        {"distribution", analysisMap.value(QStringLiteral("distribution")).toList()},
        {"passRate", summary.value(QStringLiteral("pass_rate"), 0)},
        {"average", summary.value(QStringLiteral("average_score"), 0)}
    };
}

QVariantList TeacherDataRepository::getClassScoreTrend(const QString &className, const QString &subject) const
{
    QVariantList list;
    QUrlQuery params;
    if (!className.trimmed().isEmpty()) {
        params.addQueryItem(QStringLiteral("className"), className.trimmed());
    }
    if (!subject.trimmed().isEmpty()) {
        params.addQueryItem(QStringLiteral("subject"), subject.trimmed());
    }
    params.addQueryItem(QStringLiteral("limit"), QStringLiteral("7"));

    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/scores/class-trend"), {}, params));
    for (const QVariant &rowValue : rows) {
        const QVariantMap row = rowValue.toMap();
        list.append(QVariantMap{
            {"examId", row.value(QStringLiteral("exam_id"), row.value(QStringLiteral("examId")))},
            {"examTitle", row.value(QStringLiteral("exam_title"), row.value(QStringLiteral("examTitle")))},
            {"subject", row.value(QStringLiteral("subject"))},
            {"date", row.value(QStringLiteral("exam_date"), row.value(QStringLiteral("examDate")))},
            {"label", row.value(QStringLiteral("trend_label"), row.value(QStringLiteral("trendLabel")))},
            {"value", row.value(QStringLiteral("average_score"), row.value(QStringLiteral("averageScore"), 0))},
            {"studentCount", row.value(QStringLiteral("student_count"), row.value(QStringLiteral("studentCount"), 0))}
        });
    }
    return list;
}

QVariantList TeacherDataRepository::getPendingReviews() const
{
    QVariantList list;
    QUrlQuery params;
    params.addQueryItem(QStringLiteral("status"), QStringLiteral("待批改"));
    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/scores/answer-students"), {}, params));
    for (const QVariant &rowValue : rows) {
        const QVariantMap row = rowValue.toMap();
        list.append(QVariantMap{{"paperId", row.value(QStringLiteral("exam_id"), row.value(QStringLiteral("examId")))},
                                {"studentName", row.value(QStringLiteral("student_name"), row.value(QStringLiteral("studentName")))},
                                {"studentNo", row.value(QStringLiteral("student_no"), row.value(QStringLiteral("studentNo")))},
                                {"status", row.value(QStringLiteral("review_status"), row.value(QStringLiteral("reviewStatus")))}} );
    }
    return list;
}

QVariantList TeacherDataRepository::getStudentAnswers() const
{
    QVariantList list;
    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/scores/answer-students")));
    for (const QVariant &rowValue : rows) {
        const QVariantMap row = rowValue.toMap();
        list.append(QVariantMap{{"paperId", row.value(QStringLiteral("exam_id"), row.value(QStringLiteral("examId")))},
                                {"studentName", row.value(QStringLiteral("student_name"), row.value(QStringLiteral("studentName")))},
                                {"studentNo", row.value(QStringLiteral("student_no"), row.value(QStringLiteral("studentNo")))},
                                {"className", row.value(QStringLiteral("class_name"), row.value(QStringLiteral("className")))},
                                {"score", row.value(QStringLiteral("score"))},
                                {"pendingCount", row.value(QStringLiteral("pending_count"), row.value(QStringLiteral("pendingCount"), 0))},
                                {"status", row.value(QStringLiteral("review_status"), row.value(QStringLiteral("reviewStatus")))}} );
    }
    return list;
}

QVariantList TeacherDataRepository::getStudentAnswersForPaper(int paperId) const
{
    QVariantList list;
    QUrlQuery params;
    if (paperId > 0) {
        params.addQueryItem(QStringLiteral("examId"), QString::number(paperId));
    }
    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/scores/answer-students"), {}, params));
    for (const QVariant &rowValue : rows) {
        const QVariantMap row = rowValue.toMap();
        list.append(QVariantMap{{"paperId", row.value(QStringLiteral("exam_id"), row.value(QStringLiteral("examId"), paperId))},
                                {"studentName", row.value(QStringLiteral("student_name"), row.value(QStringLiteral("studentName")))},
                                {"studentNo", row.value(QStringLiteral("student_no"), row.value(QStringLiteral("studentNo")))},
                                {"className", row.value(QStringLiteral("class_name"), row.value(QStringLiteral("className")))},
                                {"score", row.value(QStringLiteral("score"))},
                                {"pendingCount", row.value(QStringLiteral("pending_count"), row.value(QStringLiteral("pendingCount"), 0))},
                                {"answerCount", row.value(QStringLiteral("answer_count"), row.value(QStringLiteral("answerCount"), 0))},
                                {"status", row.value(QStringLiteral("review_status"), row.value(QStringLiteral("reviewStatus")))}} );
    }
    return list;
}

QVariantList TeacherDataRepository::getStudentAnswersForStudent(int paperId, const QString &studentNo) const
{
    QVariantList list;
    if (paperId <= 0 || studentNo.trimmed().isEmpty()) {
        return list;
    }
    QUrlQuery params;
    params.addQueryItem(QStringLiteral("examId"), QString::number(paperId));
    params.addQueryItem(QStringLiteral("studentNo"), studentNo.trimmed());
    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/scores/student-answers"), {}, params));
    for (const QVariant &rowValue : rows) {
        const QVariantMap row = rowValue.toMap();
        list.append(QVariantMap{{"id", row.value(QStringLiteral("id"))},
                                {"questionId", row.value(QStringLiteral("question_id"), row.value(QStringLiteral("questionId")))},
                                {"sortNo", row.value(QStringLiteral("sort_no"), row.value(QStringLiteral("sortNo")))},
                                {"studentName", row.value(QStringLiteral("student_name"), row.value(QStringLiteral("studentName")))},
                                {"studentNo", row.value(QStringLiteral("student_no"), row.value(QStringLiteral("studentNo")))},
                                {"answer", row.value(QStringLiteral("answer"))},
                                {"score", row.value(QStringLiteral("score"))},
                                {"questionScore", row.value(QStringLiteral("question_score"), row.value(QStringLiteral("questionScore")))},
                                {"status", row.value(QStringLiteral("review_status"), row.value(QStringLiteral("reviewStatus")))},
                                {"comment", row.value(QStringLiteral("comment"))}});
    }
    return list;
}

QVariantList TeacherDataRepository::getReviewExams() const
{
    QVariantList list;
    QUrlQuery params;
    if (teacherId > 0) {
        params.addQueryItem(QStringLiteral("teacherId"), QString::number(teacherId));
    }

    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/scores/review/exams"), {}, params));
    for (const QVariant &rowValue : rows) {
        const QVariantMap row = rowValue.toMap();
        const QString title = row.value(QStringLiteral("title"), QStringLiteral("未命名考试")).toString();
        const QString subject = row.value(QStringLiteral("subject"), QStringLiteral("综合")).toString();
        const QString date = row.value(QStringLiteral("exam_date"), row.value(QStringLiteral("examDate"))).toString();
        list.append(QVariantMap{
            {"id", row.value(QStringLiteral("id"))},
            {"title", title},
            {"name", title},
            {"course", subject},
            {"subject", subject},
            {"date", date},
            {"startTime", row.value(QStringLiteral("start_time"), row.value(QStringLiteral("startTime")))},
            {"endTime", row.value(QStringLiteral("end_time"), row.value(QStringLiteral("endTime")))},
            {"totalScore", row.value(QStringLiteral("total_score"), row.value(QStringLiteral("totalScore"), 0))},
            {"submittedCount", row.value(QStringLiteral("submitted_count"), row.value(QStringLiteral("submittedCount"), 0))},
            {"completedCount", row.value(QStringLiteral("completed_count"), row.value(QStringLiteral("completedCount"), 0))},
            {"pendingStudentCount", row.value(QStringLiteral("pending_student_count"), row.value(QStringLiteral("pendingStudentCount"), 0))},
            {"pendingAnswerCount", row.value(QStringLiteral("pending_answer_count"), row.value(QStringLiteral("pendingAnswerCount"), 0))},
            {"average", row.value(QStringLiteral("average_score"), row.value(QStringLiteral("averageScore"), 0))},
            {"status", row.value(QStringLiteral("review_status"), row.value(QStringLiteral("reviewStatus"), row.value(QStringLiteral("status"))))}
        });
    }
    return list;
}

QVariantList TeacherDataRepository::getReviewStudents(int examId) const
{
    QVariantList list;
    if (examId <= 0) {
        return list;
    }

    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/scores/review/exams/%1/students").arg(examId)));
    for (const QVariant &rowValue : rows) {
        const QVariantMap row = rowValue.toMap();
        const QString status = row.value(QStringLiteral("review_status"), row.value(QStringLiteral("reviewStatus"), QStringLiteral("待批改"))).toString();
        const QVariant scoreValue = row.value(QStringLiteral("score"));
        const QString scoreText = status == QStringLiteral("已批改") || status == QStringLiteral("批改中")
                ? QString::number(scoreValue.toDouble(), 'f', 0)
                : QStringLiteral("--");
        list.append(QVariantMap{
            {"paperId", row.value(QStringLiteral("exam_id"), row.value(QStringLiteral("examId"), examId))},
            {"examTitle", row.value(QStringLiteral("exam_title"), row.value(QStringLiteral("examTitle")))},
            {"subject", row.value(QStringLiteral("subject"))},
            {"studentId", row.value(QStringLiteral("student_id"), row.value(QStringLiteral("studentId")))},
            {"name", row.value(QStringLiteral("student_name"), row.value(QStringLiteral("studentName"), QStringLiteral("未命名学生")))},
            {"studentName", row.value(QStringLiteral("student_name"), row.value(QStringLiteral("studentName"), QStringLiteral("未命名学生")))},
            {"studentNo", row.value(QStringLiteral("student_no"), row.value(QStringLiteral("studentNo")))},
            {"className", row.value(QStringLiteral("class_name"), row.value(QStringLiteral("className")))},
            {"score", scoreText},
            {"rawScore", scoreValue},
            {"pendingCount", row.value(QStringLiteral("pending_count"), row.value(QStringLiteral("pendingCount"), 0))},
            {"answerCount", row.value(QStringLiteral("answer_count"), row.value(QStringLiteral("answerCount"), 0))},
            {"status", status}
        });
    }
    return list;
}

QVariantList TeacherDataRepository::getReviewStudentAnswers(int examId, const QString &studentNo) const
{
    QVariantList list;
    if (examId <= 0 || studentNo.trimmed().isEmpty()) {
        return list;
    }

    const QString encodedStudentNo = QString::fromUtf8(QUrl::toPercentEncoding(studentNo.trimmed()));
    const QVariantList rows = responseList(requestJson(
            QStringLiteral("GET"),
            QStringLiteral("/scores/review/exams/%1/students/%2/answers").arg(examId).arg(encodedStudentNo)));
    int index = 1;
    for (const QVariant &rowValue : rows) {
        const QVariantMap row = rowValue.toMap();
        const QString type = row.value(QStringLiteral("type")).toString();
        const QString status = row.value(QStringLiteral("review_status"), row.value(QStringLiteral("reviewStatus"))).toString();
        const bool autoScored = row.value(QStringLiteral("is_objective"), row.value(QStringLiteral("isObjective"))).toBool()
                || status == QStringLiteral("自动评分")
                || isObjectiveQuestion(type);
        const int number = row.value(QStringLiteral("sort_no"), row.value(QStringLiteral("sortNo"), index)).toInt();
        const double maxScore = row.value(QStringLiteral("question_score"), row.value(QStringLiteral("questionScore"), 0)).toDouble();
        list.append(QVariantMap{
            {"id", row.value(QStringLiteral("id"))},
            {"answerId", row.value(QStringLiteral("id"))},
            {"questionId", row.value(QStringLiteral("question_id"), row.value(QStringLiteral("questionId")))},
            {"number", number <= 0 ? index : number},
            {"sortNo", number <= 0 ? index : number},
            {"section", sectionTitleForType(type)},
            {"type", type},
            {"question", row.value(QStringLiteral("content"), row.value(QStringLiteral("question")))},
            {"studentAnswer", row.value(QStringLiteral("answer"), row.value(QStringLiteral("studentAnswer")))},
            {"standardAnswer", row.value(QStringLiteral("standard_answer"), row.value(QStringLiteral("standardAnswer")))},
            {"analysis", row.value(QStringLiteral("analysis"))},
            {"knowledgePoint", row.value(QStringLiteral("knowledge_point"), row.value(QStringLiteral("knowledgePoint")))},
            {"maxScore", maxScore},
            {"score", row.value(QStringLiteral("score"), 0)},
            {"autoScored", autoScored},
            {"graded", autoScored || status == QStringLiteral("已批改")},
            {"status", status},
            {"comment", row.value(QStringLiteral("comment"))}
        });
        ++index;
    }
    return list;
}

QVariantList TeacherDataRepository::getPaperQuestions(int paperId) const
{
    QVariantList list;
    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/exams/%1/questions").arg(paperId)));
    for (const QVariant &rowValue : rows) {
        const QVariantMap row = rowValue.toMap();
        list.append(QVariantMap{{"id", row.value(QStringLiteral("question_id"), row.value(QStringLiteral("questionId"), row.value(QStringLiteral("id"))))},
                                {"type", row.value(QStringLiteral("type"))},
                                {"content", row.value(QStringLiteral("content"))},
                                {"answer", row.value(QStringLiteral("answer"), row.value(QStringLiteral("standard_answer")))},
                                {"score", row.value(QStringLiteral("paper_score"), row.value(QStringLiteral("score")))}} );
    }
    return list;
}

QVariantList TeacherDataRepository::getTodoItems() const
{
    QVariantList list;
    if (teacherId <= 0) {
        return list;
    }

    QUrlQuery params;
    params.addQueryItem(QStringLiteral("teacherId"), QString::number(teacherId));
    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/teacher-todos"), {}, params));
    for (const QVariant &rowValue : rows) {
        const QVariantMap row = rowValue.toMap();
        QString remindTime = row.value(QStringLiteral("remindTime"), row.value(QStringLiteral("remind_time"))).toString();
        remindTime.replace(QLatin1Char('T'), QLatin1Char(' '));
        if (remindTime.size() >= 16) {
            remindTime = remindTime.left(16);
        }
        list.append(QVariantMap{
            {"id", row.value(QStringLiteral("id"))},
            {"title", row.value(QStringLiteral("title"))},
            {"type", row.value(QStringLiteral("type"), QStringLiteral("待办提醒"))},
            {"time", remindTime},
            {"status", row.value(QStringLiteral("status"), QStringLiteral("待处理"))}
        });
    }
    return list;
}

QVariantList TeacherDataRepository::getImportLogs() const
{
    QVariantList list;
    QUrlQuery params;
    if (teacherId > 0) {
        params.addQueryItem(QStringLiteral("userId"), QString::number(teacherId));
    }
    params.addQueryItem(QStringLiteral("limit"), QStringLiteral("50"));
    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/questions/import/logs"), {}, params));
    for (const QVariant &rowValue : rows) {
        const QVariantMap row = rowValue.toMap();
        QString timeText = row.value(QStringLiteral("createdTime"), row.value(QStringLiteral("created_time"))).toString();
        timeText.replace(QLatin1Char('T'), QLatin1Char(' '));
        if (timeText.size() > 19) {
            timeText = timeText.left(19);
        }
        list.append(QVariantMap{
            {"id", row.value(QStringLiteral("id"))},
            {"type", row.value(QStringLiteral("importType"), row.value(QStringLiteral("import_type")))},
            {"fileName", row.value(QStringLiteral("fileName"), row.value(QStringLiteral("file_name")))},
            {"totalCount", row.value(QStringLiteral("totalCount"), row.value(QStringLiteral("total_count")))},
            {"successCount", row.value(QStringLiteral("successCount"), row.value(QStringLiteral("success_count")))},
            {"failedCount", row.value(QStringLiteral("failedCount"), row.value(QStringLiteral("failed_count")))},
            {"status", row.value(QStringLiteral("status"))},
            {"message", row.value(QStringLiteral("message"))},
            {"time", timeText}
        });
    }
    return list;
}

int TeacherDataRepository::addQuestion(const QVariantMap &question)
{
    QJsonObject payload = QJsonObject::fromVariantMap(question);
    if (teacherId > 0) {
        payload.insert(QStringLiteral("createdBy"), QJsonValue::fromVariant(teacherId));
    }
    const QJsonObject response = requestJson(QStringLiteral("POST"), QStringLiteral("/questions"), payload);
    if (!response.value(QStringLiteral("success")).toBool()) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("新增题目失败"));
        return -1;
    }
    return response.value(QStringLiteral("data")).toObject().value(QStringLiteral("id")).toInt();
}

bool TeacherDataRepository::updateQuestion(int id, const QVariantMap &question)
{
    QJsonObject payload = QJsonObject::fromVariantMap(question);
    if (teacherId > 0) {
        payload.insert(QStringLiteral("createdBy"), QJsonValue::fromVariant(teacherId));
    }
    const QJsonObject response = requestJson(QStringLiteral("PUT"), QStringLiteral("/questions/%1").arg(id), payload);
    const bool ok = response.value(QStringLiteral("success")).toBool();
    if (!ok) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("修改题目失败"));
    }
    return ok;
}

bool TeacherDataRepository::removeQuestion(int id)
{
    QUrlQuery params;
    if (teacherId > 0) {
        params.addQueryItem(QStringLiteral("userId"), QString::number(teacherId));
    }
    const QJsonObject response = requestJson(QStringLiteral("DELETE"), QStringLiteral("/questions/%1").arg(id), {}, params);
    const bool ok = response.value(QStringLiteral("success")).toBool();
    if (!ok) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("删除题目失败"));
    }
    return ok;
}

int TeacherDataRepository::importQuestionsFromCsv(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        errorMessage = file.errorString();
        return 0;
    }

    int imported = 0;
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    while (!stream.atEnd()) {
        const QString line = stream.readLine().trimmed();
        if (line.isEmpty() || line.startsWith('#')) {
            continue;
        }
        const QStringList fields = line.split(',');
        if (fields.size() < 4 || fields.at(0).trimmed().compare(QStringLiteral("subject"), Qt::CaseInsensitive) == 0) {
            continue;
        }
        QVariantMap question{{"subject", fields.value(0).trimmed()},
                             {"type", fields.value(1).trimmed()},
                             {"content", fields.value(2).trimmed()},
                             {"answer", fields.value(3).trimmed()},
                             {"difficulty", fields.value(4, QStringLiteral("基础")).trimmed()}};
        if (addQuestion(question) > 0) {
            ++imported;
        }
    }
    return imported;
}

bool TeacherDataRepository::recordImportLog(const QString &type,
                                            const QString &fileName,
                                            int totalCount,
                                            int successCount,
                                            int failedCount,
                                            const QString &status,
                                            const QString &message)
{
    QJsonObject payload;
    if (teacherId > 0) {
        payload.insert(QStringLiteral("userId"), QJsonValue::fromVariant(teacherId));
    }
    payload.insert(QStringLiteral("importType"), type);
    payload.insert(QStringLiteral("fileName"), fileName);
    payload.insert(QStringLiteral("totalCount"), totalCount);
    payload.insert(QStringLiteral("successCount"), successCount);
    payload.insert(QStringLiteral("failedCount"), failedCount);
    payload.insert(QStringLiteral("status"), status);
    payload.insert(QStringLiteral("message"), message);

    const QJsonObject response = requestJson(QStringLiteral("POST"), QStringLiteral("/questions/import/logs"), payload);
    const bool ok = response.value(QStringLiteral("success")).toBool();
    if (!ok) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("导入日志记录失败"));
    }
    return ok;
}

int TeacherDataRepository::createDraftPaper(const QString &name,
                                            const QString &subject,
                                            const QDateTime &startTime,
                                            const QDateTime &endTime,
                                            const QVariantMap &counts)
{
    QJsonObject typeCounts;
    for (auto it = counts.constBegin(); it != counts.constEnd(); ++it) {
        typeCounts.insert(it.key(), it.value().toInt());
    }

    QJsonObject payload;
    payload.insert(QStringLiteral("title"), name);
    payload.insert(QStringLiteral("subject"), subject.trimmed().isEmpty() ? QStringLiteral("综合") : subject.trimmed());
    payload.insert(QStringLiteral("startTime"), isoDateTime(startTime));
    payload.insert(QStringLiteral("endTime"), isoDateTime(endTime));
    const int duration = startTime.isValid() && endTime.isValid() && startTime.secsTo(endTime) > 0
            ? qMax(1, int(startTime.secsTo(endTime) / 60))
            : 120;
    payload.insert(QStringLiteral("duration"), duration);
    payload.insert(QStringLiteral("typeCounts"), typeCounts);
    if (teacherId > 0) {
        payload.insert(QStringLiteral("createdBy"), QJsonValue::fromVariant(teacherId));
    }

    const QJsonObject response = requestJson(QStringLiteral("POST"), QStringLiteral("/exams/papers"), payload);
    if (!response.value(QStringLiteral("success")).toBool()) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("创建试卷失败"));
        return -1;
    }
    return response.value(QStringLiteral("data")).toObject().value(QStringLiteral("id")).toInt();
}

int TeacherDataRepository::createDraftPaperFromQuestions(const QString &name,
                                                         const QString &subject,
                                                         const QDateTime &startTime,
                                                         const QDateTime &endTime,
                                                         const QVariantList &questions)
{
    QJsonArray questionIds;
    QSet<int> seen;
    for (const QVariant &value : questions) {
        const QVariantMap question = value.toMap();
        const int questionId = question.value(QStringLiteral("id"),
                              question.value(QStringLiteral("questionId"),
                              question.value(QStringLiteral("question_id")))).toInt();
        if (questionId > 0 && !seen.contains(questionId)) {
            questionIds.append(questionId);
            seen.insert(questionId);
        }
    }
    if (questionIds.isEmpty()) {
        errorMessage = QStringLiteral("请先添加题目后再保存试卷");
        return -1;
    }

    QJsonObject payload;
    payload.insert(QStringLiteral("title"), name.trimmed().isEmpty() ? QStringLiteral("未命名试卷") : name.trimmed());
    payload.insert(QStringLiteral("subject"), subject.trimmed().isEmpty() ? QStringLiteral("综合") : subject.trimmed());
    payload.insert(QStringLiteral("startTime"), isoDateTime(startTime));
    payload.insert(QStringLiteral("endTime"), isoDateTime(endTime));
    const int duration = startTime.isValid() && endTime.isValid() && startTime.secsTo(endTime) > 0
            ? qMax(1, int(startTime.secsTo(endTime) / 60))
            : 120;
    payload.insert(QStringLiteral("duration"), duration);
    payload.insert(QStringLiteral("questionIds"), questionIds);
    if (teacherId > 0) {
        payload.insert(QStringLiteral("createdBy"), QJsonValue::fromVariant(teacherId));
    }

    const QJsonObject response = requestJson(QStringLiteral("POST"), QStringLiteral("/exams/papers"), payload);
    if (!response.value(QStringLiteral("success")).toBool()) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("保存试卷草稿失败"));
        return -1;
    }
    return response.value(QStringLiteral("data")).toObject().value(QStringLiteral("id")).toInt();
}

int TeacherDataRepository::copyExamAsDraft(const QString &examName, const QDateTime &startTime, const QDateTime &endTime)
{
    Q_UNUSED(startTime)
    Q_UNUSED(endTime)

    const QVariantList exams = getExamList();
    int sourceId = 0;
    for (const QVariant &examValue : exams) {
        const QVariantMap exam = examValue.toMap();
        if (exam.value(QStringLiteral("name")).toString() == examName) {
            sourceId = exam.value(QStringLiteral("id")).toInt();
            break;
        }
    }
    if (sourceId <= 0) {
        errorMessage = QStringLiteral("未找到要复制的试卷");
        return -1;
    }

    QUrlQuery params;
    params.addQueryItem(QStringLiteral("title"), examName + QStringLiteral(" 副本"));
    if (teacherId > 0) {
        params.addQueryItem(QStringLiteral("createdBy"), QString::number(teacherId));
    }

    const QJsonObject response = requestJson(QStringLiteral("POST"), QStringLiteral("/exams/%1/copy").arg(sourceId), {}, params);
    if (!response.value(QStringLiteral("success")).toBool()) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("复制试卷失败"));
        return -1;
    }
    return response.value(QStringLiteral("data")).toObject().value(QStringLiteral("id")).toInt();
}

int TeacherDataRepository::copyExamAsDraftById(int examId, const QString &copyTitle)
{
    if (examId <= 0) {
        errorMessage = QStringLiteral("请选择要复制的试卷");
        return -1;
    }

    QUrlQuery params;
    const QString title = copyTitle.trimmed().isEmpty()
            ? QStringLiteral("复制试卷草稿")
            : copyTitle.trimmed();
    params.addQueryItem(QStringLiteral("title"), title);
    if (teacherId > 0) {
        params.addQueryItem(QStringLiteral("createdBy"), QString::number(teacherId));
    }

    const QJsonObject response = requestJson(QStringLiteral("POST"), QStringLiteral("/exams/%1/copy").arg(examId), {}, params);
    if (!response.value(QStringLiteral("success")).toBool()) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("复制试卷失败"));
        return -1;
    }
    errorMessage.clear();
    return response.value(QStringLiteral("data")).toObject().value(QStringLiteral("id")).toInt();
}

bool TeacherDataRepository::publishExam(int paperId, const QStringList &classNames, const QDateTime &startTime, const QDateTime &endTime)
{
    if (paperId <= 0 || classNames.isEmpty()) {
        errorMessage = QStringLiteral("请选择试卷和目标班级");
        return false;
    }

    QJsonArray classes;
    for (const QString &className : classNames) {
        classes.append(className);
    }
    QJsonObject payload;
    payload.insert(QStringLiteral("examId"), paperId);
    payload.insert(QStringLiteral("classNames"), classes);
    payload.insert(QStringLiteral("startTime"), isoDateTime(startTime));
    payload.insert(QStringLiteral("endTime"), isoDateTime(endTime));
    payload.insert(QStringLiteral("status"), QStringLiteral("已发布"));
    if (teacherId > 0) {
        payload.insert(QStringLiteral("createdBy"), QJsonValue::fromVariant(teacherId));
    }

    const QJsonObject response = requestJson(QStringLiteral("POST"), QStringLiteral("/exams/publish"), payload);
    const bool ok = response.value(QStringLiteral("success")).toBool();
    if (!ok) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("发布考试失败"));
    }
    return ok;
}

bool TeacherDataRepository::saveReviewScore(int answerId, double score, const QString &comment)
{
    QJsonObject payload;
    payload.insert(QStringLiteral("answerId"), answerId);
    payload.insert(QStringLiteral("score"), score);
    payload.insert(QStringLiteral("comment"), comment);
    if (teacherId > 0) {
        payload.insert(QStringLiteral("teacherId"), QJsonValue::fromVariant(teacherId));
    }
    const QJsonObject response = requestJson(QStringLiteral("POST"), QStringLiteral("/scores/review"), payload);
    const bool ok = response.value(QStringLiteral("success")).toBool();
    if (!ok) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("保存评分失败"));
    }
    return ok;
}

bool TeacherDataRepository::addTodoItem(const QString &title, const QString &type, const QString &remindTime)
{
    if (teacherId <= 0) {
        errorMessage = QStringLiteral("教师账号未登录");
        return false;
    }
    if (title.trimmed().isEmpty()) {
        errorMessage = QStringLiteral("待办内容不能为空");
        return false;
    }
    if (remindTime.trimmed().isEmpty()) {
        errorMessage = QStringLiteral("提醒时间不能为空");
        return false;
    }

    QJsonObject payload;
    payload.insert(QStringLiteral("teacherId"), QJsonValue::fromVariant(teacherId));
    payload.insert(QStringLiteral("title"), title.trimmed());
    payload.insert(QStringLiteral("type"), type.trimmed().isEmpty() ? QStringLiteral("待办提醒") : type.trimmed());
    payload.insert(QStringLiteral("remindTime"), remindTime.trimmed());

    const QJsonObject response = requestJson(QStringLiteral("POST"), QStringLiteral("/teacher-todos"), payload);
    const bool ok = response.value(QStringLiteral("success")).toBool();
    if (!ok) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("新增待办失败"));
    } else {
        errorMessage.clear();
    }
    return ok;
}

int TeacherDataRepository::scoreForType(const QString &type) const
{
    if (type == QStringLiteral("单选题")) return 3;
    if (type == QStringLiteral("多选题")) return 5;
    if (type == QStringLiteral("填空题")) return 2;
    if (type == QStringLiteral("高数大题")) return 10;
    if (type == QStringLiteral("代码题")) return 15;
    return 3;
}

QVariantMap TeacherDataRepository::rowToMap(const QSqlRecord &record) const
{
    QVariantMap map;
    for (int i = 0; i < record.count(); ++i) {
        map.insert(record.fieldName(i), record.value(i));
    }
    return map;
}
