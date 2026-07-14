#include "ScoreFilterWidget.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace {
QWidget *filterBlock(const QString &labelText, QComboBox *combo)
{
    auto *box = new QWidget;
    auto *layout = new QVBoxLayout(box);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);

    auto *label = new QLabel(labelText, box);
    label->setObjectName(QStringLiteral("ScoreFilterLabel"));
    combo->setObjectName(QStringLiteral("ScoreFilterCombo"));
    combo->setMinimumHeight(54);

    layout->addWidget(label);
    layout->addWidget(combo);
    return box;
}
}

ScoreFilterWidget::ScoreFilterWidget(QWidget *parent)
    : QFrame(parent)
    , classCombo(new QComboBox(this))
    , examCombo(new QComboBox(this))
    , timeCombo(new QComboBox(this))
    , thirdFilterLabel(nullptr)
    , queryButton(new QPushButton(QStringLiteral("查询"), this))
{
    setObjectName(QStringLiteral("ScoreFilterCard"));
    setMinimumHeight(150);

    timeCombo->addItems({
        QStringLiteral("近3次考试"),
        QStringLiteral("近5次考试"),
        QStringLiteral("本学期"),
        QStringLiteral("全部时间")
    });

    queryButton->setObjectName(QStringLiteral("ScorePrimaryButton"));
    queryButton->setCursor(Qt::PointingHandCursor);
    queryButton->setMinimumSize(148, 54);

    auto *root = new QHBoxLayout(this);
    root->setContentsMargins(28, 24, 28, 24);
    root->setSpacing(22);
    root->addWidget(filterBlock(QStringLiteral("班级选择"), classCombo), 1);
    root->addWidget(filterBlock(QStringLiteral("考试选择"), examCombo), 1);

    auto *thirdBlock = new QWidget(this);
    auto *thirdLayout = new QVBoxLayout(thirdBlock);
    thirdLayout->setContentsMargins(0, 0, 0, 0);
    thirdLayout->setSpacing(10);
    thirdFilterLabel = new QLabel(QStringLiteral("时间选择"), thirdBlock);
    thirdFilterLabel->setObjectName(QStringLiteral("ScoreFilterLabel"));
    timeCombo->setObjectName(QStringLiteral("ScoreFilterCombo"));
    timeCombo->setMinimumHeight(54);
    thirdLayout->addWidget(thirdFilterLabel);
    thirdLayout->addWidget(timeCombo);
    root->addWidget(thirdBlock, 1);
    root->addWidget(queryButton, 0, Qt::AlignBottom);

    connect(queryButton, &QPushButton::clicked, this, [this]() {
        emit queryRequested(currentClass(), currentExam(), currentTimeRange());
    });
}

void ScoreFilterWidget::setClasses(const QStringList &classes)
{
    const QString current = classCombo->currentText();
    classCombo->clear();
    classCombo->addItems(classes);
    const int index = classCombo->findText(current);
    if (index >= 0) {
        classCombo->setCurrentIndex(index);
    }
}

void ScoreFilterWidget::setExams(const QStringList &exams)
{
    const QString current = examCombo->currentText();
    examCombo->clear();
    examCombo->addItems(exams);
    const int index = examCombo->findText(current);
    if (index >= 0) {
        examCombo->setCurrentIndex(index);
    }
}

void ScoreFilterWidget::setThirdFilter(const QString &label, const QStringList &items)
{
    thirdFilterLabel->setText(label);
    const QString current = timeCombo->currentText();
    timeCombo->clear();
    timeCombo->addItems(items);
    const int index = timeCombo->findText(current);
    if (index >= 0) {
        timeCombo->setCurrentIndex(index);
    }
}

void ScoreFilterWidget::setQueryButtonText(const QString &text)
{
    queryButton->setText(text);
}

QString ScoreFilterWidget::currentClass() const
{
    return classCombo->currentText();
}

QString ScoreFilterWidget::currentExam() const
{
    return examCombo->currentText();
}

QString ScoreFilterWidget::currentTimeRange() const
{
    return timeCombo->currentText();
}

QString ScoreFilterWidget::currentReportType() const
{
    return timeCombo->currentText();
}
