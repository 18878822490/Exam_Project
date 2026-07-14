#ifndef LEVELPIECHARTWIDGET_H
#define LEVELPIECHARTWIDGET_H

#include <QFrame>
#include <QVariantList>

class QChart;
class QChartView;
class QPieSeries;
class QPieSlice;

class LevelPieChartWidget : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(double animationProgress READ animationProgress WRITE setAnimationProgress)

public:
    explicit LevelPieChartWidget(QWidget *parent = nullptr);

    void setLevelData(const QVariantList &rows);
    void playChartAnimation();
    double animationProgress() const;
    void setAnimationProgress(double value);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void rebuildChart();
    void showSliceTip(QPieSlice *slice, bool visible);

    QVariantList dataRows;
    QChartView *chartView;
    QChart *chart;
    QPieSeries *series;
    double progress;
};

#endif // LEVELPIECHARTWIDGET_H
