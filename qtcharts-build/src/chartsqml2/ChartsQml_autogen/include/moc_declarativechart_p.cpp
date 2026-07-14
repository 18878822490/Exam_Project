/****************************************************************************
** Meta object code from reading C++ file 'declarativechart_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativechart_p.h"
#include <QtCharts/qlegend.h>
#include "declarativemargins_p.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'declarativechart_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN16DeclarativeChartE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN16DeclarativeChartE = QtMocHelpers::stringData(
    "DeclarativeChart",
    "QML.Element",
    "ChartView",
    "QML.AddedInVersion",
    "256",
    "QML.ExtraVersion",
    "512",
    "axisLabelsChanged",
    "",
    "titleColorChanged",
    "color",
    "backgroundColorChanged",
    "dropShadowEnabledChanged",
    "enabled",
    "marginsChanged",
    "plotAreaChanged",
    "plotArea",
    "seriesAdded",
    "QAbstractSeries*",
    "series",
    "seriesRemoved",
    "plotAreaColorChanged",
    "backgroundRoundnessChanged",
    "diameter",
    "localizeNumbersChanged",
    "localeChanged",
    "animationDurationChanged",
    "msecs",
    "animationEasingCurveChanged",
    "QEasingCurve",
    "curve",
    "needRender",
    "pendingRenderNodeMouseEventResponses",
    "handleAntialiasingChanged",
    "enable",
    "sceneChanged",
    "QList<QRectF>",
    "region",
    "renderScene",
    "changeMargins",
    "top",
    "bottom",
    "left",
    "right",
    "handleAxisXSet",
    "QAbstractAxis*",
    "axis",
    "handleAxisYSet",
    "handleAxisXTopSet",
    "handleAxisYRightSet",
    "handleSeriesAdded",
    "handlePendingRenderNodeMouseEventResponses",
    "index",
    "seriesName",
    "createSeries",
    "type",
    "name",
    "axisX",
    "axisY",
    "removeSeries",
    "removeAllSeries",
    "setAxisX",
    "setAxisY",
    "zoom",
    "factor",
    "zoomIn",
    "rectangle",
    "zoomOut",
    "zoomReset",
    "isZoomed",
    "scrollLeft",
    "pixels",
    "scrollRight",
    "scrollUp",
    "scrollDown",
    "mapToValue",
    "position",
    "mapToPosition",
    "value",
    "theme",
    "Theme",
    "animationOptions",
    "Animation",
    "animationDuration",
    "animationEasingCurve",
    "title",
    "titleFont",
    "titleColor",
    "legend",
    "QLegend*",
    "count",
    "backgroundColor",
    "dropShadowEnabled",
    "backgroundRoundness",
    "margins",
    "DeclarativeMargins*",
    "plotAreaColor",
    "axes",
    "QQmlListProperty<QAbstractAxis>",
    "localizeNumbers",
    "locale",
    "ChartThemeLight",
    "ChartThemeBlueCerulean",
    "ChartThemeDark",
    "ChartThemeBrownSand",
    "ChartThemeBlueNcs",
    "ChartThemeHighContrast",
    "ChartThemeBlueIcy",
    "ChartThemeQt",
    "NoAnimation",
    "GridAxisAnimations",
    "SeriesAnimations",
    "AllAnimations",
    "SeriesType",
    "SeriesTypeLine",
    "SeriesTypeArea",
    "SeriesTypeBar",
    "SeriesTypeStackedBar",
    "SeriesTypePercentBar",
    "SeriesTypePie",
    "SeriesTypeScatter",
    "SeriesTypeSpline",
    "SeriesTypeHorizontalBar",
    "SeriesTypeHorizontalStackedBar",
    "SeriesTypeHorizontalPercentBar",
    "SeriesTypeBoxPlot",
    "SeriesTypeCandlestick"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN16DeclarativeChartE[] = {

 // content:
      12,       // revision
       0,       // classname
       3,   14, // classinfo
      56,   20, // methods
      18,  572, // properties
       3,  662, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,  412,    8, 0x06,   22 /* Public */,
       9,    1,  413,    8, 0x06,   23 /* Public */,
      11,    0,  416,    8, 0x06,   25 /* Public */,
      12,    1,  417,    8, 0x06,   26 /* Public */,
      14,    0,  420,    8, 0x86,   28 /* Public | MethodRevisioned */,
      15,    1,  421,    8, 0x06,   29 /* Public */,
      17,    1,  424,    8, 0x06,   31 /* Public */,
      20,    1,  427,    8, 0x06,   33 /* Public */,
      21,    0,  430,    8, 0x86,   35 /* Public | MethodRevisioned */,
      22,    1,  431,    8, 0x86,   36 /* Public | MethodRevisioned */,
      24,    0,  434,    8, 0x86,   38 /* Public | MethodRevisioned */,
      25,    0,  435,    8, 0x86,   39 /* Public | MethodRevisioned */,
      26,    1,  436,    8, 0x86,   40 /* Public | MethodRevisioned */,
      28,    1,  439,    8, 0x86,   42 /* Public | MethodRevisioned */,
      31,    0,  442,    8, 0x06,   44 /* Public */,
      32,    0,  443,    8, 0x06,   45 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      33,    1,  444,    8, 0x08,   46 /* Private */,
      35,    1,  447,    8, 0x08,   48 /* Private */,
      38,    0,  450,    8, 0x08,   50 /* Private */,
      39,    4,  451,    8, 0x08,   51 /* Private */,
      44,    1,  460,    8, 0x08,   56 /* Private */,
      47,    1,  463,    8, 0x08,   58 /* Private */,
      48,    1,  466,    8, 0x08,   60 /* Private */,
      49,    1,  469,    8, 0x08,   62 /* Private */,
      50,    1,  472,    8, 0x08,   64 /* Private */,
      51,    0,  475,    8, 0x08,   66 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      19,    1,  476,    8, 0x02,   67 /* Public */,
      19,    1,  479,    8, 0x02,   69 /* Public */,
      54,    4,  482,    8, 0x02,   71 /* Public */,
      54,    3,  491,    8, 0x22,   76 /* Public | MethodCloned */,
      54,    2,  498,    8, 0x22,   80 /* Public | MethodCloned */,
      54,    1,  503,    8, 0x22,   83 /* Public | MethodCloned */,
      59,    1,  506,    8, 0x02,   85 /* Public */,
      60,    0,  509,    8, 0x02,   87 /* Public */,
      61,    2,  510,    8, 0x02,   88 /* Public */,
      61,    1,  515,    8, 0x22,   91 /* Public | MethodCloned */,
      62,    2,  518,    8, 0x02,   93 /* Public */,
      62,    1,  523,    8, 0x22,   96 /* Public | MethodCloned */,
      57,    1,  526,    8, 0x02,   98 /* Public */,
      57,    0,  529,    8, 0x22,  100 /* Public | MethodCloned */,
      58,    1,  530,    8, 0x02,  101 /* Public */,
      58,    0,  533,    8, 0x22,  103 /* Public | MethodCloned */,
      63,    1,  534,    8, 0x02,  104 /* Public */,
      65,    0,  537,    8, 0x82,  106 /* Public | MethodRevisioned */,
      65,    1,  538,    8, 0x82,  107 /* Public | MethodRevisioned */,
      67,    0,  541,    8, 0x82,  109 /* Public | MethodRevisioned */,
      68,    0,  542,    8, 0x82,  110 /* Public | MethodRevisioned */,
      69,    0,  543,    8, 0x82,  111 /* Public | MethodRevisioned */,
      70,    1,  544,    8, 0x02,  112 /* Public */,
      72,    1,  547,    8, 0x02,  114 /* Public */,
      73,    1,  550,    8, 0x02,  116 /* Public */,
      74,    1,  553,    8, 0x02,  118 /* Public */,
      75,    2,  556,    8, 0x82,  120 /* Public | MethodRevisioned */,
      75,    1,  561,    8, 0xa2,  123 /* Public | MethodCloned | MethodRevisioned */,
      77,    2,  564,    8, 0x82,  125 /* Public | MethodRevisioned */,
      77,    1,  569,    8, 0xa2,  128 /* Public | MethodCloned | MethodRevisioned */,

 // signals: revision
       0,
       0,
       0,
       0,
     258,
       0,
       0,
       0,
     259,
     259,
     512,
     512,
     513,
     513,
       0,
       0,

 // slots: revision
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,

 // methods: revision
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
     513,
     513,
     513,
     513,
     513,
       0,
       0,
       0,
       0,
     513,
     513,
     513,
     513,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRectF,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void, 0x80000000 | 29,   30,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   34,
    QMetaType::Void, 0x80000000 | 36,   37,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   40,   41,   42,   43,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,

 // methods: parameters
    0x80000000 | 18, QMetaType::Int,   52,
    0x80000000 | 18, QMetaType::QString,   53,
    0x80000000 | 18, QMetaType::Int, QMetaType::QString, 0x80000000 | 45, 0x80000000 | 45,   55,   56,   57,   58,
    0x80000000 | 18, QMetaType::Int, QMetaType::QString, 0x80000000 | 45,   55,   56,   57,
    0x80000000 | 18, QMetaType::Int, QMetaType::QString,   55,   56,
    0x80000000 | 18, QMetaType::Int,   55,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 45, 0x80000000 | 18,   46,   19,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void, 0x80000000 | 45, 0x80000000 | 18,   46,   19,
    QMetaType::Void, 0x80000000 | 45,   46,
    0x80000000 | 45, 0x80000000 | 18,   19,
    0x80000000 | 45,
    0x80000000 | 45, 0x80000000 | 18,   19,
    0x80000000 | 45,
    QMetaType::Void, QMetaType::QReal,   64,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRectF,   66,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QReal,   71,
    QMetaType::Void, QMetaType::QReal,   71,
    QMetaType::Void, QMetaType::QReal,   71,
    QMetaType::Void, QMetaType::QReal,   71,
    QMetaType::QPointF, QMetaType::QPointF, 0x80000000 | 18,   76,   19,
    QMetaType::QPointF, QMetaType::QPointF,   76,
    QMetaType::QPointF, QMetaType::QPointF, 0x80000000 | 18,   78,   19,
    QMetaType::QPointF, QMetaType::QPointF,   78,

 // properties: name, type, flags, notifyId, revision
      79, 0x80000000 | 80, 0x0001510b, uint(-1), 0,
      81, 0x80000000 | 82, 0x0001510b, uint(-1), 0,
      83, QMetaType::Int, 0x00015103, uint(12), 513,
      84, 0x80000000 | 29, 0x0001510b, uint(13), 513,
      85, QMetaType::QString, 0x00015103, uint(-1), 0,
      86, QMetaType::QFont, 0x00015103, uint(-1), 0,
      87, QMetaType::QColor, 0x00015103, uint(1), 0,
      88, 0x80000000 | 89, 0x00015409, uint(-1), 0,
      90, QMetaType::Int, 0x00015001, uint(-1), 0,
      91, QMetaType::QColor, 0x00015103, uint(2), 0,
      92, QMetaType::Bool, 0x00015103, uint(3), 0,
      93, QMetaType::QReal, 0x00015103, uint(9), 259,
      94, 0x80000000 | 95, 0x00015009, uint(4), 258,
      16, QMetaType::QRectF, 0x00015103, uint(5), 257,
      96, QMetaType::QColor, 0x00015103, uint(8), 259,
      97, 0x80000000 | 98, 0x00015009, uint(-1), 258,
      99, QMetaType::Bool, 0x00015103, uint(10), 512,
     100, QMetaType::QLocale, 0x00015103, uint(11), 512,

 // enums: name, alias, flags, count, data
      80,   80, 0x0,    8,  677,
      82,   82, 0x0,    4,  693,
     113,  113, 0x0,   13,  701,

 // enum data: key, value
     101, uint(DeclarativeChart::ChartThemeLight),
     102, uint(DeclarativeChart::ChartThemeBlueCerulean),
     103, uint(DeclarativeChart::ChartThemeDark),
     104, uint(DeclarativeChart::ChartThemeBrownSand),
     105, uint(DeclarativeChart::ChartThemeBlueNcs),
     106, uint(DeclarativeChart::ChartThemeHighContrast),
     107, uint(DeclarativeChart::ChartThemeBlueIcy),
     108, uint(DeclarativeChart::ChartThemeQt),
     109, uint(DeclarativeChart::NoAnimation),
     110, uint(DeclarativeChart::GridAxisAnimations),
     111, uint(DeclarativeChart::SeriesAnimations),
     112, uint(DeclarativeChart::AllAnimations),
     114, uint(DeclarativeChart::SeriesTypeLine),
     115, uint(DeclarativeChart::SeriesTypeArea),
     116, uint(DeclarativeChart::SeriesTypeBar),
     117, uint(DeclarativeChart::SeriesTypeStackedBar),
     118, uint(DeclarativeChart::SeriesTypePercentBar),
     119, uint(DeclarativeChart::SeriesTypePie),
     120, uint(DeclarativeChart::SeriesTypeScatter),
     121, uint(DeclarativeChart::SeriesTypeSpline),
     122, uint(DeclarativeChart::SeriesTypeHorizontalBar),
     123, uint(DeclarativeChart::SeriesTypeHorizontalStackedBar),
     124, uint(DeclarativeChart::SeriesTypeHorizontalPercentBar),
     125, uint(DeclarativeChart::SeriesTypeBoxPlot),
     126, uint(DeclarativeChart::SeriesTypeCandlestick),

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeChart::staticMetaObject = { {
    QMetaObject::SuperData::link<QQuickItem::staticMetaObject>(),
    qt_meta_stringdata_ZN16DeclarativeChartE.offsetsAndSizes,
    qt_meta_data_ZN16DeclarativeChartE,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'theme'
        Theme,
        // property 'animationOptions'
        Animation,
        // property 'animationDuration'
        int,
        // property 'animationEasingCurve'
        QEasingCurve,
        // property 'title'
        QString,
        // property 'titleFont'
        QFont,
        // property 'titleColor'
        QColor,
        // property 'legend'
        QLegend*,
        // property 'count'
        int,
        // property 'backgroundColor'
        QColor,
        // property 'dropShadowEnabled'
        bool,
        // property 'backgroundRoundness'
        qreal,
        // property 'margins'
        DeclarativeMargins*,
        // property 'plotArea'
        QRectF,
        // property 'plotAreaColor'
        QColor,
        // property 'axes'
        QQmlListProperty<QAbstractAxis>,
        // property 'localizeNumbers'
        bool,
        // property 'locale'
        QLocale,
        // enum 'Theme'
        DeclarativeChart::Theme,
        // enum 'Animation'
        DeclarativeChart::Animation,
        // enum 'SeriesType'
        DeclarativeChart::SeriesType,
        // Q_OBJECT / Q_GADGET
        DeclarativeChart,
        // method 'axisLabelsChanged'
        void,
        // method 'titleColorChanged'
        void,
        QColor,
        // method 'backgroundColorChanged'
        void,
        // method 'dropShadowEnabledChanged'
        void,
        bool,
        // method 'marginsChanged'
        void,
        // method 'plotAreaChanged'
        void,
        QRectF,
        // method 'seriesAdded'
        void,
        QAbstractSeries *,
        // method 'seriesRemoved'
        void,
        QAbstractSeries *,
        // method 'plotAreaColorChanged'
        void,
        // method 'backgroundRoundnessChanged'
        void,
        qreal,
        // method 'localizeNumbersChanged'
        void,
        // method 'localeChanged'
        void,
        // method 'animationDurationChanged'
        void,
        int,
        // method 'animationEasingCurveChanged'
        void,
        QEasingCurve,
        // method 'needRender'
        void,
        // method 'pendingRenderNodeMouseEventResponses'
        void,
        // method 'handleAntialiasingChanged'
        void,
        bool,
        // method 'sceneChanged'
        void,
        const QList<QRectF> &,
        // method 'renderScene'
        void,
        // method 'changeMargins'
        void,
        int,
        int,
        int,
        int,
        // method 'handleAxisXSet'
        void,
        QAbstractAxis *,
        // method 'handleAxisYSet'
        void,
        QAbstractAxis *,
        // method 'handleAxisXTopSet'
        void,
        QAbstractAxis *,
        // method 'handleAxisYRightSet'
        void,
        QAbstractAxis *,
        // method 'handleSeriesAdded'
        void,
        QAbstractSeries *,
        // method 'handlePendingRenderNodeMouseEventResponses'
        void,
        // method 'series'
        QAbstractSeries *,
        int,
        // method 'series'
        QAbstractSeries *,
        QString,
        // method 'createSeries'
        QAbstractSeries *,
        int,
        QString,
        QAbstractAxis *,
        QAbstractAxis *,
        // method 'createSeries'
        QAbstractSeries *,
        int,
        QString,
        QAbstractAxis *,
        // method 'createSeries'
        QAbstractSeries *,
        int,
        QString,
        // method 'createSeries'
        QAbstractSeries *,
        int,
        // method 'removeSeries'
        void,
        QAbstractSeries *,
        // method 'removeAllSeries'
        void,
        // method 'setAxisX'
        void,
        QAbstractAxis *,
        QAbstractSeries *,
        // method 'setAxisX'
        void,
        QAbstractAxis *,
        // method 'setAxisY'
        void,
        QAbstractAxis *,
        QAbstractSeries *,
        // method 'setAxisY'
        void,
        QAbstractAxis *,
        // method 'axisX'
        QAbstractAxis *,
        QAbstractSeries *,
        // method 'axisX'
        QAbstractAxis *,
        // method 'axisY'
        QAbstractAxis *,
        QAbstractSeries *,
        // method 'axisY'
        QAbstractAxis *,
        // method 'zoom'
        void,
        qreal,
        // method 'zoomIn'
        void,
        // method 'zoomIn'
        void,
        const QRectF &,
        // method 'zoomOut'
        void,
        // method 'zoomReset'
        void,
        // method 'isZoomed'
        bool,
        // method 'scrollLeft'
        void,
        qreal,
        // method 'scrollRight'
        void,
        qreal,
        // method 'scrollUp'
        void,
        qreal,
        // method 'scrollDown'
        void,
        qreal,
        // method 'mapToValue'
        QPointF,
        const QPointF &,
        QAbstractSeries *,
        // method 'mapToValue'
        QPointF,
        const QPointF &,
        // method 'mapToPosition'
        QPointF,
        const QPointF &,
        QAbstractSeries *,
        // method 'mapToPosition'
        QPointF,
        const QPointF &
    >,
    nullptr
} };

