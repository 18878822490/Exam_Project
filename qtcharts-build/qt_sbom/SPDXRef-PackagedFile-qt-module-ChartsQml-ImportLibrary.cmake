
        if(NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libQt6ChartsQml.a"
                AND NOT QT_SBOM_BUILD_TIME AND NOT QT_SBOM_FAKE_CHECKSUM)
            if(NOT TRUE)
                message(FATAL_ERROR "Cannot find 'lib/libQt6ChartsQml.a' to compute its checksum. "
                    "Expected to find it at '$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libQt6ChartsQml.a' ")
            endif()
        else()
            if(NOT QT_SBOM_BUILD_TIME)
                if(QT_SBOM_FAKE_CHECKSUM)
                    set(sha1 "158942a783ee1095eafacaffd93de73edeadbeef")
                else()
                    file(SHA1 "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libQt6ChartsQml.a" sha1)
                endif()
                list(APPEND QT_SBOM_VERIFICATION_CODES ${sha1})
            endif()
            file(APPEND "D:/Exam_Project/qtcharts-build/qt_sbom/staging-qtcharts.spdx.in"
"
FileName: ./lib/libQt6ChartsQml.a
SPDXID: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary
FileType: BINARY
FileChecksum: SHA1: ${sha1}
LicenseConcluded: LicenseRef-Qt-Commercial OR GPL-3.0-only
FileCopyrightText: <text>Copyright (C) The Qt Company Ltd. and other contributors.</text>
LicenseInfoInFile: NOASSERTION
Relationship: SPDXRef-Package-qtcharts-qt-module-ChartsQml CONTAINS SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/D:/Exam_Project/qtcharts-build/src/chartsqml2/ChartsQml_resource.rc
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /build_dir/qtcharts/include/QtChartsQml/qtchartsqmlexports.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativeabstractrendernode_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativeaxes.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativeaxes_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativecategoryaxis.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativecategoryaxis_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativechart.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativechart_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativechartglobal_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativechartnode.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativechartnode_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativeforeigntypes_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativemargins.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativemargins_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativepolarchart.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativepolarchart_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativexypoint.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativexypoint_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativexyseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativexyseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /build_dir/qtcharts/src/chartsqml2/chartsqml_qmltyperegistrations.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /build_dir/qtcharts/src/chartsqml2/.qt/rcc/qrc_qmake_QtCharts.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativeopenglrendernode.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativeopenglrendernode_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativelineseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativelineseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativesplineseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativesplineseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativeareaseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativeareaseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativescatterseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativescatterseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativepieseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativepieseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativebarseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativebarseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativeboxplotseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativeboxplotseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativecandlestickseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-ChartsQml-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/declarativecandlestickseries_p.h
"
                )
        endif()
