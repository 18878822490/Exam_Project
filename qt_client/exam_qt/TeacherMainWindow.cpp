#include "TeacherMainWindow.h"

#include "AppConfig.h"
#include "LoginWindow.h"
#include "ScorePrintWindow.h"
#include "TeacherDataRepository.h"
#include "TeacherMarkWindow.h"
#include "TeacherScoreAnalysisWindow.h"

#include <QQmlContext>
#include <QQuickWidget>
#include <QDateTime>
#include <QDebug>
#include <QDesktopServices>
#include <QDialog>
#include <QDir>
#include <QEventLoop>
#include <QFile>
#include <QFileInfo>
#include <QGuiApplication>
#include <QHttpMultiPart>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPageSize>
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>
#include <QQuickItem>
#include <QScreen>
#include <QQmlError>
#include <QStackedWidget>
#include <QStandardPaths>
#include <QTimer>
#include <QUrl>
#include <QWindow>

#if __has_include("xlsxdocument.h")
#include "xlsxdocument.h"
#include "xlsxcellrange.h"
#define EXAM_HAS_QXLSX 1
#endif

namespace {
QString compactHeader(const QString &value)
{
    QString text = value.trimmed().toLower();
    text.remove('_');
    text.remove(' ');
    return text;
}

QString valueText(const QVariant &value)
{
    return value.toString().trimmed();
}

QString headerValue(const QMap<QString, int> &headers,
                    const QList<QVariant> &row,
                    const QStringList &names)
{
    for (const QString &name : names) {
        const QString key = compactHeader(name);
        if (headers.contains(key)) {
            const int column = headers.value(key);
            if (column >= 0 && column < row.size()) {
                return valueText(row.at(column));
            }
        }
    }
    return {};
}

bool headerLooksValid(const QMap<QString, int> &headers)
{
    return headers.contains(QStringLiteral("type"))
            || headers.contains(QStringLiteral("题型"))
            || headers.contains(QStringLiteral("content"))
            || headers.contains(QStringLiteral("题目"))
            || headers.contains(QStringLiteral("answer"))
            || headers.contains(QStringLiteral("答案"));
}

QByteArray formDisposition(const QString &name, const QString &fileName = QString())
{
    QString value = QStringLiteral("form-data; name=\"%1\"").arg(name);
    if (!fileName.isEmpty()) {
        QString safeName = fileName;
        safeName.replace(QLatin1Char('"'), QLatin1Char('\''));
        value += QStringLiteral("; filename=\"%1\"").arg(safeName);
    }
    return value.toUtf8();
}

QJsonObject postMultipartFile(const QString &url,
                              const QString &path,
                              qint64 userId,
                              QString *errorMessage)
{
    QFileInfo info(path);
    QFile *file = new QFile(path);
    if (!file->open(QIODevice::ReadOnly)) {
        if (errorMessage) {
            *errorMessage = file->errorString();
        }
        delete file;
        return {};
    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/octet-stream"));
    filePart.setRawHeader("Content-Disposition", formDisposition(QStringLiteral("file"), info.fileName()));
    filePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(filePart);

    if (userId > 0) {
        QHttpPart userPart;
        userPart.setRawHeader("Content-Disposition", formDisposition(QStringLiteral("userId")));
        userPart.setBody(QString::number(userId).toUtf8());
        multiPart->append(userPart);
    }

    QNetworkRequest request{QUrl(url)};
    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply *reply = manager.post(request, multiPart);
    multiPart->setParent(reply);

    QTimer timeout;
    timeout.setSingleShot(true);
    QObject::connect(&timeout, &QTimer::timeout, [&reply]() {
        if (reply && reply->isRunning()) {
            reply->abort();
        }
    });
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    timeout.start(90000);
    loop.exec();
    timeout.stop();

    const QByteArray body = reply->readAll();
    const bool ok = reply->error() == QNetworkReply::NoError;
    if (!ok && errorMessage) {
        *errorMessage = reply->errorString();
    }
    reply->deleteLater();
    if (!ok) {
        return {};
    }

    const QJsonDocument document = QJsonDocument::fromJson(body);
    return document.isObject() ? document.object() : QJsonObject{};
}

int importedCount(const QJsonObject &response)
{
    const QJsonObject data = response.value(QStringLiteral("data")).toObject();
    return data.value(QStringLiteral("successCount")).toInt();
}

QString importStatus(const QJsonObject &response, const QString &fallback = QString())
{
    const QJsonObject data = response.value(QStringLiteral("data")).toObject();
    return data.value(QStringLiteral("status")).toString(
                fallback.isEmpty()
                    ? (response.value(QStringLiteral("success")).toBool() ? QStringLiteral("成功") : QStringLiteral("失败"))
                    : fallback);
}

QString importMessage(const QJsonObject &response)
{
    const QJsonObject data = response.value(QStringLiteral("data")).toObject();
    return data.value(QStringLiteral("message")).toString(response.value(QStringLiteral("message")).toString());
}
}

TeacherMainWindow::TeacherMainWindow(qint64 teacherId,
                                     const QString &teacherName,
                                     const QString &teacherSubject,
                                     QWidget *parent)
    : QMainWindow(parent)
    , view(new QQuickWidget(this))
    , centralStack(new QStackedWidget(this))
    , markWorkbench(new TeacherMarkWindow(this))
    , scorePrintWorkbench(new ScorePrintWindow(this))
    , scoreAnalysisWorkbench(new TeacherScoreAnalysisWindow(this))
    , repository(new TeacherDataRepository(teacherId, this))
    , teacherId(teacherId)
    , fallbackTeacherName(teacherName)
    , fallbackTeacherSubject(teacherSubject)
{
    setWindowTitle(QStringLiteral("智考星考试系统 - 教师端"));
    setWindowFlag(Qt::FramelessWindowHint, true);
    setMinimumSize(920, 620);

    const QRect available = QGuiApplication::primaryScreen() != nullptr
            ? QGuiApplication::primaryScreen()->availableGeometry()
            : QRect(0, 0, 1440, 900);
    const int initialWidth = qBound(920, int(available.width() * 0.92), 1536);
    const int initialHeight = qBound(620, int(available.height() * 0.90), 960);
    resize(initialWidth, initialHeight);
    move(available.center() - rect().center());

    if (!repository->initialize()) {
        qWarning().noquote() << QStringLiteral("数据库初始化失败:")
                             << (repository->lastError().isEmpty()
                                     ? QStringLiteral("无法连接数据库。")
                                     : repository->lastError());
    }
    markWorkbench->setRepository(repository);
    scorePrintWorkbench->setRepository(repository);
    scoreAnalysisWorkbench->setRepository(repository);

    view->setResizeMode(QQuickWidget::SizeRootObjectToView);
    view->setClearColor(QColor(QStringLiteral("#eef3fb")));
    view->rootContext()->setContextProperty(QStringLiteral("teacherApi"), this);
    connect(view, &QQuickWidget::statusChanged, this, [this](QQuickWidget::Status status) {
        if (status != QQuickWidget::Error) {
            return;
        }

        QStringList messages;
        for (const QQmlError &error : view->errors()) {
            messages.append(error.toString());
            qWarning().noquote() << error.toString();
        }

        QMessageBox::critical(this,
                              QStringLiteral("教师端界面加载失败"),
                              messages.isEmpty()
                                      ? QStringLiteral("QML 加载失败，请查看应用输出。")
                                      : messages.join(QLatin1Char('\n')));
    });
    view->setSource(QUrl(QStringLiteral("qrc:/qml/TeacherMain.qml")));
    centralStack->addWidget(view);
    centralStack->addWidget(markWorkbench);
    centralStack->addWidget(scoreAnalysisWorkbench);
    centralStack->addWidget(scorePrintWorkbench);
    centralStack->setCurrentWidget(view);
    setCentralWidget(centralStack);

    connect(markWorkbench, &TeacherMarkWindow::backRequested, this, [this]() {
        centralStack->setCurrentWidget(view);
    });
    connect(markWorkbench, &TeacherMarkWindow::pageRequested, this, &TeacherMainWindow::openTeacherPage);
    connect(markWorkbench, &TeacherMarkWindow::minimizeRequested, this, &TeacherMainWindow::minimizeWindow);
    connect(markWorkbench, &TeacherMarkWindow::maximizeRequested, this, &TeacherMainWindow::toggleMaximizeWindow);
    connect(markWorkbench, &TeacherMarkWindow::closeRequested, this, &TeacherMainWindow::closeWindow);
    connect(scoreAnalysisWorkbench, &TeacherScoreAnalysisWindow::backRequested, this, [this]() {
        centralStack->setCurrentWidget(view);
    });
    connect(scoreAnalysisWorkbench, &TeacherScoreAnalysisWindow::pageRequested, this, &TeacherMainWindow::openTeacherPage);
    connect(scoreAnalysisWorkbench, &TeacherScoreAnalysisWindow::printReportRequested, this, &TeacherMainWindow::openScorePrintWorkbench);
    connect(scoreAnalysisWorkbench, &TeacherScoreAnalysisWindow::minimizeRequested, this, &TeacherMainWindow::minimizeWindow);
    connect(scoreAnalysisWorkbench, &TeacherScoreAnalysisWindow::maximizeRequested, this, &TeacherMainWindow::toggleMaximizeWindow);
    connect(scoreAnalysisWorkbench, &TeacherScoreAnalysisWindow::closeRequested, this, &TeacherMainWindow::closeWindow);
    connect(scorePrintWorkbench, &ScorePrintWindow::backRequested, this, [this]() {
        centralStack->setCurrentWidget(scoreAnalysisWorkbench);
    });
    connect(scorePrintWorkbench, &ScorePrintWindow::minimizeRequested, this, &TeacherMainWindow::minimizeWindow);
    connect(scorePrintWorkbench, &ScorePrintWindow::maximizeRequested, this, &TeacherMainWindow::toggleMaximizeWindow);
    connect(scorePrintWorkbench, &ScorePrintWindow::closeRequested, this, &TeacherMainWindow::closeWindow);
}

QVariantMap TeacherMainWindow::getTeacherProfile() const
{
    QVariantMap profile = repository->getTeacherProfile();
    if (!fallbackTeacherName.trimmed().isEmpty()) {
        profile.insert(QStringLiteral("name"), fallbackTeacherName.trimmed());
    }
    if (!fallbackTeacherSubject.trimmed().isEmpty()) {
        profile.insert(QStringLiteral("subject"), fallbackTeacherSubject.trimmed());
    }
    profile.insert(QStringLiteral("role"), QStringLiteral("教师"));
    return profile;
}

QVariantList TeacherMainWindow::getTeacherClasses() const
{
    return repository->getTeacherClasses();
}

QVariantList TeacherMainWindow::getClassStudents(const QString &className) const
{
    return repository->getClassStudents(className);
}

QVariantList TeacherMainWindow::getExamList() const
{
    return repository->getExamList();
}

QVariantList TeacherMainWindow::getQuestions() const
{
    return repository->getQuestions();
}

QVariantList TeacherMainWindow::searchQuestions(const QString &keyword, const QString &type, const QString &difficulty) const
{
    return repository->searchQuestions(keyword, type, difficulty);
}

QVariantList TeacherMainWindow::searchQuestionsAdvanced(const QString &keyword,
                                                        const QString &subject,
                                                        const QString &type,
                                                        const QString &difficulty,
                                                        const QString &knowledgePoint) const
{
    return repository->searchQuestionsAdvanced(keyword, subject, type, difficulty, knowledgePoint);
}

QVariantList TeacherMainWindow::getImportLogs() const
{
    const QVariantList backendLogs = repository->getImportLogs();
    return backendLogs.isEmpty() ? importLogs : backendLogs;
}

QVariantList TeacherMainWindow::getPendingReviews() const
{
    return repository->getPendingReviews();
}

QVariantList TeacherMainWindow::getStudentAnswers() const
{
    return repository->getStudentAnswers();
}

QVariantList TeacherMainWindow::getStudentAnswersForPaper(int paperId) const
{
    return repository->getStudentAnswersForPaper(paperId);
}

QVariantList TeacherMainWindow::getStudentAnswersForStudent(int paperId, const QString &studentNo) const
{
    return repository->getStudentAnswersForStudent(paperId, studentNo);
}

QVariantList TeacherMainWindow::getPaperQuestions(int paperId) const
{
    return repository->getPaperQuestions(paperId);
}

QVariantList TeacherMainWindow::getTodoItems() const
{
    return repository->getTodoItems();
}

QVariantMap TeacherMainWindow::getDashboardStats() const
{
    return repository->dashboardStats();
}

QVariantMap TeacherMainWindow::getScoreStatistics() const
{
    return repository->getScoreStatistics();
}

QVariantList TeacherMainWindow::getClassScoreTrend(const QString &className, const QString &subject) const
{
    return repository->getClassScoreTrend(className, subject);
}

QVariantList TeacherMainWindow::getQuestionAnalysis() const
{
    return repository->getQuestionAnalysis();
}

int TeacherMainWindow::addQuestion(const QVariantMap &question)
{
    return repository->addQuestion(question);
}

bool TeacherMainWindow::updateQuestion(int id, const QVariantMap &question)
{
    return repository->updateQuestion(id, question);
}

bool TeacherMainWindow::removeQuestion(int id)
{
    return repository->removeQuestion(id);
}

bool TeacherMainWindow::addTodoItem(const QString &title, const QString &type, const QString &remindTime)
{
    return repository->addTodoItem(title, type, remindTime);
}

int TeacherMainWindow::importQuestionsFromFile(const QString &fileUrl)
{
    const QString path = localFilePath(fileUrl);
    const QFileInfo info(path);
    const QString suffix = info.suffix().toLower();

    if (suffix == QStringLiteral("xlsx") || suffix == QStringLiteral("xls")) {
#ifdef EXAM_HAS_QXLSX
        QXlsx::Document document(path);
        const QXlsx::CellRange range = document.dimension();
        if (range.rowCount() <= 0 || range.columnCount() <= 0) {
            appendImportLog(QStringLiteral("Excel"), info.fileName(), 0, QStringLiteral("失败"), QStringLiteral("Excel内容为空"));
            return 0;
        }

        QMap<QString, int> headers;
        for (int column = range.firstColumn(); column <= range.lastColumn(); ++column) {
            headers.insert(compactHeader(document.read(range.firstRow(), column).toString()), column - range.firstColumn());
        }
        const bool hasHeader = headerLooksValid(headers);

        QJsonArray questions;
        const int startRow = hasHeader ? range.firstRow() + 1 : range.firstRow();
        for (int rowIndex = startRow; rowIndex <= range.lastRow(); ++rowIndex) {
            QList<QVariant> rowValues;
            bool emptyRow = true;
            for (int column = range.firstColumn(); column <= range.lastColumn(); ++column) {
                const QVariant cellValue = document.read(rowIndex, column);
                if (!valueText(cellValue).isEmpty()) {
                    emptyRow = false;
                }
                rowValues.append(cellValue);
            }
            if (emptyRow) {
                continue;
            }

            QJsonObject question;
            if (hasHeader) {
                question.insert(QStringLiteral("type"), headerValue(headers, rowValues, {QStringLiteral("type"), QStringLiteral("题型")}));
                question.insert(QStringLiteral("content"), headerValue(headers, rowValues, {QStringLiteral("content"), QStringLiteral("题目"), QStringLiteral("题干")}));
                question.insert(QStringLiteral("optionA"), headerValue(headers, rowValues, {QStringLiteral("optionA"), QStringLiteral("option_a"), QStringLiteral("A"), QStringLiteral("选项A")}));
                question.insert(QStringLiteral("optionB"), headerValue(headers, rowValues, {QStringLiteral("optionB"), QStringLiteral("option_b"), QStringLiteral("B"), QStringLiteral("选项B")}));
                question.insert(QStringLiteral("optionC"), headerValue(headers, rowValues, {QStringLiteral("optionC"), QStringLiteral("option_c"), QStringLiteral("C"), QStringLiteral("选项C")}));
                question.insert(QStringLiteral("optionD"), headerValue(headers, rowValues, {QStringLiteral("optionD"), QStringLiteral("option_d"), QStringLiteral("D"), QStringLiteral("选项D")}));
                question.insert(QStringLiteral("answer"), headerValue(headers, rowValues, {QStringLiteral("answer"), QStringLiteral("答案"), QStringLiteral("标准答案")}));
                question.insert(QStringLiteral("analysis"), headerValue(headers, rowValues, {QStringLiteral("analysis"), QStringLiteral("解析")}));
                question.insert(QStringLiteral("difficulty"), headerValue(headers, rowValues, {QStringLiteral("difficulty"), QStringLiteral("难度")}));
                question.insert(QStringLiteral("knowledgePoint"), headerValue(headers, rowValues, {QStringLiteral("knowledgePoint"), QStringLiteral("knowledge_point"), QStringLiteral("知识点")}));
                const QString score = headerValue(headers, rowValues, {QStringLiteral("score"), QStringLiteral("分值")});
                if (!score.isEmpty()) {
                    question.insert(QStringLiteral("score"), score.toInt());
                }
            } else {
                question.insert(QStringLiteral("type"), valueText(rowValues.value(0)));
                question.insert(QStringLiteral("content"), valueText(rowValues.value(1)));
                question.insert(QStringLiteral("answer"), valueText(rowValues.value(2)));
                question.insert(QStringLiteral("difficulty"), valueText(rowValues.value(3)));
                question.insert(QStringLiteral("knowledgePoint"), valueText(rowValues.value(4)));
            }

            if (!question.value(QStringLiteral("type")).toString().isEmpty()
                    && !question.value(QStringLiteral("content")).toString().isEmpty()) {
                questions.append(question);
            }
        }

        QJsonObject payload;
        payload.insert(QStringLiteral("importType"), QStringLiteral("Excel"));
        payload.insert(QStringLiteral("fileName"), info.fileName());
        if (teacherId > 0) {
            payload.insert(QStringLiteral("userId"), QJsonValue::fromVariant(teacherId));
        }
        payload.insert(QStringLiteral("questions"), questions);

    QNetworkRequest request(AppConfig::apiUrl(QStringLiteral("/questions/import/excel/parsed")));
        request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));

