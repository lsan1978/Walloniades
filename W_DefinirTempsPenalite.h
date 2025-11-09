#ifndef W_DEFINIRTEMPSPENALITE_H
#define W_DEFINIRTEMPSPENALITE_H

#include <QtWidgets>
#include "Walloniade.h"
#include "Epreuve.h"

class WindowDefinirTempsPenalite : public QWidget
{
    Q_OBJECT

public:
    WindowDefinirTempsPenalite(QWidget *parent = nullptr, Walloniade *Walloniade = nullptr, QString NomEpreuve = "");
    //~WindowDefinirTempsPenalite();

private slots:
    void acceptAndClose();
    void cancelAndClose();

private:
    Walloniade *m_wallo;
    QString m_NomEpreuve;
    QSpinBox *m_tempsPenaliteSpinBox;
    QLabel *m_secondesLabel;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
    Epreuve * m_epreuve;
    int getEpreuveIndex() const;
    int getTeamIndexByNumero(int numero) const;
};

#endif // W_DEFINIRTEMPSPENALITE_H

