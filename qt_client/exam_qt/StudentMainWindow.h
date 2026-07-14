#ifndef STUDENTMAINWINDOW_H
#define STUDENTMAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QUrlQuery>
#include <QVariantList>
#include <QVariantMap>

class QQuickWidget;

class StudentMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentMainWindow(qint64 studentId = 0,
                               const QString &studentName = QString(),
                               const QString &studentNo = QString(),
                               const QString &className = QString(),
                               QWidget *parent = nullptr);

    Q_INVOKABLE QVariantMap getStudentProfile();
    Q_INVOKABLE QVariantList getPublishedExams() const;
    Q_INVOKABLE QVariantList getExamQuestions(int examId) const;
    Q_INVOKABLE QVariantList getPracticeSubjectStats() const;
    Q_INVOKABLE QVariantList getPracticeQuestions(const QString &type,
                                                  const QString &difficulty,
                                                  const QString &keyword) const;
    Q_INVOKABLE bool savePracticeAnswer(int questionId,
                                         const QString &answer,
                                         bool correct,
                                         const QString &practiceMode);
    Q_INVOKABLE QVariantMap getScoreReport(int examId) const;
    Q_INVOKABLE QVariantList getScoreHistory(const QString &subject = QString()) const;
    Q_INVOKABLE QVariantList getWrongQuestions() const;
    Q_INVOKABLE bool saveWrongQuestionCorrection(int answerId,
                                                 const QString &sourceType,
                                                 const QString &correctionAnswer,
                                                 const QString &errorReason,
                                                 const QString &knowledgeSummary);
    Q_INVOKABLE bool submitExam(int examId, const QVariantMap &answers);
    Q_INVOKABLE QString exportScoreReportExcel(int examId) const;
    Q_INVOKABLE QString exportScoreHistoryExcel(const QString &subject) const;
    Q_INVOKABLE QString printScoreReportPdf(int examId) const;
    Q_INVOKABLE bool updateProfile(const QVariantMap &profileData);
    Q_INVOKABLE bool changePassword(const QString &oldPassword, const QString &newPassword);
    Q_INVOKABLE bool saveSettings(const QVariantMap &settings);
    Q_INVOKABLE QString lastError() const;
    Q_INVOKABLE void minimizeWindow();
    Q_INVOKABLE void toggleMaximizeWindow();
    Q_INVOKABLE void closeWindow();
    Q_INVOKABLE void logout();
    Q_INVOKABLE void startWindowMove();

private:
    QJsonObject requestJson(const QString &method,
                            const QString &path,
                            const QJsonObject &payload = {},
                            const QUrlQuery &query = {}) const;

    QQuickWidget *view;
    qint64 studentId;
    QString studentName;
    QString studentNo;
    QString className;
    QVariantMap studentSettings;
    mutable QString errorMessage;
};

#endif // STUDENTMAINWINDOW_H