        QNetworkAccessManager manager;
        QEventLoop loop;
        QNetworkReply *reply = manager.post(request, QJsonDocument(payload).toJson(QJsonDocument::Compact));
        connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        if (reply->error() != QNetworkReply::NoError) {
            const QString message = reply->errorString();
            reply->deleteLater();
            appendImportLog(QStringLiteral("Excel"), info.fileName(), 0, QStringLiteral("失败"), message);
            return 0;
        }

        const QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
        reply->deleteLater();
        const QJsonObject root = response.object();
        const int imported = importedCount(root);
        return imported;
#else
        appendImportLog(QStringLiteral("Excel"), info.fileName(), 0, QStringLiteral("失败"),
                        QStringLiteral("当前编译未检测到QXlsx头文件，请检查QXlsx include路径。"));
        return 0;
#endif
    }

    QString error;
        const QJsonObject response = postMultipartFile(AppConfig::apiUrl(QStringLiteral("/questions/import/csv")).toString(), path, teacherId, &error);
    if (response.isEmpty()) {
        appendImportLog(QStringLiteral("CSV"), info.fileName(), 0, QStringLiteral("失败"), error);
        return 0;
    }
    const bool ok = response.value(QStringLiteral("success")).toBool();
    const int imported = importedCount(response);
    if (!ok) {
        appendImportLog(QStringLiteral("CSV"), info.fileName(), 0, QStringLiteral("失败"), importMessage(response));
    }
    return imported;
}

