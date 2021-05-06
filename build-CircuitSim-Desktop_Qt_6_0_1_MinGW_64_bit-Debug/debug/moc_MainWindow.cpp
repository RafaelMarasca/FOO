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
    const uint offsetsAndSize[38];
    char stringdata0[200];
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
QT_MOC_LITERAL(49, 10), // "setBGColor"
QT_MOC_LITERAL(60, 12), // "setGridColor"
QT_MOC_LITERAL(73, 17), // "setComponentColor"
QT_MOC_LITERAL(91, 16), // "setSelectedColor"
QT_MOC_LITERAL(108, 11), // "resetConfig"
QT_MOC_LITERAL(120, 12), // "setTabStatus"
QT_MOC_LITERAL(133, 8), // "modified"
QT_MOC_LITERAL(142, 9), // "closeFile"
QT_MOC_LITERAL(152, 5), // "index"
QT_MOC_LITERAL(158, 9), // "drawRes90"
QT_MOC_LITERAL(168, 10), // "drawRes180"
QT_MOC_LITERAL(179, 9), // "drawVcc90"
QT_MOC_LITERAL(189, 10) // "drawVcc180"

    },
    "MainWindow\0newFile\0\0openFile\0saveFile\0"
    "saveFileAs\0setBGColor\0setGridColor\0"
    "setComponentColor\0setSelectedColor\0"
    "resetConfig\0setTabStatus\0modified\0"
    "closeFile\0index\0drawRes90\0drawRes180\0"
    "drawVcc90\0drawVcc180"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x0a,    0 /* Public */,
       3,    0,  105,    2, 0x0a,    1 /* Public */,
       4,    0,  106,    2, 0x0a,    2 /* Public */,
       5,    0,  107,    2, 0x0a,    3 /* Public */,
       6,    0,  108,    2, 0x0a,    4 /* Public */,
       7,    0,  109,    2, 0x0a,    5 /* Public */,
       8,    0,  110,    2, 0x0a,    6 /* Public */,
       9,    0,  111,    2, 0x0a,    7 /* Public */,
      10,    0,  112,    2, 0x0a,    8 /* Public */,
      11,    1,  113,    2, 0x0a,    9 /* Public */,
      13,    1,  116,    2, 0x0a,   11 /* Public */,
      15,    0,  119,    2, 0x0a,   13 /* Public */,
      16,    0,  120,    2, 0x0a,   14 /* Public */,
      17,    0,  121,    2, 0x0a,   15 /* Public */,
      18,    0,  122,    2, 0x0a,   16 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Int,   14,
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
        case 4: _t->setBGColor(); break;
        case 5: _t->setGridColor(); break;
        case 6: _t->setComponentColor(); break;
        case 7: _t->setSelectedColor(); break;
        case 8: _t->resetConfig(); break;
        case 9: _t->setTabStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->closeFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->drawRes90(); break;
        case 12: _t->drawRes180(); break;
        case 13: _t->drawVcc90(); break;
        case 14: _t->drawVcc180(); break;
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

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
