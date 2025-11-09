#include "Participant.h"

Participant::Participant(QString const& nom, QString const& prenom, int age, QChar sexe)
{
    m_nom=nom;
    m_prenom=prenom;
    m_age=age;
    m_sexe=sexe;
}

Participant::~Participant()
{

}

QString Participant::getNomParticipant()
{
    return m_nom;
}

QString Participant::getPrenomParticipant()
{
    return m_prenom;
}

int Participant::getAgeParticipant()
{
    return m_age;
}

QChar Participant::getSexeParticipant()
{
    return m_sexe;
}