QVariantMap TeacherMainWindow::reserveOcrImport(const QString &fileUrl)
{
    const QString path = localFilePath(fileUrl);
    const QFileInfo info(path);
    QString error;
    const QJsonObject response = postMultipartFile(AppConfig::apiUrl(QStringLiteral("/questions/import/ocr")).toString(), path, teacherId, &error);
    if (response.isEmpty()) {
        appendImportLog(QStringLiteral("OCR"), info.fileName(), 0, QStringLiteral("失败"), error);
        return importLogs.isEmpty() ? QVariantMap{} : importLogs.first().toMap();
    }
    if (!response.value(QStringLiteral("success")).toBool()) {
        appendImportLog(QStringLiteral("OCR"), info.fileName(), 0, QStringLiteral("失败"), importMessage(response));
    }
    return response.value(QStringLiteral("data")).toObject().toVariantMap();
}

QString TeacherMainWindow::exportScoreReportPdf()
{
    QString documents = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    if (documents.isEmpty()) {
        documents = QDir::homePath();
    }
    QDir().mkpath(documents);
    const QString filePath = documents + QStringLiteral("/智考星成绩单报告.pdf");

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setOutputFileName(filePath);

    QPainter painter(&printer);
    if (!painter.isActive()) {
        return {};
    }
    paintScoreReport(&painter, printer.pageRect(QPrinter::DevicePixel).toRect());
    painter.end();
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    return filePath;
}

