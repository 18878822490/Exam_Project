#include "AdminMainWindow.h"

#include "AppConfig.h"
#include "LoginWindow.h"

#include <QColor>
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
#include <QScreen>
#include <QTimer>
#include <QUrl>
#include <QUrlQuery>
#include <QWindow>

namespace {
QVariantMap responseMap(const QJsonObject &response)
{
    if (!response.value(QStringLiteral("success")).toBool()) {
        return {};
    }
    return response.value(QStringLiteral("data")).toObject().toVariantMap();
}

QVariantList responseList(const QJsonObject &response)
{
    if (!response.value(QStringLiteral("success")).toBool()) {
        return {};
    }
    return response.value(QStringLiteral("data")).toArray().toVariantList();
}

QString textValue(const QVariantMap &row, const QString &key, const QString &fallback = {})
{
    const QString value = row.value(key).toString().trimmed();
    return value.isEmpty() ? fallback : value;
}

int intValue(const QVariantMap &row, const QString &key, int fallback = 0)
{
    bool ok = false;
    const int value = row.value(key).toInt(&ok);
    return ok ? value : fallback;
}

double doubleValue(const QVariantMap &row, const QString &key, double fallback = 0)
{
    bool ok = false;
    const double value = row.value(key).toDouble(&ok);
    return ok ? value : fallback;
}
}

AdminMainWindow::AdminMainWindow(const QString &adminName, QWidget *parent)
    : QMainWindow(parent)
    , view(new QQuickWidget(this))
    , fallbackAdminName(adminName.trimmed().isEmpty() ? QStringLiteral("admin") : adminName.trimmed())
{
    setWindowTitle(QStringLiteral("智考星考试系统 - 管理端"));
    setWindowFlag(Qt::FramelessWindowHint, true);
    setMinimumSize(920, 620);

    const QRect available = QGuiApplication::primaryScreen() != nullptr
            ? QGuiApplication::primaryScreen()->availableGeometry()
            : QRect(0, 0, 1536, 960);
    const int initialWidth = qBound(920, int(available.width() * 0.92), 1536);
    const int initialHeight = qBound(620, int(available.height() * 0.90), 1024);
    resize(initialWidth, initialHeight);
    move(available.center() - rect().center());

    view->setResizeMode(QQuickWidget::SizeRootObjectToView);
    view->setClearColor(QColor(QStringLiteral("#eef3fb")));
    view->rootContext()->setContextProperty(QStringLiteral("adminApi"), this);
    connect(view, &QQuickWidget::statusChanged, this, [this](QQuickWidget::Status status) {
        if (status != QQuickWidget::Error) {
            return;
        }

        QStringList messages;
        for (const QQmlError &error : view->errors()) {
            messages.append(error.toString());
        }
        QMessageBox::critical(this,
                              QStringLiteral("管理端界面加载失败"),
                              messages.isEmpty()
                                      ? QStringLiteral("QML 加载失败，请查看应用输出。")
                                      : messages.join(QLatin1Char('\n')));
    });
    view->setSource(QUrl(QStringLiteral("qrc:/qml/AdminMain.qml")));
    setCentralWidget(view);
}

QString AdminMainWindow::adminName() const
{
    return fallbackAdminName;
}

void AdminMainWindow::minimizeWindow()
{
    showMinimized();
}

void AdminMainWindow::toggleMaximizeWindow()
{
    isMaximized() ? showNormal() : showMaximized();
}

void AdminMainWindow::closeWindow()
{
    close();
}

void AdminMainWindow::logout()
{
    auto *login = new LoginWindow;
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
    close();
}

void AdminMainWindow::startWindowMove()
{
    if (windowHandle() != nullptr) {
        windowHandle()->startSystemMove();
    }
}

