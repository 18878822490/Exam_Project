# Install script for directory: D:/0/Qt/6.8.3/Src/qtcharts/src/charts

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./metatypes" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/src/charts/meta_types/qt6charts_relwithdebinfo_metatypes.json")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Charts" TYPE FILE FILES
    "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6Charts/Qt6ChartsConfig.cmake"
    "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6Charts/Qt6ChartsConfigVersion.cmake"
    "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6Charts/Qt6ChartsConfigVersionImpl.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Exam_Project/qtcharts-build/lib/libQt6Charts.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Exam_Project/qtcharts-build/bin/Qt6Charts.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/Qt6Charts.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/Qt6Charts.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "D:/0/Qt/Tools/llvm-mingw1706_64/bin/llvm-strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/Qt6Charts.dll")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Charts/Qt6ChartsTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Charts/Qt6ChartsTargets.cmake"
         "D:/Exam_Project/qtcharts-build/src/charts/CMakeFiles/Export/12e2d5f81fa4e0d630778d4472891fdb/Qt6ChartsTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Charts/Qt6ChartsTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Charts/Qt6ChartsTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Charts" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/src/charts/CMakeFiles/Export/12e2d5f81fa4e0d630778d4472891fdb/Qt6ChartsTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Charts" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/src/charts/CMakeFiles/Export/12e2d5f81fa4e0d630778d4472891fdb/Qt6ChartsTargets-relwithdebinfo.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Charts" TYPE FILE FILES
    "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6Charts/Qt6ChartsVersionlessAliasTargets.cmake"
    "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6Charts/Qt6ChartsVersionlessTargets.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Charts" TYPE FILE FILES
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/bin/Qt6Charts.debug")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/modules" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/modules/Charts.json")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "_install_html_docs_Charts")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/doc/qtcharts" TYPE DIRECTORY FILES "D:/Exam_Project/qtcharts-build/doc/qtcharts/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "_install_qch_docs_Charts")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/doc" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/doc/qtcharts.qch")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Charts" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6Charts/Qt6ChartsAdditionalTargetInfo.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/QtCharts" TYPE DIRECTORY FILES "D:/Exam_Project/qtcharts-build/include/QtCharts/.syncqt_staging/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/QtCharts" TYPE FILE FILES
    "D:/Exam_Project/qtcharts-build/include/QtCharts/qtchartsexports.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/barcategoryaxis/qbarcategoryaxis.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/categoryaxis/qcategoryaxis.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/coloraxis/qcoloraxis.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/logvalueaxis/qlogvalueaxis.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/qabstractaxis.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/valueaxis/qvalueaxis.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qlegend.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qlegendmarker.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qxylegendmarker.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/qabstractseries.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/qchart.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/qchartglobal.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/qchartview.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/qpolarchart.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/xychart/qhxymodelmapper.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/xychart/qvxymodelmapper.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/xychart/qxymodelmapper.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/xychart/qxyseries.h"
    "D:/Exam_Project/qtcharts-build/src/charts/qtcharts-config.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/areachart/qareaseries.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qarealegendmarker.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/horizontal/bar/qhorizontalbarseries.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/horizontal/percent/qhorizontalpercentbarseries.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/horizontal/stacked/qhorizontalstackedbarseries.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/qabstractbarseries.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/qbarmodelmapper.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/qbarset.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/qhbarmodelmapper.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/qvbarmodelmapper.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/vertical/bar/qbarseries.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/vertical/percent/qpercentbarseries.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/vertical/stacked/qstackedbarseries.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qbarlegendmarker.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/linechart/qlineseries.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qpielegendmarker.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/piechart/qhpiemodelmapper.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/piechart/qpiemodelmapper.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/piechart/qpieseries.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/piechart/qpieslice.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/piechart/qvpiemodelmapper.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/scatterchart/qscatterseries.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/splinechart/qsplineseries.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/boxplotchart/qboxplotmodelmapper.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/boxplotchart/qboxplotseries.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/boxplotchart/qboxset.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/boxplotchart/qhboxplotmodelmapper.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/boxplotchart/qvboxplotmodelmapper.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qboxplotlegendmarker.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/qcandlestickmodelmapper.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/qcandlestickseries.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/qcandlestickset.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/qhcandlestickmodelmapper.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/qvcandlestickmodelmapper.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qcandlesticklegendmarker.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/datetimeaxis/qdatetimeaxis.h"
    "D:/Exam_Project/qtcharts-build/include/QtCharts/QtChartsDepends"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/QtCharts/6.8.3/QtCharts/private" TYPE FILE FILES
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/animations/axisanimation_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/animations/chartanimation_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/animations/xyanimation_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/barcategoryaxis/chartbarcategoryaxisx_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/barcategoryaxis/chartbarcategoryaxisy_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/barcategoryaxis/qbarcategoryaxis_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/cartesianchartaxis_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/categoryaxis/chartcategoryaxisx_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/categoryaxis/chartcategoryaxisy_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/categoryaxis/polarchartcategoryaxisangular_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/categoryaxis/polarchartcategoryaxisradial_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/categoryaxis/qcategoryaxis_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/coloraxis/qcoloraxis_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/coloraxis/chartcoloraxisy_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/coloraxis/chartcoloraxisx_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/chartaxiselement_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/editableaxislabel_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/horizontalaxis_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/linearrowitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/logvalueaxis/chartlogvalueaxisx_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/logvalueaxis/chartlogvalueaxisy_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/logvalueaxis/polarchartlogvalueaxisangular_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/logvalueaxis/polarchartlogvalueaxisradial_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/logvalueaxis/qlogvalueaxis_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/polarchartaxis_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/polarchartaxisangular_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/polarchartaxisradial_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/qabstractaxis_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/valueaxis/chartvalueaxisx_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/valueaxis/chartvalueaxisy_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/valueaxis/polarchartvalueaxisangular_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/valueaxis/polarchartvalueaxisradial_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/valueaxis/qvalueaxis_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/valueaxis/valueaxislabel_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/verticalaxis_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/chartbackground_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/chartconfig_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/chartdataset_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/chartelement_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/charthelpers_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/chartitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/chartpresenter_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/chartthememanager_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/charttitle_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/domain/abstractdomain_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/domain/logxlogydomain_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/domain/logxlogypolardomain_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/domain/logxydomain_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/domain/logxypolardomain_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/domain/polardomain_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/domain/xlogydomain_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/domain/xlogypolardomain_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/domain/xydomain_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/domain/xypolardomain_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/layout/abstractchartlayout_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/layout/cartesianchartlayout_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/layout/polarchartlayout_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/legendlayout_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/legendmarkeritem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/legendscroller_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/legendmoveresizehandler_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qlegend_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qlegendmarker_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qxylegendmarker_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/qabstractseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/qchart_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/qchartglobal_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/qchartview_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/scroller_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/themes/charttheme_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/themes/chartthemebluecerulean_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/themes/chartthemeblueicy_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/themes/chartthemebluencs_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/themes/chartthemebrownsand_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/themes/chartthemedark_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/themes/chartthemehighcontrast_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/themes/chartthemelight_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/themes/chartthemeqt_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/themes/chartthemesystem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/xychart/glxyseriesdata_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/xychart/qxymodelmapper_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/xychart/qxyseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/xychart/xychart_p.h"
    "D:/Exam_Project/qtcharts-build/src/charts/qtcharts-config_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/glwidget_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/areachart/areachartitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/areachart/qareaseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qarealegendmarker_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/animations/baranimation_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/abstractbarchartitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/bar_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/horizontal/bar/horizontalbarchartitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/horizontal/bar/qhorizontalbarseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/horizontal/percent/horizontalpercentbarchartitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/horizontal/percent/qhorizontalpercentbarseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/horizontal/stacked/horizontalstackedbarchartitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/horizontal/stacked/qhorizontalstackedbarseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/qabstractbarseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/qbarmodelmapper_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/qbarset_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/vertical/bar/barchartitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/vertical/bar/qbarseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/vertical/percent/percentbarchartitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/vertical/percent/qpercentbarseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/vertical/stacked/qstackedbarseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/vertical/stacked/stackedbarchartitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qbarlegendmarker_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/linechart/linechartitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/linechart/qlineseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/animations/pieanimation_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/animations/piesliceanimation_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qpielegendmarker_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/piechart/piechartitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/piechart/pieslicedata_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/piechart/piesliceitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/piechart/qpiemodelmapper_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/piechart/qpieseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/piechart/qpieslice_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/animations/scatteranimation_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/scatterchart/qscatterseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/scatterchart/scatterchartitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/animations/splineanimation_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/splinechart/qsplineseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/splinechart/splinechartitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/animations/boxplotanimation_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/animations/boxwhiskersanimation_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/boxplotchart/boxplotchartitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/boxplotchart/boxwhiskers_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/boxplotchart/boxwhiskersdata_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/boxplotchart/qboxplotmodelmapper_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/boxplotchart/qboxplotseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/boxplotchart/qboxset_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qboxplotlegendmarker_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/animations/candlestickanimation_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/animations/candlestickbodywicksanimation_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/candlestick_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/candlestickchartitem_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/candlestickdata_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/qcandlestickmodelmapper_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/qcandlestickseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/qcandlestickset_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qcandlesticklegendmarker_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/datetimeaxis/chartdatetimeaxisx_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/datetimeaxis/chartdatetimeaxisy_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/datetimeaxis/datetimeaxislabel_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/datetimeaxis/polarchartdatetimeaxisangular_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/datetimeaxis/polarchartdatetimeaxisradial_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/charts/axis/datetimeaxis/qdatetimeaxis_p.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/mkspecs/modules" TYPE FILE FILES
    "D:/Exam_Project/qtcharts-build/mkspecs/modules/qt_lib_charts.pri"
    "D:/Exam_Project/qtcharts-build/mkspecs/modules/qt_lib_charts_private.pri"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/lib/pkgconfig/Qt6Charts.pc")
endif()

