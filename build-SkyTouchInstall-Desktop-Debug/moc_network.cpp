/****************************************************************************
** Meta object code from reading C++ file 'network.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SkyTouchInstall/network.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'network.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Network_t {
    QByteArrayData data[33];
    char stringdata0[471];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Network_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Network_t qt_meta_stringdata_Network = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Network"
QT_MOC_LITERAL(1, 8, 3), // "get"
QT_MOC_LITERAL(2, 12, 0), // ""
QT_MOC_LITERAL(3, 13, 3), // "url"
QT_MOC_LITERAL(4, 17, 4), // "post"
QT_MOC_LITERAL(5, 22, 4), // "data"
QT_MOC_LITERAL(6, 27, 4), // "head"
QT_MOC_LITERAL(7, 32, 9), // "readyRead"
QT_MOC_LITERAL(8, 42, 22), // "authenticationRequired"
QT_MOC_LITERAL(9, 65, 14), // "QNetworkReply*"
QT_MOC_LITERAL(10, 80, 5), // "reply"
QT_MOC_LITERAL(11, 86, 15), // "QAuthenticator*"
QT_MOC_LITERAL(12, 102, 13), // "authenticator"
QT_MOC_LITERAL(13, 116, 9), // "encrypted"
QT_MOC_LITERAL(14, 126, 8), // "finished"
QT_MOC_LITERAL(15, 135, 20), // "networkAccessChanged"
QT_MOC_LITERAL(16, 156, 43), // "QNetworkAccessManager::Networ..."
QT_MOC_LITERAL(17, 200, 10), // "accessable"
QT_MOC_LITERAL(18, 211, 34), // "preSharedKeyAuthenticationReq..."
QT_MOC_LITERAL(19, 246, 30), // "QSslPreSharedKeyAuthenticator*"
QT_MOC_LITERAL(20, 277, 27), // "proxyAuthenticationRequired"
QT_MOC_LITERAL(21, 305, 13), // "QNetworkProxy"
QT_MOC_LITERAL(22, 319, 5), // "proxy"
QT_MOC_LITERAL(23, 325, 9), // "sslErrors"
QT_MOC_LITERAL(24, 335, 16), // "QList<QSslError>"
QT_MOC_LITERAL(25, 352, 6), // "errors"
QT_MOC_LITERAL(26, 359, 5), // "error"
QT_MOC_LITERAL(27, 365, 16), // "getAccessManager"
QT_MOC_LITERAL(28, 382, 22), // "QNetworkAccessManager*"
QT_MOC_LITERAL(29, 405, 12), // "getLastReply"
QT_MOC_LITERAL(30, 418, 9), // "getReplys"
QT_MOC_LITERAL(31, 428, 22), // "vector<QNetworkReply*>"
QT_MOC_LITERAL(32, 451, 19) // "closeAllConnections"

    },
    "Network\0get\0\0url\0post\0data\0head\0"
    "readyRead\0authenticationRequired\0"
    "QNetworkReply*\0reply\0QAuthenticator*\0"
    "authenticator\0encrypted\0finished\0"
    "networkAccessChanged\0"
    "QNetworkAccessManager::NetworkAccessibility\0"
    "accessable\0preSharedKeyAuthenticationRequired\0"
    "QSslPreSharedKeyAuthenticator*\0"
    "proxyAuthenticationRequired\0QNetworkProxy\0"
    "proxy\0sslErrors\0QList<QSslError>\0"
    "errors\0error\0getAccessManager\0"
    "QNetworkAccessManager*\0getLastReply\0"
    "getReplys\0vector<QNetworkReply*>\0"
    "closeAllConnections"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Network[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x0a /* Public */,
       4,    2,   97,    2, 0x0a /* Public */,
       6,    1,  102,    2, 0x0a /* Public */,
       7,    0,  105,    2, 0x0a /* Public */,
       8,    2,  106,    2, 0x0a /* Public */,
      13,    1,  111,    2, 0x0a /* Public */,
      14,    0,  114,    2, 0x0a /* Public */,
      15,    1,  115,    2, 0x0a /* Public */,
      18,    2,  118,    2, 0x0a /* Public */,
      20,    2,  123,    2, 0x0a /* Public */,
      23,    2,  128,    2, 0x0a /* Public */,
      26,    0,  133,    2, 0x0a /* Public */,
      27,    0,  134,    2, 0x0a /* Public */,
      29,    0,  135,    2, 0x0a /* Public */,
      30,    0,  136,    2, 0x0a /* Public */,
      32,    0,  137,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    3,    5,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11,   10,   12,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 19,   10,   12,
    QMetaType::Void, 0x80000000 | 21, 0x80000000 | 11,   22,   12,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 24,   10,   25,
    QMetaType::Void,
    0x80000000 | 28,
    0x80000000 | 9,
    0x80000000 | 31,
    QMetaType::Void,

       0        // eod
};

void Network::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Network *_t = static_cast<Network *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->get((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->post((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 2: _t->head((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->readyRead(); break;
        case 4: _t->authenticationRequired((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 5: _t->encrypted((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 6: _t->finished(); break;
        case 7: _t->networkAccessChanged((*reinterpret_cast< QNetworkAccessManager::NetworkAccessibility(*)>(_a[1]))); break;
        case 8: _t->preSharedKeyAuthenticationRequired((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< QSslPreSharedKeyAuthenticator*(*)>(_a[2]))); break;
        case 9: _t->proxyAuthenticationRequired((*reinterpret_cast< const QNetworkProxy(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 10: _t->sslErrors((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< const QList<QSslError>(*)>(_a[2]))); break;
        case 11: _t->error(); break;
        case 12: { QNetworkAccessManager* _r = _t->getAccessManager();
            if (_a[0]) *reinterpret_cast< QNetworkAccessManager**>(_a[0]) = std::move(_r); }  break;
        case 13: { QNetworkReply* _r = _t->getLastReply();
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = std::move(_r); }  break;
        case 14: { vector<QNetworkReply*> _r = _t->getReplys();
            if (_a[0]) *reinterpret_cast< vector<QNetworkReply*>*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->closeAllConnections(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSslPreSharedKeyAuthenticator* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkProxy >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    }
}

const QMetaObject Network::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Network.data,
      qt_meta_data_Network,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Network::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Network::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Network.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Network::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
struct qt_meta_stringdata_ProgressListenner_t {
    QByteArrayData data[5];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProgressListenner_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProgressListenner_t qt_meta_stringdata_ProgressListenner = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ProgressListenner"
QT_MOC_LITERAL(1, 18, 18), // "onDownloadProgress"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 13), // "bytesReceived"
QT_MOC_LITERAL(4, 52, 10) // "bytesTotal"

    },
    "ProgressListenner\0onDownloadProgress\0"
    "\0bytesReceived\0bytesTotal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProgressListenner[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    3,    4,

       0        // eod
};

void ProgressListenner::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProgressListenner *_t = static_cast<ProgressListenner *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onDownloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject ProgressListenner::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ProgressListenner.data,
      qt_meta_data_ProgressListenner,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ProgressListenner::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProgressListenner::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProgressListenner.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ProgressListenner::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE