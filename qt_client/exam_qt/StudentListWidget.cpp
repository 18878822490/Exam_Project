#include "StudentListWidget.h"

#include <QAbstractItemView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPainter>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QVBoxLayout>

namespace {
QColor statusColor(const QString &status)
{
    if (status == QStringLiteral("已批改")) {
        return QColor(QStringLiteral("#16a34a"));
    }
    if (status == QStringLiteral("批改中")) {
        return QColor(QStringLiteral("#2563eb"));
    }
    return QColor(QStringLiteral("#f59e0b"));
}

QString statusText(const QVariantMap &student)
{
    const QString raw = student.value(QStringLiteral("status"), QStringLiteral("待批改")).toString();
    return raw.isEmpty() ? QStringLiteral("待批改") : raw;
}

class StudentCardWidget : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)

public:
    explicit StudentCardWidget(const QVariantMap &student, int index, QWidget *parent = nullptr)
        : QFrame(parent)
        , rowIndex(index)
        , selected(false)
        , currentBorder(QColor(QStringLiteral("#e5edf6")))
    {
        setObjectName(QStringLiteral("MarkStudentCard"));
        setMinimumHeight(132);
        setCursor(Qt::PointingHandCursor);

        auto *layout = new QVBoxLayout(this);
        layout->setContentsMargins(18, 16, 18, 16);
        layout->setSpacing(10);

        auto *top = new QHBoxLayout;
        auto *name = new QLabel(student.value(QStringLiteral("name"), QStringLiteral("张三")).toString(), this);
        name->setObjectName(QStringLiteral("MarkStudentName"));
        auto *score = new QLabel(student.value(QStringLiteral("score"), QStringLiteral("--")).toString() + QStringLiteral("分"), this);
        score->setObjectName(QStringLiteral("MarkStudentScore"));
        top->addWidget(name, 1);
        top->addWidget(score);

        auto *number = new QLabel(QStringLiteral("学号：%1").arg(student.value(QStringLiteral("studentNo"), QStringLiteral("SE01001")).toString()), this);
        number->setObjectName(QStringLiteral("MarkStudentNo"));

        const QString status = statusText(student);
        auto *badge = new QLabel((status == QStringLiteral("已批改") ? QStringLiteral("✓ ") : QString()) + status, this);
        badge->setObjectName(QStringLiteral("MarkStatusBadge"));
        badge->setStyleSheet(QStringLiteral("color:%1; background:%2; border-radius:12px; padding:5px 10px;")
                                     .arg(statusColor(status).name(),
                                          QColor(statusColor(status).red(), statusColor(status).green(), statusColor(status).blue(), 28).name(QColor::HexArgb)));

        auto *bottom = new QHBoxLayout;
        bottom->addWidget(badge, 0, Qt::AlignLeft);
        bottom->addStretch();

        layout->addLayout(top);
        layout->addWidget(number);
        layout->addLayout(bottom);
    }

    QColor borderColor() const { return currentBorder; }

    void setBorderColor(const QColor &color)
    {
        currentBorder = color;
        update();
    }

    void setSelectedAnimated(bool value)
    {
        if (selected == value) {
            return;
        }
        selected = value;
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
        painter.setPen(QPen(currentBorder, selected ? 2.2 : 1.2));
        painter.drawRoundedRect(rect, 18, 18);
    }

private:
    int rowIndex;
    bool selected;
    QColor currentBorder;
};
}

StudentListWidget::StudentListWidget(QWidget *parent)
    : QWidget(parent)
    , searchEdit(new QLineEdit(this))
    , listWidget(new QListWidget(this))
    , previousButton(new QPushButton(QStringLiteral("上一位学生"), this))
    , nextButton(new QPushButton(QStringLiteral("下一位学生"), this))
    , currentIndex(0)
{
    setObjectName(QStringLiteral("MarkPanel"));
    setMinimumWidth(340);

    searchEdit->setObjectName(QStringLiteral("MarkSearchEdit"));
    searchEdit->setPlaceholderText(QStringLiteral("搜索学生..."));
    searchEdit->setClearButtonEnabled(true);

    listWidget->setObjectName(QStringLiteral("MarkStudentList"));
    listWidget->setFrameShape(QFrame::NoFrame);
    listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setSelectionMode(QAbstractItemView::NoSelection);
    listWidget->setSpacing(12);

    previousButton->setObjectName(QStringLiteral("MarkGhostButton"));
    nextButton->setObjectName(QStringLiteral("MarkPrimaryButton"));

    auto *title = new QLabel(QStringLiteral("学生列表"), this);
    title->setObjectName(QStringLiteral("MarkPanelTitle"));

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(16);
    layout->addWidget(title);
    layout->addWidget(searchEdit);
    layout->addWidget(listWidget, 1);

    auto *buttons = new QHBoxLayout;
    buttons->setSpacing(10);
    buttons->addWidget(previousButton);
    buttons->addWidget(nextButton);
    layout->addLayout(buttons);

    connect(searchEdit, &QLineEdit::textChanged, this, &StudentListWidget::applyFilter);
    connect(previousButton, &QPushButton::clicked, this, &StudentListWidget::previousStudentRequested);
    connect(nextButton, &QPushButton::clicked, this, &StudentListWidget::nextStudentRequested);
}

void StudentListWidget::setStudents(const QVariantList &students)
{
    studentRows = students;
    currentIndex = qBound(0, currentIndex, qMax(0, studentRows.size() - 1));
    rebuildList();
}

void StudentListWidget::setCurrentStudent(int index)
{
    currentIndex = qBound(0, index, qMax(0, studentRows.size() - 1));
    refreshSelection();
}

void StudentListWidget::updateStudent(int index, const QVariantMap &student)
{
    if (index < 0 || index >= studentRows.size()) {
        return;
    }
    studentRows[index] = student;
    rebuildList();
}

int StudentListWidget::currentStudent() const
{
    return currentIndex;
}

void StudentListWidget::applyFilter(const QString &keyword)
{
    const QString key = keyword.trimmed();
    for (int row = 0; row < listWidget->count(); ++row) {
        auto *item = listWidget->item(row);
        const QVariantMap student = item->data(Qt::UserRole).toMap();
        const bool visible = key.isEmpty()
                || student.value(QStringLiteral("name")).toString().contains(key, Qt::CaseInsensitive)
                || student.value(QStringLiteral("studentNo")).toString().contains(key, Qt::CaseInsensitive);
        item->setHidden(!visible);
    }
}

void StudentListWidget::rebuildList()
{
    listWidget->clear();
    for (int i = 0; i < studentRows.size(); ++i) {
        const QVariantMap student = studentRows.at(i).toMap();
        auto *item = new QListWidgetItem(listWidget);
        item->setSizeHint(QSize(300, 132));
        item->setData(Qt::UserRole, student);
        auto *card = new StudentCardWidget(student, i, listWidget);
        connect(card, &StudentCardWidget::clicked, this, [this](int index) {
            currentIndex = index;
            refreshSelection();
            emit studentSelected(index);
        });
        listWidget->setItemWidget(item, card);
    }
    applyFilter(searchEdit->text());
    refreshSelection();
}

void StudentListWidget::refreshSelection()
{
    for (int row = 0; row < listWidget->count(); ++row) {
        if (auto *card = qobject_cast<StudentCardWidget *>(listWidget->itemWidget(listWidget->item(row)))) {
            card->setSelectedAnimated(row == currentIndex);
        }
    }
    previousButton->setEnabled(currentIndex > 0);
    nextButton->setEnabled(currentIndex < studentRows.size() - 1);
}

#include "StudentListWidget.moc"