bool TeacherMainWindow::printScoreReport()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPageSize(QPageSize::A4));
    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle(QStringLiteral("打印成绩单报告"));
    if (dialog.exec() != QDialog::Accepted) {
        return false;
    }

    QPainter painter(&printer);
    if (!painter.isActive()) {
        return false;
    }
    paintScoreReport(&painter, printer.pageRect(QPrinter::DevicePixel).toRect());
    painter.end();
    return true;
}

int TeacherMainWindow::createDraftPaper(const QString &name,
                                        const QString &subject,
                                        const QString &startTime,
                                        const QString &endTime,
                                        const QVariantMap &counts)
{
    return repository->createDraftPaper(name, subject, parseDateTime(startTime), parseDateTime(endTime), counts);
}

int TeacherMainWindow::createDraftPaperFromQuestions(const QString &name,
                                                     const QString &subject,
                                                     const QString &startTime,
                                                     const QString &endTime,
                                                     const QVariantList &questions)
{
    return repository->createDraftPaperFromQuestions(name,
                                                     subject,
                                                     parseDateTime(startTime),
                                                     parseDateTime(endTime),
                                                     questions);
}

int TeacherMainWindow::copyExamAsDraft(const QString &examName,
                                       const QString &startTime,
                                       const QString &endTime)
{
    return repository->copyExamAsDraft(examName, parseDateTime(startTime), parseDateTime(endTime));
}

