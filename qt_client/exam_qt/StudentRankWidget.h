#ifndef STUDENTRANKWIDGET_H
#define STUDENTRANKWIDGET_H

#include <QFrame>
#include <QVariantList>

class QTableWidget;

class StudentRankWidget : public QFrame
{
    Q_OBJECT

public:
    explicit StudentRankWidget(QWidget *parent = nullptr);

    void setRankData(const QVariantList &rows);

private:
    QTableWidget *table;
};

#endif // STUDENTRANKWIDGET_H
