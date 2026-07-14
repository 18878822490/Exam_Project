/****************************************************************************
** Meta object code from reading C++ file 'cartesianchartaxis_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/axis/cartesianchartaxis_p.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cartesianchartaxis_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN18CartesianChartAxisE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN18CartesianChartAxisE = QtMocHelpers::stringData(
    "CartesianChartAxis",
    "handleArrowPenChanged",
    "",
    "pen",
    "handleGridPenChanged",
    "handleShadesBrushChanged",
    "brush",
    "handleShadesPenChanged",
    "handleMinorArrowPenChanged",
    "handleMinorGridPenChanged",
    "handleGridLineColorChanged",
    "color",
    "handleMinorGridLineColorChanged"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN18CartesianChartAxisE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x0a,    1 /* Public */,
       4,    1,   65,    2, 0x0a,    3 /* Public */,
       5,    1,   68,    2, 0x0a,    5 /* Public */,
       7,    1,   71,    2, 0x0a,    7 /* Public */,
       8,    1,   74,    2, 0x0a,    9 /* Public */,
       9,    1,   77,    2, 0x0a,   11 /* Public */,
      10,    1,   80,    2, 0x0a,   13 /* Public */,
      12,    1,   83,    2, 0x0a,   15 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QPen,    3,
    QMetaType::Void, QMetaType::QPen,    3,
    QMetaType::Void, QMetaType::QBrush,    6,
    QMetaType::Void, QMetaType::QPen,    3,
    QMetaType::Void, QMetaType::QPen,    3,
    QMetaType::Void, QMetaType::QPen,    3,
    QMetaType::Void, QMetaType::QColor,   11,
    QMetaType::Void, QMetaType::QColor,   11,

       0        // eod
};

Q_CONSTINIT const QMetaObject CartesianChartAxis::staticMetaObject = { {
    QMetaObject::SuperData::link<ChartAxisElement::staticMetaObject>(),
    qt_meta_stringdata_ZN18CartesianChartAxisE.offsetsAndSizes,
    qt_meta_data_ZN18CartesianChartAxisE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN18CartesianChartAxisE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CartesianChartAxis, std::true_type>,
        // method 'handleArrowPenChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPen &, std::false_type>,
        // method 'handleGridPenChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPen &, std::false_type>,
        // method 'handleShadesBrushChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QBrush &, std::false_type>,
        // method 'handleShadesPenChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPen &, std::false_type>,
        // method 'handleMinorArrowPenChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPen &, std::false_type>,
        // method 'handleMinorGridPenChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPen &, std::false_type>,
        // method 'handleGridLineColorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QColor &, std::false_type>,
        // method 'handleMinorGridLineColorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QColor &, std::false_type>
    >,
    nullptr
} };

void CartesianChartAxis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CartesianChartAxis *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->handleArrowPenChanged((*reinterpret_cast< std::add_pointer_t<QPen>>(_a[1]))); break;
        case 1: _t->handleGridPenChanged((*reinterpret_cast< std::add_pointer_t<QPen>>(_a[1]))); break;
        case 2: _t->handleShadesBrushChanged((*reinterpret_cast< std::add_pointer_t<QBrush>>(_a[1]))); break;
        case 3: _t->handleShadesPenChanged((*reinterpret_cast< std::add_pointer_t<QPen>>(_a[1]))); break;
        case 4: _t->handleMinorArrowPenChanged((*reinterpret_cast< std::add_pointer_t<QPen>>(_a[1]))); break;
        case 5: _t->handleMinorGridPenChanged((*reinterpret_cast< std::add_pointer_t<QPen>>(_a[1]))); break;
        case 6: _t->handleGridLineColorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 7: _t->handleMinorGridLineColorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *CartesianChartAxis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CartesianChartAxis::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN18CartesianChartAxisE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QGraphicsLayoutItem"))
        return static_cast< QGraphicsLayoutItem*>(this);
    return ChartAxisElement::qt_metacast(_clname);
}

int CartesianChartAxis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ChartAxisElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
