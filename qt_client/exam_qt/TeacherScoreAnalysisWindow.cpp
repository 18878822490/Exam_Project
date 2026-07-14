#include "TeacherScoreAnalysisWindow.h"

#include "DistributionChartWidget.h"
#include "LevelPieChartWidget.h"
#include "QuestionAnalysisWidget.h"
#include "ScoreFilterWidget.h"
#include "StatisticCardWidget.h"
#include "StudentRankWidget.h"
#include "TeacherDataRepository.h"
#include "TrendChartWidget.h"

#include <QComboBox>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QPair>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QResizeEvent>
#include <QScrollArea>
#include <QTimer>
#include <QVBoxLayout>
#include <algorithm>

namespace {
void addShadow(QWidget *widget, int blur = 28, int y = 10)
{
    auto *shadow = new QGraphicsDropShadowEffect(widget);
    shadow->setBlurRadius(blur);
    shadow->setOffset(0, y);
    shadow->setColor(QColor(29, 49, 86, 24));
    widget->setGraphicsEffect(shadow);
}

QPushButton *windowButton(const QString &text, QWidget *parent)
{
    auto *button = new QPushButton(text, parent);
    button->setObjectName(QStringLiteral("ScoreWindowButton"));
    button->setCursor(Qt::PointingHandCursor);
    button->setFixedSize(44, 40);
    return button;
}

QPushButton *navButton(const QString &text, int page, int activePage, QWidget *parent = nullptr)
{
    auto *button = new QPushButton(text, parent);
    button->setObjectName(QStringLiteral("ScoreNavButton"));
    button->setCursor(Qt::PointingHandCursor);
    button->setProperty("page", page);
    button->setProperty("active", page == activePage);
    button->setMinimumSize(112, 48);
    return button;
}

QStringList fallbackClasses()
{
    return {
        QStringLiteral("软件工程2501班"),
        QStringLiteral("计算机科学2502班"),
        QStringLiteral("人工智能2501班")
    };
}

QStringList fallbackExams()
{
    return {
        QStringLiteral("Java期末考试"),
        QStringLiteral("Java阶段测试"),
        QStringLiteral("数据结构单元测验"),
        QStringLiteral("算法综合训练")
    };
}

void slideCardIn(QWidget *widget, const QPoint &offset, int delayMs)
{
    if (widget == nullptr) {
        return;
    }
    QTimer::singleShot(delayMs, widget, [widget, offset]() {
        const QPoint end = widget->pos();
        auto *animation = new QPropertyAnimation(widget, "pos", widget);
        widget->move(end + offset);
        animation->setDuration(360);
        animation->setStartValue(widget->pos());
        animation->setEndValue(end);
        animation->setEasingCurve(QEasingCurve::OutCubic);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    });
}
}

TeacherScoreAnalysisWindow::TeacherScoreAnalysisWindow(QWidget *parent)
    : QWidget(parent)
    , repository(nullptr)
    , filterWidget(nullptr)
    , averageCard(nullptr)
    , highestCard(nullptr)
    , lowestCard(nullptr)
    , excellentCard(nullptr)
    , trendChart(nullptr)
    , distributionChart(nullptr)
    , levelPieChart(nullptr)
    , rankWidget(nullptr)
    , questionWidget(nullptr)
    , scrollArea(nullptr)
    , contentWidget(nullptr)
    , contentLayout(nullptr)
    , statGrid(nullptr)
    , chartGrid(nullptr)
    , compactLayout(false)
{
    setObjectName(QStringLiteral("TeacherScoreAnalysisWindow"));
    buildUi();
    applyStyle();
    loadInitialData();
}

void TeacherScoreAnalysisWindow::setRepository(TeacherDataRepository *dataRepository)
{
    repository = dataRepository;
    loadInitialData();
}

void TeacherScoreAnalysisWindow::loadInitialData()
{
    const QStringList classes = repositoryClassNames();
    const QStringList exams = repositoryExamNames();
    filterWidget->setClasses(classes.isEmpty() ? fallbackClasses() : classes);
    filterWidget->setExams(exams.isEmpty() ? fallbackExams() : exams);
    applyFilter(filterWidget->currentClass(), filterWidget->currentExam(), filterWidget->currentTimeRange());
}

