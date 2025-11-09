// mainwindowdesigner.cpp
#include "mainwindowdesigner.h"
#include "ui_mainwindowdesigner.h"
#include "w_consultermodifierequipe.h"
#include "W_DefinirOrdreDePassage.h"
#include "W_DefinirTempsPenalite.h"
#include "W_EntrerResultats.h"
#include "Capitaine.h"
#include "Equipe.h"
#include <QMessageBox>
#include <QFileDialog> // Added for file dialog
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QRegularExpression>

Walloniade * MainWindowDesigner::m_walloniade=NULL;

MainWindowDesigner::MainWindowDesigner(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowDesigner)
{
    ui->setupUi(this);
    m_walloniade = new Walloniade();
    initListEquipe();
    m_WEE=NULL;
    WCME=NULL;
    m_WER=NULL;
    m_WDOP=NULL;
    m_WDTP=NULL;
    QObject::connect(ui->listEquipes, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(ouvrirWindowConsulterModifierEquipe(QListWidgetItem*)));
    QObject::connect(ui->listEpreuves, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(ouvrirWindowEntrerResultat(QListWidgetItem*)));
    ui->listEquipes->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listEpreuves->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(ui->listEquipes, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ProvideContextMenu(const QPoint &)));
    QObject::connect(ui->listEpreuves, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ProvideContextMenuEpreuve(const QPoint &)));
    QObject::connect(ui->boutonQuitter, &QPushButton::clicked, this, &MainWindowDesigner::on_boutonQuitter_clicked);
    QSize currentSize = this->size();
    int newWidth = static_cast<int>(currentSize.width() * 1.3);
    int newHeight = static_cast<int>(currentSize.height() * 1.3);
    this->resize(newWidth, newHeight);
}

MainWindowDesigner::~MainWindowDesigner()
{
    delete ui;
}

void MainWindowDesigner::ouvrirWindowEntrerEquipe()
{
    m_WEE = new WindowEntrerEquipe(this);
    m_WEE->show();
}

void MainWindowDesigner::ouvrirWindowEntrerEpreuve()
{
    m_WEEpreuve = new WindowEntrerEpreuve(this);
    m_WEEpreuve->show();
}

void MainWindowDesigner::ouvrirWindowDefinirOrdreDePassage(QString NomEpreuve)
{
    m_WDOP= new WindowDefinirOrdreDePassage(this,m_walloniade,NomEpreuve);
    m_WDOP->show();
}

void MainWindowDesigner::DefinirOrdreDePassage()
{
    ouvrirWindowDefinirOrdreDePassage(m_nomEpreuveSelectionee);
}

void MainWindowDesigner::DefinirTempsDePenalite()
{
    ouvrirWindowDefinirTempsPenalite(m_nomEpreuveSelectionee);
}

void MainWindowDesigner::ouvrirWindowDefinirTempsPenalite(QString NomEpreuve)
{    
    m_WDTP=new WindowDefinirTempsPenalite(this,m_walloniade,NomEpreuve);
    m_WDTP->show();
}

void MainWindowDesigner::ouvrirWindowConsulterModifierEquipe(QListWidgetItem* item)
{
    WCME = new W_ConsulterModifierEquipe(this, item->text(),m_walloniade);
    WCME->show();
}

void MainWindowDesigner::ouvrirWindowEntrerResultat(QListWidgetItem* item)
{
    if (m_WER==NULL)
    {
        int reponse = QMessageBox::question(this, "Attention !",
            "Avant de passer à l'encodage des résultats, il faut que :\n\n\n"
            "- La liste des équipes soit définitive\n\n"
            "- La liste des épreuves soit définitive\n\n"
            "- Le tirage au sort ait été défini \n\n"
            "- L'ordre de passage ait été défini pour chaque épreuve\n\n\n "
            "Est-ce bien le cas ?",
            QMessageBox::Yes | QMessageBox::No);
     if (reponse == QMessageBox::Yes)
         {
         m_WER = new WindowEntrerResultat(this,m_walloniade);
         QObject::connect(m_WER, &WindowEntrerResultat::updateResults, this, &MainWindowDesigner::initListClassementGeneral);
         int i=0;
         while(m_walloniade->getEpreuve()[i]->getNomEpreuve()!=item->text())
         {
             i++;
         }
         m_WER->getOnglets()->setCurrentIndex(i);
         m_WER->show();
         }

    }
    else
    {
        int i=0;
        while(m_walloniade->getEpreuve()[i]->getNomEpreuve()!=item->text())
        {
            i++;
        }
        m_WER->getOnglets()->setCurrentIndex(i);
    m_WER->show();
    }
}

