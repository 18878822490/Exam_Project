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
#include <QScreen>
#include <QStandardPaths>
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
            {"startTime", row.value(QStringLiteral("start_time"), row.value(QStringLiteral("startTime"), QStringLiteral("2026-07-12 09:00")))},
            {"endTime", row.value(QStringLiteral("end_time"), row.value(QStringLiteral("endTime"), QStringLiteral("2026-07-12 11:00")))},
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
            {"type", row.value(QStringLiteral("type"))},
            {"content", row.value(QStringLiteral("content"))},
            {"optionA", row.value(QStringLiteral("option_a"), row.value(QStringLiteral("optionA")))},
            {"optionB", row.value(QStringLiteral("option_b"), row.value(QStringLiteral("optionB")))},
            {"optionC", row.value(QStringLiteral("option_c"), row.value(QStringLiteral("optionC")))},
            {"optionD", row.value(QStringLiteral("option_d"), row.value(QStringLiteral("optionD")))},
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
    QVariantList subjects;
    for (const QVariant &value : rows) {
        const QVariantMap row = value.toMap();
        const QString subject = row.value(QStringLiteral("subject"), QStringLiteral("综合")).toString();
        subjects.append(QVariantMap{
            {"name", subject},
            {"icon", subjectIcon(subject)},
            {"progress", row.value(QStringLiteral("progress"), 0).toInt()},
            {"accuracy", row.value(QStringLiteral("accuracy"), 0).toInt()},
            {"easy", row.value(QStringLiteral("easy"), 0).toInt()},
            {"middle", row.value(QStringLiteral("middle"), 0).toInt()},
            {"hard", row.value(QStringLiteral("hard"), 0).toInt()},
            {"totalCount", row.value(QStringLiteral("total_count"), row.value(QStringLiteral("totalCount"), 0)).toInt()},
            {"practicedCount", row.value(QStringLiteral("practiced_count"), row.value(QStringLiteral("practicedCount"), 0)).toInt()},
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
                                                     const QString &keyword) const
{
    QUrlQuery query;
    if (!type.trimmed().isEmpty() && type != QStringLiteral("全部题型")) {
        query.addQueryItem(QStringLiteral("type"), type.trimmed());
    }
    if (!difficulty.trimmed().isEmpty() && difficulty != QStringLiteral("全部难度")) {
        query.addQueryItem(QStringLiteral("difficulty"), difficulty.trimmed());
    }
    const QStringList subjects = {
        QStringLiteral("高数"), QStringLiteral("高等数学"), QStringLiteral("Java"),
        QStringLiteral("C++"), QStringLiteral("数据结构"), QStringLiteral("数据库"),
        QStringLiteral("英语"), QStringLiteral("综合")
    };
    const QString third = keyword.trimmed();
    const bool thirdIsSubject = subjects.contains(third);
    if (thirdIsSubject) {
        query.addQueryItem(QStringLiteral("subject"), third);
    }

    QVariantList rows = responseList(requestJson(QStringLiteral("GET"), QStringLiteral("/questions"), {}, query));
    QVariantList questions;
    const QString needle = thirdIsSubject ? QString() : third;
    for (const QVariant &value : rows) {
        const QVariantMap row = value.toMap();
        const QString content = row.value(QStringLiteral("content")).toString();
        const QString knowledgePoint = row.value(QStringLiteral("knowledgePoint"), row.value(QStringLiteral("knowledge_point"))).toString();
        if (!needle.isEmpty()
            && !content.contains(needle, Qt::CaseInsensitive)
            && !knowledgePoint.contains(needle, Qt::CaseInsensitive)) {
            continue;
        }

        questions.append(QVariantMap{
            {"id", row.value(QStringLiteral("question_id"), row.value(QStringLiteral("questionId"), row.value(QStringLiteral("id"))))},
            {"type", row.value(QStringLiteral("type"))},
            {"content", content},
            {"optionA", row.value(QStringLiteral("option_a"), row.value(QStringLiteral("optionA")))} ,
            {"optionB", row.value(QStringLiteral("option_b"), row.value(QStringLiteral("optionB")))} ,
            {"optionC", row.value(QStringLiteral("option_c"), row.value(QStringLiteral("optionC")))} ,
            {"optionD", row.value(QStringLiteral("option_d"), row.value(QStringLiteral("optionD")))} ,
            {"answer", row.value(QStringLiteral("answer"), row.value(QStringLiteral("standard_answer")))},
            {"analysis", row.value(QStringLiteral("analysis"))},
            {"difficulty", row.value(QStringLiteral("difficulty"), QStringLiteral("基础"))},
            {"knowledgePoint", knowledgePoint},
            {"score", row.value(QStringLiteral("score"), 0)}
        });
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
            {"type", row.value(QStringLiteral("type"))},
            {"difficulty", row.value(QStringLiteral("difficulty"), QStringLiteral("中等"))},
            {"content", row.value(QStringLiteral("content"))},
            {"optionA", row.value(QStringLiteral("option_a"), row.value(QStringLiteral("optionA")))},
            {"optionB", row.value(QStringLiteral("option_b"), row.value(QStringLiteral("optionB")))},
            {"optionC", row.value(QStringLiteral("option_c"), row.value(QStringLiteral("optionC")))},
            {"optionD", row.value(QStringLiteral("option_d"), row.value(QStringLiteral("optionD")))},
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
    if (examId <= 0 || answers.isEmpty()) {
        errorMessage = QStringLiteral("请完成答题后再交卷");
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
    request.setTransferTimeout(1200);

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
    timeout.start(1200);
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
