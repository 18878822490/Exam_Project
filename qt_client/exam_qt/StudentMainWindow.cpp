#include "StudentMainWindow.h"

#include "AppConfig.h"
#include "LoginWindow.h"

#include <QColor>
#include <QDateTime>
#include <QDir>
#include <QEventLoop>
#include <QGuiApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QQmlContext>
#include <QQmlError>
#include <QQuickWidget>
#include <QPrinter>
#include <QRandomGenerator>
#include <QScreen>
#include <QStandardPaths>
#include <QStringList>
#include <QTextDocument>
#include <QTimer>
#include <QUrl>
#include <QUrlQuery>
#include <QWindow>

#include "xlsxdocument.h"

namespace {
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

QVariant firstNonBlankValue(const QVariantMap &row, const QStringList &keys, const QVariant &fallback = {})
{
    for (const QString &key : keys) {
        const QVariant value = row.value(key);
        if (value.isValid() && !value.toString().trimmed().isEmpty()) {
            return value;
        }
    }
    return fallback;
}

QString subjectAccent(const QString &subject)
{
    if (subject.contains(QStringLiteral("高等")) || subject.contains(QStringLiteral("数学"))) {
        return QStringLiteral("#3b82f6");
    }
    if (subject.contains(QStringLiteral("线性"))) {
        return QStringLiteral("#22c55e");
    }
    if (subject.contains(QStringLiteral("概率"))) {
        return QStringLiteral("#a855f7");
    }
    if (subject.contains(QStringLiteral("数据库"))) {
        return QStringLiteral("#ef4444");
    }
    if (subject.contains(QStringLiteral("数据"))) {
        return QStringLiteral("#06b6d4");
    }
    return QStringLiteral("#22c55e");
}

QString subjectIcon(const QString &subject)
{
    if (subject.contains(QStringLiteral("数学")) || subject.contains(QStringLiteral("高数"))) {
        return QStringLiteral("数");
    }
    if (subject.contains(QStringLiteral("线性"))) {
        return QStringLiteral("线");
    }
    if (subject.contains(QStringLiteral("概率"))) {
        return QStringLiteral("概");
    }
    if (subject.contains(QStringLiteral("数据结构"))) {
        return QStringLiteral("构");
    }
    if (subject.contains(QStringLiteral("数据库"))) {
        return QStringLiteral("库");
    }
    if (subject.contains(QStringLiteral("英语"))) {
        return QStringLiteral("英");
    }
    if (subject.contains(QStringLiteral("Java"), Qt::CaseInsensitive)) {
        return QStringLiteral("J");
    }
    if (subject.contains(QStringLiteral("C++"), Qt::CaseInsensitive)) {
        return QStringLiteral("C");
    }
    return subject.isEmpty() ? QStringLiteral("题") : subject.left(1);
}

QString practiceSubjectBucket(const QString &subject)
{
    const QString raw = subject.trimmed();
    const QString lower = raw.toLower();
    if (raw.isEmpty()) {
        return {};
    }
    if (lower.contains(QStringLiteral("codex")) || lower.contains(QStringLiteral("test"))
        || raw.contains(QStringLiteral("测试")) || lower == QStringLiteral("single")
        || lower == QStringLiteral("multiple")) {
        return {};
    }
    if (raw.contains(QStringLiteral("高数")) || raw.contains(QStringLiteral("高等数学"))
        || raw.contains(QStringLiteral("数学")) || lower == QStringLiteral("math")) {
        return QStringLiteral("高数");
    }
    if (raw.contains(QStringLiteral("线性代数")) || raw.contains(QStringLiteral("线代"))) {
        return QStringLiteral("线性代数");
    }
    if (raw.contains(QStringLiteral("数据结构")) || raw.contains(QStringLiteral("算法"))
        || lower.contains(QStringLiteral("data structure"))) {
        return QStringLiteral("数据结构");
    }
    if (raw.contains(QStringLiteral("数据库")) || lower.contains(QStringLiteral("mysql"))
        || lower.contains(QStringLiteral("sql"))) {
        return QStringLiteral("数据库");
    }
    if (lower.contains(QStringLiteral("java"))) {
        return QStringLiteral("Java");
    }
    if (lower.contains(QStringLiteral("c++")) || lower.contains(QStringLiteral("cpp"))) {
        return QStringLiteral("C++");
    }
    if (raw.contains(QStringLiteral("英语")) || lower.contains(QStringLiteral("english"))) {
        return QStringLiteral("英语");
    }
    return raw;
}

bool isPracticeSubjectBucket(const QString &subject)
{
    static const QStringList buckets = {
        QStringLiteral("高数"),
        QStringLiteral("线性代数"),
        QStringLiteral("数据库"),
        QStringLiteral("Java"),
        QStringLiteral("数据结构"),
        QStringLiteral("C++"),
        QStringLiteral("英语")
    };
    return buckets.contains(subject.trimmed(), Qt::CaseInsensitive);
}

bool practiceSubjectMatches(const QString &rawSubject, const QString &selectedSubject)
{
    const QString selected = selectedSubject.trimmed();
    if (selected.isEmpty() || selected == QStringLiteral("全部科目") || selected == QStringLiteral("全部")) {
        return true;
    }
    if (isPracticeSubjectBucket(selected)) {
        return practiceSubjectBucket(rawSubject).compare(selected, Qt::CaseInsensitive) == 0;
    }
    return rawSubject.trimmed().compare(selected, Qt::CaseInsensitive) == 0;
}

QString normalizedQuestionType(const QVariantMap &row)
{
    const QString text = row.value(QStringLiteral("type")).toString().trimmed();
    const QString lower = text.toLower();
    if (lower == QStringLiteral("single") || lower == QStringLiteral("singlechoice")
        || text == QStringLiteral("单选") || text == QStringLiteral("选择题")) {
        return QStringLiteral("单选题");
    }
    if (lower == QStringLiteral("multiple") || lower == QStringLiteral("multiplechoice")
        || lower == QStringLiteral("multi") || text == QStringLiteral("多选")) {
        return QStringLiteral("多选题");
    }
    if (lower == QStringLiteral("judge") || lower == QStringLiteral("truefalse")
        || lower == QStringLiteral("true/false") || text == QStringLiteral("判断")) {
        return QStringLiteral("判断题");
    }
    if (lower == QStringLiteral("blank") || lower == QStringLiteral("fill")
        || text == QStringLiteral("填空")) {
        return QStringLiteral("填空题");
    }
    if (lower == QStringLiteral("program") || lower == QStringLiteral("coding")
        || lower == QStringLiteral("code") || text == QStringLiteral("代码题")) {
        return QStringLiteral("编程题");
    }
    if (lower == QStringLiteral("math") || text == QStringLiteral("高数题")
        || text == QStringLiteral("数学大题") || text == QStringLiteral("高数大题")) {
        return QStringLiteral("编程题");
    }
    return text;
}

QVariantMap practiceQuestionMap(const QVariantMap &row, const QString &selectedSubject)
{
    const QString rawSubject = row.value(QStringLiteral("subject"), selectedSubject).toString();
    const QString bucket = practiceSubjectBucket(rawSubject);
    const QString displaySubject = !bucket.isEmpty() ? bucket : (rawSubject.trimmed().isEmpty() ? QStringLiteral("综合") : rawSubject.trimmed());
    return QVariantMap{
        {"id", row.value(QStringLiteral("question_id"), row.value(QStringLiteral("questionId"), row.value(QStringLiteral("id"))))},
        {"subject", displaySubject},
        {"type", normalizedQuestionType(row)},
        {"content", row.value(QStringLiteral("content"))},
        {"optionA", firstNonBlankValue(row, {QStringLiteral("optionA"), QStringLiteral("option_a"), QStringLiteral("optiona"), QStringLiteral("A"), QStringLiteral("a")})},
        {"optionB", firstNonBlankValue(row, {QStringLiteral("optionB"), QStringLiteral("option_b"), QStringLiteral("optionb"), QStringLiteral("B"), QStringLiteral("b")})},
        {"optionC", firstNonBlankValue(row, {QStringLiteral("optionC"), QStringLiteral("option_c"), QStringLiteral("optionc"), QStringLiteral("C"), QStringLiteral("c")})},
        {"optionD", firstNonBlankValue(row, {QStringLiteral("optionD"), QStringLiteral("option_d"), QStringLiteral("optiond"), QStringLiteral("D"), QStringLiteral("d")})},
        {"answer", row.value(QStringLiteral("answer"), row.value(QStringLiteral("standard_answer")))},
        {"analysis", row.value(QStringLiteral("analysis"))},
        {"difficulty", row.value(QStringLiteral("difficulty"), QStringLiteral("基础"))},
        {"knowledgePoint", row.value(QStringLiteral("knowledgePoint"), row.value(QStringLiteral("knowledge_point")))},
        {"score", row.value(QStringLiteral("score"), 0)}
    };
}
}

