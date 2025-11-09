#ifndef CAPITAINE_H
#define CAPITAINE_H
#include "Participant.h"
#include <QString>

class Capitaine : public Participant
{
public:
    Capitaine(QString const& nom, QString const& prenom, int age, QChar sexe, QString const& telephone, QString const& mail, QString const& rueNumeroBoite, QString CP, QString localite);
    ~Capitaine();
    QString getMail();
    QString getTelephone();
    QString getRueNumeroBoite();
    QString getCP();
    QString getLocalite();
protected:

    QString m_telephone;
    QString m_mail;
    QString m_rueNumeroBoite;
    QString m_CP;
    QString m_localite;
};

#endif // CAPITAINE_H
