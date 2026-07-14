#include "AnswerPreviewWidget.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QScrollArea>
#include <QTimer>
#include <QVBoxLayout>

namespace {
class AnswerQuestionCard : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)

public:
    AnswerQuestionCard(const QVariantMap &question, int index, bool selected, QWidget *parent = nullptr)
        : QFrame(parent)
        , rowIndex(index)
        , selectedState(selected)
        , currentBorder(selected ? QColor(QStringLiteral("#2563eb")) : QColor(QStringLiteral("#e5edf6")))
    {
        setObjectName(QStringLiteral("MarkAnswerCard"));
        setCursor(Qt::PointingHandCursor);
        setMinimumHeight(540);

        const bool autoScored = question.value(QStringLiteral("autoScored")).toBool();
        auto *layout = new QVBoxLayout(this);
        layout->setContentsMargins(24, 22, 24, 22);
        layout->setSpacing(16);

        auto *top = new QHBoxLayout;
        auto *number = new QLabel(QStringLiteral("第%1题：").arg(question.value(QStringLiteral("number"), index + 1).toInt()), this);
        number->setObjectName(QStringLiteral("MarkQuestionNumber"));
        auto *tag = new QLabel(autoScored ? QStringLiteral("系统题") : QStringLiteral("人工评分题"), this);
        tag->setObjectName(autoScored ? QStringLiteral("MarkAutoTag") : QStringLiteral("MarkManualTag"));
        top->addWidget(number);
        top->addStretch();
        top->addWidget(tag);
        layout->addLayout(top);

        auto *questionText = new QLabel(question.value(QStringLiteral("question")).toString(), this);
        questionText->setObjectName(QStringLiteral("MarkQuestionText"));
        questionText->setWordWrap(true);
        layout->addWidget(questionText);

        auto *answerBox = new QFrame(this);
        answerBox->setObjectName(QStringLiteral("MarkAnswerBox"));
        auto *answerLayout = new QVBoxLayout(answerBox);
        answerLayout->setContentsMargins(18, 16, 18, 16);
        answerLayout->setSpacing(12);
        answerLayout->addWidget(makeText(QStringLiteral("学生答案："), question.value(QStringLiteral("studentAnswer")).toString(), QStringLiteral("#2563eb"), answerBox));
        answerLayout->addWidget(makeText(QStringLiteral("标准答案："), question.value(QStringLiteral("standardAnswer")).toString(), QStringLiteral("#16a34a"), answerBox));
        const QString analysis = question.value(QStringLiteral("analysis")).toString();
        if (!analysis.trimmed().isEmpty()) {
            answerLayout->addWidget(makeText(QStringLiteral("解析："), analysis, QStringLiteral("#f59e0b"), answerBox));
        }
        layout->addWidget(answerBox);
        layout->addStretch();
    }

    QColor borderColor() const { return currentBorder; }

    void setBorderColor(const QColor &color)
    {
        currentBorder = color;
        update();
    }

    void setSelectedAnimated(bool value)
    {
        selectedState = value;
        auto *animation = new QPropertyAnimation(this, "borderColor", this);
        animation->setDuration(220);
        animation->setStartValue(currentBorder);
        animation->setEndValue(value ? QColor(QStringLiteral("#2563eb")) : QColor(QStringLiteral("#e5edf6")));
        animation->setEasingCurve(QEasingCurve::OutCubic);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }

signals:
    void clicked(int index);

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        QFrame::mousePressEvent(event);
        emit clicked(rowIndex);
    }

    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event)
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        QRectF rect = this->rect().adjusted(1, 1, -1, -1);
        painter.setBrush(QColor(QStringLiteral("#ffffff")));
        painter.setPen(QPen(currentBorder, selectedState ? 2.2 : 1.1));
        painter.drawRoundedRect(rect, 20, 20);
    }

private:
    static QLabel *makeText(const QString &prefix, const QString &value, const QString &color, QWidget *parent)
    {
        auto *label = new QLabel(parent);
        label->setObjectName(QStringLiteral("MarkAnswerText"));
        label->setTextFormat(Qt::RichText);
        label->setText(QStringLiteral("<b style='color:%1'>%2</b><span style='color:#334155'>%3</span>")
                               .arg(color, prefix, value.toHtmlEscaped().replace(QLatin1Char('\n'), QStringLiteral("<br>"))));
        label->setWordWrap(true);
        return label;
    }

    int rowIndex;
    bool selectedState;
    QColor currentBorder;
};
}

