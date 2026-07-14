#ifndef SCOREPRINTWINDOW_H
#define SCOREPRINTWINDOW_H

#include <QVariantList>
#include <QVariantMap>
#include <QWidget>

class ExcelExporter;
class PdfExporter;
class PrintPreviewWidget;
class ReportGenerator;
class ScoreFilterWidget;
class TeacherDataRepository;
class QPushButton;
class QLabel;
class QListWidget;

class ScorePrintWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ScorePrintWindow(QWidget *parent = nullptr);
    ~ScorePrintWindow() override;

    void setRepository(TeacherDataRepository *dataRepository);
    void loadInitialData();
    QVariantList loadScoreData(const QString &className, const QString &examName);
    QVariantMap generateReport(const QString &className, const QString &examName, const QString &reportType);
    bool exportPDF(const QString &filePath);
    bool exportExcel(const QString &filePath);
    bool printReport();
    void playEnterAnimation();

signals:
    void backRequested();
    void minimizeRequested();
    void maximizeRequested();
    void closeRequested();

private:
    void buildUi();
    void applyStyle();
    void refreshReport(const QString &className, const QString &examName, const QString &reportType);
    void refreshStudentSelection();
    QVariantList selectedStudentScores() const;
    void batchGenerateStudentReports();
    QString defaultExportPath(const QString &suffix) const;
    QStringList repositoryClassNames() const;
    QStringList repositoryExamNames() const;
    void showStatus(const QString &message, bool success);

    TeacherDataRepository *repository;
    ReportGenerator *reportGenerator;
    PdfExporter *pdfExporter;
    ExcelExporter *excelExporter;
    ScoreFilterWidget *filterWidget;
    PrintPreviewWidget *previewWidget;
    QListWidget *studentListWidget;
    QLabel *statusLabel;
    QVariantMap currentReport;
};

#endif // SCOREPRINTWINDOW_H
