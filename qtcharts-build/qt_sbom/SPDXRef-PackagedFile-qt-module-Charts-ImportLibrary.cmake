
        if(NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libQt6Charts.a"
                AND NOT QT_SBOM_BUILD_TIME AND NOT QT_SBOM_FAKE_CHECKSUM)
            if(NOT TRUE)
                message(FATAL_ERROR "Cannot find 'lib/libQt6Charts.a' to compute its checksum. "
                    "Expected to find it at '$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libQt6Charts.a' ")
            endif()
        else()
            if(NOT QT_SBOM_BUILD_TIME)
                if(QT_SBOM_FAKE_CHECKSUM)
                    set(sha1 "158942a783ee1095eafacaffd93de73edeadbeef")
                else()
                    file(SHA1 "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libQt6Charts.a" sha1)
                endif()
                list(APPEND QT_SBOM_VERIFICATION_CODES ${sha1})
            endif()
            file(APPEND "D:/Exam_Project/qtcharts-build/qt_sbom/staging-qtcharts.spdx.in"
"
FileName: ./lib/libQt6Charts.a
SPDXID: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary
FileType: BINARY
FileChecksum: SHA1: ${sha1}
LicenseConcluded: LicenseRef-Qt-Commercial OR GPL-3.0-only
FileCopyrightText: <text>Copyright (C) The Qt Company Ltd. and other contributors.</text>
LicenseInfoInFile: NOASSERTION
Relationship: SPDXRef-Package-qtcharts-qt-module-Charts CONTAINS SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/D:/Exam_Project/qtcharts-build/src/charts/Charts_resource.rc
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /build_dir/qtcharts/include/QtCharts/qtchartsexports.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/axisanimation.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/axisanimation_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/chartanimation.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/chartanimation_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/xyanimation.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/xyanimation_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/barcategoryaxis/chartbarcategoryaxisx.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/barcategoryaxis/chartbarcategoryaxisx_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/barcategoryaxis/chartbarcategoryaxisy.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/barcategoryaxis/chartbarcategoryaxisy_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/barcategoryaxis/qbarcategoryaxis.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/barcategoryaxis/qbarcategoryaxis.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/barcategoryaxis/qbarcategoryaxis_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/cartesianchartaxis.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/cartesianchartaxis_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/categoryaxis/chartcategoryaxisx.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/categoryaxis/chartcategoryaxisx_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/categoryaxis/chartcategoryaxisy.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/categoryaxis/chartcategoryaxisy_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/categoryaxis/polarchartcategoryaxisangular.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/categoryaxis/polarchartcategoryaxisangular_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/categoryaxis/polarchartcategoryaxisradial.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/categoryaxis/polarchartcategoryaxisradial_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/categoryaxis/qcategoryaxis.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/categoryaxis/qcategoryaxis.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/categoryaxis/qcategoryaxis_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/coloraxis/qcoloraxis.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/coloraxis/qcoloraxis.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/coloraxis/qcoloraxis_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/coloraxis/chartcoloraxisy.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/coloraxis/chartcoloraxisy_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/coloraxis/chartcoloraxisx.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/coloraxis/chartcoloraxisx_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/chartaxiselement.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/chartaxiselement_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/editableaxislabel.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/editableaxislabel_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/horizontalaxis.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/horizontalaxis_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/linearrowitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/logvalueaxis/chartlogvalueaxisx.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/logvalueaxis/chartlogvalueaxisx_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/logvalueaxis/chartlogvalueaxisy.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/logvalueaxis/chartlogvalueaxisy_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/logvalueaxis/polarchartlogvalueaxisangular.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/logvalueaxis/polarchartlogvalueaxisangular_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/logvalueaxis/polarchartlogvalueaxisradial.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/logvalueaxis/polarchartlogvalueaxisradial_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/logvalueaxis/qlogvalueaxis.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/logvalueaxis/qlogvalueaxis.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/logvalueaxis/qlogvalueaxis_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/polarchartaxis.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/polarchartaxis_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/polarchartaxisangular.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/polarchartaxisangular_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/polarchartaxisradial.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/polarchartaxisradial_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/qabstractaxis.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/qabstractaxis.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/qabstractaxis_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/valueaxis/chartvalueaxisx.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/valueaxis/chartvalueaxisx_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/valueaxis/chartvalueaxisy.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/valueaxis/chartvalueaxisy_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/valueaxis/polarchartvalueaxisangular.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/valueaxis/polarchartvalueaxisangular_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/valueaxis/polarchartvalueaxisradial.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/valueaxis/polarchartvalueaxisradial_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/valueaxis/qvalueaxis.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/valueaxis/qvalueaxis.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/valueaxis/qvalueaxis_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/valueaxis/valueaxislabel.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/valueaxis/valueaxislabel_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/verticalaxis.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/verticalaxis_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/chartbackground.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/chartbackground_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/chartconfig_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/chartdataset.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/chartdataset_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/chartelement.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/chartelement_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/charthelpers_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/chartitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/chartitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/chartpresenter.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/chartpresenter_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/chartthememanager.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/chartthememanager_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/charttitle.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/charttitle_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/abstractdomain.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/abstractdomain_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/logxlogydomain.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/logxlogydomain_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/logxlogypolardomain.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/logxlogypolardomain_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/logxydomain.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/logxydomain_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/logxypolardomain.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/logxypolardomain_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/polardomain.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/polardomain_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/xlogydomain.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/xlogydomain_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/xlogypolardomain.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/xlogypolardomain_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/xydomain.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/xydomain_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/xypolardomain.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/domain/xypolardomain_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/layout/abstractchartlayout.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/layout/abstractchartlayout_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/layout/cartesianchartlayout.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/layout/cartesianchartlayout_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/layout/polarchartlayout.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/layout/polarchartlayout_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/legendlayout.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/legendlayout_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/legendmarkeritem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/legendmarkeritem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/legendscroller.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/legendscroller_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/legendmoveresizehandler.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/legendmoveresizehandler_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qlegend.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qlegend.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qlegend_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qlegendmarker.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qlegendmarker.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qlegendmarker_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qxylegendmarker.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qxylegendmarker.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qxylegendmarker_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/qabstractseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/qabstractseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/qabstractseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/qchart.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/qchart.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/qchart_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/qchartglobal.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/qchartglobal_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/qchartview.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/qchartview.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/qchartview_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/qpolarchart.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/qpolarchart.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/scroller.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/scroller_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/themes/charttheme_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/themes/chartthemebluecerulean_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/themes/chartthemeblueicy_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/themes/chartthemebluencs_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/themes/chartthemebrownsand_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/themes/chartthemedark_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/themes/chartthemehighcontrast_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/themes/chartthemelight_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/themes/chartthemeqt_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/themes/chartthemesystem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/xychart/glxyseriesdata.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/xychart/glxyseriesdata_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/xychart/qhxymodelmapper.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/xychart/qhxymodelmapper.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/xychart/qvxymodelmapper.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/xychart/qvxymodelmapper.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/xychart/qxymodelmapper.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/xychart/qxymodelmapper.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/xychart/qxymodelmapper_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/xychart/qxyseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/xychart/qxyseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/xychart/qxyseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/xychart/xychart.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/xychart/xychart_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /build_dir/qtcharts/src/charts/qtcharts-config.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /build_dir/qtcharts/src/charts/qtcharts-config_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/glwidget.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/glwidget_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/areachart/areachartitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/areachart/areachartitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/areachart/qareaseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/areachart/qareaseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/areachart/qareaseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qarealegendmarker.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qarealegendmarker.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qarealegendmarker_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/baranimation.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/baranimation_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/abstractbarchartitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/abstractbarchartitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/bar.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/bar_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/horizontal/bar/horizontalbarchartitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/horizontal/bar/horizontalbarchartitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/horizontal/bar/qhorizontalbarseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/horizontal/bar/qhorizontalbarseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/horizontal/bar/qhorizontalbarseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/horizontal/percent/horizontalpercentbarchartitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/horizontal/percent/horizontalpercentbarchartitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/horizontal/percent/qhorizontalpercentbarseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/horizontal/percent/qhorizontalpercentbarseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/horizontal/percent/qhorizontalpercentbarseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/horizontal/stacked/horizontalstackedbarchartitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/horizontal/stacked/horizontalstackedbarchartitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/horizontal/stacked/qhorizontalstackedbarseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/horizontal/stacked/qhorizontalstackedbarseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/horizontal/stacked/qhorizontalstackedbarseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/qabstractbarseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/qabstractbarseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/qabstractbarseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/qbarmodelmapper.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/qbarmodelmapper.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/qbarmodelmapper_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/qbarset.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/qbarset.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/qbarset_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/qhbarmodelmapper.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/qhbarmodelmapper.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/qvbarmodelmapper.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/qvbarmodelmapper.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/vertical/bar/barchartitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/vertical/bar/barchartitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/vertical/bar/qbarseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/vertical/bar/qbarseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/vertical/bar/qbarseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/vertical/percent/percentbarchartitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/vertical/percent/percentbarchartitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/vertical/percent/qpercentbarseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/vertical/percent/qpercentbarseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/vertical/percent/qpercentbarseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/vertical/stacked/qstackedbarseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/vertical/stacked/qstackedbarseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/vertical/stacked/qstackedbarseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/vertical/stacked/stackedbarchartitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/barchart/vertical/stacked/stackedbarchartitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qbarlegendmarker.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qbarlegendmarker.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qbarlegendmarker_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/linechart/linechartitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/linechart/linechartitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/linechart/qlineseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/linechart/qlineseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/linechart/qlineseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/pieanimation.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/pieanimation_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/piesliceanimation.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/piesliceanimation_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qpielegendmarker.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qpielegendmarker.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qpielegendmarker_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/piechartitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/piechartitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/pieslicedata_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/piesliceitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/piesliceitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/qhpiemodelmapper.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/qhpiemodelmapper.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/qpiemodelmapper.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/qpiemodelmapper.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/qpiemodelmapper_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/qpieseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/qpieseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/qpieseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/qpieslice.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/qpieslice.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/qpieslice_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/qvpiemodelmapper.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/piechart/qvpiemodelmapper.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/scatteranimation.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/scatteranimation_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/scatterchart/qscatterseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/scatterchart/qscatterseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/scatterchart/qscatterseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/scatterchart/scatterchartitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/scatterchart/scatterchartitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/splineanimation.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/splineanimation_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/splinechart/qsplineseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/splinechart/qsplineseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/splinechart/qsplineseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/splinechart/splinechartitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/splinechart/splinechartitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/boxplotanimation.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/boxplotanimation_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/boxwhiskersanimation.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/boxwhiskersanimation_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/boxplotchartitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/boxplotchartitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/boxwhiskers.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/boxwhiskers_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/boxwhiskersdata_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/qboxplotmodelmapper.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/qboxplotmodelmapper.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/qboxplotmodelmapper_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/qboxplotseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/qboxplotseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/qboxplotseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/qboxset.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/qboxset.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/qboxset_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/qhboxplotmodelmapper.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/qhboxplotmodelmapper.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/qvboxplotmodelmapper.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/boxplotchart/qvboxplotmodelmapper.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qboxplotlegendmarker.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qboxplotlegendmarker.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qboxplotlegendmarker_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/candlestickanimation.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/candlestickanimation_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/candlestickbodywicksanimation.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/animations/candlestickbodywicksanimation_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/candlestick.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/candlestick_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/candlestickchartitem.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/candlestickchartitem_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/candlestickdata_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/qcandlestickmodelmapper.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/qcandlestickmodelmapper.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/qcandlestickmodelmapper_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/qcandlestickseries.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/qcandlestickseries.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/qcandlestickseries_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/qcandlestickset.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/qcandlestickset.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/qcandlestickset_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/qhcandlestickmodelmapper.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/qhcandlestickmodelmapper.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/qvcandlestickmodelmapper.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/candlestickchart/qvcandlestickmodelmapper.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qcandlesticklegendmarker.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qcandlesticklegendmarker.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/legend/qcandlesticklegendmarker_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/datetimeaxis/chartdatetimeaxisx.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/datetimeaxis/chartdatetimeaxisx_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/datetimeaxis/chartdatetimeaxisy.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/datetimeaxis/chartdatetimeaxisy_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/datetimeaxis/datetimeaxislabel.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/datetimeaxis/datetimeaxislabel_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/datetimeaxis/polarchartdatetimeaxisangular.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/datetimeaxis/polarchartdatetimeaxisangular_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/datetimeaxis/polarchartdatetimeaxisradial.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/datetimeaxis/polarchartdatetimeaxisradial_p.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/datetimeaxis/qdatetimeaxis.cpp
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/datetimeaxis/qdatetimeaxis.h
Relationship: SPDXRef-PackagedFile-qt-module-Charts-ImportLibrary GENERATED_FROM NOASSERTION
RelationshipComment: /src_dir/qtcharts/src/charts/axis/datetimeaxis/qdatetimeaxis_p.h
"
                )
        endif()
