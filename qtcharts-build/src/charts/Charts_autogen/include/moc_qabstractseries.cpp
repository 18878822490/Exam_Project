/****************************************************************************
** Meta object code from reading C++ file 'qabstractseries.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/qabstractseries.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qabstractseries.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN15QAbstractSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN15QAbstractSeriesE = QtMocHelpers::stringData(
    "QAbstractSeries",
    "nameChanged",
    "",
    "visibleChanged",
    "opacityChanged",
    "useOpenGLChanged",
    "name",
    "visible",
    "opacity",
    "type",
    "SeriesType",
    "useOpenGL",
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

Q_CONSTINIT static const uint qt_meta_data_ZN15QAbstractSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       5,   42, // properties
       1,   67, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x06,    7 /* Public */,
       3,    0,   39,    2, 0x06,    8 /* Public */,
       4,    0,   40,    2, 0x06,    9 /* Public */,
       5,    0,   41,    2, 0x06,   10 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
       6, QMetaType::QString, 0x00015103, uint(0), 0,
       7, QMetaType::Bool, 0x00015103, uint(1), 0,
       8, QMetaType::QReal, 0x00015103, uint(2), 0,
       9, 0x80000000 | 10, 0x00015009, uint(-1), 0,
      11, QMetaType::Bool, 0x00015103, uint(3), 0,

 // enums: name, alias, flags, count, data
      10,   10, 0x0,   13,   72,

 // enum data: key, value
      12, uint(QAbstractSeries::SeriesTypeLine),
      13, uint(QAbstractSeries::SeriesTypeArea),
      14, uint(QAbstractSeries::SeriesTypeBar),
      15, uint(QAbstractSeries::SeriesTypeStackedBar),
      16, uint(QAbstractSeries::SeriesTypePercentBar),
      17, uint(QAbstractSeries::SeriesTypePie),
      18, uint(QAbstractSeries::SeriesTypeScatter),
      19, uint(QAbstractSeries::SeriesTypeSpline),
      20, uint(QAbstractSeries::SeriesTypeHorizontalBar),
      21, uint(QAbstractSeries::SeriesTypeHorizontalStackedBar),
      22, uint(QAbstractSeries::SeriesTypeHorizontalPercentBar),
      23, uint(QAbstractSeries::SeriesTypeBoxPlot),
      24, uint(QAbstractSeries::SeriesTypeCandlestick),

       0        // eod
};

Q_CONSTINIT const QMetaObject QAbstractSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN15QAbstractSeriesE.offsetsAndSizes,
    qt_meta_data_ZN15QAbstractSeriesE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN15QAbstractSeriesE_t,
        // property 'name'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'visible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'opacity'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'type'
        QtPrivate::TypeAndForceComplete<SeriesType, std::true_type>,
        // property 'useOpenGL'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // enum 'SeriesType'
        QtPrivate::TypeAndForceComplete<QAbstractSeries::SeriesType, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QAbstractSeries, std::true_type>,
        // method 'nameChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'visibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'opacityChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'useOpenGLChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QAbstractSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QAbstractSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->nameChanged(); break;
        case 1: _t->visibleChanged(); break;
        case 2: _t->opacityChanged(); break;
        case 3: _t->useOpenGLChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QAbstractSeries::*)();
            if (_q_method_type _q_method = &QAbstractSeries::nameChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractSeries::*)();
            if (_q_method_type _q_method = &QAbstractSeries::visibleChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractSeries::*)();
            if (_q_method_type _q_method = &QAbstractSeries::opacityChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractSeries::*)();
            if (_q_method_type _q_method = &QAbstractSeries::useOpenGLChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->name(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->isVisible(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = _t->opacity(); break;
        case 3: *reinterpret_cast< SeriesType*>(_v) = _t->type(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->useOpenGL(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setVisible(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setOpacity(*reinterpret_cast< qreal*>(_v)); break;
        case 4: _t->setUseOpenGL(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QAbstractSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QAbstractSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN15QAbstractSeriesE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QAbstractSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QAbstractSeries::nameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QAbstractSeries::visibleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QAbstractSeries::opacityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QAbstractSeries::useOpenGLChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
