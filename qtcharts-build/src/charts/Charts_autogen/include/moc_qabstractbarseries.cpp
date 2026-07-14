/****************************************************************************
** Meta object code from reading C++ file 'qabstractbarseries.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/barchart/qabstractbarseries.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qabstractbarseries.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN18QAbstractBarSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN18QAbstractBarSeriesE = QtMocHelpers::stringData(
    "QAbstractBarSeries",
    "clicked",
    "",
    "index",
    "QBarSet*",
    "barset",
    "hovered",
    "status",
    "pressed",
    "released",
    "doubleClicked",
    "countChanged",
    "labelsVisibleChanged",
    "labelsFormatChanged",
    "format",
    "labelsPositionChanged",
    "QAbstractBarSeries::LabelsPosition",
    "position",
    "labelsAngleChanged",
    "angle",
    "labelsPrecisionChanged",
    "precision",
    "barsetsAdded",
    "QList<QBarSet*>",
    "sets",
    "barsetsRemoved",
    "barWidth",
    "count",
    "labelsVisible",
    "labelsFormat",
    "labelsPosition",
    "LabelsPosition",
    "labelsAngle",
    "labelsPrecision",
    "LabelsCenter",
    "LabelsInsideEnd",
    "LabelsInsideBase",
    "LabelsOutsideEnd"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN18QAbstractBarSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       7,  139, // properties
       1,  174, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   92,    2, 0x06,    9 /* Public */,
       6,    3,   97,    2, 0x06,   12 /* Public */,
       8,    2,  104,    2, 0x06,   16 /* Public */,
       9,    2,  109,    2, 0x06,   19 /* Public */,
      10,    2,  114,    2, 0x06,   22 /* Public */,
      11,    0,  119,    2, 0x06,   25 /* Public */,
      12,    0,  120,    2, 0x06,   26 /* Public */,
      13,    1,  121,    2, 0x06,   27 /* Public */,
      15,    1,  124,    2, 0x06,   29 /* Public */,
      18,    1,  127,    2, 0x06,   31 /* Public */,
      20,    1,  130,    2, 0x06,   33 /* Public */,
      22,    1,  133,    2, 0x06,   35 /* Public */,
      25,    1,  136,    2, 0x06,   37 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, 0x80000000 | 4,    7,    3,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::QReal,   19,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void, 0x80000000 | 23,   24,

 // properties: name, type, flags, notifyId, revision
      26, QMetaType::QReal, 0x00015103, uint(-1), 0,
      27, QMetaType::Int, 0x00015001, uint(5), 0,
      28, QMetaType::Bool, 0x00015103, uint(6), 0,
      29, QMetaType::QString, 0x00015103, uint(7), 0,
      30, 0x80000000 | 31, 0x0001510b, uint(8), 0,
      32, QMetaType::QReal, 0x00015103, uint(9), 0,
      33, QMetaType::Int, 0x00015103, uint(10), 0,

 // enums: name, alias, flags, count, data
      31,   31, 0x0,    4,  179,

 // enum data: key, value
      34, uint(QAbstractBarSeries::LabelsCenter),
      35, uint(QAbstractBarSeries::LabelsInsideEnd),
      36, uint(QAbstractBarSeries::LabelsInsideBase),
      37, uint(QAbstractBarSeries::LabelsOutsideEnd),

       0        // eod
};

Q_CONSTINIT const QMetaObject QAbstractBarSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractSeries::staticMetaObject>(),
    qt_meta_stringdata_ZN18QAbstractBarSeriesE.offsetsAndSizes,
    qt_meta_data_ZN18QAbstractBarSeriesE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN18QAbstractBarSeriesE_t,
        // property 'barWidth'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'count'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'labelsVisible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'labelsFormat'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'labelsPosition'
        QtPrivate::TypeAndForceComplete<LabelsPosition, std::true_type>,
        // property 'labelsAngle'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'labelsPrecision'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // enum 'LabelsPosition'
        QtPrivate::TypeAndForceComplete<QAbstractBarSeries::LabelsPosition, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QAbstractBarSeries, std::true_type>,
        // method 'clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBarSet *, std::false_type>,
        // method 'hovered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
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
        // method 'countChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'labelsVisibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'labelsFormatChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'labelsPositionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractBarSeries::LabelsPosition, std::false_type>,
        // method 'labelsAngleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qreal, std::false_type>,
        // method 'labelsPrecisionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'barsetsAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QBarSet*> &, std::false_type>,
        // method 'barsetsRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QBarSet*> &, std::false_type>
    >,
    nullptr
} };

void QAbstractBarSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QAbstractBarSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->clicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[2]))); break;
        case 1: _t->hovered((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[3]))); break;
        case 2: _t->pressed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[2]))); break;
        case 3: _t->released((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[2]))); break;
        case 4: _t->doubleClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[2]))); break;
        case 5: _t->countChanged(); break;
        case 6: _t->labelsVisibleChanged(); break;
        case 7: _t->labelsFormatChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->labelsPositionChanged((*reinterpret_cast< std::add_pointer_t<QAbstractBarSeries::LabelsPosition>>(_a[1]))); break;
        case 9: _t->labelsAngleChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 10: _t->labelsPrecisionChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->barsetsAdded((*reinterpret_cast< std::add_pointer_t<QList<QBarSet*>>>(_a[1]))); break;
        case 12: _t->barsetsRemoved((*reinterpret_cast< std::add_pointer_t<QList<QBarSet*>>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QAbstractBarSeries::*)(int , QBarSet * );
            if (_q_method_type _q_method = &QAbstractBarSeries::clicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeries::*)(bool , int , QBarSet * );
            if (_q_method_type _q_method = &QAbstractBarSeries::hovered; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeries::*)(int , QBarSet * );
            if (_q_method_type _q_method = &QAbstractBarSeries::pressed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeries::*)(int , QBarSet * );
            if (_q_method_type _q_method = &QAbstractBarSeries::released; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeries::*)(int , QBarSet * );
            if (_q_method_type _q_method = &QAbstractBarSeries::doubleClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeries::*)();
            if (_q_method_type _q_method = &QAbstractBarSeries::countChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeries::*)();
            if (_q_method_type _q_method = &QAbstractBarSeries::labelsVisibleChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeries::*)(const QString & );
            if (_q_method_type _q_method = &QAbstractBarSeries::labelsFormatChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeries::*)(QAbstractBarSeries::LabelsPosition );
            if (_q_method_type _q_method = &QAbstractBarSeries::labelsPositionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeries::*)(qreal );
            if (_q_method_type _q_method = &QAbstractBarSeries::labelsAngleChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeries::*)(int );
            if (_q_method_type _q_method = &QAbstractBarSeries::labelsPrecisionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeries::*)(const QList<QBarSet*> & );
            if (_q_method_type _q_method = &QAbstractBarSeries::barsetsAdded; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _q_method_type = void (QAbstractBarSeries::*)(const QList<QBarSet*> & );
            if (_q_method_type _q_method = &QAbstractBarSeries::barsetsRemoved; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->barWidth(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->count(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isLabelsVisible(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->labelsFormat(); break;
        case 4: *reinterpret_cast< LabelsPosition*>(_v) = _t->labelsPosition(); break;
        case 5: *reinterpret_cast< qreal*>(_v) = _t->labelsAngle(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->labelsPrecision(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBarWidth(*reinterpret_cast< qreal*>(_v)); break;
        case 2: _t->setLabelsVisible(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setLabelsFormat(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setLabelsPosition(*reinterpret_cast< LabelsPosition*>(_v)); break;
        case 5: _t->setLabelsAngle(*reinterpret_cast< qreal*>(_v)); break;
        case 6: _t->setLabelsPrecision(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QAbstractBarSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QAbstractBarSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN18QAbstractBarSeriesE.stringdata0))
        return static_cast<void*>(this);
    return QAbstractSeries::qt_metacast(_clname);
}

int QAbstractBarSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractSeries::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
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
void QAbstractBarSeries::clicked(int _t1, QBarSet * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QAbstractBarSeries::hovered(bool _t1, int _t2, QBarSet * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QAbstractBarSeries::pressed(int _t1, QBarSet * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QAbstractBarSeries::released(int _t1, QBarSet * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QAbstractBarSeries::doubleClicked(int _t1, QBarSet * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QAbstractBarSeries::countChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QAbstractBarSeries::labelsVisibleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void QAbstractBarSeries::labelsFormatChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QAbstractBarSeries::labelsPositionChanged(QAbstractBarSeries::LabelsPosition _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QAbstractBarSeries::labelsAngleChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QAbstractBarSeries::labelsPrecisionChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void QAbstractBarSeries::barsetsAdded(const QList<QBarSet*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void QAbstractBarSeries::barsetsRemoved(const QList<QBarSet*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_WARNING_POP
