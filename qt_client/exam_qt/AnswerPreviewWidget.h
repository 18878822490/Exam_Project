#ifndef ANSWERPREVIEWWIDGET_H
#define ANSWERPREVIEWWIDGET_H

#include <QWidget>
#include <QVariantList>
#include <QVariantMap>

class QLabel;
class QScrollArea;
class QVBoxLayout;

class AnswerPreviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AnswerPreviewWidget(QWidget *parent = nullptr);

    void setPaperAnswer(const QVariantMap &student, const QVariantList &questions, int currentQuestionIndex);
    void setCurrentQuestion(int index);

signals:
    void questionSelected(int index);

private:
    void rebuildQuestions();
    QVariantMap currentVisibleQuestion() const;

    QLabel *titleLabel;
    QLabel *autoScoreLabel;
    QLabel *sectionLabel;
    QScrollArea *scrollArea;
    QWidget *contentWidget;
    QVBoxLayout *questionLayout;
    QVariantMap currentStudent;
    QVariantList questionRows;
    int currentIndex;
};

#endif // ANSWERPREVIEWWIDGET_H
