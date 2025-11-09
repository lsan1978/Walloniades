/****************************************************************************
** Meta object code from reading C++ file 'w_consultermodifierequipe.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../w_consultermodifierequipe.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'w_consultermodifierequipe.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN25W_ConsulterModifierEquipeE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN25W_ConsulterModifierEquipeE = QtMocHelpers::stringData(
    "W_ConsulterModifierEquipe",
    "ParticipantAcquired",
    "",
    "Participant*",
    "acceptAndRefresh",
    "displayListeParticipants",
    "Equipe*",
    "equipe",
    "supprimerParticipant",
    "QListWidgetItem*",
    "item",
    "ProvideContextMenu",
    "pos",
    "supprimerParticipantSelectionne"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN25W_ConsulterModifierEquipeE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   53,    2, 0x0a,    3 /* Public */,
       5,    1,   54,    2, 0x0a,    4 /* Public */,
       8,    1,   57,    2, 0x0a,    6 /* Public */,
      11,    1,   60,    2, 0x0a,    8 /* Public */,
      13,    0,   63,    2, 0x0a,   10 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QPoint,   12,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject W_ConsulterModifierEquipe::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ZN25W_ConsulterModifierEquipeE.offsetsAndSizes,
    qt_meta_data_ZN25W_ConsulterModifierEquipeE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN25W_ConsulterModifierEquipeE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<W_ConsulterModifierEquipe, std::true_type>,
        // method 'ParticipantAcquired'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Participant *, std::false_type>,
        // method 'acceptAndRefresh'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'displayListeParticipants'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Equipe *, std::false_type>,
        // method 'supprimerParticipant'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'ProvideContextMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>,
        // method 'supprimerParticipantSelectionne'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void W_ConsulterModifierEquipe::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<W_ConsulterModifierEquipe *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->ParticipantAcquired((*reinterpret_cast< std::add_pointer_t<Participant*>>(_a[1]))); break;
        case 1: _t->acceptAndRefresh(); break;
        case 2: _t->displayListeParticipants((*reinterpret_cast< std::add_pointer_t<Equipe*>>(_a[1]))); break;
        case 3: _t->supprimerParticipant((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 4: _t->ProvideContextMenu((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 5: _t->supprimerParticipantSelectionne(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (W_ConsulterModifierEquipe::*)(Participant * );
            if (_q_method_type _q_method = &W_ConsulterModifierEquipe::ParticipantAcquired; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *W_ConsulterModifierEquipe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *W_ConsulterModifierEquipe::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN25W_ConsulterModifierEquipeE.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int W_ConsulterModifierEquipe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void W_ConsulterModifierEquipe::ParticipantAcquired(Participant * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
