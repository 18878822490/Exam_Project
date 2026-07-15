#include "ScorePrintWindow.h"

#include "ExcelExporter.h"
#include "PdfExporter.h"
#include "PrintPreviewWidget.h"
#include "ReportGenerator.h"
#include "ScoreFilterWidget.h"
#include "TeacherDataRepository.h"

#include <QDesktopServices>
#include <QAbstractItemView>
#include <QDate>
#include <QDir>
#include <QFileInfo>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPainter>
#include <QPageSize>
#include <QPrintDialog>
#include <QPrinter>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QScrollArea>
#include <QStandardPaths>
#include <QTimer>
#include <QUrl>
#include <QVBoxLayout>

namespace {
void addPrintShadow(QWidget *widget, int blur = 28, int y = 10)
{
    auto *shadow = new QGraphicsDropShadowEffect(widget);
    shadow->setBlurRadius(blur);
    shadow->setOffset(0, y);
    shadow->setColor(QColor(29, 49, 86, 24));
    widget->setGraphicsEffect(shadow);
}

QPushButton *printWindowButton(const QString &text, QWidget *parent)
{
    auto *button = new QPushButton(text, parent);
    button->setObjectName(QStringLiteral("PrintWindowButton"));
    button->setCursor(Qt::PointingHandCursor);
    button->setFixedSize(40, 36);
    return button;
}

QPushButton *actionButton(const QString &text, const QString &objectName, QWidget *parent)
{
    auto *button = new QPushButton(text, parent);
    button->setObjectName(objectName);
    button->setCursor(Qt::PointingHandCursor);
    button->setMinimumHeight(46);
    return button;
}

QString safeFilePart(QString value)
{
    value = value.trimmed();
    const QString bad = QStringLiteral("\\/:*?\"<>| ");
    for (const QChar ch : bad) {
        value.replace(ch, QLatin1Char('_'));
    }
    return value.isEmpty() ? QStringLiteral("成绩报告") : value;
}
}

ScorePrintWindow::ScorePrintWindow(QWidget *parent)
    : QWidget(parent)
    , repository(nullptr)
    , reportGenerator(new ReportGenerator)
    , pdfExporter(new PdfExporter)
    , excelExporter(new ExcelExporter)
    , filterWidget(nullptr)
    , previewWidget(nullptr)
    , studentListWidget(nullptr)
    , statusLabel(nullptr)
{
    setObjectName(QStringLiteral("ScorePrintWindow"));
    buildUi();
    applyStyle();
    loadInitialData();
}

ScorePrintWindow::~ScorePrintWindow()
{
    delete reportGenerator;
    delete pdfExporter;
    delete excelExporter;
}

void ScorePrintWindow::setRepository(TeacherDataRepository *dataRepository)
{
    repository = dataRepository;
    loadInitialData();
}

void ScorePrintWindow::loadInitialData()
{
    QStringList classes = repositoryClassNames();
    QStringList exams = repositoryExamNames();

    filterWidget->setClasses(classes);
    filterWidget->setExams(exams);
    filterWidget->setThirdFilter(QStringLiteral("报表类型"), {
        QStringLiteral("班级成绩总表"),
        QStringLiteral("学生成绩报告"),
        QStringLiteral("成绩分析报告")
    });
    filterWidget->setQueryButtonText(QStringLiteral("生成报表"));
    refreshReport(filterWidget->currentClass(), filterWidget->currentExam(), filterWidget->currentReportType());
}

QVariantList ScorePrintWindow::loadScoreData(const QString &className, const QString &examName)
{
    if (repository == nullptr) {
        return {};
    }
    const int examId = repository->examIdForName(examName);
    return repository->getScoreAnalysis(examId, className).value(QStringLiteral("scores")).toList();
}