void MainWindowDesigner::ajouterEquipe(Equipe *NewTeam)
{
    m_walloniade->ajouterEquipe(NewTeam);
}

void MainWindowDesigner::ajouterEpreuve(Epreuve *NewEpreuve)
{
    m_walloniade->ajouterEpreuve(NewEpreuve);
}
void MainWindowDesigner::ajouterEquipeDansListe(Equipe *NewTeam)
{
    ui->listEquipes->addItem(NewTeam->getNomEquipe());
    ui->listEquipes->sortItems();
}

void MainWindowDesigner::ajouterEpreuveDansListe(Epreuve *NewEpreuve)
{
    ui->listEpreuves->addItem(NewEpreuve->getNomEpreuve());

}

void MainWindowDesigner::on_boutonAjouterEquipe_clicked()
{
    m_WEE = new WindowEntrerEquipe(this);
    m_WEE->show();
}

void MainWindowDesigner::on_actionEquipe_triggered()
{
    m_WEE = new WindowEntrerEquipe(this);
    m_WEE->show();
}

void MainWindowDesigner::on_actionQuitter_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Voulez-vous quitter le programme ?");
    QPushButton *exitWithoutSavingButton = msgBox.addButton("Quitter sans Enregistrer", QMessageBox::RejectRole);
    QPushButton *saveAndQuitButton = msgBox.addButton("Enregistrer et quitter", QMessageBox::AcceptRole);
    QPushButton *cancelButton = msgBox.addButton("Annuler", QMessageBox::NoRole);
    //msgBox.setDefaultButton(cancelButton);

    // Use exec() and store the result in a variable
    int result = msgBox.exec();

    // Check the result directly
    if (msgBox.clickedButton() == exitWithoutSavingButton)
    {
       QApplication::quit();
    }
    else if (msgBox.clickedButton() == saveAndQuitButton)
    {
        on_actionEnregistrer_triggered();
        QApplication::quit();
    }
    else if (msgBox.clickedButton() == cancelButton)
    {
        msgBox.close(); // Close the message box explicitly
    }
}

void MainWindowDesigner::on_actionDefinir_Tirage_au_Sort_triggered()
{
    
    
    if (m_walloniade->getEquipe().isEmpty() || m_walloniade->getEquipe()[0]==NULL)
    {
        QMessageBox::information(this, "Information", "Il n'y a pas d'équipe à tirer au sort !");
    }
    else
    {
        
        m_WDT = new WindowDefinirTirage(this, m_walloniade);
        m_WDT->show();
    }
}
void MainWindowDesigner::on_actionEpreuve_triggered()
{
    m_WEEpreuve = new WindowEntrerEpreuve(this);
    m_WEEpreuve->show();
}

void MainWindowDesigner::on_boutonAjouterEpreuve_clicked()
{
    m_WEEpreuve = new WindowEntrerEpreuve(this);
    m_WEEpreuve->show();
}

