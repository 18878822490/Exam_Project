/****************************************************************************
** Meta object code from reading C++ file 'declarativeaxes_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativeaxes_p.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'declarativeaxes_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN15DeclarativeAxesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN15DeclarativeAxesE = QtMocHelpers::stringData(
    "DeclarativeAxes",
    "QML.Element",
    "QML.AddedInVersion",
    "256",
    "QML.ExtraVersion",
    "512",
    "QML.Creatable",
    "false",
    "QML.UncreatableReason",
    "Abstract base type",
    "axisXChanged",
    "",
    "QAbstractAxis*",
    "axis",
    "axisYChanged",
    "axisXTopChanged",
    "axisYRightChanged",
    "axisX",
    "axisY",
    "axisXTop",
    "axisYRight"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN15DeclarativeAxesE[] = {

 // content:
      12,       // revision
       0,       // classname
       5,   14, // classinfo
       4,   24, // methods
       4,   60, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    0,
       2,    3,
       4,    5,
       6,    7,
       8,    9,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
      10,    1,   48,   11, 0x06,    5 /* Public */,
      14,    1,   51,   11, 0x06,    7 /* Public */,
      15,    1,   54,   11, 0x06,    9 /* Public */,
      16,    1,   57,   11, 0x06,   11 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,

 // properties: name, type, flags, notifyId, revision
      17, 0x80000000 | 12, 0x0001510b, uint(0), 0,
      18, 0x80000000 | 12, 0x0001510b, uint(1), 0,
      19, 0x80000000 | 12, 0x0001510b, uint(2), 0,
      20, 0x80000000 | 12, 0x0001510b, uint(3), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeAxes::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN15DeclarativeAxesE.offsetsAndSizes,
    qt_meta_data_ZN15DeclarativeAxesE,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'axisX'
        QAbstractAxis*,
        // property 'axisY'
        QAbstractAxis*,
        // property 'axisXTop'
        QAbstractAxis*,
        // property 'axisYRight'
        QAbstractAxis*,
        // Q_OBJECT / Q_GADGET
        DeclarativeAxes,
        // method 'axisXChanged'
        void,
        QAbstractAxis *,
        // method 'axisYChanged'
        void,
        QAbstractAxis *,
        // method 'axisXTopChanged'
        void,
        QAbstractAxis *,
        // method 'axisYRightChanged'
        void,
        QAbstractAxis *
    >,
    nullptr
} };

void DeclarativeAxes::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeAxes *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->axisXChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 1: _t->axisYChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 2: _t->axisXTopChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 3: _t->axisYRightChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativeAxes::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeAxes::axisXChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeAxes::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeAxes::axisYChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeAxes::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeAxes::axisXTopChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeAxes::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeAxes::axisYRightChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
        case 2:
        case 1:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractAxis* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QAbstractAxis**>(_v) = _t->axisX(); break;
        case 1: *reinterpret_cast< QAbstractAxis**>(_v) = _t->axisY(); break;
        case 2: *reinterpret_cast< QAbstractAxis**>(_v) = _t->axisXTop(); break;
        case 3: *reinterpret_cast< QAbstractAxis**>(_v) = _t->axisYRight(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAxisX(*reinterpret_cast< QAbstractAxis**>(_v)); break;
        case 1: _t->setAxisY(*reinterpret_cast< QAbstractAxis**>(_v)); break;
        case 2: _t->setAxisXTop(*reinterpret_cast< QAbstractAxis**>(_v)); break;
        case 3: _t->setAxisYRight(*reinterpret_cast< QAbstractAxis**>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *DeclarativeAxes::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeAxes::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN15DeclarativeAxesE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DeclarativeAxes::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DeclarativeAxes::axisXChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeclarativeAxes::axisYChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeclarativeAxes::axisXTopChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DeclarativeAxes::axisYRightChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
