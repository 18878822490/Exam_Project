#include "TrendChartWidget.h"

#include <QtCharts/QAbstractAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include <QCursor>
#include <QFont>
#include <QHBoxLayout>
#include <QPen>
#include <QPropertyAnimation>
#include <QToolTip>

TrendChartWidget::TrendChartWidget(QWidget *parent)
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

    chart->setTitle(QStringLiteral("成绩趋势折线图"));
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

void TrendChartWidget::setTrendData(const QVariantList &rows)
{
    dataRows = rows;
    rebuildChart();
}

void TrendChartWidget::playChartAnimation()
{
    chart->setAnimationOptions(QChart::AllAnimations);
    auto *animation = new QPropertyAnimation(this, "animationProgress", this);
    animation->setDuration(760);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

double TrendChartWidget::animationProgress() const
{
    return progress;
}

void TrendChartWidget::setAnimationProgress(double value)
{
    progress = qBound(0.0, value, 1.0);
    chart->setOpacity(progress);
}

void TrendChartWidget::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);
    chart->setMargins(width() < 560 ? QMargins(4, 4, 4, 4) : QMargins(10, 8, 10, 8));
}

void TrendChartWidget::rebuildChart()
{
    chart->removeAllSeries();
    const QList<QAbstractAxis *> oldAxes = chart->axes();
    for (QAbstractAxis *axis : oldAxes) {
        chart->removeAxis(axis);
        axis->deleteLater();
    }

    labels.clear();
    series = new QLineSeries(chart);
    series->setName(QStringLiteral("班级平均分"));
    series->setColor(QColor(QStringLiteral("#2563eb")));
    series->setPen(QPen(QColor(QStringLiteral("#2563eb")), 3.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    series->setPointsVisible(true);
    series->setPointLabelsVisible(false);

    double minValue = 100.0;
    double maxValue = 0.0;
    for (int i = 0; i < dataRows.size(); ++i) {
        const QVariantMap row = dataRows.at(i).toMap();
        const double score = row.value(QStringLiteral("value")).toDouble();
        labels.append(row.value(QStringLiteral("label")).toString());
        series->append(i, score);
        minValue = qMin(minValue, score);
        maxValue = qMax(maxValue, score);
    }

    chart->addSeries(series);
    connect(series, &QLineSeries::hovered, this, &TrendChartWidget::showPointTip);

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
    if (dataRows.isEmpty()) {
        axisY->setRange(0, 100);
    } else {
        const double lower = qMax(0.0, qFloor((minValue - 5.0) / 10.0) * 10.0);
        const double upper = qMin(100.0, qCeil((maxValue + 5.0) / 10.0) * 10.0);
        axisY->setRange(lower, qFuzzyCompare(lower, upper) ? lower + 10.0 : upper);
    }
    axisY->setTickCount(5);
    axisY->setLabelFormat(QStringLiteral("%.0f"));
    axisY->setLabelsColor(QColor(QStringLiteral("#64748b")));
    axisY->setLabelsFont(axisFont);
    axisY->setGridLineColor(QColor(QStringLiteral("#e2e8f0")));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}

void TrendChartWidget::showPointTip(const QPointF &point, bool visible)
{
    if (!visible) {
        QToolTip::hideText();
        return;
    }

    const int index = qRound(point.x());
    if (index < 0 || index >= labels.size()) {
        return;
    }
    const QString text = QStringLiteral("%1：%2分")
            .arg(labels.at(index), QString::number(point.y(), 'f', 1));
    QToolTip::showText(QCursor::pos(), text, chartView);
}