StudentMainWindow::StudentMainWindow(qint64 studentId,
                                     const QString &studentName,
                                     const QString &studentNo,
                                     const QString &className,
                                     QWidget *parent)
    : QMainWindow(parent)
    , view(new QQuickWidget(this))
    , studentId(studentId)
    , studentName(studentName.trimmed().isEmpty() ? QStringLiteral("学生") : studentName.trimmed())
    , studentNo(studentNo.trimmed())
    , className(className.trimmed())
{
    studentSettings = QVariantMap{
        {QStringLiteral("noticeEnabled"), true},
        {QStringLiteral("autoSaveEnabled"), true},
        {QStringLiteral("compactMode"), false}
    };

    setWindowTitle(QStringLiteral("智考星考试系统 - 学生端"));
    setWindowFlag(Qt::FramelessWindowHint, true);
    setMinimumSize(920, 620);

    const QRect available = QGuiApplication::primaryScreen() != nullptr
            ? QGuiApplication::primaryScreen()->availableGeometry()
            : QRect(0, 0, 1360, 860);
    const int initialWidth = qBound(920, int(available.width() * 0.92), 1440);
    const int initialHeight = qBound(620, int(available.height() * 0.90), 920);
    resize(initialWidth, initialHeight);
    move(available.center() - rect().center());

    view->setResizeMode(QQuickWidget::SizeRootObjectToView);
    view->setClearColor(QColor(QStringLiteral("#eef3fb")));
    view->rootContext()->setContextProperty(QStringLiteral("studentApi"), this);
    connect(view, &QQuickWidget::statusChanged, this, [this](QQuickWidget::Status status) {
        if (status != QQuickWidget::Error) {
            return;
        }

        QStringList messages;
        for (const QQmlError &error : view->errors()) {
            messages.append(error.toString());
        }
        QMessageBox::critical(this,
                              QStringLiteral("学生端界面加载失败"),
                              messages.isEmpty()
                                      ? QStringLiteral("QML 加载失败，请查看应用输出。")
                                      : messages.join(QLatin1Char('\n')));
    });
    view->setSource(QUrl(QStringLiteral("qrc:/qml/StudentMain.qml")));
    setCentralWidget(view);
}

QVariantMap StudentMainWindow::getStudentProfile()
{
    if (studentId > 0) {
        QVariantMap remote = responseMap(requestJson(QStringLiteral("GET"), QStringLiteral("/users/students/%1").arg(studentId)));
        if (!remote.isEmpty()) {
            studentName = remote.value(QStringLiteral("name"), studentName).toString();
            studentNo = remote.value(QStringLiteral("student_no"), remote.value(QStringLiteral("studentNo"), studentNo)).toString();
            className = remote.value(QStringLiteral("class_name"), remote.value(QStringLiteral("className"), className)).toString();
        }
    }
    if (studentId > 0) {
        QUrlQuery settingsQuery;
        settingsQuery.addQueryItem(QStringLiteral("studentId"), QString::number(studentId));
        QVariantMap remoteSettings = responseMap(requestJson(QStringLiteral("GET"),
                                                             QStringLiteral("/student-settings"),
                                                             {},
                                                             settingsQuery));
        if (!remoteSettings.isEmpty()) {
            studentSettings = remoteSettings;
        }
    }
    return {
        {"id", studentId},
        {"name", studentName},
        {"studentNo", studentNo},
        {"username", studentNo},
        {"className", className},
        {"role", QStringLiteral("学生")},
        {"settings", studentSettings}
    };
}

QVariantList StudentMainWindow::getPublishedExams() const
{
    if (className.isEmpty()) {
        errorMessage = QStringLiteral("当前学生账号未绑定班级，无法查询已发布考试");
        return {};
    }
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("className"), className);
    if (!studentNo.isEmpty()) {
        query.addQueryItem(QStringLiteral("studentNo"), studentNo);
    }
    QVariantList list = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/exams/published"), {}, query));
    QVariantList exams;
    for (const QVariant &value : list) {
        const QVariantMap row = value.toMap();
        const int examId = row.value(QStringLiteral("exam_id"), row.value(QStringLiteral("examId"), row.value(QStringLiteral("id")))).toInt();
        exams.append(QVariantMap{
            {"id", examId},
            {"title", row.value(QStringLiteral("title"), row.value(QStringLiteral("name"), QStringLiteral("未命名考试")))},
            {"subject", row.value(QStringLiteral("subject"), QStringLiteral("综合"))},
            {"duration", row.value(QStringLiteral("duration"), 90)},
            {"totalScore", row.value(QStringLiteral("total_score"), row.value(QStringLiteral("totalScore"), 100))},
            {"status", row.value(QStringLiteral("status"), QStringLiteral("待参加"))},
            {"score", row.value(QStringLiteral("student_score"), row.value(QStringLiteral("studentScore")))},
            {"answerCount", row.value(QStringLiteral("answer_count"), row.value(QStringLiteral("answerCount"), 0))},
            {"pendingReviewCount", row.value(QStringLiteral("pending_review_count"), row.value(QStringLiteral("pendingReviewCount"), 0))},
            {"targetStudentCount", row.value(QStringLiteral("target_student_count"), row.value(QStringLiteral("targetStudentCount"), 0))},
            {"submittedCount", row.value(QStringLiteral("submitted_count"), row.value(QStringLiteral("submittedCount"), 0))},
            {"reviewedStudentCount", row.value(QStringLiteral("reviewed_student_count"), row.value(QStringLiteral("reviewedStudentCount"), 0))},
            {"startTime", row.value(QStringLiteral("start_time"), row.value(QStringLiteral("startTime"), QString()))},
            {"endTime", row.value(QStringLiteral("end_time"), row.value(QStringLiteral("endTime"), QString()))},
            {"className", row.value(QStringLiteral("class_name"), row.value(QStringLiteral("className"), className))}
        });
    }
    if (exams.isEmpty()) {
        errorMessage = QStringLiteral("当前班级暂无已发布考试");
    } else {
        errorMessage.clear();
    }
    return exams;
}

