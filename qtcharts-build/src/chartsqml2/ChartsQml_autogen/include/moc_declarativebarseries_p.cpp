/****************************************************************************
** Meta object code from reading C++ file 'declarativebarseries_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativebarseries_p.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'declarativebarseries_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN17DeclarativeBarSetE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN17DeclarativeBarSetE = QtMocHelpers::stringData(
    "DeclarativeBarSet",
    "QML.Element",
    "BarSet",
    "QML.AddedInVersion",
    "256",
    "QML.ExtraVersion",
    "512",
    "countChanged",
    "",
    "count",
    "borderWidthChanged",
    "width",
    "brushFilenameChanged",
    "brushFilename",
    "handleCountChanged",
    "index",
    "handleBrushChanged",
    "append",
    "value",
    "remove",
    "replace",
    "at",
    "values",
    "QVariantList",
    "borderWidth"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN17DeclarativeBarSetE[] = {

 // content:
      12,       // revision
       0,       // classname
       3,   14, // classinfo
      10,   20, // methods
       4,  124, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       7,    1,   90,    8, 0x06,    5 /* Public */,
      10,    1,   93,    8, 0x86,    7 /* Public | MethodRevisioned */,
      12,    1,   96,    8, 0x86,    9 /* Public | MethodRevisioned */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      14,    2,   99,    8, 0x08,   11 /* Private */,
      16,    0,  104,    8, 0x08,   14 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      17,    1,  105,    8, 0x02,   15 /* Public */,
      19,    2,  108,    8, 0x02,   17 /* Public */,
      19,    1,  113,    8, 0x22,   20 /* Public | MethodCloned */,
      20,    2,  116,    8, 0x02,   22 /* Public */,
      21,    1,  121,    8, 0x02,   25 /* Public */,

 // signals: revision
       0,
     257,
     260,

 // slots: revision
       0,
       0,

 // methods: revision
       0,
       0,
       0,
       0,
       0,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::QReal,   11,
    QMetaType::Void, QMetaType::QString,   13,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   15,    9,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QReal,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   15,    9,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::QReal,   15,   18,
    QMetaType::QReal, QMetaType::Int,   15,

 // properties: name, type, flags, notifyId, revision
      22, 0x80000000 | 23, 0x0001510b, uint(-1), 0,
      24, QMetaType::QReal, 0x00015103, uint(1), 257,
       9, QMetaType::Int, 0x00015001, uint(0), 0,
      13, QMetaType::QString, 0x00015103, uint(2), 260,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeBarSet::staticMetaObject = { {
    QMetaObject::SuperData::link<QBarSet::staticMetaObject>(),
    qt_meta_stringdata_ZN17DeclarativeBarSetE.offsetsAndSizes,
    qt_meta_data_ZN17DeclarativeBarSetE,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'values'
        QVariantList,
        // property 'borderWidth'
        qreal,
        // property 'count'
        int,
        // property 'brushFilename'
        QString,
        // Q_OBJECT / Q_GADGET
        DeclarativeBarSet,
        // method 'countChanged'
        void,
        int,
        // method 'borderWidthChanged'
        void,
        qreal,
        // method 'brushFilenameChanged'
        void,
        const QString &,
        // method 'handleCountChanged'
        void,
        int,
        int,
        // method 'handleBrushChanged'
        void,
        // method 'append'
        void,
        qreal,
        // method 'remove'
        void,
        const int,
        const int,
        // method 'remove'
        void,
        const int,
        // method 'replace'
        void,
        int,
        qreal,
        // method 'at'
        qreal,
        int
    >,
    nullptr
} };

