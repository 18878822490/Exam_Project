
        file(APPEND "D:/Exam_Project/qtcharts-build/qt_sbom/staging-qtcharts.spdx.in"
"
PackageName: qtchartsqml2
SPDXID: SPDXRef-Package-qtcharts-qt-plugin-qtchartsqml2
PackageDownloadLocation: git://code.qt.io/qt/qtcharts.git
PackageVersion: 6.8.3
PackageSupplier: Organization: TheQtCompany
PackageLicenseConcluded: LicenseRef-Qt-Commercial OR GPL-3.0-only
PackageLicenseDeclared: LicenseRef-Qt-Commercial OR GPL-3.0-only
ExternalRef: PACKAGE-MANAGER purl pkg:github/qt/qtcharts?library_name=qtchartsqml2#src/chartsqml2
ExternalRef: PACKAGE-MANAGER purl pkg:generic/TheQtCompany/qtcharts-qtchartsqml2?vcs_url=https://code.qt.io/qt/qtcharts.git&library_name=qtchartsqml2#src/chartsqml2
FilesAnalyzed: true
PackageCopyrightText: <text>Copyright (C) The Qt Company Ltd. and other contributors.</text>
PrimaryPackagePurpose: LIBRARY
PackageComment: <text>
CMake target name: qtchartsqml2
</text>
ExternalRef: SECURITY cpe23Type cpe:2.3:a:qt:qtcharts:6.8.3:*:*:*:*:*:*:*
ExternalRef: SECURITY cpe23Type cpe:2.3:a:qt:qt:6.8.3:*:*:*:*:*:*:*
Relationship: SPDXRef-Package-qtcharts-qt-plugin-qtchartsqml2 DEPENDS_ON DocumentRef-qtbase:SPDXRef-Package-qtbase-qt-module-PlatformPluginInternal
Relationship: SPDXRef-Package-qtcharts-qt-plugin-qtchartsqml2 DEPENDS_ON DocumentRef-qtdeclarative:SPDXRef-Package-qtdeclarative-qt-module-Qml
Relationship: SPDXRef-Package-qtcharts-qt-plugin-qtchartsqml2 DEPENDS_ON SPDXRef-Package-qtcharts-qt-module-ChartsQml
Relationship: SPDXRef-Package-qtcharts CONTAINS SPDXRef-Package-qtcharts-qt-plugin-qtchartsqml2
"
        )
