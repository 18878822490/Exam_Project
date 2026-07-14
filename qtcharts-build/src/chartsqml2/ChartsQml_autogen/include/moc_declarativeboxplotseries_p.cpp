/****************************************************************************
** Meta object code from reading C++ file 'declarativeboxplotseries_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativeboxplotseries_p.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'declarativeboxplotseries_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN17DeclarativeBoxSetE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN17DeclarativeBoxSetE = QtMocHelpers::stringData(
    "DeclarativeBoxSet",
    "QML.Element",
    "BoxSet",
    "QML.AddedInVersion",
    "259",
    "QML.ExtraVersion",
    "512",
    "changedValues",
    "",
    "changedValue",
    "index",
    "brushFilenameChanged",
    "brushFilename",
    "handleBrushChanged",
    "append",
    "value",
    "clear",
    "at",
    "setValue",
    "values",
    "QVariantList",
    "label",
    "count",
    "ValuePositions",
    "LowerExtreme",
    "LowerQuartile",
    "Median",
    "UpperQuartile",
    "UpperExtreme"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN17DeclarativeBoxSetE[] = {

 // content:
      12,       // revision
       0,       // classname
       3,   14, // classinfo
       8,   20, // methods
       4,   96, // properties
       1,  116, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   76,    8, 0x06,    6 /* Public */,
       9,    1,   77,    8, 0x06,    7 /* Public */,
      11,    1,   80,    8, 0x86,    9 /* Public | MethodRevisioned */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    0,   83,    8, 0x08,   11 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      14,    1,   84,    8, 0x02,   12 /* Public */,
      16,    0,   87,    8, 0x02,   14 /* Public */,
      17,    1,   88,    8, 0x02,   15 /* Public */,
      18,    2,   91,    8, 0x02,   17 /* Public */,

 // signals: revision
       0,
       0,
     260,

 // slots: revision
       0,

 // methods: revision
       0,
       0,
       0,
       0,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::QString,   12,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QReal,   15,
    QMetaType::Void,
    QMetaType::QReal, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::QReal,   10,   15,

 // properties: name, type, flags, notifyId, revision
      19, 0x80000000 | 20, 0x0001510b, uint(-1), 0,
      21, QMetaType::QString, 0x00015103, uint(-1), 0,
      22, QMetaType::Int, 0x00015001, uint(-1), 0,
      12, QMetaType::QString, 0x00015103, uint(2), 260,

 // enums: name, alias, flags, count, data
      23,   23, 0x0,    5,  121,

 // enum data: key, value
      24, uint(DeclarativeBoxSet::LowerExtreme),
      25, uint(DeclarativeBoxSet::LowerQuartile),
      26, uint(DeclarativeBoxSet::Median),
      27, uint(DeclarativeBoxSet::UpperQuartile),
      28, uint(DeclarativeBoxSet::UpperExtreme),

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeBoxSet::staticMetaObject = { {
    QMetaObject::SuperData::link<QBoxSet::staticMetaObject>(),
    qt_meta_stringdata_ZN17DeclarativeBoxSetE.offsetsAndSizes,
    qt_meta_data_ZN17DeclarativeBoxSetE,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'values'
        QVariantList,
        // property 'label'
        QString,
        // property 'count'
        int,
        // property 'brushFilename'
        QString,
        // enum 'ValuePositions'
        DeclarativeBoxSet::ValuePositions,
        // Q_OBJECT / Q_GADGET
        DeclarativeBoxSet,
        // method 'changedValues'
        void,
        // method 'changedValue'
        void,
        int,
        // method 'brushFilenameChanged'
        void,
        const QString &,
        // method 'handleBrushChanged'
        void,
        // method 'append'
        void,
        qreal,
        // method 'clear'
        void,
        // method 'at'
        qreal,
        int,
        // method 'setValue'
        void,
        int,
        qreal
    >,
    nullptr
} };