void MainWindowDesigner::initListClassementGeneral()
{
    ui->listClassement->clear();
    ui->listClassement->setFont(QFont("consolas",11));
    QList<CopyTeam> ListeEquipe;

     for (int i = 0; i < m_walloniade->getEquipe().size(); i++)
     {
         CopyTeam temporaire;
         temporaire.EquipeID=m_walloniade->getEquipe()[i]->getID();
         temporaire.NomEquipe=m_walloniade->getEquipe()[i]->getNomEquipe();
         temporaire.TotalPoints=m_walloniade->getEquipe()[i]->getTotalPoints();
         temporaire.nbrePremierePlace=m_walloniade->getEquipe()[i]->getNbrePremierePlace();
         temporaire.nbreDeuxiemePlace=m_walloniade->getEquipe()[i]->getNbreDeuxiemePlace();
         temporaire.nbreTroisiemePlace=m_walloniade->getEquipe()[i]->getNbreTroisiemePlace();
         ListeEquipe.append(temporaire);
     }

     std::sort(ListeEquipe.begin(), ListeEquipe.end(), [](const CopyTeam& a, const CopyTeam& b) {
         // Premier critère : TotalPoints
         if (a.TotalPoints != b.TotalPoints) {
             return a.TotalPoints < b.TotalPoints; // Tri croissant par TotalPoints
         }
         
         // Deuxième critère : NombrePremierePlace
         if (a.nbrePremierePlace != b.nbrePremierePlace) {
             return a.nbrePremierePlace > b.nbrePremierePlace; // Tri décroissant
         }

         // Troisième critère : NombreDeuxiemePlace
         if (a.nbreDeuxiemePlace != b.nbreDeuxiemePlace) {
             return a.nbreDeuxiemePlace > b.nbreDeuxiemePlace; // Tri décroissant
         }

         // Quatrième critère : NombreTroisiemePlace
         if (a.nbreTroisiemePlace != b.nbreTroisiemePlace) {
             return a.nbreTroisiemePlace > b.nbreTroisiemePlace; // Tri décroissant
         }

         // Cinquième critère : Ordre alphabétique
         return a.NomEquipe < b.NomEquipe; // Tri croissant
     });
     int ranking = 1;
     for (int i = 0; i < ListeEquipe.size(); i++)
        {
            if (i==0)
            {
                QString ClassementStr=QString::number(ranking) + ".";
                ClassementStr.insert(5,ListeEquipe[i].NomEquipe);
                ClassementStr.insert(30,QString::number(ListeEquipe[i].TotalPoints));
                ui->listClassement->addItem(ClassementStr);
            }
            else if (ListeEquipe[i].TotalPoints==ListeEquipe[i-1].TotalPoints && ListeEquipe[i].nbrePremierePlace==ListeEquipe[i-1].nbrePremierePlace && ListeEquipe[i].nbreDeuxiemePlace==ListeEquipe[i-1].nbreDeuxiemePlace && ListeEquipe[i].nbreTroisiemePlace==ListeEquipe[i-1].nbreTroisiemePlace)
            {
                QString ClassementStr=QString::number(ranking) + ".";
                ClassementStr.insert(5,ListeEquipe[i].NomEquipe);
                ClassementStr.insert(30,QString::number(ListeEquipe[i].TotalPoints));
                ui->listClassement->addItem(ClassementStr);

            }
            else
            {
                ranking=i+1;
                QString ClassementStr=QString::number(ranking) + ".";
                ClassementStr.insert(5,ListeEquipe[i].NomEquipe);
                ClassementStr.insert(30,QString::number(ListeEquipe[i].TotalPoints));
                ui->listClassement->addItem(ClassementStr);
            }
        }    
         


        
    
}

void MainWindowDesigner::initListEquipe()
{
    ui->listEquipes->clear();
    if (!m_walloniade->getEquipe().isEmpty() && m_walloniade->getEquipe()[0]!=NULL)
    {
        for (int i=0; i<m_walloniade->getEquipe().size();i++)
        {
            ui->listEquipes->addItem(m_walloniade->getEquipe()[i]->getNomEquipe());
        }
        ui->listEquipes->sortItems();
    }
}

void MainWindowDesigner::initListEpreuve()
{
    ui->listEpreuves->clear();
    if (!m_walloniade->getEpreuve().isEmpty() && m_walloniade->getEpreuve()[0]!=NULL)
    {
        for (int i=0; i<m_walloniade->getEpreuve().size();i++)
        {
            ui->listEpreuves->addItem(m_walloniade->getEpreuve()[i]->getNomEpreuve());
        }

    }
}