void DeclarativeBarSet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeBarSet *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->countChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->borderWidthChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 2: _t->brushFilenameChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->handleCountChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->handleBrushChanged(); break;
        case 5: _t->append((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 6: _t->remove((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 7: _t->remove((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->replace((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[2]))); break;
        case 9: { qreal _r = _t->at((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativeBarSet::*)(int );
            if (_q_method_type _q_method = &DeclarativeBarSet::countChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBarSet::*)(qreal );
            if (_q_method_type _q_method = &DeclarativeBarSet::borderWidthChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBarSet::*)(const QString & );
            if (_q_method_type _q_method = &DeclarativeBarSet::brushFilenameChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariantList*>(_v) = _t->values(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = _t->borderWidth(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->count(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->brushFilename(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setValues(*reinterpret_cast< QVariantList*>(_v)); break;
        case 1: _t->setBorderWidth(*reinterpret_cast< qreal*>(_v)); break;
        case 3: _t->setBrushFilename(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *DeclarativeBarSet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeBarSet::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN17DeclarativeBarSetE.stringdata0))
        return static_cast<void*>(this);
    return QBarSet::qt_metacast(_clname);
}

int DeclarativeBarSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QBarSet::qt_metacall(_c, _id, _a);
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
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DeclarativeBarSet::countChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeclarativeBarSet::borderWidthChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeclarativeBarSet::brushFilenameChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
namespace {
struct qt_meta_tag_ZN20DeclarativeBarSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN20DeclarativeBarSeriesE = QtMocHelpers::stringData(
    "DeclarativeBarSeries",
    "DefaultProperty",
    "seriesChildren",
    "QML.Element",
    "BarSeries",
    "QML.AddedInVersion",
    "256",
    "QML.ExtraVersion",
    "512",
    "axisXChanged",
    "",
    "QAbstractAxis*",
    "axis",
    "axisYChanged",
    "axisXTopChanged",
    "axisYRightChanged",
    "at",
    "DeclarativeBarSet*",
    "index",
    "append",
    "label",
    "QVariantList",
    "values",
    "insert",
    "remove",
    "QBarSet*",
    "barset",
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

Q_CONSTINIT static const uint qt_meta_data_ZN20DeclarativeBarSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       4,   14, // classinfo
       9,   22, // methods
       5,  116, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,
       7,    8,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,   85,   10, 0x86,    6 /* Public | MethodRevisioned */,
      13,    1,   88,   10, 0x86,    8 /* Public | MethodRevisioned */,
      14,    1,   91,   10, 0x86,   10 /* Public | MethodRevisioned */,
      15,    1,   94,   10, 0x86,   12 /* Public | MethodRevisioned */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      16,    1,   97,   10, 0x02,   14 /* Public */,
      19,    2,  100,   10, 0x02,   16 /* Public */,
      23,    3,  105,   10, 0x02,   19 /* Public */,
      24,    1,  112,   10, 0x02,   23 /* Public */,
      27,    0,  115,   10, 0x02,   25 /* Public */,

 // signals: revision
     257,
     257,
     258,
     258,

 // methods: revision
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

 // methods: parameters
    0x80000000 | 17, QMetaType::Int,   18,
    0x80000000 | 17, QMetaType::QString, 0x80000000 | 21,   20,   22,
    0x80000000 | 17, QMetaType::Int, QMetaType::QString, 0x80000000 | 21,   18,   20,   22,
    QMetaType::Bool, 0x80000000 | 25,   26,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      28, 0x80000000 | 11, 0x0001510b, uint(0), 257,
      29, 0x80000000 | 11, 0x0001510b, uint(1), 257,
      30, 0x80000000 | 11, 0x0001510b, uint(2), 258,
      31, 0x80000000 | 11, 0x0001510b, uint(3), 258,
       2, 0x80000000 | 32, 0x00015009, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeBarSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QBarSeries::staticMetaObject>(),
    qt_meta_stringdata_ZN20DeclarativeBarSeriesE.offsetsAndSizes,
    qt_meta_data_ZN20DeclarativeBarSeriesE,
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
        // Q_OBJECT / Q_GADGET
        DeclarativeBarSeries,
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
        // method 'at'
        DeclarativeBarSet *,
        int,
        // method 'append'
        DeclarativeBarSet *,
        QString,
        QVariantList,
        // method 'insert'
        DeclarativeBarSet *,
        int,
        QString,
        QVariantList,
        // method 'remove'
        bool,
        QBarSet *,
        // method 'clear'
        void
    >,
    nullptr
} };

void DeclarativeBarSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeBarSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->axisXChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 1: _t->axisYChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 2: _t->axisXTopChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 3: _t->axisYRightChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 4: { DeclarativeBarSet* _r = _t->at((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 5: { DeclarativeBarSet* _r = _t->append((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[2])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 6: { DeclarativeBarSet* _r = _t->insert((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[3])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->remove((*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->clear(); break;
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
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBarSet* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativeBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeBarSeries::axisXChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeBarSeries::axisYChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeBarSeries::axisXTopChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeBarSeries::axisYRightChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
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
        default: break;
        }
    }
}

const QMetaObject *DeclarativeBarSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeBarSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN20DeclarativeBarSeriesE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    return QBarSeries::qt_metacast(_clname);
}

int DeclarativeBarSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QBarSeries::qt_metacall(_c, _id, _a);
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
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DeclarativeBarSeries::axisXChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeclarativeBarSeries::axisYChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeclarativeBarSeries::axisXTopChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DeclarativeBarSeries::axisYRightChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
namespace {
struct qt_meta_tag_ZN27DeclarativeStackedBarSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN27DeclarativeStackedBarSeriesE = QtMocHelpers::stringData(
    "DeclarativeStackedBarSeries",
    "DefaultProperty",
    "seriesChildren",
    "QML.Element",
    "StackedBarSeries",
    "QML.AddedInVersion",
    "256",
    "QML.ExtraVersion",
    "512",
    "axisXChanged",
    "",
    "QAbstractAxis*",
    "axis",
    "axisYChanged",
    "axisXTopChanged",
    "axisYRightChanged",
    "at",
    "DeclarativeBarSet*",
    "index",
    "append",
    "label",
    "QVariantList",
    "values",
    "insert",
    "remove",
    "QBarSet*",
    "barset",
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

Q_CONSTINIT static const uint qt_meta_data_ZN27DeclarativeStackedBarSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       4,   14, // classinfo
       9,   22, // methods
       5,  116, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,
       7,    8,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,   85,   10, 0x86,    6 /* Public | MethodRevisioned */,
      13,    1,   88,   10, 0x86,    8 /* Public | MethodRevisioned */,
      14,    1,   91,   10, 0x86,   10 /* Public | MethodRevisioned */,
      15,    1,   94,   10, 0x86,   12 /* Public | MethodRevisioned */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      16,    1,   97,   10, 0x02,   14 /* Public */,
      19,    2,  100,   10, 0x02,   16 /* Public */,
      23,    3,  105,   10, 0x02,   19 /* Public */,
      24,    1,  112,   10, 0x02,   23 /* Public */,
      27,    0,  115,   10, 0x02,   25 /* Public */,

 // signals: revision
     257,
     257,
     258,
     258,

 // methods: revision
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

 // methods: parameters
    0x80000000 | 17, QMetaType::Int,   18,
    0x80000000 | 17, QMetaType::QString, 0x80000000 | 21,   20,   22,
    0x80000000 | 17, QMetaType::Int, QMetaType::QString, 0x80000000 | 21,   18,   20,   22,
    QMetaType::Bool, 0x80000000 | 25,   26,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      28, 0x80000000 | 11, 0x0001510b, uint(0), 257,
      29, 0x80000000 | 11, 0x0001510b, uint(1), 257,
      30, 0x80000000 | 11, 0x0001510b, uint(2), 258,
      31, 0x80000000 | 11, 0x0001510b, uint(3), 258,
       2, 0x80000000 | 32, 0x00015009, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeStackedBarSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QStackedBarSeries::staticMetaObject>(),
    qt_meta_stringdata_ZN27DeclarativeStackedBarSeriesE.offsetsAndSizes,
    qt_meta_data_ZN27DeclarativeStackedBarSeriesE,
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
        // Q_OBJECT / Q_GADGET
        DeclarativeStackedBarSeries,
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
        // method 'at'
        DeclarativeBarSet *,
        int,
        // method 'append'
        DeclarativeBarSet *,
        QString,
        QVariantList,
        // method 'insert'
        DeclarativeBarSet *,
        int,
        QString,
        QVariantList,
        // method 'remove'
        bool,
        QBarSet *,
        // method 'clear'
        void
    >,
    nullptr
} };

void DeclarativeStackedBarSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeStackedBarSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->axisXChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 1: _t->axisYChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 2: _t->axisXTopChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 3: _t->axisYRightChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 4: { DeclarativeBarSet* _r = _t->at((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 5: { DeclarativeBarSet* _r = _t->append((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[2])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 6: { DeclarativeBarSet* _r = _t->insert((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[3])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->remove((*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->clear(); break;
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
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBarSet* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativeStackedBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeStackedBarSeries::axisXChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeStackedBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeStackedBarSeries::axisYChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeStackedBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeStackedBarSeries::axisXTopChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeStackedBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeStackedBarSeries::axisYRightChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
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
        default: break;
        }
    }
}

const QMetaObject *DeclarativeStackedBarSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeStackedBarSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN27DeclarativeStackedBarSeriesE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    return QStackedBarSeries::qt_metacast(_clname);
}

int DeclarativeStackedBarSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStackedBarSeries::qt_metacall(_c, _id, _a);
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
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DeclarativeStackedBarSeries::axisXChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeclarativeStackedBarSeries::axisYChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeclarativeStackedBarSeries::axisXTopChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DeclarativeStackedBarSeries::axisYRightChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
namespace {
struct qt_meta_tag_ZN27DeclarativePercentBarSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN27DeclarativePercentBarSeriesE = QtMocHelpers::stringData(
    "DeclarativePercentBarSeries",
    "DefaultProperty",
    "seriesChildren",
    "QML.Element",
    "PercentBarSeries",
    "QML.AddedInVersion",
    "256",
    "QML.ExtraVersion",
    "512",
    "axisXChanged",
    "",
    "QAbstractAxis*",
    "axis",
    "axisYChanged",
    "axisXTopChanged",
    "axisYRightChanged",
    "at",
    "DeclarativeBarSet*",
    "index",
    "append",
    "label",
    "QVariantList",
    "values",
    "insert",
    "remove",
    "QBarSet*",
    "barset",
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

Q_CONSTINIT static const uint qt_meta_data_ZN27DeclarativePercentBarSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       4,   14, // classinfo
       9,   22, // methods
       5,  116, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,
       7,    8,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,   85,   10, 0x86,    6 /* Public | MethodRevisioned */,
      13,    1,   88,   10, 0x86,    8 /* Public | MethodRevisioned */,
      14,    1,   91,   10, 0x86,   10 /* Public | MethodRevisioned */,
      15,    1,   94,   10, 0x86,   12 /* Public | MethodRevisioned */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      16,    1,   97,   10, 0x02,   14 /* Public */,
      19,    2,  100,   10, 0x02,   16 /* Public */,
      23,    3,  105,   10, 0x02,   19 /* Public */,
      24,    1,  112,   10, 0x02,   23 /* Public */,
      27,    0,  115,   10, 0x02,   25 /* Public */,

 // signals: revision
     257,
     257,
     258,
     258,

 // methods: revision
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

 // methods: parameters
    0x80000000 | 17, QMetaType::Int,   18,
    0x80000000 | 17, QMetaType::QString, 0x80000000 | 21,   20,   22,
    0x80000000 | 17, QMetaType::Int, QMetaType::QString, 0x80000000 | 21,   18,   20,   22,
    QMetaType::Bool, 0x80000000 | 25,   26,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      28, 0x80000000 | 11, 0x0001510b, uint(0), 257,
      29, 0x80000000 | 11, 0x0001510b, uint(1), 257,
      30, 0x80000000 | 11, 0x0001510b, uint(2), 258,
      31, 0x80000000 | 11, 0x0001510b, uint(3), 258,
       2, 0x80000000 | 32, 0x00015009, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativePercentBarSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QPercentBarSeries::staticMetaObject>(),
    qt_meta_stringdata_ZN27DeclarativePercentBarSeriesE.offsetsAndSizes,
    qt_meta_data_ZN27DeclarativePercentBarSeriesE,
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
        // Q_OBJECT / Q_GADGET
        DeclarativePercentBarSeries,
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
        // method 'at'
        DeclarativeBarSet *,
        int,
        // method 'append'
        DeclarativeBarSet *,
        QString,
        QVariantList,
        // method 'insert'
        DeclarativeBarSet *,
        int,
        QString,
        QVariantList,
        // method 'remove'
        bool,
        QBarSet *,
        // method 'clear'
        void
    >,
    nullptr
} };

void DeclarativePercentBarSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativePercentBarSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->axisXChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 1: _t->axisYChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 2: _t->axisXTopChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 3: _t->axisYRightChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 4: { DeclarativeBarSet* _r = _t->at((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 5: { DeclarativeBarSet* _r = _t->append((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[2])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 6: { DeclarativeBarSet* _r = _t->insert((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[3])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->remove((*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->clear(); break;
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
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBarSet* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativePercentBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativePercentBarSeries::axisXChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativePercentBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativePercentBarSeries::axisYChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativePercentBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativePercentBarSeries::axisXTopChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativePercentBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativePercentBarSeries::axisYRightChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
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
        default: break;
        }
    }
}

const QMetaObject *DeclarativePercentBarSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativePercentBarSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN27DeclarativePercentBarSeriesE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    return QPercentBarSeries::qt_metacast(_clname);
}

int DeclarativePercentBarSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPercentBarSeries::qt_metacall(_c, _id, _a);
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
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DeclarativePercentBarSeries::axisXChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeclarativePercentBarSeries::axisYChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeclarativePercentBarSeries::axisXTopChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DeclarativePercentBarSeries::axisYRightChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
namespace {
struct qt_meta_tag_ZN30DeclarativeHorizontalBarSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN30DeclarativeHorizontalBarSeriesE = QtMocHelpers::stringData(
    "DeclarativeHorizontalBarSeries",
    "DefaultProperty",
    "seriesChildren",
    "QML.Element",
    "HorizontalBarSeries",
    "QML.AddedInVersion",
    "256",
    "QML.ExtraVersion",
    "512",
    "axisXChanged",
    "",
    "QAbstractAxis*",
    "axis",
    "axisYChanged",
    "axisXTopChanged",
    "axisYRightChanged",
    "at",
    "DeclarativeBarSet*",
    "index",
    "append",
    "label",
    "QVariantList",
    "values",
    "insert",
    "remove",
    "QBarSet*",
    "barset",
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

Q_CONSTINIT static const uint qt_meta_data_ZN30DeclarativeHorizontalBarSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       4,   14, // classinfo
       9,   22, // methods
       5,  116, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,
       7,    8,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,   85,   10, 0x86,    6 /* Public | MethodRevisioned */,
      13,    1,   88,   10, 0x86,    8 /* Public | MethodRevisioned */,
      14,    1,   91,   10, 0x86,   10 /* Public | MethodRevisioned */,
      15,    1,   94,   10, 0x86,   12 /* Public | MethodRevisioned */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      16,    1,   97,   10, 0x02,   14 /* Public */,
      19,    2,  100,   10, 0x02,   16 /* Public */,
      23,    3,  105,   10, 0x02,   19 /* Public */,
      24,    1,  112,   10, 0x02,   23 /* Public */,
      27,    0,  115,   10, 0x02,   25 /* Public */,

 // signals: revision
     257,
     257,
     258,
     258,

 // methods: revision
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

 // methods: parameters
    0x80000000 | 17, QMetaType::Int,   18,
    0x80000000 | 17, QMetaType::QString, 0x80000000 | 21,   20,   22,
    0x80000000 | 17, QMetaType::Int, QMetaType::QString, 0x80000000 | 21,   18,   20,   22,
    QMetaType::Bool, 0x80000000 | 25,   26,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      28, 0x80000000 | 11, 0x0001510b, uint(0), 257,
      29, 0x80000000 | 11, 0x0001510b, uint(1), 257,
      30, 0x80000000 | 11, 0x0001510b, uint(2), 258,
      31, 0x80000000 | 11, 0x0001510b, uint(3), 258,
       2, 0x80000000 | 32, 0x00015009, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeHorizontalBarSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QHorizontalBarSeries::staticMetaObject>(),
    qt_meta_stringdata_ZN30DeclarativeHorizontalBarSeriesE.offsetsAndSizes,
    qt_meta_data_ZN30DeclarativeHorizontalBarSeriesE,
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
        // Q_OBJECT / Q_GADGET
        DeclarativeHorizontalBarSeries,
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
        // method 'at'
        DeclarativeBarSet *,
        int,
        // method 'append'
        DeclarativeBarSet *,
        QString,
        QVariantList,
        // method 'insert'
        DeclarativeBarSet *,
        int,
        QString,
        QVariantList,
        // method 'remove'
        bool,
        QBarSet *,
        // method 'clear'
        void
    >,
    nullptr
} };

void DeclarativeHorizontalBarSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeHorizontalBarSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->axisXChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 1: _t->axisYChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 2: _t->axisXTopChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 3: _t->axisYRightChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 4: { DeclarativeBarSet* _r = _t->at((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 5: { DeclarativeBarSet* _r = _t->append((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[2])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 6: { DeclarativeBarSet* _r = _t->insert((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[3])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->remove((*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->clear(); break;
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
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBarSet* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativeHorizontalBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeHorizontalBarSeries::axisXChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeHorizontalBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeHorizontalBarSeries::axisYChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeHorizontalBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeHorizontalBarSeries::axisXTopChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeHorizontalBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeHorizontalBarSeries::axisYRightChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
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
        default: break;
        }
    }
}

const QMetaObject *DeclarativeHorizontalBarSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeHorizontalBarSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN30DeclarativeHorizontalBarSeriesE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    return QHorizontalBarSeries::qt_metacast(_clname);
}

int DeclarativeHorizontalBarSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHorizontalBarSeries::qt_metacall(_c, _id, _a);
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
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DeclarativeHorizontalBarSeries::axisXChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeclarativeHorizontalBarSeries::axisYChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeclarativeHorizontalBarSeries::axisXTopChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DeclarativeHorizontalBarSeries::axisYRightChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
namespace {
struct qt_meta_tag_ZN37DeclarativeHorizontalStackedBarSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN37DeclarativeHorizontalStackedBarSeriesE = QtMocHelpers::stringData(
    "DeclarativeHorizontalStackedBarSeries",
    "DefaultProperty",
    "seriesChildren",
    "QML.Element",
    "HorizontalStackedBarSeries",
    "QML.AddedInVersion",
    "256",
    "QML.ExtraVersion",
    "512",
    "axisXChanged",
    "",
    "QAbstractAxis*",
    "axis",
    "axisYChanged",
    "axisXTopChanged",
    "axisYRightChanged",
    "at",
    "DeclarativeBarSet*",
    "index",
    "append",
    "label",
    "QVariantList",
    "values",
    "insert",
    "remove",
    "QBarSet*",
    "barset",
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

Q_CONSTINIT static const uint qt_meta_data_ZN37DeclarativeHorizontalStackedBarSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       4,   14, // classinfo
       9,   22, // methods
       5,  116, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,
       7,    8,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,   85,   10, 0x86,    6 /* Public | MethodRevisioned */,
      13,    1,   88,   10, 0x86,    8 /* Public | MethodRevisioned */,
      14,    1,   91,   10, 0x86,   10 /* Public | MethodRevisioned */,
      15,    1,   94,   10, 0x86,   12 /* Public | MethodRevisioned */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      16,    1,   97,   10, 0x02,   14 /* Public */,
      19,    2,  100,   10, 0x02,   16 /* Public */,
      23,    3,  105,   10, 0x02,   19 /* Public */,
      24,    1,  112,   10, 0x02,   23 /* Public */,
      27,    0,  115,   10, 0x02,   25 /* Public */,

 // signals: revision
     257,
     257,
     258,
     258,

 // methods: revision
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

 // methods: parameters
    0x80000000 | 17, QMetaType::Int,   18,
    0x80000000 | 17, QMetaType::QString, 0x80000000 | 21,   20,   22,
    0x80000000 | 17, QMetaType::Int, QMetaType::QString, 0x80000000 | 21,   18,   20,   22,
    QMetaType::Bool, 0x80000000 | 25,   26,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      28, 0x80000000 | 11, 0x0001510b, uint(0), 257,
      29, 0x80000000 | 11, 0x0001510b, uint(1), 257,
      30, 0x80000000 | 11, 0x0001510b, uint(2), 258,
      31, 0x80000000 | 11, 0x0001510b, uint(3), 258,
       2, 0x80000000 | 32, 0x00015009, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeHorizontalStackedBarSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QHorizontalStackedBarSeries::staticMetaObject>(),
    qt_meta_stringdata_ZN37DeclarativeHorizontalStackedBarSeriesE.offsetsAndSizes,
    qt_meta_data_ZN37DeclarativeHorizontalStackedBarSeriesE,
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
        // Q_OBJECT / Q_GADGET
        DeclarativeHorizontalStackedBarSeries,
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
        // method 'at'
        DeclarativeBarSet *,
        int,
        // method 'append'
        DeclarativeBarSet *,
        QString,
        QVariantList,
        // method 'insert'
        DeclarativeBarSet *,
        int,
        QString,
        QVariantList,
        // method 'remove'
        bool,
        QBarSet *,
        // method 'clear'
        void
    >,
    nullptr
} };

void DeclarativeHorizontalStackedBarSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeHorizontalStackedBarSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->axisXChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 1: _t->axisYChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 2: _t->axisXTopChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 3: _t->axisYRightChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 4: { DeclarativeBarSet* _r = _t->at((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 5: { DeclarativeBarSet* _r = _t->append((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[2])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 6: { DeclarativeBarSet* _r = _t->insert((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[3])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->remove((*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->clear(); break;
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
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBarSet* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativeHorizontalStackedBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeHorizontalStackedBarSeries::axisXChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeHorizontalStackedBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeHorizontalStackedBarSeries::axisYChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeHorizontalStackedBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeHorizontalStackedBarSeries::axisXTopChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeHorizontalStackedBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeHorizontalStackedBarSeries::axisYRightChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
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
        default: break;
        }
    }
}

const QMetaObject *DeclarativeHorizontalStackedBarSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeHorizontalStackedBarSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN37DeclarativeHorizontalStackedBarSeriesE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    return QHorizontalStackedBarSeries::qt_metacast(_clname);
}

int DeclarativeHorizontalStackedBarSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHorizontalStackedBarSeries::qt_metacall(_c, _id, _a);
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
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DeclarativeHorizontalStackedBarSeries::axisXChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeclarativeHorizontalStackedBarSeries::axisYChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeclarativeHorizontalStackedBarSeries::axisXTopChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DeclarativeHorizontalStackedBarSeries::axisYRightChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
namespace {
struct qt_meta_tag_ZN37DeclarativeHorizontalPercentBarSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN37DeclarativeHorizontalPercentBarSeriesE = QtMocHelpers::stringData(
    "DeclarativeHorizontalPercentBarSeries",
    "DefaultProperty",
    "seriesChildren",
    "QML.Element",
    "HorizontalPercentBarSeries",
    "QML.AddedInVersion",
    "256",
    "QML.ExtraVersion",
    "512",
    "axisXChanged",
    "",
    "QAbstractAxis*",
    "axis",
    "axisYChanged",
    "axisXTopChanged",
    "axisYRightChanged",
    "at",
    "DeclarativeBarSet*",
    "index",
    "append",
    "label",
    "QVariantList",
    "values",
    "insert",
    "remove",
    "QBarSet*",
    "barset",
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

Q_CONSTINIT static const uint qt_meta_data_ZN37DeclarativeHorizontalPercentBarSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       4,   14, // classinfo
       9,   22, // methods
       5,  116, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,
       7,    8,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,   85,   10, 0x86,    6 /* Public | MethodRevisioned */,
      13,    1,   88,   10, 0x86,    8 /* Public | MethodRevisioned */,
      14,    1,   91,   10, 0x86,   10 /* Public | MethodRevisioned */,
      15,    1,   94,   10, 0x86,   12 /* Public | MethodRevisioned */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      16,    1,   97,   10, 0x02,   14 /* Public */,
      19,    2,  100,   10, 0x02,   16 /* Public */,
      23,    3,  105,   10, 0x02,   19 /* Public */,
      24,    1,  112,   10, 0x02,   23 /* Public */,
      27,    0,  115,   10, 0x02,   25 /* Public */,

 // signals: revision
     257,
     257,
     258,
     258,

 // methods: revision
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

 // methods: parameters
    0x80000000 | 17, QMetaType::Int,   18,
    0x80000000 | 17, QMetaType::QString, 0x80000000 | 21,   20,   22,
    0x80000000 | 17, QMetaType::Int, QMetaType::QString, 0x80000000 | 21,   18,   20,   22,
    QMetaType::Bool, 0x80000000 | 25,   26,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      28, 0x80000000 | 11, 0x0001510b, uint(0), 257,
      29, 0x80000000 | 11, 0x0001510b, uint(1), 257,
      30, 0x80000000 | 11, 0x0001510b, uint(2), 258,
      31, 0x80000000 | 11, 0x0001510b, uint(3), 258,
       2, 0x80000000 | 32, 0x00015009, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeHorizontalPercentBarSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QHorizontalPercentBarSeries::staticMetaObject>(),
    qt_meta_stringdata_ZN37DeclarativeHorizontalPercentBarSeriesE.offsetsAndSizes,
    qt_meta_data_ZN37DeclarativeHorizontalPercentBarSeriesE,
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
        // Q_OBJECT / Q_GADGET
        DeclarativeHorizontalPercentBarSeries,
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
        // method 'at'
        DeclarativeBarSet *,
        int,
        // method 'append'
        DeclarativeBarSet *,
        QString,
        QVariantList,
        // method 'insert'
        DeclarativeBarSet *,
        int,
        QString,
        QVariantList,
        // method 'remove'
        bool,
        QBarSet *,
        // method 'clear'
        void
    >,
    nullptr
} };

void DeclarativeHorizontalPercentBarSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeHorizontalPercentBarSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->axisXChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 1: _t->axisYChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 2: _t->axisXTopChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 3: _t->axisYRightChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 4: { DeclarativeBarSet* _r = _t->at((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 5: { DeclarativeBarSet* _r = _t->append((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[2])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 6: { DeclarativeBarSet* _r = _t->insert((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[3])));
            if (_a[0]) *reinterpret_cast< DeclarativeBarSet**>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->remove((*reinterpret_cast< std::add_pointer_t<QBarSet*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->clear(); break;
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
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QBarSet* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativeHorizontalPercentBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeHorizontalPercentBarSeries::axisXChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeHorizontalPercentBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeHorizontalPercentBarSeries::axisYChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeHorizontalPercentBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeHorizontalPercentBarSeries::axisXTopChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeHorizontalPercentBarSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeHorizontalPercentBarSeries::axisYRightChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
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
        default: break;
        }
    }
}

const QMetaObject *DeclarativeHorizontalPercentBarSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeHorizontalPercentBarSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN37DeclarativeHorizontalPercentBarSeriesE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    return QHorizontalPercentBarSeries::qt_metacast(_clname);
}

int DeclarativeHorizontalPercentBarSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHorizontalPercentBarSeries::qt_metacall(_c, _id, _a);
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
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DeclarativeHorizontalPercentBarSeries::axisXChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeclarativeHorizontalPercentBarSeries::axisYChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeclarativeHorizontalPercentBarSeries::axisXTopChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DeclarativeHorizontalPercentBarSeries::axisYRightChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
