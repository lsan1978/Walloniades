#ifndef WALLONIADE_H
#define WALLONIADE_H
#include "Epreuve.h"
#include "Equipe.h"
#include <QObject>
#include <vector>


class Walloniade : public QObject
{

   Q_GADGET
public:
    Walloniade();
    ~Walloniade();
    Q_INVOKABLE void ajouterEquipe(Equipe * newTeam);
    Q_INVOKABLE void ajouterEpreuve(Epreuve * newEpreuve);
    Q_INVOKABLE QList<Equipe *>& getEquipe();
    Q_INVOKABLE void supprimerEquipe(int i);
    Q_INVOKABLE void supprimerEquipe(QString NomEquipe);
    Q_INVOKABLE void supprimerEpreuve(QString NomEquipe);
    Q_INVOKABLE QList<Epreuve *>& getEpreuve();

protected:
    QList<Equipe*> m_equipes; 
    QList<Epreuve*> m_epreuves;
};


#endif // WALLONIADE_H

