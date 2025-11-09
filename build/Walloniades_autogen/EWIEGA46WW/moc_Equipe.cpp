/****************************************************************************
** Meta object code from reading C++ file 'Equipe.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Equipe.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Equipe.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN6EquipeE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN6EquipeE = QtMocHelpers::stringData(
    "Equipe",
    "ajouterParticipant",
    "",
    "nom",
    "prenom",
    "age",
    "sexe",
    "ajoutParticipant",
    "Participant*",
    "parti"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN6EquipeE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    4,   26,    2, 0x0a,    1 /* Public */,
       7,    1,   35,    2, 0x0a,    6 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QChar,    3,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

Q_CONSTINIT const QMetaObject Equipe::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QObject>::value,
    qt_meta_stringdata_ZN6EquipeE.offsetsAndSizes,
    qt_meta_data_ZN6EquipeE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN6EquipeE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Equipe, std::true_type>,
        // method 'ajouterParticipant'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString const &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString const &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int const &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QChar const &, std::false_type>,
        // method 'ajoutParticipant'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Participant *, std::false_type>
    >,
    nullptr
} };

QT_WARNING_POP
