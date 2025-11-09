#ifndef W_ENTREREQUIPE_H
#define W_ENTREREQUIPE_H

#include <QtWidgets>
#include "Capitaine.h"
#include "Equipe.h"


class WindowEntrerEquipe : public QWidget
{
    Q_OBJECT
public:
    WindowEntrerEquipe(QWidget *parent);
    WindowEntrerEquipe(QString monstring);
public slots:
   void acceptAndClose();
signals:
   void equipeAcquired(Equipe * newTeam);
protected:
   QLineEdit *m_champNom;
   QLineEdit *m_champNomCapitaine;
   QLineEdit *m_champPrenomCapitaine;
   QRadioButton *m_champSexeCapitaineM;
   QRadioButton *m_champSexeCapitaineF;
   QSpinBox *m_champAgeCapitaine;
   QSpinBox *m_champNombreParticipants;
   QLineEdit *m_champTelephoneCapitaine;
   QLineEdit *m_champMailCapitaine;
   QLineEdit *m_champRueNumeroBoiteCapitaine;
   QLineEdit *m_champCPCapitaine;
   QLineEdit *m_champLocaliteCapitaine;
   QLabel *m_labelNom;
   Equipe *newTeam;

};

#endif // W_ENTREREQUIPE_H
