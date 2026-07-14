#include "TeacherUiUtils.h"

#include <QColor>
#include <QEvent>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QPropertyAnimation>

namespace TeacherUi {

QFrame *createCard(QWidget *parent)
{
    auto *card = new QFrame(parent);
    card->setObjectName(QStringLiteral("TeacherCard"));
    card->setFrameShape(QFrame::NoFrame);
    addShadow(card);
    return card;
}

void addShadow(QWidget *widget, int blur, int yOffset)
{
    auto *shadow = new QGraphicsDropShadowEffect(widget);
    shadow->setBlurRadius(blur);
    shadow->setOffset(0, yOffset);
    shadow->setColor(QColor(31, 49, 80, 28));
    widget->setGraphicsEffect(shadow);
}

QPushButton *primaryButton(const QString &text, QWidget *parent)
{
    auto *button = new QPushButton(text, parent);
    button->setObjectName(QStringLiteral("TeacherPrimaryButton"));
    button->setCursor(Qt::PointingHandCursor);
    button->setMinimumHeight(38);
    return button;
}

QPushButton *ghostButton(const QString &text, QWidget *parent)
{
    auto *button = new QPushButton(text, parent);
    button->setObjectName(QStringLiteral("TeacherGhostButton"));
    button->setCursor(Qt::PointingHandCursor);
    button->setMinimumHeight(36);
    return button;
}

QScrollArea *scrollArea(QWidget *content, QWidget *parent)
{
    auto *area = new QScrollArea(parent);
    area->setObjectName(QStringLiteral("TeacherScrollArea"));
    area->setWidgetResizable(true);
    area->setFrameShape(QFrame::NoFrame);
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    area->setWidget(content);
    return area;
}

QLabel *sectionTitle(const QString &text, QWidget *parent)
{
    auto *label = new QLabel(text, parent);
    label->setObjectName(QStringLiteral("TeacherSectionTitle"));
    return label;
}

QLabel *mutedLabel(const QString &text, QWidget *parent)
{
    auto *label = new QLabel(text, parent);
    label->setObjectName(QStringLiteral("TeacherMutedLabel"));
    return label;
}

}

HoverCard::HoverCard(QWidget *parent)
    : QFrame(parent)
    , lifted(false)
{
    setObjectName(QStringLiteral("TeacherCard"));
    setFrameShape(QFrame::NoFrame);
    TeacherUi::addShadow(this, 24, 8);
}

void HoverCard::enterEvent(QEnterEvent *event)
{
    QFrame::enterEvent(event);
    if (lifted) {
        return;
    }
    lifted = true;
    setProperty("hovered", true);
    style()->unpolish(this);
    style()->polish(this);

    if (auto *shadow = qobject_cast<QGraphicsDropShadowEffect *>(graphicsEffect())) {
        auto *blur = new QPropertyAnimation(shadow, "blurRadius", this);
        blur->setDuration(160);
        blur->setStartValue(shadow->blurRadius());
        blur->setEndValue(38);
        blur->setEasingCurve(QEasingCurve::OutCubic);
        blur->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void HoverCard::leaveEvent(QEvent *event)
{
    QFrame::leaveEvent(event);
    if (!lifted) {
        return;
    }
    lifted = false;
    setProperty("hovered", false);
    style()->unpolish(this);
    style()->polish(this);

    if (auto *shadow = qobject_cast<QGraphicsDropShadowEffect *>(graphicsEffect())) {
        auto *blur = new QPropertyAnimation(shadow, "blurRadius", this);
        blur->setDuration(160);
        blur->setStartValue(shadow->blurRadius());
        blur->setEndValue(24);
        blur->setEasingCurve(QEasingCurve::OutCubic);
        blur->start(QAbstractAnimation::DeleteWhenStopped);
    }
}
