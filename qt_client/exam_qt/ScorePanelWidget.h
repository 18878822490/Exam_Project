#ifndef SCOREPANELWIDGET_H
#define SCOREPANELWIDGET_H

#include <QWidget>
#include <QVariantMap>

class QLabel;
class QDoubleValidator;
class QLineEdit;
class QPushButton;
class QTextEdit;

class ScorePanelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScorePanelWidget(QWidget *parent = nullptr);

    void setQuestion(const QVariantMap &question);
    void showSaveSuccess();

signals:
    void saveScoreRequested(double score, const QString &comment);
    void submitQuestionRequested(double score, const QString &comment);
    void previousQuestionRequested();
    void nextQuestionRequested();

private:
    void setEditorEnabled(bool enabled);
    QPushButton *quickButton(const QString &label, double ratio);

    QLabel *questionLabel;
    QLabel *maxScoreLabel;
    QLabel *stateLabel;
    QLabel *successLabel;
    QLabel *scoreSuffixLabel;
    QLineEdit *scoreEdit;
    QTextEdit *commentEdit;
    QPushButton *saveButton;
    QPushButton *submitButton;
    QPushButton *previousButton;
    QPushButton *nextButton;
    QDoubleValidator *scoreValidator;
    QList<QPushButton *> quickButtons;
    QVariantMap currentQuestion;
};

#endif // SCOREPANELWIDGET_H