AnswerPreviewWidget::AnswerPreviewWidget(QWidget *parent)
    : QWidget(parent)
    , titleLabel(new QLabel(QStringLiteral("张三的答卷"), this))
    , autoScoreLabel(new QLabel(QStringLiteral("人工评分题 1 / 1"), this))
    , sectionLabel(new QLabel(QStringLiteral("第二部分 主观题"), this))
    , scrollArea(new QScrollArea(this))
    , contentWidget(new QWidget(this))
    , questionLayout(new QVBoxLayout(contentWidget))
    , currentIndex(0)
{
    setObjectName(QStringLiteral("MarkPanel"));
    titleLabel->setObjectName(QStringLiteral("MarkPanelTitle"));
    autoScoreLabel->setObjectName(QStringLiteral("MarkAutoScoreSummary"));
    sectionLabel->setObjectName(QStringLiteral("MarkSectionLabel"));

    questionLayout->setContentsMargins(0, 0, 0, 0);
    questionLayout->setSpacing(18);
    questionLayout->addStretch();

    scrollArea->setObjectName(QStringLiteral("MarkScrollArea"));
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidget(contentWidget);

    auto *header = new QHBoxLayout;
    auto *left = new QVBoxLayout;
    left->addWidget(titleLabel);
    left->addWidget(sectionLabel);
    header->addLayout(left, 1);
    header->addWidget(autoScoreLabel, 0, Qt::AlignBottom);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(18);
    layout->addLayout(header);
    layout->addWidget(scrollArea, 1);
}

void AnswerPreviewWidget::setPaperAnswer(const QVariantMap &student, const QVariantList &questions, int currentQuestionIndex)
{
    currentStudent = student;
    questionRows = questions;
    currentIndex = qBound(0, currentQuestionIndex, qMax(0, questionRows.size() - 1));

    titleLabel->setText(QStringLiteral("%1的答卷").arg(student.value(QStringLiteral("name"), QStringLiteral("张三")).toString()));

    int manualCount = 0;
    int manualPosition = 0;
    for (int i = 0; i < questionRows.size(); ++i) {
        const QVariantMap row = questionRows.at(i).toMap();
        if (!row.value(QStringLiteral("autoScored")).toBool()) {
            ++manualCount;
            if (i <= currentIndex) {
                manualPosition = manualCount;
            }
        }
    }
    if (manualCount <= 0) {
        autoScoreLabel->setText(QStringLiteral("暂无人工评分题"));
        sectionLabel->setText(QStringLiteral("系统评分题已自动处理"));
    } else {
        autoScoreLabel->setText(QStringLiteral("人工评分题 %1 / %2").arg(qMax(1, manualPosition)).arg(manualCount));
        sectionLabel->setText(currentVisibleQuestion().value(QStringLiteral("section"), QStringLiteral("第二部分 主观题")).toString());
    }
    rebuildQuestions();
}

void AnswerPreviewWidget::setCurrentQuestion(int index)
{
    currentIndex = qBound(0, index, qMax(0, questionRows.size() - 1));
    int manualCount = 0;
    int manualPosition = 0;
    for (int i = 0; i < questionRows.size(); ++i) {
        const QVariantMap row = questionRows.at(i).toMap();
        if (!row.value(QStringLiteral("autoScored")).toBool()) {
            ++manualCount;
            if (i <= currentIndex) {
                manualPosition = manualCount;
            }
        }
    }
    if (manualCount <= 0) {
        autoScoreLabel->setText(QStringLiteral("暂无人工评分题"));
        sectionLabel->setText(QStringLiteral("系统评分题已自动处理"));
    } else {
        autoScoreLabel->setText(QStringLiteral("人工评分题 %1 / %2").arg(qMax(1, manualPosition)).arg(manualCount));
        sectionLabel->setText(currentVisibleQuestion().value(QStringLiteral("section"), QStringLiteral("第二部分 主观题")).toString());
    }
    rebuildQuestions();
}

void AnswerPreviewWidget::rebuildQuestions()
{
    while (questionLayout->count() > 0) {
        QLayoutItem *item = questionLayout->takeAt(0);
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    const QVariantMap question = currentVisibleQuestion();
    if (question.isEmpty()) {
        auto *empty = new QLabel(QStringLiteral("当前学生暂无需要人工评分的题目"), contentWidget);
        empty->setObjectName(QStringLiteral("MarkQuestionText"));
        empty->setAlignment(Qt::AlignCenter);
        empty->setMinimumHeight(360);
        questionLayout->addWidget(empty);
        questionLayout->addStretch();
        return;
    }

    auto *card = new AnswerQuestionCard(question, currentIndex, true, contentWidget);
    questionLayout->addWidget(card);
    questionLayout->addStretch();

    const QPoint end = card->pos();
    card->move(end + QPoint(36, 0));
    auto *animation = new QPropertyAnimation(card, "pos", card);
    animation->setDuration(320);
    animation->setStartValue(card->pos());
    animation->setEndValue(end);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    QTimer::singleShot(0, card, [animation]() {
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    });
}

QVariantMap AnswerPreviewWidget::currentVisibleQuestion() const
{
    if (currentIndex >= 0 && currentIndex < questionRows.size()) {
        const QVariantMap row = questionRows.at(currentIndex).toMap();
        if (!row.value(QStringLiteral("autoScored")).toBool()) {
            return row;
        }
    }

    for (const QVariant &value : questionRows) {
        const QVariantMap row = value.toMap();
        if (!row.value(QStringLiteral("autoScored")).toBool()) {
            return row;
        }
    }
    return {};
}

#include "AnswerPreviewWidget.moc"
