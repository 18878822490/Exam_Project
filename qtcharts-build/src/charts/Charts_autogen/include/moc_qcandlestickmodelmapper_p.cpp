/****************************************************************************
** Meta object code from reading C++ file 'qcandlestickmodelmapper_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/qcandlestickmodelmapper_p.h"
#include <QtCharts/qcandlestickseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcandlestickmodelmapper_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN30QCandlestickModelMapperPrivateE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN30QCandlestickModelMapperPrivateE = QtMocHelpers::stringData(
    "QCandlestickModelMapperPrivate",
    "timestampChanged",
    "",
    "openChanged",
    "highChanged",
    "lowChanged",
    "closeChanged",
    "firstSetSectionChanged",
    "lastSetSectionChanged",
    "initializeCandlestickFromModel",
    "modelDataUpdated",
    "QModelIndex",
    "topLeft",
    "bottomRight",
    "modelHeaderDataUpdated",
    "Qt::Orientation",
    "orientation",
    "first",
    "last",
    "modelRowsInserted",
    "parent",
    "start",
    "end",
    "modelRowsRemoved",
    "modelColumnsInserted",
    "modelColumnsRemoved",
    "modelDestroyed",
    "candlestickSetsAdded",
    "QList<QCandlestickSet*>",
    "sets",
    "candlestickSetsRemoved",
    "candlestickSetChanged",
    "seriesDestroyed"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN30QCandlestickModelMapperPrivateE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  128,    2, 0x06,    1 /* Public */,
       3,    0,  129,    2, 0x06,    2 /* Public */,
       4,    0,  130,    2, 0x06,    3 /* Public */,
       5,    0,  131,    2, 0x06,    4 /* Public */,
       6,    0,  132,    2, 0x06,    5 /* Public */,
       7,    0,  133,    2, 0x06,    6 /* Public */,
       8,    0,  134,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,  135,    2, 0x08,    8 /* Private */,
      10,    2,  136,    2, 0x08,    9 /* Private */,
      14,    3,  141,    2, 0x08,   12 /* Private */,
      19,    3,  148,    2, 0x08,   16 /* Private */,
      23,    3,  155,    2, 0x08,   20 /* Private */,
      24,    3,  162,    2, 0x08,   24 /* Private */,
      25,    3,  169,    2, 0x08,   28 /* Private */,
      26,    0,  176,    2, 0x08,   32 /* Private */,
      27,    1,  177,    2, 0x08,   33 /* Private */,
      30,    1,  180,    2, 0x08,   35 /* Private */,
      31,    0,  183,    2, 0x08,   37 /* Private */,
      32,    0,  184,    2, 0x08,   38 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 11,   12,   13,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int, QMetaType::Int,   16,   17,   18,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int, QMetaType::Int,   20,   21,   22,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int, QMetaType::Int,   20,   21,   22,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int, QMetaType::Int,   20,   21,   22,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int, QMetaType::Int,   20,   21,   22,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCandlestickModelMapperPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN30QCandlestickModelMapperPrivateE.offsetsAndSizes,
    qt_meta_data_ZN30QCandlestickModelMapperPrivateE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN30QCandlestickModelMapperPrivateE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCandlestickModelMapperPrivate, std::true_type>,
        // method 'timestampChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'highChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'lowChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'firstSetSectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'lastSetSectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'initializeCandlestickFromModel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'modelDataUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>,
        // method 'modelHeaderDataUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Qt::Orientation, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'modelRowsInserted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'modelRowsRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'modelColumnsInserted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'modelColumnsRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'modelDestroyed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'candlestickSetsAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QCandlestickSet*> &, std::false_type>,
        // method 'candlestickSetsRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QCandlestickSet*> &, std::false_type>,
        // method 'candlestickSetChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'seriesDestroyed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QCandlestickModelMapperPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCandlestickModelMapperPrivate *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->timestampChanged(); break;
        case 1: _t->openChanged(); break;
        case 2: _t->highChanged(); break;
        case 3: _t->lowChanged(); break;
        case 4: _t->closeChanged(); break;
        case 5: _t->firstSetSectionChanged(); break;
        case 6: _t->lastSetSectionChanged(); break;
        case 7: _t->initializeCandlestickFromModel(); break;
        case 8: _t->modelDataUpdated((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[2]))); break;
        case 9: _t->modelHeaderDataUpdated((*reinterpret_cast< std::add_pointer_t<Qt::Orientation>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 10: _t->modelRowsInserted((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 11: _t->modelRowsRemoved((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 12: _t->modelColumnsInserted((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 13: _t->modelColumnsRemoved((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 14: _t->modelDestroyed(); break;
        case 15: _t->candlestickSetsAdded((*reinterpret_cast< std::add_pointer_t<QList<QCandlestickSet*>>>(_a[1]))); break;
        case 16: _t->candlestickSetsRemoved((*reinterpret_cast< std::add_pointer_t<QList<QCandlestickSet*>>>(_a[1]))); break;
        case 17: _t->candlestickSetChanged(); break;
        case 18: _t->seriesDestroyed(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCandlestickModelMapperPrivate::*)();
            if (_q_method_type _q_method = &QCandlestickModelMapperPrivate::timestampChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickModelMapperPrivate::*)();
            if (_q_method_type _q_method = &QCandlestickModelMapperPrivate::openChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickModelMapperPrivate::*)();
            if (_q_method_type _q_method = &QCandlestickModelMapperPrivate::highChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickModelMapperPrivate::*)();
            if (_q_method_type _q_method = &QCandlestickModelMapperPrivate::lowChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickModelMapperPrivate::*)();
            if (_q_method_type _q_method = &QCandlestickModelMapperPrivate::closeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickModelMapperPrivate::*)();
            if (_q_method_type _q_method = &QCandlestickModelMapperPrivate::firstSetSectionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickModelMapperPrivate::*)();
            if (_q_method_type _q_method = &QCandlestickModelMapperPrivate::lastSetSectionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject *QCandlestickModelMapperPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCandlestickModelMapperPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN30QCandlestickModelMapperPrivateE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QCandlestickModelMapperPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void QCandlestickModelMapperPrivate::timestampChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QCandlestickModelMapperPrivate::openChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QCandlestickModelMapperPrivate::highChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QCandlestickModelMapperPrivate::lowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QCandlestickModelMapperPrivate::closeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QCandlestickModelMapperPrivate::firstSetSectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QCandlestickModelMapperPrivate::lastSetSectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
