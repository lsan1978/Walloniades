#include "w_consultermodifierequipe.h"
#include "Walloniade.h"
#include "Participant.h"




W_ConsulterModifierEquipe::W_ConsulterModifierEquipe(QWidget *parent, QString Nom, Walloniade * Walloniade)
{
    setWindowModality(Qt::ApplicationModal);
    
    m_wallo=Walloniade;

    int i=0;
    while (Walloniade->getEquipe()[i]->getNomEquipe()!=Nom)
    {
        i++;
    }

    QString numero = QString::number(Walloniade->getEquipe()[i]->getID());
    setWindowTitle(Nom+" - "+numero);
    m_equipe=Walloniade->getEquipe()[i];

    QLineEdit *NomEquipe = new QLineEdit(Nom);
    QSpinBox *NombreParticipants=new QSpinBox();

    NombreParticipants->setValue(Walloniade->getEquipe()[i]->getNombreParticipants());

    QLineEdit *NomCapitaine = new QLineEdit(Walloniade->getEquipe()[i]->getCapi()->getNomParticipant());

    QLineEdit *PrenomCapitaine = new QLineEdit(Walloniade->getEquipe()[i]->getCapi()->getPrenomParticipant());

    QLineEdit *SexeCapitaine = new QLineEdit(Walloniade->getEquipe()[i]->getCapi()->getSexeParticipant());

    QSpinBox *AgeCapitaine = new QSpinBox();

    AgeCapitaine->setValue(Walloniade->getEquipe()[i]->getCapi()->getAgeParticipant());

    QLineEdit *TelephoneCapitaine = new QLineEdit(Walloniade->getEquipe()[i]->getCapi()->getTelephone());

    QLineEdit *MailCapitaine = new QLineEdit(Walloniade->getEquipe()[i]->getCapi()->getMail());

    QLineEdit *RueNumeroBoite = new QLineEdit(Walloniade->getEquipe()[i]->getCapi()->getRueNumeroBoite());

    QLineEdit *CP = new QLineEdit(Walloniade->getEquipe()[i]->getCapi()->getCP());

    QLineEdit *Localite = new QLineEdit(Walloniade->getEquipe()[i]->getCapi()->getLocalite());

    NomEquipe->setReadOnly(true);
    NombreParticipants->setReadOnly(true);
    NomCapitaine->setReadOnly(true);
    PrenomCapitaine->setReadOnly(true);
    SexeCapitaine->setReadOnly(true);
    AgeCapitaine->setReadOnly(true);
    TelephoneCapitaine->setReadOnly(true);
    MailCapitaine->setReadOnly(true);
    RueNumeroBoite->setReadOnly(true);
    CP->setReadOnly(true);
    Localite->setReadOnly(true);
    QGroupBox *groupBoxCapitaine = new QGroupBox("Capitaine");
    //groupBoxCapitaine->setStyleSheet("QGroupBox {   border: 1px solid gray;}");
    QVBoxLayout *verticalWindow = new QVBoxLayout; //Layout Principal de la fenêtre
    verticalWindow->setSpacing(40);
    QVBoxLayout *verticalCapi = new QVBoxLayout;
    QHBoxLayout *horizontalOneCapi = new QHBoxLayout;
    QHBoxLayout *horizontalTwoCapi = new QHBoxLayout;
    QHBoxLayout *horizontalThreeCapi = new QHBoxLayout;
    QHBoxLayout *horizontalAddressCapi = new QHBoxLayout;
    QVBoxLayout *verticalAddressCapi = new QVBoxLayout;
    horizontalOneCapi->addWidget(PrenomCapitaine);
    horizontalOneCapi->addWidget(NomCapitaine);
    horizontalOneCapi->addWidget(SexeCapitaine);
    horizontalOneCapi->addWidget(AgeCapitaine);
    horizontalTwoCapi->addWidget(TelephoneCapitaine);
    horizontalTwoCapi->addWidget(MailCapitaine);

    horizontalAddressCapi->addWidget(CP);
    horizontalAddressCapi->addWidget(Localite);
    verticalAddressCapi->addWidget(RueNumeroBoite);
    verticalAddressCapi->addLayout(horizontalAddressCapi);
    horizontalThreeCapi->addLayout(verticalAddressCapi);
    verticalCapi->addLayout(horizontalOneCapi);
    verticalCapi->addLayout(horizontalTwoCapi);
    verticalCapi->addLayout(horizontalThreeCapi);

    groupBoxCapitaine->setLayout(verticalCapi);
    verticalWindow->addWidget(groupBoxCapitaine);

    QGroupBox *groupBoxAjoutParticipant = new QGroupBox("Ajouter un participant...");
    QGridLayout * grille = new QGridLayout;
    NomParticipant = new QLineEdit();
    PrenomParticipant = new QLineEdit();
    AgeParticipant = new QSpinBox();
    SexeParticipantM = new QRadioButton("M");
    SexeParticipantF = new QRadioButton("F");
    QGroupBox *groupBox = new QGroupBox;
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(SexeParticipantM);
    hbox->addWidget(SexeParticipantF);
    groupBox->setLayout(hbox);
    QFormLayout *layout1 = new QFormLayout;
    layout1->addRow("Nom : ", NomParticipant);
    QFormLayout *layout2 = new QFormLayout;
    layout2->addRow("Prénom : ", PrenomParticipant);
    QFormLayout *layout3 = new QFormLayout;
    layout3->addRow("Age : ", AgeParticipant);
    QFormLayout *layout4 = new QFormLayout;
    layout4->addRow("Sexe : ", groupBox);
    QPushButton *Ajouter = new QPushButton("Ajouter");

    grille->addLayout(layout1,0,0);
    grille->addLayout(layout2,0,1);
    grille->addLayout(layout3,0,2);
    grille->addLayout(layout4,1,0);
    grille->addWidget(Ajouter,1,2);


    QObject::connect(Ajouter,SIGNAL(clicked()), this, SLOT(acceptAndRefresh()));
    groupBoxAjoutParticipant->setLayout(grille);


    QGroupBox *groupBoxListeParticipants = new QGroupBox("Participants");
    ListePrtpt = new QListWidget(this);
    ListePrtpt->setFont(QFont("consolas",9));
    displayListeParticipants(Walloniade->getEquipe()[i]);

    //QObject::connect(ListePrtpt, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(supprimerParticipant(QListWidgetItem*)));

    QVBoxLayout *Listeprtpt = new QVBoxLayout;
    Listeprtpt->addWidget(ListePrtpt);
    groupBoxListeParticipants->setLayout(Listeprtpt);

    verticalWindow->addWidget(groupBoxListeParticipants);
    verticalWindow->addWidget(groupBoxAjoutParticipant);
    ListePrtpt->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(ListePrtpt, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ProvideContextMenu(const QPoint &)));

    this->setLayout(verticalWindow);
}