QVariantList TeacherScoreAnalysisWindow::loadClassScore(const QString &className, const QString &examName, const QString &timeRange)
{
    Q_UNUSED(timeRange)
    const QStringList names = {
        QStringLiteral("石晓虹"), QStringLiteral("张思远"), QStringLiteral("李雨涵"), QStringLiteral("王一鸣"),
        QStringLiteral("陈嘉宁"), QStringLiteral("赵若溪"), QStringLiteral("刘子墨"), QStringLiteral("周明轩"),
        QStringLiteral("孙亦辰"), QStringLiteral("吴佳怡"), QStringLiteral("郑云帆"), QStringLiteral("高梓萱"),
        QStringLiteral("马天宇"), QStringLiteral("何清越"), QStringLiteral("罗星然"), QStringLiteral("许安琪"),
        QStringLiteral("宋景行"), QStringLiteral("林芷若"), QStringLiteral("唐书宁"), QStringLiteral("韩知远")
    };

    const uint seed = qHash(className + examName);
    QVariantList rows;
    for (int i = 0; i < names.size(); ++i) {
        const double wave = ((seed / (i + 3)) % 19) - 8;
        const double score = qBound(42.0, 76.0 + wave + (i % 5) * 3.5 - (i % 4) * 1.8, 99.0);
        rows.append(QVariantMap{
            {QStringLiteral("studentNo"), QStringLiteral("S%1%2").arg(seed % 100, 2, 10, QLatin1Char('0')).arg(i + 1, 3, 10, QLatin1Char('0'))},
            {QStringLiteral("name"), names.at(i)},
            {QStringLiteral("score"), score}
        });
    }

    std::sort(rows.begin(), rows.end(), [](const QVariant &left, const QVariant &right) {
        return left.toMap().value(QStringLiteral("score")).toDouble()
                > right.toMap().value(QStringLiteral("score")).toDouble();
    });
    return rows;
}

QVariantMap TeacherScoreAnalysisWindow::loadExamStatistics(const QVariantList &scores)
{
    if (scores.isEmpty()) {
        return {
            {QStringLiteral("average"), 0},
            {QStringLiteral("highest"), 0},
            {QStringLiteral("lowest"), 0},
            {QStringLiteral("excellentRate"), 0}
        };
    }

    double sum = 0;
    double highest = 0;
    double lowest = 100;
    int excellent = 0;
    for (const QVariant &value : scores) {
        const double score = value.toMap().value(QStringLiteral("score")).toDouble();
        sum += score;
        highest = qMax(highest, score);
        lowest = qMin(lowest, score);
        if (score >= 90) {
            ++excellent;
        }
    }
    return {
        {QStringLiteral("average"), sum / scores.size()},
        {QStringLiteral("highest"), highest},
        {QStringLiteral("lowest"), lowest},
        {QStringLiteral("excellentRate"), excellent * 100.0 / scores.size()}
    };
}

QVariantList TeacherScoreAnalysisWindow::loadScoreTrend(const QString &className, const QString &timeRange)
{
    Q_UNUSED(timeRange)
    const uint seed = qHash(className);
    const QStringList labels = {
        QStringLiteral("第一次"),
        QStringLiteral("第二次"),
        QStringLiteral("第三次"),
        QStringLiteral("第四次"),
        QStringLiteral("第五次"),
        QStringLiteral("第六次")
    };

    QVariantList rows;
    for (int i = 0; i < labels.size(); ++i) {
        const double base = 72.0 + i * 2.4 + ((seed / (i + 5)) % 9);
        rows.append(QVariantMap{
            {QStringLiteral("label"), labels.at(i)},
            {QStringLiteral("value"), qBound(58.0, base, 94.0)}
        });
    }
    return rows;
}