QVariantMap AdminMainWindow::getStudentManagementData() const
{
    errorMessage.clear();

    const QJsonObject statsResponse = requestJson(QStringLiteral("GET"), QStringLiteral("/users/students/admin-stats"));
    const QJsonObject listResponse = requestJson(QStringLiteral("GET"), QStringLiteral("/users/students"));
    if (!statsResponse.value(QStringLiteral("success")).toBool()
            || !listResponse.value(QStringLiteral("success")).toBool()) {
        if (errorMessage.isEmpty()) {
            errorMessage = QStringLiteral("管理端学生数据读取失败，请确认后端服务已启动");
        }
        return {};
    }

    const QVariantMap statsRaw = responseMap(statsResponse);
    const QVariantList studentsRaw = responseList(listResponse);

    QVariantList rows;
    QVariantList detailRows;
    QVariantList maintenanceRows;
    QVariantList scoreRows;

    for (const QVariant &value : studentsRaw) {
        const QVariantMap student = value.toMap();
        const QString studentNo = textValue(student, QStringLiteral("student_no"), textValue(student, QStringLiteral("studentNo"), QStringLiteral("--")));
        const QString name = textValue(student, QStringLiteral("name"), textValue(student, QStringLiteral("username"), QStringLiteral("未命名")));
        const QString className = textValue(student, QStringLiteral("class_name"), textValue(student, QStringLiteral("className"), QStringLiteral("--")));
        const QString major = textValue(student, QStringLiteral("major"), QStringLiteral("--"));
        const int examCount = intValue(student, QStringLiteral("exam_count"));
        const int absentCount = intValue(student, QStringLiteral("absent_count"));
        const double averageScore = doubleValue(student, QStringLiteral("average_score"));
        const QString averageText = examCount > 0 ? QString::number(averageScore, 'f', 1) : QStringLiteral("--");
        const QString examText = examCount > 0
                ? QStringLiteral("已考 %1 / 缺考 %2").arg(examCount).arg(absentCount)
                : QStringLiteral("暂无考试记录");

        rows.append(QVariantList{
            studentNo,
            name,
            className,
            QStringLiteral("已通过"),
            examText,
            averageText,
            QStringLiteral("查看 / 编辑")
        });

        detailRows.append(QVariantList{
            name,
            examCount > 0 ? QStringLiteral("最近考试已记录") : QStringLiteral("暂无考试"),
            examCount > 0 ? QStringLiteral("%1 次").arg(examCount) : QStringLiteral("0 次"),
            averageText,
            averageText,
            examCount == 0 ? QStringLiteral("待参加") : (averageScore >= 85 ? QStringLiteral("稳定") : QStringLiteral("需关注")),
            QStringLiteral("成绩档案")
        });

        if (maintenanceRows.size() < 6) {
            maintenanceRows.append(QVariantList{
                QStringLiteral("学生资料"),
                QStringLiteral("%1 / %2").arg(name, studentNo),
                QStringLiteral("已通过"),
                QStringLiteral("维护专业、班级、账号和密码")
            });
        }
        if (scoreRows.size() < 6) {
            scoreRows.append(QVariantList{
                name,
                examText,
                averageText == QStringLiteral("--") ? QStringLiteral("暂无成绩") : QStringLiteral("平均 %1").arg(averageText),
                QStringLiteral("查看成绩趋势和考试报告")
            });
        }
    }

    if (rows.isEmpty()) {
        rows.append(QVariantList{
            QStringLiteral("--"),
            QStringLiteral("暂无学生"),
            QStringLiteral("--"),
            QStringLiteral("待新增"),
            QStringLiteral("注册或新增后会显示在这里"),
            QStringLiteral("--"),
            QStringLiteral("新增学生")
        });
    }

    const QString total = statsRaw.value(QStringLiteral("total_count"), rows.size()).toString();
    const QString today = statsRaw.value(QStringLiteral("today_new"), 0).toString();
    const QString pending = statsRaw.value(QStringLiteral("pending_review"), 0).toString();
    const QString rate = statsRaw.value(QStringLiteral("reference_rate"), QStringLiteral("0%")).toString();

    QVariantList stats = {
        QVariantMap{{QStringLiteral("label"), QStringLiteral("学生总数")}, {QStringLiteral("value"), total}, {QStringLiteral("color"), QStringLiteral("#2563eb")}},
        QVariantMap{{QStringLiteral("label"), QStringLiteral("今日新增")}, {QStringLiteral("value"), today}, {QStringLiteral("color"), QStringLiteral("#16a34a")}},
        QVariantMap{{QStringLiteral("label"), QStringLiteral("待审核注册")}, {QStringLiteral("value"), pending}, {QStringLiteral("color"), QStringLiteral("#f97316")}},
        QVariantMap{{QStringLiteral("label"), QStringLiteral("平均参考率")}, {QStringLiteral("value"), rate}, {QStringLiteral("color"), QStringLiteral("#7c3aed")}}
    };

    QVariantList workflowPanels = {
        QVariantMap{
            {QStringLiteral("title"), QStringLiteral("注册审核与信息维护")},
            {QStringLiteral("headers"), QVariantList{QStringLiteral("管理事项"), QStringLiteral("学生"), QStringLiteral("当前状态"), QStringLiteral("处理动作")}},
            {QStringLiteral("weights"), QVariantList{0.95, 1.05, 1.18, 1.2}},
            {QStringLiteral("statusIndex"), 2},
            {QStringLiteral("rows"), maintenanceRows}
        },
        QVariantMap{
            {QStringLiteral("title"), QStringLiteral("考试记录与成绩档案")},
            {QStringLiteral("headers"), QVariantList{QStringLiteral("学生"), QStringLiteral("考试情况"), QStringLiteral("成绩情况"), QStringLiteral("可执行操作")}},
            {QStringLiteral("weights"), QVariantList{0.9, 1.22, 1.0, 1.2}},
            {QStringLiteral("statusIndex"), 2},
            {QStringLiteral("rows"), scoreRows}
        }
    };

    QVariantList focusCards = {
        QVariantMap{{QStringLiteral("title"), QStringLiteral("注册审核")}, {QStringLiteral("value"), pending + QStringLiteral(" 人")}, {QStringLiteral("detail"), QStringLiteral("当前注册默认通过，后续可扩展待审核流程")}, {QStringLiteral("accent"), QStringLiteral("#f97316")}},
        QVariantMap{{QStringLiteral("title"), QStringLiteral("今日新增")}, {QStringLiteral("value"), today + QStringLiteral(" 人")}, {QStringLiteral("detail"), QStringLiteral("来自注册页面或管理端新增入库")}, {QStringLiteral("accent"), QStringLiteral("#2563eb")}},
        QVariantMap{{QStringLiteral("title"), QStringLiteral("考试与成绩")}, {QStringLiteral("value"), total + QStringLiteral(" 人")}, {QStringLiteral("detail"), QStringLiteral("按学生读取考试次数、缺考和平均分")}, {QStringLiteral("accent"), QStringLiteral("#16a34a")}}
    };

    return QVariantMap{
        {QStringLiteral("stats"), stats},
        {QStringLiteral("rows"), rows},
        {QStringLiteral("detailRows"), detailRows},
        {QStringLiteral("workflowPanels"), workflowPanels},
        {QStringLiteral("focusCards"), focusCards},
        {QStringLiteral("loaded"), true}
    };
}