void MainWindowDesigner::on_actionEnregistrer_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Walloniade Data"), "", tr("Walloniade Data Files (*.dat);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", "Could not open file for saving.");
        return;
    }

    QDataStream out(&file);
    int nbreEquipes, nbreParticipantEncodes,EquipeID, nbreEpreuves, typeEpreuve, NbreDeSecondeParPenalite;
    

    if(m_walloniade->getEquipe()[0]!=NULL)
    {
    nbreEquipes=m_walloniade->getEquipe().size();
    }
    else
    {
        nbreEquipes=0;
    }

    if(m_walloniade->getEpreuve()[0]!=NULL)
    {
    nbreEpreuves=m_walloniade->getEpreuve().size();
    }
    else
    {
        nbreEpreuves=0;
    }

    out << nbreEquipes;

    for (int i=0; i<nbreEquipes;i++)
    {
        EquipeID=m_walloniade->getEquipe()[i]->getID();
    //qDebug() << EquipeID;
        out << m_walloniade->getEquipe()[i]->getNomEquipe() << EquipeID
            << m_walloniade->getEquipe()[i]->getNombreParticipants()
            << m_walloniade->getEquipe()[i]->getCapi()->getNomParticipant()
            << m_walloniade->getEquipe()[i]->getCapi()->getPrenomParticipant()
            << m_walloniade->getEquipe()[i]->getCapi()->getAgeParticipant()
            << m_walloniade->getEquipe()[i]->getCapi()->getSexeParticipant()
            << m_walloniade->getEquipe()[i]->getCapi()->getTelephone()
            << m_walloniade->getEquipe()[i]->getCapi()->getMail()
            << m_walloniade->getEquipe()[i]->getCapi()->getRueNumeroBoite()
            << m_walloniade->getEquipe()[i]->getCapi()->getCP()
            << m_walloniade->getEquipe()[i]->getCapi()->getLocalite();
        nbreParticipantEncodes=m_walloniade->getEquipe()[i]->getListeParticipants().size();
        out << nbreParticipantEncodes;
        for (int j=1;j<m_walloniade->getEquipe()[i]->getListeParticipants().size();j++)
        {

            out << m_walloniade->getEquipe()[i]->getListeParticipants()[j]->getNomParticipant()
                << m_walloniade->getEquipe()[i]->getListeParticipants()[j]->getPrenomParticipant()
                << m_walloniade->getEquipe()[i]->getListeParticipants()[j]->getAgeParticipant()
                << m_walloniade->getEquipe()[i]->getListeParticipants()[j]->getSexeParticipant();
        }


    }

    out << nbreEpreuves;

    for (int i=0; i<nbreEpreuves;i++)
    {
        typeEpreuve= m_walloniade->getEpreuve()[i]->getType();
        NbreDeSecondeParPenalite=m_walloniade->getEpreuve()[i]->getNombreDeSecondeParPenalite();
        out << m_walloniade->getEpreuve()[i]->getNomEpreuve() << typeEpreuve << NbreDeSecondeParPenalite;
        if (m_walloniade->getEpreuve()[i]->getOrdreDePassage().isEmpty())
        {
            out << 0;
        }
        
        else
        {
        QList<int> ordre = m_walloniade->getEpreuve()[i]->getOrdreDePassage();
        int p;
        p=ordre.size();
        out << p;

        for(int j = 0; j < ordre.size(); ++j) out << ordre[j];
        }

    }

    bool resultatspresents;
    if (m_WER!=NULL)
    {
        resultatspresents=true;
    }
    else
    {
        resultatspresents=false;
    }


    out << resultatspresents;
    if (resultatspresents) {
        
        for (int i = 0; i < m_walloniade->getEpreuve().size(); ++i) {
            out << m_walloniade->getEpreuve()[i]->getType(); // Save the type of Epreuve
            if (m_walloniade->getEpreuve()[i]->getType() == 0) { // Temps
                int compteurderesultatTemps = 0;
                int compteurderesultatPenalite = 0;
                for (int j = 0; j < m_walloniade->getEquipe().size(); ++j) {
                    if (!m_WER->MapTempsBrut[i][j]->text().isEmpty())
                    {
                        compteurderesultatTemps++;
                    }
                    if (!m_WER->MapPenalites[i][j]->text().isEmpty())
                    {
                        compteurderesultatPenalite++;
                    }
                }
                out << compteurderesultatTemps;
                
                
                for (int j = 0; j < m_walloniade->getEquipe().size(); ++j) {
                    if (!m_WER->MapTempsBrut[i][j]->text().isEmpty())
                    {
                    out << j << m_WER->MapTempsBrut[i][j]->value();

                    
                    }
                }

                out << compteurderesultatPenalite;

                for (int j = 0; j < m_walloniade->getEquipe().size(); ++j) {
                    if (!m_WER->MapPenalites[i][j]->text().isEmpty())
                    {
                    out << j << m_WER->MapPenalites[i][j]->value();

                    
                    }
                }
                
            } 
            
            else if (m_walloniade->getEpreuve()[i]->getType() == 1)  // Points
            {    
                int compteurderesultatPoints = 0;
                for (int j = 0; j < m_walloniade->getEquipe().size(); ++j) 
                {
                    if (!m_WER->MapPoints[i][j]->text().isEmpty())
                    {
                        compteurderesultatPoints++;
                    }
                    
                }
                out << compteurderesultatPoints;

                for (int j = 0; j < m_walloniade->getEquipe().size(); ++j) 
                {
                    if (!m_WER->MapPoints[i][j]->text().isEmpty())
                    {
                        out << j << m_WER->MapPoints[i][j]->value();
                    }
                }
                
            
            } 
            
            else if (m_walloniade->getEpreuve()[i]->getType() == 2) // Temps Pos/Neg
            {
                int compteurderesultatTemps = 0;
                for (int j = 0; j < m_walloniade->getEquipe().size(); ++j) 
                {
                    if (!m_WER->MapTempsBrut[i][j]->text().isEmpty())
                    {
                        compteurderesultatTemps++;
                    }
                    
                }
                out << compteurderesultatTemps;

                for (int j = 0; j < m_walloniade->getEquipe().size(); ++j) 
                {
                    if (!m_WER->MapTempsBrut[i][j]->text().isEmpty())
                    {
                        out << j << m_WER->MapTempsBrut[i][j]->value();
                    }
                }
                 
            } 
            
            else if (m_walloniade->getEpreuve()[i]->getType() == 3) // Temps/Niveau
            { 
                int compteurderesultatTemps = 0;
                int compteurderesultatNiveau = 0;
                for (int j = 0; j < m_walloniade->getEquipe().size(); ++j) {
                    if (!m_WER->MapTempsBrut[i][j]->text().isEmpty())
                    {
                        compteurderesultatTemps++;
                    }
                    if (!m_WER->MapNiveau[i][j]->text().isEmpty())
                    {
                        compteurderesultatNiveau++;
                    }
                }
                out << compteurderesultatTemps;
                
                
                for (int j = 0; j < m_walloniade->getEquipe().size(); ++j) {
                    if (!m_WER->MapTempsBrut[i][j]->text().isEmpty())
                    {
                    out << j << m_WER->MapTempsBrut[i][j]->value();

                    
                    }
                }

                out << compteurderesultatNiveau;

                for (int j = 0; j < m_walloniade->getEquipe().size(); ++j) {
                    if (!m_WER->MapNiveau[i][j]->text().isEmpty())
                    {
                    out << j << m_WER->MapNiveau[i][j]->value();

                    
                    }
                }  
            }
        }
    }
    
    file.close();
}


