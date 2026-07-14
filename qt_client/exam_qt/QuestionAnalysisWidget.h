#ifndef QUESTIONANALYSISWIDGET_H
#define QUESTIONANALYSISWIDGET_H

#include <QFrame>
#include <QVariantList>

class QTableWidget;

class QuestionAnalysisWidget : public QFrame
{
    Q_OBJECT

public:
    explicit QuestionAnalysisWidget(QWidget *parent = nullptr);

    void setQuestionData(const QVariantList &rows);

private:
    QTableWidget *table;
};

#endif // QUESTIONANALYSISWIDGET_H