QVariantList TeacherScoreAnalysisWindow::loadQuestionAnalysis(const QString &className, const QString &examName)
{
    const uint seed = qHash(className + examName + QStringLiteral("questions"));
    const QStringList types = {
        QStringLiteral("单选题"),
        QStringLiteral("多选题"),
        QStringLiteral("判断题"),
        QStringLiteral("填空题"),
        QStringLiteral("简答题"),
        QStringLiteral("编程题"),
        QStringLiteral("分析题"),
        QStringLiteral("综合题")
    };

    QVariantList rows;
    for (int i = 0; i < types.size(); ++i) {
        const double full = i < 4 ? 5.0 : (i < 6 ? 10.0 : 15.0);
        const double rate = qBound(0.38, 0.58 + ((seed / (i + 7)) % 32) / 100.0, 0.96);
        rows.append(QVariantMap{
            {QStringLiteral("number"), i + 1},
            {QStringLiteral("type"), types.at(i)},
            {QStringLiteral("full"), full},
            {QStringLiteral("average"), full * rate}
        });
    }
    std::sort(rows.begin(), rows.end(), [](const QVariant &left, const QVariant &right) {
        const QVariantMap leftRow = left.toMap();
        const QVariantMap rightRow = right.toMap();
        const double leftRate = leftRow.value(QStringLiteral("average")).toDouble() / qMax(1.0, leftRow.value(QStringLiteral("full")).toDouble());
        const double rightRate = rightRow.value(QStringLiteral("average")).toDouble() / qMax(1.0, rightRow.value(QStringLiteral("full")).toDouble());
        return leftRate < rightRate;
    });
    return rows;
}

void TeacherScoreAnalysisWindow::playEnterAnimation()
{
    QTimer::singleShot(0, this, [this]() {
        slideCardIn(filterWidget, QPoint(0, -34), 0);
        slideCardIn(averageCard, QPoint(-34, 0), 80);
        slideCardIn(highestCard, QPoint(-24, 0), 130);
        slideCardIn(lowestCard, QPoint(24, 0), 180);
        slideCardIn(excellentCard, QPoint(34, 0), 230);
        slideCardIn(trendChart, QPoint(0, 38), 180);
        slideCardIn(distributionChart, QPoint(-38, 0), 250);
        slideCardIn(levelPieChart, QPoint(38, 0), 300);
        slideCardIn(rankWidget, QPoint(-38, 0), 350);
        slideCardIn(questionWidget, QPoint(38, 0), 400);
    });

    averageCard->playLoadAnimation(50);
    highestCard->playLoadAnimation(120);
    lowestCard->playLoadAnimation(190);
    excellentCard->playLoadAnimation(260);
    QTimer::singleShot(180, trendChart, &TrendChartWidget::playChartAnimation);
    QTimer::singleShot(260, distributionChart, &DistributionChartWidget::playChartAnimation);
    QTimer::singleShot(340, levelPieChart, &LevelPieChartWidget::playChartAnimation);
}

void TeacherScoreAnalysisWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    relayoutResponsiveSections();
}

