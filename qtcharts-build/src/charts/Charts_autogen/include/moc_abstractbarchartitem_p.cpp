/****************************************************************************
** Meta object code from reading C++ file 'abstractbarchartitem_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/abstractbarchartitem_p.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abstractbarchartitem_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN20AbstractBarChartItemE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN20AbstractBarChartItemE = QtMocHelpers::stringData(
    "AbstractBarChartItem",
    "handleDomainUpdated",
    "",
    "handleLayoutChanged",
    "handleLabelsVisibleChanged",
    "visible",
    "handleDataStructureChanged",
    "handleVisibleChanged",
    "handleOpacityChanged",
    "handleUpdatedBars",
    "handleLabelsPositionChanged",
    "positionLabels",
    "handleBarValueChange",
    "index",
    "QBarSet*",
    "barset",
    "handleBarValueAdd",
    "count",
    "handleBarValueRemove",
    "handleSeriesAdded",
    "QAbstractSeries*",
    "series",
    "handleSeriesRemoved"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN20AbstractBarChartItemE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x0a,    1 /* Public */,
       3,    0,   99,    2, 0x0a,    2 /* Public */,
       4,    1,  100,    2, 0x0a,    3 /* Public */,
       6,    0,  103,    2, 0x0a,    5 /* Public */,
       7,    0,  104,    2, 0x0a,    6 /* Public */,
       8,    0,  105,    2, 0x0a,    7 /* Public */,
       9,    0,  106,    2, 0x0a,    8 /* Public */,
      10,    0,  107,    2, 0x0a,    9 /* Public */,
      11,    0,  108,    2, 0x0a,   10 /* Public */,
      12,    2,  109,    2, 0x0a,   11 /* Public */,
      16,    3,  114,    2, 0x0a,   14 /* Public */,
      18,    3,  121,    2, 0x0a,   18 /* Public */,
      19,    1,  128,    2, 0x0a,   22 /* Public */,
      22,    1,  131,    2, 0x0a,   24 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14,   13,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 14,   13,   17,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 14,   13,   17,   15,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 20,   21,

       0        // eod
};

Q_CONSTINIT const QMetaObject AbstractBarChartItem::staticMetaObject = { {
    QMetaObject::SuperData::link<ChartItem::staticMetaObject>(),
    qt_meta_stringdata_ZN20AbstractBarChartItemE.offsetsAndSizes,
    qt_meta_data_ZN20AbstractBarChartItemE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN20AbstractBarChartItemE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<AbstractBarChartItem, std::true_type>,
        // method 'handleDomainUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleLayoutChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleLabelsVisibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handleDataStructureChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleVisibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleOpacityChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleUpdatedBars'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleLabelsPositionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'positionLabels'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleBarValueChange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBarSet *, std::false_type>,
        // method 'handleBarValueAdd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBarSet *, std::false_type>,
        // method 'handleBarValueRemove'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBarSet *, std::false_type>,
        // method 'handleSeriesAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSeries *, std::false_type>,
        // method 'handleSeriesRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSeries *, std::false_type>
    >,
    nullptr
} };

void AbstractBarChartItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AbstractBarChartItem *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->handleDomainUpdated(); break;
        case 1: _t->handleLayoutChanged(); break;
        case 2: _t->handleLabelsVisibleChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->handleDataStructureChanged(); break;
        case 4: _t->handleVisibleChanged(); break;
        case 5: _t->handleOpacityChanged(); break;
        case 6: _t->handleUpdatedBars(); break;
        case 7: _t->handleLabelsPositionChanged(); break;
        case 8: _t->positionLabels(); break;
        case 9: _t->handleBarValueChange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[2]))); break;
        case 10: _t->handleBarValueAdd((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[3]))); break;
        case 11: _t->handleBarValueRemove((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[3]))); break;
        case 12: _t->handleSeriesAdded((*reinterpret_cast< std::add_pointer_t<QAbstractSeries*>>(_a[1]))); break;
        case 13: _t->handleSeriesRemoved((*reinterpret_cast< std::add_pointer_t<QAbstractSeries*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSeries* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *AbstractBarChartItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AbstractBarChartItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN20AbstractBarChartItemE.stringdata0))
        return static_cast<void*>(this);
    return ChartItem::qt_metacast(_clname);
}

int AbstractBarChartItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ChartItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
