/****************************************************************************
** Meta object code from reading C++ file 'qpieseries_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/piechart/qpieseries_p.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qpieseries_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN17QPieSeriesPrivateE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN17QPieSeriesPrivateE = QtMocHelpers::stringData(
    "QPieSeriesPrivate",
    "calculatedDataChanged",
    "",
    "pieSizeChanged",
    "pieStartAngleChanged",
    "pieEndAngleChanged",
    "horizontalPositionChanged",
    "verticalPositionChanged",
    "sliceValueChanged",
    "sliceClicked",
    "sliceHovered",
    "state",
    "slicePressed",
    "sliceReleased",
    "sliceDoubleClicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN17QPieSeriesPrivateE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x06,    1 /* Public */,
       3,    0,   87,    2, 0x06,    2 /* Public */,
       4,    0,   88,    2, 0x06,    3 /* Public */,
       5,    0,   89,    2, 0x06,    4 /* Public */,
       6,    0,   90,    2, 0x06,    5 /* Public */,
       7,    0,   91,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,   92,    2, 0x0a,    7 /* Public */,
       9,    0,   93,    2, 0x0a,    8 /* Public */,
      10,    1,   94,    2, 0x0a,    9 /* Public */,
      12,    0,   97,    2, 0x0a,   11 /* Public */,
      13,    0,   98,    2, 0x0a,   12 /* Public */,
      14,    0,   99,    2, 0x0a,   13 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QPieSeriesPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractSeriesPrivate::staticMetaObject>(),
    qt_meta_stringdata_ZN17QPieSeriesPrivateE.offsetsAndSizes,
    qt_meta_data_ZN17QPieSeriesPrivateE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN17QPieSeriesPrivateE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QPieSeriesPrivate, std::true_type>,
        // method 'calculatedDataChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pieSizeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pieStartAngleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pieEndAngleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'horizontalPositionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'verticalPositionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sliceValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sliceClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sliceHovered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'slicePressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sliceReleased'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sliceDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QPieSeriesPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QPieSeriesPrivate *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->calculatedDataChanged(); break;
        case 1: _t->pieSizeChanged(); break;
        case 2: _t->pieStartAngleChanged(); break;
        case 3: _t->pieEndAngleChanged(); break;
        case 4: _t->horizontalPositionChanged(); break;
        case 5: _t->verticalPositionChanged(); break;
        case 6: _t->sliceValueChanged(); break;
        case 7: _t->sliceClicked(); break;
        case 8: _t->sliceHovered((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->slicePressed(); break;
        case 10: _t->sliceReleased(); break;
        case 11: _t->sliceDoubleClicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QPieSeriesPrivate::*)();
            if (_q_method_type _q_method = &QPieSeriesPrivate::calculatedDataChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QPieSeriesPrivate::*)();
            if (_q_method_type _q_method = &QPieSeriesPrivate::pieSizeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QPieSeriesPrivate::*)();
            if (_q_method_type _q_method = &QPieSeriesPrivate::pieStartAngleChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QPieSeriesPrivate::*)();
            if (_q_method_type _q_method = &QPieSeriesPrivate::pieEndAngleChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QPieSeriesPrivate::*)();
            if (_q_method_type _q_method = &QPieSeriesPrivate::horizontalPositionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QPieSeriesPrivate::*)();
            if (_q_method_type _q_method = &QPieSeriesPrivate::verticalPositionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject *QPieSeriesPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QPieSeriesPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN17QPieSeriesPrivateE.stringdata0))
        return static_cast<void*>(this);
    return QAbstractSeriesPrivate::qt_metacast(_clname);
}

int QPieSeriesPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractSeriesPrivate::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void QPieSeriesPrivate::calculatedDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QPieSeriesPrivate::pieSizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QPieSeriesPrivate::pieStartAngleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QPieSeriesPrivate::pieEndAngleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QPieSeriesPrivate::horizontalPositionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QPieSeriesPrivate::verticalPositionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
