#include "Capitaine.h"
#include <QString>

Capitaine::Capitaine(QString const& nom, QString const& prenom, int age, QChar sexe, QString const& telephone, QString const& mail, QString const& rueNumeroBoite, QString CP, QString localite) : Participant(nom, prenom, age, sexe)
{
    m_telephone=telephone;
    m_mail=mail;
    m_rueNumeroBoite=rueNumeroBoite;
    m_CP=CP;
    m_localite=localite;
}


Capitaine::~Capitaine()
{

}

QString Capitaine::getMail()
{
    return m_mail;
}

QString Capitaine::getTelephone()
{
    return m_telephone;
}

QString Capitaine::getRueNumeroBoite()
{
    return m_rueNumeroBoite;
}

QString Capitaine::getCP()
{
    return m_CP;
}

QString Capitaine::getLocalite()
{
    return m_localite;
}
