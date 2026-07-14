/****************************************************************************
** Meta object code from reading C++ file 'qlegend.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/legend/qlegend.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qlegend.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN7QLegendE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN7QLegendE = QtMocHelpers::stringData(
    "QLegend",
    "backgroundVisibleChanged",
    "",
    "visible",
    "colorChanged",
    "color",
    "borderColorChanged",
    "fontChanged",
    "font",
    "labelColorChanged",
    "reverseMarkersChanged",
    "reverseMarkers",
    "showToolTipsChanged",
    "showToolTips",
    "markerShapeChanged",
    "MarkerShape",
    "shape",
    "attachedToChartChanged",
    "attachedToChart",
    "interactiveChanged",
    "interactive",
    "alignment",
    "Qt::Alignment",
    "backgroundVisible",
    "borderColor",
    "labelColor",
    "markerShape",
    "MarkerShapeDefault",
    "MarkerShapeRectangle",
    "MarkerShapeCircle",
    "MarkerShapeFromSeries",
    "MarkerShapeRotatedRectangle",
    "MarkerShapeTriangle",
    "MarkerShapeStar",
    "MarkerShapePentagon"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN7QLegendE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       9,  114, // properties
       1,  159, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   84,    2, 0x06,   11 /* Public */,
       4,    1,   87,    2, 0x06,   13 /* Public */,
       6,    1,   90,    2, 0x06,   15 /* Public */,
       7,    1,   93,    2, 0x06,   17 /* Public */,
       9,    1,   96,    2, 0x06,   19 /* Public */,
      10,    1,   99,    2, 0x06,   21 /* Public */,
      12,    1,  102,    2, 0x06,   23 /* Public */,
      14,    1,  105,    2, 0x06,   25 /* Public */,
      17,    1,  108,    2, 0x86,   27 /* Public | MethodRevisioned */,
      19,    1,  111,    2, 0x06,   29 /* Public */,

 // signals: revision
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
    1538,
       0,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QColor,    5,
    QMetaType::Void, QMetaType::QColor,    5,
    QMetaType::Void, QMetaType::QFont,    8,
    QMetaType::Void, QMetaType::QColor,    5,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   20,

 // properties: name, type, flags, notifyId, revision
      21, 0x80000000 | 22, 0x0001510b, uint(-1), 0,
      23, QMetaType::Bool, 0x00015103, uint(0), 0,
       5, QMetaType::QColor, 0x00015103, uint(1), 0,
      24, QMetaType::QColor, 0x00015103, uint(2), 0,
       8, QMetaType::QFont, 0x00015103, uint(3), 0,
      25, QMetaType::QColor, 0x00015103, uint(4), 0,
      11, QMetaType::Bool, 0x00015103, uint(5), 0,
      13, QMetaType::Bool, 0x00015103, uint(6), 0,
      26, 0x80000000 | 15, 0x0001510b, uint(7), 0,

 // enums: name, alias, flags, count, data
      15,   15, 0x0,    8,  164,

 // enum data: key, value
      27, uint(QLegend::MarkerShapeDefault),
      28, uint(QLegend::MarkerShapeRectangle),
      29, uint(QLegend::MarkerShapeCircle),
      30, uint(QLegend::MarkerShapeFromSeries),
      31, uint(QLegend::MarkerShapeRotatedRectangle),
      32, uint(QLegend::MarkerShapeTriangle),
      33, uint(QLegend::MarkerShapeStar),
      34, uint(QLegend::MarkerShapePentagon),

       0        // eod
};

Q_CONSTINIT const QMetaObject QLegend::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsWidget::staticMetaObject>(),
    qt_meta_stringdata_ZN7QLegendE.offsetsAndSizes,
    qt_meta_data_ZN7QLegendE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN7QLegendE_t,
        // property 'alignment'
        QtPrivate::TypeAndForceComplete<Qt::Alignment, std::true_type>,
        // property 'backgroundVisible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'color'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'borderColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'font'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'labelColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'reverseMarkers'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'showToolTips'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'markerShape'
        QtPrivate::TypeAndForceComplete<MarkerShape, std::true_type>,
        // enum 'MarkerShape'
        QtPrivate::TypeAndForceComplete<QLegend::MarkerShape, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QLegend, std::true_type>,
        // method 'backgroundVisibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'colorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'borderColorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'fontChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QFont, std::false_type>,
        // method 'labelColorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'reverseMarkersChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'showToolTipsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'markerShapeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<MarkerShape, std::false_type>,
        // method 'attachedToChartChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'interactiveChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void QLegend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QLegend *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->backgroundVisibleChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->colorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 2: _t->borderColorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 3: _t->fontChanged((*reinterpret_cast< std::add_pointer_t<QFont>>(_a[1]))); break;
        case 4: _t->labelColorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 5: _t->reverseMarkersChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->showToolTipsChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->markerShapeChanged((*reinterpret_cast< std::add_pointer_t<MarkerShape>>(_a[1]))); break;
        case 8: _t->attachedToChartChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->interactiveChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QLegend::*)(bool );
            if (_q_method_type _q_method = &QLegend::backgroundVisibleChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QLegend::*)(QColor );
            if (_q_method_type _q_method = &QLegend::colorChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QLegend::*)(QColor );
            if (_q_method_type _q_method = &QLegend::borderColorChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QLegend::*)(QFont );
            if (_q_method_type _q_method = &QLegend::fontChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QLegend::*)(QColor );
            if (_q_method_type _q_method = &QLegend::labelColorChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QLegend::*)(bool );
            if (_q_method_type _q_method = &QLegend::reverseMarkersChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QLegend::*)(bool );
            if (_q_method_type _q_method = &QLegend::showToolTipsChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (QLegend::*)(MarkerShape );
            if (_q_method_type _q_method = &QLegend::markerShapeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (QLegend::*)(bool );
            if (_q_method_type _q_method = &QLegend::attachedToChartChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (QLegend::*)(bool );
            if (_q_method_type _q_method = &QLegend::interactiveChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Qt::Alignment*>(_v) = _t->alignment(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->isBackgroundVisible(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->color(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->borderColor(); break;
        case 4: *reinterpret_cast< QFont*>(_v) = _t->font(); break;
        case 5: *reinterpret_cast< QColor*>(_v) = _t->labelColor(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->reverseMarkers(); break;
        case 7: *reinterpret_cast< bool*>(_v) = _t->showToolTips(); break;
        case 8: *reinterpret_cast< MarkerShape*>(_v) = _t->markerShape(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAlignment(*reinterpret_cast< Qt::Alignment*>(_v)); break;
        case 1: _t->setBackgroundVisible(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setColor(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setBorderColor(*reinterpret_cast< QColor*>(_v)); break;
        case 4: _t->setFont(*reinterpret_cast< QFont*>(_v)); break;
        case 5: _t->setLabelColor(*reinterpret_cast< QColor*>(_v)); break;
        case 6: _t->setReverseMarkers(*reinterpret_cast< bool*>(_v)); break;
        case 7: _t->setShowToolTips(*reinterpret_cast< bool*>(_v)); break;
        case 8: _t->setMarkerShape(*reinterpret_cast< MarkerShape*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QLegend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QLegend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN7QLegendE.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsWidget::qt_metacast(_clname);
}

int QLegend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void QLegend::backgroundVisibleChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QLegend::colorChanged(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QLegend::borderColorChanged(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QLegend::fontChanged(QFont _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QLegend::labelColorChanged(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QLegend::reverseMarkersChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QLegend::showToolTipsChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QLegend::markerShapeChanged(MarkerShape _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QLegend::attachedToChartChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QLegend::interactiveChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
