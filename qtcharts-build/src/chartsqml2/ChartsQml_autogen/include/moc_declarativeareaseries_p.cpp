/****************************************************************************
** Meta object code from reading C++ file 'declarativeareaseries_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativeareaseries_p.h"
#include <QtCharts/qlineseries.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'declarativeareaseries_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN21DeclarativeAreaSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN21DeclarativeAreaSeriesE = QtMocHelpers::stringData(
    "DeclarativeAreaSeries",
    "QML.Element",
    "AreaSeries",
    "QML.AddedInVersion",
    "256",
    "QML.ExtraVersion",
    "512",
    "axisXChanged",
    "",
    "QAbstractAxis*",
    "axis",
    "axisYChanged",
    "borderWidthChanged",
    "width",
    "axisXTopChanged",
    "axisYRightChanged",
    "axisAngularChanged",
    "axisRadialChanged",
    "brushChanged",
    "brushFilenameChanged",
    "brushFilename",
    "handleBrushChanged",
    "upperSeries",
    "DeclarativeLineSeries*",
    "lowerSeries",
    "axisX",
    "axisY",
    "axisXTop",
    "axisYRight",
    "axisAngular",
    "axisRadial",
    "borderWidth",
    "brush"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN21DeclarativeAreaSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       3,   14, // classinfo
      10,   20, // methods
      11,  116, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       7,    1,   90,    8, 0x86,   12 /* Public | MethodRevisioned */,
      11,    1,   93,    8, 0x86,   14 /* Public | MethodRevisioned */,
      12,    1,   96,    8, 0x86,   16 /* Public | MethodRevisioned */,
      14,    1,   99,    8, 0x86,   18 /* Public | MethodRevisioned */,
      15,    1,  102,    8, 0x86,   20 /* Public | MethodRevisioned */,
      16,    1,  105,    8, 0x86,   22 /* Public | MethodRevisioned */,
      17,    1,  108,    8, 0x86,   24 /* Public | MethodRevisioned */,
      18,    0,  111,    8, 0x86,   26 /* Public | MethodRevisioned */,
      19,    1,  112,    8, 0x86,   27 /* Public | MethodRevisioned */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      21,    0,  115,    8, 0x08,   29 /* Private */,

 // signals: revision
     257,
     257,
     257,
     258,
     258,
     259,
     259,
     260,
     260,

 // slots: revision
       0,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QReal,   13,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   20,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      22, 0x80000000 | 23, 0x0001510b, uint(-1), 0,
      24, 0x80000000 | 23, 0x0001510b, uint(-1), 0,
      25, 0x80000000 | 9, 0x0001510b, uint(0), 257,
      26, 0x80000000 | 9, 0x0001510b, uint(1), 257,
      27, 0x80000000 | 9, 0x0001510b, uint(3), 258,
      28, 0x80000000 | 9, 0x0001510b, uint(4), 258,
      29, 0x80000000 | 9, 0x0001510b, uint(5), 259,
      30, 0x80000000 | 9, 0x0001510b, uint(6), 259,
      31, QMetaType::QReal, 0x00015103, uint(2), 257,
      20, QMetaType::QString, 0x00015103, uint(8), 260,
      32, QMetaType::QBrush, 0x00015103, uint(7), 260,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeAreaSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QAreaSeries::staticMetaObject>(),
    qt_meta_stringdata_ZN21DeclarativeAreaSeriesE.offsetsAndSizes,
    qt_meta_data_ZN21DeclarativeAreaSeriesE,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'upperSeries'
        DeclarativeLineSeries*,
        // property 'lowerSeries'
        DeclarativeLineSeries*,
        // property 'axisX'
        QAbstractAxis*,
        // property 'axisY'
        QAbstractAxis*,
        // property 'axisXTop'
        QAbstractAxis*,
        // property 'axisYRight'
        QAbstractAxis*,
        // property 'axisAngular'
        QAbstractAxis*,
        // property 'axisRadial'
        QAbstractAxis*,
        // property 'borderWidth'
        qreal,
        // property 'brushFilename'
        QString,
        // property 'brush'
        QBrush,
        // Q_OBJECT / Q_GADGET
        DeclarativeAreaSeries,
        // method 'axisXChanged'
        void,
        QAbstractAxis *,
        // method 'axisYChanged'
        void,
        QAbstractAxis *,
        // method 'borderWidthChanged'
        void,
        qreal,
        // method 'axisXTopChanged'
        void,
        QAbstractAxis *,
        // method 'axisYRightChanged'
        void,
        QAbstractAxis *,
        // method 'axisAngularChanged'
        void,
        QAbstractAxis *,
        // method 'axisRadialChanged'
        void,
        QAbstractAxis *,
        // method 'brushChanged'
        void,
        // method 'brushFilenameChanged'
        void,
        const QString &,
        // method 'handleBrushChanged'
        void
    >,
    nullptr
} };

void DeclarativeAreaSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeAreaSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->axisXChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 1: _t->axisYChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 2: _t->borderWidthChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 3: _t->axisXTopChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 4: _t->axisYRightChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 5: _t->axisAngularChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 6: _t->axisRadialChanged((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1]))); break;
        case 7: _t->brushChanged(); break;
        case 8: _t->brushFilenameChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->handleBrushChanged(); break;
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
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativeAreaSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeAreaSeries::axisXChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeAreaSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeAreaSeries::axisYChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeAreaSeries::*)(qreal );
            if (_q_method_type _q_method = &DeclarativeAreaSeries::borderWidthChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeAreaSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeAreaSeries::axisXTopChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeAreaSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeAreaSeries::axisYRightChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeAreaSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeAreaSeries::axisAngularChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeAreaSeries::*)(QAbstractAxis * );
            if (_q_method_type _q_method = &DeclarativeAreaSeries::axisRadialChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeAreaSeries::*)();
            if (_q_method_type _q_method = &DeclarativeAreaSeries::brushChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativeAreaSeries::*)(const QString & );
            if (_q_method_type _q_method = &DeclarativeAreaSeries::brushFilenameChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DeclarativeLineSeries* >(); break;
        case 7:
        case 6:
        case 5:
        case 4:
        case 3:
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractAxis* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< DeclarativeLineSeries**>(_v) = _t->upperSeries(); break;
        case 1: *reinterpret_cast< DeclarativeLineSeries**>(_v) = _t->lowerSeries(); break;
        case 2: *reinterpret_cast< QAbstractAxis**>(_v) = _t->axisX(); break;
        case 3: *reinterpret_cast< QAbstractAxis**>(_v) = _t->axisY(); break;
        case 4: *reinterpret_cast< QAbstractAxis**>(_v) = _t->axisXTop(); break;
        case 5: *reinterpret_cast< QAbstractAxis**>(_v) = _t->axisYRight(); break;
        case 6: *reinterpret_cast< QAbstractAxis**>(_v) = _t->axisAngular(); break;
        case 7: *reinterpret_cast< QAbstractAxis**>(_v) = _t->axisRadial(); break;
        case 8: *reinterpret_cast< qreal*>(_v) = _t->borderWidth(); break;
        case 9: *reinterpret_cast< QString*>(_v) = _t->brushFilename(); break;
        case 10: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setUpperSeries(*reinterpret_cast< DeclarativeLineSeries**>(_v)); break;
        case 1: _t->setLowerSeries(*reinterpret_cast< DeclarativeLineSeries**>(_v)); break;
        case 2: _t->setAxisX(*reinterpret_cast< QAbstractAxis**>(_v)); break;
        case 3: _t->setAxisY(*reinterpret_cast< QAbstractAxis**>(_v)); break;
        case 4: _t->setAxisXTop(*reinterpret_cast< QAbstractAxis**>(_v)); break;
        case 5: _t->setAxisYRight(*reinterpret_cast< QAbstractAxis**>(_v)); break;
        case 6: _t->setAxisAngular(*reinterpret_cast< QAbstractAxis**>(_v)); break;
        case 7: _t->setAxisRadial(*reinterpret_cast< QAbstractAxis**>(_v)); break;
        case 8: _t->setBorderWidth(*reinterpret_cast< qreal*>(_v)); break;
        case 9: _t->setBrushFilename(*reinterpret_cast< QString*>(_v)); break;
        case 10: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *DeclarativeAreaSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeAreaSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN21DeclarativeAreaSeriesE.stringdata0))
        return static_cast<void*>(this);
    return QAreaSeries::qt_metacast(_clname);
}

int DeclarativeAreaSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAreaSeries::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void DeclarativeAreaSeries::axisXChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeclarativeAreaSeries::axisYChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeclarativeAreaSeries::borderWidthChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DeclarativeAreaSeries::axisXTopChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DeclarativeAreaSeries::axisYRightChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DeclarativeAreaSeries::axisAngularChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DeclarativeAreaSeries::axisRadialChanged(QAbstractAxis * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DeclarativeAreaSeries::brushChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void DeclarativeAreaSeries::brushFilenameChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
