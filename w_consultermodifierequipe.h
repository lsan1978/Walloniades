#ifndef W_CONSULTERMODIFIEREQUIPE_H
#define W_CONSULTERMODIFIEREQUIPE_H
#include <QtWidgets>
#include "Walloniade.h"




class W_ConsulterModifierEquipe : public QWidget
{
    Q_OBJECT
public:
    W_ConsulterModifierEquipe(QWidget * parent, QString nom, Walloniade * Walloniade );
    void supprimerParticipantBis(int i);
signals:
    void ParticipantAcquired(Participant *);

public slots:
    void acceptAndRefresh();
    void displayListeParticipants(Equipe * equipe);
    void supprimerParticipant(QListWidgetItem* item);
    void ProvideContextMenu(const QPoint &pos);
    void supprimerParticipantSelectionne();
    //void addMember(Walloniade * Walloniade, int i);

protected:
    QLineEdit * NomParticipant;
    QLineEdit * PrenomParticipant;
    QSpinBox * AgeParticipant;
    QRadioButton *SexeParticipantM;
    QRadioButton *SexeParticipantF;
    Walloniade * m_wallo;
    Equipe * m_equipe;
    QGridLayout *grilleListe;
    QListWidget * ListePrtpt;
    int m_indice;

};

#endif // W_CONSULTERMODIFIEREQUIPE_H
