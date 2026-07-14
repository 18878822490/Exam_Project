#include "QuestionAnalysisWidget.h"

#include <QAbstractItemView>
#include <QHeaderView>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QTableWidget>
#include <QVBoxLayout>

namespace {
QTableWidgetItem *plainItem(const QString &text, Qt::Alignment alignment = Qt::AlignCenter)
{
    auto *item = new QTableWidgetItem(text);
    item->setTextAlignment(alignment);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    return item;
}
}

QuestionAnalysisWidget::QuestionAnalysisWidget(QWidget *parent)
    : QFrame(parent)
    , table(new QTableWidget(this))
{
    setObjectName(QStringLiteral("ScoreAnalysisCard"));
    setMinimumHeight(360);

    auto *title = new QLabel(QStringLiteral("题目得分分析"), this);
    title->setObjectName(QStringLiteral("ScorePanelTitle"));

    table->setObjectName(QStringLiteral("ScoreTable"));
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({
        QStringLiteral("题号"),
        QStringLiteral("题型"),
        QStringLiteral("平均得分"),
        QStringLiteral("得分率"),
        QStringLiteral("薄弱程度")
    });
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
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

void QuestionAnalysisWidget::setQuestionData(const QVariantList &rows)
{
    table->setSortingEnabled(false);
    table->setRowCount(rows.size());
    for (int i = 0; i < rows.size(); ++i) {
        const QVariantMap row = rows.at(i).toMap();
        const double average = row.value(QStringLiteral("average")).toDouble();
        const double full = row.value(QStringLiteral("full")).toDouble();
        const int rate = full <= 0 ? 0 : qBound(0, int(average * 100.0 / full + 0.5), 100);

        table->setItem(i, 0, plainItem(QStringLiteral("第%1题").arg(row.value(QStringLiteral("number")).toInt())));
        table->setItem(i, 1, plainItem(row.value(QStringLiteral("type")).toString()));
        table->setItem(i, 2, plainItem(QStringLiteral("%1/%2").arg(QString::number(average, 'f', 1),
                                                                  QString::number(full, 'f', full == int(full) ? 0 : 1))));

        auto *bar = new QProgressBar(table);
        bar->setObjectName(QStringLiteral("ScoreRateBar"));
        bar->setRange(0, 100);
        bar->setValue(0);
        bar->setFormat(QStringLiteral("%1%").arg(rate));
        table->setCellWidget(i, 3, bar);
        auto *barAnimation = new QPropertyAnimation(bar, "value", bar);
        barAnimation->setDuration(620 + i * 35);
        barAnimation->setStartValue(0);
        barAnimation->setEndValue(rate);
        barAnimation->setEasingCurve(QEasingCurve::OutCubic);
        barAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        QString weakness = QStringLiteral("稳定");
        if (rate < 60) {
            weakness = QStringLiteral("重点薄弱");
        } else if (rate < 75) {
            weakness = QStringLiteral("需要巩固");
        } else if (rate < 88) {
            weakness = QStringLiteral("基本掌握");
        }
        table->setItem(i, 4, plainItem(weakness));
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
