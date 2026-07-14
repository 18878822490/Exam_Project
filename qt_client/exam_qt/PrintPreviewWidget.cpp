#include "PrintPreviewWidget.h"

#include <QPainter>
#include <QPaintEvent>

PrintPreviewWidget::PrintPreviewWidget(QWidget *parent)
    : QWidget(parent)
{
    setObjectName(QStringLiteral("PrintPreviewWidget"));
    setMinimumSize(620, 860);
}

void PrintPreviewWidget::setReportData(const QVariantMap &report)
{
    currentReport = report;
    update();
}

QVariantMap PrintPreviewWidget::reportData() const
{
    return currentReport;
}

void PrintPreviewWidget::renderReport(QPainter *painter, const QRectF &targetRect) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    QRectF page = targetRect;
    painter->fillRect(page, QColor(QStringLiteral("#ffffff")));
    painter->setPen(QPen(QColor(QStringLiteral("#e5edf6")), 1));
    painter->drawRect(page.adjusted(0.5, 0.5, -0.5, -0.5));

    page = page.adjusted(42, 38, -42, -38);
    QRectF cursor = drawHeader(painter, page);
    cursor = drawSummary(painter, cursor);
    drawScoreTable(painter, cursor);

    QFont footerFont = painter->font();
    footerFont.setPixelSize(10);
    painter->setFont(footerFont);
    painter->setPen(QColor(QStringLiteral("#94a3b8")));
    painter->drawText(QRectF(page.left(), targetRect.bottom() - 34, page.width(), 18),
                      Qt::AlignCenter,
                      QStringLiteral("由智考星智能考试系统生成"));

    painter->restore();
}

void PrintPreviewWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(rect(), QColor(QStringLiteral("#e8eef7")));

    const double ratio = 210.0 / 297.0;
    const int pageHeight = qMin(height() - 40, int((width() - 64) / ratio));
    const int pageWidth = int(pageHeight * ratio);
    QRectF page((width() - pageWidth) / 2.0, 20, pageWidth, pageHeight);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(15, 23, 42, 28));
    painter.drawRoundedRect(page.translated(0, 10), 8, 8);
    renderReport(&painter, page);
}

QSize PrintPreviewWidget::sizeHint() const
{
    return QSize(720, 980);
}

QRectF PrintPreviewWidget::drawHeader(QPainter *painter, const QRectF &page) const
{
    QFont titleFont = painter->font();
    titleFont.setPixelSize(24);
    titleFont.setBold(true);
    painter->setFont(titleFont);
    painter->setPen(QColor(QStringLiteral("#111827")));
    painter->drawText(QRectF(page.left(), page.top(), page.width(), 34), Qt::AlignCenter, QStringLiteral("智考星成绩报告"));

    QFont metaFont = painter->font();
    metaFont.setPixelSize(11);
    metaFont.setBold(false);
    painter->setFont(metaFont);
    painter->setPen(QColor(QStringLiteral("#475569")));

    const QString examName = currentReport.value(QStringLiteral("examName"), QStringLiteral("Java期末考试")).toString();
    const QString className = currentReport.value(QStringLiteral("className"), QStringLiteral("软件工程2501班")).toString();
    const QString reportType = currentReport.value(QStringLiteral("reportType"), QStringLiteral("班级成绩总表")).toString();
    const QString date = currentReport.value(QStringLiteral("date"), QStringLiteral("2026-07-14")).toString();
    const QString line = QStringLiteral("考试名称：%1    班级：%2    报表类型：%3    日期：%4")
            .arg(examName, className, reportType, date);
    painter->drawText(QRectF(page.left(), page.top() + 42, page.width(), 24), Qt::AlignCenter, line);

    painter->setPen(QPen(QColor(QStringLiteral("#dbeafe")), 1.2));
    painter->drawLine(QPointF(page.left(), page.top() + 78), QPointF(page.right(), page.top() + 78));
    return QRectF(page.left(), page.top() + 94, page.width(), page.height() - 94);
}

