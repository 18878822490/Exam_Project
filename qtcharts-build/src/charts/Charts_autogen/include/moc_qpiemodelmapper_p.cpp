/****************************************************************************
** Meta object code from reading C++ file 'qpiemodelmapper_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/piechart/qpiemodelmapper_p.h"
#include <QtCharts/qpieseries.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qpiemodelmapper_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN22QPieModelMapperPrivateE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN22QPieModelMapperPrivateE = QtMocHelpers::stringData(
    "QPieModelMapperPrivate",
    "modelUpdated",
    "",
    "QModelIndex",
    "topLeft",
    "bottomRight",
    "modelRowsAdded",
    "parent",
    "start",
    "end",
    "modelRowsRemoved",
    "modelColumnsAdded",
    "modelColumnsRemoved",
    "handleModelDestroyed",
    "slicesAdded",
    "QList<QPieSlice*>",
    "slices",
    "slicesRemoved",
    "sliceLabelChanged",
    "sliceValueChanged",
    "handleSeriesDestroyed",
    "initializePieFromModel"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN22QPieModelMapperPrivateE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   86,    2, 0x0a,    1 /* Public */,
       6,    3,   91,    2, 0x0a,    4 /* Public */,
      10,    3,   98,    2, 0x0a,    8 /* Public */,
      11,    3,  105,    2, 0x0a,   12 /* Public */,
      12,    3,  112,    2, 0x0a,   16 /* Public */,
      13,    0,  119,    2, 0x0a,   20 /* Public */,
      14,    1,  120,    2, 0x0a,   21 /* Public */,
      17,    1,  123,    2, 0x0a,   23 /* Public */,
      18,    0,  126,    2, 0x0a,   25 /* Public */,
      19,    0,  127,    2, 0x0a,   26 /* Public */,
      20,    0,  128,    2, 0x0a,   27 /* Public */,
      21,    0,  129,    2, 0x0a,   28 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QPieModelMapperPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN22QPieModelMapperPrivateE.offsetsAndSizes,
    qt_meta_data_ZN22QPieModelMapperPrivateE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN22QPieModelMapperPrivateE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QPieModelMapperPrivate, std::true_type>,
        // method 'modelUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>,
        // method 'modelRowsAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'modelRowsRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'modelColumnsAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'modelColumnsRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handleModelDestroyed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slicesAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QPieSlice*> &, std::false_type>,
        // method 'slicesRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QPieSlice*> &, std::false_type>,
        // method 'sliceLabelChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sliceValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleSeriesDestroyed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'initializePieFromModel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QPieModelMapperPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QPieModelMapperPrivate *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->modelUpdated((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[2]))); break;
        case 1: _t->modelRowsAdded((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 2: _t->modelRowsRemoved((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 3: _t->modelColumnsAdded((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 4: _t->modelColumnsRemoved((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 5: _t->handleModelDestroyed(); break;
        case 6: _t->slicesAdded((*reinterpret_cast< std::add_pointer_t<QList<QPieSlice*>>>(_a[1]))); break;
        case 7: _t->slicesRemoved((*reinterpret_cast< std::add_pointer_t<QList<QPieSlice*>>>(_a[1]))); break;
        case 8: _t->sliceLabelChanged(); break;
        case 9: _t->sliceValueChanged(); break;
        case 10: _t->handleSeriesDestroyed(); break;
        case 11: _t->initializePieFromModel(); break;
        default: ;
        }
    }
}

const QMetaObject *QPieModelMapperPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QPieModelMapperPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN22QPieModelMapperPrivateE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QPieModelMapperPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