void MainWindowDesigner::on_actionOuvrir_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Walloniade Data"), "", tr("Walloniade Data Files (*.dat);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    QFile file(fileName);
     if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Could not open file for reading.");
        return;
    }
    QDataStream in(&file);
    QString NomEquipe,NomCapi,PrenomCapi,TelephoneCapi,MailCapi,RueNumeroBoiteCapi,CPCapi,LocaliteCapi, NomParticipant, PrenomParticipant, NomEpreuve, OrdreEpreuve;
    QChar SexeCapi, SexeParticipant;
    int NombreParticipants, AgeCapi, AgeParticipant, nbreEquipes, nbreParticipantsEncodes,EquipeID,nbreEpreuves, typeEpreuve, NbreDeSecondeParPenalite, ordreSize;
    in >> nbreEquipes;
    for (int i=0; i<nbreEquipes;i++)
    {

        in >> NomEquipe >> EquipeID >> NombreParticipants >> NomCapi >> PrenomCapi >> AgeCapi >> SexeCapi
                >> TelephoneCapi >> MailCapi >> RueNumeroBoiteCapi >> CPCapi >> LocaliteCapi;

        Capitaine *capi=new Capitaine(NomCapi, PrenomCapi, AgeCapi, SexeCapi, TelephoneCapi, MailCapi, RueNumeroBoiteCapi, CPCapi, LocaliteCapi);
        Equipe *equipe = new Equipe(NomEquipe,capi,NombreParticipants);
        equipe->setID(EquipeID);
        m_walloniade->ajouterEquipe(equipe);
        in >> nbreParticipantsEncodes;
        for (int j=1; j<nbreParticipantsEncodes;j++)
        {

            in >> NomParticipant >> PrenomParticipant >> AgeParticipant >> SexeParticipant;
            Participant * NewParticipant = new Participant(NomParticipant,PrenomParticipant,AgeParticipant,SexeParticipant);
            m_walloniade->getEquipe()[i]->ajoutParticipant(NewParticipant);

        }
    }
    initListEquipe();
    in >> nbreEpreuves;
    for (int i=0; i<nbreEpreuves;i++)
    {
        
        in >> NomEpreuve >> typeEpreuve >> NbreDeSecondeParPenalite;
        Epreuve *epreuve = new Epreuve(NomEpreuve,typeEpreuve);
        m_walloniade->ajouterEpreuve(epreuve);
        m_walloniade->getEpreuve()[i]->setNombreDeSecondeParPenalite(NbreDeSecondeParPenalite);
        int ordreSize;
        in >> ordreSize;
        if (ordreSize!=0)
        {
        // QMessageBox::information(this, "Information", QString("Un ordre de passage contenant %1 valeurs détecté à la lecture").arg(ordreSize));
        QList<int> ordre;
        for(int j = 0; j < ordreSize; ++j) {int temp; in >> temp; ordre.append(temp);}
        m_walloniade->getEpreuve()[i]->setOrdreDePassage(ordre);
        }
    }
    initListEpreuve();

    bool resultatsacharger;
    in >> resultatsacharger;

    if (resultatsacharger)
    {
        
        if (m_WER == NULL) 
        {
            m_WER = new WindowEntrerResultat(this,m_walloniade);
            QObject::connect(m_WER, &WindowEntrerResultat::updateResults, this, &MainWindowDesigner::initListClassementGeneral);

        }

        for (int i = 0; i < nbreEpreuves; ++i) 
        {
            int savedTypeEpreuve;
            in >> savedTypeEpreuve;
            if (savedTypeEpreuve == 0)  // Temps
            {        
                int CompteurdeResultatTemps;
                in >> CompteurdeResultatTemps; 
                for (int j = 0; j < CompteurdeResultatTemps; ++j) 
                {
                    double temps;
                    int indice;
                    in >> indice;
                    in >> temps;
                    m_WER->MapTempsBrut[i][indice]->setValue(temps);
                    
                }

                int CompteurdeResultatPenalite;
                in >> CompteurdeResultatPenalite; 
                for (int j = 0; j < CompteurdeResultatPenalite; ++j) 
                {
                    int penalite;
                    int indice;
                    in >> indice;
                    in >> penalite;
                    m_WER->MapPenalites[i][indice]->setValue(penalite);
                    
                }
            }
            
            if (savedTypeEpreuve == 1)  // Points
            {        
                int CompteurdeResultatPoints;
                in >> CompteurdeResultatPoints; 
                for (int j = 0; j < CompteurdeResultatPoints; ++j) 
                {
                    int points;
                    int indice;
                    in >> indice;
                    in >> points;
                    m_WER->MapPoints[i][indice]->setValue(points);
                    
                }
            }

            if (savedTypeEpreuve == 2)  // Temps Pos/Neg
            {        
                int CompteurdeResultatTemps;
                in >> CompteurdeResultatTemps; 
                for (int j = 0; j < CompteurdeResultatTemps; ++j) 
                {
                    double temps;
                    int indice;
                    in >> indice;
                    in >> temps;
                    m_WER->MapTempsBrut[i][indice]->setValue(temps);
                    
                }
            }

            if (savedTypeEpreuve == 3)  // Temps / Niveau
            {        
                int CompteurdeResultatTemps;
                in >> CompteurdeResultatTemps; 
                for (int j = 0; j < CompteurdeResultatTemps; ++j) 
                {
                    double temps;
                    int indice;
                    in >> indice;
                    in >> temps;
                    m_WER->MapTempsBrut[i][indice]->setValue(temps);
                    
                }

                int CompteurdeResultatNiveau;
                in >> CompteurdeResultatNiveau; 
                for (int j = 0; j < CompteurdeResultatNiveau; ++j) 
                {
                    int niveau;
                    int indice;
                    in >> indice;
                    in >> niveau;
                    m_WER->MapNiveau[i][indice]->setValue(niveau);
                    
                }
            }
                    
            
        }
            
        m_WER->updateResultsButtonClicked();  

    }

    

    file.close();
}





