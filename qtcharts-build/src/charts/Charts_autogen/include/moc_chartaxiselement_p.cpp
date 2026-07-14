/****************************************************************************
** Meta object code from reading C++ file 'chartaxiselement_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/charts/axis/chartaxiselement_p.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chartaxiselement_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN16ChartAxisElementE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN16ChartAxisElementE = QtMocHelpers::stringData(
    "ChartAxisElement",
    "clicked",
    "",
    "handleVisibleChanged",
    "visible",
    "handleArrowVisibleChanged",
    "handleGridVisibleChanged",
    "handleLabelsVisibleChanged",
    "handleShadesVisibleChanged",
    "handleLabelsAngleChanged",
    "angle",
    "handleShadesBrushChanged",
    "brush",
    "handleShadesPenChanged",
    "pen",
    "handleArrowPenChanged",
    "handleGridPenChanged",
    "handleMinorArrowPenChanged",
    "handleMinorGridPenChanged",
    "handleMinorGridLineColorChanged",
    "color",
    "handleGridLineColorChanged",
    "handleLabelsBrushChanged",
    "handleLabelsFontChanged",
    "font",
    "handleTitleBrushChanged",
    "handleTitleFontChanged",
    "handleTitleTextChanged",
    "title",
    "handleTitleVisibleChanged",
    "handleRangeChanged",
    "min",
    "max",
    "handleReverseChanged",
    "reverse",
    "handleMinorArrowVisibleChanged",
    "handleMinorGridVisibleChanged",
    "handleLabelsPositionChanged",
    "handleTruncateLabelsChanged",
    "handleColorScaleSizeChanged",
    "handleColorScaleGradientChanged",
    "valueLabelEdited",
    "oldValue",
    "newValue",
    "dateTimeLabelEdited",
    "oldTime",
    "newTime"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN16ChartAxisElementE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  200,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,  201,    2, 0x0a,    2 /* Public */,
       5,    1,  204,    2, 0x0a,    4 /* Public */,
       6,    1,  207,    2, 0x0a,    6 /* Public */,
       7,    1,  210,    2, 0x0a,    8 /* Public */,
       8,    1,  213,    2, 0x0a,   10 /* Public */,
       9,    1,  216,    2, 0x0a,   12 /* Public */,
      11,    1,  219,    2, 0x0a,   14 /* Public */,
      13,    1,  222,    2, 0x0a,   16 /* Public */,
      15,    1,  225,    2, 0x0a,   18 /* Public */,
      16,    1,  228,    2, 0x0a,   20 /* Public */,
      17,    1,  231,    2, 0x0a,   22 /* Public */,
      18,    1,  234,    2, 0x0a,   24 /* Public */,
      19,    1,  237,    2, 0x0a,   26 /* Public */,
      21,    1,  240,    2, 0x0a,   28 /* Public */,
      22,    1,  243,    2, 0x0a,   30 /* Public */,
      23,    1,  246,    2, 0x0a,   32 /* Public */,
      25,    1,  249,    2, 0x0a,   34 /* Public */,
      26,    1,  252,    2, 0x0a,   36 /* Public */,
      27,    1,  255,    2, 0x0a,   38 /* Public */,
      29,    1,  258,    2, 0x0a,   40 /* Public */,
      30,    2,  261,    2, 0x0a,   42 /* Public */,
      33,    1,  266,    2, 0x0a,   45 /* Public */,
      35,    1,  269,    2, 0x0a,   47 /* Public */,
      36,    1,  272,    2, 0x0a,   49 /* Public */,
      37,    0,  275,    2, 0x0a,   51 /* Public */,
      38,    0,  276,    2, 0x0a,   52 /* Public */,
      39,    0,  277,    2, 0x0a,   53 /* Public */,
      40,    0,  278,    2, 0x0a,   54 /* Public */,
      41,    2,  279,    2, 0x0a,   55 /* Public */,
      44,    2,  284,    2, 0x0a,   58 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::QBrush,   12,
    QMetaType::Void, QMetaType::QPen,   14,
    QMetaType::Void, QMetaType::QPen,   14,
    QMetaType::Void, QMetaType::QPen,   14,
    QMetaType::Void, QMetaType::QPen,   14,
    QMetaType::Void, QMetaType::QPen,   14,
    QMetaType::Void, QMetaType::QColor,   20,
    QMetaType::Void, QMetaType::QColor,   20,
    QMetaType::Void, QMetaType::QBrush,   12,
    QMetaType::Void, QMetaType::QFont,   24,
    QMetaType::Void, QMetaType::QBrush,   12,
    QMetaType::Void, QMetaType::QFont,   24,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,   31,   32,
    QMetaType::Void, QMetaType::Bool,   34,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,   42,   43,
    QMetaType::Void, QMetaType::QDateTime, QMetaType::QDateTime,   45,   46,

       0        // eod
};

