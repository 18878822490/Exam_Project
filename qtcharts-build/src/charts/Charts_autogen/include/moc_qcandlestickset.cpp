/****************************************************************************
** Meta object code from reading C++ file 'qcandlestickset.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/candlestickchart/qcandlestickset.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcandlestickset.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN15QCandlestickSetE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN15QCandlestickSetE = QtMocHelpers::stringData(
    "QCandlestickSet",
    "clicked",
    "",
    "hovered",
    "status",
    "pressed",
    "released",
    "doubleClicked",
    "timestampChanged",
    "openChanged",
    "highChanged",
    "lowChanged",
    "closeChanged",
    "brushChanged",
    "penChanged",
    "timestamp",
    "open",
    "high",
    "low",
    "close",
    "brush",
    "pen"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN15QCandlestickSetE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       7,  100, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x06,    8 /* Public */,
       3,    1,   87,    2, 0x06,    9 /* Public */,
       5,    0,   90,    2, 0x06,   11 /* Public */,
       6,    0,   91,    2, 0x06,   12 /* Public */,
       7,    0,   92,    2, 0x06,   13 /* Public */,
       8,    0,   93,    2, 0x06,   14 /* Public */,
       9,    0,   94,    2, 0x06,   15 /* Public */,
      10,    0,   95,    2, 0x06,   16 /* Public */,
      11,    0,   96,    2, 0x06,   17 /* Public */,
      12,    0,   97,    2, 0x06,   18 /* Public */,
      13,    0,   98,    2, 0x06,   19 /* Public */,
      14,    0,   99,    2, 0x06,   20 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      15, QMetaType::QReal, 0x00015103, uint(5), 0,
      16, QMetaType::QReal, 0x00015103, uint(6), 0,
      17, QMetaType::QReal, 0x00015103, uint(7), 0,
      18, QMetaType::QReal, 0x00015103, uint(8), 0,
      19, QMetaType::QReal, 0x00015103, uint(9), 0,
      20, QMetaType::QBrush, 0x00015103, uint(10), 0,
      21, QMetaType::QPen, 0x00015103, uint(11), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCandlestickSet::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN15QCandlestickSetE.offsetsAndSizes,
    qt_meta_data_ZN15QCandlestickSetE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN15QCandlestickSetE_t,
        // property 'timestamp'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'open'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'high'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'low'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'close'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCandlestickSet, std::true_type>,
        // method 'clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hovered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'released'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'doubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
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
        // method 'brushChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'penChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QCandlestickSet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCandlestickSet *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->hovered((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->pressed(); break;
        case 3: _t->released(); break;
        case 4: _t->doubleClicked(); break;
        case 5: _t->timestampChanged(); break;
        case 6: _t->openChanged(); break;
        case 7: _t->highChanged(); break;
        case 8: _t->lowChanged(); break;
        case 9: _t->closeChanged(); break;
        case 10: _t->brushChanged(); break;
        case 11: _t->penChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QCandlestickSet::*)();
            if (_q_method_type _q_method = &QCandlestickSet::clicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickSet::*)(bool );
            if (_q_method_type _q_method = &QCandlestickSet::hovered; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickSet::*)();
            if (_q_method_type _q_method = &QCandlestickSet::pressed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickSet::*)();
            if (_q_method_type _q_method = &QCandlestickSet::released; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickSet::*)();
            if (_q_method_type _q_method = &QCandlestickSet::doubleClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickSet::*)();
            if (_q_method_type _q_method = &QCandlestickSet::timestampChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickSet::*)();
            if (_q_method_type _q_method = &QCandlestickSet::openChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickSet::*)();
            if (_q_method_type _q_method = &QCandlestickSet::highChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickSet::*)();
            if (_q_method_type _q_method = &QCandlestickSet::lowChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickSet::*)();
            if (_q_method_type _q_method = &QCandlestickSet::closeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickSet::*)();
            if (_q_method_type _q_method = &QCandlestickSet::brushChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _q_method_type = void (QCandlestickSet::*)();
            if (_q_method_type _q_method = &QCandlestickSet::penChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->timestamp(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = _t->open(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = _t->high(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = _t->low(); break;
        case 4: *reinterpret_cast< qreal*>(_v) = _t->close(); break;
        case 5: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 6: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTimestamp(*reinterpret_cast< qreal*>(_v)); break;
        case 1: _t->setOpen(*reinterpret_cast< qreal*>(_v)); break;
        case 2: _t->setHigh(*reinterpret_cast< qreal*>(_v)); break;
        case 3: _t->setLow(*reinterpret_cast< qreal*>(_v)); break;
        case 4: _t->setClose(*reinterpret_cast< qreal*>(_v)); break;
        case 5: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 6: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QCandlestickSet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCandlestickSet::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN15QCandlestickSetE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QCandlestickSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QCandlestickSet::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QCandlestickSet::hovered(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCandlestickSet::pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QCandlestickSet::released()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QCandlestickSet::doubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QCandlestickSet::timestampChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QCandlestickSet::openChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void QCandlestickSet::highChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void QCandlestickSet::lowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void QCandlestickSet::closeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void QCandlestickSet::brushChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void QCandlestickSet::penChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}
QT_WARNING_POP