QVariantList StudentMainWindow::getExamQuestions(int examId) const
{
    QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/exams/%1/questions").arg(examId)));
    QVariantList questions;
    for (const QVariant &value : rows) {
        const QVariantMap row = value.toMap();
        questions.append(QVariantMap{
            {"id", row.value(QStringLiteral("question_id"), row.value(QStringLiteral("questionId"), row.value(QStringLiteral("id"))))},
            {"type", normalizedQuestionType(row)},
            {"content", row.value(QStringLiteral("content"))},
            {"optionA", firstNonBlankValue(row, {QStringLiteral("optionA"), QStringLiteral("option_a"), QStringLiteral("optiona"), QStringLiteral("A"), QStringLiteral("a")})},
            {"optionB", firstNonBlankValue(row, {QStringLiteral("optionB"), QStringLiteral("option_b"), QStringLiteral("optionb"), QStringLiteral("B"), QStringLiteral("b")})},
            {"optionC", firstNonBlankValue(row, {QStringLiteral("optionC"), QStringLiteral("option_c"), QStringLiteral("optionc"), QStringLiteral("C"), QStringLiteral("c")})},
            {"optionD", firstNonBlankValue(row, {QStringLiteral("optionD"), QStringLiteral("option_d"), QStringLiteral("optiond"), QStringLiteral("D"), QStringLiteral("d")})},
            {"answer", row.value(QStringLiteral("answer"), row.value(QStringLiteral("standard_answer")))},
            {"analysis", row.value(QStringLiteral("analysis"))},
            {"subject", row.value(QStringLiteral("subject"), QStringLiteral("综合"))},
            {"difficulty", row.value(QStringLiteral("difficulty"), QStringLiteral("基础"))},
            {"knowledgePoint", row.value(QStringLiteral("knowledgePoint"), row.value(QStringLiteral("knowledge_point")))},
            {"score", row.value(QStringLiteral("paper_score"), row.value(QStringLiteral("score"), 0))}
        });
    }
    return questions;
}

QVariantList StudentMainWindow::getPracticeSubjectStats() const
{
    QUrlQuery query;
    if (!studentNo.isEmpty()) {
        query.addQueryItem(QStringLiteral("studentNo"), studentNo);
    }

    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/questions/subject-stats"), {}, query));
    QVariantMap grouped;
    QStringList order = {
        QStringLiteral("高数"),
        QStringLiteral("线性代数"),
        QStringLiteral("数据库"),
        QStringLiteral("Java"),
        QStringLiteral("数据结构"),
        QStringLiteral("C++"),
        QStringLiteral("英语")
    };
    for (const QVariant &value : rows) {
        const QVariantMap rawRow = value.toMap();
        const QString subject = practiceSubjectBucket(rawRow.value(QStringLiteral("subject"), QStringLiteral("综合")).toString());
        if (subject.isEmpty()) {
            continue;
        }
        if (!order.contains(subject)) {
            order.append(subject);
        }
        QVariantMap row = grouped.value(subject).toMap();
        const int total = rawRow.value(QStringLiteral("total_count"), rawRow.value(QStringLiteral("totalCount"), 0)).toInt();
        const int practiced = rawRow.value(QStringLiteral("practiced_count"), rawRow.value(QStringLiteral("practicedCount"), 0)).toInt();
        const int weight = qMax(1, total);
        row[QStringLiteral("totalCount")] = row.value(QStringLiteral("totalCount"), 0).toInt() + total;
        row[QStringLiteral("practicedCount")] = row.value(QStringLiteral("practicedCount"), 0).toInt() + practiced;
        row[QStringLiteral("easyCount")] = row.value(QStringLiteral("easyCount"), 0).toInt() + rawRow.value(QStringLiteral("easy"), 0).toInt();
        row[QStringLiteral("middleCount")] = row.value(QStringLiteral("middleCount"), 0).toInt() + rawRow.value(QStringLiteral("middle"), 0).toInt();
        row[QStringLiteral("hardCount")] = row.value(QStringLiteral("hardCount"), 0).toInt() + rawRow.value(QStringLiteral("hard"), 0).toInt();
        row[QStringLiteral("progressSum")] = row.value(QStringLiteral("progressSum"), 0).toInt() + rawRow.value(QStringLiteral("progress"), 0).toInt() * weight;
        row[QStringLiteral("accuracySum")] = row.value(QStringLiteral("accuracySum"), 0).toInt() + rawRow.value(QStringLiteral("accuracy"), 0).toInt() * weight;
        row[QStringLiteral("weight")] = row.value(QStringLiteral("weight"), 0).toInt() + weight;
        grouped.insert(subject, row);
    }

    QVariantList subjects;
    for (const QString &subject : order) {
        const QVariantMap row = grouped.value(subject).toMap();
        if (row.isEmpty()) {
            continue;
        }
        const int total = row.value(QStringLiteral("totalCount"), 0).toInt();
        const int easy = row.value(QStringLiteral("easyCount"), 0).toInt();
        const int middle = row.value(QStringLiteral("middleCount"), 0).toInt();
        const int hard = row.value(QStringLiteral("hardCount"), 0).toInt();
        const int difficultyTotal = qMax(1, easy + middle + hard);
        const int weight = qMax(1, row.value(QStringLiteral("weight"), 0).toInt());
        subjects.append(QVariantMap{
            {"name", subject},
            {"icon", subjectIcon(subject)},
            {"progress", row.value(QStringLiteral("progressSum"), 0).toInt() / weight},
            {"accuracy", row.value(QStringLiteral("accuracySum"), 0).toInt() / weight},
            {"easy", int(easy * 100.0 / difficultyTotal)},
            {"middle", int(middle * 100.0 / difficultyTotal)},
            {"hard", int(hard * 100.0 / difficultyTotal)},
            {"totalCount", total},
            {"practicedCount", row.value(QStringLiteral("practicedCount"), 0).toInt()},
            {"color", subjectAccent(subject)}
        });
    }
    if (subjects.isEmpty()) {
        errorMessage = QStringLiteral("题库暂无科目数据");
    } else {
        errorMessage.clear();
    }
    return subjects;
}

