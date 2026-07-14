#ifndef SCOREFILTERWIDGET_H
#define SCOREFILTERWIDGET_H

#include <QFrame>

class QComboBox;
class QLabel;
class QPushButton;

class ScoreFilterWidget : public QFrame
{
    Q_OBJECT

public:
    explicit ScoreFilterWidget(QWidget *parent = nullptr);

    void setClasses(const QStringList &classes);
    void setExams(const QStringList &exams);
    void setThirdFilter(const QString &label, const QStringList &items);
    void setQueryButtonText(const QString &text);
    QString currentClass() const;
    QString currentExam() const;
    QString currentTimeRange() const;
    QString currentReportType() const;

signals:
    void queryRequested(const QString &className, const QString &examName, const QString &timeRange);

private:
    QComboBox *classCombo;
    QComboBox *examCombo;
    QComboBox *timeCombo;
    QLabel *thirdFilterLabel;
    QPushButton *queryButton;
};

#endif // SCOREFILTERWIDGET_H
