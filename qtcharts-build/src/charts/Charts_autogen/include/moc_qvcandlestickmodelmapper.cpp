/****************************************************************************
** Meta object code from reading C++ file 'qvcandlestickmodelmapper.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/qvcandlestickmodelmapper.h"
#include <QtCharts/qcandlestickseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qvcandlestickmodelmapper.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN24QVCandlestickModelMapperE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN24QVCandlestickModelMapperE = QtMocHelpers::stringData(
    "QVCandlestickModelMapper",
    "timestampRowChanged",
    "",
    "openRowChanged",
    "highRowChanged",
    "lowRowChanged",
    "closeRowChanged",
    "firstSetColumnChanged",
    "lastSetColumnChanged",
    "timestampRow",
    "openRow",
    "highRow",
    "lowRow",
    "closeRow",
    "firstSetColumn",
    "lastSetColumn"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN24QVCandlestickModelMapperE[] = {

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

Q_CONSTINIT const QMetaObject QVCandlestickModelMapper::staticMetaObject = { {
    QMetaObject::SuperData::link<QCandlestickModelMapper::staticMetaObject>(),
    qt_meta_stringdata_ZN24QVCandlestickModelMapperE.offsetsAndSizes,
    qt_meta_data_ZN24QVCandlestickModelMapperE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN24QVCandlestickModelMapperE_t,
        // property 'timestampRow'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'openRow'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'highRow'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'lowRow'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'closeRow'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'firstSetColumn'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'lastSetColumn'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QVCandlestickModelMapper, std::true_type>,
        // method 'timestampRowChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openRowChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'highRowChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'lowRowChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closeRowChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'firstSetColumnChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'lastSetColumnChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QVCandlestickModelMapper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QVCandlestickModelMapper *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->timestampRowChanged(); break;
        case 1: _t->openRowChanged(); break;
        case 2: _t->highRowChanged(); break;
        case 3: _t->lowRowChanged(); break;
        case 4: _t->closeRowChanged(); break;
        case 5: _t->firstSetColumnChanged(); break;
        case 6: _t->lastSetColumnChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QVCandlestickModelMapper::*)();
            if (_q_method_type _q_method = &QVCandlestickModelMapper::timestampRowChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QVCandlestickModelMapper::*)();
            if (_q_method_type _q_method = &QVCandlestickModelMapper::openRowChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QVCandlestickModelMapper::*)();
            if (_q_method_type _q_method = &QVCandlestickModelMapper::highRowChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QVCandlestickModelMapper::*)();
            if (_q_method_type _q_method = &QVCandlestickModelMapper::lowRowChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QVCandlestickModelMapper::*)();
            if (_q_method_type _q_method = &QVCandlestickModelMapper::closeRowChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QVCandlestickModelMapper::*)();
            if (_q_method_type _q_method = &QVCandlestickModelMapper::firstSetColumnChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QVCandlestickModelMapper::*)();
            if (_q_method_type _q_method = &QVCandlestickModelMapper::lastSetColumnChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->timestampRow(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->openRow(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->highRow(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->lowRow(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->closeRow(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->firstSetColumn(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->lastSetColumn(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTimestampRow(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setOpenRow(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setHighRow(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setLowRow(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setCloseRow(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setFirstSetColumn(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setLastSetColumn(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QVCandlestickModelMapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QVCandlestickModelMapper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN24QVCandlestickModelMapperE.stringdata0))
        return static_cast<void*>(this);
    return QCandlestickModelMapper::qt_metacast(_clname);
}

int QVCandlestickModelMapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void QVCandlestickModelMapper::timestampRowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QVCandlestickModelMapper::openRowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QVCandlestickModelMapper::highRowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QVCandlestickModelMapper::lowRowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QVCandlestickModelMapper::closeRowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QVCandlestickModelMapper::firstSetColumnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QVCandlestickModelMapper::lastSetColumnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
