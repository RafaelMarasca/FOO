/****************************************************************************
** Meta object code from reading C++ file 'Diagram.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CircuitSim/Diagram.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Diagram.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Diagram_t {
    QByteArrayData data[7];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Diagram_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Diagram_t qt_meta_stringdata_Diagram = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Diagram"
QT_MOC_LITERAL(1, 8, 8), // "modified"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 7), // "checked"
QT_MOC_LITERAL(4, 26, 9), // "loadError"
QT_MOC_LITERAL(5, 36, 7), // "upScale"
QT_MOC_LITERAL(6, 44, 9) // "downScale"

    },
    "Diagram\0modified\0\0checked\0loadError\0"
    "upScale\0downScale"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Diagram[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       1,    0,   47,    2, 0x26 /* Public | MethodCloned */,
       4,    1,   48,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x26 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Diagram::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Diagram *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->modified((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->modified(); break;
        case 2: _t->loadError((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->loadError(); break;
        case 4: _t->upScale(); break;
        case 5: _t->downScale(); break;
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
    }
}

QT_INIT_METAOBJECT const QMetaObject Diagram::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Diagram.data,
    qt_meta_data_Diagram,
    qt_static_metacall,
    nullptr,
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
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Diagram::modified(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void Diagram::loadError(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE