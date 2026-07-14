#ifndef TEACHERDATAREPOSITORY_H
#define TEACHERDATAREPOSITORY_H

#include <QObject>
#include <QDateTime>
#include <QSqlDatabase>
#include <QVariantList>
#include <QVariantMap>

class QNetworkAccessManager;
class QSqlRecord;

class TeacherDataRepository : public QObject
{
    Q_OBJECT

public:
    explicit TeacherDataRepository(qint64 teacherId = 0, QObject *parent = nullptr);
    ~TeacherDataRepository();

    bool initialize();
    QString lastError() const;

    QVariantMap getTeacherProfile() const;
    QVariantMap dashboardStats() const;
    QVariantList getTeacherClasses() const;
    QVariantList getClassStudents(const QString &className) const;
    QVariantList getExamList() const;
    QVariantList getQuestions() const;
    QVariantList searchQuestions(const QString &keyword, const QString &type, const QString &difficulty) const;
    QVariantList searchQuestionsAdvanced(const QString &keyword,
                                         const QString &subject,
                                         const QString &type,
                                         const QString &difficulty,
                                         const QString &knowledgePoint) const;
    QVariantList getQuestionAnalysis() const;
    QVariantMap getScoreStatistics() const;
    QVariantList getClassScoreTrend(const QString &className, const QString &subject) const;
    QVariantList getPendingReviews() const;
    QVariantList getStudentAnswers() const;
    QVariantList getStudentAnswersForPaper(int paperId) const;
    QVariantList getStudentAnswersForStudent(int paperId, const QString &studentNo) const;
    QVariantList getReviewExams() const;
    QVariantList getReviewStudents(int examId) const;
    QVariantList getReviewStudentAnswers(int examId, const QString &studentNo) const;
    QVariantList getPaperQuestions(int paperId) const;
    QVariantList getTodoItems() const;
    QVariantList getImportLogs() const;

    int addQuestion(const QVariantMap &question);
    bool updateQuestion(int id, const QVariantMap &question);
    bool removeQuestion(int id);
    int importQuestionsFromCsv(const QString &filePath);
    bool recordImportLog(const QString &type, const QString &fileName, int totalCount, int successCount, int failedCount, const QString &status, const QString &message);
    bool addTodoItem(const QString &title, const QString &type, const QString &remindTime);

    int createDraftPaper(const QString &name,
                         const QString &subject,
                         const QDateTime &startTime,
                         const QDateTime &endTime,
                         const QVariantMap &counts);
    int createDraftPaperFromQuestions(const QString &name,
                                      const QString &subject,
                                      const QDateTime &startTime,
                                      const QDateTime &endTime,
                                      const QVariantList &questions);
    int copyExamAsDraft(const QString &examName, const QDateTime &startTime, const QDateTime &endTime);
    int copyExamAsDraftById(int examId, const QString &copyTitle);
    bool publishExam(int paperId, const QStringList &classNames, const QDateTime &startTime, const QDateTime &endTime);
    bool saveReviewScore(int answerId, double score, const QString &comment);
    bool updateTeacherProfile(const QVariantMap &profileData);
    bool changePassword(const QString &oldPassword, const QString &newPassword);

private:
    bool openDatabase();
    bool createSchema();
    bool ensureColumn(const QString &tableName, const QString &columnName, const QString &definition);
    void dropOldTeacherClassForeignKeys();
    void seedData();
    int scoreForType(const QString &type) const;
    QVariantMap rowToMap(const QSqlRecord &record) const;

    QSqlDatabase db;
    QNetworkAccessManager *network;
    QString errorMessage;
    qint64 teacherId;
};

#endif // TEACHERDATAREPOSITORY_H
