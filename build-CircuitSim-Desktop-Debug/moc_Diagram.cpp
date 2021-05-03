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
    QByteArrayData data[17];
    char stringdata0[144];
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
QT_MOC_LITERAL(5, 36, 9), // "queryMode"
QT_MOC_LITERAL(6, 46, 8), // "editMode"
QT_MOC_LITERAL(7, 55, 18), // "rightButtonClicked"
QT_MOC_LITERAL(8, 74, 1), // "x"
QT_MOC_LITERAL(9, 76, 1), // "y"
QT_MOC_LITERAL(10, 78, 5), // "cArea"
QT_MOC_LITERAL(11, 84, 17), // "leftButtonClicked"
QT_MOC_LITERAL(12, 102, 14), // "showEditDialog"
QT_MOC_LITERAL(13, 117, 4), // "edit"
QT_MOC_LITERAL(14, 122, 8), // "newValue"
QT_MOC_LITERAL(15, 131, 6), // "remove"
QT_MOC_LITERAL(16, 138, 5) // "query"

    },
    "Diagram\0modified\0\0checked\0loadError\0"
    "queryMode\0editMode\0rightButtonClicked\0"
    "x\0y\0cArea\0leftButtonClicked\0showEditDialog\0"
    "edit\0newValue\0remove\0query"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Diagram[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       1,    0,   77,    2, 0x26 /* Public | MethodCloned */,
       4,    1,   78,    2, 0x06 /* Public */,
       4,    0,   81,    2, 0x26 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    3,   84,    2, 0x0a /* Public */,
      11,    3,   91,    2, 0x0a /* Public */,
      12,    0,   98,    2, 0x0a /* Public */,
      13,    1,   99,    2, 0x0a /* Public */,
      15,    0,  102,    2, 0x0a /* Public */,
      16,    0,  103,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    8,    9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    8,    9,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   14,
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
        case 4: _t->queryMode(); break;
        case 5: _t->editMode(); break;
        case 6: _t->rightButtonClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: _t->leftButtonClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 8: _t->showEditDialog(); break;
        case 9: _t->edit((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->remove(); break;
        case 11: _t->query(); break;
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
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
