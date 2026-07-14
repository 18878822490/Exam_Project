/****************************************************************************
** Meta object code from reading C++ file 'candlestickchartitem_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/candlestickchartitem_p.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'candlestickchartitem_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN20CandlestickChartItemE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN20CandlestickChartItemE = QtMocHelpers::stringData(
    "CandlestickChartItem",
    "handleDomainUpdated",
    "",
    "handleLayoutUpdated",
    "handleCandlesticksUpdated",
    "handleCandlestickSeriesChange",
    "handleCandlestickSetsAdd",
    "QList<QCandlestickSet*>",
    "sets",
    "handleCandlestickSetsRemove",
    "handleDataStructureChanged"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN20CandlestickChartItemE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x0a,    1 /* Public */,
       3,    0,   57,    2, 0x0a,    2 /* Public */,
       4,    0,   58,    2, 0x0a,    3 /* Public */,
       5,    0,   59,    2, 0x0a,    4 /* Public */,
       6,    1,   60,    2, 0x08,    5 /* Private */,
       9,    1,   63,    2, 0x08,    7 /* Private */,
      10,    0,   66,    2, 0x08,    9 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject CandlestickChartItem::staticMetaObject = { {
    QMetaObject::SuperData::link<ChartItem::staticMetaObject>(),
    qt_meta_stringdata_ZN20CandlestickChartItemE.offsetsAndSizes,
    qt_meta_data_ZN20CandlestickChartItemE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN20CandlestickChartItemE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CandlestickChartItem, std::true_type>,
        // method 'handleDomainUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleLayoutUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleCandlesticksUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleCandlestickSeriesChange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleCandlestickSetsAdd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QCandlestickSet*> &, std::false_type>,
        // method 'handleCandlestickSetsRemove'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QCandlestickSet*> &, std::false_type>,
        // method 'handleDataStructureChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void CandlestickChartItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CandlestickChartItem *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->handleDomainUpdated(); break;
        case 1: _t->handleLayoutUpdated(); break;
        case 2: _t->handleCandlesticksUpdated(); break;
        case 3: _t->handleCandlestickSeriesChange(); break;
        case 4: _t->handleCandlestickSetsAdd((*reinterpret_cast< std::add_pointer_t<QList<QCandlestickSet*>>>(_a[1]))); break;
        case 5: _t->handleCandlestickSetsRemove((*reinterpret_cast< std::add_pointer_t<QList<QCandlestickSet*>>>(_a[1]))); break;
        case 6: _t->handleDataStructureChanged(); break;
        default: ;
        }
    }
}

const QMetaObject *CandlestickChartItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CandlestickChartItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN20CandlestickChartItemE.stringdata0))
        return static_cast<void*>(this);
    return ChartItem::qt_metacast(_clname);
}

int CandlestickChartItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ChartItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
