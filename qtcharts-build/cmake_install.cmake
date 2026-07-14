# Install script for directory: D:/0/Qt/6.8.3/Src/qtcharts

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Exam_Project/qtcharts-build/src/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Charts" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6Charts/Qt6ChartsDependencies.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6ChartsQml" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6ChartsQml/Qt6ChartsQmlDependencies.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6BuildInternals/StandaloneTests" TYPE FILE FILES "D:/Exam_Project/qtcharts-build/lib/cmake/Qt6BuildInternals/StandaloneTests/QtChartsTestsConfig.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE DIRECTORY FILES "D:/Exam_Project/qtcharts-build/lib/" FILES_MATCHING REGEX "/[^/]*\\.prl$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "sbom" OR NOT CMAKE_INSTALL_COMPONENT)
  
        set(QT_SBOM_INSTALLED_ALL_CONFIGS TRUE)
        
        if(QT_SBOM_INSTALLED_ALL_CONFIGS)
            set(QT_SBOM_BUILD_TIME FALSE)
            set(QT_SBOM_OUTPUT_DIR "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/sbom")
            set(QT_SBOM_OUTPUT_PATH "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/sbom/qtcharts-6.8.3.spdx")
            set(QT_SBOM_OUTPUT_PATH_WITHOUT_EXT "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/sbom/qtcharts-6.8.3")
            file(MAKE_DIRECTORY "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/sbom")
            include("D:/Exam_Project/qtcharts-build/qt_sbom/assemble_sbom.cmake")
            
            list(SORT QT_SBOM_VERIFICATION_CODES)
            string(REPLACE ";" "" QT_SBOM_VERIFICATION_CODES "${QT_SBOM_VERIFICATION_CODES}")
            file(WRITE "D:/Exam_Project/qtcharts-build/qt_sbom/verification.txt" "${QT_SBOM_VERIFICATION_CODES}")
            file(SHA1 "D:/Exam_Project/qtcharts-build/qt_sbom/verification.txt" QT_SBOM_VERIFICATION_CODE)
            
            message(STATUS "Finalizing SBOM generation in install dir: ${QT_SBOM_OUTPUT_PATH}")
            configure_file("D:/Exam_Project/qtcharts-build/qt_sbom/staging-qtcharts.spdx.in" "${QT_SBOM_OUTPUT_PATH}")
            
            
            
        else()
            message(STATUS "Skipping SBOM finalization because not all configs were installed.")
        endif()

endif()

if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
  file(WRITE "D:/Exam_Project/qtcharts-build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
