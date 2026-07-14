#ifndef TEACHERSCOREANALYSISWINDOW_H
#define TEACHERSCOREANALYSISWINDOW_H

#include <QVariantList>
#include <QVariantMap>
#include <QWidget>

class DistributionChartWidget;
class LevelPieChartWidget;
class QuestionAnalysisWidget;
class ScoreFilterWidget;
class StatisticCardWidget;
class StudentRankWidget;
class TeacherDataRepository;
class TrendChartWidget;
class QGridLayout;
class QScrollArea;
class QVBoxLayout;

class TeacherScoreAnalysisWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherScoreAnalysisWindow(QWidget *parent = nullptr);

    void setRepository(TeacherDataRepository *dataRepository);
    void loadInitialData();
    QVariantList loadClassScore(const QString &className, const QString &examName, const QString &timeRange);
    QVariantMap loadExamStatistics(const QVariantList &scores);
    QVariantList loadScoreTrend(const QString &className, const QString &timeRange);
    QVariantList loadQuestionAnalysis(const QString &className, const QString &examName);
    void playEnterAnimation();

signals:
    void backRequested();
    void pageRequested(int page);
    void printReportRequested();
    void minimizeRequested();
    void maximizeRequested();
    void closeRequested();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void buildUi();
    void applyStyle();
    void applyFilter(const QString &className, const QString &examName, const QString &timeRange);
    void refreshStatisticCards(const QVariantMap &stats);
    QVariantList buildDistribution(const QVariantList &scores) const;
    QVariantList buildLevelData(const QVariantList &scores) const;
    void relayoutResponsiveSections();
    QStringList repositoryClassNames() const;
    QStringList repositoryExamNames() const;

    TeacherDataRepository *repository;
    ScoreFilterWidget *filterWidget;
    StatisticCardWidget *averageCard;
    StatisticCardWidget *highestCard;
    StatisticCardWidget *lowestCard;
    StatisticCardWidget *excellentCard;
    TrendChartWidget *trendChart;
    DistributionChartWidget *distributionChart;
    LevelPieChartWidget *levelPieChart;
    StudentRankWidget *rankWidget;
    QuestionAnalysisWidget *questionWidget;
    QScrollArea *scrollArea;
    QWidget *contentWidget;
    QVBoxLayout *contentLayout;
    QGridLayout *statGrid;
    QGridLayout *chartGrid;
    bool compactLayout;
};

#endif // TEACHERSCOREANALYSISWINDOW_H
