#include "StatisticCardWidget.h"

#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QPainter>
#include <QPropertyAnimation>
#include <QTimer>
#include <QVBoxLayout>

StatisticCardWidget::StatisticCardWidget(const QString &title, const QString &accent, QWidget *parent)
    : QFrame(parent)
    , titleLabel(new QLabel(title, this))
    , valueLabel(new QLabel(QStringLiteral("--"), this))
    , captionLabel(new QLabel(QStringLiteral("等待查询"), this))
    , accentColor(accent)
    , progress(1.0)
{
    setObjectName(QStringLiteral("ScoreStatisticCard"));
    setMinimumHeight(180);

    titleLabel->setObjectName(QStringLiteral("ScoreStatTitle"));
    valueLabel->setObjectName(QStringLiteral("ScoreStatValue"));
    captionLabel->setObjectName(QStringLiteral("ScoreStatCaption"));
    valueLabel->setStyleSheet(QStringLiteral("color:%1;").arg(accentColor));

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(26, 22, 26, 22);
    layout->setSpacing(10);
    layout->addWidget(titleLabel);
    layout->addWidget(valueLabel);
    layout->addStretch();
    layout->addWidget(captionLabel);
}

void StatisticCardWidget::setStatistic(const QString &title, const QString &value, const QString &caption, const QString &accent)
{
    accentColor = accent;
    titleLabel->setText(title);
    valueLabel->setText(value);
    captionLabel->setText(caption);
    valueLabel->setStyleSheet(QStringLiteral("color:%1;").arg(accentColor));
    update();
}

void StatisticCardWidget::playLoadAnimation(int delayMs)
{
    progress = 0.0;

    auto startAnimation = [this]() {
        auto *reveal = new QPropertyAnimation(this, "revealProgress", this);
        reveal->setDuration(520);
        reveal->setStartValue(0.0);
        reveal->setEndValue(1.0);
        reveal->setEasingCurve(QEasingCurve::OutCubic);
        reveal->start(QAbstractAnimation::DeleteWhenStopped);
    };

    if (delayMs > 0) {
        QTimer::singleShot(delayMs, this, startAnimation);
    } else {
        startAnimation();
    }
}

double StatisticCardWidget::revealProgress() const
{
    return progress;
}

void StatisticCardWidget::setRevealProgress(double value)
{
    progress = qBound(0.0, value, 1.0);
    update();
}

void StatisticCardWidget::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    const QColor accent(accentColor);
    QRectF barRect(22, height() - 8, (width() - 44) * progress, 4);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(accent.red(), accent.green(), accent.blue(), 42));
    painter.drawRoundedRect(QRectF(22, height() - 8, width() - 44, 4), 2, 2);
    painter.setBrush(accent);
    painter.drawRoundedRect(barRect, 2, 2);
}
