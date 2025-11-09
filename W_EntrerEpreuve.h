#ifndef W_ENTREREPREUVE_H
#define W_ENTREREPREUVE_H

#include <QtWidgets>
#include "Epreuve.h"



class WindowEntrerEpreuve : public QWidget
{
    Q_OBJECT
public:
    WindowEntrerEpreuve(QWidget *parent);
    WindowEntrerEpreuve(QString monstring);
public slots:
   void acceptAndClose();
signals:
   void epreuveAcquired(Epreuve * newEpreuve);
protected:
   QLineEdit *m_champNom;
   QRadioButton *m_epreuveTemps;
   QRadioButton *m_epreuvePoints;
   QRadioButton *m_epreuveTempsPosNeg;
   QRadioButton *m_epreuveTempsOuNiveau;
   QLabel *m_labelNom;
   Epreuve *newEpreuve;
   QLabel *m_labelDefaultPenalty;
   QSpinBox *m_defaultPenaltySpinBox;

};
#endif // W_ENTREREPREUVE_H