void W_ConsulterModifierEquipe::acceptAndRefresh()
{

    QChar a;
    if (SexeParticipantM->isChecked())
    {
        a='M';
    }
    else
    {
        a='F';
    }
    Participant * NewParticipant = new Participant(NomParticipant->text(),PrenomParticipant->text(),AgeParticipant->value(),a);
    m_equipe->ajoutParticipant(NewParticipant);

    displayListeParticipants(m_equipe);

    NomParticipant->clear();
    PrenomParticipant->clear();
    AgeParticipant->clear();
    SexeParticipantM->setAutoExclusive(false);
    SexeParticipantM->setChecked(false);
    SexeParticipantM->setAutoExclusive(true);
    SexeParticipantF->setAutoExclusive(false);
    SexeParticipantF->setChecked(false);
    SexeParticipantF->setAutoExclusive(true);

}

void W_ConsulterModifierEquipe::displayListeParticipants(Equipe * equipe)
{

    ListePrtpt->clear();
    if (!equipe->getListeParticipants().isEmpty())
    {

    for (int j=0; j<equipe->getListeParticipants().size();j++)
    {

        QString ParticipantStr=QString::number(j+1) + ".";
        ParticipantStr.insert(6,equipe->getListeParticipants()[j]->getPrenomParticipant());
        ParticipantStr.insert(22,equipe->getListeParticipants()[j]->getNomParticipant());
        ParticipantStr.insert(42,QString::number(equipe->getListeParticipants()[j]->getAgeParticipant()));
        ParticipantStr.insert(56,equipe->getListeParticipants()[j]->getSexeParticipant());

        ListePrtpt->addItem(ParticipantStr);


    }
    }

}

void W_ConsulterModifierEquipe::supprimerParticipant(QListWidgetItem* item)
{
    m_equipe->supprimerParticipant(ListePrtpt->row(item));
    displayListeParticipants(m_equipe);
}


void W_ConsulterModifierEquipe::ProvideContextMenu(const QPoint &pos)
{
    QPoint point = ListePrtpt->mapToGlobal(pos);
    m_indice=ListePrtpt->indexAt(pos).row();
    QMenu submenu;
    submenu.addAction("Supprimer", this, SLOT(supprimerParticipantSelectionne()));
    submenu.exec(point);
}

void W_ConsulterModifierEquipe::supprimerParticipantSelectionne()
{
    this->supprimerParticipantBis(m_indice);

}

void W_ConsulterModifierEquipe::supprimerParticipantBis(int i)
{
    m_equipe->supprimerParticipant(i);
    displayListeParticipants(m_equipe);
}
