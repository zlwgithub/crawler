/****************************************************************************
** Meta object code from reading C++ file 'service.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../service.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Service_t {
    QByteArrayData data[7];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Service_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Service_t qt_meta_stringdata_Service = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Service"
QT_MOC_LITERAL(1, 8, 25), // "GET_QRCODE_MSG_ACK_Signal"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 2), // "qs"
QT_MOC_LITERAL(4, 38, 29), // "QRCODE_CONFIRM_MSG_ACK_Signal"
QT_MOC_LITERAL(5, 68, 26), // "START_CRAWL_MSG_ACK_Signal"
QT_MOC_LITERAL(6, 95, 30) // "CURRENT_PROGESS_MSG_ACK_Signal"

    },
    "Service\0GET_QRCODE_MSG_ACK_Signal\0\0"
    "qs\0QRCODE_CONFIRM_MSG_ACK_Signal\0"
    "START_CRAWL_MSG_ACK_Signal\0"
    "CURRENT_PROGESS_MSG_ACK_Signal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Service[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,
       5,    1,   40,    2, 0x06 /* Public */,
       6,    1,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void Service::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Service *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->GET_QRCODE_MSG_ACK_Signal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->QRCODE_CONFIRM_MSG_ACK_Signal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->START_CRAWL_MSG_ACK_Signal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->CURRENT_PROGESS_MSG_ACK_Signal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Service::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Service::GET_QRCODE_MSG_ACK_Signal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Service::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Service::QRCODE_CONFIRM_MSG_ACK_Signal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Service::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Service::START_CRAWL_MSG_ACK_Signal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Service::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Service::CURRENT_PROGESS_MSG_ACK_Signal)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Service::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_Service.data,
    qt_meta_data_Service,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Service::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Service::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Service.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int Service::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Service::GET_QRCODE_MSG_ACK_Signal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Service::QRCODE_CONFIRM_MSG_ACK_Signal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Service::START_CRAWL_MSG_ACK_Signal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Service::CURRENT_PROGESS_MSG_ACK_Signal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