int TeacherMainWindow::copyExamAsDraftById(int examId, const QString &copyTitle)
{
    return repository->copyExamAsDraftById(examId, copyTitle);
}

bool TeacherMainWindow::publishExam(int paperId,
                                    const QVariantList &classNames,
                                    const QString &startTime,
                                    const QString &endTime)
{
    QStringList names;
    for (const QVariant &className : classNames) {
        names.append(className.toString());
    }
    return repository->publishExam(paperId, names, parseDateTime(startTime), parseDateTime(endTime));
}

bool TeacherMainWindow::saveReviewScore(int answerId, double score, const QString &comment)
{
    return repository->saveReviewScore(answerId, score, comment);
}

bool TeacherMainWindow::updateTeacherProfile(const QVariantMap &profileData)
{
    return repository->updateTeacherProfile(profileData);
}

bool TeacherMainWindow::changePassword(const QString &oldPassword, const QString &newPassword)
{
    return repository->changePassword(oldPassword, newPassword);
}

QString TeacherMainWindow::lastError() const
{
    return repository->lastError();
}

void TeacherMainWindow::minimizeWindow()
{
    showMinimized();
}

void TeacherMainWindow::toggleMaximizeWindow()
{
    isMaximized() ? showNormal() : showMaximized();
}

void TeacherMainWindow::closeWindow()
{
    close();
}

