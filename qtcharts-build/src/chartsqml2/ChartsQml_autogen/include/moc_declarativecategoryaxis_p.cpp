/****************************************************************************
** Meta object code from reading C++ file 'declarativecategoryaxis_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativecategoryaxis_p.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'declarativecategoryaxis_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN24DeclarativeCategoryRangeE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN24DeclarativeCategoryRangeE = QtMocHelpers::stringData(
    "DeclarativeCategoryRange",
    "QML.Element",
    "CategoryRange",
    "QML.AddedInVersion",
    "257",
    "QML.ExtraVersion",
    "512",
    "endValue",
    "label"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN24DeclarativeCategoryRangeE[] = {

 // content:
      12,       // revision
       0,       // classname
       3,   14, // classinfo
       0,    0, // methods
       2,   20, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,

 // properties: name, type, flags, notifyId, revision
       7, QMetaType::QReal, 0x00015103, uint(-1), 0,
       8, QMetaType::QString, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeCategoryRange::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN24DeclarativeCategoryRangeE.offsetsAndSizes,
    qt_meta_data_ZN24DeclarativeCategoryRangeE,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'endValue'
        qreal,
        // property 'label'
        QString,
        // Q_OBJECT / Q_GADGET
        DeclarativeCategoryRange
    >,
    nullptr
} };

void DeclarativeCategoryRange::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeCategoryRange *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->endValue(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->label(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEndValue(*reinterpret_cast< qreal*>(_v)); break;
        case 1: _t->setLabel(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *DeclarativeCategoryRange::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeCategoryRange::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN24DeclarativeCategoryRangeE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DeclarativeCategoryRange::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN23DeclarativeCategoryAxisE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN23DeclarativeCategoryAxisE = QtMocHelpers::stringData(
    "DeclarativeCategoryAxis",
    "DefaultProperty",
    "axisChildren",
    "QML.Element",
    "CategoryAxis",
    "QML.AddedInVersion",
    "257",
    "QML.ExtraVersion",
    "512",
    "labelsPositionChanged",
    "",
    "AxisLabelsPosition",
    "position",
    "append",
    "label",
    "categoryEndValue",
    "remove",
    "replace",
    "oldLabel",
    "newLabel",
    "QQmlListProperty<QObject>",
    "labelsPosition",
    "AxisLabelsPositionCenter",
    "AxisLabelsPositionOnValue"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN23DeclarativeCategoryAxisE[] = {

 // content:
      12,       // revision
       0,       // classname
       4,   14, // classinfo
       4,   22, // methods
       2,   66, // properties
       1,   76, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,
       7,    8,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,   50,   10, 0x86,    4 /* Public | MethodRevisioned */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    2,   53,   10, 0x0a,    6 /* Public */,
      16,    1,   58,   10, 0x0a,    9 /* Public */,
      17,    2,   61,   10, 0x0a,   11 /* Public */,

 // signals: revision
     513,

 // slots: revision
       0,
       0,
       0,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 11,   12,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QReal,   14,   15,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   18,   19,

 // properties: name, type, flags, notifyId, revision
       2, 0x80000000 | 20, 0x00015009, uint(-1), 0,
      21, 0x80000000 | 11, 0x0001510b, uint(0), 513,

 // enums: name, alias, flags, count, data
      11,   11, 0x0,    2,   81,

 // enum data: key, value
      22, uint(DeclarativeCategoryAxis::AxisLabelsPositionCenter),
      23, uint(DeclarativeCategoryAxis::AxisLabelsPositionOnValue),

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativeCategoryAxis::staticMetaObject = { {
    QMetaObject::SuperData::link<QCategoryAxis::staticMetaObject>(),
    qt_meta_stringdata_ZN23DeclarativeCategoryAxisE.offsetsAndSizes,
    qt_meta_data_ZN23DeclarativeCategoryAxisE,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'axisChildren'
        QQmlListProperty<QObject>,
        // property 'labelsPosition'
        AxisLabelsPosition,
        // enum 'AxisLabelsPosition'
        DeclarativeCategoryAxis::AxisLabelsPosition,
        // Q_OBJECT / Q_GADGET
        DeclarativeCategoryAxis,
        // method 'labelsPositionChanged'
        void,
        AxisLabelsPosition,
        // method 'append'
        void,
        const QString &,
        qreal,
        // method 'remove'
        void,
        const QString &,
        // method 'replace'
        void,
        const QString &,
        const QString &
    >,
    nullptr
} };

void DeclarativeCategoryAxis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativeCategoryAxis *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->labelsPositionChanged((*reinterpret_cast< std::add_pointer_t<AxisLabelsPosition>>(_a[1]))); break;
        case 1: _t->append((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[2]))); break;
        case 2: _t->remove((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->replace((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativeCategoryAxis::*)(AxisLabelsPosition );
            if (_q_method_type _q_method = &DeclarativeCategoryAxis::labelsPositionChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QQmlListProperty<QObject>*>(_v) = _t->axisChildren(); break;
        case 1: *reinterpret_cast< AxisLabelsPosition*>(_v) = _t->labelsPosition(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setLabelsPosition(*reinterpret_cast< AxisLabelsPosition*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *DeclarativeCategoryAxis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativeCategoryAxis::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN23DeclarativeCategoryAxisE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    return QCategoryAxis::qt_metacast(_clname);
}

int DeclarativeCategoryAxis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCategoryAxis::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DeclarativeCategoryAxis::labelsPositionChanged(AxisLabelsPosition _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
