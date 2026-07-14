#include "StudentRankWidget.h"

#include <QHeaderView>
#include <QLabel>
#include <QAbstractItemView>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QTableWidget>
#include <QVBoxLayout>

namespace {
QTableWidgetItem *tableItem(const QString &text, Qt::Alignment alignment = Qt::AlignCenter)
{
    auto *item = new QTableWidgetItem(text);
    item->setTextAlignment(alignment);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    return item;
}
}

StudentRankWidget::StudentRankWidget(QWidget *parent)
    : QFrame(parent)
    , table(new QTableWidget(this))
{
    setObjectName(QStringLiteral("ScoreAnalysisCard"));
    setMinimumHeight(360);

    auto *title = new QLabel(QStringLiteral("学生排名"), this);
    title->setObjectName(QStringLiteral("ScorePanelTitle"));

    table->setObjectName(QStringLiteral("ScoreTable"));
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({QStringLiteral("排名"), QStringLiteral("学号"), QStringLiteral("姓名"), QStringLiteral("成绩")});
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    table->setAlternatingRowColors(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSortingEnabled(true);
    table->setShowGrid(false);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(24, 20, 24, 24);
    layout->setSpacing(16);
    layout->addWidget(title);
    layout->addWidget(table, 1);
}

void StudentRankWidget::setRankData(const QVariantList &rows)
{
    table->setSortingEnabled(false);
    table->setRowCount(rows.size());
    for (int i = 0; i < rows.size(); ++i) {
        const QVariantMap row = rows.at(i).toMap();
        table->setItem(i, 0, tableItem(QString::number(i + 1)));
        table->setItem(i, 1, tableItem(row.value(QStringLiteral("studentNo")).toString()));
        table->setItem(i, 2, tableItem(row.value(QStringLiteral("name")).toString(), Qt::AlignCenter));
        table->setItem(i, 3, tableItem(QString::number(row.value(QStringLiteral("score")).toDouble(), 'f', 1)));
    }
    table->setSortingEnabled(true);

    auto *effect = new QGraphicsOpacityEffect(table);
    table->setGraphicsEffect(effect);
    auto *animation = new QPropertyAnimation(effect, "opacity", table);
    animation->setDuration(520);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    connect(animation, &QPropertyAnimation::finished, table, [this]() {
        table->setGraphicsEffect(nullptr);
    });
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
