/****************************************************************************
** Meta object code from reading C++ file 'qvalueaxis.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/axis/valueaxis/qvalueaxis.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qvalueaxis.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10QValueAxisE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10QValueAxisE = QtMocHelpers::stringData(
    "QValueAxis",
    "minChanged",
    "",
    "min",
    "maxChanged",
    "max",
    "rangeChanged",
    "tickCountChanged",
    "tickCount",
    "minorTickCountChanged",
    "labelFormatChanged",
    "format",
    "tickIntervalChanged",
    "interval",
    "tickAnchorChanged",
    "anchor",
    "tickTypeChanged",
    "QValueAxis::TickType",
    "type",
    "applyNiceNumbers",
    "labelFormat",
    "minorTickCount",
    "tickAnchor",
    "tickInterval",
    "tickType",
    "TickType",
    "TicksDynamic",
    "TicksFixed"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10QValueAxisE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       8,  114, // properties
       1,  154, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   84,    2, 0x06,   10 /* Public */,
       4,    1,   87,    2, 0x06,   12 /* Public */,
       6,    2,   90,    2, 0x06,   14 /* Public */,
       7,    1,   95,    2, 0x06,   17 /* Public */,
       9,    1,   98,    2, 0x06,   19 /* Public */,
      10,    1,  101,    2, 0x06,   21 /* Public */,
      12,    1,  104,    2, 0x86,   23 /* Public | MethodRevisioned */,
      14,    1,  107,    2, 0x86,   25 /* Public | MethodRevisioned */,
      16,    1,  110,    2, 0x86,   27 /* Public | MethodRevisioned */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      19,    0,  113,    2, 0x0a,   29 /* Public */,

 // signals: revision
       0,
       0,
       0,
       0,
       0,
       0,
     515,
     515,
     515,

 // slots: revision
       0,

 // signals: parameters
    QMetaType::Void, QMetaType::QReal,    3,
    QMetaType::Void, QMetaType::QReal,    5,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,    3,    5,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QReal,   13,
    QMetaType::Void, QMetaType::QReal,   15,
    QMetaType::Void, 0x80000000 | 17,   18,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
       8, QMetaType::Int, 0x00015103, uint(3), 0,
       3, QMetaType::QReal, 0x00015103, uint(0), 0,
       5, QMetaType::QReal, 0x00015103, uint(1), 0,
      20, QMetaType::QString, 0x00015103, uint(5), 0,
      21, QMetaType::Int, 0x00015103, uint(4), 0,
      22, QMetaType::QReal, 0x00015103, uint(7), 515,
      23, QMetaType::QReal, 0x00015103, uint(6), 515,
      24, 0x80000000 | 25, 0x0001510b, uint(8), 515,

 // enums: name, alias, flags, count, data
      25,   25, 0x0,    2,  159,

 // enum data: key, value
      26, uint(QValueAxis::TicksDynamic),
      27, uint(QValueAxis::TicksFixed),

       0        // eod
};

Q_CONSTINIT const QMetaObject QValueAxis::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractAxis::staticMetaObject>(),
    qt_meta_stringdata_ZN10QValueAxisE.offsetsAndSizes,
    qt_meta_data_ZN10QValueAxisE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10QValueAxisE_t,
        // property 'tickCount'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'min'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'max'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'labelFormat'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'minorTickCount'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'tickAnchor'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'tickInterval'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'tickType'
        QtPrivate::TypeAndForceComplete<TickType, std::true_type>,
        // enum 'TickType'
        QtPrivate::TypeAndForceComplete<QValueAxis::TickType, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QValueAxis, std::true_type>,
        // method 'minChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qreal, std::false_type>,
        // method 'maxChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qreal, std::false_type>,
        // method 'rangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qreal, std::false_type>,
        QtPrivate::TypeAndForceComplete<qreal, std::false_type>,
        // method 'tickCountChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'minorTickCountChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'labelFormatChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'tickIntervalChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qreal, std::false_type>,
        // method 'tickAnchorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qreal, std::false_type>,
        // method 'tickTypeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QValueAxis::TickType, std::false_type>,
        // method 'applyNiceNumbers'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QValueAxis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QValueAxis *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->minChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 1: _t->maxChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 2: _t->rangeChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[2]))); break;
        case 3: _t->tickCountChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->minorTickCountChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->labelFormatChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->tickIntervalChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 7: _t->tickAnchorChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 8: _t->tickTypeChanged((*reinterpret_cast< std::add_pointer_t<QValueAxis::TickType>>(_a[1]))); break;
        case 9: _t->applyNiceNumbers(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QValueAxis::*)(qreal );
            if (_q_method_type _q_method = &QValueAxis::minChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QValueAxis::*)(qreal );
            if (_q_method_type _q_method = &QValueAxis::maxChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QValueAxis::*)(qreal , qreal );
            if (_q_method_type _q_method = &QValueAxis::rangeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QValueAxis::*)(int );
            if (_q_method_type _q_method = &QValueAxis::tickCountChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QValueAxis::*)(int );
            if (_q_method_type _q_method = &QValueAxis::minorTickCountChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QValueAxis::*)(const QString & );
            if (_q_method_type _q_method = &QValueAxis::labelFormatChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QValueAxis::*)(qreal );
            if (_q_method_type _q_method = &QValueAxis::tickIntervalChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (QValueAxis::*)(qreal );
            if (_q_method_type _q_method = &QValueAxis::tickAnchorChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (QValueAxis::*)(QValueAxis::TickType );
            if (_q_method_type _q_method = &QValueAxis::tickTypeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->tickCount(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = _t->min(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = _t->max(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->labelFormat(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->minorTickCount(); break;
        case 5: *reinterpret_cast< qreal*>(_v) = _t->tickAnchor(); break;
        case 6: *reinterpret_cast< qreal*>(_v) = _t->tickInterval(); break;
        case 7: *reinterpret_cast< TickType*>(_v) = _t->tickType(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTickCount(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setMin(*reinterpret_cast< qreal*>(_v)); break;
        case 2: _t->setMax(*reinterpret_cast< qreal*>(_v)); break;
        case 3: _t->setLabelFormat(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setMinorTickCount(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setTickAnchor(*reinterpret_cast< qreal*>(_v)); break;
        case 6: _t->setTickInterval(*reinterpret_cast< qreal*>(_v)); break;
        case 7: _t->setTickType(*reinterpret_cast< TickType*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QValueAxis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QValueAxis::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10QValueAxisE.stringdata0))
        return static_cast<void*>(this);
    return QAbstractAxis::qt_metacast(_clname);
}

int QValueAxis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractAxis::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QValueAxis::minChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QValueAxis::maxChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QValueAxis::rangeChanged(qreal _t1, qreal _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QValueAxis::tickCountChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QValueAxis::minorTickCountChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QValueAxis::labelFormatChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QValueAxis::tickIntervalChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QValueAxis::tickAnchorChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QValueAxis::tickTypeChanged(QValueAxis::TickType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
