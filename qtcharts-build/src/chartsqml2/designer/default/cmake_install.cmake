# Install script for directory: D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/0/Qt/6.8.3/llvm-mingw_64")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "D:/0/Qt/Tools/llvm-mingw1706_64/bin/llvm-objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/qml/QtCharts/designer/default" TYPE FILE FILES
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/AreaSeries.qml"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/BarSeries.qml"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/BoxPlotSeries.qml"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/HorizontalBarSeries.qml"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/HorizontalPercentBarSeries.qml"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/HorizontalStackedBarSeries.qml"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/LineSeries.qml"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/PercentBarSeries.qml"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/PieSeries.qml"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/ScatterSeries.qml"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/SplineSeries.qml"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/StackedBarSeries.qml"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/PolarAreaSeries.qml"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/PolarLineSeries.qml"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/PolarScatterSeries.qml"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/designer/default/PolarSplineSeries.qml"
    )
endif()