void TeacherScoreAnalysisWindow::buildUi()
{
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(28, 22, 28, 26);
    root->setSpacing(20);

    auto *topNav = new QFrame(this);
    topNav->setObjectName(QStringLiteral("ScoreTopNav"));
    topNav->setMinimumHeight(96);
    auto *toolbar = new QHBoxLayout(topNav);
    toolbar->setContentsMargins(22, 14, 18, 14);
    toolbar->setSpacing(14);

    auto *brandBox = new QVBoxLayout;
    brandBox->setSpacing(0);
    auto *brand = new QLabel(QStringLiteral("智考星"), topNav);
    brand->setObjectName(QStringLiteral("ScoreBrandTitle"));
    auto *subtitle = new QLabel(QStringLiteral("考试系统教师端"), topNav);
    subtitle->setObjectName(QStringLiteral("ScoreBrandSubtitle"));
    brandBox->addWidget(brand);
    brandBox->addWidget(subtitle);

    auto *navRow = new QHBoxLayout;
    navRow->setSpacing(10);
    const QList<QPair<QString, int>> pages = {
        {QStringLiteral("教师首页"), 0},
        {QStringLiteral("题库管理"), 1},
        {QStringLiteral("发布考试"), 2},
        {QStringLiteral("批改试卷"), 3},
        {QStringLiteral("成绩分析"), 4},
        {QStringLiteral("个人中心"), 5}
    };
    for (const auto &page : pages) {
        auto *button = navButton(page.first, page.second, 4, topNav);
        navRow->addWidget(button);
        connect(button, &QPushButton::clicked, this, [this, page]() {
            if (page.second != 4) {
                emit pageRequested(page.second);
            }
        });
    }

    auto *printButton = new QPushButton(QStringLiteral("报表打印"), this);
    printButton->setObjectName(QStringLiteral("ScorePrimaryButton"));
    printButton->setCursor(Qt::PointingHandCursor);
    auto *minButton = windowButton(QStringLiteral("-"), this);
    auto *maxButton = windowButton(QStringLiteral("□"), this);
    auto *closeButton = windowButton(QStringLiteral("X"), this);
    closeButton->setProperty("danger", true);

    toolbar->addLayout(brandBox);
    toolbar->addSpacing(10);
    toolbar->addLayout(navRow);
    toolbar->addStretch();
    toolbar->addWidget(printButton);
    toolbar->addWidget(minButton);
    toolbar->addWidget(maxButton);
    toolbar->addWidget(closeButton);
    root->addWidget(topNav);

    scrollArea = new QScrollArea(this);
    scrollArea->setObjectName(QStringLiteral("ScoreScrollArea"));
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    contentWidget = new QWidget(scrollArea);
    contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(0, 0, 12, 10);
    contentLayout->setSpacing(26);

    filterWidget = new ScoreFilterWidget(contentWidget);
    addShadow(filterWidget);
    contentLayout->addWidget(filterWidget);

    auto *statHost = new QWidget(contentWidget);
    statGrid = new QGridLayout(statHost);
    statGrid->setContentsMargins(0, 0, 0, 0);
    statGrid->setHorizontalSpacing(18);
    statGrid->setVerticalSpacing(18);
    averageCard = new StatisticCardWidget(QStringLiteral("平均分"), QStringLiteral("#2563eb"), statHost);
    highestCard = new StatisticCardWidget(QStringLiteral("最高分"), QStringLiteral("#16a34a"), statHost);
    lowestCard = new StatisticCardWidget(QStringLiteral("最低分"), QStringLiteral("#f59e0b"), statHost);
    excellentCard = new StatisticCardWidget(QStringLiteral("优秀率"), QStringLiteral("#8b5cf6"), statHost);
    averageCard->setMinimumHeight(206);
    highestCard->setMinimumHeight(206);
    lowestCard->setMinimumHeight(206);
    excellentCard->setMinimumHeight(206);
    addShadow(averageCard);
    addShadow(highestCard);
    addShadow(lowestCard);
    addShadow(excellentCard);
    contentLayout->addWidget(statHost);

    auto *chartHost = new QWidget(contentWidget);
    chartGrid = new QGridLayout(chartHost);
    chartGrid->setContentsMargins(0, 0, 0, 0);
    chartGrid->setHorizontalSpacing(18);
    chartGrid->setVerticalSpacing(18);
    trendChart = new TrendChartWidget(chartHost);
    distributionChart = new DistributionChartWidget(chartHost);
    levelPieChart = new LevelPieChartWidget(chartHost);
    rankWidget = new StudentRankWidget(chartHost);
    questionWidget = new QuestionAnalysisWidget(chartHost);
    trendChart->setMinimumHeight(520);
    distributionChart->setMinimumHeight(460);
    levelPieChart->setMinimumHeight(460);
    rankWidget->setMinimumHeight(500);
    questionWidget->setMinimumHeight(500);
    addShadow(trendChart);
    addShadow(distributionChart);
    addShadow(levelPieChart);
    addShadow(rankWidget);
    addShadow(questionWidget);
    contentLayout->addWidget(chartHost);
    contentLayout->addStretch();

    scrollArea->setWidget(contentWidget);
    root->addWidget(scrollArea, 1);

    relayoutResponsiveSections();

    connect(printButton, &QPushButton::clicked, this, &TeacherScoreAnalysisWindow::printReportRequested);
    connect(minButton, &QPushButton::clicked, this, &TeacherScoreAnalysisWindow::minimizeRequested);
    connect(maxButton, &QPushButton::clicked, this, &TeacherScoreAnalysisWindow::maximizeRequested);
    connect(closeButton, &QPushButton::clicked, this, &TeacherScoreAnalysisWindow::closeRequested);
    connect(filterWidget, &ScoreFilterWidget::queryRequested, this, &TeacherScoreAnalysisWindow::applyFilter);
}