void MainWindowDesigner::on_boutonQuitter_clicked()
{
    // Temporarily disconnect the button's clicked signal
    disconnect(ui->boutonQuitter, &QPushButton::clicked, this, &MainWindowDesigner::on_boutonQuitter_clicked);

    QMessageBox msgBox;
    msgBox.setText("Voulez-vous quitter le programme ?");
    QPushButton *exitWithoutSavingButton = msgBox.addButton("Quitter sans Enregistrer", QMessageBox::RejectRole);
    QPushButton *saveAndQuitButton = msgBox.addButton("Enregistrer et quitter", QMessageBox::AcceptRole);
    QPushButton *cancelButton = msgBox.addButton("Annuler", QMessageBox::NoRole);
    //msgBox.setDefaultButton(cancelButton);

    // Use exec() and store the result in a variable
    int result = msgBox.exec();

    // Check the result directly
    if (msgBox.clickedButton() == exitWithoutSavingButton)
    {
       QApplication::quit();
    }
    else if (msgBox.clickedButton() == saveAndQuitButton)
    {
        on_actionEnregistrer_triggered();
        QApplication::quit();
    }
    else if (msgBox.clickedButton() == cancelButton)
    {
        msgBox.close(); // Close the message box explicitly
    }

    // Reconnect the button's clicked signal
    connect(ui->boutonQuitter, &QPushButton::clicked, this, &MainWindowDesigner::on_boutonQuitter_clicked);
}

