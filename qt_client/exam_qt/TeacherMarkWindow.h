#ifndef TEACHERMARKWINDOW_H
#define TEACHERMARKWINDOW_H

#include <QWidget>
#include <QMap>
#include <QVariantList>
#include <QVariantMap>

class AnswerPreviewWidget;
class ExamInfoCard;
class ScorePanelWidget;
class StudentListWidget;
class TeacherDataRepository;
class QComboBox;

class TeacherMarkWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherMarkWindow(QWidget *parent = nullptr);

    void setRepository(TeacherDataRepository *dataRepository);
    void loadExam(int examId = 0);
    void loadStudents();
    void loadPaperAnswer(const QString &studentNo);
    bool saveScore(int questionIndex, double score, const QString &comment);
    void playEnterAnimation();

signals:
    void backRequested();
    void pageRequested(int page);
    void minimizeRequested();
    void maximizeRequested();
    void closeRequested();

private slots:
    void selectStudent(int index);
    void selectQuestion(int index);
    void saveCurrentScore(double score, const QString &comment);
    void submitCurrentQuestion(double score, const QString &comment);
    void goPreviousStudent();
    void goNextStudent();
    void goPreviousQuestion();
    void goNextQuestion();

private:
    void buildUi();
    void applyStyle();
    void seedMockData();
    void loadBackendExam(int examId);
    QVariantMap normalizeExam(const QVariantMap &exam) const;
    void refreshExamSelector();
    void refreshAll();
    void refreshExamInfo();
    void refreshStudent();
    QVariantMap currentStudent() const;
    QVariantList currentAnswers() const;
    QVariantMap currentQuestion() const;
    void setCurrentQuestion(int index);
    int firstTeacherQuestionIndex(const QVariantList &answers) const;
    int adjacentTeacherQuestionIndex(int fromIndex, int direction) const;
    bool isStudentCompleted(const QVariantList &answers) const;
    double totalScore(const QVariantList &answers) const;

    ExamInfoCard *examInfoCard;
    QComboBox *examCombo;
    StudentListWidget *studentListWidget;
    AnswerPreviewWidget *answerPreviewWidget;
    ScorePanelWidget *scorePanelWidget;
    QVariantMap examInfo;
    QVariantList reviewExams;
    QVariantList students;
    QMap<QString, QVariantList> answersByStudent;
    TeacherDataRepository *repository;
    int currentExamId;
    bool backendDataLoaded;
    bool syncingExamCombo;
    int currentStudentIndex;
    int currentQuestionIndex;
};

#endif // TEACHERMARKWINDOW_H
