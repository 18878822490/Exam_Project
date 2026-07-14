#include "PdfExporter.h"

#include "PrintPreviewWidget.h"

#include <QPainter>
#include <QPageSize>
#include <QPrinter>

bool PdfExporter::exportPDF(const QString &filePath,
                            const QVariantMap &report,
                            const PrintPreviewWidget *preview,
                            QString *errorMessage) const
{
    Q_UNUSED(report)
    if (preview == nullptr) {
        if (errorMessage) {
            *errorMessage = QStringLiteral("打印预览为空");
        }
        return false;
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setOutputFileName(filePath);

    QPainter painter(&printer);
    if (!painter.isActive()) {
        if (errorMessage) {
            *errorMessage = QStringLiteral("无法创建PDF文件");
        }
        return false;
    }

    preview->renderReport(&painter, printer.pageRect(QPrinter::DevicePixel).toRect());
    painter.end();
    return true;
}
