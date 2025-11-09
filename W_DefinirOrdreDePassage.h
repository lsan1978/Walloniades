#ifndef W_DEFINIRORDREDEPASSAGE_H
#define W_DEFINIRORDREDEPASSAGE_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QList>
#include "Walloniade.h"

class WindowDefinirOrdreDePassage : public QWidget
{
    Q_OBJECT

public:
    WindowDefinirOrdreDePassage(QWidget *parent = nullptr, Walloniade *Walloniade = nullptr, QString NomEpreuve = "");

private slots:
    void acceptAndClose();
    void setRandomOrder();
    void printOrder(int m);

private:
    Walloniade *m_wallo;
    QString m_NomEpreuve;
    QStringList m_ListeNom;
    QList<QSpinBox*> m_listeChamps;
    QList<int> m_ListeNumeros;
    int getEpreuveIndex() const;
    int getTeamIndexByNumero(int numero) const;
};

#endif // W_DEFINIRORDREDEPASSAGE_H
