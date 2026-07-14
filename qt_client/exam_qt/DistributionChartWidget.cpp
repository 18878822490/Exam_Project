#include "DistributionChartWidget.h"

#include <QtCharts/QAbstractAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>

#include <QCursor>
#include <QFont>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QToolTip>

DistributionChartWidget::DistributionChartWidget(QWidget *parent)
    : QFrame(parent)
    , chartView(nullptr)
    , chart(new QChart)
    , series(nullptr)
    , barSet(nullptr)
    , progress(1.0)
{
    setObjectName(QStringLiteral("ScoreAnalysisCard"));
    setMinimumHeight(320);
    setMouseTracking(true);

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);

    chart->setTitle(QStringLiteral("成绩分布柱状图"));
    QFont titleFont(QStringLiteral("Microsoft YaHei"));
    titleFont.setPixelSize(26);
    titleFont.setBold(true);
    chart->setTitleFont(titleFont);
    chart->setTitleBrush(QColor(QStringLiteral("#111827")));
    chart->setBackgroundVisible(false);
    chart->setDropShadowEnabled(false);
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setAnimationDuration(820);
    chart->setAnimationEasingCurve(QEasingCurve::OutCubic);
    chart->setMargins(QMargins(10, 8, 10, 8));

    chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing, true);
    chartView->setFrameShape(QFrame::NoFrame);
    chartView->setBackgroundBrush(Qt::NoBrush);
    chartView->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
    chartView->setMouseTracking(true);
    layout->addWidget(chartView);
}

void DistributionChartWidget::setDistributionData(const QVariantList &rows)
{
    dataRows = rows;
    rebuildChart();
}

void DistributionChartWidget::playChartAnimation()
{
    chart->setAnimationOptions(QChart::AllAnimations);
    auto *animation = new QPropertyAnimation(this, "animationProgress", this);
    animation->setDuration(720);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

double DistributionChartWidget::animationProgress() const
{
    return progress;
}

void DistributionChartWidget::setAnimationProgress(double value)
{
    progress = qBound(0.0, value, 1.0);
    chart->setOpacity(progress);
}

void DistributionChartWidget::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);
    chart->setMargins(width() < 520 ? QMargins(4, 4, 4, 4) : QMargins(10, 8, 10, 8));
}

void DistributionChartWidget::rebuildChart()
{
    chart->removeAllSeries();
    const QList<QAbstractAxis *> oldAxes = chart->axes();
    for (QAbstractAxis *axis : oldAxes) {
        chart->removeAxis(axis);
        axis->deleteLater();
    }

    labels.clear();
    series = new QBarSeries(chart);
    series->setBarWidth(0.52);
    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    series->setLabelsFormat(QStringLiteral("@value"));

    barSet = new QBarSet(QStringLiteral("人数"), series);
    barSet->setColor(QColor(QStringLiteral("#2563eb")));
    barSet->setBorderColor(QColor(QStringLiteral("#93c5fd")));
    barSet->setLabelColor(QColor(QStringLiteral("#334155")));

    int maxCount = 1;
    for (const QVariant &value : dataRows) {
        const QVariantMap row = value.toMap();
        const int count = row.value(QStringLiteral("value")).toInt();
        labels.append(row.value(QStringLiteral("label")).toString());
        *barSet << count;
        maxCount = qMax(maxCount, count);
    }

    series->append(barSet);
    chart->addSeries(series);
    connect(barSet, &QBarSet::hovered, this, &DistributionChartWidget::showBarTip);

    auto *axisX = new QBarCategoryAxis(chart);
    axisX->append(labels);
    axisX->setLabelsColor(QColor(QStringLiteral("#64748b")));
    QFont axisFont(QStringLiteral("Microsoft YaHei"));
    axisFont.setPixelSize(14);
    axisFont.setBold(true);
    axisX->setLabelsFont(axisFont);
    axisX->setGridLineVisible(false);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto *axisY = new QValueAxis(chart);
    axisY->setRange(0, maxCount + 2);
    axisY->setTickCount(5);
    axisY->setLabelFormat(QStringLiteral("%.0f"));
    axisY->setLabelsColor(QColor(QStringLiteral("#64748b")));
    axisY->setLabelsFont(axisFont);
    axisY->setGridLineColor(QColor(QStringLiteral("#e2e8f0")));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}

void DistributionChartWidget::showBarTip(bool visible, int index)
{
    if (!visible) {
        QToolTip::hideText();
        return;
    }
    if (index < 0 || index >= labels.size() || barSet == nullptr) {
        return;
    }

    const QString text = QStringLiteral("%1：%2人").arg(labels.at(index), QString::number(barSet->at(index)));
    QToolTip::showText(QCursor::pos(), text, chartView);
}
