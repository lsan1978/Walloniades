#include "W_EntrerEpreuve.h"


WindowEntrerEpreuve::WindowEntrerEpreuve(QWidget *parent)
{
    newEpreuve=NULL;
    setWindowModality(Qt::ApplicationModal);
    QFormLayout *layout = new QFormLayout;
    QVBoxLayout *layout3 = new QVBoxLayout;
    QHBoxLayout *layout2 = new QHBoxLayout;
    QPushButton *annuler = new QPushButton("Annuler");
    QPushButton *accepter = new QPushButton("Ok");
    m_champNom = new QLineEdit();
    m_epreuveTemps = new QRadioButton("Temps");
    m_epreuvePoints = new QRadioButton("Points");
    m_epreuveTempsPosNeg=new QRadioButton("Temps positif et négatif");
    m_epreuveTempsOuNiveau=new QRadioButton("Temps ou niveau");
    m_labelDefaultPenalty = new QLabel("Pénalité par défaut:");
    m_defaultPenaltySpinBox = new QSpinBox;
    m_defaultPenaltySpinBox->setMinimum(1);
    m_defaultPenaltySpinBox->setMaximum(10);
    m_defaultPenaltySpinBox->setValue(5);
    m_defaultPenaltySpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    QLabel *secondesLabel = new QLabel("secondes");
    QHBoxLayout *penaliteLayout = new QHBoxLayout;
    penaliteLayout->addWidget(m_defaultPenaltySpinBox);
    penaliteLayout->addWidget(secondesLabel);

    QGroupBox *groupBox = new QGroupBox;
     QGridLayout *gridbox = new QGridLayout;
     gridbox->addWidget(m_epreuveTemps,0,0);
     gridbox->addWidget(m_epreuvePoints,0,1);
     gridbox->addWidget(m_epreuveTempsPosNeg,1,0);
     gridbox->addWidget(m_epreuveTempsOuNiveau,1,1);
     groupBox->setLayout(gridbox);

    layout->addRow("Nom de l'épreuve: ", m_champNom);

    layout->addRow("Type de l'épreuve: ", groupBox);
    layout->addRow(m_labelDefaultPenalty, penaliteLayout);
    layout2->addWidget(annuler);
    layout2->addWidget(accepter);

    layout3->addLayout(layout);
    layout3->addLayout(layout2);
    this->setLayout(layout3);
    this->setWindowTitle("Ajouter une épreuve...");
    QObject::connect(annuler, SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(accepter, SIGNAL(clicked()),this,SLOT(acceptAndClose()));
    QObject::connect(this, SIGNAL(epreuveAcquired(Epreuve*)),parent, SLOT(ajouterEpreuve(Epreuve*)));
    QObject::connect(this, SIGNAL(epreuveAcquired(Epreuve*)),parent, SLOT(ajouterEpreuveDansListe(Epreuve*)));


}

void WindowEntrerEpreuve::acceptAndClose()
{

    int a;
    if (m_epreuveTemps->isChecked())
    {
        a=0;
    }
    else if(m_epreuvePoints->isChecked())
    {
        a=1;
    }
    else if (m_epreuveTempsPosNeg->isChecked())
    {
        a=2;
    }
    else
    {
        a=3;
    }
    int defaultPenalite = m_defaultPenaltySpinBox->value();
    newEpreuve=new Epreuve(m_champNom->text(),a);
    newEpreuve->setNombreDeSecondeParPenalite(defaultPenalite);
    emit epreuveAcquired(newEpreuve);
    
    close();
}
