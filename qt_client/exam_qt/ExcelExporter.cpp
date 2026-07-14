#include "ExcelExporter.h"

#include "xlsxdocument.h"
#include "xlsxformat.h"

#include <QColor>

bool ExcelExporter::exportExcel(const QString &filePath, const QVariantMap &report, QString *errorMessage) const
{
    QXlsx::Document xlsx;

    QXlsx::Format titleFormat;
    titleFormat.setFontBold(true);
    titleFormat.setFontSize(16);
    titleFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);

    QXlsx::Format headerFormat;
    headerFormat.setFontBold(true);
    headerFormat.setPatternBackgroundColor(QColor(QStringLiteral("#eff6ff")));
    headerFormat.setBorderStyle(QXlsx::Format::BorderThin);
    headerFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);

    QXlsx::Format cellFormat;
    cellFormat.setBorderStyle(QXlsx::Format::BorderThin);
    cellFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);

    const QString title = QStringLiteral("智考星成绩报告");
    xlsx.mergeCells(QStringLiteral("A1:E1"), titleFormat);
    xlsx.write(QStringLiteral("A1"), title, titleFormat);
    xlsx.write(QStringLiteral("A2"), QStringLiteral("考试名称"));
    xlsx.write(QStringLiteral("B2"), report.value(QStringLiteral("examName")).toString());
    xlsx.write(QStringLiteral("C2"), QStringLiteral("班级"));
    xlsx.write(QStringLiteral("D2"), report.value(QStringLiteral("className")).toString());
    xlsx.write(QStringLiteral("E2"), report.value(QStringLiteral("reportType")).toString());

    const QStringList headers = {
        QStringLiteral("排名"),
        QStringLiteral("学号"),
        QStringLiteral("姓名"),
        QStringLiteral("成绩"),
        QStringLiteral("等级")
    };
    for (int col = 0; col < headers.size(); ++col) {
        xlsx.write(4, col + 1, headers.at(col), headerFormat);
    }

    const QVariantList scores = report.value(QStringLiteral("scores")).toList();
    for (int row = 0; row < scores.size(); ++row) {
        const QVariantMap item = scores.at(row).toMap();
        const double score = item.value(QStringLiteral("score")).toDouble();
        xlsx.write(row + 5, 1, row + 1, cellFormat);
        xlsx.write(row + 5, 2, item.value(QStringLiteral("studentNo")).toString(), cellFormat);
        xlsx.write(row + 5, 3, item.value(QStringLiteral("name")).toString(), cellFormat);
        xlsx.write(row + 5, 4, score, cellFormat);
        xlsx.write(row + 5, 5, gradeForScore(score), cellFormat);
    }

    xlsx.setColumnWidth(1, 10);
    xlsx.setColumnWidth(2, 18);
    xlsx.setColumnWidth(3, 16);
    xlsx.setColumnWidth(4, 12);
    xlsx.setColumnWidth(5, 14);

    if (!xlsx.saveAs(filePath)) {
        if (errorMessage) {
            *errorMessage = QStringLiteral("Excel文件保存失败");
        }
        return false;
    }
    return true;
}

QString ExcelExporter::gradeForScore(double score) const
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
