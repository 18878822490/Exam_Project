/****************************************************************************
** Meta object code from reading C++ file 'qchart.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/qchart.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qchart.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN6QChartE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN6QChartE = QtMocHelpers::stringData(
    "QChart",
    "plotAreaChanged",
    "",
    "plotArea",
    "theme",
    "QChart::ChartTheme",
    "title",
    "backgroundVisible",
    "dropShadowEnabled",
    "backgroundRoundness",
    "animationOptions",
    "QChart::AnimationOptions",
    "animationDuration",
    "animationEasingCurve",
    "QEasingCurve",
    "margins",
    "QMargins",
    "chartType",
    "QChart::ChartType",
    "plotAreaBackgroundVisible",
    "localizeNumbers",
    "locale",
    "ChartType",
    "ChartTypeUndefined",
    "ChartTypeCartesian",
    "ChartTypePolar",
    "ChartTheme",
    "ChartThemeLight",
    "ChartThemeBlueCerulean",
    "ChartThemeDark",
    "ChartThemeBrownSand",
    "ChartThemeBlueNcs",
    "ChartThemeHighContrast",
    "ChartThemeBlueIcy",
    "ChartThemeQt",
    "AnimationOption",
    "NoAnimation",
    "GridAxisAnimations",
    "SeriesAnimations",
    "AllAnimations"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN6QChartE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
      14,   23, // properties
       3,   93, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x06,   18 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QRectF,    3,

 // properties: name, type, flags, notifyId, revision
       4, 0x80000000 | 5, 0x0001510b, uint(-1), 0,
       6, QMetaType::QString, 0x00015103, uint(-1), 0,
       7, QMetaType::Bool, 0x00015103, uint(-1), 0,
       8, QMetaType::Bool, 0x00015103, uint(-1), 0,
       9, QMetaType::QReal, 0x00015103, uint(-1), 0,
      10, 0x80000000 | 11, 0x0001510b, uint(-1), 0,
      12, QMetaType::Int, 0x00015103, uint(-1), 0,
      13, 0x80000000 | 14, 0x0001510b, uint(-1), 0,
      15, 0x80000000 | 16, 0x0001510b, uint(-1), 0,
      17, 0x80000000 | 18, 0x00015009, uint(-1), 0,
      19, QMetaType::Bool, 0x00015103, uint(-1), 0,
      20, QMetaType::Bool, 0x00015103, uint(-1), 0,
      21, QMetaType::QLocale, 0x00015103, uint(-1), 0,
       3, QMetaType::QRectF, 0x00015103, uint(0), 0,

 // enums: name, alias, flags, count, data
      22,   22, 0x0,    3,  108,
      26,   26, 0x0,    8,  114,
      35,   35, 0x0,    4,  130,

 // enum data: key, value
      23, uint(QChart::ChartTypeUndefined),
      24, uint(QChart::ChartTypeCartesian),
      25, uint(QChart::ChartTypePolar),
      27, uint(QChart::ChartThemeLight),
      28, uint(QChart::ChartThemeBlueCerulean),
      29, uint(QChart::ChartThemeDark),
      30, uint(QChart::ChartThemeBrownSand),
      31, uint(QChart::ChartThemeBlueNcs),
      32, uint(QChart::ChartThemeHighContrast),
      33, uint(QChart::ChartThemeBlueIcy),
      34, uint(QChart::ChartThemeQt),
      36, uint(QChart::NoAnimation),
      37, uint(QChart::GridAxisAnimations),
      38, uint(QChart::SeriesAnimations),
      39, uint(QChart::AllAnimations),

       0        // eod
};

Q_CONSTINIT const QMetaObject QChart::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsWidget::staticMetaObject>(),
    qt_meta_stringdata_ZN6QChartE.offsetsAndSizes,
    qt_meta_data_ZN6QChartE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN6QChartE_t,
        // property 'theme'
        QtPrivate::TypeAndForceComplete<QChart::ChartTheme, std::true_type>,
        // property 'title'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'backgroundVisible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'dropShadowEnabled'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'backgroundRoundness'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'animationOptions'
        QtPrivate::TypeAndForceComplete<QChart::AnimationOptions, std::true_type>,
        // property 'animationDuration'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'animationEasingCurve'
        QtPrivate::TypeAndForceComplete<QEasingCurve, std::true_type>,
        // property 'margins'
        QtPrivate::TypeAndForceComplete<QMargins, std::true_type>,
        // property 'chartType'
        QtPrivate::TypeAndForceComplete<QChart::ChartType, std::true_type>,
        // property 'plotAreaBackgroundVisible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'localizeNumbers'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'locale'
        QtPrivate::TypeAndForceComplete<QLocale, std::true_type>,
        // property 'plotArea'
        QtPrivate::TypeAndForceComplete<QRectF, std::true_type>,
        // enum 'ChartType'
        QtPrivate::TypeAndForceComplete<QChart::ChartType, std::true_type>,
        // enum 'ChartTheme'
        QtPrivate::TypeAndForceComplete<QChart::ChartTheme, std::true_type>,
        // enum 'AnimationOption'
        QtPrivate::TypeAndForceComplete<QChart::AnimationOption, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QChart, std::true_type>,
        // method 'plotAreaChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QRectF &, std::false_type>
    >,
    nullptr
} };

void QChart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QChart *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->plotAreaChanged((*reinterpret_cast< std::add_pointer_t<QRectF>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QChart::*)(const QRectF & );
            if (_q_method_type _q_method = &QChart::plotAreaChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QChart::ChartTheme*>(_v) = _t->theme(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->title(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isBackgroundVisible(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->isDropShadowEnabled(); break;
        case 4: *reinterpret_cast< qreal*>(_v) = _t->backgroundRoundness(); break;
        case 5: *reinterpret_cast< QChart::AnimationOptions*>(_v) = _t->animationOptions(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->animationDuration(); break;
        case 7: *reinterpret_cast< QEasingCurve*>(_v) = _t->animationEasingCurve(); break;
        case 8: *reinterpret_cast< QMargins*>(_v) = _t->margins(); break;
        case 9: *reinterpret_cast< QChart::ChartType*>(_v) = _t->chartType(); break;
        case 10: *reinterpret_cast< bool*>(_v) = _t->isPlotAreaBackgroundVisible(); break;
        case 11: *reinterpret_cast< bool*>(_v) = _t->localizeNumbers(); break;
        case 12: *reinterpret_cast< QLocale*>(_v) = _t->locale(); break;
        case 13: *reinterpret_cast< QRectF*>(_v) = _t->plotArea(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTheme(*reinterpret_cast< QChart::ChartTheme*>(_v)); break;
        case 1: _t->setTitle(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setBackgroundVisible(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setDropShadowEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setBackgroundRoundness(*reinterpret_cast< qreal*>(_v)); break;
        case 5: _t->setAnimationOptions(*reinterpret_cast< QChart::AnimationOptions*>(_v)); break;
        case 6: _t->setAnimationDuration(*reinterpret_cast< int*>(_v)); break;
        case 7: _t->setAnimationEasingCurve(*reinterpret_cast< QEasingCurve*>(_v)); break;
        case 8: _t->setMargins(*reinterpret_cast< QMargins*>(_v)); break;
        case 10: _t->setPlotAreaBackgroundVisible(*reinterpret_cast< bool*>(_v)); break;
        case 11: _t->setLocalizeNumbers(*reinterpret_cast< bool*>(_v)); break;
        case 12: _t->setLocale(*reinterpret_cast< QLocale*>(_v)); break;
        case 13: _t->setPlotArea(*reinterpret_cast< QRectF*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QChart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QChart::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN6QChartE.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsWidget::qt_metacast(_clname);
}

int QChart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void QChart::plotAreaChanged(const QRectF & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
