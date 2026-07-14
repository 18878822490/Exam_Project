QT       += core gui network qml quick quickwidgets quickcontrols2 sql printsupport charts core-private

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header
SOURCES += \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxabstractooxmlfile.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxabstractsheet.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxcell.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxcellformula.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxcelllocation.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxcellrange.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxcellreference.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxchart.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxchartsheet.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxcolor.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxconditionalformatting.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxcontenttypes.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxdatavalidation.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxdatetype.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxdocpropsapp.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxdocpropscore.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxdocument.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxdrawing.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxdrawinganchor.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxformat.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxmediafile.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxnumformatparser.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxreadsax.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxrelationships.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxrichstring.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxsharedstrings.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxsimpleooxmlfile.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxstyles.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxtheme.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxutility.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxworkbook.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxworksheet.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxzipreader.cpp \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/source/xlsxzipwriter.cpp \
    main.cpp \
    mainwindow.cpp \
    AppConfig.cpp \
    LoginWindow.cpp \
    AdminMainWindow.cpp \
    ExamInfoCard.cpp \
    StudentListWidget.cpp \
    AnswerPreviewWidget.cpp \
    ScorePanelWidget.cpp \
    TeacherMarkWindow.cpp \
    ScoreFilterWidget.cpp \
    StatisticCardWidget.cpp \
    TrendChartWidget.cpp \
    DistributionChartWidget.cpp \
    LevelPieChartWidget.cpp \
    StudentRankWidget.cpp \
    QuestionAnalysisWidget.cpp \
    TeacherScoreAnalysisWindow.cpp \
    PrintPreviewWidget.cpp \
    ReportGenerator.cpp \
    PdfExporter.cpp \
    ExcelExporter.cpp \
    ScorePrintWindow.cpp \
    TeacherMainWindow.cpp \
    TeacherDataRepository.cpp \
    StudentMainWindow.cpp

HEADERS += \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxabstractooxmlfile.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxabstractooxmlfile_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxabstractsheet.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxabstractsheet_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxcell.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxcell_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxcellformula.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxcellformula_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxcelllocation.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxcellrange.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxcellreference.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxchart.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxchart_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxchartsheet.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxchartsheet_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxcolor_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxconditionalformatting.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxconditionalformatting_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxcontenttypes_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxdatavalidation.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxdatavalidation_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxdatetype.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxdocpropsapp_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxdocpropscore_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxdocument.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxdocument_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxdrawing_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxdrawinganchor_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxformat.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxformat_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxglobal.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxmediafile_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxnumformatparser_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxreadsax.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxrelationships_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxrichstring.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxrichstring_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxsharedstrings_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxsimpleooxmlfile_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxstyles_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxtheme_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxutility_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxworkbook.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxworkbook_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxworksheet.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxworksheet_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxzipreader_p.h \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/header/xlsxzipwriter_p.h \
    mainwindow.h \
    AppConfig.h \
    LoginWindow.h \
    AdminMainWindow.h \
    ExamInfoCard.h \
    StudentListWidget.h \
    AnswerPreviewWidget.h \
    ScorePanelWidget.h \
    TeacherMarkWindow.h \
    ScoreFilterWidget.h \
    StatisticCardWidget.h \
    TrendChartWidget.h \
    DistributionChartWidget.h \
    LevelPieChartWidget.h \
    StudentRankWidget.h \
    QuestionAnalysisWidget.h \
    TeacherScoreAnalysisWindow.h \
    PrintPreviewWidget.h \
    ReportGenerator.h \
    PdfExporter.h \
    ExcelExporter.h \
    ScorePrintWindow.h \
    LoginWidget.h \
    RegisterWidget.h \
    TeacherMainWindow.h \
    TeacherDataRepository.h \
    StudentMainWindow.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    ../../../0/Qt/QXlsx-master.zip \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/CMakeLists.txt \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/QXlsx.pri \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/cmake/modules/CPackConfig.cmake \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/cmake/modules/qxlsx-config-version.cmake.in \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/cmake/modules/qxlsx-config.cmake.in \
    style.qss \
    QMakeLists.txt \
    CMakeLists.txt \
    qml/LoginView.qml \
    qml/TeacherMain.qml \
    qml/StudentMain.qml \
    qml/AdminMain.qml

TRANSLATIONS += \
    exam_qt_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    ../../../0/Qt/QXlsx/QXlsx-master/QXlsx/QXlsx.pro