QVariantList StudentMainWindow::getPracticeQuestions(const QString &type,
                                                     const QString &difficulty,
                                                     const QString &subject) const
{
    QUrlQuery query;
    if (!type.trimmed().isEmpty() && type != QStringLiteral("全部题型")) {
        query.addQueryItem(QStringLiteral("type"), type.trimmed());
    }
    if (!difficulty.trimmed().isEmpty() && difficulty != QStringLiteral("全部难度")) {
        query.addQueryItem(QStringLiteral("difficulty"), difficulty.trimmed());
    }
    const QString subjectName = subject.trimmed();
    const bool selectedBucket = isPracticeSubjectBucket(subjectName);
    if (!subjectName.isEmpty()
        && subjectName != QStringLiteral("全部科目")
        && subjectName != QStringLiteral("全部")
        && !selectedBucket) {
        query.addQueryItem(QStringLiteral("subject"), subjectName);
    }

    QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/questions"), {}, query));
    QVariantList questions;
    for (const QVariant &value : rows) {
        const QVariantMap row = value.toMap();
        const QString rawSubject = row.value(QStringLiteral("subject")).toString();
        if (practiceSubjectBucket(rawSubject).isEmpty() || !practiceSubjectMatches(rawSubject, subjectName)) {
            continue;
        }
        questions.append(practiceQuestionMap(row, subjectName));
    }

    return questions;
}

QVariantList StudentMainWindow::getRandomPracticeQuestions(const QString &type,
                                                           const QString &difficulty,
                                                           const QString &subject,
                                                           int count) const
{
    QUrlQuery query;
    if (!type.trimmed().isEmpty() && type != QStringLiteral("全部题型")) {
        query.addQueryItem(QStringLiteral("type"), type.trimmed());
    }
    if (!difficulty.trimmed().isEmpty() && difficulty != QStringLiteral("全部难度")) {
        query.addQueryItem(QStringLiteral("difficulty"), difficulty.trimmed());
    }
    const QString subjectName = subject.trimmed();
    const bool selectedBucket = isPracticeSubjectBucket(subjectName);
    const bool clientSideSubjectFilter = selectedBucket
            || subjectName.isEmpty()
            || subjectName == QStringLiteral("全部科目")
            || subjectName == QStringLiteral("全部");
    if (!subjectName.isEmpty()
        && subjectName != QStringLiteral("全部科目")
        && subjectName != QStringLiteral("全部")
        && !selectedBucket) {
        query.addQueryItem(QStringLiteral("subject"), subjectName);
    }
    const int safeCount = qBound(1, count, 100);
    if (!clientSideSubjectFilter) {
        query.addQueryItem(QStringLiteral("count"), QString::number(safeCount));
    }

    QVariantList rows = responseList(requestJson(QStringLiteral("GET"),
                                                 clientSideSubjectFilter ? QStringLiteral("/questions") : QStringLiteral("/questions/random"),
                                                 {}, query));
    QVariantList questions;
    for (const QVariant &value : rows) {
        const QVariantMap row = value.toMap();
        const QString rawSubject = row.value(QStringLiteral("subject")).toString();
        if (practiceSubjectBucket(rawSubject).isEmpty() || !practiceSubjectMatches(rawSubject, subjectName)) {
            continue;
        }
        questions.append(practiceQuestionMap(row, subjectName));
    }

    for (int i = questions.size() - 1; i > 0; --i) {
        questions.swapItemsAt(i, QRandomGenerator::global()->bounded(i + 1));
    }
    while (questions.size() > safeCount) {
        questions.removeLast();
    }

    if (questions.isEmpty()) {
        errorMessage = QStringLiteral("当前条件下没有可抽取的题目");
    } else {
        errorMessage.clear();
    }
    return questions;
}

bool StudentMainWindow::savePracticeAnswer(int questionId,
                                           const QString &answer,
                                           bool correct,
                                           const QString &practiceMode)
{
    if (questionId <= 0) {
        errorMessage = QStringLiteral("题目ID不能为空");
        return false;
    }
    if (studentNo.isEmpty()) {
        errorMessage = QStringLiteral("当前学生账号缺少学号，无法保存练习记录");
        return false;
    }
    if (answer.trimmed().isEmpty()) {
        errorMessage = QStringLiteral("请先作答");
        return false;
    }

    QJsonObject payload;
    payload.insert(QStringLiteral("studentId"), QJsonValue::fromVariant(studentId));
    payload.insert(QStringLiteral("studentName"), studentName);
    payload.insert(QStringLiteral("studentNo"), studentNo);
    payload.insert(QStringLiteral("questionId"), questionId);
    payload.insert(QStringLiteral("answer"), answer.trimmed());
    payload.insert(QStringLiteral("correct"), correct);
    payload.insert(QStringLiteral("practiceMode"), practiceMode.trimmed().isEmpty() ? QStringLiteral("题库练习") : practiceMode.trimmed());

    const QJsonObject response = requestJson(QStringLiteral("POST"), QStringLiteral("/questions/practice-record"), payload);
    const bool ok = response.value(QStringLiteral("success")).toBool();
    if (!ok) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("练习记录保存失败"));
    } else {
        errorMessage.clear();
    }
    return ok;
}

