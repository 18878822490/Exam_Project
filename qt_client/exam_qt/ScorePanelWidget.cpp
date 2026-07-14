#include "ScorePanelWidget.h"

#include <QDoubleValidator>
#include <QGraphicsOpacityEffect>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QStyle>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>

ScorePanelWidget::ScorePanelWidget(QWidget *parent)
    : QWidget(parent)
    , questionLabel(new QLabel(QStringLiteral("当前题目：第5题"), this))
    , maxScoreLabel(new QLabel(QStringLiteral("满分：10"), this))
    , stateLabel(new QLabel(QStringLiteral("等待教师评分"), this))
    , successLabel(new QLabel(QStringLiteral("✓ 保存成功"), this))
    , scoreSuffixLabel(new QLabel(QStringLiteral("/10"), this))
    , scoreEdit(new QLineEdit(this))
    , commentEdit(new QTextEdit(this))
    , saveButton(new QPushButton(QStringLiteral("保存评分"), this))
    , submitButton(new QPushButton(QStringLiteral("提交本题"), this))
    , previousButton(new QPushButton(QStringLiteral("上一题"), this))
    , nextButton(new QPushButton(QStringLiteral("下一题"), this))
    , scoreValidator(new QDoubleValidator(0, 100, 1, this))
{
    setObjectName(QStringLiteral("MarkPanel"));
    setMinimumWidth(420);
    setMaximumWidth(560);

    auto *title = new QLabel(QStringLiteral("评分区域"), this);
    title->setObjectName(QStringLiteral("MarkPanelTitle"));
    questionLabel->setObjectName(QStringLiteral("MarkScoreQuestion"));
    maxScoreLabel->setObjectName(QStringLiteral("MarkMetaText"));
    stateLabel->setObjectName(QStringLiteral("MarkManualTag"));
    successLabel->setObjectName(QStringLiteral("MarkSuccessText"));
    successLabel->setVisible(false);

    scoreEdit->setObjectName(QStringLiteral("MarkScoreEdit"));
    scoreEdit->setPlaceholderText(QStringLiteral("输入得分"));
    scoreEdit->setValidator(scoreValidator);

    commentEdit->setObjectName(QStringLiteral("MarkCommentEdit"));
    commentEdit->setPlaceholderText(QStringLiteral("计算过程正确，\n最后一步存在错误。"));
    commentEdit->setMinimumHeight(210);

    saveButton->setObjectName(QStringLiteral("MarkPrimaryButton"));
    submitButton->setObjectName(QStringLiteral("MarkGhostButton"));
    previousButton->setObjectName(QStringLiteral("MarkGhostButton"));
    nextButton->setObjectName(QStringLiteral("MarkPrimaryButton"));
    saveButton->setCursor(Qt::PointingHandCursor);
    submitButton->setCursor(Qt::PointingHandCursor);
    previousButton->setCursor(Qt::PointingHandCursor);
    nextButton->setCursor(Qt::PointingHandCursor);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(20);
    layout->addWidget(title);

    auto *infoCard = new QFrame(this);
    infoCard->setObjectName(QStringLiteral("MarkInnerCard"));
    auto *infoLayout = new QVBoxLayout(infoCard);
    infoLayout->setContentsMargins(20, 18, 20, 18);
    infoLayout->setSpacing(10);
    infoLayout->addWidget(questionLabel);
    infoLayout->addWidget(maxScoreLabel);
    infoLayout->addWidget(stateLabel, 0, Qt::AlignLeft);
    layout->addWidget(infoCard);

    auto *scoreRow = new QHBoxLayout;
    auto *scoreTitle = new QLabel(QStringLiteral("教师评分："), this);
    scoreTitle->setObjectName(QStringLiteral("MarkSmallTitle"));
    scoreSuffixLabel->setObjectName(QStringLiteral("MarkMetaText"));
    scoreRow->addWidget(scoreTitle);
    scoreRow->addWidget(scoreEdit, 1);
    scoreRow->addWidget(scoreSuffixLabel);
    layout->addLayout(scoreRow);

    auto *quickGrid = new QGridLayout;
    quickGrid->setHorizontalSpacing(10);
    quickGrid->setVerticalSpacing(10);
    quickGrid->addWidget(quickButton(QStringLiteral("满分"), 1.0), 0, 0);
    quickGrid->addWidget(quickButton(QStringLiteral("优秀"), 0.8), 0, 1);
    quickGrid->addWidget(quickButton(QStringLiteral("一般"), 0.5), 1, 0);
    quickGrid->addWidget(quickButton(QStringLiteral("错误"), 0.0), 1, 1);
    layout->addLayout(quickGrid);

    auto *commentTitle = new QLabel(QStringLiteral("批语："), this);
    commentTitle->setObjectName(QStringLiteral("MarkSmallTitle"));
    layout->addWidget(commentTitle);
    layout->addWidget(commentEdit);
    layout->addWidget(successLabel);
    layout->addStretch();
    layout->addWidget(saveButton);
    layout->addWidget(submitButton);

    auto *navRow = new QHBoxLayout;
    navRow->setSpacing(10);
    navRow->addWidget(previousButton);
    navRow->addWidget(nextButton);
    layout->addLayout(navRow);

    connect(saveButton, &QPushButton::clicked, this, [this]() {
        emit saveScoreRequested(scoreEdit->text().toDouble(), commentEdit->toPlainText());
    });
    connect(submitButton, &QPushButton::clicked, this, [this]() {
        emit submitQuestionRequested(scoreEdit->text().toDouble(), commentEdit->toPlainText());
    });
    connect(previousButton, &QPushButton::clicked, this, &ScorePanelWidget::previousQuestionRequested);
    connect(nextButton, &QPushButton::clicked, this, &ScorePanelWidget::nextQuestionRequested);
}

