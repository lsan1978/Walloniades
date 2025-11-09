#include "W_EntrerEquipe.h"
#include "Capitaine.h"
#include "Equipe.h"
#include "mainwindow.h"


WindowEntrerEquipe::WindowEntrerEquipe(QWidget *parent)
{
    setMinimumWidth(400);
    newTeam=NULL;
    setWindowModality(Qt::ApplicationModal);
    QFormLayout *layout = new QFormLayout;
    QVBoxLayout *layout3 = new QVBoxLayout;
    QHBoxLayout *layout2 = new QHBoxLayout;
    QPushButton *annuler = new QPushButton("Annuler");
    QPushButton *accepter = new QPushButton("Ok");
    m_champNom = new QLineEdit();
    m_champNombreParticipants=new QSpinBox();
    m_champNombreParticipants->setValue(10);
    m_champNomCapitaine = new QLineEdit();
    m_champPrenomCapitaine = new QLineEdit();
    m_champAgeCapitaine = new QSpinBox();
    m_champAgeCapitaine->setButtonSymbols(QAbstractSpinBox::NoButtons);
    m_champAgeCapitaine->clear();
    m_champSexeCapitaineM = new QRadioButton("M");
    m_champSexeCapitaineF = new QRadioButton("F");
    m_champTelephoneCapitaine = new QLineEdit();
    m_champMailCapitaine=new QLineEdit();
    m_champRueNumeroBoiteCapitaine=new QLineEdit();
    m_champCPCapitaine=new QLineEdit();
    m_champLocaliteCapitaine= new QLineEdit;

    QGroupBox *groupBox = new QGroupBox;
     QHBoxLayout *hbox = new QHBoxLayout;
     hbox->addWidget(m_champSexeCapitaineM);
     hbox->addWidget(m_champSexeCapitaineF);
     groupBox->setLayout(hbox);

    layout->addRow("Nom de l'équipe: ", m_champNom);
    layout->addRow("Nombre de participants: ", m_champNombreParticipants);
    layout->addRow("Nom du Capitaine: ", m_champNomCapitaine);
    layout->addRow("Prénom du Capitaine: ", m_champPrenomCapitaine);
    layout->addRow("Age du Capitaine: ",m_champAgeCapitaine);
    layout->addRow("Sexe du Capitaine: ", groupBox);
    layout->addRow("Numero de téléphone du Capitaine: ", m_champTelephoneCapitaine);
    layout->addRow("Adresse email du Capitaine: ", m_champMailCapitaine);
    layout->addRow("Rue et numéro (Boîte): ", m_champRueNumeroBoiteCapitaine);
    layout->addRow("Code Postal: ", m_champCPCapitaine);
    layout->addRow("Localité: ", m_champLocaliteCapitaine);
    layout2->addWidget(annuler);
    layout2->addWidget(accepter);
    layout3->addLayout(layout);
    layout3->addLayout(layout2);
    this->setLayout(layout3);
    this->setWindowTitle("Ajouter une équipe...");
    QObject::connect(annuler, SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(accepter, SIGNAL(clicked()),this,SLOT(acceptAndClose()));
    QObject::connect(this, SIGNAL(equipeAcquired(Equipe*)),parent, SLOT(ajouterEquipe(Equipe*)));
    QObject::connect(this, SIGNAL(equipeAcquired(Equipe*)),parent, SLOT(ajouterEquipeDansListe(Equipe*)));


}

void WindowEntrerEquipe::acceptAndClose()
{

    QChar a;
    if (m_champSexeCapitaineM->isChecked())
    {
        a='M';
    }
    else
    {
        a='F';
    }
    Capitaine *capi=new Capitaine(m_champNomCapitaine->text(),m_champPrenomCapitaine->text(), m_champAgeCapitaine->value(),a,m_champTelephoneCapitaine->text(),m_champMailCapitaine->text(),m_champRueNumeroBoiteCapitaine->text(),m_champCPCapitaine->text(),m_champLocaliteCapitaine->text());
    newTeam=new Equipe(m_champNom->text(), capi, m_champNombreParticipants->value());
    emit equipeAcquired(newTeam);

    close();
}


