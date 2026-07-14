
        file(APPEND "D:/Exam_Project/qtcharts-build/qt_sbom/staging-qtcharts.spdx.in"
"
PackageName: ChartsQml
SPDXID: SPDXRef-Package-qtcharts-qt-module-ChartsQml
PackageDownloadLocation: git://code.qt.io/qt/qtcharts.git
PackageVersion: 6.8.3
PackageSupplier: Organization: TheQtCompany
PackageLicenseConcluded: LicenseRef-Qt-Commercial OR GPL-3.0-only
PackageLicenseDeclared: LicenseRef-Qt-Commercial OR GPL-3.0-only
ExternalRef: PACKAGE-MANAGER purl pkg:github/qt/qtcharts?library_name=ChartsQml#src/chartsqml2
ExternalRef: PACKAGE-MANAGER purl pkg:generic/TheQtCompany/qtcharts-ChartsQml?vcs_url=https://code.qt.io/qt/qtcharts.git&library_name=ChartsQml#src/chartsqml2
FilesAnalyzed: true
PackageCopyrightText: <text>Copyright (C) The Qt Company Ltd. and other contributors.</text>
PrimaryPackagePurpose: LIBRARY
PackageComment: <text>
CMake target name: ChartsQml
CMake exported target name: Qt6::ChartsQml
Contained in CMake package: Qt6ChartsQml
</text>
ExternalRef: SECURITY cpe23Type cpe:2.3:a:qt:qtcharts:6.8.3:*:*:*:*:*:*:*
ExternalRef: SECURITY cpe23Type cpe:2.3:a:qt:qt:6.8.3:*:*:*:*:*:*:*
Relationship: SPDXRef-Package-qtcharts-qt-module-ChartsQml DEPENDS_ON DocumentRef-qtbase:SPDXRef-Package-qtbase-qt-module-Core
Relationship: SPDXRef-Package-qtcharts-qt-module-ChartsQml DEPENDS_ON DocumentRef-qtbase:SPDXRef-Package-qtbase-qt-module-PlatformModuleInternal
Relationship: SPDXRef-Package-qtcharts-qt-module-ChartsQml DEPENDS_ON DocumentRef-qtbase:SPDXRef-Package-qtbase-qt-module-Gui
Relationship: SPDXRef-Package-qtcharts-qt-module-ChartsQml DEPENDS_ON DocumentRef-qtdeclarative:SPDXRef-Package-qtdeclarative-qt-module-Qml
Relationship: SPDXRef-Package-qtcharts-qt-module-ChartsQml DEPENDS_ON DocumentRef-qtdeclarative:SPDXRef-Package-qtdeclarative-qt-module-Quick
Relationship: SPDXRef-Package-qtcharts-qt-module-ChartsQml DEPENDS_ON DocumentRef-qtbase:SPDXRef-Package-qtbase-qt-module-OpenGL
Relationship: SPDXRef-Package-qtcharts-qt-module-ChartsQml DEPENDS_ON SPDXRef-Package-qtcharts-qt-module-Charts
Relationship: SPDXRef-Package-qtcharts CONTAINS SPDXRef-Package-qtcharts-qt-module-ChartsQml
"
        )
