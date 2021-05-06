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
    const uint offsetsAndSize[2];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_GraphicComponent_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_GraphicComponent_t qt_meta_stringdata_GraphicComponent = {
    {
QT_MOC_LITERAL(0, 16) // "GraphicComponent"

    },
    "GraphicComponent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicComponent[] = {

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

void GraphicComponent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject GraphicComponent::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GraphicComponent.offsetsAndSize,
    qt_meta_data_GraphicComponent,
    qt_static_metacall,
    nullptr,
    nullptr,
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
    return _id;
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
