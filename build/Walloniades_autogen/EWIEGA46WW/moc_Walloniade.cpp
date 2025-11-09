/****************************************************************************
** Meta object code from reading C++ file 'Walloniade.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Walloniade.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Walloniade.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10WalloniadeE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10WalloniadeE = QtMocHelpers::stringData(
    "Walloniade",
    "ajouterEquipe",
    "",
    "Equipe*",
    "newTeam",
    "ajouterEpreuve",
    "Epreuve*",
    "newEpreuve",
    "getEquipe",
    "supprimerEquipe",
    "i",
    "NomEquipe",
    "supprimerEpreuve",
    "getEpreuve"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10WalloniadeE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x02,    1 /* Public */,
       5,    1,   59,    2, 0x02,    3 /* Public */,
       8,    0,   62,    2, 0x02,    5 /* Public */,
       9,    1,   63,    2, 0x02,    6 /* Public */,
       9,    1,   66,    2, 0x02,    8 /* Public */,
      12,    1,   69,    2, 0x02,   10 /* Public */,
      13,    0,   72,    2, 0x02,   12 /* Public */,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Walloniade::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QObject>::value,
    qt_meta_stringdata_ZN10WalloniadeE.offsetsAndSizes,
    qt_meta_data_ZN10WalloniadeE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10WalloniadeE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Walloniade, std::true_type>,
        // method 'ajouterEquipe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Equipe *, std::false_type>,
        // method 'ajouterEpreuve'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Epreuve *, std::false_type>,
        // method 'getEquipe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'supprimerEquipe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'supprimerEquipe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'supprimerEpreuve'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'getEpreuve'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Walloniade::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<Walloniade *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->ajouterEquipe((*reinterpret_cast< std::add_pointer_t<Equipe*>>(_a[1]))); break;
        case 1: _t->ajouterEpreuve((*reinterpret_cast< std::add_pointer_t<Epreuve*>>(_a[1]))); break;
        case 2: _t->getEquipe(); break;
        case 3: _t->supprimerEquipe((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->supprimerEquipe((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->supprimerEpreuve((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->getEpreuve(); break;
        default: ;
        }
    }
}
QT_WARNING_POP
