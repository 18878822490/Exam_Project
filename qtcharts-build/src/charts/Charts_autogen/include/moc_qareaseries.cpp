/****************************************************************************
** Meta object code from reading C++ file 'qareaseries.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/areachart/qareaseries.h"
#include <QtCharts/qlineseries.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qareaseries.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11QAreaSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN11QAreaSeriesE = QtMocHelpers::stringData(
    "QAreaSeries",
    "clicked",
    "",
    "point",
    "hovered",
    "state",
    "pressed",
    "released",
    "doubleClicked",
    "selected",
    "colorChanged",
    "color",
    "borderColorChanged",
    "pointLabelsFormatChanged",
    "format",
    "pointLabelsVisibilityChanged",
    "visible",
    "pointLabelsFontChanged",
    "font",
    "pointLabelsColorChanged",
    "pointLabelsClippingChanged",
    "clipping",
    "upperSeries",
    "QLineSeries*",
    "lowerSeries",
    "borderColor",
    "pointLabelsFormat",
    "pointLabelsVisible",
    "pointLabelsFont",
    "pointLabelsColor",
    "pointLabelsClipping"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN11QAreaSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       9,  131, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   92,    2, 0x06,   10 /* Public */,
       4,    2,   95,    2, 0x06,   12 /* Public */,
       6,    1,  100,    2, 0x06,   15 /* Public */,
       7,    1,  103,    2, 0x06,   17 /* Public */,
       8,    1,  106,    2, 0x06,   19 /* Public */,
       9,    0,  109,    2, 0x06,   21 /* Public */,
      10,    1,  110,    2, 0x06,   22 /* Public */,
      12,    1,  113,    2, 0x06,   24 /* Public */,
      13,    1,  116,    2, 0x06,   26 /* Public */,
      15,    1,  119,    2, 0x06,   28 /* Public */,
      17,    1,  122,    2, 0x06,   30 /* Public */,
      19,    1,  125,    2, 0x06,   32 /* Public */,
      20,    1,  128,    2, 0x06,   34 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPointF,    3,
    QMetaType::Void, QMetaType::QPointF, QMetaType::Bool,    3,    5,
    QMetaType::Void, QMetaType::QPointF,    3,
    QMetaType::Void, QMetaType::QPointF,    3,
    QMetaType::Void, QMetaType::QPointF,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,   11,
    QMetaType::Void, QMetaType::QColor,   11,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::QFont,   18,
    QMetaType::Void, QMetaType::QColor,   11,
    QMetaType::Void, QMetaType::Bool,   21,

 // properties: name, type, flags, notifyId, revision
      22, 0x80000000 | 23, 0x00015009, uint(-1), 0,
      24, 0x80000000 | 23, 0x00015009, uint(-1), 0,
      11, QMetaType::QColor, 0x00015103, uint(6), 0,
      25, QMetaType::QColor, 0x00015103, uint(7), 0,
      26, QMetaType::QString, 0x00015103, uint(8), 0,
      27, QMetaType::Bool, 0x00015103, uint(9), 0,
      28, QMetaType::QFont, 0x00015103, uint(10), 0,
      29, QMetaType::QColor, 0x00015103, uint(11), 0,
      30, QMetaType::Bool, 0x00015103, uint(12), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QAreaSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractSeries::staticMetaObject>(),
    qt_meta_stringdata_ZN11QAreaSeriesE.offsetsAndSizes,
    qt_meta_data_ZN11QAreaSeriesE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN11QAreaSeriesE_t,
        // property 'upperSeries'
        QtPrivate::TypeAndForceComplete<QLineSeries*, std::true_type>,
        // property 'lowerSeries'
        QtPrivate::TypeAndForceComplete<QLineSeries*, std::true_type>,
        // property 'color'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'borderColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'pointLabelsFormat'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'pointLabelsVisible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'pointLabelsFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'pointLabelsColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'pointLabelsClipping'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QAreaSeries, std::true_type>,
        // method 'clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        // method 'hovered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        // method 'released'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        // method 'doubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        // method 'selected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'colorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'borderColorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'pointLabelsFormatChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'pointLabelsVisibilityChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'pointLabelsFontChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QFont &, std::false_type>,
        // method 'pointLabelsColorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QColor &, std::false_type>,
        // method 'pointLabelsClippingChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void QAreaSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QAreaSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->clicked((*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[1]))); break;
        case 1: _t->hovered((*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 2: _t->pressed((*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[1]))); break;
        case 3: _t->released((*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[1]))); break;
        case 4: _t->doubleClicked((*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[1]))); break;
        case 5: _t->selected(); break;
        case 6: _t->colorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 7: _t->borderColorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 8: _t->pointLabelsFormatChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->pointLabelsVisibilityChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 10: _t->pointLabelsFontChanged((*reinterpret_cast< std::add_pointer_t<QFont>>(_a[1]))); break;
        case 11: _t->pointLabelsColorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 12: _t->pointLabelsClippingChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QAreaSeries::*)(const QPointF & );
            if (_q_method_type _q_method = &QAreaSeries::clicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QAreaSeries::*)(const QPointF & , bool );
            if (_q_method_type _q_method = &QAreaSeries::hovered; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QAreaSeries::*)(const QPointF & );
            if (_q_method_type _q_method = &QAreaSeries::pressed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QAreaSeries::*)(const QPointF & );
            if (_q_method_type _q_method = &QAreaSeries::released; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QAreaSeries::*)(const QPointF & );
            if (_q_method_type _q_method = &QAreaSeries::doubleClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QAreaSeries::*)();
            if (_q_method_type _q_method = &QAreaSeries::selected; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QAreaSeries::*)(QColor );
            if (_q_method_type _q_method = &QAreaSeries::colorChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (QAreaSeries::*)(QColor );
            if (_q_method_type _q_method = &QAreaSeries::borderColorChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (QAreaSeries::*)(const QString & );
            if (_q_method_type _q_method = &QAreaSeries::pointLabelsFormatChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (QAreaSeries::*)(bool );
            if (_q_method_type _q_method = &QAreaSeries::pointLabelsVisibilityChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _q_method_type = void (QAreaSeries::*)(const QFont & );
            if (_q_method_type _q_method = &QAreaSeries::pointLabelsFontChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _q_method_type = void (QAreaSeries::*)(const QColor & );
            if (_q_method_type _q_method = &QAreaSeries::pointLabelsColorChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _q_method_type = void (QAreaSeries::*)(bool );
            if (_q_method_type _q_method = &QAreaSeries::pointLabelsClippingChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QLineSeries**>(_v) = _t->upperSeries(); break;
        case 1: *reinterpret_cast< QLineSeries**>(_v) = _t->lowerSeries(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->color(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->borderColor(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->pointLabelsFormat(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->pointLabelsVisible(); break;
        case 6: *reinterpret_cast< QFont*>(_v) = _t->pointLabelsFont(); break;
        case 7: *reinterpret_cast< QColor*>(_v) = _t->pointLabelsColor(); break;
        case 8: *reinterpret_cast< bool*>(_v) = _t->pointLabelsClipping(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setColor(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setBorderColor(*reinterpret_cast< QColor*>(_v)); break;
        case 4: _t->setPointLabelsFormat(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setPointLabelsVisible(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setPointLabelsFont(*reinterpret_cast< QFont*>(_v)); break;
        case 7: _t->setPointLabelsColor(*reinterpret_cast< QColor*>(_v)); break;
        case 8: _t->setPointLabelsClipping(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *QAreaSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QAreaSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN11QAreaSeriesE.stringdata0))
        return static_cast<void*>(this);
    return QAbstractSeries::qt_metacast(_clname);
}

int QAreaSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void QAreaSeries::clicked(const QPointF & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QAreaSeries::hovered(const QPointF & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QAreaSeries::pressed(const QPointF & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QAreaSeries::released(const QPointF & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QAreaSeries::doubleClicked(const QPointF & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QAreaSeries::selected()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QAreaSeries::colorChanged(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QAreaSeries::borderColorChanged(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QAreaSeries::pointLabelsFormatChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QAreaSeries::pointLabelsVisibilityChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QAreaSeries::pointLabelsFontChanged(const QFont & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void QAreaSeries::pointLabelsColorChanged(const QColor & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void QAreaSeries::pointLabelsClippingChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_WARNING_POP
