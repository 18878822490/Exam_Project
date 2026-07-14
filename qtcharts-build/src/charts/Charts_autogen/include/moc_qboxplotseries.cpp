/****************************************************************************
** Meta object code from reading C++ file 'qboxplotseries.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/boxplotchart/qboxplotseries.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qboxplotseries.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14QBoxPlotSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN14QBoxPlotSeriesE = QtMocHelpers::stringData(
    "QBoxPlotSeries",
    "clicked",
    "",
    "QBoxSet*",
    "boxset",
    "hovered",
    "status",
    "pressed",
    "released",
    "doubleClicked",
    "countChanged",
    "penChanged",
    "brushChanged",
    "boxOutlineVisibilityChanged",
    "boxWidthChanged",
    "boxsetsAdded",
    "QList<QBoxSet*>",
    "sets",
    "boxsetsRemoved",
    "boxOutlineVisible",
    "boxWidth",
    "pen",
    "brush",
    "count"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN14QBoxPlotSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       5,  114, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   86,    2, 0x06,    6 /* Public */,
       5,    2,   89,    2, 0x06,    8 /* Public */,
       7,    1,   94,    2, 0x06,   11 /* Public */,
       8,    1,   97,    2, 0x06,   13 /* Public */,
       9,    1,  100,    2, 0x06,   15 /* Public */,
      10,    0,  103,    2, 0x06,   17 /* Public */,
      11,    0,  104,    2, 0x06,   18 /* Public */,
      12,    0,  105,    2, 0x06,   19 /* Public */,
      13,    0,  106,    2, 0x06,   20 /* Public */,
      14,    0,  107,    2, 0x06,   21 /* Public */,
      15,    1,  108,    2, 0x06,   22 /* Public */,
      18,    1,  111,    2, 0x06,   24 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 3,    6,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,

 // properties: name, type, flags, notifyId, revision
      19, QMetaType::Bool, 0x00015103, uint(8), 0,
      20, QMetaType::QReal, 0x00015103, uint(9), 0,
      21, QMetaType::QPen, 0x00015103, uint(6), 0,
      22, QMetaType::QBrush, 0x00015103, uint(7), 0,
      23, QMetaType::Int, 0x00015001, uint(5), 512,

       0        // eod
};

Q_CONSTINIT const QMetaObject QBoxPlotSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractSeries::staticMetaObject>(),
    qt_meta_stringdata_ZN14QBoxPlotSeriesE.offsetsAndSizes,
    qt_meta_data_ZN14QBoxPlotSeriesE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN14QBoxPlotSeriesE_t,
        // property 'boxOutlineVisible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'boxWidth'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'count'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QBoxPlotSeries, std::true_type>,
        // method 'clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBoxSet *, std::false_type>,
        // method 'hovered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBoxSet *, std::false_type>,
        // method 'pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBoxSet *, std::false_type>,
        // method 'released'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBoxSet *, std::false_type>,
        // method 'doubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QBoxSet *, std::false_type>,
        // method 'countChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'penChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'brushChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'boxOutlineVisibilityChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'boxWidthChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'boxsetsAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QBoxSet*> &, std::false_type>,
        // method 'boxsetsRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QBoxSet*> &, std::false_type>
    >,
    nullptr
} };

void QBoxPlotSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QBoxPlotSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->clicked((*reinterpret_cast< std::add_pointer_t<QBoxSet*>>(_a[1]))); break;
        case 1: _t->hovered((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QBoxSet*>>(_a[2]))); break;
        case 2: _t->pressed((*reinterpret_cast< std::add_pointer_t<QBoxSet*>>(_a[1]))); break;
        case 3: _t->released((*reinterpret_cast< std::add_pointer_t<QBoxSet*>>(_a[1]))); break;
        case 4: _t->doubleClicked((*reinterpret_cast< std::add_pointer_t<QBoxSet*>>(_a[1]))); break;
        case 5: _t->countChanged(); break;
        case 6: _t->penChanged(); break;
        case 7: _t->brushChanged(); break;
        case 8: _t->boxOutlineVisibilityChanged(); break;
        case 9: _t->boxWidthChanged(); break;
        case 10: _t->boxsetsAdded((*reinterpret_cast< std::add_pointer_t<QList<QBoxSet*>>>(_a[1]))); break;
        case 11: _t->boxsetsRemoved((*reinterpret_cast< std::add_pointer_t<QList<QBoxSet*>>>(_a[1]))); break;
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
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBoxSet* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBoxSet* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBoxSet* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBoxSet* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBoxSet* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QBoxSet*> >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QBoxSet*> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QBoxPlotSeries::*)(QBoxSet * );
            if (_q_method_type _q_method = &QBoxPlotSeries::clicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QBoxPlotSeries::*)(bool , QBoxSet * );
            if (_q_method_type _q_method = &QBoxPlotSeries::hovered; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QBoxPlotSeries::*)(QBoxSet * );
            if (_q_method_type _q_method = &QBoxPlotSeries::pressed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QBoxPlotSeries::*)(QBoxSet * );
            if (_q_method_type _q_method = &QBoxPlotSeries::released; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QBoxPlotSeries::*)(QBoxSet * );
            if (_q_method_type _q_method = &QBoxPlotSeries::doubleClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QBoxPlotSeries::*)();
            if (_q_method_type _q_method = &QBoxPlotSeries::countChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QBoxPlotSeries::*)();
            if (_q_method_type _q_method = &QBoxPlotSeries::penChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (QBoxPlotSeries::*)();
            if (_q_method_type _q_method = &QBoxPlotSeries::brushChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (QBoxPlotSeries::*)();
            if (_q_method_type _q_method = &QBoxPlotSeries::boxOutlineVisibilityChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (QBoxPlotSeries::*)();
            if (_q_method_type _q_method = &QBoxPlotSeries::boxWidthChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _q_method_type = void (QBoxPlotSeries::*)(const QList<QBoxSet*> & );
            if (_q_method_type _q_method = &QBoxPlotSeries::boxsetsAdded; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _q_method_type = void (QBoxPlotSeries::*)(const QList<QBoxSet*> & );
            if (_q_method_type _q_method = &QBoxPlotSeries::boxsetsRemoved; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->boxOutlineVisible(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = _t->boxWidth(); break;
        case 2: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 3: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->count(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBoxOutlineVisible(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setBoxWidth(*reinterpret_cast< qreal*>(_v)); break;
        case 2: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 3: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QBoxPlotSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QBoxPlotSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN14QBoxPlotSeriesE.stringdata0))
        return static_cast<void*>(this);
    return QAbstractSeries::qt_metacast(_clname);
}

int QBoxPlotSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractSeries::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
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
void QBoxPlotSeries::clicked(QBoxSet * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QBoxPlotSeries::hovered(bool _t1, QBoxSet * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QBoxPlotSeries::pressed(QBoxSet * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QBoxPlotSeries::released(QBoxSet * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QBoxPlotSeries::doubleClicked(QBoxSet * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QBoxPlotSeries::countChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QBoxPlotSeries::penChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void QBoxPlotSeries::brushChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void QBoxPlotSeries::boxOutlineVisibilityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void QBoxPlotSeries::boxWidthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void QBoxPlotSeries::boxsetsAdded(const QList<QBoxSet*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void QBoxPlotSeries::boxsetsRemoved(const QList<QBoxSet*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_WARNING_POP
