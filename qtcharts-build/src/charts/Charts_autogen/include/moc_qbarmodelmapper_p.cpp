/****************************************************************************
** Meta object code from reading C++ file 'qbarmodelmapper_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/qbarmodelmapper_p.h"
#include <QtCharts/qabstractbarseries.h>
#include <QtCharts/qvbarmodelmapper.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qbarmodelmapper_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN22QBarModelMapperPrivateE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN22QBarModelMapperPrivateE = QtMocHelpers::stringData(
    "QBarModelMapperPrivate",
    "modelUpdated",
    "",
    "QModelIndex",
    "topLeft",
    "bottomRight",
    "modelHeaderDataUpdated",
    "Qt::Orientation",
    "orientation",
    "first",
    "last",
    "modelRowsAdded",
    "parent",
    "start",
    "end",
    "modelRowsRemoved",
    "modelColumnsAdded",
    "modelColumnsRemoved",
    "handleModelDestroyed",
    "barSetsAdded",
    "QList<QBarSet*>",
    "sets",
    "barSetsRemoved",
    "valuesAdded",
    "index",
    "count",
    "valuesRemoved",
    "barLabelChanged",
    "barValueChanged",
    "handleSeriesDestroyed",
    "initializeBarFromModel"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN22QBarModelMapperPrivateE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  104,    2, 0x0a,    1 /* Public */,
       6,    3,  109,    2, 0x0a,    4 /* Public */,
      11,    3,  116,    2, 0x0a,    8 /* Public */,
      15,    3,  123,    2, 0x0a,   12 /* Public */,
      16,    3,  130,    2, 0x0a,   16 /* Public */,
      17,    3,  137,    2, 0x0a,   20 /* Public */,
      18,    0,  144,    2, 0x0a,   24 /* Public */,
      19,    1,  145,    2, 0x0a,   25 /* Public */,
      22,    1,  148,    2, 0x0a,   27 /* Public */,
      23,    2,  151,    2, 0x0a,   29 /* Public */,
      26,    2,  156,    2, 0x0a,   32 /* Public */,
      27,    0,  161,    2, 0x0a,   35 /* Public */,
      28,    1,  162,    2, 0x0a,   36 /* Public */,
      29,    0,  165,    2, 0x0a,   38 /* Public */,
      30,    0,  166,    2, 0x0a,   39 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int, QMetaType::Int,    8,    9,   10,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,   12,   13,   14,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,   12,   13,   14,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,   12,   13,   14,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,   12,   13,   14,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   24,   25,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   24,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QBarModelMapperPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN22QBarModelMapperPrivateE.offsetsAndSizes,
    qt_meta_data_ZN22QBarModelMapperPrivateE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN22QBarModelMapperPrivateE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QBarModelMapperPrivate, std::true_type>,
        // method 'modelUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>,
        // method 'modelHeaderDataUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Qt::Orientation, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
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
        // method 'barSetsAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QBarSet*> &, std::false_type>,
        // method 'barSetsRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QBarSet*> &, std::false_type>,
        // method 'valuesAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'valuesRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'barLabelChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'barValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handleSeriesDestroyed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'initializeBarFromModel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QBarModelMapperPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QBarModelMapperPrivate *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->modelUpdated((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[2]))); break;
        case 1: _t->modelHeaderDataUpdated((*reinterpret_cast< std::add_pointer_t<Qt::Orientation>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 2: _t->modelRowsAdded((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 3: _t->modelRowsRemoved((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 4: _t->modelColumnsAdded((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 5: _t->modelColumnsRemoved((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 6: _t->handleModelDestroyed(); break;
        case 7: _t->barSetsAdded((*reinterpret_cast< std::add_pointer_t<QList<QBarSet*>>>(_a[1]))); break;
        case 8: _t->barSetsRemoved((*reinterpret_cast< std::add_pointer_t<QList<QBarSet*>>>(_a[1]))); break;
        case 9: _t->valuesAdded((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 10: _t->valuesRemoved((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 11: _t->barLabelChanged(); break;
        case 12: _t->barValueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->handleSeriesDestroyed(); break;
        case 14: _t->initializeBarFromModel(); break;
        default: ;
        }
    }
}

const QMetaObject *QBarModelMapperPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QBarModelMapperPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN22QBarModelMapperPrivateE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QBarModelMapperPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