QVariantMap ScorePrintWindow::generateReport(const QString &className, const QString &examName, const QString &reportType)
{
    if (repository == nullptr) {
        return {};
    }

    const int examId = repository->examIdForName(examName);
    QVariantMap report = repository->getScoreReport(examId, className);
    if (report.isEmpty()) {
        report = QVariantMap{
            {QStringLiteral("title"), QStringLiteral("智考星成绩报告")},
            {QStringLiteral("examId"), examId},
            {QStringLiteral("examName"), examName},
            {QStringLiteral("className"), className},
            {QStringLiteral("reportType"), reportType},
            {QStringLiteral("date"), QDate::currentDate().toString(QStringLiteral("yyyy-MM-dd"))},
            {QStringLiteral("scores"), QVariantList{}},
            {QStringLiteral("summary"), QVariantMap{}}
        };
    }

    QVariantMap summary = report.value(QStringLiteral("summary")).toMap();
    report.insert(QStringLiteral("title"), QStringLiteral("智考星成绩报告"));
    report.insert(QStringLiteral("examName"), examName);
    report.insert(QStringLiteral("className"), className);
    report.insert(QStringLiteral("reportType"), reportType);
    report.insert(QStringLiteral("date"), QDate::currentDate().toString(QStringLiteral("yyyy-MM-dd")));
    report.insert(QStringLiteral("stats"), QVariantMap{
                      {QStringLiteral("average"), summary.value(QStringLiteral("average"), summary.value(QStringLiteral("average_score"), 0))},
                      {QStringLiteral("highest"), summary.value(QStringLiteral("highest"), summary.value(QStringLiteral("highest_score"), 0))},
                      {QStringLiteral("lowest"), summary.value(QStringLiteral("lowest"), summary.value(QStringLiteral("lowest_score"), 0))}
                  });
    return report;
}

bool ScorePrintWindow::exportPDF(const QString &filePath)
{
    QString error;
    const bool ok = pdfExporter->exportPDF(filePath, currentReport, previewWidget, &error);
    showStatus(ok ? QStringLiteral("PDF已导出：%1").arg(QFileInfo(filePath).fileName())
                  : QStringLiteral("PDF导出失败：%1").arg(error),
               ok);
    if (ok) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    }
    return ok;
}

bool ScorePrintWindow::exportExcel(const QString &filePath)
{
    QString error;
    const bool ok = excelExporter->exportExcel(filePath, currentReport, &error);
    showStatus(ok ? QStringLiteral("Excel已导出：%1").arg(QFileInfo(filePath).fileName())
                  : QStringLiteral("Excel导出失败：%1").arg(error),
               ok);
    if (ok) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    }
    return ok;
}

bool ScorePrintWindow::printReport()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPageSize(QPageSize::A4));
    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle(QStringLiteral("打印成绩报告"));
    if (dialog.exec() != QDialog::Accepted) {
        return false;
    }

    QPainter painter(&printer);
    if (!painter.isActive()) {
        showStatus(QStringLiteral("打印失败：无法连接打印设备"), false);
        return false;
    }
    previewWidget->renderReport(&painter, printer.pageRect(QPrinter::DevicePixel).toRect());
    painter.end();
    showStatus(QStringLiteral("已发送到打印机"), true);
    return true;
}