void TeacherMainWindow::logout()
{
    auto *login = new LoginWindow;
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
    login->raise();
    login->activateWindow();
    close();
}

void TeacherMainWindow::openMarkWorkbench()
{
    markWorkbench->loadExam();
    markWorkbench->loadStudents();
    centralStack->setCurrentWidget(markWorkbench);
    markWorkbench->playEnterAnimation();
    markWorkbench->setFocus();
}

void TeacherMainWindow::openScoreAnalysisWorkbench()
{
    scoreAnalysisWorkbench->loadInitialData();
    centralStack->setCurrentWidget(scoreAnalysisWorkbench);
    scoreAnalysisWorkbench->playEnterAnimation();
    scoreAnalysisWorkbench->setFocus();
}

void TeacherMainWindow::openScorePrintWorkbench()
{
    scorePrintWorkbench->loadInitialData();
    centralStack->setCurrentWidget(scorePrintWorkbench);
    scorePrintWorkbench->playEnterAnimation();
    scorePrintWorkbench->setFocus();
}

void TeacherMainWindow::openTeacherPage(int page)
{
    if (page == 3) {
        openMarkWorkbench();
        return;
    }
    if (page == 4) {
        openScoreAnalysisWorkbench();
        return;
    }

    centralStack->setCurrentWidget(view);
    if (QQuickItem *root = view->rootObject()) {
        QMetaObject::invokeMethod(root, "switchPage", Q_ARG(QVariant, QVariant(page)));
    }
    view->setFocus();
}