void TeacherScoreAnalysisWindow::applyStyle()
{
    setStyleSheet(QStringLiteral(R"(
        #TeacherScoreAnalysisWindow {
            background: #eef3fb;
            color: #111827;
            font-family: "Microsoft YaHei", "Segoe UI";
        }
        #ScoreTopNav {
            background: #f8fafd;
            border: 1px solid #dbeafe;
            border-radius: 24px;
        }
        #ScoreBrandTitle {
            color: #111827;
            font-size: 34px;
            font-weight: 800;
        }
        #ScoreBrandSubtitle {
            color: #64748b;
            font-size: 17px;
            font-weight: 700;
        }
        #ScoreNavButton {
            min-height: 48px;
            padding: 0 18px;
            color: #334155;
            background: #ffffff;
            border: 1px solid #dbe7f6;
            border-radius: 18px;
            font-size: 18px;
            font-weight: 800;
        }
        #ScoreNavButton:hover {
            color: #2563eb;
            background: #eff6ff;
            border-color: #bfdbfe;
        }
        #ScoreNavButton[active="true"] {
            color: #ffffff;
            background: #2563eb;
            border-color: #2563eb;
        }
        #ScoreFilterCard, #ScoreStatisticCard, #ScoreAnalysisCard {
            background: #ffffff;
            border: 1px solid #e5edf6;
            border-radius: 24px;
        }
        #ScorePanelTitle {
            color: #111827;
            font-size: 28px;
            font-weight: 800;
        }
        #ScoreFilterLabel, #ScoreStatTitle {
            color: #64748b;
            font-size: 18px;
            font-weight: 700;
        }
        #ScoreStatValue {
            font-size: 52px;
            font-weight: 900;
        }
        #ScoreStatCaption {
            color: #94a3b8;
            font-size: 18px;
            font-weight: 700;
        }
        #ScoreFilterCombo {
            background: #f8fbff;
            border: 1px solid #dbe7f6;
            border-radius: 14px;
            padding: 0 14px;
            color: #111827;
            font-size: 19px;
            font-weight: 700;
        }
        #ScoreFilterCombo::drop-down {
            border: none;
            width: 34px;
        }
        #ScorePrimaryButton, #ScoreGhostButton {
            min-height: 48px;
            border-radius: 14px;
            font-size: 18px;
            font-weight: 800;
            padding: 0 22px;
        }
        #ScorePrimaryButton {
            color: #ffffff;
            background: #2563eb;
            border: 1px solid #2563eb;
        }
        #ScorePrimaryButton:hover {
            background: #1d4ed8;
        }
        #ScoreGhostButton {
            color: #2563eb;
            background: #eff6ff;
            border: 1px solid #bfdbfe;
        }
        #ScoreGhostButton:hover {
            background: #dbeafe;
        }
        #ScoreWindowButton {
            color: #334155;
            background: #ffffff;
            border: 1px solid #dbe7f6;
            border-radius: 12px;
            font-size: 17px;
            font-weight: 800;
        }
        #ScoreWindowButton:hover {
            background: #eff6ff;
        }
        #ScoreWindowButton[danger="true"]:hover {
            color: #ffffff;
            background: #ef4444;
            border-color: #ef4444;
        }
        #ScoreTable {
            background: transparent;
            border: none;
            color: #111827;
            font-size: 18px;
            gridline-color: transparent;
            selection-background-color: #eff6ff;
            selection-color: #111827;
        }
        #ScoreTable::item {
            min-height: 52px;
            border-bottom: 1px solid #eef2f7;
        }
        QHeaderView::section {
            min-height: 54px;
            color: #64748b;
            background: #f8fbff;
            border: none;
            border-bottom: 1px solid #e5edf6;
            font-size: 18px;
            font-weight: 800;
        }
        #ScoreRateBar {
            min-height: 18px;
            text-align: center;
            color: #111827;
            background: #edf2f8;
            border: none;
            border-radius: 9px;
            font-size: 16px;
            font-weight: 800;
        }
        #ScoreRateBar::chunk {
            background: #2563eb;
            border-radius: 9px;
        }
        QScrollBar:vertical {
            width: 12px;
            background: transparent;
            margin: 2px;
        }
        QScrollBar::handle:vertical {
            background: #bfd0e5;
            border-radius: 6px;
            min-height: 48px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0;
        }
    )"));
}

