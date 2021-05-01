/****************************************************************************
** Meta object code from reading C++ file 'GraphicComponent.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../CircuitSim/GraphicComponent.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GraphicComponent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GraphicComponent_t {
    const uint offsetsAndSize[14];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_GraphicComponent_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_GraphicComponent_t qt_meta_stringdata_GraphicComponent = {
    {
QT_MOC_LITERAL(0, 16), // "GraphicComponent"
QT_MOC_LITERAL(17, 13), // "clickedVertex"
QT_MOC_LITERAL(31, 0), // ""
QT_MOC_LITERAL(32, 4), // "Area"
QT_MOC_LITERAL(37, 17), // "GraphicComponent*"
QT_MOC_LITERAL(55, 7), // "clicked"
QT_MOC_LITERAL(63, 7) // "checked"

    },
    "GraphicComponent\0clickedVertex\0\0Area\0"
    "GraphicComponent*\0clicked\0checked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicComponent[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   32,    2, 0x06,    0 /* Public */,
       5,    1,   37,    2, 0x06,    3 /* Public */,
       5,    0,   40,    2, 0x26,    5 /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    2,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,

       0        // eod
};

void GraphicComponent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GraphicComponent *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clickedVertex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< GraphicComponent*(*)>(_a[2]))); break;
        case 1: _t->clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< GraphicComponent* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GraphicComponent::*)(int , GraphicComponent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GraphicComponent::clickedVertex)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GraphicComponent::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GraphicComponent::clicked)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject GraphicComponent::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GraphicComponent.offsetsAndSize,
    qt_meta_data_GraphicComponent,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_GraphicComponent_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<GraphicComponent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *GraphicComponent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicComponent::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicComponent.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GraphicComponent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void GraphicComponent::clickedVertex(int _t1, GraphicComponent * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GraphicComponent::clicked(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_Resistor_t {
    const uint offsetsAndSize[2];
    char stringdata0[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Resistor_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Resistor_t qt_meta_stringdata_Resistor = {
    {
QT_MOC_LITERAL(0, 8) // "Resistor"

    },
    "Resistor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Resistor[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Resistor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject Resistor::staticMetaObject = { {
    QMetaObject::SuperData::link<GraphicComponent::staticMetaObject>(),
    qt_meta_stringdata_Resistor.offsetsAndSize,
    qt_meta_data_Resistor,
    qt_static_metacall,
    nullptr,
    nullptr,
    nullptr
} };


const QMetaObject *Resistor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Resistor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Resistor.stringdata0))
        return static_cast<void*>(this);
    return GraphicComponent::qt_metacast(_clname);
}

int Resistor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GraphicComponent::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_Vcc_t {
    const uint offsetsAndSize[2];
    char stringdata0[4];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Vcc_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Vcc_t qt_meta_stringdata_Vcc = {
    {
QT_MOC_LITERAL(0, 3) // "Vcc"

    },
    "Vcc"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Vcc[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Vcc::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject Vcc::staticMetaObject = { {
    QMetaObject::SuperData::link<GraphicComponent::staticMetaObject>(),
    qt_meta_stringdata_Vcc.offsetsAndSize,
    qt_meta_data_Vcc,
    qt_static_metacall,
    nullptr,
    nullptr,
    nullptr
} };


const QMetaObject *Vcc::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Vcc::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Vcc.stringdata0))
        return static_cast<void*>(this);
    return GraphicComponent::qt_metacast(_clname);
}

int Vcc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GraphicComponent::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
