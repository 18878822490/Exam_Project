
        cmake_minimum_required(VERSION 3.16)
        message(STATUS "Starting SBOM generation in build dir: D:/Exam_Project/qtcharts-build/qt_sbom/staging-qtcharts.spdx.in")
        set(QT_SBOM_EXTERNAL_DOC_REFS "")
        file(READ "D:/Exam_Project/qtcharts-build/qt_sbom/SPDXRef-DOCUMENT-qtcharts.spdx.in" content)
        # Override any previous file because we're starting from scratch.
        file(WRITE "D:/Exam_Project/qtcharts-build/qt_sbom/staging-qtcharts.spdx.in" "${content}")