QVariantMap StudentMainWindow::getScoreReport(int examId) const
{
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("examId"), QString::number(examId));
    query.addQueryItem(QStringLiteral("className"), className);
    if (!studentNo.isEmpty()) {
        query.addQueryItem(QStringLiteral("studentNo"), studentNo);
    }
    QVariantMap report = responseMap(requestJson(QStringLiteral("GET"), QStringLiteral("/scores/report"), {}, query));
    if (report.isEmpty()) {
        errorMessage = QStringLiteral("暂无该考试的成绩报告");
        return {};
    }

    QVariantMap summary = report.value(QStringLiteral("summary")).toMap();
    if (!summary.contains(QStringLiteral("average"))) {
        summary.insert(QStringLiteral("average"), summary.value(QStringLiteral("average_score"), 0));
    }
    if (!summary.contains(QStringLiteral("maxScore"))) {
        summary.insert(QStringLiteral("maxScore"), summary.value(QStringLiteral("highest_score"), 0));
    }
    if (!summary.contains(QStringLiteral("minScore"))) {
        summary.insert(QStringLiteral("minScore"), summary.value(QStringLiteral("lowest_score"), 0));
    }
    if (!summary.contains(QStringLiteral("passRate"))) {
        summary.insert(QStringLiteral("passRate"), summary.value(QStringLiteral("pass_rate"), 0));
    }
    report.insert(QStringLiteral("summary"), summary);
    report.insert(QStringLiteral("reviewStatus"),
                  report.value(QStringLiteral("reviewStatus"), report.value(QStringLiteral("review_status"), QStringLiteral("暂无提交"))));
    report.insert(QStringLiteral("pendingCount"),
                  report.value(QStringLiteral("pendingCount"), report.value(QStringLiteral("pending_count"), 0)));
    report.insert(QStringLiteral("answerCount"),
                  report.value(QStringLiteral("answerCount"), report.value(QStringLiteral("answer_count"), 0)));

    QVariantList scores;
    int rank = 1;
    for (const QVariant &value : report.value(QStringLiteral("scores")).toList()) {
        QVariantMap row = value.toMap();
        row.insert(QStringLiteral("rank"), rank++);
        if (!row.contains(QStringLiteral("studentName"))) {
            row.insert(QStringLiteral("studentName"), row.value(QStringLiteral("student_name")));
        }
        if (!row.contains(QStringLiteral("studentNo"))) {
            row.insert(QStringLiteral("studentNo"), row.value(QStringLiteral("student_no")));
        }
        if (!row.contains(QStringLiteral("totalScore"))) {
            row.insert(QStringLiteral("totalScore"), row.value(QStringLiteral("total_score"), 0));
        }
        scores.append(row);
    }
    report.insert(QStringLiteral("scores"), scores);

    QVariantList analysis;
    int index = 1;
    for (const QVariant &value : report.value(QStringLiteral("questionAnalysis")).toList()) {
        QVariantMap row = value.toMap();
        row.insert(QStringLiteral("index"), row.value(QStringLiteral("index"), QStringLiteral("第%1题").arg(index++)));
        row.insert(QStringLiteral("average"), row.value(QStringLiteral("average"), row.value(QStringLiteral("average_score"), 0)));
        row.insert(QStringLiteral("full"), row.value(QStringLiteral("full"), row.value(QStringLiteral("full_score"), 0)));
        row.insert(QStringLiteral("low"), row.value(QStringLiteral("low"), row.value(QStringLiteral("low_score"), 0)).toInt() != 0);
        analysis.append(row);
    }
    report.insert(QStringLiteral("questionAnalysis"), analysis);

    QVariantList typeBreakdown;
    for (const QVariant &value : report.value(QStringLiteral("typeBreakdown")).toList()) {
        QVariantMap row = value.toMap();
        row.insert(QStringLiteral("type"), normalizedQuestionType(row));
        row.insert(QStringLiteral("fullScore"), row.value(QStringLiteral("fullScore"), row.value(QStringLiteral("full_score"), 0)));
        row.insert(QStringLiteral("score"), row.value(QStringLiteral("score"), 0));
        row.insert(QStringLiteral("deduction"), row.value(QStringLiteral("deduction"), row.value(QStringLiteral("deduct"), 0)));
        typeBreakdown.append(row);
    }
    report.insert(QStringLiteral("typeBreakdown"), typeBreakdown);

    QVariantList weakKnowledge;
    for (const QVariant &value : report.value(QStringLiteral("weakKnowledgePoints")).toList()) {
        QVariantMap row = value.toMap();
        row.insert(QStringLiteral("knowledgePoint"), row.value(QStringLiteral("knowledgePoint"), row.value(QStringLiteral("name"))));
        row.insert(QStringLiteral("deduction"), row.value(QStringLiteral("deduction"), row.value(QStringLiteral("lost"), 0)));
        weakKnowledge.append(row);
    }
    report.insert(QStringLiteral("weakKnowledgePoints"), weakKnowledge);

    QVariantList deductionDetails;
    for (const QVariant &value : report.value(QStringLiteral("deductionDetails")).toList()) {
        QVariantMap row = value.toMap();
        row.insert(QStringLiteral("type"), normalizedQuestionType(row));
        row.insert(QStringLiteral("questionIndex"), row.value(QStringLiteral("questionIndex"), row.value(QStringLiteral("question_index"))));
        row.insert(QStringLiteral("index"), row.value(QStringLiteral("index"), QStringLiteral("第%1题").arg(row.value(QStringLiteral("questionIndex")).toInt())));
        row.insert(QStringLiteral("fullScore"), row.value(QStringLiteral("fullScore"), row.value(QStringLiteral("full_score"), 0)));
        row.insert(QStringLiteral("questionScore"), row.value(QStringLiteral("questionScore"), row.value(QStringLiteral("fullScore"), 0)));
        row.insert(QStringLiteral("knowledgePoint"), row.value(QStringLiteral("knowledgePoint"), row.value(QStringLiteral("knowledge_point"))));
        row.insert(QStringLiteral("standardAnswer"), row.value(QStringLiteral("standardAnswer"), row.value(QStringLiteral("standard_answer"))));
        deductionDetails.append(row);
    }
    report.insert(QStringLiteral("deductionDetails"), deductionDetails);
    report.insert(QStringLiteral("answerDetails"), deductionDetails);
    report.insert(QStringLiteral("personalAnswers"), deductionDetails);

    return report;
}

QVariantList StudentMainWindow::getScoreHistory(const QString &subject) const
{
    if (studentNo.isEmpty()) {
        errorMessage = QStringLiteral("当前学生账号缺少学号，无法查询成绩历史");
        return {};
    }

    QUrlQuery query;
    query.addQueryItem(QStringLiteral("studentNo"), studentNo);
    const QString normalizedSubject = subject.trimmed();
    if (!normalizedSubject.isEmpty() && normalizedSubject != QStringLiteral("全部科目")) {
        query.addQueryItem(QStringLiteral("subject"), normalizedSubject);
    }

    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/scores/student-history"), {}, query));
    QVariantList history;
    for (const QVariant &value : rows) {
        const QVariantMap row = value.toMap();
        const double score = row.value(QStringLiteral("total_score"), row.value(QStringLiteral("totalScore"), 0)).toDouble();
        const double fullScore = row.value(QStringLiteral("full_score"), row.value(QStringLiteral("fullScore"), 100)).toDouble();
        const double percent = fullScore > 0 ? score / fullScore : 0;
        const int rank = row.value(QStringLiteral("class_rank"), row.value(QStringLiteral("classRank"), 0)).toInt();
        const int classCount = row.value(QStringLiteral("class_student_count"), row.value(QStringLiteral("classStudentCount"), 0)).toInt();
        const QString subjectName = row.value(QStringLiteral("subject"), QStringLiteral("综合")).toString();
        const QString rankText = rank > 0
                ? (classCount > 0
                   ? QStringLiteral("第 %1 / %2").arg(rank).arg(classCount)
                   : QStringLiteral("第 %1").arg(rank))
                : QStringLiteral("--");

        QString level = QStringLiteral("需加强");
        if (percent >= 0.9) {
            level = QStringLiteral("优秀");
        } else if (percent >= 0.8) {
            level = QStringLiteral("良好");
        } else if (percent >= 0.6) {
            level = QStringLiteral("合格");
        }

        history.append(QVariantMap{
            {"id", row.value(QStringLiteral("exam_id"), row.value(QStringLiteral("examId")))},
            {"examId", row.value(QStringLiteral("exam_id"), row.value(QStringLiteral("examId")))},
            {"title", row.value(QStringLiteral("exam_title"), row.value(QStringLiteral("examTitle"), QStringLiteral("未命名考试")))},
            {"name", row.value(QStringLiteral("exam_title"), row.value(QStringLiteral("examTitle"), QStringLiteral("未命名考试")))},
            {"subject", subjectName},
            {"score", score},
            {"totalScore", score},
            {"full", fullScore > 0 ? fullScore : 100},
            {"fullScore", fullScore > 0 ? fullScore : 100},
            {"classAverage", row.value(QStringLiteral("class_average"), row.value(QStringLiteral("classAverage"), 0)).toDouble()},
            {"classRank", rank},
            {"classStudentCount", classCount},
            {"rank", rankText},
            {"date", row.value(QStringLiteral("exam_date"), row.value(QStringLiteral("examDate")))},
            {"trendLabel", row.value(QStringLiteral("trend_label"), row.value(QStringLiteral("trendLabel")))},
            {"className", row.value(QStringLiteral("class_name"), row.value(QStringLiteral("className"), className))},
            {"level", level},
            {"accent", subjectAccent(subjectName)}
        });
    }

    if (history.isEmpty()) {
        errorMessage = QStringLiteral("暂无成绩历史");
    } else {
        errorMessage.clear();
    }
    return history;
}

