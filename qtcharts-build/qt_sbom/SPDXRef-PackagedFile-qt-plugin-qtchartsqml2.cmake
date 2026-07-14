
        if(NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/qml/QtCharts/qtchartsqml2plugin.dll"
                AND NOT QT_SBOM_BUILD_TIME AND NOT QT_SBOM_FAKE_CHECKSUM)
            if(NOT FALSE)
                message(FATAL_ERROR "Cannot find 'qml/QtCharts/qtchartsqml2plugin.dll' to compute its checksum. "
                    "Expected to find it at '$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/qml/QtCharts/qtchartsqml2plugin.dll' ")
            endif()
        else()
            if(NOT QT_SBOM_BUILD_TIME)
                if(QT_SBOM_FAKE_CHECKSUM)
                    set(sha1 "158942a783ee1095eafacaffd93de73edeadbeef")
                else()
                    file(SHA1 "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/qml/QtCharts/qtchartsqml2plugin.dll" sha1)
                endif()
                list(APPEND QT_SBOM_VERIFICATION_CODES ${sha1})
            endif()
            file(APPEND "D:/Exam_Project/qtcharts-build/qt_sbom/staging-qtcharts.spdx.in"
"
FileName: ./qml/QtCharts/qtchartsqml2plugin.dll
SPDXID: SPDXRef-PackagedFile-qt-plugin-qtchartsqml2
FileType: BINARY
FileChecksum: SHA1: ${sha1}
LicenseConcluded: LicenseRef-Qt-Commercial OR GPL-3.0-only
FileCopyrightText: <text>Copyright (C) The Qt Company Ltd. and other contributors.</text>
LicenseInfoInFile: NOASSERTION
Relationship: SPDXRef-Package-qtcharts-qt-plugin-qtchartsqml2 CONTAINS SPDXRef-PackagedFile-qt-plugin-qtchartsqml2
Relationship: SPDXRef-PackagedFile-qt-plugin-qtchartsqml2 GENERATED_FROM NOASSERTION
RelationshipComment: /build_dir/qtcharts/src/chartsqml2/qtchartsqml2_QtChartsQml2Plugin.cpp
Relationship: SPDXRef-PackagedFile-qt-plugin-qtchartsqml2 GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/chartsqml2/D:/Exam_Project/qtcharts-build/src/chartsqml2/qtchartsqml2_resource.rc
"
                )
        endif()