QRectF PrintPreviewWidget::drawSummary(QPainter *painter, const QRectF &area) const
{
    const QVariantMap stats = currentReport.value(QStringLiteral("stats")).toMap();
    const QStringList labels = {
        QStringLiteral("平均分"),
        QStringLiteral("最高分"),
        QStringLiteral("最低分"),
        QStringLiteral("参考人数")
    };
    const QStringList values = {
        QString::number(stats.value(QStringLiteral("average")).toDouble(), 'f', 1),
        QString::number(stats.value(QStringLiteral("highest")).toDouble(), 'f', 1),
        QString::number(stats.value(QStringLiteral("lowest")).toDouble(), 'f', 1),
        QString::number(currentReport.value(QStringLiteral("scores")).toList().size())
    };

    const double gap = 10;
    const double itemWidth = (area.width() - gap * 3) / 4.0;
    QRectF row(area.left(), area.top(), area.width(), 60);
    for (int i = 0; i < labels.size(); ++i) {
        QRectF card(row.left() + i * (itemWidth + gap), row.top(), itemWidth, row.height());
        painter->setPen(QPen(QColor(QStringLiteral("#dbeafe")), 1));
        painter->setBrush(QColor(QStringLiteral("#f8fbff")));
        painter->drawRoundedRect(card, 8, 8);

        QFont labelFont = painter->font();
        labelFont.setPixelSize(9);
        labelFont.setBold(false);
        painter->setFont(labelFont);
        painter->setPen(QColor(QStringLiteral("#64748b")));
        painter->drawText(card.adjusted(8, 8, -8, -30), Qt::AlignLeft | Qt::AlignVCenter, labels.at(i));

        QFont valueFont = painter->font();
        valueFont.setPixelSize(16);
        valueFont.setBold(true);
        painter->setFont(valueFont);
        painter->setPen(QColor(QStringLiteral("#2563eb")));
        painter->drawText(card.adjusted(8, 26, -8, -8), Qt::AlignLeft | Qt::AlignVCenter, values.at(i));
    }
    return QRectF(area.left(), area.top() + 82, area.width(), area.height() - 82);
}

QRectF PrintPreviewWidget::drawScoreTable(QPainter *painter, const QRectF &area) const
{
    QVariantList scores = currentReport.value(QStringLiteral("scores")).toList();
    const QStringList headers = {
        QStringLiteral("排名"),
        QStringLiteral("学号"),
        QStringLiteral("姓名"),
        QStringLiteral("成绩"),
        QStringLiteral("等级")
    };
    const QList<double> widths = {0.12, 0.26, 0.22, 0.18, 0.22};
    const double rowHeight = 26;
    const double headerHeight = 30;
    QRectF table(area.left(), area.top(), area.width(), qMin(area.height(), headerHeight + rowHeight * qMin(24, scores.size())));

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(QStringLiteral("#eff6ff")));
    painter->drawRoundedRect(QRectF(table.left(), table.top(), table.width(), headerHeight), 8, 8);

    QFont headerFont = painter->font();
    headerFont.setPixelSize(10);
    headerFont.setBold(true);
    painter->setFont(headerFont);
    painter->setPen(QColor(QStringLiteral("#1e3a8a")));

    double x = table.left();
    for (int i = 0; i < headers.size(); ++i) {
        const double w = table.width() * widths.at(i);
        painter->drawText(QRectF(x + 6, table.top(), w - 12, headerHeight), Qt::AlignCenter, headers.at(i));
        x += w;
    }

    QFont bodyFont = painter->font();
    bodyFont.setPixelSize(10);
    bodyFont.setBold(false);
    painter->setFont(bodyFont);

    const int count = qMin(24, scores.size());
    for (int row = 0; row < count; ++row) {
        const QVariantMap scoreRow = scores.at(row).toMap();
        const double y = table.top() + headerHeight + row * rowHeight;
        painter->setPen(Qt::NoPen);
        painter->setBrush(row % 2 == 0 ? QColor(QStringLiteral("#ffffff")) : QColor(QStringLiteral("#f8fbff")));
        painter->drawRect(QRectF(table.left(), y, table.width(), rowHeight));

        const double score = scoreRow.value(QStringLiteral("score")).toDouble();
        const QStringList cells = {
            QString::number(row + 1),
            scoreRow.value(QStringLiteral("studentNo")).toString(),
            scoreRow.value(QStringLiteral("name")).toString(),
            QString::number(score, 'f', 1),
            gradeForScore(score)
        };
        painter->setPen(QColor(QStringLiteral("#334155")));
        x = table.left();
        for (int col = 0; col < cells.size(); ++col) {
            const double w = table.width() * widths.at(col);
            painter->drawText(QRectF(x + 6, y, w - 12, rowHeight), Qt::AlignCenter, cells.at(col));
            x += w;
        }
        painter->setPen(QPen(QColor(QStringLiteral("#e5edf6")), 1));
        painter->drawLine(QPointF(table.left(), y + rowHeight), QPointF(table.right(), y + rowHeight));
    }

    if (scores.size() > count) {
        painter->setPen(QColor(QStringLiteral("#94a3b8")));
        painter->drawText(QRectF(table.left(), table.bottom() + 8, table.width(), 18),
                          Qt::AlignCenter,
                          QStringLiteral("预览仅显示前%1名，导出Excel包含全部学生").arg(count));
    }
    return QRectF(area.left(), table.bottom() + 28, area.width(), area.height() - table.height() - 28);
}

QString PrintPreviewWidget::gradeForScore(double score) const
{
    if (score >= 90) {
        return QStringLiteral("优秀");
    }
    if (score >= 80) {
        return QStringLiteral("良好");
    }
    if (score >= 70) {
        return QStringLiteral("中等");
    }
    if (score >= 60) {
        return QStringLiteral("及格");
    }
    return QStringLiteral("不及格");
}
