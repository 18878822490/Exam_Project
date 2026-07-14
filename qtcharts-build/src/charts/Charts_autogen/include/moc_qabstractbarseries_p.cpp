/****************************************************************************
** Meta object code from reading C++ file 'qabstractbarseries_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/qabstractbarseries_p.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qabstractbarseries_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN25QAbstractBarSeriesPrivateE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN25QAbstractBarSeriesPrivateE = QtMocHelpers::stringData(
    "QAbstractBarSeriesPrivate",
    "clicked",
    "",
    "index",
    "QBarSet*",
    "barset",
    "pressed",
    "released",
    "doubleClicked",
    "updatedBars",
    "updatedLayout",
    "restructuredBars",
    "labelsVisibleChanged",
    "visible",
    "visibleChanged",
    "setValueChanged",
    "setValueAdded",
    "count",
    "setValueRemoved",
    "handleSetValueChange",
    "handleSetValueAdd",
    "handleSetValueRemove"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN25QAbstractBarSeriesPrivateE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  104,    2, 0x06,    1 /* Public */,
       6,    2,  109,    2, 0x06,    4 /* Public */,
       7,    2,  114,    2, 0x06,    7 /* Public */,
       8,    2,  119,    2, 0x06,   10 /* Public */,
       9,    0,  124,    2, 0x06,   13 /* Public */,
      10,    0,  125,    2, 0x06,   14 /* Public */,
      11,    0,  126,    2, 0x06,   15 /* Public */,
      12,    1,  127,    2, 0x06,   16 /* Public */,
      14,    0,  130,    2, 0x06,   18 /* Public */,
      15,    2,  131,    2, 0x06,   19 /* Public */,
      16,    3,  136,    2, 0x06,   22 /* Public */,
      18,    3,  143,    2, 0x06,   26 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      19,    1,  150,    2, 0x08,   30 /* Private */,
      20,    2,  153,    2, 0x08,   32 /* Private */,
      21,    2,  158,    2, 0x08,   35 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 4,    3,   17,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 4,    3,   17,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,   17,

       0        // eod
};

Q_CONSTINIT const QMetaObject QAbstractBarSeriesPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractSeriesPrivate::staticMetaObject>(),
    qt_meta_stringdata_ZN25QAbstractBarSeriesPrivateE.offsetsAndSizes,
    qt_meta_data_ZN25QAbstractBarSeriesPrivateE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN25QAbstractBarSeriesPrivateE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QAbstractBarSeriesPrivate, std::true_type>,
        // method 'clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBarSet *, std::false_type>,
        // method 'pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBarSet *, std::false_type>,
        // method 'released'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBarSet *, std::false_type>,
        // method 'doubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBarSet *, std::false_type>,
        // method 'updatedBars'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updatedLayout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'restructuredBars'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'labelsVisibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'visibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBarSet *, std::false_type>,
        // method 'setValueAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBarSet *, std::false_type>,
        // method 'setValueRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBarSet *, std::false_type>,
        // method 'handleSetValueChange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handleSetValueAdd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handleSetValueRemove'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void QAbstractBarSeriesPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QAbstractBarSeriesPrivate *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->clicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[2]))); break;
        case 1: _t->pressed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[2]))); break;
        case 2: _t->released((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[2]))); break;
        case 3: _t->doubleClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[2]))); break;
        case 4: _t->updatedBars(); break;
        case 5: _t->updatedLayout(); break;
        case 6: _t->restructuredBars(); break;
        case 7: _t->labelsVisibleChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->visibleChanged(); break;
        case 9: _t->setValueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[2]))); break;
        case 10: _t->setValueAdded((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[3]))); break;
        case 11: _t->setValueRemoved((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[3]))); break;
        case 12: _t->handleSetValueChange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->handleSetValueAdd((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 14: _t->handleSetValueRemove((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QAbstractBarSeriesPrivate::*)(int , QBarSet * );
            if (_q_method_type _q_method = &QAbstractBarSeriesPrivate::clicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeriesPrivate::*)(int , QBarSet * );
            if (_q_method_type _q_method = &QAbstractBarSeriesPrivate::pressed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeriesPrivate::*)(int , QBarSet * );
            if (_q_method_type _q_method = &QAbstractBarSeriesPrivate::released; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeriesPrivate::*)(int , QBarSet * );
            if (_q_method_type _q_method = &QAbstractBarSeriesPrivate::doubleClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeriesPrivate::*)();
            if (_q_method_type _q_method = &QAbstractBarSeriesPrivate::updatedBars; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeriesPrivate::*)();
            if (_q_method_type _q_method = &QAbstractBarSeriesPrivate::updatedLayout; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeriesPrivate::*)();
            if (_q_method_type _q_method = &QAbstractBarSeriesPrivate::restructuredBars; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeriesPrivate::*)(bool );
            if (_q_method_type _q_method = &QAbstractBarSeriesPrivate::labelsVisibleChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeriesPrivate::*)();
            if (_q_method_type _q_method = &QAbstractBarSeriesPrivate::visibleChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeriesPrivate::*)(int , QBarSet * );
            if (_q_method_type _q_method = &QAbstractBarSeriesPrivate::setValueChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeriesPrivate::*)(int , int , QBarSet * );
            if (_q_method_type _q_method = &QAbstractBarSeriesPrivate::setValueAdded; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeriesPrivate::*)(int , int , QBarSet * );
            if (_q_method_type _q_method = &QAbstractBarSeriesPrivate::setValueRemoved; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
    }
}

const QMetaObject *QAbstractBarSeriesPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QAbstractBarSeriesPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN25QAbstractBarSeriesPrivateE.stringdata0))
        return static_cast<void*>(this);
    return QAbstractSeriesPrivate::qt_metacast(_clname);
}

int QAbstractBarSeriesPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractSeriesPrivate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void QAbstractBarSeriesPrivate::clicked(int _t1, QBarSet * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QAbstractBarSeriesPrivate::pressed(int _t1, QBarSet * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QAbstractBarSeriesPrivate::released(int _t1, QBarSet * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QAbstractBarSeriesPrivate::doubleClicked(int _t1, QBarSet * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QAbstractBarSeriesPrivate::updatedBars()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QAbstractBarSeriesPrivate::updatedLayout()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QAbstractBarSeriesPrivate::restructuredBars()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void QAbstractBarSeriesPrivate::labelsVisibleChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QAbstractBarSeriesPrivate::visibleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void QAbstractBarSeriesPrivate::setValueChanged(int _t1, QBarSet * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QAbstractBarSeriesPrivate::setValueAdded(int _t1, int _t2, QBarSet * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void QAbstractBarSeriesPrivate::setValueRemoved(int _t1, int _t2, QBarSet * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_WARNING_POP
