/****************************************************************************
** Meta object code from reading C++ file 'gamewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../main/gamewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameWindow_t {
    QByteArrayData data[19];
    char stringdata0[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameWindow_t qt_meta_stringdata_GameWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GameWindow"
QT_MOC_LITERAL(1, 11, 17), // "onStartBtnClicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 17), // "onBetNoBtnClicked"
QT_MOC_LITERAL(4, 48, 16), // "onBet1BtnClicked"
QT_MOC_LITERAL(5, 65, 16), // "onBet2BtnClicked"
QT_MOC_LITERAL(6, 82, 16), // "onBet3BtnClicked"
QT_MOC_LITERAL(7, 99, 15), // "onBetPointsCall"
QT_MOC_LITERAL(8, 115, 7), // "Player*"
QT_MOC_LITERAL(9, 123, 6), // "player"
QT_MOC_LITERAL(10, 130, 12), // "cardSelected"
QT_MOC_LITERAL(11, 143, 15), // "Qt::MouseButton"
QT_MOC_LITERAL(12, 159, 11), // "mouseButton"
QT_MOC_LITERAL(13, 171, 9), // "playCards"
QT_MOC_LITERAL(14, 181, 9), // "passCards"
QT_MOC_LITERAL(15, 191, 20), // "otherPlayerShowCards"
QT_MOC_LITERAL(16, 212, 10), // "CardGroups"
QT_MOC_LITERAL(17, 223, 5), // "cards"
QT_MOC_LITERAL(18, 229, 18) // "myPlayerShowButton"

    },
    "GameWindow\0onStartBtnClicked\0\0"
    "onBetNoBtnClicked\0onBet1BtnClicked\0"
    "onBet2BtnClicked\0onBet3BtnClicked\0"
    "onBetPointsCall\0Player*\0player\0"
    "cardSelected\0Qt::MouseButton\0mouseButton\0"
    "playCards\0passCards\0otherPlayerShowCards\0"
    "CardGroups\0cards\0myPlayerShowButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    1,   74,    2, 0x0a /* Public */,
      10,    1,   77,    2, 0x0a /* Public */,
      13,    0,   80,    2, 0x0a /* Public */,
      14,    0,   81,    2, 0x0a /* Public */,
      15,    2,   82,    2, 0x0a /* Public */,
      18,    1,   87,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 16,    9,   17,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void GameWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onStartBtnClicked(); break;
        case 1: _t->onBetNoBtnClicked(); break;
        case 2: _t->onBet1BtnClicked(); break;
        case 3: _t->onBet2BtnClicked(); break;
        case 4: _t->onBet3BtnClicked(); break;
        case 5: _t->onBetPointsCall((*reinterpret_cast< Player*(*)>(_a[1]))); break;
        case 6: _t->cardSelected((*reinterpret_cast< Qt::MouseButton(*)>(_a[1]))); break;
        case 7: _t->playCards(); break;
        case 8: _t->passCards(); break;
        case 9: _t->otherPlayerShowCards((*reinterpret_cast< Player*(*)>(_a[1])),(*reinterpret_cast< CardGroups(*)>(_a[2]))); break;
        case 10: _t->myPlayerShowButton((*reinterpret_cast< Player*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GameWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_GameWindow.data,
    qt_meta_data_GameWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GameWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int GameWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
