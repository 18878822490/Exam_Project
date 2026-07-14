
        file(APPEND "D:/Exam_Project/qtcharts-build/qt_sbom/staging-qtcharts.spdx.in"
"
PackageName: Charts
SPDXID: SPDXRef-Package-qtcharts-qt-module-Charts
PackageDownloadLocation: git://code.qt.io/qt/qtcharts.git
PackageVersion: 6.8.3
PackageSupplier: Organization: TheQtCompany
PackageLicenseConcluded: LicenseRef-Qt-Commercial OR GPL-3.0-only
PackageLicenseDeclared: LicenseRef-Qt-Commercial OR GPL-3.0-only
ExternalRef: PACKAGE-MANAGER purl pkg:github/qt/qtcharts?library_name=Charts#src/charts
ExternalRef: PACKAGE-MANAGER purl pkg:generic/TheQtCompany/qtcharts-Charts?vcs_url=https://code.qt.io/qt/qtcharts.git&library_name=Charts#src/charts
FilesAnalyzed: true
PackageCopyrightText: <text>Copyright (C) The Qt Company Ltd. and other contributors.</text>
PrimaryPackagePurpose: LIBRARY
PackageComment: <text>
CMake target name: Charts
CMake exported target name: Qt6::Charts
Contained in CMake package: Qt6Charts
</text>
ExternalRef: SECURITY cpe23Type cpe:2.3:a:qt:qtcharts:6.8.3:*:*:*:*:*:*:*
ExternalRef: SECURITY cpe23Type cpe:2.3:a:qt:qt:6.8.3:*:*:*:*:*:*:*
Relationship: SPDXRef-Package-qtcharts-qt-module-Charts DEPENDS_ON DocumentRef-qtbase:SPDXRef-Package-qtbase-qt-module-Core
Relationship: SPDXRef-Package-qtcharts-qt-module-Charts DEPENDS_ON DocumentRef-qtbase:SPDXRef-Package-qtbase-qt-module-PlatformModuleInternal
Relationship: SPDXRef-Package-qtcharts-qt-module-Charts DEPENDS_ON DocumentRef-qtbase:SPDXRef-Package-qtbase-qt-module-Gui
Relationship: SPDXRef-Package-qtcharts-qt-module-Charts DEPENDS_ON DocumentRef-qtbase:SPDXRef-Package-qtbase-qt-module-Widgets
Relationship: SPDXRef-Package-qtcharts-qt-module-Charts DEPENDS_ON DocumentRef-qtbase:SPDXRef-Package-qtbase-qt-module-OpenGL
Relationship: SPDXRef-Package-qtcharts-qt-module-Charts DEPENDS_ON DocumentRef-qtbase:SPDXRef-Package-qtbase-qt-module-OpenGLWidgets
Relationship: SPDXRef-Package-qtcharts CONTAINS SPDXRef-Package-qtcharts-qt-module-Charts
"
        )