Q_CONSTINIT const QMetaObject ChartAxisElement::staticMetaObject = { {
    QMetaObject::SuperData::link<ChartElement::staticMetaObject>(),
    qt_meta_stringdata_ZN16ChartAxisElementE.offsetsAndSizes,
    qt_meta_data_ZN16ChartAxisElementE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN16ChartAxisElementE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ChartAxisElement, std::true_type>,
        // method 'clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleVisibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handleArrowVisibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handleGridVisibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handleLabelsVisibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handleShadesVisibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handleLabelsAngleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handleShadesBrushChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QBrush &, std::false_type>,
        // method 'handleShadesPenChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPen &, std::false_type>,
        // method 'handleArrowPenChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPen &, std::false_type>,
        // method 'handleGridPenChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPen &, std::false_type>,
        // method 'handleMinorArrowPenChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPen &, std::false_type>,
        // method 'handleMinorGridPenChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPen &, std::false_type>,
        // method 'handleMinorGridLineColorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QColor &, std::false_type>,
        // method 'handleGridLineColorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QColor &, std::false_type>,
        // method 'handleLabelsBrushChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QBrush &, std::false_type>,
        // method 'handleLabelsFontChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QFont &, std::false_type>,
        // method 'handleTitleBrushChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QBrush &, std::false_type>,
        // method 'handleTitleFontChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QFont &, std::false_type>,
        // method 'handleTitleTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'handleTitleVisibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handleRangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qreal, std::false_type>,
        QtPrivate::TypeAndForceComplete<qreal, std::false_type>,
        // method 'handleReverseChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handleMinorArrowVisibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handleMinorGridVisibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handleLabelsPositionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleTruncateLabelsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleColorScaleSizeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleColorScaleGradientChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'valueLabelEdited'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qreal, std::false_type>,
        QtPrivate::TypeAndForceComplete<qreal, std::false_type>,
        // method 'dateTimeLabelEdited'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDateTime &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDateTime &, std::false_type>
    >,
    nullptr
} };

void ChartAxisElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ChartAxisElement *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->handleVisibleChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->handleArrowVisibleChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->handleGridVisibleChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->handleLabelsVisibleChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->handleShadesVisibleChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->handleLabelsAngleChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->handleShadesBrushChanged((*reinterpret_cast< std::add_pointer_t<QBrush>>(_a[1]))); break;
        case 8: _t->handleShadesPenChanged((*reinterpret_cast< std::add_pointer_t<QPen>>(_a[1]))); break;
        case 9: _t->handleArrowPenChanged((*reinterpret_cast< std::add_pointer_t<QPen>>(_a[1]))); break;
        case 10: _t->handleGridPenChanged((*reinterpret_cast< std::add_pointer_t<QPen>>(_a[1]))); break;
        case 11: _t->handleMinorArrowPenChanged((*reinterpret_cast< std::add_pointer_t<QPen>>(_a[1]))); break;
        case 12: _t->handleMinorGridPenChanged((*reinterpret_cast< std::add_pointer_t<QPen>>(_a[1]))); break;
        case 13: _t->handleMinorGridLineColorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 14: _t->handleGridLineColorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 15: _t->handleLabelsBrushChanged((*reinterpret_cast< std::add_pointer_t<QBrush>>(_a[1]))); break;
        case 16: _t->handleLabelsFontChanged((*reinterpret_cast< std::add_pointer_t<QFont>>(_a[1]))); break;
        case 17: _t->handleTitleBrushChanged((*reinterpret_cast< std::add_pointer_t<QBrush>>(_a[1]))); break;
        case 18: _t->handleTitleFontChanged((*reinterpret_cast< std::add_pointer_t<QFont>>(_a[1]))); break;
        case 19: _t->handleTitleTextChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->handleTitleVisibleChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 21: _t->handleRangeChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[2]))); break;
        case 22: _t->handleReverseChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 23: _t->handleMinorArrowVisibleChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 24: _t->handleMinorGridVisibleChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 25: _t->handleLabelsPositionChanged(); break;
        case 26: _t->handleTruncateLabelsChanged(); break;
        case 27: _t->handleColorScaleSizeChanged(); break;
        case 28: _t->handleColorScaleGradientChanged(); break;
        case 29: _t->valueLabelEdited((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[2]))); break;
        case 30: _t->dateTimeLabelEdited((*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (ChartAxisElement::*)();
            if (_q_method_type _q_method = &ChartAxisElement::clicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *ChartAxisElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChartAxisElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN16ChartAxisElementE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsLayoutItem"))
        return static_cast< QGraphicsLayoutItem*>(this);
    return ChartElement::qt_metacast(_clname);
}

int ChartAxisElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ChartElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 31)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 31;
    }
    return _id;
}

// SIGNAL 0
void ChartAxisElement::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
