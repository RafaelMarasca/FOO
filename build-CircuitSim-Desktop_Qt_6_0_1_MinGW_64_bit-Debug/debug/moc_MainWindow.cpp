/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../CircuitSim/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[40];
    char stringdata0[209];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 7), // "newFile"
QT_MOC_LITERAL(19, 0), // ""
QT_MOC_LITERAL(20, 8), // "openFile"
QT_MOC_LITERAL(29, 8), // "saveFile"
QT_MOC_LITERAL(38, 10), // "saveFileAs"
QT_MOC_LITERAL(49, 12), // "setTabStatus"
QT_MOC_LITERAL(62, 8), // "modified"
QT_MOC_LITERAL(71, 9), // "closeFile"
QT_MOC_LITERAL(81, 5), // "index"
QT_MOC_LITERAL(87, 8), // "tutorial"
QT_MOC_LITERAL(96, 9), // "drawRes90"
QT_MOC_LITERAL(106, 10), // "drawRes180"
QT_MOC_LITERAL(117, 9), // "drawVcc90"
QT_MOC_LITERAL(127, 10), // "drawVcc180"
QT_MOC_LITERAL(138, 10), // "setBGColor"
QT_MOC_LITERAL(149, 12), // "setGridColor"
QT_MOC_LITERAL(162, 17), // "setComponentColor"
QT_MOC_LITERAL(180, 16), // "setSelectedColor"
QT_MOC_LITERAL(197, 11) // "resetConfig"

    },
    "MainWindow\0newFile\0\0openFile\0saveFile\0"
    "saveFileAs\0setTabStatus\0modified\0"
    "closeFile\0index\0tutorial\0drawRes90\0"
    "drawRes180\0drawVcc90\0drawVcc180\0"
    "setBGColor\0setGridColor\0setComponentColor\0"
    "setSelectedColor\0resetConfig"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  110,    2, 0x0a,    0 /* Public */,
       3,    0,  111,    2, 0x0a,    1 /* Public */,
       4,    0,  112,    2, 0x0a,    2 /* Public */,
       5,    0,  113,    2, 0x0a,    3 /* Public */,
       6,    1,  114,    2, 0x0a,    4 /* Public */,
       8,    1,  117,    2, 0x0a,    6 /* Public */,
      10,    0,  120,    2, 0x0a,    8 /* Public */,
      11,    0,  121,    2, 0x0a,    9 /* Public */,
      12,    0,  122,    2, 0x0a,   10 /* Public */,
      13,    0,  123,    2, 0x0a,   11 /* Public */,
      14,    0,  124,    2, 0x0a,   12 /* Public */,
      15,    0,  125,    2, 0x0a,   13 /* Public */,
      16,    0,  126,    2, 0x0a,   14 /* Public */,
      17,    0,  127,    2, 0x0a,   15 /* Public */,
      18,    0,  128,    2, 0x0a,   16 /* Public */,
      19,    0,  129,    2, 0x0a,   17 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newFile(); break;
        case 1: _t->openFile(); break;
        case 2: _t->saveFile(); break;
        case 3: _t->saveFileAs(); break;
        case 4: _t->setTabStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->closeFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->tutorial(); break;
        case 7: _t->drawRes90(); break;
        case 8: _t->drawRes180(); break;
        case 9: _t->drawVcc90(); break;
        case 10: _t->drawVcc180(); break;
        case 11: _t->setBGColor(); break;
        case 12: _t->setGridColor(); break;
        case 13: _t->setComponentColor(); break;
        case 14: _t->setSelectedColor(); break;
        case 15: _t->resetConfig(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
