#ifndef EXAMINFOCARD_H
#define EXAMINFOCARD_H

#include <QFrame>
#include <QVariantMap>

class QLabel;
class QProgressBar;

class ExamInfoCard : public QFrame
{
    Q_OBJECT

public:
    explicit ExamInfoCard(QWidget *parent = nullptr);

    void setExamInfo(const QVariantMap &exam, int completedCount, int totalCount, double averageScore);
    void playEnterAnimation();

private:
    QFrame *createStatCard(const QString &title, QLabel **valueLabel, const QString &accent);

    QLabel *titleLabel;
    QLabel *courseLabel;
    QLabel *timeLabel;
    QLabel *scoreLabel;
    QLabel *progressLabel;
    QLabel *pendingValueLabel;
    QLabel *averageValueLabel;
    QProgressBar *progressBar;
};

#endif // EXAMINFOCARD_H
