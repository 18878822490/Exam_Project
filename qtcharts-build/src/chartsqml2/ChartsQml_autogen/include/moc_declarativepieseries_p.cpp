/****************************************************************************
** Meta object code from reading C++ file 'declarativepieseries_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../0/Qt/6.8.3/Src/qtcharts/src/chartsqml2/declarativepieseries_p.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'declarativepieseries_p.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN19DeclarativePieSliceE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN19DeclarativePieSliceE = QtMocHelpers::stringData(
    "DeclarativePieSlice",
    "QML.Element",
    "PieSlice",
    "QML.AddedInVersion",
    "256",
    "QML.ExtraVersion",
    "512",
    "brushFilenameChanged",
    "",
    "brushFilename",
    "handleBrushChanged"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN19DeclarativePieSliceE[] = {

 // content:
      12,       // revision
       0,       // classname
       3,   14, // classinfo
       2,   20, // methods
       1,   36, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       7,    1,   32,    8, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    0,   35,    8, 0x08,    4 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    9,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
       9, QMetaType::QString, 0x00015103, uint(0), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativePieSlice::staticMetaObject = { {
    QMetaObject::SuperData::link<QPieSlice::staticMetaObject>(),
    qt_meta_stringdata_ZN19DeclarativePieSliceE.offsetsAndSizes,
    qt_meta_data_ZN19DeclarativePieSliceE,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'brushFilename'
        QString,
        // Q_OBJECT / Q_GADGET
        DeclarativePieSlice,
        // method 'brushFilenameChanged'
        void,
        const QString &,
        // method 'handleBrushChanged'
        void
    >,
    nullptr
} };

void DeclarativePieSlice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativePieSlice *>(_o);
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
            using _q_method_type = void (DeclarativePieSlice::*)(const QString & );
            if (_q_method_type _q_method = &DeclarativePieSlice::brushFilenameChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
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

const QMetaObject *DeclarativePieSlice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativePieSlice::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN19DeclarativePieSliceE.stringdata0))
        return static_cast<void*>(this);
    return QPieSlice::qt_metacast(_clname);
}

int DeclarativePieSlice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPieSlice::qt_metacall(_c, _id, _a);
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
void DeclarativePieSlice::brushFilenameChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
namespace {
struct qt_meta_tag_ZN20DeclarativePieSeriesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN20DeclarativePieSeriesE = QtMocHelpers::stringData(
    "DeclarativePieSeries",
    "DefaultProperty",
    "seriesChildren",
    "QML.Element",
    "PieSeries",
    "QML.AddedInVersion",
    "256",
    "QML.ExtraVersion",
    "512",
    "sliceAdded",
    "",
    "QPieSlice*",
    "slice",
    "sliceRemoved",
    "handleAdded",
    "QList<QPieSlice*>",
    "slices",
    "handleRemoved",
    "at",
    "index",
    "find",
    "label",
    "append",
    "DeclarativePieSlice*",
    "value",
    "remove",
    "clear",
    "QQmlListProperty<QObject>"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN20DeclarativePieSeriesE[] = {

 // content:
      12,       // revision
       0,       // classname
       4,   14, // classinfo
       9,   22, // methods
       1,  103, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,
       7,    8,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,   76,   10, 0x06,    2 /* Public */,
      13,    1,   79,   10, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      14,    1,   82,   10, 0x0a,    6 /* Public */,
      17,    1,   85,   10, 0x0a,    8 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      18,    1,   88,   10, 0x02,   10 /* Public */,
      20,    1,   91,   10, 0x02,   12 /* Public */,
      22,    2,   94,   10, 0x02,   14 /* Public */,
      25,    1,   99,   10, 0x02,   17 /* Public */,
      26,    0,  102,   10, 0x02,   19 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 15,   16,

 // methods: parameters
    0x80000000 | 11, QMetaType::Int,   19,
    0x80000000 | 11, QMetaType::QString,   21,
    0x80000000 | 23, QMetaType::QString, QMetaType::QReal,   21,   24,
    QMetaType::Bool, 0x80000000 | 11,   12,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
       2, 0x80000000 | 27, 0x00015009, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject DeclarativePieSeries::staticMetaObject = { {
    QMetaObject::SuperData::link<QPieSeries::staticMetaObject>(),
    qt_meta_stringdata_ZN20DeclarativePieSeriesE.offsetsAndSizes,
    qt_meta_data_ZN20DeclarativePieSeriesE,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'seriesChildren'
        QQmlListProperty<QObject>,
        // Q_OBJECT / Q_GADGET
        DeclarativePieSeries,
        // method 'sliceAdded'
        void,
        QPieSlice *,
        // method 'sliceRemoved'
        void,
        QPieSlice *,
        // method 'handleAdded'
        void,
        const QList<QPieSlice*> &,
        // method 'handleRemoved'
        void,
        const QList<QPieSlice*> &,
        // method 'at'
        QPieSlice *,
        int,
        // method 'find'
        QPieSlice *,
        QString,
        // method 'append'
        DeclarativePieSlice *,
        QString,
        qreal,
        // method 'remove'
        bool,
        QPieSlice *,
        // method 'clear'
        void
    >,
    nullptr
} };

void DeclarativePieSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DeclarativePieSeries *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sliceAdded((*reinterpret_cast< std::add_pointer_t<QPieSlice*>>(_a[1]))); break;
        case 1: _t->sliceRemoved((*reinterpret_cast< std::add_pointer_t<QPieSlice*>>(_a[1]))); break;
        case 2: _t->handleAdded((*reinterpret_cast< std::add_pointer_t<QList<QPieSlice*>>>(_a[1]))); break;
        case 3: _t->handleRemoved((*reinterpret_cast< std::add_pointer_t<QList<QPieSlice*>>>(_a[1]))); break;
        case 4: { QPieSlice* _r = _t->at((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QPieSlice**>(_a[0]) = std::move(_r); }  break;
        case 5: { QPieSlice* _r = _t->find((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QPieSlice**>(_a[0]) = std::move(_r); }  break;
        case 6: { DeclarativePieSlice* _r = _t->append((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[2])));
            if (_a[0]) *reinterpret_cast< DeclarativePieSlice**>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->remove((*reinterpret_cast< std::add_pointer_t<QPieSlice*>>(_a[1])));
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
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QPieSlice* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QPieSlice* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QPieSlice*> >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QPieSlice*> >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QPieSlice* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (DeclarativePieSeries::*)(QPieSlice * );
            if (_q_method_type _q_method = &DeclarativePieSeries::sliceAdded; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (DeclarativePieSeries::*)(QPieSlice * );
            if (_q_method_type _q_method = &DeclarativePieSeries::sliceRemoved; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QQmlListProperty<QObject>*>(_v) = _t->seriesChildren(); break;
        default: break;
        }
    }
}

const QMetaObject *DeclarativePieSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeclarativePieSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN20DeclarativePieSeriesE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    return QPieSeries::qt_metacast(_clname);
}

int DeclarativePieSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPieSeries::qt_metacall(_c, _id, _a);
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
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void DeclarativePieSeries::sliceAdded(QPieSlice * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeclarativePieSeries::sliceRemoved(QPieSlice * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
