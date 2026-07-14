/****************************************************************************
** Meta object code from reading C++ file 'declarativecandlestickseries_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativecandlestickseries_p.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'declarativecandlestickseries_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN25DeclarativeCandlestickSetE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN25DeclarativeCandlestickSetE = QtMocHelpers::stringData(
    "DeclarativeCandlestickSet",
    "QML.Element",
    "CandlestickSet",
    "QML.AddedInVersion",
    "514",
    "brushFilenameChanged",
    "",
    "brushFilename",
    "handleBrushChanged"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN25DeclarativeCandlestickSetE[] = {

 // content:
      12,       // revision
       0,       // classname
       2,   14, // classinfo
       2,   18, // methods
       1,   34, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   30,    6, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,   33,    6, 0x08,    4 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
       7, QMetaType::QString, 0x00015103, uint(0), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeCandlestickSet::staticMetaObject = { {
    QMetaObject::SuperData::link<QCandlestickSet::staticMetaObject>(),
    qt_meta_stringdata_ZN25DeclarativeCandlestickSetE.offsetsAndSizes,
    qt_meta_data_ZN25DeclarativeCandlestickSetE,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'brushFilename'
        QString,
        // Q_OBJECT / Q_GADGET
        DeclarativeCandlestickSet,
        // method 'brushFilenameChanged'
        void,
        const QString &,
        // method 'handleBrushChanged'
        void
    >,
    nullptr
} };

void DeclarativeCandlestickSet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeCandlestickSet *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->brushFilenameChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->handleBrushChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativeCandlestickSet::*)(const QString & );
            if (_q_method_type _q_method = &DeclarativeCandlestickSet::brushFilenameChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->brushFilename(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBrushFilename(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *DeclarativeCandlestickSet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeCandlestickSet::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN25DeclarativeCandlestickSetE.stringdata0))
        return static_cast<void*>(this);
    return QCandlestickSet::qt_metacast(_clname);
}

int DeclarativeCandlestickSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCandlestickSet::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void DeclarativeCandlestickSet::brushFilenameChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
namespace {
struct qt_meta_tag_ZN28DeclarativeCandlestickSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN28DeclarativeCandlestickSeriesE = QtMocHelpers::stringData(
    "DeclarativeCandlestickSeries",
    "DefaultProperty",
    "seriesChildren",
    "QML.Element",
    "CandlestickSeries",
    "QML.AddedInVersion",
    "514",
    "axisXChanged",
    "",
    "QAbstractAxis*",
    "axis",
    "axisYChanged",
    "axisXTopChanged",
    "axisYRightChanged",
    "clicked",
    "DeclarativeCandlestickSet*",
    "set",
    "hovered",
    "status",
    "pressed",
    "released",
    "doubleClicked",
    "brushFilenameChanged",
    "brushFilename",
    "onClicked",
    "QCandlestickSet*",
    "onHovered",
    "onPressed",
    "onReleased",
    "onDoubleClicked",
    "handleBrushChanged",
    "at",
    "index",
    "append",
    "remove",
    "open",
    "high",
    "low",
    "close",
    "timestamp",
    "insert",
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

Q_CONSTINIT static const uint qt_meta_data_ZN28DeclarativeCandlestickSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       3,   14, // classinfo
      23,   20, // methods
       6,  237, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       7,    1,  158,    8, 0x06,    7 /* Public */,
      11,    1,  161,    8, 0x06,    9 /* Public */,
      12,    1,  164,    8, 0x06,   11 /* Public */,
      13,    1,  167,    8, 0x06,   13 /* Public */,
      14,    1,  170,    8, 0x06,   15 /* Public */,
      17,    2,  173,    8, 0x06,   17 /* Public */,
      19,    1,  178,    8, 0x06,   20 /* Public */,
      20,    1,  181,    8, 0x06,   22 /* Public */,
      21,    1,  184,    8, 0x06,   24 /* Public */,
      22,    1,  187,    8, 0x06,   26 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      24,    1,  190,    8, 0x0a,   28 /* Public */,
      26,    2,  193,    8, 0x0a,   30 /* Public */,
      27,    1,  198,    8, 0x0a,   33 /* Public */,
      28,    1,  201,    8, 0x0a,   35 /* Public */,
      29,    1,  204,    8, 0x0a,   37 /* Public */,
      30,    0,  207,    8, 0x08,   39 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      31,    1,  208,    8, 0x02,   40 /* Public */,
      33,    1,  211,    8, 0x02,   42 /* Public */,
      34,    1,  214,    8, 0x02,   44 /* Public */,
      33,    5,  217,    8, 0x02,   46 /* Public */,
      34,    1,  228,    8, 0x02,   52 /* Public */,
      40,    2,  231,    8, 0x02,   54 /* Public */,
      41,    0,  236,    8, 0x02,   57 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 15,   18,   16,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::QString,   23,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 25,   16,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 25,   18,   16,
    QMetaType::Void, 0x80000000 | 25,   16,
    QMetaType::Void, 0x80000000 | 25,   16,
    QMetaType::Void, 0x80000000 | 25,   16,
    QMetaType::Void,

 // methods: parameters
    0x80000000 | 15, QMetaType::Int,   32,
    QMetaType::Bool, 0x80000000 | 15,   16,
    QMetaType::Bool, 0x80000000 | 15,   16,
    QMetaType::Bool, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal,   35,   36,   37,   38,   39,
    QMetaType::Bool, QMetaType::QReal,   39,
    QMetaType::Bool, QMetaType::Int, 0x80000000 | 15,   32,   16,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      42, 0x80000000 | 9, 0x0001510b, uint(0), 0,
      43, 0x80000000 | 9, 0x0001510b, uint(1), 0,
      44, 0x80000000 | 9, 0x0001510b, uint(2), 0,
      45, 0x80000000 | 9, 0x0001510b, uint(3), 0,
       2, 0x80000000 | 46, 0x00015009, uint(-1), 0,
      23, QMetaType::QString, 0x00015103, uint(9), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeCandlestickSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QCandlestickSeries::staticMetaObject>(),
    qt_meta_stringdata_ZN28DeclarativeCandlestickSeriesE.offsetsAndSizes,
    qt_meta_data_ZN28DeclarativeCandlestickSeriesE,
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
        DeclarativeCandlestickSeries,
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
        DeclarativeCandlestickSet *,
        // method 'hovered'
        void,
        bool,
        DeclarativeCandlestickSet *,
        // method 'pressed'
        void,
        DeclarativeCandlestickSet *,
        // method 'released'
        void,
        DeclarativeCandlestickSet *,
        // method 'doubleClicked'
        void,
        DeclarativeCandlestickSet *,
        // method 'brushFilenameChanged'
        void,
        const QString &,
        // method 'onClicked'
        void,
        QCandlestickSet *,
        // method 'onHovered'
        void,
        bool,
        QCandlestickSet *,
        // method 'onPressed'
        void,
        QCandlestickSet *,
        // method 'onReleased'
        void,
        QCandlestickSet *,
        // method 'onDoubleClicked'
        void,
        QCandlestickSet *,
        // method 'handleBrushChanged'
        void,
        // method 'at'
        DeclarativeCandlestickSet *,
        int,
        // method 'append'
        bool,
        DeclarativeCandlestickSet *,
        // method 'remove'
        bool,
        DeclarativeCandlestickSet *,
        // method 'append'
        bool,
        qreal,
        qreal,
        qreal,
        qreal,
        qreal,
        // method 'remove'
        bool,
        qreal,
        // method 'insert'
        bool,
        int,
        DeclarativeCandlestickSet *,
        // method 'clear'
        void
    >,
    nullptr
} };

void DeclarativeCandlestickSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeCandlestickSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->axisXChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 1: _t->axisYChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 2: _t->axisXTopChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 3: _t->axisYRightChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 4: _t->clicked((*reinterpret_cast< std::add_pointer_t<DeclarativeCandlestickSet*>>(_a[1]))); break;
        case 5: _t->hovered((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<DeclarativeCandlestickSet*>>(_a[2]))); break;
        case 6: _t->pressed((*reinterpret_cast< std::add_pointer_t<DeclarativeCandlestickSet*>>(_a[1]))); break;
        case 7: _t->released((*reinterpret_cast< std::add_pointer_t<DeclarativeCandlestickSet*>>(_a[1]))); break;
        case 8: _t->doubleClicked((*reinterpret_cast< std::add_pointer_t<DeclarativeCandlestickSet*>>(_a[1]))); break;
        case 9: _t->brushFilenameChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->onClicked((*reinterpret_cast< std::add_pointer_t<QCandlestickSet*>>(_a[1]))); break;
        case 11: _t->onHovered((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCandlestickSet*>>(_a[2]))); break;
        case 12: _t->onPressed((*reinterpret_cast< std::add_pointer_t<QCandlestickSet*>>(_a[1]))); break;
        case 13: _t->onReleased((*reinterpret_cast< std::add_pointer_t<QCandlestickSet*>>(_a[1]))); break;
        case 14: _t->onDoubleClicked((*reinterpret_cast< std::add_pointer_t<QCandlestickSet*>>(_a[1]))); break;
        case 15: _t->handleBrushChanged(); break;
        case 16: { DeclarativeCandlestickSet* _r = _t->at((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< DeclarativeCandlestickSet**>(_a[0]) = std::move(_r); }  break;
        case 17: { bool _r = _t->append((*reinterpret_cast< std::add_pointer_t<DeclarativeCandlestickSet*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 18: { bool _r = _t->remove((*reinterpret_cast< std::add_pointer_t<DeclarativeCandlestickSet*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 19: { bool _r = _t->append((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[5])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 20: { bool _r = _t->remove((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 21: { bool _r = _t->insert((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<DeclarativeCandlestickSet*>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 22: _t->clear(); break;
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
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DeclarativeCandlestickSet* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DeclarativeCandlestickSet* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DeclarativeCandlestickSet* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DeclarativeCandlestickSet* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DeclarativeCandlestickSet* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCandlestickSet* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCandlestickSet* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCandlestickSet* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCandlestickSet* >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCandlestickSet* >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DeclarativeCandlestickSet* >(); break;
            }
            break;
        case 18:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DeclarativeCandlestickSet* >(); break;
            }
            break;
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DeclarativeCandlestickSet* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativeCandlestickSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeCandlestickSeries::axisXChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeCandlestickSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeCandlestickSeries::axisYChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeCandlestickSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeCandlestickSeries::axisXTopChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeCandlestickSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeCandlestickSeries::axisYRightChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeCandlestickSeries::*)(DeclarativeCandlestickSet * );
            if (_q_method_type _q_method = &DeclarativeCandlestickSeries::clicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeCandlestickSeries::*)(bool , DeclarativeCandlestickSet * );
            if (_q_method_type _q_method = &DeclarativeCandlestickSeries::hovered; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeCandlestickSeries::*)(DeclarativeCandlestickSet * );
            if (_q_method_type _q_method = &DeclarativeCandlestickSeries::pressed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeCandlestickSeries::*)(DeclarativeCandlestickSet * );
            if (_q_method_type _q_method = &DeclarativeCandlestickSeries::released; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeCandlestickSeries::*)(DeclarativeCandlestickSet * );
            if (_q_method_type _q_method = &DeclarativeCandlestickSeries::doubleClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeCandlestickSeries::*)(const QString & );
            if (_q_method_type _q_method = &DeclarativeCandlestickSeries::brushFilenameChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
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

const QMetaObject *DeclarativeCandlestickSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeCandlestickSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN28DeclarativeCandlestickSeriesE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    return QCandlestickSeries::qt_metacast(_clname);
}

int DeclarativeCandlestickSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCandlestickSeries::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
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
void DeclarativeCandlestickSeries::axisXChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeclarativeCandlestickSeries::axisYChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeclarativeCandlestickSeries::axisXTopChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DeclarativeCandlestickSeries::axisYRightChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DeclarativeCandlestickSeries::clicked(DeclarativeCandlestickSet * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DeclarativeCandlestickSeries::hovered(bool _t1, DeclarativeCandlestickSet * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DeclarativeCandlestickSeries::pressed(DeclarativeCandlestickSet * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DeclarativeCandlestickSeries::released(DeclarativeCandlestickSet * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void DeclarativeCandlestickSeries::doubleClicked(DeclarativeCandlestickSet * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void DeclarativeCandlestickSeries::brushFilenameChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