void ScorePrintWindow::playEnterAnimation()
{
    auto *effect = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(effect);
    auto *animation = new QPropertyAnimation(effect, "opacity", this);
    animation->setDuration(480);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    connect(animation, &QPropertyAnimation::finished, this, [this]() {
        setGraphicsEffect(nullptr);
    });
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void ScorePrintWindow::buildUi()
{
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(24, 20, 24, 24);
    root->setSpacing(18);

    auto *toolbar = new QHBoxLayout;
    toolbar->setSpacing(12);
    auto *brand = new QLabel(QStringLiteral("智考星 · 成绩报表打印中心"), this);
    brand->setObjectName(QStringLiteral("PrintBrandTitle"));
    auto *backButton = new QPushButton(QStringLiteral("返回成绩分析"), this);
    backButton->setObjectName(QStringLiteral("PrintGhostButton"));
    backButton->setCursor(Qt::PointingHandCursor);
    auto *minButton = printWindowButton(QStringLiteral("-"), this);
    auto *maxButton = printWindowButton(QStringLiteral("□"), this);
    auto *closeButton = printWindowButton(QStringLiteral("X"), this);
    closeButton->setProperty("danger", true);

    toolbar->addWidget(brand);
    toolbar->addStretch();
    toolbar->addWidget(backButton);
    toolbar->addWidget(minButton);
    toolbar->addWidget(maxButton);
    toolbar->addWidget(closeButton);
    root->addLayout(toolbar);

    filterWidget = new ScoreFilterWidget(this);
    addPrintShadow(filterWidget);
    root->addWidget(filterWidget);

    auto *previewCard = new QFrame(this);
    previewCard->setObjectName(QStringLiteral("PrintPreviewCard"));
    addPrintShadow(previewCard);
    auto *previewLayout = new QVBoxLayout(previewCard);
    previewLayout->setContentsMargins(22, 22, 22, 22);
    previewLayout->setSpacing(14);
    auto *previewTitle = new QLabel(QStringLiteral("打印预览"), previewCard);
    previewTitle->setObjectName(QStringLiteral("PrintPanelTitle"));
    previewWidget = new PrintPreviewWidget(previewCard);
    auto *scroll = new QScrollArea(previewCard);
    scroll->setObjectName(QStringLiteral("PrintPreviewScroll"));
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setWidget(previewWidget);
    previewLayout->addWidget(previewTitle);

    auto *previewBody = new QHBoxLayout;
    previewBody->setSpacing(16);
    previewBody->addWidget(scroll, 1);

    auto *studentPanel = new QFrame(previewCard);
    studentPanel->setObjectName(QStringLiteral("PrintStudentPanel"));
    studentPanel->setMinimumWidth(240);
    auto *studentPanelLayout = new QVBoxLayout(studentPanel);
    studentPanelLayout->setContentsMargins(16, 16, 16, 16);
    studentPanelLayout->setSpacing(12);
    auto *studentTitle = new QLabel(QStringLiteral("批量学生"), studentPanel);
    studentTitle->setObjectName(QStringLiteral("PrintPanelTitleSmall"));
    auto *studentHint = new QLabel(QStringLiteral("勾选学生后可批量生成个人成绩报告"), studentPanel);
    studentHint->setObjectName(QStringLiteral("PrintHintLabel"));
    studentHint->setWordWrap(true);
    studentListWidget = new QListWidget(studentPanel);
    studentListWidget->setObjectName(QStringLiteral("PrintStudentList"));
    studentListWidget->setSelectionMode(QAbstractItemView::NoSelection);
    studentPanelLayout->addWidget(studentTitle);
    studentPanelLayout->addWidget(studentHint);
    studentPanelLayout->addWidget(studentListWidget, 1);
    previewBody->addWidget(studentPanel);

    previewLayout->addLayout(previewBody, 1);
    root->addWidget(previewCard, 1);

    auto *actionBar = new QFrame(this);
    actionBar->setObjectName(QStringLiteral("PrintActionBar"));
    addPrintShadow(actionBar);
    auto *actionLayout = new QHBoxLayout(actionBar);
    actionLayout->setContentsMargins(20, 16, 20, 16);
    actionLayout->setSpacing(12);
    statusLabel = new QLabel(QStringLiteral("选择班级和考试后可生成、打印或导出报表"), actionBar);
    statusLabel->setObjectName(QStringLiteral("PrintStatusLabel"));
    auto *batchButton = actionButton(QStringLiteral("批量生成个人报告"), QStringLiteral("PrintGhostButton"), actionBar);
    auto *printButton = actionButton(QStringLiteral("打印"), QStringLiteral("PrintPrimaryButton"), actionBar);
    auto *pdfButton = actionButton(QStringLiteral("导出PDF"), QStringLiteral("PrintPrimaryButton"), actionBar);
    auto *excelButton = actionButton(QStringLiteral("导出Excel"), QStringLiteral("PrintPrimaryButton"), actionBar);
    actionLayout->addWidget(statusLabel, 1);
    actionLayout->addWidget(batchButton);
    actionLayout->addWidget(printButton);
    actionLayout->addWidget(pdfButton);
    actionLayout->addWidget(excelButton);
    root->addWidget(actionBar);

    connect(backButton, &QPushButton::clicked, this, &ScorePrintWindow::backRequested);
    connect(minButton, &QPushButton::clicked, this, &ScorePrintWindow::minimizeRequested);
    connect(maxButton, &QPushButton::clicked, this, &ScorePrintWindow::maximizeRequested);
    connect(closeButton, &QPushButton::clicked, this, &ScorePrintWindow::closeRequested);
    connect(filterWidget, &ScoreFilterWidget::queryRequested, this, [this](const QString &className, const QString &examName, const QString &reportType) {
        refreshReport(className, examName, reportType);
    });
    connect(printButton, &QPushButton::clicked, this, &ScorePrintWindow::printReport);
    connect(pdfButton, &QPushButton::clicked, this, [this]() {
        exportPDF(defaultExportPath(QStringLiteral("pdf")));
    });
    connect(excelButton, &QPushButton::clicked, this, [this]() {
        exportExcel(defaultExportPath(QStringLiteral("xlsx")));
    });
    connect(batchButton, &QPushButton::clicked, this, &ScorePrintWindow::batchGenerateStudentReports);
}

void ScorePrintWindow::applyStyle()
{
    setStyleSheet(QStringLiteral(R"(
        #ScorePrintWindow {
            background: #eef3fb;
            color: #111827;
            font-family: "Microsoft YaHei", "Segoe UI";
        }
        #PrintBrandTitle {
            color: #111827;
            font-size: 28px;
            font-weight: 800;
        }
        #PrintPreviewCard, #PrintActionBar {
            background: #ffffff;
            border: 1px solid #e5edf6;
            border-radius: 24px;
        }
        #PrintStudentPanel {
            background: #f8fbff;
            border: 1px solid #e5edf6;
            border-radius: 18px;
        }
        #PrintPanelTitle {
            color: #111827;
            font-size: 22px;
            font-weight: 800;
        }
        #PrintPanelTitleSmall {
            color: #111827;
            font-size: 18px;
            font-weight: 800;
        }
        #PrintHintLabel {
            color: #64748b;
            font-size: 13px;
            font-weight: 700;
        }
        #PrintStudentList {
            background: transparent;
            border: none;
            color: #111827;
            font-size: 14px;
            outline: none;
        }
        #PrintStudentList::item {
            min-height: 34px;
            padding: 4px 6px;
            border-radius: 8px;
        }
        #PrintStudentList::item:hover {
            background: #eff6ff;
        }
        #PrintPreviewScroll {
            background: transparent;
            border: none;
        }
        #PrintStatusLabel {
            color: #64748b;
            font-size: 15px;
            font-weight: 700;
        }
        #PrintPrimaryButton, #PrintGhostButton {
            min-height: 42px;
            border-radius: 14px;
            font-size: 15px;
            font-weight: 800;
            padding: 0 18px;
        }
        #PrintPrimaryButton {
            color: #ffffff;
            background: #2563eb;
            border: 1px solid #2563eb;
        }
        #PrintPrimaryButton:hover {
            background: #1d4ed8;
        }
        #PrintGhostButton {
            color: #2563eb;
            background: #eff6ff;
            border: 1px solid #bfdbfe;
        }
        #PrintGhostButton:hover {
            background: #dbeafe;
        }
        #PrintWindowButton {
            color: #334155;
            background: #ffffff;
            border: 1px solid #dbe7f6;
            border-radius: 12px;
            font-size: 16px;
            font-weight: 800;
        }
        #PrintWindowButton:hover {
            background: #eff6ff;
        }
        #PrintWindowButton[danger="true"]:hover {
            color: #ffffff;
            background: #ef4444;
            border-color: #ef4444;
        }
        QScrollBar:vertical {
            width: 12px;
            background: transparent;
            margin: 2px;
        }
        QScrollBar::handle:vertical {
            background: #bfd0e5;
            border-radius: 6px;
            min-height: 48px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0;
        }
    )"));
}

