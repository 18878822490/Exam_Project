/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#if __has_include(<private/declarativeareaseries_p.h>)
#  include <private/declarativeareaseries_p.h>
#endif
#if __has_include(<private/declarativeaxes_p.h>)
#  include <private/declarativeaxes_p.h>
#endif
#if __has_include(<private/declarativebarseries_p.h>)
#  include <private/declarativebarseries_p.h>
#endif
#if __has_include(<private/declarativeboxplotseries_p.h>)
#  include <private/declarativeboxplotseries_p.h>
#endif
#if __has_include(<private/declarativecandlestickseries_p.h>)
#  include <private/declarativecandlestickseries_p.h>
#endif
#if __has_include(<private/declarativecategoryaxis_p.h>)
#  include <private/declarativecategoryaxis_p.h>
#endif
#if __has_include(<private/declarativechart_p.h>)
#  include <private/declarativechart_p.h>
#endif
#if __has_include(<private/declarativeforeigntypes_p.h>)
#  include <private/declarativeforeigntypes_p.h>
#endif
#if __has_include(<private/declarativelineseries_p.h>)
#  include <private/declarativelineseries_p.h>
#endif
#if __has_include(<private/declarativemargins_p.h>)
#  include <private/declarativemargins_p.h>
#endif
#if __has_include(<private/declarativepieseries_p.h>)
#  include <private/declarativepieseries_p.h>
#endif
#if __has_include(<private/declarativepolarchart_p.h>)
#  include <private/declarativepolarchart_p.h>
#endif
#if __has_include(<private/declarativescatterseries_p.h>)
#  include <private/declarativescatterseries_p.h>
#endif
#if __has_include(<private/declarativesplineseries_p.h>)
#  include <private/declarativesplineseries_p.h>
#endif
#if __has_include(<private/declarativexypoint_p.h>)
#  include <private/declarativexypoint_p.h>
#endif


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_QtCharts()
{
    qmlRegisterModule("QtCharts", 1, 0);
    qmlRegisterModule("QtCharts", 1, 254);
    qmlRegisterModule("QtCharts", 2, 0);
    qmlRegisterModule("QtCharts", 2, 254);
    qmlRegisterModule("QtCharts", 6, 0);
    QT_WARNING_PUSH QT_WARNING_DISABLE_DEPRECATED
    qmlRegisterTypesAndRevisions<BarCategoriesAxis>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQAbstractAxis>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQAbstractBarSeries>("QtCharts", 6);
    QMetaType::fromType<QAbstractBarSeries::LabelsPosition>().id();
    qmlRegisterTypesAndRevisions<CppQAbstractSeries>("QtCharts", 6);
    QMetaType::fromType<QAbstractSeries::SeriesType>().id();
    qmlRegisterTypesAndRevisions<CppQBarCategoryAxis>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQBarModelMapper>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQBoxPlotModelMapper>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQBrush>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQCandlestickModelMapper>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQDateTimeAxis>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQHBarModelMapper>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQHBoxPlotModelMapper>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQHCandlestickModelMapper>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQHPieModelMapper>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQHXYModelMapper>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQHashPointConfiguration>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQLegend>("QtCharts", 6);
    QMetaType::fromType<QLegend::MarkerShape>().id();
    qmlRegisterTypesAndRevisions<CppQListBarSet>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQListBoxSet>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQListCandlestickSet>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQListPieSlice>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQLogValueAxis>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQPen>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQPieModelMapper>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQVBarModelMapper>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQVBoxPlotModelMapper>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQVCandlestickModelMapper>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQVPieModelMapper>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQVXYModelMapper>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQXYModelMapper>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<CppQXYSeries>("QtCharts", 6);
    QMetaType::fromType<QXYSeries::PointConfiguration>().id();
    qmlRegisterTypesAndRevisions<DeclarativeAreaSeries>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeAxes>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeBarSeries>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeBarSet>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeBoxPlotSeries>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeBoxSet>("QtCharts", 6);
    QMetaType::fromType<DeclarativeBoxSet::ValuePositions>().id();
    qmlRegisterTypesAndRevisions<DeclarativeCandlestickSeries>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeCandlestickSet>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeCategoryAxis>("QtCharts", 6);
    qmlRegisterAnonymousTypesAndRevisions<QValueAxis>("QtCharts", 6);
    qmlRegisterAnonymousTypesAndRevisions<QAbstractAxis>("QtCharts", 6);
    QMetaType::fromType<DeclarativeCategoryAxis::AxisLabelsPosition>().id();
    qmlRegisterTypesAndRevisions<DeclarativeCategoryRange>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeChart>("QtCharts", 6);
    qmlRegisterAnonymousTypesAndRevisions<QQuickItem>("QtCharts", 6);
    QMetaType::fromType<DeclarativeChart::Theme>().id();
    QMetaType::fromType<DeclarativeChart::Animation>().id();
    QMetaType::fromType<DeclarativeChart::SeriesType>().id();
    qmlRegisterTypesAndRevisions<DeclarativeHorizontalBarSeries>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeHorizontalPercentBarSeries>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeHorizontalStackedBarSeries>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeLineSeries>("QtCharts", 6);
    qmlRegisterAnonymousTypesAndRevisions<QXYSeries>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeMargins>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativePercentBarSeries>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativePieSeries>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativePieSlice>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativePolarChart>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeScatterSeries>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeSplineSeries>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeStackedBarSeries>("QtCharts", 6);
    qmlRegisterTypesAndRevisions<DeclarativeXYPoint>("QtCharts", 6);
    QMetaType::fromType<QAreaSeries *>().id();
    QMetaType::fromType<QBarSeries *>().id();
    QMetaType::fromType<QBarSet *>().id();
    QMetaType::fromType<QBoxPlotSeries *>().id();
    QMetaType::fromType<QBoxSet *>().id();
    QMetaType::fromType<QCandlestickSeries *>().id();
    QMetaType::fromType<QCandlestickSet *>().id();
    QMetaType::fromType<QCategoryAxis *>().id();
    QMetaType::fromType<QCategoryAxis::AxisLabelsPosition>().id();
    QMetaType::fromType<QGraphicsObject *>().id();
    QMetaType::fromType<QGraphicsWidget *>().id();
    QMetaType::fromType<QHorizontalBarSeries *>().id();
    QMetaType::fromType<QHorizontalPercentBarSeries *>().id();
    QMetaType::fromType<QHorizontalStackedBarSeries *>().id();
    QMetaType::fromType<QLineSeries *>().id();
    QMetaType::fromType<QPercentBarSeries *>().id();
    QMetaType::fromType<QPieSeries *>().id();
    QMetaType::fromType<QPieSlice *>().id();
    QMetaType::fromType<QPieSlice::LabelPosition>().id();
    QMetaType::fromType<QScatterSeries *>().id();
    QMetaType::fromType<QScatterSeries::MarkerShape>().id();
    QMetaType::fromType<QSplineSeries *>().id();
    QMetaType::fromType<QStackedBarSeries *>().id();
    qmlRegisterTypesAndRevisions<ValueAxis>("QtCharts", 6);
    QMetaType::fromType<QValueAxis::TickType>().id();
    qmlRegisterTypesAndRevisions<ValuesAxis>("QtCharts", 6);
    QMetaType::fromType<QValueAxis::TickType>().id();
    QT_WARNING_POP
    qmlRegisterModule("QtCharts", 6, 8);
}

static const QQmlModuleRegistration qtChartsRegistration("QtCharts", qml_register_types_QtCharts);
