#ifndef TEACHERMAINWINDOW_H
#define TEACHERMAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QRect>
#include <QString>
#include <QVariantList>
#include <QVariantMap>

class QPainter;
class TeacherDataRepository;
class TeacherMarkWindow;
class ScorePrintWindow;
class TeacherScoreAnalysisWindow;
class QQuickWidget;
class QStackedWidget;

class TeacherMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeacherMainWindow(qint64 teacherId = 0,
                               const QString &teacherName = QString(),
                               const QString &teacherSubject = QString(),
                               QWidget *parent = nullptr);

    Q_INVOKABLE QVariantMap getTeacherProfile() const;
    Q_INVOKABLE QVariantList getTeacherClasses() const;
    Q_INVOKABLE QVariantList getClassStudents(const QString &className) const;
    Q_INVOKABLE QVariantList getExamList() const;
    Q_INVOKABLE QVariantList getQuestions() const;
    Q_INVOKABLE QVariantList searchQuestions(const QString &keyword, const QString &type, const QString &difficulty) const;
    Q_INVOKABLE QVariantList searchQuestionsAdvanced(const QString &keyword,
                                                     const QString &subject,
                                                     const QString &type,
                                                     const QString &difficulty,
                                                     const QString &knowledgePoint) const;
    Q_INVOKABLE QVariantList getImportLogs() const;
    Q_INVOKABLE QVariantList getPendingReviews() const;
    Q_INVOKABLE QVariantList getStudentAnswers() const;
    Q_INVOKABLE QVariantList getStudentAnswersForPaper(int paperId) const;
    Q_INVOKABLE QVariantList getStudentAnswersForStudent(int paperId, const QString &studentNo) const;
    Q_INVOKABLE QVariantList getPaperQuestions(int paperId) const;
    Q_INVOKABLE QVariantList getTodoItems() const;
    Q_INVOKABLE QVariantMap getDashboardStats() const;
    Q_INVOKABLE QVariantMap getScoreStatistics() const;
    Q_INVOKABLE QVariantList getClassScoreTrend(const QString &className, const QString &subject) const;
    Q_INVOKABLE QVariantList getQuestionAnalysis() const;
    Q_INVOKABLE int addQuestion(const QVariantMap &question);
    Q_INVOKABLE bool updateQuestion(int id, const QVariantMap &question);
    Q_INVOKABLE bool removeQuestion(int id);
    Q_INVOKABLE bool addTodoItem(const QString &title, const QString &type, const QString &remindTime);
    Q_INVOKABLE int importQuestionsFromFile(const QString &fileUrl);
    Q_INVOKABLE QVariantMap reserveOcrImport(const QString &fileUrl);
    Q_INVOKABLE QString exportScoreReportPdf();
    Q_INVOKABLE bool printScoreReport();
    Q_INVOKABLE int createDraftPaper(const QString &name,
                                     const QString &subject,
                                     const QString &startTime,
                                     const QString &endTime,
                                     const QVariantMap &counts);
    Q_INVOKABLE int createDraftPaperFromQuestions(const QString &name,
                                                  const QString &subject,
                                                  const QString &startTime,
                                                  const QString &endTime,
                                                  const QVariantList &questions);
    Q_INVOKABLE int copyExamAsDraft(const QString &examName,
                                    const QString &startTime,
                                    const QString &endTime);
    Q_INVOKABLE int copyExamAsDraftById(int examId, const QString &copyTitle);
    Q_INVOKABLE bool publishExam(int paperId,
                                 const QVariantList &classNames,
                                 const QString &startTime,
                                 const QString &endTime);
    Q_INVOKABLE bool saveReviewScore(int answerId, double score, const QString &comment);
    Q_INVOKABLE bool updateTeacherProfile(const QVariantMap &profileData);
    Q_INVOKABLE bool changePassword(const QString &oldPassword, const QString &newPassword);
    Q_INVOKABLE QString lastError() const;
    Q_INVOKABLE void minimizeWindow();
    Q_INVOKABLE void toggleMaximizeWindow();
    Q_INVOKABLE void closeWindow();
    Q_INVOKABLE void logout();
    Q_INVOKABLE void openMarkWorkbench();
    Q_INVOKABLE void openScoreAnalysisWorkbench();
    Q_INVOKABLE void openScorePrintWorkbench();
    Q_INVOKABLE void startWindowMove();

private:
    void openTeacherPage(int page);
    QDateTime parseDateTime(const QString &value) const;
    QString localFilePath(const QString &fileUrl) const;
    void appendImportLog(const QString &type, const QString &fileName, int count, const QString &status, const QString &message);
    void paintScoreReport(QPainter *painter, const QRect &pageRect) const;

    QQuickWidget *view;
    QStackedWidget *centralStack;
    TeacherMarkWindow *markWorkbench;
    ScorePrintWindow *scorePrintWorkbench;
    TeacherScoreAnalysisWindow *scoreAnalysisWorkbench;
    TeacherDataRepository *repository;
    QVariantList importLogs;
    qint64 teacherId;
    QString fallbackTeacherName;
    QString fallbackTeacherSubject;
};

#endif // TEACHERMAINWINDOW_H