void ScorePrintWindow::refreshReport(const QString &className, const QString &examName, const QString &reportType)
{
    currentReport = generateReport(className, examName, reportType);
    previewWidget->setReportData(currentReport);
    refreshStudentSelection();
    showStatus(QStringLiteral("已生成：%1 · %2 · %3").arg(className, examName, reportType), true);
}

void ScorePrintWindow::refreshStudentSelection()
{
    studentListWidget->clear();
    const QVariantList scores = currentReport.value(QStringLiteral("scores")).toList();
    for (int i = 0; i < scores.size(); ++i) {
        const QVariantMap row = scores.at(i).toMap();
        auto *item = new QListWidgetItem(QStringLiteral("%1  %2分").arg(row.value(QStringLiteral("name")).toString(),
                                                                    QString::number(row.value(QStringLiteral("score")).toDouble(), 'f', 1)),
                                         studentListWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(i < 8 ? Qt::Checked : Qt::Unchecked);
        item->setData(Qt::UserRole, row);
    }
}

QVariantList ScorePrintWindow::selectedStudentScores() const
{
    QVariantList rows;
    for (int i = 0; i < studentListWidget->count(); ++i) {
        const QListWidgetItem *item = studentListWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            rows.append(item->data(Qt::UserRole));
        }
    }
    return rows;
}

