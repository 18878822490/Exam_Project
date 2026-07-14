# Install script for directory: D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./metatypes" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/src/chartsqml2/meta_types/qt6chartsqml_relwithdebinfo_metatypes.json")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6ChartsQml" TYPE FILE FILES
    "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6ChartsQml/Qt6ChartsQmlConfig.cmake"
    "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6ChartsQml/Qt6ChartsQmlConfigVersion.cmake"
    "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6ChartsQml/Qt6ChartsQmlConfigVersionImpl.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Exam_Project/qtcharts-build/lib/libQt6ChartsQml.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Exam_Project/qtcharts-build/bin/Qt6ChartsQml.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/Qt6ChartsQml.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/Qt6ChartsQml.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "D:/0/Qt/Tools/llvm-mingw1706_64/bin/llvm-strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/Qt6ChartsQml.dll")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6ChartsQml/Qt6ChartsQmlTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6ChartsQml/Qt6ChartsQmlTargets.cmake"
         "D:/Exam_Project/qtcharts-build/src/chartsqml2/CMakeFiles/Export/f8e0043e4e32e8c4aa72197c94459f3a/Qt6ChartsQmlTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6ChartsQml/Qt6ChartsQmlTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6ChartsQml/Qt6ChartsQmlTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6ChartsQml" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/src/chartsqml2/CMakeFiles/Export/f8e0043e4e32e8c4aa72197c94459f3a/Qt6ChartsQmlTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6ChartsQml" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/src/chartsqml2/CMakeFiles/Export/f8e0043e4e32e8c4aa72197c94459f3a/Qt6ChartsQmlTargets-relwithdebinfo.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6ChartsQml" TYPE FILE FILES
    "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6ChartsQml/Qt6ChartsQmlVersionlessAliasTargets.cmake"
    "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6ChartsQml/Qt6ChartsQmlVersionlessTargets.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6ChartsQml" TYPE FILE FILES
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/bin/Qt6ChartsQml.debug")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/modules" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/modules/ChartsQml.json")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Qml/QmlPlugins" TYPE FILE FILES
    "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6Qml/QmlPlugins/Qt6qtchartsqml2Config.cmake"
    "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6Qml/QmlPlugins/Qt6qtchartsqml2ConfigVersion.cmake"
    "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6Qml/QmlPlugins/Qt6qtchartsqml2ConfigVersionImpl.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/qml/QtCharts" TYPE MODULE FILES "D:/Exam_Project/qtcharts-build/qml/QtCharts/qtchartsqml2plugin.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/qml/QtCharts/qtchartsqml2plugin.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/qml/QtCharts/qtchartsqml2plugin.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "D:/0/Qt/Tools/llvm-mingw1706_64/bin/llvm-strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/qml/QtCharts/qtchartsqml2plugin.dll")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Qml/QmlPlugins/Qt6qtchartsqml2Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Qml/QmlPlugins/Qt6qtchartsqml2Targets.cmake"
         "D:/Exam_Project/qtcharts-build/src/chartsqml2/CMakeFiles/Export/a1553df5751c39c799cb845445fde701/Qt6qtchartsqml2Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Qml/QmlPlugins/Qt6qtchartsqml2Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Qml/QmlPlugins/Qt6qtchartsqml2Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Qml/QmlPlugins" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/src/chartsqml2/CMakeFiles/Export/a1553df5751c39c799cb845445fde701/Qt6qtchartsqml2Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Qml/QmlPlugins" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/src/chartsqml2/CMakeFiles/Export/a1553df5751c39c799cb845445fde701/Qt6qtchartsqml2Targets-relwithdebinfo.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/qml/QtCharts" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/qml/QtCharts/qtchartsqml2plugin.debug")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/qml/QtCharts" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/qml/QtCharts/plugins.qmltypes")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/qml/QtCharts" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/qml/QtCharts/qmldir")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Exam_Project/qtcharts-build/src/chartsqml2/designer/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6ChartsQml" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6ChartsQml/Qt6ChartsQmlAdditionalTargetInfo.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Qml/QmlPlugins" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6Qml/QmlPlugins/Qt6qtchartsqml2AdditionalTargetInfo.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/QtChartsQml" TYPE DIRECTORY FILES "D:/Exam_Project/qtcharts-build/include/QtChartsQml/.syncqt_staging/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/QtChartsQml" TYPE FILE FILES
    "D:/Exam_Project/qtcharts-build/include/QtChartsQml/qtchartsqmlexports.h"
    "D:/Exam_Project/qtcharts-build/include/QtChartsQml/QtChartsQmlDepends"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/QtChartsQml/6.8.3/QtChartsQml/private" TYPE FILE FILES
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativeabstractrendernode_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativeaxes_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativecategoryaxis_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativechart_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativechartglobal_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativechartnode_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativeforeigntypes_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativemargins_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativepolarchart_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativexypoint_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativexyseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativeopenglrendernode_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativelineseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativesplineseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativeareaseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativescatterseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativepieseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativebarseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativeboxplotseries_p.h"
    "D:/0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativecandlestickseries_p.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/mkspecs/modules" TYPE FILE FILES
    "D:/Exam_Project/qtcharts-build/mkspecs/modules/qt_lib_chartsqml.pri"
    "D:/Exam_Project/qtcharts-build/mkspecs/modules/qt_lib_chartsqml_private.pri"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/lib/pkgconfig/Qt6ChartsQml.pc")
endif()