void MainWindowDesigner::ProvideContextMenu(const QPoint &pos)
{
    QPoint point = ui->listEquipes->mapToGlobal(pos);
    //m_indice=ui->listEquipes->indexAt(pos).row();
    m_nomEquipeSelectionee=ui->listEquipes->itemAt(pos)->text();
    QMenu submenu;
    submenu.addAction("Supprimer", this, SLOT(supprimerEquipeSelectionnee()));
    submenu.exec(point);
}

void MainWindowDesigner::ProvideContextMenuEpreuve(const QPoint &pos)
{
    QPoint point = ui->listEpreuves->mapToGlobal(pos);
    //m_indice=ui->listEquipes->indexAt(pos).row();
    m_nomEpreuveSelectionee=ui->listEpreuves->itemAt(pos)->text();
    QMenu submenu;
    submenu.addAction("Supprimer", this, SLOT(supprimerEpreuveSelectionnee()));
    submenu.addAction("Définir Ordre de Passage", this, SLOT(DefinirOrdreDePassage()));
    submenu.addAction("Définir Temps de Pénalité", this, SLOT(DefinirTempsDePenalite()));
    submenu.exec(point);
}

void MainWindowDesigner::supprimerEpreuveSelectionnee()
{
    this->supprimerEpreuveBis(m_nomEpreuveSelectionee);

}

