/****************************************************************************
** Meta object code from reading C++ file 'qpieseries.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/piechart/qpieseries.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qpieseries.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10QPieSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10QPieSeriesE = QtMocHelpers::stringData(
    "QPieSeries",
    "added",
    "",
    "QList<QPieSlice*>",
    "slices",
    "removed",
    "clicked",
    "QPieSlice*",
    "slice",
    "hovered",
    "state",
    "pressed",
    "released",
    "doubleClicked",
    "countChanged",
    "sumChanged",
    "horizontalPosition",
    "verticalPosition",
    "size",
    "startAngle",
    "endAngle",
    "count",
    "sum",
    "holeSize"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10QPieSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       8,   93, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,    9 /* Public */,
       5,    1,   71,    2, 0x06,   11 /* Public */,
       6,    1,   74,    2, 0x06,   13 /* Public */,
       9,    2,   77,    2, 0x06,   15 /* Public */,
      11,    1,   82,    2, 0x06,   18 /* Public */,
      12,    1,   85,    2, 0x06,   20 /* Public */,
      13,    1,   88,    2, 0x06,   22 /* Public */,
      14,    0,   91,    2, 0x06,   24 /* Public */,
      15,    0,   92,    2, 0x06,   25 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Bool,    8,   10,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      16, QMetaType::QReal, 0x00015103, uint(-1), 0,
      17, QMetaType::QReal, 0x00015103, uint(-1), 0,
      18, QMetaType::QReal, 0x00015003, uint(-1), 0,
      19, QMetaType::QReal, 0x00015003, uint(-1), 0,
      20, QMetaType::QReal, 0x00015003, uint(-1), 0,
      21, QMetaType::Int, 0x00015001, uint(7), 0,
      22, QMetaType::QReal, 0x00015001, uint(8), 0,
      23, QMetaType::QReal, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QPieSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractSeries::staticMetaObject>(),
    qt_meta_stringdata_ZN10QPieSeriesE.offsetsAndSizes,
    qt_meta_data_ZN10QPieSeriesE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10QPieSeriesE_t,
        // property 'horizontalPosition'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'verticalPosition'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'size'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'startAngle'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'endAngle'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'count'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'sum'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'holeSize'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QPieSeries, std::true_type>,
        // method 'added'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QPieSlice*> &, std::false_type>,
        // method 'removed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QPieSlice*> &, std::false_type>,
        // method 'clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPieSlice *, std::false_type>,
        // method 'hovered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPieSlice *, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPieSlice *, std::false_type>,
        // method 'released'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPieSlice *, std::false_type>,
        // method 'doubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPieSlice *, std::false_type>,
        // method 'countChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sumChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QPieSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QPieSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->added((*reinterpret_cast< std::add_pointer_t<QList<QPieSlice*>>>(_a[1]))); break;
        case 1: _t->removed((*reinterpret_cast< std::add_pointer_t<QList<QPieSlice*>>>(_a[1]))); break;
        case 2: _t->clicked((*reinterpret_cast< std::add_pointer_t<QPieSlice*>>(_a[1]))); break;
        case 3: _t->hovered((*reinterpret_cast< std::add_pointer_t<QPieSlice*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 4: _t->pressed((*reinterpret_cast< std::add_pointer_t<QPieSlice*>>(_a[1]))); break;
        case 5: _t->released((*reinterpret_cast< std::add_pointer_t<QPieSlice*>>(_a[1]))); break;
        case 6: _t->doubleClicked((*reinterpret_cast< std::add_pointer_t<QPieSlice*>>(_a[1]))); break;
        case 7: _t->countChanged(); break;
        case 8: _t->sumChanged(); break;
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
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QPieSlice*> >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QPieSlice*> >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QPieSlice* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QPieSlice* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QPieSlice* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QPieSlice* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QPieSlice* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QPieSeries::*)(const QList<QPieSlice*> & );
            if (_q_method_type _q_method = &QPieSeries::added; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QPieSeries::*)(const QList<QPieSlice*> & );
            if (_q_method_type _q_method = &QPieSeries::removed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QPieSeries::*)(QPieSlice * );
            if (_q_method_type _q_method = &QPieSeries::clicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QPieSeries::*)(QPieSlice * , bool );
            if (_q_method_type _q_method = &QPieSeries::hovered; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QPieSeries::*)(QPieSlice * );
            if (_q_method_type _q_method = &QPieSeries::pressed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QPieSeries::*)(QPieSlice * );
            if (_q_method_type _q_method = &QPieSeries::released; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QPieSeries::*)(QPieSlice * );
            if (_q_method_type _q_method = &QPieSeries::doubleClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (QPieSeries::*)();
            if (_q_method_type _q_method = &QPieSeries::countChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (QPieSeries::*)();
            if (_q_method_type _q_method = &QPieSeries::sumChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->horizontalPosition(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = _t->verticalPosition(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = _t->pieSize(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = _t->pieStartAngle(); break;
        case 4: *reinterpret_cast< qreal*>(_v) = _t->pieEndAngle(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->count(); break;
        case 6: *reinterpret_cast< qreal*>(_v) = _t->sum(); break;
        case 7: *reinterpret_cast< qreal*>(_v) = _t->holeSize(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setHorizontalPosition(*reinterpret_cast< qreal*>(_v)); break;
        case 1: _t->setVerticalPosition(*reinterpret_cast< qreal*>(_v)); break;
        case 2: _t->setPieSize(*reinterpret_cast< qreal*>(_v)); break;
        case 3: _t->setPieStartAngle(*reinterpret_cast< qreal*>(_v)); break;
        case 4: _t->setPieEndAngle(*reinterpret_cast< qreal*>(_v)); break;
        case 7: _t->setHoleSize(*reinterpret_cast< qreal*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QPieSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QPieSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10QPieSeriesE.stringdata0))
        return static_cast<void*>(this);
    return QAbstractSeries::qt_metacast(_clname);
}

int QPieSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractSeries::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
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
void QPieSeries::added(const QList<QPieSlice*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QPieSeries::removed(const QList<QPieSlice*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QPieSeries::clicked(QPieSlice * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QPieSeries::hovered(QPieSlice * _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QPieSeries::pressed(QPieSlice * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QPieSeries::released(QPieSlice * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QPieSeries::doubleClicked(QPieSlice * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QPieSeries::countChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void QPieSeries::sumChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