void TeacherScoreAnalysisWindow::applyFilter(const QString &className, const QString &examName, const QString &timeRange)
{
    const QVariantList scores = loadClassScore(className, examName, timeRange);
    const QVariantMap stats = loadExamStatistics(scores);
    refreshStatisticCards(stats);

    rankWidget->setRankData(scores);
    trendChart->setTrendData(loadScoreTrend(className, timeRange));
    distributionChart->setDistributionData(buildDistribution(scores));
    levelPieChart->setLevelData(buildLevelData(scores));
    questionWidget->setQuestionData(loadQuestionAnalysis(className, examName));

    trendChart->playChartAnimation();
    distributionChart->playChartAnimation();
    levelPieChart->playChartAnimation();
}

void TeacherScoreAnalysisWindow::refreshStatisticCards(const QVariantMap &stats)
{
    averageCard->setStatistic(QStringLiteral("平均分"),
                              QString::number(stats.value(QStringLiteral("average")).toDouble(), 'f', 1),
                              QStringLiteral("班级整体水平"),
                              QStringLiteral("#2563eb"));
    highestCard->setStatistic(QStringLiteral("最高分"),
                              QString::number(stats.value(QStringLiteral("highest")).toDouble(), 'f', 1),
                              QStringLiteral("本次考试最高成绩"),
                              QStringLiteral("#16a34a"));
    lowestCard->setStatistic(QStringLiteral("最低分"),
                             QString::number(stats.value(QStringLiteral("lowest")).toDouble(), 'f', 1),
                             QStringLiteral("需要重点关注"),
                             QStringLiteral("#f59e0b"));
    excellentCard->setStatistic(QStringLiteral("优秀率"),
                                QString::number(stats.value(QStringLiteral("excellentRate")).toDouble(), 'f', 1) + QStringLiteral("%"),
                                QStringLiteral("90分及以上占比"),
                                QStringLiteral("#8b5cf6"));
}

QVariantList TeacherScoreAnalysisWindow::buildDistribution(const QVariantList &scores) const
{
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    for (const QVariant &value : scores) {
        const double score = value.toMap().value(QStringLiteral("score")).toDouble();
        if (score < 60) {
            ++a;
        } else if (score < 70) {
            ++b;
        } else if (score < 80) {
            ++c;
        } else if (score < 90) {
            ++d;
        } else {
            ++e;
        }
    }
    return {
        QVariantMap{{QStringLiteral("label"), QStringLiteral("0-60")}, {QStringLiteral("value"), a}},
        QVariantMap{{QStringLiteral("label"), QStringLiteral("60-70")}, {QStringLiteral("value"), b}},
        QVariantMap{{QStringLiteral("label"), QStringLiteral("70-80")}, {QStringLiteral("value"), c}},
        QVariantMap{{QStringLiteral("label"), QStringLiteral("80-90")}, {QStringLiteral("value"), d}},
        QVariantMap{{QStringLiteral("label"), QStringLiteral("90-100")}, {QStringLiteral("value"), e}}
    };
}

