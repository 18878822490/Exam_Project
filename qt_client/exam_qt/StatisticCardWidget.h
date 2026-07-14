#ifndef STATISTICCARDWIDGET_H
#define STATISTICCARDWIDGET_H

#include <QFrame>

class QLabel;

class StatisticCardWidget : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(double revealProgress READ revealProgress WRITE setRevealProgress)

public:
    explicit StatisticCardWidget(const QString &title = QString(),
                                 const QString &accent = QStringLiteral("#2563eb"),
                                 QWidget *parent = nullptr);

    void setStatistic(const QString &title, const QString &value, const QString &caption, const QString &accent);
    void playLoadAnimation(int delayMs = 0);
    double revealProgress() const;
    void setRevealProgress(double value);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QLabel *titleLabel;
    QLabel *valueLabel;
    QLabel *captionLabel;
    QString accentColor;
    double progress;
};

#endif // STATISTICCARDWIDGET_H