QVariantList StudentMainWindow::getWrongQuestions() const
{
    if (studentNo.isEmpty()) {
        errorMessage = QStringLiteral("当前学生账号缺少学号，无法查询错题本");
        return {};
    }

    QUrlQuery query;
    query.addQueryItem(QStringLiteral("studentNo"), studentNo);
    const QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/scores/wrong-questions"), {}, query));
    QVariantList questions;
    for (const QVariant &value : rows) {
        const QVariantMap row = value.toMap();
        questions.append(QVariantMap{
            {"id", row.value(QStringLiteral("question_id"), row.value(QStringLiteral("questionId")))},
            {"answerId", row.value(QStringLiteral("answer_id"), row.value(QStringLiteral("answerId")))},
            {"examId", row.value(QStringLiteral("exam_id"), row.value(QStringLiteral("examId")))},
            {"source", row.value(QStringLiteral("exam_title"), row.value(QStringLiteral("examTitle"), QStringLiteral("考试错题")))},
            {"sourceType", row.value(QStringLiteral("source_type"), row.value(QStringLiteral("sourceType"), QStringLiteral("exam")))},
            {"subject", row.value(QStringLiteral("subject"), QStringLiteral("综合"))},
            {"type", normalizedQuestionType(row)},
            {"difficulty", row.value(QStringLiteral("difficulty"), QStringLiteral("中等"))},
            {"content", row.value(QStringLiteral("content"))},
            {"optionA", firstNonBlankValue(row, {QStringLiteral("optionA"), QStringLiteral("option_a"), QStringLiteral("optiona"), QStringLiteral("A"), QStringLiteral("a")})},
            {"optionB", firstNonBlankValue(row, {QStringLiteral("optionB"), QStringLiteral("option_b"), QStringLiteral("optionb"), QStringLiteral("B"), QStringLiteral("b")})},
            {"optionC", firstNonBlankValue(row, {QStringLiteral("optionC"), QStringLiteral("option_c"), QStringLiteral("optionc"), QStringLiteral("C"), QStringLiteral("c")})},
            {"optionD", firstNonBlankValue(row, {QStringLiteral("optionD"), QStringLiteral("option_d"), QStringLiteral("optiond"), QStringLiteral("D"), QStringLiteral("d")})},
            {"wrongAnswer", row.value(QStringLiteral("wrong_answer"), row.value(QStringLiteral("wrongAnswer")))},
            {"answer", row.value(QStringLiteral("standard_answer"), row.value(QStringLiteral("standardAnswer")))},
            {"analysis", row.value(QStringLiteral("analysis"))},
            {"knowledge", row.value(QStringLiteral("knowledge_point"), row.value(QStringLiteral("knowledgePoint")))},
            {"score", row.value(QStringLiteral("score"), 0)},
            {"fullScore", row.value(QStringLiteral("full_score"), row.value(QStringLiteral("fullScore"), 0))},
            {"deduction", row.value(QStringLiteral("deduction"), 0)},
            {"comment", row.value(QStringLiteral("comment"))},
            {"reviewStatus", row.value(QStringLiteral("review_status"), row.value(QStringLiteral("reviewStatus")))},
            {"correctionAnswer", row.value(QStringLiteral("correction_answer"), row.value(QStringLiteral("correctionAnswer")))},
            {"correctionReason", row.value(QStringLiteral("correction_reason"), row.value(QStringLiteral("correctionReason")))},
            {"correctionSummary", row.value(QStringLiteral("correction_summary"), row.value(QStringLiteral("correctionSummary")))},
            {"correctionStatus", row.value(QStringLiteral("correction_status"), row.value(QStringLiteral("correctionStatus"), QStringLiteral("未订正")))},
            {"correctedTime", row.value(QStringLiteral("corrected_time"), row.value(QStringLiteral("correctedTime")))}
        });
    }

    if (questions.isEmpty()) {
        errorMessage = QStringLiteral("暂无错题记录");
    } else {
        errorMessage.clear();
    }
    return questions;
}

bool StudentMainWindow::saveWrongQuestionCorrection(int answerId,
                                                    const QString &sourceType,
                                                    const QString &correctionAnswer,
                                                    const QString &errorReason,
                                                    const QString &knowledgeSummary)
{
    if (answerId <= 0) {
        errorMessage = QStringLiteral("请选择要订正的错题");
        return false;
    }
    if (studentNo.isEmpty()) {
        errorMessage = QStringLiteral("当前学生账号缺少学号，无法保存订正");
        return false;
    }

    QJsonObject payload;
    payload.insert(QStringLiteral("answerId"), answerId);
    payload.insert(QStringLiteral("sourceType"), sourceType.trimmed().isEmpty() ? QStringLiteral("exam") : sourceType.trimmed());
    payload.insert(QStringLiteral("studentNo"), studentNo);
    payload.insert(QStringLiteral("correctionAnswer"), correctionAnswer.trimmed());
    payload.insert(QStringLiteral("errorReason"), errorReason.trimmed());
    payload.insert(QStringLiteral("knowledgeSummary"), knowledgeSummary.trimmed());

    const QJsonObject response = requestJson(QStringLiteral("POST"), QStringLiteral("/scores/wrong-questions/correction"), payload);
    const bool ok = response.value(QStringLiteral("success")).toBool();
    if (!ok) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("订正保存失败，请稍后重试"));
    } else {
        errorMessage.clear();
    }
    return ok;
}

bool StudentMainWindow::submitExam(int examId, const QVariantMap &answers)
{
    if (examId <= 0) {
        errorMessage = QStringLiteral("请选择要提交的考试");
        return false;
    }
    if (studentNo.isEmpty()) {
        errorMessage = QStringLiteral("当前学生账号缺少学号，无法提交考试");
        return false;
    }

    QJsonObject answerObject;
    for (auto it = answers.constBegin(); it != answers.constEnd(); ++it) {
        answerObject.insert(it.key(), QJsonValue::fromVariant(it.value()));
    }

    QJsonObject payload;
    payload.insert(QStringLiteral("examId"), examId);
    payload.insert(QStringLiteral("studentId"), QJsonValue::fromVariant(studentId));
    payload.insert(QStringLiteral("studentName"), studentName);
    payload.insert(QStringLiteral("studentNo"), studentNo);
    payload.insert(QStringLiteral("className"), className);
    payload.insert(QStringLiteral("answers"), answerObject);

    const QJsonObject response = requestJson(QStringLiteral("POST"), QStringLiteral("/scores/submit"), payload);
    const bool ok = response.value(QStringLiteral("success")).toBool();
    if (!ok) {
        errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("提交失败，请稍后重试"));
    }
    return ok;
}

