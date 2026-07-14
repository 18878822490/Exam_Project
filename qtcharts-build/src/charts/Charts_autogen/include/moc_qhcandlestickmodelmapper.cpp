/****************************************************************************
** Meta object code from reading C++ file 'qhcandlestickmodelmapper.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/qhcandlestickmodelmapper.h"
#include <QtCharts/qcandlestickseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qhcandlestickmodelmapper.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN24QHCandlestickModelMapperE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN24QHCandlestickModelMapperE = QtMocHelpers::stringData(
    "QHCandlestickModelMapper",
    "timestampColumnChanged",
    "",
    "openColumnChanged",
    "highColumnChanged",
    "lowColumnChanged",
    "closeColumnChanged",
    "firstSetRowChanged",
    "lastSetRowChanged",
    "timestampColumn",
    "openColumn",
    "highColumn",
    "lowColumn",
    "closeColumn",
    "firstSetRow",
    "lastSetRow"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN24QHCandlestickModelMapperE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       7,   63, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x06,    8 /* Public */,
       3,    0,   57,    2, 0x06,    9 /* Public */,
       4,    0,   58,    2, 0x06,   10 /* Public */,
       5,    0,   59,    2, 0x06,   11 /* Public */,
       6,    0,   60,    2, 0x06,   12 /* Public */,
       7,    0,   61,    2, 0x06,   13 /* Public */,
       8,    0,   62,    2, 0x06,   14 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
       9, QMetaType::Int, 0x00015103, uint(0), 0,
      10, QMetaType::Int, 0x00015103, uint(1), 0,
      11, QMetaType::Int, 0x00015103, uint(2), 0,
      12, QMetaType::Int, 0x00015103, uint(3), 0,
      13, QMetaType::Int, 0x00015103, uint(4), 0,
      14, QMetaType::Int, 0x00015103, uint(5), 0,
      15, QMetaType::Int, 0x00015103, uint(6), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QHCandlestickModelMapper::staticMetaObject = { {
    QMetaObject::SuperData::link<QCandlestickModelMapper::staticMetaObject>(),
    qt_meta_stringdata_ZN24QHCandlestickModelMapperE.offsetsAndSizes,
    qt_meta_data_ZN24QHCandlestickModelMapperE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN24QHCandlestickModelMapperE_t,
        // property 'timestampColumn'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'openColumn'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'highColumn'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'lowColumn'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'closeColumn'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'firstSetRow'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'lastSetRow'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QHCandlestickModelMapper, std::true_type>,
        // method 'timestampColumnChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openColumnChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'highColumnChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'lowColumnChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closeColumnChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'firstSetRowChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'lastSetRowChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QHCandlestickModelMapper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QHCandlestickModelMapper *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->timestampColumnChanged(); break;
        case 1: _t->openColumnChanged(); break;
        case 2: _t->highColumnChanged(); break;
        case 3: _t->lowColumnChanged(); break;
        case 4: _t->closeColumnChanged(); break;
        case 5: _t->firstSetRowChanged(); break;
        case 6: _t->lastSetRowChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QHCandlestickModelMapper::*)();
            if (_q_method_type _q_method = &QHCandlestickModelMapper::timestampColumnChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QHCandlestickModelMapper::*)();
            if (_q_method_type _q_method = &QHCandlestickModelMapper::openColumnChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QHCandlestickModelMapper::*)();
            if (_q_method_type _q_method = &QHCandlestickModelMapper::highColumnChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QHCandlestickModelMapper::*)();
            if (_q_method_type _q_method = &QHCandlestickModelMapper::lowColumnChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QHCandlestickModelMapper::*)();
            if (_q_method_type _q_method = &QHCandlestickModelMapper::closeColumnChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QHCandlestickModelMapper::*)();
            if (_q_method_type _q_method = &QHCandlestickModelMapper::firstSetRowChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QHCandlestickModelMapper::*)();
            if (_q_method_type _q_method = &QHCandlestickModelMapper::lastSetRowChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->timestampColumn(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->openColumn(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->highColumn(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->lowColumn(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->closeColumn(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->firstSetRow(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->lastSetRow(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTimestampColumn(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setOpenColumn(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setHighColumn(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setLowColumn(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setCloseColumn(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setFirstSetRow(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setLastSetRow(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QHCandlestickModelMapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QHCandlestickModelMapper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN24QHCandlestickModelMapperE.stringdata0))
        return static_cast<void*>(this);
    return QCandlestickModelMapper::qt_metacast(_clname);
}

int QHCandlestickModelMapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCandlestickModelMapper::qt_metacall(_c, _id, _a);
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
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QHCandlestickModelMapper::timestampColumnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QHCandlestickModelMapper::openColumnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QHCandlestickModelMapper::highColumnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QHCandlestickModelMapper::lowColumnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QHCandlestickModelMapper::closeColumnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QHCandlestickModelMapper::firstSetRowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QHCandlestickModelMapper::lastSetRowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