void DeclarativeChart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeChart *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->axisLabelsChanged(); break;
        case 1: _t->titleColorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 2: _t->backgroundColorChanged(); break;
        case 3: _t->dropShadowEnabledChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->marginsChanged(); break;
        case 5: _t->plotAreaChanged((*reinterpret_cast< std::add_pointer_t<QRectF>>(_a[1]))); break;
        case 6: _t->seriesAdded((*reinterpret_cast< std::add_pointer_t<QAbstractSeries*>>(_a[1]))); break;
        case 7: _t->seriesRemoved((*reinterpret_cast< std::add_pointer_t<QAbstractSeries*>>(_a[1]))); break;
        case 8: _t->plotAreaColorChanged(); break;
        case 9: _t->backgroundRoundnessChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 10: _t->localizeNumbersChanged(); break;
        case 11: _t->localeChanged(); break;
        case 12: _t->animationDurationChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->animationEasingCurveChanged((*reinterpret_cast< std::add_pointer_t<QEasingCurve>>(_a[1]))); break;
        case 14: _t->needRender(); break;
        case 15: _t->pendingRenderNodeMouseEventResponses(); break;
        case 16: _t->handleAntialiasingChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 17: _t->sceneChanged((*reinterpret_cast< std::add_pointer_t<QList<QRectF>>>(_a[1]))); break;
        case 18: _t->renderScene(); break;
        case 19: _t->changeMargins((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        case 20: _t->handleAxisXSet((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 21: _t->handleAxisYSet((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 22: _t->handleAxisXTopSet((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 23: _t->handleAxisYRightSet((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 24: _t->handleSeriesAdded((*reinterpret_cast< std::add_pointer_t<QAbstractSeries*>>(_a[1]))); break;
        case 25: _t->handlePendingRenderNodeMouseEventResponses(); break;
        case 26: { QAbstractSeries* _r = _t->series((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QAbstractSeries**>(_a[0]) = std::move(_r); }  break;
        case 27: { QAbstractSeries* _r = _t->series((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QAbstractSeries**>(_a[0]) = std::move(_r); }  break;
        case 28: { QAbstractSeries* _r = _t->createSeries((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[4])));
            if (_a[0]) *reinterpret_cast< QAbstractSeries**>(_a[0]) = std::move(_r); }  break;
        case 29: { QAbstractSeries* _r = _t->createSeries((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QAbstractSeries**>(_a[0]) = std::move(_r); }  break;
        case 30: { QAbstractSeries* _r = _t->createSeries((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QAbstractSeries**>(_a[0]) = std::move(_r); }  break;
        case 31: { QAbstractSeries* _r = _t->createSeries((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QAbstractSeries**>(_a[0]) = std::move(_r); }  break;
        case 32: _t->removeSeries((*reinterpret_cast< std::add_pointer_t<QAbstractSeries*>>(_a[1]))); break;
        case 33: _t->removeAllSeries(); break;
        case 34: _t->setAxisX((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QAbstractSeries*>>(_a[2]))); break;
        case 35: _t->setAxisX((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 36: _t->setAxisY((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QAbstractSeries*>>(_a[2]))); break;
        case 37: _t->setAxisY((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 38: { QAbstractAxis* _r = _t->axisX((*reinterpret_cast< std::add_pointer_t<QAbstractSeries*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QAbstractAxis**>(_a[0]) = std::move(_r); }  break;
        case 39: { QAbstractAxis* _r = _t->axisX();
            if (_a[0]) *reinterpret_cast< QAbstractAxis**>(_a[0]) = std::move(_r); }  break;
        case 40: { QAbstractAxis* _r = _t->axisY((*reinterpret_cast< std::add_pointer_t<QAbstractSeries*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QAbstractAxis**>(_a[0]) = std::move(_r); }  break;
        case 41: { QAbstractAxis* _r = _t->axisY();
            if (_a[0]) *reinterpret_cast< QAbstractAxis**>(_a[0]) = std::move(_r); }  break;
        case 42: _t->zoom((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 43: _t->zoomIn(); break;
        case 44: _t->zoomIn((*reinterpret_cast< std::add_pointer_t<QRectF>>(_a[1]))); break;
        case 45: _t->zoomOut(); break;
        case 46: _t->zoomReset(); break;
        case 47: { bool _r = _t->isZoomed();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 48: _t->scrollLeft((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 49: _t->scrollRight((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 50: _t->scrollUp((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 51: _t->scrollDown((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 52: { QPointF _r = _t->mapToValue((*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QAbstractSeries*>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QPointF*>(_a[0]) = std::move(_r); }  break;
        case 53: { QPointF _r = _t->mapToValue((*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QPointF*>(_a[0]) = std::move(_r); }  break;
        case 54: { QPointF _r = _t->mapToPosition((*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QAbstractSeries*>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QPointF*>(_a[0]) = std::move(_r); }  break;
        case 55: { QPointF _r = _t->mapToPosition((*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QPointF*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QRectF> >(); break;
            }
            break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 24:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        case 28:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 3:
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 29:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 32:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        case 34:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        case 35:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 36:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        case 37:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 38:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        case 40:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        case 52:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        case 54:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativeChart::*)();
            if (_q_method_type _q_method = &DeclarativeChart::axisLabelsChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeChart::*)(QColor );
            if (_q_method_type _q_method = &DeclarativeChart::titleColorChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeChart::*)();
            if (_q_method_type _q_method = &DeclarativeChart::backgroundColorChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeChart::*)(bool );
            if (_q_method_type _q_method = &DeclarativeChart::dropShadowEnabledChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeChart::*)();
            if (_q_method_type _q_method = &DeclarativeChart::marginsChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeChart::*)(QRectF );
            if (_q_method_type _q_method = &DeclarativeChart::plotAreaChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeChart::*)(QAbstractSeries * );
            if (_q_method_type _q_method = &DeclarativeChart::seriesAdded; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeChart::*)(QAbstractSeries * );
            if (_q_method_type _q_method = &DeclarativeChart::seriesRemoved; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeChart::*)();
            if (_q_method_type _q_method = &DeclarativeChart::plotAreaColorChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeChart::*)(qreal );
            if (_q_method_type _q_method = &DeclarativeChart::backgroundRoundnessChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeChart::*)();
            if (_q_method_type _q_method = &DeclarativeChart::localizeNumbersChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeChart::*)();
            if (_q_method_type _q_method = &DeclarativeChart::localeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeChart::*)(int );
            if (_q_method_type _q_method = &DeclarativeChart::animationDurationChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeChart::*)(QEasingCurve );
            if (_q_method_type _q_method = &DeclarativeChart::animationEasingCurveChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 13;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeChart::*)();
            if (_q_method_type _q_method = &DeclarativeChart::needRender; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 14;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeChart::*)();
            if (_q_method_type _q_method = &DeclarativeChart::pendingRenderNodeMouseEventResponses; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 15;
                return;
            }
        }
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLegend* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Theme*>(_v) = _t->theme(); break;
        case 1: *reinterpret_cast< Animation*>(_v) = _t->animationOptions(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->animationDuration(); break;
        case 3: *reinterpret_cast< QEasingCurve*>(_v) = _t->animationEasingCurve(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->title(); break;
        case 5: *reinterpret_cast< QFont*>(_v) = _t->titleFont(); break;
        case 6: *reinterpret_cast< QColor*>(_v) = _t->titleColor(); break;
        case 7: *reinterpret_cast< QLegend**>(_v) = _t->legend(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->count(); break;
        case 9: *reinterpret_cast< QColor*>(_v) = _t->backgroundColor(); break;
        case 10: *reinterpret_cast< bool*>(_v) = _t->dropShadowEnabled(); break;
        case 11: *reinterpret_cast< qreal*>(_v) = _t->backgroundRoundness(); break;
        case 12: *reinterpret_cast< DeclarativeMargins**>(_v) = _t->margins(); break;
        case 13: *reinterpret_cast< QRectF*>(_v) = _t->plotArea(); break;
        case 14: *reinterpret_cast< QColor*>(_v) = _t->plotAreaColor(); break;
        case 15: *reinterpret_cast< QQmlListProperty<QAbstractAxis>*>(_v) = _t->axes(); break;
        case 16: *reinterpret_cast< bool*>(_v) = _t->localizeNumbers(); break;
        case 17: *reinterpret_cast< QLocale*>(_v) = _t->locale(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTheme(*reinterpret_cast< Theme*>(_v)); break;
        case 1: _t->setAnimationOptions(*reinterpret_cast< Animation*>(_v)); break;
        case 2: _t->setAnimationDuration(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setAnimationEasingCurve(*reinterpret_cast< QEasingCurve*>(_v)); break;
        case 4: _t->setTitle(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setTitleFont(*reinterpret_cast< QFont*>(_v)); break;
        case 6: _t->setTitleColor(*reinterpret_cast< QColor*>(_v)); break;
        case 9: _t->setBackgroundColor(*reinterpret_cast< QColor*>(_v)); break;
        case 10: _t->setDropShadowEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 11: _t->setBackgroundRoundness(*reinterpret_cast< qreal*>(_v)); break;
        case 13: _t->setPlotArea(*reinterpret_cast< QRectF*>(_v)); break;
        case 14: _t->setPlotAreaColor(*reinterpret_cast< QColor*>(_v)); break;
        case 16: _t->setLocalizeNumbers(*reinterpret_cast< bool*>(_v)); break;
        case 17: _t->setLocale(*reinterpret_cast< QLocale*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *DeclarativeChart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeChart::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN16DeclarativeChartE.stringdata0))
        return static_cast<void*>(this);
    return QQuickItem::qt_metacast(_clname);
}

int DeclarativeChart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 56)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 56;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 56)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 56;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void DeclarativeChart::axisLabelsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DeclarativeChart::titleColorChanged(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeclarativeChart::backgroundColorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DeclarativeChart::dropShadowEnabledChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DeclarativeChart::marginsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void DeclarativeChart::plotAreaChanged(QRectF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DeclarativeChart::seriesAdded(QAbstractSeries * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DeclarativeChart::seriesRemoved(QAbstractSeries * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void DeclarativeChart::plotAreaColorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void DeclarativeChart::backgroundRoundnessChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void DeclarativeChart::localizeNumbersChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void DeclarativeChart::localeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void DeclarativeChart::animationDurationChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void DeclarativeChart::animationEasingCurveChanged(QEasingCurve _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void DeclarativeChart::needRender()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void DeclarativeChart::pendingRenderNodeMouseEventResponses()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}
QT_WARNING_POP