void DeclarativeBoxSet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeBoxSet *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->changedValues(); break;
        case 1: _t->changedValue((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->brushFilenameChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->handleBrushChanged(); break;
        case 4: _t->append((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 5: _t->clear(); break;
        case 6: { qreal _r = _t->at((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->setValue((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativeBoxSet::*)();
            if (_q_method_type _q_method = &DeclarativeBoxSet::changedValues; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBoxSet::*)(int );
            if (_q_method_type _q_method = &DeclarativeBoxSet::changedValue; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBoxSet::*)(const QString & );
            if (_q_method_type _q_method = &DeclarativeBoxSet::brushFilenameChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariantList*>(_v) = _t->values(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->label(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->count(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->brushFilename(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setValues(*reinterpret_cast< QVariantList*>(_v)); break;
        case 1: _t->setLabel(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setBrushFilename(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *DeclarativeBoxSet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeBoxSet::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN17DeclarativeBoxSetE.stringdata0))
        return static_cast<void*>(this);
    return QBoxSet::qt_metacast(_clname);
}

int DeclarativeBoxSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QBoxSet::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DeclarativeBoxSet::changedValues()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DeclarativeBoxSet::changedValue(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeclarativeBoxSet::brushFilenameChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
namespace {
struct qt_meta_tag_ZN24DeclarativeBoxPlotSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN24DeclarativeBoxPlotSeriesE = QtMocHelpers::stringData(
    "DeclarativeBoxPlotSeries",
    "DefaultProperty",
    "seriesChildren",
    "QML.Element",
    "BoxPlotSeries",
    "QML.AddedInVersion",
    "259",
    "QML.ExtraVersion",
    "512",
    "axisXChanged",
    "",
    "QAbstractAxis*",
    "axis",
    "axisYChanged",
    "axisXTopChanged",
    "axisYRightChanged",
    "clicked",
    "DeclarativeBoxSet*",
    "boxset",
    "hovered",
    "status",
    "pressed",
    "released",
    "doubleClicked",
    "brushFilenameChanged",
    "brushFilename",
    "onHovered",
    "QBoxSet*",
    "onClicked",
    "onPressed",
    "onReleased",
    "onDoubleClicked",
    "handleBrushChanged",
    "at",
    "index",
    "append",
    "label",
    "QVariantList",
    "values",
    "box",
    "insert",
    "remove",
    "clear",
    "axisX",
    "axisY",
    "axisXTop",
    "axisYRight",
    "QQmlListProperty<QObject>"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN24DeclarativeBoxPlotSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       4,   14, // classinfo
      22,   22, // methods
       6,  248, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,
       7,    8,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,  176,   10, 0x06,    7 /* Public */,
      13,    1,  179,   10, 0x06,    9 /* Public */,
      14,    1,  182,   10, 0x06,   11 /* Public */,
      15,    1,  185,   10, 0x06,   13 /* Public */,
      16,    1,  188,   10, 0x06,   15 /* Public */,
      19,    2,  191,   10, 0x06,   17 /* Public */,
      21,    1,  196,   10, 0x06,   20 /* Public */,
      22,    1,  199,   10, 0x06,   22 /* Public */,
      23,    1,  202,   10, 0x06,   24 /* Public */,
      24,    1,  205,   10, 0x86,   26 /* Public | MethodRevisioned */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      26,    2,  208,   10, 0x0a,   28 /* Public */,
      28,    1,  213,   10, 0x0a,   31 /* Public */,
      29,    1,  216,   10, 0x0a,   33 /* Public */,
      30,    1,  219,   10, 0x0a,   35 /* Public */,
      31,    1,  222,   10, 0x0a,   37 /* Public */,
      32,    0,  225,   10, 0x08,   39 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      33,    1,  226,   10, 0x02,   40 /* Public */,
      35,    2,  229,   10, 0x02,   42 /* Public */,
      35,    1,  234,   10, 0x02,   45 /* Public */,
      40,    3,  237,   10, 0x02,   47 /* Public */,
      41,    1,  244,   10, 0x02,   51 /* Public */,
      42,    0,  247,   10, 0x02,   53 /* Public */,

 // signals: revision
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
     260,

 // slots: revision
       0,
       0,
       0,
       0,
       0,
       0,

 // methods: revision
       0,
       0,
       0,
       0,
       0,
       0,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 17,   20,   18,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::QString,   25,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 27,   20,   18,
    QMetaType::Void, 0x80000000 | 27,   18,
    QMetaType::Void, 0x80000000 | 27,   18,
    QMetaType::Void, 0x80000000 | 27,   18,
    QMetaType::Void, 0x80000000 | 27,   18,
    QMetaType::Void,

 // methods: parameters
    0x80000000 | 17, QMetaType::Int,   34,
    0x80000000 | 17, QMetaType::QString, 0x80000000 | 37,   36,   38,
    QMetaType::Void, 0x80000000 | 17,   39,
    0x80000000 | 17, QMetaType::Int, QMetaType::QString, 0x80000000 | 37,   34,   36,   38,
    QMetaType::Bool, 0x80000000 | 17,   39,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      43, 0x80000000 | 11, 0x0001510b, uint(0), 0,
      44, 0x80000000 | 11, 0x0001510b, uint(1), 0,
      45, 0x80000000 | 11, 0x0001510b, uint(2), 0,
      46, 0x80000000 | 11, 0x0001510b, uint(3), 0,
       2, 0x80000000 | 47, 0x00015009, uint(-1), 0,
      25, QMetaType::QString, 0x00015103, uint(9), 260,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeBoxPlotSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QBoxPlotSeries::staticMetaObject>(),
    qt_meta_stringdata_ZN24DeclarativeBoxPlotSeriesE.offsetsAndSizes,
    qt_meta_data_ZN24DeclarativeBoxPlotSeriesE,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'axisX'
        QAbstractAxis*,
        // property 'axisY'
        QAbstractAxis*,
        // property 'axisXTop'
        QAbstractAxis*,
        // property 'axisYRight'
        QAbstractAxis*,
        // property 'seriesChildren'
        QQmlListProperty<QObject>,
        // property 'brushFilename'
        QString,
        // Q_OBJECT / Q_GADGET
        DeclarativeBoxPlotSeries,
        // method 'axisXChanged'
        void,
        QAbstractAxis *,
        // method 'axisYChanged'
        void,
        QAbstractAxis *,
        // method 'axisXTopChanged'
        void,
        QAbstractAxis *,
        // method 'axisYRightChanged'
        void,
        QAbstractAxis *,
        // method 'clicked'
        void,
        DeclarativeBoxSet *,
        // method 'hovered'
        void,
        bool,
        DeclarativeBoxSet *,
        // method 'pressed'
        void,
        DeclarativeBoxSet *,
        // method 'released'
        void,
        DeclarativeBoxSet *,
        // method 'doubleClicked'
        void,
        DeclarativeBoxSet *,
        // method 'brushFilenameChanged'
        void,
        const QString &,
        // method 'onHovered'
        void,
        bool,
        QBoxSet *,
        // method 'onClicked'
        void,
        QBoxSet *,
        // method 'onPressed'
        void,
        QBoxSet *,
        // method 'onReleased'
        void,
        QBoxSet *,
        // method 'onDoubleClicked'
        void,
        QBoxSet *,
        // method 'handleBrushChanged'
        void,
        // method 'at'
        DeclarativeBoxSet *,
        int,
        // method 'append'
        DeclarativeBoxSet *,
        const QString,
        QVariantList,
        // method 'append'
        void,
        DeclarativeBoxSet *,
        // method 'insert'
        DeclarativeBoxSet *,
        int,
        const QString,
        QVariantList,
        // method 'remove'
        bool,
        DeclarativeBoxSet *,
        // method 'clear'
        void
    >,
    nullptr
} };

void DeclarativeBoxPlotSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeBoxPlotSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->axisXChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 1: _t->axisYChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 2: _t->axisXTopChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 3: _t->axisYRightChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 4: _t->clicked((*reinterpret_cast< std::add_pointer_t<DeclarativeBoxSet*>>(_a[1]))); break;
        case 5: _t->hovered((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<DeclarativeBoxSet*>>(_a[2]))); break;
        case 6: _t->pressed((*reinterpret_cast< std::add_pointer_t<DeclarativeBoxSet*>>(_a[1]))); break;
        case 7: _t->released((*reinterpret_cast< std::add_pointer_t<DeclarativeBoxSet*>>(_a[1]))); break;
        case 8: _t->doubleClicked((*reinterpret_cast< std::add_pointer_t<DeclarativeBoxSet*>>(_a[1]))); break;
        case 9: _t->brushFilenameChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->onHovered((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QBoxSet*>>(_a[2]))); break;
        case 11: _t->onClicked((*reinterpret_cast< std::add_pointer_t<QBoxSet*>>(_a[1]))); break;
        case 12: _t->onPressed((*reinterpret_cast< std::add_pointer_t<QBoxSet*>>(_a[1]))); break;
        case 13: _t->onReleased((*reinterpret_cast< std::add_pointer_t<QBoxSet*>>(_a[1]))); break;
        case 14: _t->onDoubleClicked((*reinterpret_cast< std::add_pointer_t<QBoxSet*>>(_a[1]))); break;
        case 15: _t->handleBrushChanged(); break;
        case 16: { DeclarativeBoxSet* _r = _t->at((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< DeclarativeBoxSet**>(_a[0]) = std::move(_r); }  break;
        case 17: { DeclarativeBoxSet* _r = _t->append((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[2])));
            if (_a[0]) *reinterpret_cast< DeclarativeBoxSet**>(_a[0]) = std::move(_r); }  break;
        case 18: _t->append((*reinterpret_cast< std::add_pointer_t<DeclarativeBoxSet*>>(_a[1]))); break;
        case 19: { DeclarativeBoxSet* _r = _t->insert((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[3])));
            if (_a[0]) *reinterpret_cast< DeclarativeBoxSet**>(_a[0]) = std::move(_r); }  break;
        case 20: { bool _r = _t->remove((*reinterpret_cast< std::add_pointer_t<DeclarativeBoxSet*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 21: _t->clear(); break;
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
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DeclarativeBoxSet* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DeclarativeBoxSet* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DeclarativeBoxSet* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DeclarativeBoxSet* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DeclarativeBoxSet* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBoxSet* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBoxSet* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBoxSet* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBoxSet* >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBoxSet* >(); break;
            }
            break;
        case 18:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DeclarativeBoxSet* >(); break;
            }
            break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DeclarativeBoxSet* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativeBoxPlotSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeBoxPlotSeries::axisXChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBoxPlotSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeBoxPlotSeries::axisYChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBoxPlotSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeBoxPlotSeries::axisXTopChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBoxPlotSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeBoxPlotSeries::axisYRightChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBoxPlotSeries::*)(DeclarativeBoxSet * );
            if (_q_method_type _q_method = &DeclarativeBoxPlotSeries::clicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBoxPlotSeries::*)(bool , DeclarativeBoxSet * );
            if (_q_method_type _q_method = &DeclarativeBoxPlotSeries::hovered; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBoxPlotSeries::*)(DeclarativeBoxSet * );
            if (_q_method_type _q_method = &DeclarativeBoxPlotSeries::pressed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBoxPlotSeries::*)(DeclarativeBoxSet * );
            if (_q_method_type _q_method = &DeclarativeBoxPlotSeries::released; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBoxPlotSeries::*)(DeclarativeBoxSet * );
            if (_q_method_type _q_method = &DeclarativeBoxPlotSeries::doubleClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBoxPlotSeries::*)(const QString & );
            if (_q_method_type _q_method = &DeclarativeBoxPlotSeries::brushFilenameChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
        case 2:
        case 1:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractAxis* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QAbstractAxis**>(_v) = _t->axisX(); break;
        case 1: *reinterpret_cast< QAbstractAxis**>(_v) = _t->axisY(); break;
        case 2: *reinterpret_cast< QAbstractAxis**>(_v) = _t->axisXTop(); break;
        case 3: *reinterpret_cast< QAbstractAxis**>(_v) = _t->axisYRight(); break;
        case 4: *reinterpret_cast< QQmlListProperty<QObject>*>(_v) = _t->seriesChildren(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->brushFilename(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAxisX(*reinterpret_cast< QAbstractAxis**>(_v)); break;
        case 1: _t->setAxisY(*reinterpret_cast< QAbstractAxis**>(_v)); break;
        case 2: _t->setAxisXTop(*reinterpret_cast< QAbstractAxis**>(_v)); break;
        case 3: _t->setAxisYRight(*reinterpret_cast< QAbstractAxis**>(_v)); break;
        case 5: _t->setBrushFilename(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *DeclarativeBoxPlotSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeBoxPlotSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN24DeclarativeBoxPlotSeriesE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    return QBoxPlotSeries::qt_metacast(_clname);
}

int DeclarativeBoxPlotSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QBoxPlotSeries::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
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
void DeclarativeBoxPlotSeries::axisXChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeclarativeBoxPlotSeries::axisYChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeclarativeBoxPlotSeries::axisXTopChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DeclarativeBoxPlotSeries::axisYRightChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DeclarativeBoxPlotSeries::clicked(DeclarativeBoxSet * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DeclarativeBoxPlotSeries::hovered(bool _t1, DeclarativeBoxSet * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DeclarativeBoxPlotSeries::pressed(DeclarativeBoxSet * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DeclarativeBoxPlotSeries::released(DeclarativeBoxSet * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void DeclarativeBoxPlotSeries::doubleClicked(DeclarativeBoxSet * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void DeclarativeBoxPlotSeries::brushFilenameChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