void ScorePrintWindow::batchGenerateStudentReports()
{
    const QVariantList selected = selectedStudentScores();
    if (selected.isEmpty()) {
        showStatus(QStringLiteral("请至少勾选一名学生"), false);
        return;
    }

    QString dir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    if (dir.isEmpty()) {
        dir = QDir::homePath();
    }
    QDir outputDir(QDir(dir).filePath(QStringLiteral("智考星_学生成绩报告")));
    outputDir.mkpath(QStringLiteral("."));

    const QVariantMap original = currentReport;
    int successCount = 0;
    for (const QVariant &value : selected) {
        const QVariantMap student = value.toMap();
        QVariantMap personal = original;
        personal.insert(QStringLiteral("reportType"), QStringLiteral("学生成绩报告"));
        personal.insert(QStringLiteral("scores"), QVariantList{student});
        currentReport = personal;
        previewWidget->setReportData(currentReport);
        const QString fileName = QStringLiteral("%1_%2_%3.pdf")
                .arg(safeFilePart(original.value(QStringLiteral("examName")).toString()),
                     safeFilePart(student.value(QStringLiteral("studentNo")).toString()),
                     safeFilePart(student.value(QStringLiteral("name")).toString()));
        if (pdfExporter->exportPDF(outputDir.filePath(fileName), currentReport, previewWidget)) {
            ++successCount;
        }
    }
    currentReport = original;
    previewWidget->setReportData(currentReport);
    showStatus(QStringLiteral("已生成 %1 份个人PDF报告：%2").arg(successCount).arg(outputDir.path()), successCount > 0);
    if (successCount > 0) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(outputDir.path()));
    }
}

QString ScorePrintWindow::defaultExportPath(const QString &suffix) const
{
    QString dir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    if (dir.isEmpty()) {
        dir = QDir::homePath();
    }
    const QString name = QStringLiteral("智考星_%1_%2.%3")
            .arg(safeFilePart(currentReport.value(QStringLiteral("examName")).toString()),
                 safeFilePart(currentReport.value(QStringLiteral("className")).toString()),
                 suffix);
    return QDir(dir).filePath(name);
}

QStringList ScorePrintWindow::repositoryClassNames() const
{
    QStringList names;
    if (repository == nullptr) {
        return names;
    }
    const QVariantList rows = repository->getTeacherClasses();
    for (const QVariant &value : rows) {
        const QString name = value.toMap().value(QStringLiteral("name")).toString().trimmed();
        if (!name.isEmpty() && !names.contains(name)) {
            names.append(name);
        }
    }
    return names;
}

QStringList ScorePrintWindow::repositoryExamNames() const
{
    QStringList names;
    if (repository == nullptr) {
        return names;
    }
    const QVariantList rows = repository->getExamList();
    for (const QVariant &value : rows) {
        const QVariantMap row = value.toMap();
        const QString name = row.value(QStringLiteral("name"), row.value(QStringLiteral("title"))).toString().trimmed();
        if (!name.isEmpty() && !names.contains(name)) {
            names.append(name);
        }
    }
    return names;
}

void ScorePrintWindow::showStatus(const QString &message, bool success)
{
    statusLabel->setText(message);
    statusLabel->setStyleSheet(QStringLiteral("color:%1;").arg(success ? QStringLiteral("#16a34a") : QStringLiteral("#ef4444")));
}
