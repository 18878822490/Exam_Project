/****************************************************************************
** Meta object code from reading C++ file 'qscatterseries.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/scatterchart/qscatterseries.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qscatterseries.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14QScatterSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN14QScatterSeriesE = QtMocHelpers::stringData(
    "QScatterSeries",
    "colorChanged",
    "",
    "color",
    "borderColorChanged",
    "markerShapeChanged",
    "MarkerShape",
    "shape",
    "markerSizeChanged",
    "size",
    "borderColor",
    "markerShape",
    "markerSize",
    "brush",
    "MarkerShapeCircle",
    "MarkerShapeRectangle",
    "MarkerShapeRotatedRectangle",
    "MarkerShapeTriangle",
    "MarkerShapeStar",
    "MarkerShapePentagon"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN14QScatterSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       5,   50, // properties
       1,   75, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    7 /* Public */,
       4,    1,   41,    2, 0x06,    9 /* Public */,
       5,    1,   44,    2, 0x06,   11 /* Public */,
       8,    1,   47,    2, 0x06,   13 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QReal,    9,

 // properties: name, type, flags, notifyId, revision
       3, QMetaType::QColor, 0x00015103, uint(0), 0,
      10, QMetaType::QColor, 0x00015103, uint(1), 0,
      11, 0x80000000 | 6, 0x0001510b, uint(2), 0,
      12, QMetaType::QReal, 0x00015103, uint(3), 0,
      13, QMetaType::QBrush, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
       6,    6, 0x0,    6,   80,

 // enum data: key, value
      14, uint(QScatterSeries::MarkerShapeCircle),
      15, uint(QScatterSeries::MarkerShapeRectangle),
      16, uint(QScatterSeries::MarkerShapeRotatedRectangle),
      17, uint(QScatterSeries::MarkerShapeTriangle),
      18, uint(QScatterSeries::MarkerShapeStar),
      19, uint(QScatterSeries::MarkerShapePentagon),

       0        // eod
};

Q_CONSTINIT const QMetaObject QScatterSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QXYSeries::staticMetaObject>(),
    qt_meta_stringdata_ZN14QScatterSeriesE.offsetsAndSizes,
    qt_meta_data_ZN14QScatterSeriesE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN14QScatterSeriesE_t,
        // property 'color'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'borderColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'markerShape'
        QtPrivate::TypeAndForceComplete<MarkerShape, std::true_type>,
        // property 'markerSize'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // enum 'MarkerShape'
        QtPrivate::TypeAndForceComplete<QScatterSeries::MarkerShape, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QScatterSeries, std::true_type>,
        // method 'colorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'borderColorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'markerShapeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<MarkerShape, std::false_type>,
        // method 'markerSizeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qreal, std::false_type>
    >,
    nullptr
} };

void QScatterSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QScatterSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->colorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 1: _t->borderColorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 2: _t->markerShapeChanged((*reinterpret_cast< std::add_pointer_t<MarkerShape>>(_a[1]))); break;
        case 3: _t->markerSizeChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QScatterSeries::*)(QColor );
            if (_q_method_type _q_method = &QScatterSeries::colorChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QScatterSeries::*)(QColor );
            if (_q_method_type _q_method = &QScatterSeries::borderColorChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QScatterSeries::*)(MarkerShape );
            if (_q_method_type _q_method = &QScatterSeries::markerShapeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QScatterSeries::*)(qreal );
            if (_q_method_type _q_method = &QScatterSeries::markerSizeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->color(); break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->borderColor(); break;
        case 2: *reinterpret_cast< MarkerShape*>(_v) = _t->markerShape(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = _t->markerSize(); break;
        case 4: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setColor(*reinterpret_cast< QColor*>(_v)); break;
        case 1: _t->setBorderColor(*reinterpret_cast< QColor*>(_v)); break;
        case 2: _t->setMarkerShape(*reinterpret_cast< MarkerShape*>(_v)); break;
        case 3: _t->setMarkerSize(*reinterpret_cast< qreal*>(_v)); break;
        case 4: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QScatterSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QScatterSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN14QScatterSeriesE.stringdata0))
        return static_cast<void*>(this);
    return QXYSeries::qt_metacast(_clname);
}

int QScatterSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QXYSeries::qt_metacall(_c, _id, _a);
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
void QScatterSeries::colorChanged(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QScatterSeries::borderColorChanged(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QScatterSeries::markerShapeChanged(MarkerShape _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QScatterSeries::markerSizeChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
