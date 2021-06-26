/****************************************************************************
** Meta object code from reading C++ file 'gamecontrol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../main/gamecontrol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamecontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameControl_t {
    QByteArrayData data[12];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameControl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameControl_t qt_meta_stringdata_GameControl = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GameControl"
QT_MOC_LITERAL(1, 12, 23), // "callGamewindowShowCards"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 22), // "callGamewindowShowBets"
QT_MOC_LITERAL(4, 60, 7), // "Player*"
QT_MOC_LITERAL(5, 68, 26), // "callGamewindowShowLandlord"
QT_MOC_LITERAL(6, 95, 20), // "NotifyPlayerPlayHand"
QT_MOC_LITERAL(7, 116, 6), // "player"
QT_MOC_LITERAL(8, 123, 11), // "CardGroups&"
QT_MOC_LITERAL(9, 135, 5), // "cards"
QT_MOC_LITERAL(10, 141, 18), // "NotifyPlayerbutton"
QT_MOC_LITERAL(11, 160, 18) // "NotifyPlayerStatus"

    },
    "GameControl\0callGamewindowShowCards\0"
    "\0callGamewindowShowBets\0Player*\0"
    "callGamewindowShowLandlord\0"
    "NotifyPlayerPlayHand\0player\0CardGroups&\0"
    "cards\0NotifyPlayerbutton\0NotifyPlayerStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameControl[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,
       5,    0,   48,    2, 0x06 /* Public */,
       6,    2,   49,    2, 0x06 /* Public */,
      10,    1,   54,    2, 0x06 /* Public */,
      11,    1,   57,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 8,    7,    9,
    QMetaType::Void, 0x80000000 | 4,    7,
    QMetaType::Void, 0x80000000 | 4,    7,

       0        // eod
};

void GameControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameControl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->callGamewindowShowCards(); break;
        case 1: _t->callGamewindowShowBets((*reinterpret_cast< Player*(*)>(_a[1]))); break;
        case 2: _t->callGamewindowShowLandlord(); break;
        case 3: _t->NotifyPlayerPlayHand((*reinterpret_cast< Player*(*)>(_a[1])),(*reinterpret_cast< CardGroups(*)>(_a[2]))); break;
        case 4: _t->NotifyPlayerbutton((*reinterpret_cast< Player*(*)>(_a[1]))); break;
        case 5: _t->NotifyPlayerStatus((*reinterpret_cast< Player*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameControl::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameControl::callGamewindowShowCards)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GameControl::*)(Player * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameControl::callGamewindowShowBets)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GameControl::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameControl::callGamewindowShowLandlord)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GameControl::*)(Player * , CardGroups & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameControl::NotifyPlayerPlayHand)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GameControl::*)(Player * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameControl::NotifyPlayerbutton)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GameControl::*)(Player * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameControl::NotifyPlayerStatus)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GameControl::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GameControl.data,
    qt_meta_data_GameControl,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GameControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameControl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameControl.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GameControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void GameControl::callGamewindowShowCards()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GameControl::callGamewindowShowBets(Player * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GameControl::callGamewindowShowLandlord()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GameControl::NotifyPlayerPlayHand(Player * _t1, CardGroups & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GameControl::NotifyPlayerbutton(Player * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GameControl::NotifyPlayerStatus(Player * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
