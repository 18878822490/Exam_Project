/****************************************************************************
** Meta object code from reading C++ file 'qlogvalueaxis.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/axis/logvalueaxis/qlogvalueaxis.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qlogvalueaxis.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13QLogValueAxisE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13QLogValueAxisE = QtMocHelpers::stringData(
    "QLogValueAxis",
    "minChanged",
    "",
    "min",
    "maxChanged",
    "max",
    "rangeChanged",
    "labelFormatChanged",
    "format",
    "baseChanged",
    "base",
    "tickCountChanged",
    "tickCount",
    "minorTickCountChanged",
    "minorTickCount",
    "labelFormat"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13QLogValueAxisE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       6,   79, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    7 /* Public */,
       4,    1,   59,    2, 0x06,    9 /* Public */,
       6,    2,   62,    2, 0x06,   11 /* Public */,
       7,    1,   67,    2, 0x06,   14 /* Public */,
       9,    1,   70,    2, 0x06,   16 /* Public */,
      11,    1,   73,    2, 0x06,   18 /* Public */,
      13,    1,   76,    2, 0x06,   20 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QReal,    3,
    QMetaType::Void, QMetaType::QReal,    5,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,    3,    5,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QReal,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   14,

 // properties: name, type, flags, notifyId, revision
       3, QMetaType::QReal, 0x00015103, uint(0), 0,
       5, QMetaType::QReal, 0x00015103, uint(1), 0,
      15, QMetaType::QString, 0x00015103, uint(3), 0,
      10, QMetaType::QReal, 0x00015103, uint(4), 0,
      12, QMetaType::Int, 0x00015001, uint(5), 0,
      14, QMetaType::Int, 0x00015103, uint(6), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QLogValueAxis::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractAxis::staticMetaObject>(),
    qt_meta_stringdata_ZN13QLogValueAxisE.offsetsAndSizes,
    qt_meta_data_ZN13QLogValueAxisE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13QLogValueAxisE_t,
        // property 'min'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'max'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'labelFormat'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'base'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'tickCount'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'minorTickCount'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QLogValueAxis, std::true_type>,
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
        // method 'labelFormatChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'baseChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qreal, std::false_type>,
        // method 'tickCountChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'minorTickCountChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void QLogValueAxis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QLogValueAxis *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->minChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 1: _t->maxChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 2: _t->rangeChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[2]))); break;
        case 3: _t->labelFormatChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->baseChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 5: _t->tickCountChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->minorTickCountChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QLogValueAxis::*)(qreal );
            if (_q_method_type _q_method = &QLogValueAxis::minChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QLogValueAxis::*)(qreal );
            if (_q_method_type _q_method = &QLogValueAxis::maxChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QLogValueAxis::*)(qreal , qreal );
            if (_q_method_type _q_method = &QLogValueAxis::rangeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QLogValueAxis::*)(const QString & );
            if (_q_method_type _q_method = &QLogValueAxis::labelFormatChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QLogValueAxis::*)(qreal );
            if (_q_method_type _q_method = &QLogValueAxis::baseChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QLogValueAxis::*)(int );
            if (_q_method_type _q_method = &QLogValueAxis::tickCountChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QLogValueAxis::*)(int );
            if (_q_method_type _q_method = &QLogValueAxis::minorTickCountChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->min(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = _t->max(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->labelFormat(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = _t->base(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->tickCount(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->minorTickCount(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMin(*reinterpret_cast< qreal*>(_v)); break;
        case 1: _t->setMax(*reinterpret_cast< qreal*>(_v)); break;
        case 2: _t->setLabelFormat(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setBase(*reinterpret_cast< qreal*>(_v)); break;
        case 5: _t->setMinorTickCount(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QLogValueAxis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QLogValueAxis::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN13QLogValueAxisE.stringdata0))
        return static_cast<void*>(this);
    return QAbstractAxis::qt_metacast(_clname);
}

int QLogValueAxis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QLogValueAxis::minChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QLogValueAxis::maxChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QLogValueAxis::rangeChanged(qreal _t1, qreal _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QLogValueAxis::labelFormatChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QLogValueAxis::baseChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QLogValueAxis::tickCountChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QLogValueAxis::minorTickCountChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
