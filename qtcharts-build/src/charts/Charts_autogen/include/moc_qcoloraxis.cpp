/****************************************************************************
** Meta object code from reading C++ file 'qcoloraxis.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/axis/coloraxis/qcoloraxis.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcoloraxis.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10QColorAxisE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10QColorAxisE = QtMocHelpers::stringData(
    "QColorAxis",
    "minChanged",
    "",
    "min",
    "maxChanged",
    "max",
    "rangeChanged",
    "tickCountChanged",
    "tickCount",
    "gradientChanged",
    "QLinearGradient",
    "gradient",
    "sizeChanged",
    "size",
    "autoRangeChanged",
    "autoRange"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10QColorAxisE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       5,   79, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    6 /* Public */,
       4,    1,   59,    2, 0x06,    8 /* Public */,
       6,    2,   62,    2, 0x06,   10 /* Public */,
       7,    1,   67,    2, 0x06,   13 /* Public */,
       9,    1,   70,    2, 0x06,   15 /* Public */,
      12,    1,   73,    2, 0x06,   17 /* Public */,
      14,    1,   76,    2, 0x06,   19 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QReal,    3,
    QMetaType::Void, QMetaType::QReal,    5,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,    3,    5,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::QReal,   13,
    QMetaType::Void, QMetaType::Bool,   15,

 // properties: name, type, flags, notifyId, revision
       8, QMetaType::Int, 0x00015103, uint(3), 0,
       3, QMetaType::QReal, 0x00015103, uint(0), 0,
       5, QMetaType::QReal, 0x00015103, uint(1), 0,
      13, QMetaType::QReal, 0x00015103, uint(5), 0,
      15, QMetaType::Bool, 0x00015103, uint(6), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QColorAxis::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractAxis::staticMetaObject>(),
    qt_meta_stringdata_ZN10QColorAxisE.offsetsAndSizes,
    qt_meta_data_ZN10QColorAxisE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10QColorAxisE_t,
        // property 'tickCount'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'min'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'max'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'size'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'autoRange'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QColorAxis, std::true_type>,
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
        // method 'gradientChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QLinearGradient &, std::false_type>,
        // method 'sizeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const qreal, std::false_type>,
        // method 'autoRangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void QColorAxis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QColorAxis *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->minChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 1: _t->maxChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 2: _t->rangeChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[2]))); break;
        case 3: _t->tickCountChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->gradientChanged((*reinterpret_cast< std::add_pointer_t<QLinearGradient>>(_a[1]))); break;
        case 5: _t->sizeChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 6: _t->autoRangeChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QColorAxis::*)(qreal );
            if (_q_method_type _q_method = &QColorAxis::minChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QColorAxis::*)(qreal );
            if (_q_method_type _q_method = &QColorAxis::maxChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QColorAxis::*)(qreal , qreal );
            if (_q_method_type _q_method = &QColorAxis::rangeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QColorAxis::*)(int );
            if (_q_method_type _q_method = &QColorAxis::tickCountChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QColorAxis::*)(const QLinearGradient & );
            if (_q_method_type _q_method = &QColorAxis::gradientChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QColorAxis::*)(const qreal );
            if (_q_method_type _q_method = &QColorAxis::sizeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QColorAxis::*)(bool );
            if (_q_method_type _q_method = &QColorAxis::autoRangeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
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
        case 3: *reinterpret_cast< qreal*>(_v) = _t->size(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->autoRange(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTickCount(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setMin(*reinterpret_cast< qreal*>(_v)); break;
        case 2: _t->setMax(*reinterpret_cast< qreal*>(_v)); break;
        case 3: _t->setSize(*reinterpret_cast< qreal*>(_v)); break;
        case 4: _t->setAutoRange(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QColorAxis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QColorAxis::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10QColorAxisE.stringdata0))
        return static_cast<void*>(this);
    return QAbstractAxis::qt_metacast(_clname);
}

int QColorAxis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractAxis::qt_metacall(_c, _id, _a);
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
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QColorAxis::minChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QColorAxis::maxChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QColorAxis::rangeChanged(qreal _t1, qreal _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QColorAxis::tickCountChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QColorAxis::gradientChanged(const QLinearGradient & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QColorAxis::sizeChanged(const qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QColorAxis::autoRangeChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