void ScorePanelWidget::setQuestion(const QVariantMap &question)
{
    currentQuestion = question;
    if (question.isEmpty()) {
        questionLabel->setText(QStringLiteral("当前题目：暂无待评分题"));
        maxScoreLabel->setText(QStringLiteral("请选择有待评分题目的学生"));
        scoreSuffixLabel->setText(QStringLiteral("/0"));
        scoreEdit->clear();
        commentEdit->clear();
        stateLabel->setText(QStringLiteral("无待评分题"));
        stateLabel->setObjectName(QStringLiteral("MarkManualTag"));
        stateLabel->style()->unpolish(stateLabel);
        stateLabel->style()->polish(stateLabel);
        scoreValidator->setTop(0);
        setEditorEnabled(false);
        previousButton->setEnabled(false);
        nextButton->setEnabled(false);
        for (QPushButton *button : quickButtons) {
            button->setText(button->property("label").toString());
        }
        return;
    }

    const int number = question.value(QStringLiteral("number"), 1).toInt();
    const double maxScore = question.value(QStringLiteral("maxScore"), 10).toDouble();
    const bool autoScored = question.value(QStringLiteral("autoScored")).toBool();

    questionLabel->setText(QStringLiteral("当前题目：第%1题").arg(number));
    maxScoreLabel->setText(QStringLiteral("满分：%1").arg(maxScore, 0, 'f', maxScore == int(maxScore) ? 0 : 1));
    scoreSuffixLabel->setText(QStringLiteral("/%1").arg(maxScore, 0, 'f', maxScore == int(maxScore) ? 0 : 1));
    scoreEdit->setText(QString::number(question.value(QStringLiteral("score"), 0).toDouble(), 'f', 1).replace(QStringLiteral(".0"), QString()));
    scoreEdit->setPlaceholderText(QStringLiteral("输入得分"));
    commentEdit->setPlainText(question.value(QStringLiteral("comment")).toString());

    scoreValidator->setTop(maxScore);

    setEditorEnabled(!autoScored);
    previousButton->setEnabled(true);
    nextButton->setEnabled(true);
    stateLabel->setText(autoScored ? QStringLiteral("✓ 系统已评分") : QStringLiteral("等待教师评分"));
    stateLabel->setObjectName(autoScored ? QStringLiteral("MarkAutoTag") : QStringLiteral("MarkManualTag"));
    stateLabel->style()->unpolish(stateLabel);
    stateLabel->style()->polish(stateLabel);

    for (QPushButton *button : quickButtons) {
        const double ratio = button->property("ratio").toDouble();
        const double quickScore = maxScore * ratio;
        button->setProperty("score", quickScore);
        button->setText(QStringLiteral("%1%2")
                                .arg(button->property("label").toString(),
                                     QString::number(quickScore, 'f', quickScore == int(quickScore) ? 0 : 1)));
    }
}

void ScorePanelWidget::showSaveSuccess()
{
    successLabel->setVisible(true);
    auto *effect = new QGraphicsOpacityEffect(successLabel);
    successLabel->setGraphicsEffect(effect);

    auto *animation = new QPropertyAnimation(effect, "opacity", successLabel);
    animation->setDuration(360);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    QTimer::singleShot(1400, successLabel, [this, effect]() {
        auto *fade = new QPropertyAnimation(effect, "opacity", successLabel);
        fade->setDuration(260);
        fade->setStartValue(1.0);
        fade->setEndValue(0.0);
        connect(fade, &QPropertyAnimation::finished, successLabel, [this]() {
            successLabel->setVisible(false);
            successLabel->setGraphicsEffect(nullptr);
        });
        fade->start(QAbstractAnimation::DeleteWhenStopped);
    });
}

void ScorePanelWidget::setEditorEnabled(bool enabled)
{
    scoreEdit->setEnabled(enabled);
    commentEdit->setEnabled(enabled);
    saveButton->setEnabled(enabled);
    submitButton->setEnabled(enabled);
    for (QPushButton *button : quickButtons) {
        button->setEnabled(enabled);
    }
}

QPushButton *ScorePanelWidget::quickButton(const QString &label, double ratio)
{
    auto *button = new QPushButton(label, this);
    button->setObjectName(QStringLiteral("MarkQuickButton"));
    button->setCursor(Qt::PointingHandCursor);
    button->setProperty("score", 10 * ratio);
    button->setProperty("ratio", ratio);
    button->setProperty("label", label);
    quickButtons.append(button);
    connect(button, &QPushButton::clicked, this, [this, button]() {
        const double value = button->property("score").toDouble();
        scoreEdit->setText(QString::number(value, 'f', value == int(value) ? 0 : 1));
    });
    return button;
}
