#ifndef TRENDCHARTWIDGET_H
#define TRENDCHARTWIDGET_H

#include <QFrame>
#include <QVariantList>

class QChart;
class QChartView;
class QLineSeries;

class TrendChartWidget : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(double animationProgress READ animationProgress WRITE setAnimationProgress)

public:
    explicit TrendChartWidget(QWidget *parent = nullptr);

    void setTrendData(const QVariantList &rows);
    void playChartAnimation();
    double animationProgress() const;
    void setAnimationProgress(double value);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void rebuildChart();
    void showPointTip(const QPointF &point, bool visible);

    QVariantList dataRows;
    QStringList labels;
    QChartView *chartView;
    QChart *chart;
    QLineSeries *series;
    double progress;
};

#endif // TRENDCHARTWIDGET_H
