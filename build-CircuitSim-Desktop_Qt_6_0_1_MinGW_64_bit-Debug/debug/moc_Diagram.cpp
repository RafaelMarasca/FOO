/****************************************************************************
** Meta object code from reading C++ file 'Diagram.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../CircuitSim/Diagram.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Diagram.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Diagram_t {
    const uint offsetsAndSize[38];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Diagram_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Diagram_t qt_meta_stringdata_Diagram = {
    {
QT_MOC_LITERAL(0, 7), // "Diagram"
QT_MOC_LITERAL(8, 8), // "modified"
QT_MOC_LITERAL(17, 0), // ""
QT_MOC_LITERAL(18, 7), // "checked"
QT_MOC_LITERAL(26, 9), // "loadError"
QT_MOC_LITERAL(36, 13), // "statusBarText"
QT_MOC_LITERAL(50, 3), // "str"
QT_MOC_LITERAL(54, 9), // "queryMode"
QT_MOC_LITERAL(64, 8), // "editMode"
QT_MOC_LITERAL(73, 18), // "rightButtonClicked"
QT_MOC_LITERAL(92, 1), // "x"
QT_MOC_LITERAL(94, 1), // "y"
QT_MOC_LITERAL(96, 5), // "cArea"
QT_MOC_LITERAL(102, 17), // "leftButtonClicked"
QT_MOC_LITERAL(120, 14), // "showEditDialog"
QT_MOC_LITERAL(135, 4), // "edit"
QT_MOC_LITERAL(140, 8), // "newValue"
QT_MOC_LITERAL(149, 6), // "remove"
QT_MOC_LITERAL(156, 5) // "query"

    },
    "Diagram\0modified\0\0checked\0loadError\0"
    "statusBarText\0str\0queryMode\0editMode\0"
    "rightButtonClicked\0x\0y\0cArea\0"
    "leftButtonClicked\0showEditDialog\0edit\0"
    "newValue\0remove\0query"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Diagram[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   92,    2, 0x06,    0 /* Public */,
       1,    0,   95,    2, 0x26,    2 /* Public | MethodCloned */,
       4,    1,   96,    2, 0x06,    3 /* Public */,
       4,    0,   99,    2, 0x26,    5 /* Public | MethodCloned */,
       5,    1,  100,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,  103,    2, 0x0a,    8 /* Public */,
       8,    0,  104,    2, 0x0a,    9 /* Public */,
       9,    3,  105,    2, 0x0a,   10 /* Public */,
      13,    3,  112,    2, 0x0a,   14 /* Public */,
      14,    0,  119,    2, 0x0a,   18 /* Public */,
      15,    1,  120,    2, 0x0a,   19 /* Public */,
      17,    0,  123,    2, 0x0a,   21 /* Public */,
      18,    0,  124,    2, 0x0a,   22 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   10,   11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   10,   11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   16,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Diagram::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Diagram *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->modified((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->modified(); break;
        case 2: _t->loadError((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->loadError(); break;
        case 4: _t->statusBarText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->queryMode(); break;
        case 6: _t->editMode(); break;
        case 7: _t->rightButtonClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 8: _t->leftButtonClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: _t->showEditDialog(); break;
        case 10: _t->edit((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->remove(); break;
        case 12: _t->query(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Diagram::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Diagram::modified)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Diagram::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Diagram::loadError)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Diagram::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Diagram::statusBarText)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject Diagram::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Diagram.offsetsAndSize,
    qt_meta_data_Diagram,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Diagram_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *Diagram::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Diagram::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Diagram.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Diagram::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Diagram::modified(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void Diagram::loadError(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void Diagram::statusBarText(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
