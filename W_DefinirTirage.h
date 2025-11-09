#ifndef W_DEFINIRTIRAGE_H
#define W_DEFINIRTIRAGE_H

#include <QtWidgets>
#include "Walloniade.h"

class WindowDefinirTirage : public QWidget
{
    Q_OBJECT
public:
    WindowDefinirTirage(QWidget *parent, Walloniade * Walloniade);
public slots:
   void acceptAndClose();
signals:
   void TirageAcquired(QList<QString>,QList<int>);
   void TirageAcquiredBis(int);
protected:
   Walloniade * m_wallo;
   QList<QSpinBox *>m_listeChamps;
   QList<QString> m_ListeNom;
   QList<int> m_ListeNumeros;


};

#endif // W_DEFINIRTIRAGE_H