void MainWindowDesigner::supprimerEquipeSelectionnee()
{
    this->supprimerEquipeBis(m_nomEquipeSelectionee);

}

void MainWindowDesigner::supprimerEquipeBis(QString NomEquipe)
{
    m_walloniade->supprimerEquipe(NomEquipe);
    this->initListEquipe();
}

void MainWindowDesigner::supprimerEpreuveBis(QString NomEpreuve)
{
    m_walloniade->supprimerEpreuve(NomEpreuve);
    this->initListEpreuve();
}

void MainWindowDesigner::ajouterTirage(QList<QString> ListeNom,QList<int> ListeNumeros)
{
    for (int i=0; i<ListeNom.size(); i++)
    {
        int j=0;
        while (m_walloniade->getEquipe()[j]->getNomEquipe()!=ListeNom[i])
        {
            j++;
        }
        m_walloniade->getEquipe()[j]->setID(ListeNumeros[i]);
    }

}


/*void MainWindowDesigner::PrintMainWindow()
{

}*/

void MainWindowDesigner::on_actionImprimer_triggered()
{
    QPrinter printer;
    printer.setPageMargins(QMarginsF(0, 10, 0, 10)); // Remove printer margins

    QPrintDialog printDialog(&printer, this);

    if (printDialog.exec() == QDialog::Accepted) {
        QTextDocument doc;
        QString html;

        // Header
        html += "<html><head><title>Classement Général</title>";
        html += "<style>";
        html += "table { border-collapse: collapse; width: auto; display: inline-block; }"; // Table styling
        html += "th, td { border: 1px solid black; padding: 5px 10px; text-align: center; }"; // Cell styling
        html += "th { background-color: #f0f0f0; }"; // Header background color (optional)
        html += "</style>";
        html += "</head><body>";
        html += "<div style='text-align: center; margin-bottom: 20px;'><h1>Classement Général</h1></div>";
        html += "<br>";

        // Conteneur centré
        html += "<div style='text-align: center; width: 100%;'>";
        html += "<table>"; // Centrage optimisé

        // En-tête du tableau
        html += "<tr>";
        html += "<th>Classement</th>";
        html += "<th>Equipe</th>";
        html += "<th>Points</th>";
        html += "</tr>";

        // Corps du tableau
        for (int i = 0; i < ui->listClassement->count(); ++i) {
            QString itemText = ui->listClassement->item(i)->text();
            if (!itemText.isEmpty())
            {
                // Find the position of the dot (.) after the ranking
                int dotPos = itemText.indexOf(".");
                // Find the last space (before the points)
                int lastSpacePos = itemText.lastIndexOf(" ");

                if (dotPos != -1 && lastSpacePos != -1 && lastSpacePos > dotPos)
                {
                    // Extract the ranking
                    QString classement = itemText.left(dotPos + 1);

                    // Extract the points
                    QString points = itemText.mid(lastSpacePos + 1);

                    // Extract the team name (everything in between)
                    QString equipe = itemText.mid(dotPos + 1, lastSpacePos - dotPos - 1).trimmed();

                    html += "<tr>";
                    html += QString("<td>%1</td>").arg(classement);
                    html += QString("<td>%1</td>").arg(equipe);
                    html += QString("<td>%1</td>").arg(points);
                    html += "</tr>";
                }
                else
                {
                    html += "<tr>";
                    html += QString("<td></td>");
                    html += QString("<td>%1</td>").arg(itemText);
                    html += QString("<td></td>");
                    html += "</tr>";
                }
            }
        }

        html += "</table></div>"; // Ferme le div
        html += "</body></html>";

        doc.setHtml(html);
        doc.setPageSize(printer.pageRect(QPrinter::Point).size()); // Prevent QTextDocument from adding hidden margins
        doc.print(&printer);
    }
}
