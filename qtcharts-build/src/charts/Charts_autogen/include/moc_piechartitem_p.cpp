/****************************************************************************
** Meta object code from reading C++ file 'piechartitem_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/piechart/piechartitem_p.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'piechartitem_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12PieChartItemE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12PieChartItemE = QtMocHelpers::stringData(
    "PieChartItem",
    "handleDomainUpdated",
    "",
    "updateLayout",
    "handleSlicesAdded",
    "QList<QPieSlice*>",
    "slices",
    "handleSlicesRemoved",
    "handleSliceChanged",
    "handleSeriesVisibleChanged",
    "handleOpacityChanged",
    "setAnimation",
    "PieAnimation*",
    "animation",
    "ChartAnimation*",
    "cleanup"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12PieChartItemE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x0a,    1 /* Public */,
       3,    0,   75,    2, 0x0a,    2 /* Public */,
       4,    1,   76,    2, 0x0a,    3 /* Public */,
       7,    1,   79,    2, 0x0a,    5 /* Public */,
       8,    0,   82,    2, 0x0a,    7 /* Public */,
       9,    0,   83,    2, 0x0a,    8 /* Public */,
      10,    0,   84,    2, 0x0a,    9 /* Public */,
      11,    1,   85,    2, 0x0a,   10 /* Public */,
      13,    0,   88,    2, 0x10a,   12 /* Public | MethodIsConst  */,
      15,    0,   89,    2, 0x0a,   13 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    0x80000000 | 14,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject PieChartItem::staticMetaObject = { {
    QMetaObject::SuperData::link<ChartItem::staticMetaObject>(),
    qt_meta_stringdata_ZN12PieChartItemE.offsetsAndSizes,
    qt_meta_data_ZN12PieChartItemE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN12PieChartItemE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PieChartItem, std::true_type>,
        // method 'handleDomainUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateLayout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleSlicesAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QPieSlice*> &, std::false_type>,
        // method 'handleSlicesRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QPieSlice*> &, std::false_type>,
        // method 'handleSliceChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleSeriesVisibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleOpacityChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setAnimation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<PieAnimation *, std::false_type>,
        // method 'animation'
        QtPrivate::TypeAndForceComplete<ChartAnimation *, std::false_type>,
        // method 'cleanup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void PieChartItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PieChartItem *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->handleDomainUpdated(); break;
        case 1: _t->updateLayout(); break;
        case 2: _t->handleSlicesAdded((*reinterpret_cast< std::add_pointer_t<QList<QPieSlice*>>>(_a[1]))); break;
        case 3: _t->handleSlicesRemoved((*reinterpret_cast< std::add_pointer_t<QList<QPieSlice*>>>(_a[1]))); break;
        case 4: _t->handleSliceChanged(); break;
        case 5: _t->handleSeriesVisibleChanged(); break;
        case 6: _t->handleOpacityChanged(); break;
        case 7: _t->setAnimation((*reinterpret_cast< std::add_pointer_t<PieAnimation*>>(_a[1]))); break;
        case 8: { ChartAnimation* _r = _t->animation();
            if (_a[0]) *reinterpret_cast< ChartAnimation**>(_a[0]) = std::move(_r); }  break;
        case 9: _t->cleanup(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QPieSlice*> >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QPieSlice*> >(); break;
            }
            break;
        }
    }
}

const QMetaObject *PieChartItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PieChartItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN12PieChartItemE.stringdata0))
        return static_cast<void*>(this);
    return ChartItem::qt_metacast(_clname);
}

int PieChartItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ChartItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
