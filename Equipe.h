#ifndef EQUIPE_H
#define EQUIPE_H
#include <QString>
#include <vector>
#include <QObject>
#include "Capitaine.h"
#include "Participant.h"

typedef struct
{
    int EquipeID;
    QString NomEquipe;
    int TotalPoints;
	int nbrePremierePlace;
    int nbreDeuxiemePlace;
    int nbreTroisiemePlace;
	
} CopyTeam;



class Equipe : public QObject
{
    Q_GADGET
public:
    Equipe(QString const& nom, Capitaine *capi, int nombreParticipants);
    Equipe(const Equipe& other);
    ~Equipe();

    QString getNomEquipe();
    Capitaine * getCapi();
    QList<Participant*> getListeParticipants();
    int getNombreParticipants();
    int getID();
    void supprimerParticipant(int i);
    void supprimerCapitaine();
    void setID(int numero);
    void ajouterResultat(int points);
    void increaseNombrePremierePlace();
    void increaseNombreDeuxiemePlace();
    void increaseNombreTroisiemePlace();
    void resetNombrePremierePlace();
    void resetNombreDeuxiemePlace();
    void resetNombreTroisiemePlace();
    void resetTotalPoints();
    void increaseTotalPoints(int points);
    int getNbrePremierePlace();
    int getNbreDeuxiemePlace();
    int getNbreTroisiemePlace();
    int getTotalPoints();
    //QList<int> getPoints();
    //void resetPoints();
    //void setPoints(QList<int> points);
    //void SetTotalPoints(int TotalPoints);
    
public slots:
    void ajouterParticipant(QString const& nom, QString const& prenom, int const& age, QChar const& sexe);
    void ajoutParticipant(Participant* parti);


protected:

    QString m_nom;
    int m_nombreParticipants;
    QList<Participant*> m_listeParticipants;
    Capitaine *m_capi;
    int m_ID;
    QList<int> m_Points;
    int m_totalPoints;
    int m_nbrePremierePlace;
    int m_nbreDeuxiemePlace;
    int m_nbreTroisiemePlace;
    

};

#endif // EQUIPE_H
