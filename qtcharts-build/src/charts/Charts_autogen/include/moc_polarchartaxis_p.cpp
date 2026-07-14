/****************************************************************************
** Meta object code from reading C++ file 'polarchartaxis_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/axis/polarchartaxis_p.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'polarchartaxis_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14PolarChartAxisE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN14PolarChartAxisE = QtMocHelpers::stringData(
    "PolarChartAxis",
    "handleShadesBrushChanged",
    "",
    "brush",
    "handleShadesPenChanged",
    "pen"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN14PolarChartAxisE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x0a,    1 /* Public */,
       4,    1,   29,    2, 0x0a,    3 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QBrush,    3,
    QMetaType::Void, QMetaType::QPen,    5,

       0        // eod
};

Q_CONSTINIT const QMetaObject PolarChartAxis::staticMetaObject = { {
    QMetaObject::SuperData::link<ChartAxisElement::staticMetaObject>(),
    qt_meta_stringdata_ZN14PolarChartAxisE.offsetsAndSizes,
    qt_meta_data_ZN14PolarChartAxisE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN14PolarChartAxisE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PolarChartAxis, std::true_type>,
        // method 'handleShadesBrushChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QBrush &, std::false_type>,
        // method 'handleShadesPenChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPen &, std::false_type>
    >,
    nullptr
} };

void PolarChartAxis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PolarChartAxis *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->handleShadesBrushChanged((*reinterpret_cast< std::add_pointer_t<QBrush>>(_a[1]))); break;
        case 1: _t->handleShadesPenChanged((*reinterpret_cast< std::add_pointer_t<QPen>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *PolarChartAxis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PolarChartAxis::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN14PolarChartAxisE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QGraphicsLayoutItem"))
        return static_cast< QGraphicsLayoutItem*>(this);
    return ChartAxisElement::qt_metacast(_clname);
}

int PolarChartAxis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ChartAxisElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