QVariantMap AdminMainWindow::getTeacherManagementData() const
{
    errorMessage.clear();

    const QJsonObject statsResponse = requestJson(QStringLiteral("GET"), QStringLiteral("/users/teachers/admin-stats"));
    const QJsonObject listResponse = requestJson(QStringLiteral("GET"), QStringLiteral("/users/teachers"));
    if (!statsResponse.value(QStringLiteral("success")).toBool()
            || !listResponse.value(QStringLiteral("success")).toBool()) {
        if (errorMessage.isEmpty()) {
            errorMessage = QStringLiteral("管理端教师数据读取失败，请确认后端服务已启动");
        }
        return {};
    }

    const QVariantMap statsRaw = responseMap(statsResponse);
    const QVariantList teachersRaw = responseList(listResponse);

    QVariantList rows;
    QVariantList detailRows;
    QVariantList auditRows;
    QVariantList taskRows;

    for (const QVariant &value : teachersRaw) {
        const QVariantMap teacher = value.toMap();
        const QString username = textValue(teacher, QStringLiteral("username"), QStringLiteral("--"));
        const QString name = textValue(teacher, QStringLiteral("name"), username);
        const QString subject = textValue(teacher, QStringLiteral("subject"), QStringLiteral("未设置"));
        const QString classNames = textValue(teacher, QStringLiteral("class_names"), QStringLiteral("暂未分配班级"));
        const int examCount = intValue(teacher, QStringLiteral("exam_count"));
        const int pendingReviewCount = intValue(teacher, QStringLiteral("pending_review_count"));

        rows.append(QVariantList{
            username,
            name,
            subject,
            QStringLiteral("已通过"),
            QStringLiteral("%1 场").arg(examCount),
            pendingReviewCount > 0 ? QStringLiteral("%1 份").arg(pendingReviewCount) : QStringLiteral("0 份"),
            QStringLiteral("查看 / 编辑")
        });

        detailRows.append(QVariantList{
            name,
            examCount > 0 ? QStringLiteral("已发布考试") : QStringLiteral("暂未发布考试"),
            classNames,
            QStringLiteral("%1 场").arg(examCount),
            pendingReviewCount > 0 ? QStringLiteral("%1 份").arg(pendingReviewCount) : QStringLiteral("0 份"),
            pendingReviewCount > 0 ? QStringLiteral("需处理") : QStringLiteral("100%"),
            pendingReviewCount > 0 ? QStringLiteral("进入任务") : QStringLiteral("查看记录")
        });

        if (auditRows.size() < 6) {
            auditRows.append(QVariantList{
                QStringLiteral("教师资料"),
                QStringLiteral("%1 / %2").arg(name, username),
                QStringLiteral("已通过"),
                QStringLiteral("维护科目、手机号和可管理班级")
            });
        }
        if (taskRows.size() < 6) {
            taskRows.append(QVariantList{
                name,
                QStringLiteral("%1 / %2 场").arg(subject).arg(examCount),
                pendingReviewCount > 0 ? QStringLiteral("待批改 %1 份").arg(pendingReviewCount) : QStringLiteral("已完成"),
                QStringLiteral("查看发布考试和批改任务")
            });
        }
    }

    if (rows.isEmpty()) {
        rows.append(QVariantList{
            QStringLiteral("--"),
            QStringLiteral("暂无教师"),
            QStringLiteral("--"),
            QStringLiteral("待注册"),
            QStringLiteral("0 场"),
            QStringLiteral("0 份"),
            QStringLiteral("等待注册")
        });
    }

    const QString total = statsRaw.value(QStringLiteral("total_count"), rows.size()).toString();
    const QString today = statsRaw.value(QStringLiteral("today_new"), 0).toString();
    const QString pending = statsRaw.value(QStringLiteral("pending_review"), 0).toString();
    const QString rate = statsRaw.value(QStringLiteral("active_rate"), QStringLiteral("0%")).toString();

    QVariantList stats = {
        QVariantMap{{QStringLiteral("label"), QStringLiteral("教师总数")}, {QStringLiteral("value"), total}, {QStringLiteral("color"), QStringLiteral("#2563eb")}},
        QVariantMap{{QStringLiteral("label"), QStringLiteral("今日新增")}, {QStringLiteral("value"), today}, {QStringLiteral("color"), QStringLiteral("#16a34a")}},
        QVariantMap{{QStringLiteral("label"), QStringLiteral("待审核账号")}, {QStringLiteral("value"), pending}, {QStringLiteral("color"), QStringLiteral("#f97316")}},
        QVariantMap{{QStringLiteral("label"), QStringLiteral("任务完成率")}, {QStringLiteral("value"), rate}, {QStringLiteral("color"), QStringLiteral("#7c3aed")}}
    };

    QVariantList workflowPanels = {
        QVariantMap{
            {QStringLiteral("title"), QStringLiteral("教师账号审核与权限维护")},
            {QStringLiteral("headers"), QVariantList{QStringLiteral("管理事项"), QStringLiteral("教师"), QStringLiteral("当前状态"), QStringLiteral("处理动作")}},
            {QStringLiteral("weights"), QVariantList{0.95, 1.0, 1.05, 1.28}},
            {QStringLiteral("statusIndex"), 2},
            {QStringLiteral("rows"), auditRows}
        },
        QVariantMap{
            {QStringLiteral("title"), QStringLiteral("发布考试与批改任务")},
            {QStringLiteral("headers"), QVariantList{QStringLiteral("教师"), QStringLiteral("发布考试"), QStringLiteral("批改情况"), QStringLiteral("可执行操作")}},
            {QStringLiteral("weights"), QVariantList{0.85, 1.28, 1.05, 1.18}},
            {QStringLiteral("statusIndex"), 2},
            {QStringLiteral("rows"), taskRows}
        }
    };

    QVariantList focusCards = {
        QVariantMap{{QStringLiteral("title"), QStringLiteral("账号审核")}, {QStringLiteral("value"), pending + QStringLiteral(" 人")}, {QStringLiteral("detail"), QStringLiteral("当前注册默认通过，后续可扩展待审核流程")}, {QStringLiteral("accent"), QStringLiteral("#f97316")}},
        QVariantMap{{QStringLiteral("title"), QStringLiteral("今日新增")}, {QStringLiteral("value"), today + QStringLiteral(" 人")}, {QStringLiteral("detail"), QStringLiteral("来自教师注册页面的新增账号")}, {QStringLiteral("accent"), QStringLiteral("#2563eb")}},
        QVariantMap{{QStringLiteral("title"), QStringLiteral("发布与批改")}, {QStringLiteral("value"), total + QStringLiteral(" 人")}, {QStringLiteral("detail"), QStringLiteral("按教师读取考试发布与待批改任务")}, {QStringLiteral("accent"), QStringLiteral("#16a34a")}}
    };

    return QVariantMap{
        {QStringLiteral("stats"), stats},
        {QStringLiteral("rows"), rows},
        {QStringLiteral("detailRows"), detailRows},
        {QStringLiteral("workflowPanels"), workflowPanels},
        {QStringLiteral("focusCards"), focusCards},
        {QStringLiteral("loaded"), true}
    };
}

QString AdminMainWindow::lastError() const
{
    return errorMessage;
}

QJsonObject AdminMainWindow::requestJson(const QString &method,
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
    request.setTransferTimeout(1500);

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
    timeout.start(1500);
    loop.exec();
    timeout.stop();

    const QByteArray responseBody = reply->readAll();
    const bool ok = reply->error() == QNetworkReply::NoError;
    if (!ok) {
        errorMessage = reply->errorString();
    }
    reply->deleteLater();
    if (!ok) {
        return {};
    }

    const QJsonDocument document = QJsonDocument::fromJson(responseBody);
    return document.isObject() ? document.object() : QJsonObject{};
}
