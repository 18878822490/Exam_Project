#include "LevelPieChartWidget.h"

#include <QtCharts/QAbstractAxis>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include <QCursor>
#include <QFont>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QToolTip>

namespace {
QStringList defaultColors()
{
    return {
        QStringLiteral("#2563eb"),
        QStringLiteral("#16a34a"),
        QStringLiteral("#f59e0b"),
        QStringLiteral("#8b5cf6"),
        QStringLiteral("#ef4444")
    };
}
}

LevelPieChartWidget::LevelPieChartWidget(QWidget *parent)
    : QFrame(parent)
    , chartView(nullptr)
    , chart(new QChart)
    , series(nullptr)
    , progress(1.0)
{
    setObjectName(QStringLiteral("ScoreAnalysisCard"));
    setMinimumHeight(320);
    setMouseTracking(true);

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);

    chart->setTitle(QStringLiteral("成绩等级饼图"));
    QFont titleFont(QStringLiteral("Microsoft YaHei"));
    titleFont.setPixelSize(26);
    titleFont.setBold(true);
    chart->setTitleFont(titleFont);
    chart->setTitleBrush(QColor(QStringLiteral("#111827")));
    chart->setBackgroundVisible(false);
    chart->setDropShadowEnabled(false);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setAnimationDuration(820);
    chart->setAnimationEasingCurve(QEasingCurve::OutCubic);
    chart->setMargins(QMargins(8, 8, 8, 8));
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setLabelColor(QColor(QStringLiteral("#334155")));
    QFont legendFont(QStringLiteral("Microsoft YaHei"));
    legendFont.setPixelSize(14);
    legendFont.setBold(true);
    chart->legend()->setFont(legendFont);

    chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing, true);
    chartView->setFrameShape(QFrame::NoFrame);
    chartView->setBackgroundBrush(Qt::NoBrush);
    chartView->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
    chartView->setMouseTracking(true);
    layout->addWidget(chartView);
}

void LevelPieChartWidget::setLevelData(const QVariantList &rows)
{
    dataRows = rows;
    rebuildChart();
}

void LevelPieChartWidget::playChartAnimation()
{
    chart->setAnimationOptions(QChart::AllAnimations);
    auto *animation = new QPropertyAnimation(this, "animationProgress", this);
    animation->setDuration(720);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

double LevelPieChartWidget::animationProgress() const
{
    return progress;
}

void LevelPieChartWidget::setAnimationProgress(double value)
{
    progress = qBound(0.0, value, 1.0);
    chart->setOpacity(progress);
}

void LevelPieChartWidget::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);
    chart->legend()->setAlignment(width() < 560 ? Qt::AlignBottom : Qt::AlignRight);
}

void LevelPieChartWidget::rebuildChart()
{
    chart->removeAllSeries();
    const QList<QAbstractAxis *> oldAxes = chart->axes();
    for (QAbstractAxis *axis : oldAxes) {
        chart->removeAxis(axis);
        axis->deleteLater();
    }

    series = new QPieSeries(chart);
    series->setHoleSize(0.36);
    series->setPieSize(0.72);

    const QStringList colors = defaultColors();
    for (int i = 0; i < dataRows.size(); ++i) {
        const QVariantMap row = dataRows.at(i).toMap();
        const int count = row.value(QStringLiteral("value")).toInt();
        auto *slice = series->append(
                QStringLiteral("%1  %2人").arg(row.value(QStringLiteral("label")).toString(), QString::number(count)),
                count);
        slice->setColor(QColor(row.value(QStringLiteral("color"), colors.value(i % colors.size())).toString()));
        slice->setBorderColor(Qt::white);
        slice->setBorderWidth(2);
        connect(slice, &QPieSlice::hovered, this, [this, slice](bool visible) {
            showSliceTip(slice, visible);
        });
    }

    chart->addSeries(series);
    chart->legend()->setMarkerShape(QLegend::MarkerShapeCircle);
}

void LevelPieChartWidget::showSliceTip(QPieSlice *slice, bool visible)
{
    if (slice == nullptr) {
        return;
    }

    slice->setExploded(visible);
    slice->setLabelVisible(visible);
    slice->setExplodeDistanceFactor(0.08);

    if (!visible) {
        QToolTip::hideText();
        return;
    }

    const QString text = QStringLiteral("%1：%2%")
            .arg(slice->label(), QString::number(slice->percentage() * 100.0, 'f', 1));
    QToolTip::showText(QCursor::pos(), text, chartView);
}
