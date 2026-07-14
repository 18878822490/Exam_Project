#ifndef EXCELEXPORTER_H
#define EXCELEXPORTER_H

#include <QString>
#include <QVariantMap>

class ExcelExporter
{
public:
    bool exportExcel(const QString &filePath, const QVariantMap &report, QString *errorMessage = nullptr) const;

private:
    QString gradeForScore(double score) const;
};

#endif // EXCELEXPORTER_H
