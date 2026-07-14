#ifndef PDFEXPORTER_H
#define PDFEXPORTER_H

#include <QString>
#include <QVariantMap>

class PrintPreviewWidget;

class PdfExporter
{
public:
    bool exportPDF(const QString &filePath,
                   const QVariantMap &report,
                   const PrintPreviewWidget *preview,
                   QString *errorMessage = nullptr) const;
};

#endif // PDFEXPORTER_H
