#include "W_DefinirTempsPenalite.h"
#include "Walloniade.h"
#include "Epreuve.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

WindowDefinirTempsPenalite::WindowDefinirTempsPenalite(QWidget *parent, Walloniade *Walloniade, QString NomEpreuve)
    
{
    //setWindowTitle("Définir ordre de passage...");
    setMinimumWidth(300);
    m_wallo = Walloniade;
    m_NomEpreuve = NomEpreuve;
    setWindowTitle(m_NomEpreuve + " - Définir Temps de Pénalité");

    // Find the Epreuve
    int epreuveIndex = -1;
    for (int i = 0; i < m_wallo->getEpreuve().size(); ++i) {
        if (m_wallo->getEpreuve()[i]->getNomEpreuve() == m_NomEpreuve) {
            epreuveIndex = i;
            m_epreuve=m_wallo->getEpreuve()[i];
            break;
        }
    }

    if (epreuveIndex == -1) {
        QMessageBox::critical(this, "Erreur", "Epreuve not found!");
        close();
        return;
    }


    m_tempsPenaliteSpinBox = new QSpinBox;
    m_tempsPenaliteSpinBox->setMinimum(1);
    m_tempsPenaliteSpinBox->setMaximum(10);
    m_tempsPenaliteSpinBox->setValue(5);
    m_tempsPenaliteSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

    m_secondesLabel = new QLabel("secondes");

    m_okButton = new QPushButton("Ok");
    m_cancelButton = new QPushButton("Annuler");

    QHBoxLayout *spinBoxLayout = new QHBoxLayout;
    spinBoxLayout->addWidget(m_tempsPenaliteSpinBox);
    spinBoxLayout->addWidget(m_secondesLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_cancelButton);
    buttonLayout->addWidget(m_okButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(spinBoxLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(m_okButton, &QPushButton::clicked, this, &WindowDefinirTempsPenalite::acceptAndClose);
    connect(m_cancelButton, &QPushButton::clicked, this, &WindowDefinirTempsPenalite::cancelAndClose);
}

/*WindowDefinirTempsPenalite::~WindowDefinirTempsPenalite(){

}*/

int WindowDefinirTempsPenalite::getEpreuveIndex() const
{
    for (int i = 0; i < m_wallo->getEpreuve().size(); ++i) {
        if (m_wallo->getEpreuve()[i]->getNomEpreuve() == m_NomEpreuve)
        {
            return i;
        }
    }
    return -1;
}



void WindowDefinirTempsPenalite::acceptAndClose()
{
    m_epreuve->setNombreDeSecondeParPenalite(m_tempsPenaliteSpinBox->value());
    close();
}

void WindowDefinirTempsPenalite::cancelAndClose()
{
    close();
}