QString StudentMainWindow::exportScoreReportExcel(int examId) const
{
    if (examId <= 0) {
        errorMessage = QStringLiteral("请选择要导出的考试");
        return {};
    }

    const QVariantMap report = getScoreReport(examId);
    const QVariantMap summary = report.value(QStringLiteral("summary")).toMap();
    const QVariantList scores = report.value(QStringLiteral("scores")).toList();

    const QString baseDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
            + QStringLiteral("/ExamReports");
    QDir().mkpath(baseDir);
    const QString path = baseDir + QStringLiteral("/成绩报告_%1_%2.xlsx")
            .arg(studentNo, QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMdd_HHmmss")));

    QXlsx::Document xlsx;
    xlsx.write(QStringLiteral("A1"), QStringLiteral("学生成绩报告"));
    xlsx.write(QStringLiteral("A3"), QStringLiteral("姓名"));
    xlsx.write(QStringLiteral("B3"), studentName);
    xlsx.write(QStringLiteral("C3"), QStringLiteral("学号"));
    xlsx.write(QStringLiteral("D3"), studentNo);
    xlsx.write(QStringLiteral("A4"), QStringLiteral("班级"));
    xlsx.write(QStringLiteral("B4"), className);
    xlsx.write(QStringLiteral("C4"), QStringLiteral("考试ID"));
    xlsx.write(QStringLiteral("D4"), examId);
    xlsx.write(QStringLiteral("A6"), QStringLiteral("班级均分"));
    xlsx.write(QStringLiteral("B6"), summary.value(QStringLiteral("average"), 0));
    xlsx.write(QStringLiteral("C6"), QStringLiteral("最高分"));
    xlsx.write(QStringLiteral("D6"), summary.value(QStringLiteral("maxScore"), 0));
    xlsx.write(QStringLiteral("E6"), QStringLiteral("通过率"));
    xlsx.write(QStringLiteral("F6"), QStringLiteral("%1%").arg(summary.value(QStringLiteral("passRate"), 0).toString()));

    xlsx.write(QStringLiteral("A8"), QStringLiteral("排名"));
    xlsx.write(QStringLiteral("B8"), QStringLiteral("姓名"));
    xlsx.write(QStringLiteral("C8"), QStringLiteral("学号"));
    xlsx.write(QStringLiteral("D8"), QStringLiteral("班级"));
    xlsx.write(QStringLiteral("E8"), QStringLiteral("总分"));

    int rowNumber = 9;
    for (const QVariant &value : scores) {
        const QVariantMap row = value.toMap();
        xlsx.write(rowNumber, 1, row.value(QStringLiteral("rank"), rowNumber - 8));
        xlsx.write(rowNumber, 2, row.value(QStringLiteral("studentName"), studentName));
        xlsx.write(rowNumber, 3, row.value(QStringLiteral("studentNo"), studentNo));
        xlsx.write(rowNumber, 4, row.value(QStringLiteral("className"), className));
        xlsx.write(rowNumber, 5, row.value(QStringLiteral("totalScore"), 0));
        ++rowNumber;
    }

    if (!xlsx.saveAs(path)) {
        errorMessage = QStringLiteral("Excel 导出失败，请检查文档目录权限");
        return {};
    }

    errorMessage.clear();
    return path;
}

QString StudentMainWindow::exportScoreHistoryExcel(const QString &subject) const
{
    const QVariantList history = getScoreHistory(subject);
    if (history.isEmpty()) {
        errorMessage = QStringLiteral("暂无可导出的科目成绩");
        return {};
    }

    QString safeSubject = subject.trimmed().isEmpty() || subject.trimmed() == QStringLiteral("全部科目")
            ? QStringLiteral("全部科目")
            : subject.trimmed();
    for (const QChar ch : QStringLiteral("\\/:*?\"<>|")) {
        safeSubject.replace(ch, QLatin1Char('_'));
    }

    const QString baseDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
            + QStringLiteral("/ExamReports");
    QDir().mkpath(baseDir);
    const QString path = baseDir + QStringLiteral("/科目成绩_%1_%2_%3.xlsx")
            .arg(safeSubject, studentNo, QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMdd_HHmmss")));

    QXlsx::Document xlsx;
    xlsx.write(QStringLiteral("A1"), QStringLiteral("学生科目成绩历史"));
    xlsx.write(QStringLiteral("A3"), QStringLiteral("姓名"));
    xlsx.write(QStringLiteral("B3"), studentName);
    xlsx.write(QStringLiteral("C3"), QStringLiteral("学号"));
    xlsx.write(QStringLiteral("D3"), studentNo);
    xlsx.write(QStringLiteral("E3"), QStringLiteral("科目"));
    xlsx.write(QStringLiteral("F3"), safeSubject);

    xlsx.write(QStringLiteral("A5"), QStringLiteral("考试名称"));
    xlsx.write(QStringLiteral("B5"), QStringLiteral("科目"));
    xlsx.write(QStringLiteral("C5"), QStringLiteral("考试日期"));
    xlsx.write(QStringLiteral("D5"), QStringLiteral("得分"));
    xlsx.write(QStringLiteral("E5"), QStringLiteral("满分"));
    xlsx.write(QStringLiteral("F5"), QStringLiteral("班级均分"));
    xlsx.write(QStringLiteral("G5"), QStringLiteral("班级排名"));
    xlsx.write(QStringLiteral("H5"), QStringLiteral("评级"));

    int rowNumber = 6;
    for (const QVariant &value : history) {
        const QVariantMap row = value.toMap();
        xlsx.write(rowNumber, 1, row.value(QStringLiteral("title")));
        xlsx.write(rowNumber, 2, row.value(QStringLiteral("subject")));
        xlsx.write(rowNumber, 3, row.value(QStringLiteral("date")));
        xlsx.write(rowNumber, 4, row.value(QStringLiteral("score")));
        xlsx.write(rowNumber, 5, row.value(QStringLiteral("full")));
        xlsx.write(rowNumber, 6, row.value(QStringLiteral("classAverage")));
        xlsx.write(rowNumber, 7, row.value(QStringLiteral("rank")));
        xlsx.write(rowNumber, 8, row.value(QStringLiteral("level")));
        ++rowNumber;
    }

    if (!xlsx.saveAs(path)) {
        errorMessage = QStringLiteral("Excel 导出失败，请检查文档目录权限");
        return {};
    }

    errorMessage.clear();
    return path;
}

QString StudentMainWindow::printScoreReportPdf(int examId) const
{
    if (examId <= 0) {
        errorMessage = QStringLiteral("请选择要打印的考试");
        return {};
    }

    const QVariantMap report = getScoreReport(examId);
    const QVariantMap summary = report.value(QStringLiteral("summary")).toMap();
    const QVariantList scores = report.value(QStringLiteral("scores")).toList();

    const QString baseDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
            + QStringLiteral("/ExamReports");
    QDir().mkpath(baseDir);
    const QString path = baseDir + QStringLiteral("/成绩报告_%1_%2.pdf")
            .arg(studentNo, QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMdd_HHmmss")));

    QString rowsHtml;
    for (const QVariant &value : scores) {
        const QVariantMap row = value.toMap();
        rowsHtml += QStringLiteral("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td></tr>")
                .arg(row.value(QStringLiteral("rank"), 1).toString().toHtmlEscaped(),
                     row.value(QStringLiteral("studentName"), studentName).toString().toHtmlEscaped(),
                     row.value(QStringLiteral("studentNo"), studentNo).toString().toHtmlEscaped(),
                     row.value(QStringLiteral("className"), className).toString().toHtmlEscaped(),
                     row.value(QStringLiteral("totalScore"), 0).toString().toHtmlEscaped());
    }

    const QString html = QStringLiteral(
        "<html><head><meta charset='utf-8'>"
        "<style>body{font-family:'Microsoft YaHei',sans-serif;color:#111827;}"
        "h1{font-size:24px;} .meta{color:#64748b;margin-bottom:18px;}"
        ".card{border:1px solid #e5e7eb;border-radius:12px;padding:14px;margin:12px 0;}"
        "table{width:100%;border-collapse:collapse;margin-top:12px;}"
        "th,td{border:1px solid #e5e7eb;padding:8px;text-align:left;font-size:12px;}"
        "th{background:#f8fafc;}</style></head><body>"
        "<h1>学生成绩报告</h1>"
        "<div class='meta'>姓名：%1　学号：%2　班级：%3　考试ID：%4</div>"
        "<div class='card'>班级均分：%5　最高分：%6　通过率：%7%</div>"
        "<table><tr><th>排名</th><th>姓名</th><th>学号</th><th>班级</th><th>总分</th></tr>%8</table>"
        "</body></html>")
            .arg(studentName.toHtmlEscaped(),
                 studentNo.toHtmlEscaped(),
                 className.toHtmlEscaped(),
                 QString::number(examId),
                 summary.value(QStringLiteral("average"), 0).toString().toHtmlEscaped(),
                 summary.value(QStringLiteral("maxScore"), 0).toString().toHtmlEscaped(),
                 summary.value(QStringLiteral("passRate"), 0).toString().toHtmlEscaped(),
                 rowsHtml);

    QTextDocument document;
    document.setHtml(html);
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(path);
    document.print(&printer);

    errorMessage.clear();
    return path;
}

bool StudentMainWindow::updateProfile(const QVariantMap &profileData)
{
    const QString nextName = profileData.value(QStringLiteral("name"), studentName).toString().trimmed();
    const QString nextStudentNo = profileData.value(QStringLiteral("studentNo"), studentNo).toString().trimmed();
    const QString nextClassName = profileData.value(QStringLiteral("className"), className).toString().trimmed();
    if (nextName.isEmpty() || nextStudentNo.isEmpty() || nextClassName.isEmpty()) {
        errorMessage = QStringLiteral("姓名、学号和班级不能为空");
        return false;
    }

    if (studentId > 0) {
        QJsonObject payload;
        payload.insert(QStringLiteral("name"), nextName);
        payload.insert(QStringLiteral("studentNo"), nextStudentNo);
        payload.insert(QStringLiteral("className"), nextClassName);
        if (profileData.contains(QStringLiteral("major"))) {
            payload.insert(QStringLiteral("major"), profileData.value(QStringLiteral("major")).toString());
        }
        const QJsonObject response = requestJson(QStringLiteral("PUT"), QStringLiteral("/users/students/%1").arg(studentId), payload);
        if (!response.value(QStringLiteral("success")).toBool()) {
            errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("个人信息保存失败"));
            return false;
        }
    }

    studentName = nextName;
    studentNo = nextStudentNo;
    className = nextClassName;
    errorMessage.clear();
    return true;
}

bool StudentMainWindow::changePassword(const QString &oldPassword, const QString &newPassword)
{
    if (oldPassword.isEmpty()) {
        errorMessage = QStringLiteral("请输入原密码");
        return false;
    }
    if (newPassword.length() < 6) {
        errorMessage = QStringLiteral("新密码至少 6 位");
        return false;
    }

    if (studentId > 0) {
        QJsonObject payload;
        payload.insert(QStringLiteral("oldPassword"), oldPassword);
        payload.insert(QStringLiteral("newPassword"), newPassword);
        const QJsonObject response = requestJson(QStringLiteral("POST"), QStringLiteral("/users/STUDENT/%1/password").arg(studentId), payload);
        if (!response.value(QStringLiteral("success")).toBool()) {
            errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("密码修改失败"));
            return false;
        }
    }

    errorMessage.clear();
    return true;
}

bool StudentMainWindow::saveSettings(const QVariantMap &settings)
{
    if (settings.isEmpty()) {
        errorMessage = QStringLiteral("设置内容不能为空");
        return false;
    }
    if (studentId > 0) {
        QUrlQuery query;
        query.addQueryItem(QStringLiteral("studentId"), QString::number(studentId));
        const QJsonObject response = requestJson(QStringLiteral("PUT"),
                                                 QStringLiteral("/student-settings"),
                                                 QJsonObject::fromVariantMap(settings),
                                                 query);
        if (!response.value(QStringLiteral("success")).toBool()) {
            errorMessage = response.value(QStringLiteral("message")).toString(QStringLiteral("考试设置保存失败"));
            return false;
        }
        const QVariantMap remoteSettings = responseMap(response);
        studentSettings = remoteSettings.isEmpty() ? settings : remoteSettings;
        errorMessage.clear();
        return true;
    }
    studentSettings = settings;
    errorMessage.clear();
    return true;
}

QString StudentMainWindow::lastError() const
{
    return errorMessage;
}

void StudentMainWindow::minimizeWindow()
{
    showMinimized();
}

void StudentMainWindow::toggleMaximizeWindow()
{
    isMaximized() ? showNormal() : showMaximized();
}

void StudentMainWindow::closeWindow()
{
    close();
}

void StudentMainWindow::logout()
{
    if (studentId > 0) {
        QJsonObject payload;
        payload.insert(QStringLiteral("userId"), static_cast<qint64>(studentId));
        payload.insert(QStringLiteral("role"), QStringLiteral("STUDENT"));
        payload.insert(QStringLiteral("username"), studentNo.isEmpty() ? studentName : studentNo);
        requestJson(QStringLiteral("POST"), QStringLiteral("/auth/logout"), payload);
    }

    auto *login = new LoginWindow;
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
    close();
}

void StudentMainWindow::startWindowMove()
{
    if (windowHandle() != nullptr) {
        windowHandle()->startSystemMove();
    }
}

QJsonObject StudentMainWindow::requestJson(const QString &method,
                                           const QString &path,
                                           const QJsonObject &payload,
                                           const QUrlQuery &query) const
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
