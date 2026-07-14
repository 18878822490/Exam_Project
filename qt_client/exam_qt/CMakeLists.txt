cmake_minimum_required(VERSION 3.21)

project(exam_qt VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network Qml Quick QuickWidgets QuickControls2 Sql PrintSupport Charts)

qt_add_executable(exam_qt
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    LoginWindow.cpp
    LoginWindow.h
    AdminMainWindow.cpp
    AdminMainWindow.h
    ExamInfoCard.cpp
    ExamInfoCard.h
    StudentListWidget.cpp
    StudentListWidget.h
    AnswerPreviewWidget.cpp
    AnswerPreviewWidget.h
    ScorePanelWidget.cpp
    ScorePanelWidget.h
    TeacherMarkWindow.cpp
    TeacherMarkWindow.h
    ScoreFilterWidget.cpp
    ScoreFilterWidget.h
    StatisticCardWidget.cpp
    StatisticCardWidget.h
    TrendChartWidget.cpp
    TrendChartWidget.h
    DistributionChartWidget.cpp
    DistributionChartWidget.h
    LevelPieChartWidget.cpp
    LevelPieChartWidget.h
    StudentRankWidget.cpp
    StudentRankWidget.h
    QuestionAnalysisWidget.cpp
    QuestionAnalysisWidget.h
    TeacherScoreAnalysisWindow.cpp
    TeacherScoreAnalysisWindow.h
    PrintPreviewWidget.cpp
    PrintPreviewWidget.h
    ReportGenerator.cpp
    ReportGenerator.h
    PdfExporter.cpp
    PdfExporter.h
    ExcelExporter.cpp
    ExcelExporter.h
    ScorePrintWindow.cpp
    ScorePrintWindow.h
    AppConfig.cpp
    AppConfig.h
    LoginWidget.h
    RegisterWidget.h
    TeacherMainWindow.cpp
    TeacherMainWindow.h
    TeacherDataRepository.cpp
    TeacherDataRepository.h
    StudentMainWindow.cpp
    StudentMainWindow.h
    resources.qrc
)

target_link_libraries(exam_qt PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickWidgets
    Qt6::QuickControls2
    Qt6::Sql
    Qt6::PrintSupport
    Qt6::Charts
)