void TeacherMainWindow::startWindowMove()
{
    if (QWindow *handle = windowHandle()) {
        handle->startSystemMove();
    }
}

QDateTime TeacherMainWindow::parseDateTime(const QString &value) const
{
    QDateTime dateTime = QDateTime::fromString(value, Qt::ISODate);
    if (!dateTime.isValid()) {
        dateTime = QDateTime::fromString(value, QStringLiteral("yyyy-MM-dd HH:mm"));
    }
    if (!dateTime.isValid()) {
        dateTime = QDateTime::currentDateTime();
    }
    return dateTime;
}

QString TeacherMainWindow::localFilePath(const QString &fileUrl) const
{
    const QUrl url(fileUrl);
    return url.isLocalFile() ? url.toLocalFile() : fileUrl;
}

void TeacherMainWindow::appendImportLog(const QString &type,
                                        const QString &fileName,
                                        int count,
                                        const QString &status,
                                        const QString &message)
{
    const int failedCount = status.contains(QStringLiteral("失败")) ? qMax(1, count == 0 ? 1 : 0) : 0;
    if (repository) {
        repository->recordImportLog(type, fileName, qMax(count, failedCount), status.contains(QStringLiteral("失败")) ? 0 : count, failedCount, status, message);
    }
    importLogs.prepend(QVariantMap{
        {"time", QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd HH:mm:ss"))},
        {"type", type},
        {"fileName", fileName},
        {"count", count},
        {"status", status},
        {"message", message}
    });
    while (importLogs.size() > 30) {
        importLogs.removeLast();
    }
}

void TeacherMainWindow::paintScoreReport(QPainter *painter, const QRect &pageRect) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillRect(pageRect, Qt::white);

    const int margin = pageRect.width() * 0.08;
    QRect content(pageRect.left() + margin,
                  pageRect.top() + margin,
                  pageRect.width() - margin * 2,
                  pageRect.height() - margin * 2);

    QFont titleFont(QStringLiteral("Microsoft YaHei"), 22, QFont::Bold);
    QFont headingFont(QStringLiteral("Microsoft YaHei"), 12, QFont::Bold);
    QFont bodyFont(QStringLiteral("Microsoft YaHei"), 10);

    painter->setPen(QColor(17, 24, 39));
    painter->setFont(titleFont);
    painter->drawText(QRect(content.left(), content.top(), content.width(), 60),
                      Qt::AlignCenter,
                      QStringLiteral("智考星考试系统 - 成绩单报告"));

    painter->setFont(bodyFont);
    painter->setPen(QColor(100, 116, 139));
    painter->drawText(content.left(), content.top() + 86,
                      QStringLiteral("班级：软工01    考试：Java期末考试    生成时间：%1")
                              .arg(QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd HH:mm"))));

    const QVariantMap stats = repository->getScoreStatistics();
    const QStringList metricLabels = {QStringLiteral("平均成绩"), QStringLiteral("最高分"), QStringLiteral("最低分"), QStringLiteral("及格率")};
    const QStringList metricValues = {
        QString::number(stats.value(QStringLiteral("average"), 86.5).toDouble(), 'f', 1),
        QStringLiteral("98"),
        QStringLiteral("54"),
        QStringLiteral("%1%").arg(stats.value(QStringLiteral("passRate"), 91).toInt())
    };

    int y = content.top() + 130;
    const int cardGap = 18;
    const int cardW = (content.width() - cardGap * 3) / 4;
    for (int i = 0; i < 4; ++i) {
        QRect card(content.left() + i * (cardW + cardGap), y, cardW, 96);
        painter->setPen(QPen(QColor(226, 232, 240), 2));
        painter->setBrush(QColor(248, 251, 255));
        painter->drawRoundedRect(card, 16, 16);
        painter->setFont(headingFont);
        painter->setPen(QColor(37, 99, 235));
        painter->drawText(card.adjusted(16, 14, -16, -48), Qt::AlignLeft | Qt::AlignVCenter, metricValues.at(i));
        painter->setFont(bodyFont);
        painter->setPen(QColor(100, 116, 139));
        painter->drawText(card.adjusted(16, 52, -16, -12), Qt::AlignLeft | Qt::AlignVCenter, metricLabels.at(i));
    }

    y += 140;
    painter->setFont(headingFont);
    painter->setPen(QColor(17, 24, 39));
    painter->drawText(content.left(), y, QStringLiteral("学生成绩明细"));
    y += 28;

    const QStringList headers = {QStringLiteral("姓名"), QStringLiteral("学号"), QStringLiteral("成绩"), QStringLiteral("状态")};
    const int rowH = 38;
    painter->setFont(headingFont);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(241, 245, 251));
    painter->drawRoundedRect(QRect(content.left(), y, content.width(), rowH), 10, 10);
    painter->setPen(QColor(71, 85, 105));
    for (int i = 0; i < headers.size(); ++i) {
        painter->drawText(content.left() + i * content.width() / 4 + 14, y + 25, headers.at(i));
    }
    y += rowH + 6;

    const QVariantList answers = repository->getStudentAnswers();
    painter->setFont(bodyFont);
    const int maxRows = qMin(answers.size(), 14);
    for (int r = 0; r < maxRows; ++r) {
        const QVariantMap row = answers.at(r).toMap();
        painter->setPen(QPen(QColor(226, 232, 240), 1));
        painter->setBrush(QColor(255, 255, 255));
        painter->drawRoundedRect(QRect(content.left(), y, content.width(), rowH), 8, 8);
        painter->setPen(QColor(30, 41, 59));
        const QStringList values = {
            row.value(QStringLiteral("studentName")).toString(),
            row.value(QStringLiteral("studentNo")).toString(),
            row.value(QStringLiteral("score")).toString().isEmpty() ? QStringLiteral("--") : row.value(QStringLiteral("score")).toString(),
            row.value(QStringLiteral("status")).toString()
        };
        for (int i = 0; i < values.size(); ++i) {
            painter->drawText(content.left() + i * content.width() / 4 + 14, y + 25, values.at(i));
        }
        y += rowH + 6;
    }

    painter->setPen(QColor(148, 163, 184));
    painter->drawText(QRect(content.left(), content.bottom() - 40, content.width(), 30),
                      Qt::AlignCenter,
                      QStringLiteral("本报告由智考星考试系统生成"));
    painter->restore();
}
