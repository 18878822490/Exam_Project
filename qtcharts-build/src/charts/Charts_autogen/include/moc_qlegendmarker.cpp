/****************************************************************************
** Meta object code from reading C++ file 'qlegendmarker.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qlegendmarker.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qlegendmarker.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13QLegendMarkerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13QLegendMarkerE = QtMocHelpers::stringData(
    "QLegendMarker",
    "clicked",
    "",
    "hovered",
    "status",
    "labelChanged",
    "labelBrushChanged",
    "fontChanged",
    "penChanged",
    "brushChanged",
    "visibleChanged",
    "shapeChanged",
    "label",
    "labelBrush",
    "font",
    "pen",
    "brush",
    "visible",
    "shape",
    "QLegend::MarkerShape",
    "LegendMarkerType",
    "LegendMarkerTypeArea",
    "LegendMarkerTypeBar",
    "LegendMarkerTypePie",
    "LegendMarkerTypeXY",
    "LegendMarkerTypeBoxPlot",
    "LegendMarkerTypeCandlestick"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13QLegendMarkerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       7,   79, // properties
       1,  114, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x06,    9 /* Public */,
       3,    1,   69,    2, 0x06,   10 /* Public */,
       5,    0,   72,    2, 0x06,   12 /* Public */,
       6,    0,   73,    2, 0x06,   13 /* Public */,
       7,    0,   74,    2, 0x06,   14 /* Public */,
       8,    0,   75,    2, 0x06,   15 /* Public */,
       9,    0,   76,    2, 0x06,   16 /* Public */,
      10,    0,   77,    2, 0x06,   17 /* Public */,
      11,    0,   78,    2, 0x06,   18 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      12, QMetaType::QString, 0x00015103, uint(2), 0,
      13, QMetaType::QBrush, 0x00015103, uint(3), 0,
      14, QMetaType::QFont, 0x00015103, uint(4), 0,
      15, QMetaType::QPen, 0x00015103, uint(5), 0,
      16, QMetaType::QBrush, 0x00015103, uint(6), 0,
      17, QMetaType::Bool, 0x00015103, uint(7), 0,
      18, 0x80000000 | 19, 0x0001510b, uint(8), 0,

 // enums: name, alias, flags, count, data
      20,   20, 0x0,    6,  119,

 // enum data: key, value
      21, uint(QLegendMarker::LegendMarkerTypeArea),
      22, uint(QLegendMarker::LegendMarkerTypeBar),
      23, uint(QLegendMarker::LegendMarkerTypePie),
      24, uint(QLegendMarker::LegendMarkerTypeXY),
      25, uint(QLegendMarker::LegendMarkerTypeBoxPlot),
      26, uint(QLegendMarker::LegendMarkerTypeCandlestick),

       0        // eod
};

Q_CONSTINIT static const QMetaObject::SuperData qt_meta_extradata_ZN13QLegendMarkerE[] = {
    QMetaObject::SuperData::link<QLegend::staticMetaObject>(),
    nullptr
};

Q_CONSTINIT const QMetaObject QLegendMarker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN13QLegendMarkerE.offsetsAndSizes,
    qt_meta_data_ZN13QLegendMarkerE,
    qt_static_metacall,
    qt_meta_extradata_ZN13QLegendMarkerE,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13QLegendMarkerE_t,
        // property 'label'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'labelBrush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'font'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'visible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'shape'
        QtPrivate::TypeAndForceComplete<QLegend::MarkerShape, std::true_type>,
        // enum 'LegendMarkerType'
        QtPrivate::TypeAndForceComplete<QLegendMarker::LegendMarkerType, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QLegendMarker, std::true_type>,
        // method 'clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hovered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'labelChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'labelBrushChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fontChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'penChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'brushChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'visibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'shapeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QLegendMarker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QLegendMarker *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->hovered((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->labelChanged(); break;
        case 3: _t->labelBrushChanged(); break;
        case 4: _t->fontChanged(); break;
        case 5: _t->penChanged(); break;
        case 6: _t->brushChanged(); break;
        case 7: _t->visibleChanged(); break;
        case 8: _t->shapeChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QLegendMarker::*)();
            if (_q_method_type _q_method = &QLegendMarker::clicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QLegendMarker::*)(bool );
            if (_q_method_type _q_method = &QLegendMarker::hovered; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QLegendMarker::*)();
            if (_q_method_type _q_method = &QLegendMarker::labelChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QLegendMarker::*)();
            if (_q_method_type _q_method = &QLegendMarker::labelBrushChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QLegendMarker::*)();
            if (_q_method_type _q_method = &QLegendMarker::fontChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QLegendMarker::*)();
            if (_q_method_type _q_method = &QLegendMarker::penChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QLegendMarker::*)();
            if (_q_method_type _q_method = &QLegendMarker::brushChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (QLegendMarker::*)();
            if (_q_method_type _q_method = &QLegendMarker::visibleChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (QLegendMarker::*)();
            if (_q_method_type _q_method = &QLegendMarker::shapeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->label(); break;
        case 1: *reinterpret_cast< QBrush*>(_v) = _t->labelBrush(); break;
        case 2: *reinterpret_cast< QFont*>(_v) = _t->font(); break;
        case 3: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 4: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->isVisible(); break;
        case 6: *reinterpret_cast< QLegend::MarkerShape*>(_v) = _t->shape(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setLabel(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setLabelBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 2: _t->setFont(*reinterpret_cast< QFont*>(_v)); break;
        case 3: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 4: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 5: _t->setVisible(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setShape(*reinterpret_cast< QLegend::MarkerShape*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QLegendMarker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QLegendMarker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN13QLegendMarkerE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QLegendMarker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
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
void QLegendMarker::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QLegendMarker::hovered(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QLegendMarker::labelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QLegendMarker::labelBrushChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QLegendMarker::fontChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QLegendMarker::penChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QLegendMarker::brushChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void QLegendMarker::visibleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void QLegendMarker::shapeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
