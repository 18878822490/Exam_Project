/****************************************************************************
** Meta object code from reading C++ file 'qboxplotmodelmapper_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/boxplotchart/qboxplotmodelmapper_p.h"
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qboxplotmodelmapper_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN26QBoxPlotModelMapperPrivateE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN26QBoxPlotModelMapperPrivateE = QtMocHelpers::stringData(
    "QBoxPlotModelMapperPrivate",
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
    "boxSetsAdded",
    "QList<QBoxSet*>",
    "sets",
    "boxSetsRemoved",
    "boxValueChanged",
    "index",
    "handleSeriesDestroyed",
    "initializeBoxFromModel"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN26QBoxPlotModelMapperPrivateE[] = {

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
      11,    3,   98,    2, 0x0a,    8 /* Public */,
      15,    3,  105,    2, 0x0a,   12 /* Public */,
      16,    3,  112,    2, 0x0a,   16 /* Public */,
      17,    3,  119,    2, 0x0a,   20 /* Public */,
      18,    0,  126,    2, 0x0a,   24 /* Public */,
      19,    1,  127,    2, 0x0a,   25 /* Public */,
      22,    1,  130,    2, 0x0a,   27 /* Public */,
      23,    1,  133,    2, 0x0a,   29 /* Public */,
      25,    0,  136,    2, 0x0a,   31 /* Public */,
      26,    0,  137,    2, 0x0a,   32 /* Public */,

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
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QBoxPlotModelMapperPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN26QBoxPlotModelMapperPrivateE.offsetsAndSizes,
    qt_meta_data_ZN26QBoxPlotModelMapperPrivateE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN26QBoxPlotModelMapperPrivateE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QBoxPlotModelMapperPrivate, std::true_type>,
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
        // method 'boxSetsAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QBoxSet*> &, std::false_type>,
        // method 'boxSetsRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QBoxSet*> &, std::false_type>,
        // method 'boxValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handleSeriesDestroyed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'initializeBoxFromModel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QBoxPlotModelMapperPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QBoxPlotModelMapperPrivate *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->modelUpdated((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[2]))); break;
        case 1: _t->modelHeaderDataUpdated((*reinterpret_cast< std::add_pointer_t<Qt::Orientation>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 2: _t->modelRowsAdded((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 3: _t->modelRowsRemoved((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 4: _t->modelColumnsAdded((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 5: _t->modelColumnsRemoved((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 6: _t->handleModelDestroyed(); break;
        case 7: _t->boxSetsAdded((*reinterpret_cast< std::add_pointer_t<QList<QBoxSet*>>>(_a[1]))); break;
        case 8: _t->boxSetsRemoved((*reinterpret_cast< std::add_pointer_t<QList<QBoxSet*>>>(_a[1]))); break;
        case 9: _t->boxValueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->handleSeriesDestroyed(); break;
        case 11: _t->initializeBoxFromModel(); break;
        default: ;
        }
    }
}

const QMetaObject *QBoxPlotModelMapperPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QBoxPlotModelMapperPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN26QBoxPlotModelMapperPrivateE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QBoxPlotModelMapperPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
