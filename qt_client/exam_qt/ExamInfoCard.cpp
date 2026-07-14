#include "ExamInfoCard.h"

#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QVBoxLayout>

namespace {
void addSoftShadow(QWidget *widget, int blur = 30, int y = 10)
{
    auto *shadow = new QGraphicsDropShadowEffect(widget);
    shadow->setBlurRadius(blur);
    shadow->setOffset(0, y);
    shadow->setColor(QColor(29, 49, 86, 28));
    widget->setGraphicsEffect(shadow);
}

QLabel *makeLabel(const QString &text, const QString &objectName)
{
    auto *label = new QLabel(text);
    label->setObjectName(objectName);
    label->setTextInteractionFlags(Qt::NoTextInteraction);
    return label;
}
}

ExamInfoCard::ExamInfoCard(QWidget *parent)
    : QFrame(parent)
    , titleLabel(makeLabel(QStringLiteral("Java期末考试"), QStringLiteral("MarkExamTitle")))
    , courseLabel(makeLabel(QStringLiteral("课程：Java程序设计"), QStringLiteral("MarkMetaText")))
    , timeLabel(makeLabel(QStringLiteral("考试时间：2026-06-20"), QStringLiteral("MarkMetaText")))
    , scoreLabel(makeLabel(QStringLiteral("总分：100"), QStringLiteral("MarkMetaText")))
    , progressLabel(makeLabel(QStringLiteral("已完成 32 / 45"), QStringLiteral("MarkProgressText")))
    , pendingValueLabel(nullptr)
    , averageValueLabel(nullptr)
    , progressBar(new QProgressBar(this))
{
    setObjectName(QStringLiteral("MarkCard"));
    setFrameShape(QFrame::NoFrame);
    setMinimumHeight(214);
    addSoftShadow(this);

    progressBar->setObjectName(QStringLiteral("MarkProgressBar"));
    progressBar->setRange(0, 100);
    progressBar->setTextVisible(false);
    progressBar->setFixedHeight(10);

    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(32, 28, 32, 28);
    mainLayout->setSpacing(28);

    auto *leftLayout = new QVBoxLayout;
    leftLayout->setSpacing(15);
    leftLayout->addWidget(titleLabel);

    auto *metaLayout = new QHBoxLayout;
    metaLayout->setSpacing(18);
    metaLayout->addWidget(courseLabel);
    metaLayout->addWidget(timeLabel);
    metaLayout->addWidget(scoreLabel);
    metaLayout->addStretch();
    leftLayout->addLayout(metaLayout);

    auto *progressRow = new QHBoxLayout;
    progressRow->setSpacing(12);
    progressRow->addWidget(makeLabel(QStringLiteral("批改进度"), QStringLiteral("MarkSmallTitle")));
    progressRow->addWidget(progressLabel);
    progressRow->addStretch();
    leftLayout->addLayout(progressRow);
    leftLayout->addWidget(progressBar);
    leftLayout->addStretch();

    auto *statsLayout = new QHBoxLayout;
    statsLayout->setSpacing(16);
    statsLayout->addWidget(createStatCard(QStringLiteral("待批改"), &pendingValueLabel, QStringLiteral("#f59e0b")));
    statsLayout->addWidget(createStatCard(QStringLiteral("平均分"), &averageValueLabel, QStringLiteral("#2563eb")));

    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addLayout(statsLayout);
}

void ExamInfoCard::setExamInfo(const QVariantMap &exam, int completedCount, int totalCount, double averageScore)
{
    const int displayTotal = qMax(0, totalCount);
    const int progressTotal = qMax(1, totalCount);
    const int pending = qMax(0, totalCount - completedCount);
    const int progress = qBound(0, int((completedCount * 100.0) / progressTotal + 0.5), 100);

    titleLabel->setText(exam.value(QStringLiteral("title"), QStringLiteral("Java期末考试")).toString());
    courseLabel->setText(QStringLiteral("课程：%1").arg(exam.value(QStringLiteral("course"), QStringLiteral("Java程序设计")).toString()));
    timeLabel->setText(QStringLiteral("考试时间：%1").arg(exam.value(QStringLiteral("date"), QStringLiteral("2026-06-20")).toString()));
    scoreLabel->setText(QStringLiteral("总分：%1").arg(exam.value(QStringLiteral("totalScore"), 100).toString()));
    progressLabel->setText(QStringLiteral("已完成 %1 / %2").arg(completedCount).arg(displayTotal));
    progressBar->setValue(progress);
    pendingValueLabel->setText(QStringLiteral("%1人").arg(pending));
    averageValueLabel->setText(QString::number(averageScore, 'f', 1));
}

void ExamInfoCard::playEnterAnimation()
{
    auto *effect = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(effect);

    auto *animation = new QPropertyAnimation(effect, "opacity", this);
    animation->setDuration(500);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    connect(animation, &QPropertyAnimation::finished, this, [this]() {
        setGraphicsEffect(nullptr);
        addSoftShadow(this);
    });
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

QFrame *ExamInfoCard::createStatCard(const QString &title, QLabel **valueLabel, const QString &accent)
{
    auto *card = new QFrame(this);
    card->setObjectName(QStringLiteral("MarkMiniStatCard"));
    card->setMinimumSize(170, 116);
    card->setProperty("accent", accent);

    auto *layout = new QVBoxLayout(card);
    layout->setContentsMargins(20, 16, 20, 16);
    layout->setSpacing(8);

    auto *titleWidget = makeLabel(title, QStringLiteral("MarkStatTitle"));
    *valueLabel = makeLabel(QStringLiteral("--"), QStringLiteral("MarkStatValue"));
    (*valueLabel)->setStyleSheet(QStringLiteral("color: %1;").arg(accent));

    layout->addWidget(titleWidget);
    layout->addWidget(*valueLabel);
    layout->addStretch();
    return card;
}
