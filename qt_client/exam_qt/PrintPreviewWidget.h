#ifndef PRINTPREVIEWWIDGET_H
#define PRINTPREVIEWWIDGET_H

#include <QVariantList>
#include <QVariantMap>
#include <QWidget>

class QPainter;

class PrintPreviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrintPreviewWidget(QWidget *parent = nullptr);

    void setReportData(const QVariantMap &report);
    QVariantMap reportData() const;
    void renderReport(QPainter *painter, const QRectF &targetRect) const;

protected:
    void paintEvent(QPaintEvent *event) override;
    QSize sizeHint() const override;

private:
    QRectF drawHeader(QPainter *painter, const QRectF &page) const;
    QRectF drawSummary(QPainter *painter, const QRectF &area) const;
    QRectF drawScoreTable(QPainter *painter, const QRectF &area) const;
    QString gradeForScore(double score) const;

    QVariantMap currentReport;
};

#endif // PRINTPREVIEWWIDGET_H
