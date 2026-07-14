#ifndef DISTRIBUTIONCHARTWIDGET_H
#define DISTRIBUTIONCHARTWIDGET_H

#include <QFrame>
#include <QVariantList>

class QBarSeries;
class QBarSet;
class QChart;
class QChartView;

class DistributionChartWidget : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(double animationProgress READ animationProgress WRITE setAnimationProgress)

public:
    explicit DistributionChartWidget(QWidget *parent = nullptr);

    void setDistributionData(const QVariantList &rows);
    void playChartAnimation();
    double animationProgress() const;
    void setAnimationProgress(double value);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void rebuildChart();
    void showBarTip(bool visible, int index);

    QVariantList dataRows;
    QStringList labels;
    QChartView *chartView;
    QChart *chart;
    QBarSeries *series;
    QBarSet *barSet;
    double progress;
};

#endif // DISTRIBUTIONCHARTWIDGET_H
