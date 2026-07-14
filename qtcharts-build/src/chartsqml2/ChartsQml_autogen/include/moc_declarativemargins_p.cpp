/****************************************************************************
** Meta object code from reading C++ file 'declarativemargins_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativemargins_p.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'declarativemargins_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN18DeclarativeMarginsE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN18DeclarativeMarginsE = QtMocHelpers::stringData(
    "DeclarativeMargins",
    "QML.Element",
    "Margins",
    "QML.AddedInVersion",
    "257",
    "QML.ExtraVersion",
    "512",
    "QML.Creatable",
    "false",
    "QML.UncreatableReason",
    "Abstract base type",
    "topChanged",
    "",
    "top",
    "bottom",
    "left",
    "right",
    "bottomChanged",
    "leftChanged",
    "rightChanged"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN18DeclarativeMarginsE[] = {

 // content:
      12,       // revision
       0,       // classname
       5,   14, // classinfo
       4,   24, // methods
       4,   84, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,
       7,    8,
       9,   10,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
      11,    4,   48,   12, 0x06,    5 /* Public */,
      17,    4,   57,   12, 0x06,   10 /* Public */,
      18,    4,   66,   12, 0x06,   15 /* Public */,
      19,    4,   75,   12, 0x06,   20 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,   16,

 // properties: name, type, flags, notifyId, revision
      13, QMetaType::Int, 0x00015103, uint(0), 0,
      14, QMetaType::Int, 0x00015103, uint(1), 0,
      15, QMetaType::Int, 0x00015103, uint(2), 0,
      16, QMetaType::Int, 0x00015103, uint(3), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeMargins::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN18DeclarativeMarginsE.offsetsAndSizes,
    qt_meta_data_ZN18DeclarativeMarginsE,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'top'
        int,
        // property 'bottom'
        int,
        // property 'left'
        int,
        // property 'right'
        int,
        // Q_OBJECT / Q_GADGET
        DeclarativeMargins,
        // method 'topChanged'
        void,
        int,
        int,
        int,
        int,
        // method 'bottomChanged'
        void,
        int,
        int,
        int,
        int,
        // method 'leftChanged'
        void,
        int,
        int,
        int,
        int,
        // method 'rightChanged'
        void,
        int,
        int,
        int,
        int
    >,
    nullptr
} };

void DeclarativeMargins::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeMargins *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->topChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        case 1: _t->bottomChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        case 2: _t->leftChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        case 3: _t->rightChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativeMargins::*)(int , int , int , int );
            if (_q_method_type _q_method = &DeclarativeMargins::topChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeMargins::*)(int , int , int , int );
            if (_q_method_type _q_method = &DeclarativeMargins::bottomChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeMargins::*)(int , int , int , int );
            if (_q_method_type _q_method = &DeclarativeMargins::leftChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeMargins::*)(int , int , int , int );
            if (_q_method_type _q_method = &DeclarativeMargins::rightChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->top(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->bottom(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->left(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->right(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTop(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setBottom(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setLeft(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setRight(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *DeclarativeMargins::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeMargins::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN18DeclarativeMarginsE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QMargins"))
        return static_cast< QMargins*>(this);
    return QObject::qt_metacast(_clname);
}

int DeclarativeMargins::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
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
void DeclarativeMargins::topChanged(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeclarativeMargins::bottomChanged(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeclarativeMargins::leftChanged(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DeclarativeMargins::rightChanged(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
