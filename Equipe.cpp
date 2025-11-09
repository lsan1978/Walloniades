#include "Equipe.h"
#include <QDebug>

Equipe::Equipe(QString const& nom, Capitaine *capi, int nombreParticipants)
{
    m_nom=nom;
    m_capi=capi;
    m_nombreParticipants=nombreParticipants;
    Participant * parti = new Participant(capi->getNomParticipant(),capi->getPrenomParticipant(), capi->getAgeParticipant(), capi->getSexeParticipant());
    m_listeParticipants.append(parti);
    m_ID=0;
    m_totalPoints=0;
    m_nbrePremierePlace=0;
    m_nbreDeuxiemePlace=0;
    m_nbreTroisiemePlace=0;
    
}

Equipe::Equipe(const Equipe& other) 
{
    this->m_nom = other.m_nom;
    this->m_ID = other.m_ID;
    this->m_totalPoints = other.m_totalPoints;
    this->m_nbrePremierePlace = other.m_nbrePremierePlace;
    this->m_nbreDeuxiemePlace = other.m_nbreDeuxiemePlace;
    this->m_nbreTroisiemePlace = other.m_nbreTroisiemePlace;
    //this->m_Points = other.m_Points;
}






Equipe::~Equipe()
{
    for (int i=0; i<m_listeParticipants.size(); i++)
        {
            delete m_listeParticipants[i];
            m_listeParticipants[i]=NULL;
        }
}

void Equipe::ajouterParticipant(QString const& nom, QString const& prenom, int const& age, QChar const& sexe)
{
    m_listeParticipants.append(new Participant(nom,prenom,age,sexe));
}
void Equipe::ajoutParticipant(Participant* parti)
{
    m_listeParticipants.append(parti);
}

QString Equipe::getNomEquipe()
{
    return m_nom;
}

Capitaine * Equipe::getCapi()
{
    return m_capi;
}

int Equipe::getNombreParticipants()
{
    return m_nombreParticipants;
}

int Equipe::getID()
{
    return m_ID;
}

QList<Participant*> Equipe::getListeParticipants()
{
    return m_listeParticipants;
}

void Equipe::supprimerParticipant(int i)
{

    delete m_listeParticipants[i];
    m_listeParticipants.removeAt(i);


}

void Equipe::supprimerCapitaine()
{

    delete m_capi;
    m_capi=NULL;


}

void Equipe::setID(int numero)
{
    m_ID=numero;
}

void Equipe::ajouterResultat(int points)
{
    m_Points.append(points);
}

void Equipe::increaseNombrePremierePlace()
{
    m_nbrePremierePlace++;
}

void Equipe::increaseNombreDeuxiemePlace()
{
    m_nbreDeuxiemePlace++;
}

void Equipe::increaseNombreTroisiemePlace()
{
    m_nbreTroisiemePlace++;
}

int Equipe::getNbrePremierePlace()
{
    return m_nbrePremierePlace;
}

int Equipe::getNbreDeuxiemePlace()
{
    return m_nbreDeuxiemePlace;
}

int Equipe::getNbreTroisiemePlace()
{
    return m_nbreTroisiemePlace;
}

int Equipe::getTotalPoints()
{
    return m_totalPoints;
}

/*QList<int> Equipe::getPoints()
{
    return m_Points;
}*/

/*void Equipe::SetTotalPoints(int TotalPoints)
{
    m_totalPoints=TotalPoints;
}*/

//void Equipe::setPoints(QList<int> points)
//{
//    m_Points=points;
//}
//

void Equipe::resetNombrePremierePlace()
{
    m_nbrePremierePlace=0;
}

void Equipe::resetNombreDeuxiemePlace()
{
    m_nbreDeuxiemePlace=0;
}

void Equipe::resetNombreTroisiemePlace()
{
    m_nbreTroisiemePlace=0;
}


void Equipe::resetTotalPoints()
{
    m_totalPoints=0;
}

/*void Equipe::resetPoints()
{
    m_Points.clear();
}*/

void Equipe::increaseTotalPoints(int points)
{
    m_totalPoints+=points;
}