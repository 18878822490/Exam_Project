/****************************************************************************
** Meta object code from reading C++ file 'qhboxplotmodelmapper.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/boxplotchart/qhboxplotmodelmapper.h"
#include <QtCharts/qboxplotseries.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qhboxplotmodelmapper.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN20QHBoxPlotModelMapperE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN20QHBoxPlotModelMapperE = QtMocHelpers::stringData(
    "QHBoxPlotModelMapper",
    "seriesReplaced",
    "",
    "modelReplaced",
    "firstBoxSetRowChanged",
    "lastBoxSetRowChanged",
    "firstColumnChanged",
    "columnCountChanged",
    "series",
    "QBoxPlotSeries*",
    "model",
    "QAbstractItemModel*",
    "firstBoxSetRow",
    "lastBoxSetRow",
    "firstColumn",
    "columnCount"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN20QHBoxPlotModelMapperE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       6,   56, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    7 /* Public */,
       3,    0,   51,    2, 0x06,    8 /* Public */,
       4,    0,   52,    2, 0x06,    9 /* Public */,
       5,    0,   53,    2, 0x06,   10 /* Public */,
       6,    0,   54,    2, 0x06,   11 /* Public */,
       7,    0,   55,    2, 0x06,   12 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
       8, 0x80000000 | 9, 0x0001510b, uint(0), 0,
      10, 0x80000000 | 11, 0x0001510b, uint(1), 0,
      12, QMetaType::Int, 0x00015103, uint(2), 0,
      13, QMetaType::Int, 0x00015103, uint(3), 0,
      14, QMetaType::Int, 0x00015103, uint(4), 0,
      15, QMetaType::Int, 0x00015103, uint(5), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QHBoxPlotModelMapper::staticMetaObject = { {
    QMetaObject::SuperData::link<QBoxPlotModelMapper::staticMetaObject>(),
    qt_meta_stringdata_ZN20QHBoxPlotModelMapperE.offsetsAndSizes,
    qt_meta_data_ZN20QHBoxPlotModelMapperE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN20QHBoxPlotModelMapperE_t,
        // property 'series'
        QtPrivate::TypeAndForceComplete<QBoxPlotSeries*, std::true_type>,
        // property 'model'
        QtPrivate::TypeAndForceComplete<QAbstractItemModel*, std::true_type>,
        // property 'firstBoxSetRow'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'lastBoxSetRow'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'firstColumn'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'columnCount'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QHBoxPlotModelMapper, std::true_type>,
        // method 'seriesReplaced'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'modelReplaced'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'firstBoxSetRowChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'lastBoxSetRowChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'firstColumnChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'columnCountChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QHBoxPlotModelMapper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QHBoxPlotModelMapper *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->seriesReplaced(); break;
        case 1: _t->modelReplaced(); break;
        case 2: _t->firstBoxSetRowChanged(); break;
        case 3: _t->lastBoxSetRowChanged(); break;
        case 4: _t->firstColumnChanged(); break;
        case 5: _t->columnCountChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QHBoxPlotModelMapper::*)();
            if (_q_method_type _q_method = &QHBoxPlotModelMapper::seriesReplaced; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QHBoxPlotModelMapper::*)();
            if (_q_method_type _q_method = &QHBoxPlotModelMapper::modelReplaced; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QHBoxPlotModelMapper::*)();
            if (_q_method_type _q_method = &QHBoxPlotModelMapper::firstBoxSetRowChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QHBoxPlotModelMapper::*)();
            if (_q_method_type _q_method = &QHBoxPlotModelMapper::lastBoxSetRowChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QHBoxPlotModelMapper::*)();
            if (_q_method_type _q_method = &QHBoxPlotModelMapper::firstColumnChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QHBoxPlotModelMapper::*)();
            if (_q_method_type _q_method = &QHBoxPlotModelMapper::columnCountChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QBoxPlotSeries**>(_v) = _t->series(); break;
        case 1: *reinterpret_cast< QAbstractItemModel**>(_v) = _t->model(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->firstBoxSetRow(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->lastBoxSetRow(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->firstColumn(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->columnCount(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSeries(*reinterpret_cast< QBoxPlotSeries**>(_v)); break;
        case 1: _t->setModel(*reinterpret_cast< QAbstractItemModel**>(_v)); break;
        case 2: _t->setFirstBoxSetRow(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setLastBoxSetRow(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setFirstColumn(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setColumnCount(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QHBoxPlotModelMapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QHBoxPlotModelMapper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN20QHBoxPlotModelMapperE.stringdata0))
        return static_cast<void*>(this);
    return QBoxPlotModelMapper::qt_metacast(_clname);
}

int QHBoxPlotModelMapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QBoxPlotModelMapper::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
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
void QHBoxPlotModelMapper::seriesReplaced()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QHBoxPlotModelMapper::modelReplaced()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QHBoxPlotModelMapper::firstBoxSetRowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QHBoxPlotModelMapper::lastBoxSetRowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QHBoxPlotModelMapper::firstColumnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QHBoxPlotModelMapper::columnCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