QVariantList TeacherScoreAnalysisWindow::buildLevelData(const QVariantList &scores) const
{
    int excellent = 0;
    int good = 0;
    int medium = 0;
    int pass = 0;
    int fail = 0;
    for (const QVariant &value : scores) {
        const double score = value.toMap().value(QStringLiteral("score")).toDouble();
        if (score >= 90) {
            ++excellent;
        } else if (score >= 80) {
            ++good;
        } else if (score >= 70) {
            ++medium;
        } else if (score >= 60) {
            ++pass;
        } else {
            ++fail;
        }
    }
    return {
        QVariantMap{{QStringLiteral("label"), QStringLiteral("优秀")}, {QStringLiteral("value"), excellent}, {QStringLiteral("color"), QStringLiteral("#2563eb")}},
        QVariantMap{{QStringLiteral("label"), QStringLiteral("良好")}, {QStringLiteral("value"), good}, {QStringLiteral("color"), QStringLiteral("#16a34a")}},
        QVariantMap{{QStringLiteral("label"), QStringLiteral("中等")}, {QStringLiteral("value"), medium}, {QStringLiteral("color"), QStringLiteral("#f59e0b")}},
        QVariantMap{{QStringLiteral("label"), QStringLiteral("及格")}, {QStringLiteral("value"), pass}, {QStringLiteral("color"), QStringLiteral("#8b5cf6")}},
        QVariantMap{{QStringLiteral("label"), QStringLiteral("不及格")}, {QStringLiteral("value"), fail}, {QStringLiteral("color"), QStringLiteral("#ef4444")}}
    };
}

void TeacherScoreAnalysisWindow::relayoutResponsiveSections()
{
    const bool useCompact = width() < 1080;
    compactLayout = useCompact;

    const QList<QWidget *> statCards{averageCard, highestCard, lowestCard, excellentCard};
    for (QWidget *card : statCards) {
        statGrid->removeWidget(card);
    }
    const int statColumns = width() < 760 ? 1 : (width() < 1180 ? 2 : 4);
    for (int i = 0; i < statCards.size(); ++i) {
        statGrid->addWidget(statCards.at(i), i / statColumns, i % statColumns);
    }

    const QList<QWidget *> charts{trendChart, distributionChart, levelPieChart, rankWidget, questionWidget};
    for (QWidget *chart : charts) {
        chartGrid->removeWidget(chart);
    }
    if (useCompact) {
        chartGrid->addWidget(trendChart, 0, 0);
        chartGrid->addWidget(distributionChart, 1, 0);
        chartGrid->addWidget(levelPieChart, 2, 0);
        chartGrid->addWidget(rankWidget, 3, 0);
        chartGrid->addWidget(questionWidget, 4, 0);
    } else {
        chartGrid->addWidget(trendChart, 0, 0, 1, 2);
        chartGrid->addWidget(distributionChart, 1, 0);
        chartGrid->addWidget(levelPieChart, 1, 1);
        chartGrid->addWidget(rankWidget, 2, 0);
        chartGrid->addWidget(questionWidget, 2, 1);
    }
}

QStringList TeacherScoreAnalysisWindow::repositoryClassNames() const
{
    QStringList names;
    if (repository == nullptr) {
        return names;
    }
    const QVariantList rows = repository->getTeacherClasses();
    for (const QVariant &value : rows) {
        const QString name = value.toMap().value(QStringLiteral("name")).toString().trimmed();
        if (!name.isEmpty() && !names.contains(name)) {
            names.append(name);
        }
    }
    return names;
}

QStringList TeacherScoreAnalysisWindow::repositoryExamNames() const
{
    QStringList names;
    if (repository == nullptr) {
        return names;
    }
    const QVariantList rows = repository->getExamList();
    for (const QVariant &value : rows) {
        const QVariantMap row = value.toMap();
        const QString name = row.value(QStringLiteral("name"), row.value(QStringLiteral("title"))).toString().trimmed();
        if (!name.isEmpty() && !names.contains(name)) {
            names.append(name);
        }
    }
    return names;
}
