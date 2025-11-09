#include "W_EntrerResultats.h"
#include "mainwindowdesigner.h"
#include <QDebug>
#include <QMessageBox>
#include <QtWidgets>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <QtNumeric>
#include "Equipe.h"
#include <QFileDialog> // Added for file dialog
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QRegularExpression>

WindowEntrerResultat::WindowEntrerResultat(QWidget *parent, Walloniade *Walloniade)
{
    setWindowTitle("Résultats");
    setMinimumWidth(1200);
    // setMinimumHeight(800);
    m_wallo = Walloniade;
    onglets = new QTabWidget;
    m_main = qobject_cast<MainWindowDesigner *>(parent);

    // Create the top zone with the button
    QWidget *topZone = new QWidget;
    QHBoxLayout *topLayout = new QHBoxLayout(topZone);
    QPushButton *m_saveButton = new QPushButton("Enregistrer");
    // QPushButton *m_openButton = new QPushButton("Ouvrir");
    QPushButton *m_updateResultsButton = new QPushButton("Mettre résultats à jour");
    QPushButton *m_resetTabButton = new QPushButton("Réinitialiser Onglet En Cours");
    QPushButton *m_PrintTabRankingButton = new QPushButton("Imprimer Classement Final Onglet En Cours");
    // m_updateResultsButton = new QPushButton("Mettre résultats à jour");
    m_updateResultsButton->setStyleSheet("QPushButton {font-size: 14px; padding: 10px;}"); // Added style for a better look
    m_resetTabButton->setStyleSheet("QPushButton {font-size: 14px; padding: 10px;}");
    m_PrintTabRankingButton->setStyleSheet("QPushButton {font-size: 14px; padding: 10px;}");
    // m_openButton->setStyleSheet("QPushButton {font-size: 14px; padding: 10px;}");
    m_saveButton->setStyleSheet("QPushButton {font-size: 14px; padding: 10px;}");

    // Center the button
    topLayout->addStretch(1);
    topLayout->addWidget(m_updateResultsButton);
    topLayout->addWidget(m_resetTabButton);
    topLayout->addWidget(m_PrintTabRankingButton);
    topLayout->addWidget(m_saveButton);
    // topLayout->addWidget(m_openButton);
    topLayout->addStretch(1);

    // Connect the button's clicked signal to the slot
    connect(m_updateResultsButton, &QPushButton::clicked, this, &WindowEntrerResultat::updateResultsButtonClicked);

    // Connect the reset button's clicked signal to the slot
    connect(m_resetTabButton, &QPushButton::clicked, this, &WindowEntrerResultat::resetCurrentTab);

    // Connect the print button's clicked signal to the slot
    connect(m_PrintTabRankingButton, &QPushButton::clicked, this, &WindowEntrerResultat::printCurrentTab);

    // Connect the save button'sclicked signal to the slot
    connect(m_saveButton, &QPushButton::clicked, this, &WindowEntrerResultat::saveButtonClicked);

    // Connect the open button's clicked signal to the slot
    // connect(m_openButton, &QPushButton::clicked, this, &WindowEntrerResultat::openButtonClicked);

    // Main layout for the window
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(topZone);
    mainLayout->addWidget(onglets);

    // Initialize tabs (same as before)
    for (int j = 0; j < m_wallo->getEpreuve().size(); j++)
    {
        QWidget *page = new QWidget;
        if (m_wallo->getEpreuve()[j]->getType() == 0)
        {
            initialiserLayoutEpreuveTemps(page, j);
            m_wallo->getEpreuve()[j]->setPageEntrerResultat(page);
        }
        else if (m_wallo->getEpreuve()[j]->getType() == 1)
        {
            initialiserLayoutEpreuvePoints(page, j);
            m_wallo->getEpreuve()[j]->setPageEntrerResultat(page);
        }
        else if (m_wallo->getEpreuve()[j]->getType() == 2)
        {
            initialiserLayoutEpreuveTempsPosNeg(page, j);
            m_wallo->getEpreuve()[j]->setPageEntrerResultat(page);
        }
        else
        {
            initialiserLayoutEpreuveTempsOuNiveau(page, j);
            m_wallo->getEpreuve()[j]->setPageEntrerResultat(page);
        }

        onglets->addTab(page, m_wallo->getEpreuve()[j]->getNomEpreuve());
    }
    int k = onglets->count();
    QWidget *page = new QWidget;
    initialiserLayoutClassementGeneral(page, k);
    onglets->addTab(page, "Classement Général");

    // Set the main layout for the window

    this->setLayout(mainLayout);
}

QTabWidget *WindowEntrerResultat::getOnglets()
{
    return onglets;
}

QList<QDoubleSpinBox *> WindowEntrerResultat::getListeChampsTemps()
{
    return m_listeChampsTemps;
}

QMap<int, QListWidget *> WindowEntrerResultat::getMapClassementFinal()
{
    return MapClassementFinal;
}

void WindowEntrerResultat::initialiserLayoutClassementGeneral(QWidget *page, int j)
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    QLabel *titre = new QLabel("Classement Général");
    titre->setAlignment(Qt::AlignCenter);
    titre->setFont(QFont("Comic Sans MS", 20, QFont::Bold, true));
    layoutPrincipal->addWidget(titre);
    QListWidget *classement = new QListWidget;
    classement->setFont(QFont("consolas", 12));
    // classement->setStyleSheet("QListWidget { font-size: 12px; }");
    layoutPrincipal->addWidget(classement);
    page->setLayout(layoutPrincipal);
    MapClassementFinal.insert(j, classement);
}

void WindowEntrerResultat::initialiserLayoutEpreuveTemps(QWidget *page, int j)
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    QHBoxLayout *layoutHorizontalPrincipal = new QHBoxLayout;
    QVBoxLayout *layoutVerticalGaucheComplet = new QVBoxLayout;

    QGridLayout *layoutVerticalGauche = new QGridLayout;

    QVBoxLayout *layoutVerticalCentre = new QVBoxLayout;

    QVBoxLayout *layoutVerticalDroite = new QVBoxLayout;

    QListWidget *classementPartiel = new QListWidget;
    // QListWidget *listeEquipesRestantes = new QListWidget;
    QListWidget *classementFinal = new QListWidget;
    QGroupBox *encoderResultats = new QGroupBox;
    QGroupBox *MajResultats = new QGroupBox;
    QGroupBox *situationPartielle = new QGroupBox;
    QGroupBox *classement = new QGroupBox;

    encoderResultats->setTitle("Encodage des résultats...");
    situationPartielle->setTitle("Classement partiel :");
    MajResultats->setTitle("Mise à jour des résultats :");
    classement->setTitle("Classement Final de l'épreuve");

    QLabel *titre = new QLabel(m_wallo->getEpreuve()[j]->getNomEpreuve());
    titre->setAlignment(Qt::AlignCenter);
    titre->setFont(QFont("Comic Sans MS", 20, QFont::Bold, true));
    QLabel *nomColonne1 = new QLabel("Equipe");
    QLabel *nomColonne2 = new QLabel("Temps Brut");
    QLabel *nomColonne3 = new QLabel("Pénalités");
    layoutVerticalGauche->addWidget(nomColonne1, 0, 0);
    layoutVerticalGauche->addWidget(nomColonne2, 0, 1);
    layoutVerticalGauche->addWidget(nomColonne3, 0, 2);

    m_listeChampsTemps.clear();
    m_listeChampsPenalite.clear();
    for (int i = 0; i < m_wallo->getEquipe().size(); i++)
    {
        int k = m_wallo->getEpreuve()[j]->getOrdreDePassage()[i];
        k = k - 1;
        // QMessageBox::information(this, "Information", QString("Numéro d'ordre de passage %1 - Equipe %2").arg(k+1).arg(m_wallo->getEquipe()[k]->getNomEquipe()));
        QLabel *NomEquipe = new QLabel(m_wallo->getEquipe()[k]->getNomEquipe());
        QSpinBox *NouveauChampPenalite = new QSpinBox();
        NouveauChampPenalite->setButtonSymbols(QAbstractSpinBox::NoButtons);
        NouveauChampPenalite->setAlignment(Qt::AlignRight);
        NouveauChampPenalite->clear();
        m_listeChampsPenalite.append(NouveauChampPenalite);

        QDoubleSpinBox *NouveauChampTempsBrut = new QDoubleSpinBox();
        NouveauChampTempsBrut->setMinimum(0);
        NouveauChampTempsBrut->setMaximum(1000);
        NouveauChampTempsBrut->setDecimals(2);
        NouveauChampTempsBrut->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        NouveauChampTempsBrut->setButtonSymbols(QAbstractSpinBox::NoButtons);
        NouveauChampTempsBrut->setAlignment(Qt::AlignRight);
        NouveauChampTempsBrut->clear();
        m_listeChampsTemps.append(NouveauChampTempsBrut);

        layoutVerticalGauche->addWidget(NomEquipe, i + 1, 0);
        layoutVerticalGauche->addWidget(NouveauChampTempsBrut, i + 1, 1);
        layoutVerticalGauche->addWidget(NouveauChampPenalite, i + 1, 2);
    }

    layoutVerticalGaucheComplet->addLayout(layoutVerticalGauche);

    encoderResultats->setLayout(layoutVerticalGaucheComplet);

    layoutVerticalCentre->addWidget(classementPartiel);
    // layoutVerticalCentre->addWidget(listeEquipesRestantes);
    situationPartielle->setLayout(layoutVerticalCentre);

    layoutVerticalDroite->addWidget(classementFinal);
    classement->setLayout(layoutVerticalDroite);

    layoutHorizontalPrincipal->addWidget(encoderResultats);
    layoutHorizontalPrincipal->addWidget(situationPartielle);
    layoutHorizontalPrincipal->addWidget(classement);
    layoutPrincipal->addWidget(titre);
    layoutPrincipal->addLayout(layoutHorizontalPrincipal);
    page->setLayout(layoutPrincipal);
    MapTempsBrut.insert(j, m_listeChampsTemps);
    MapPenalites.insert(j, m_listeChampsPenalite);
    MapClassementPartiel.insert(j, classementPartiel);
    MapClassementFinal.insert(j, classementFinal);
}

void WindowEntrerResultat::initialiserLayoutEpreuveTempsOuNiveau(QWidget *page, int j)
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    QHBoxLayout *layoutHorizontalPrincipal = new QHBoxLayout;
    QGridLayout *layoutVerticalGauche = new QGridLayout;

    QVBoxLayout *layoutVerticalCentre = new QVBoxLayout;

    QVBoxLayout *layoutVerticalDroite = new QVBoxLayout;

    QListWidget *classementPartiel = new QListWidget;
    // QListWidget *listeEquipesRestantes = new QListWidget;
    QListWidget *classementFinal = new QListWidget;
    QGroupBox *encoderResultats = new QGroupBox;
    QGroupBox *situationPartielle = new QGroupBox;
    QGroupBox *classement = new QGroupBox;

    encoderResultats->setTitle("Encodage des résultats...");
    situationPartielle->setTitle("Classement partiel :");
    classement->setTitle("Classement Final de l'épreuve :");

    QLabel *titre = new QLabel(m_wallo->getEpreuve()[j]->getNomEpreuve());
    titre->setAlignment(Qt::AlignCenter);
    titre->setFont(QFont("Comic Sans MS", 20, QFont::Bold, true));
    QLabel *nomColonne1 = new QLabel("Equipe");
    QLabel *nomColonne2 = new QLabel("Temps Brut");
    QLabel *nomColonne3 = new QLabel("Niveau");
    layoutVerticalGauche->addWidget(nomColonne1, 0, 0);
    layoutVerticalGauche->addWidget(nomColonne2, 0, 1);
    layoutVerticalGauche->addWidget(nomColonne3, 0, 2);
    m_listeChampsTemps.clear();
    m_listeChampsNiveau.clear();
    for (int i = 0; i < m_wallo->getEquipe().size(); i++)
    {
        int k = m_wallo->getEpreuve()[j]->getOrdreDePassage()[i];
        k = k - 1;
        QLabel *NomEquipe = new QLabel(m_wallo->getEquipe()[k]->getNomEquipe());
        QSpinBox *NouveauChampNiveau = new QSpinBox();
        NouveauChampNiveau->setButtonSymbols(QAbstractSpinBox::NoButtons);
        NouveauChampNiveau->setAlignment(Qt::AlignRight);
        NouveauChampNiveau->clear();
        m_listeChampsNiveau.append(NouveauChampNiveau);

        QDoubleSpinBox *NouveauChampTempsBrut = new QDoubleSpinBox();
        NouveauChampTempsBrut->setMinimum(0);
        NouveauChampTempsBrut->setMaximum(1000);
        NouveauChampTempsBrut->setDecimals(2);
        NouveauChampTempsBrut->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        NouveauChampTempsBrut->setButtonSymbols(QAbstractSpinBox::NoButtons);
        NouveauChampTempsBrut->setAlignment(Qt::AlignRight);
        NouveauChampTempsBrut->clear();
        m_listeChampsTemps.append(NouveauChampTempsBrut);

        layoutVerticalGauche->addWidget(NomEquipe, i + 1, 0);
        layoutVerticalGauche->addWidget(NouveauChampTempsBrut, i + 1, 1);
        layoutVerticalGauche->addWidget(NouveauChampNiveau, i + 1, 2);
    }
    encoderResultats->setLayout(layoutVerticalGauche);
    // layoutVerticalGaucheComplet->addWidget(MettreAJour);

    layoutVerticalCentre->addWidget(classementPartiel);
    // layoutVerticalCentre->addWidget(listeEquipesRestantes);
    situationPartielle->setLayout(layoutVerticalCentre);

    layoutVerticalDroite->addWidget(classementFinal);
    classement->setLayout(layoutVerticalDroite);

    layoutHorizontalPrincipal->addWidget(encoderResultats);
    layoutHorizontalPrincipal->addWidget(situationPartielle);
    layoutHorizontalPrincipal->addWidget(classement);
    layoutPrincipal->addWidget(titre);
    layoutPrincipal->addLayout(layoutHorizontalPrincipal);
    page->setLayout(layoutPrincipal);
    MapTempsBrut.insert(j, m_listeChampsTemps);
    MapNiveau.insert(j, m_listeChampsNiveau);
    MapClassementPartiel.insert(j, classementPartiel);
    MapClassementFinal.insert(j, classementFinal);
}

void WindowEntrerResultat::initialiserLayoutEpreuvePoints(QWidget *page, int j)
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    QHBoxLayout *layoutHorizontalPrincipal = new QHBoxLayout;
    QGridLayout *layoutVerticalGauche = new QGridLayout;

    QVBoxLayout *layoutVerticalCentre = new QVBoxLayout;

    QVBoxLayout *layoutVerticalDroite = new QVBoxLayout;

    QListWidget *classementPartiel = new QListWidget;

    // QListWidget *listeEquipesRestantes = new QListWidget;
    QListWidget *classementFinal = new QListWidget;
    QGroupBox *encoderResultats = new QGroupBox;
    QGroupBox *situationPartielle = new QGroupBox;
    QGroupBox *classement = new QGroupBox;

    encoderResultats->setTitle("Encodage des résultats...");
    situationPartielle->setTitle("Classement partiel :");
    classement->setTitle("Classement Final de l'épreuve :");

    QLabel *titre = new QLabel(m_wallo->getEpreuve()[j]->getNomEpreuve());
    titre->setAlignment(Qt::AlignCenter);
    titre->setFont(QFont("Comic Sans MS", 20, QFont::Bold, true));
    QLabel *nomColonne1 = new QLabel("Equipe");
    QLabel *nomColonne2 = new QLabel("Points");
    layoutVerticalGauche->addWidget(nomColonne1, 0, 0);
    layoutVerticalGauche->addWidget(nomColonne2, 0, 1);
    m_listeChampsPoints.clear();

    for (int i = 0; i < m_wallo->getEquipe().size(); i++)
    {

        QLabel *NomEquipe = new QLabel(m_wallo->getEquipe()[i]->getNomEquipe());
        QSpinBox *NouveauChampPoints = new QSpinBox();
        NouveauChampPoints->setButtonSymbols(QAbstractSpinBox::NoButtons);
        NouveauChampPoints->setAlignment(Qt::AlignRight);
        NouveauChampPoints->clear();
        m_listeChampsPoints.append(NouveauChampPoints);

        layoutVerticalGauche->addWidget(NomEquipe, i + 1, 0);
        layoutVerticalGauche->addWidget(NouveauChampPoints, i + 1, 1);
    }
    encoderResultats->setLayout(layoutVerticalGauche);
    // layoutVerticalGaucheComplet->addWidget(MettreAJour);

    layoutVerticalCentre->addWidget(classementPartiel);
    // layoutVerticalCentre->addWidget(listeEquipesRestantes);
    situationPartielle->setLayout(layoutVerticalCentre);

    layoutVerticalDroite->addWidget(classementFinal);
    classement->setLayout(layoutVerticalDroite);

    layoutHorizontalPrincipal->addWidget(encoderResultats);
    layoutHorizontalPrincipal->addWidget(situationPartielle);
    layoutHorizontalPrincipal->addWidget(classement);
    layoutPrincipal->addWidget(titre);
    layoutPrincipal->addLayout(layoutHorizontalPrincipal);
    page->setLayout(layoutPrincipal);
    MapPoints.insert(j, m_listeChampsPoints);
    MapClassementPartiel.insert(j, classementPartiel);
    MapClassementFinal.insert(j, classementFinal);
}

void WindowEntrerResultat::initialiserLayoutEpreuveTempsPosNeg(QWidget *page, int j)
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    QHBoxLayout *layoutHorizontalPrincipal = new QHBoxLayout;
    QVBoxLayout *layoutVerticalGaucheComplet = new QVBoxLayout;

    QGridLayout *layoutVerticalGauche = new QGridLayout;

    QVBoxLayout *layoutVerticalCentre = new QVBoxLayout;

    QVBoxLayout *layoutVerticalDroite = new QVBoxLayout;

    QListWidget *classementPartiel = new QListWidget;
    // QListWidget *listeEquipesRestantes = new QListWidget;
    QListWidget *classementFinal = new QListWidget;
    QGroupBox *encoderResultats = new QGroupBox;
    QGroupBox *MajResultats = new QGroupBox;
    QGroupBox *situationPartielle = new QGroupBox;
    QGroupBox *classement = new QGroupBox;

    encoderResultats->setTitle("Encodage des résultats...");
    situationPartielle->setTitle("Classement partiel :");
    // MajResultats->setTitle("Mise à jour des résultats");
    classement->setTitle("Classement Final de l'épreuve :");

    QLabel *titre = new QLabel(m_wallo->getEpreuve()[j]->getNomEpreuve());
    titre->setAlignment(Qt::AlignCenter);
    titre->setFont(QFont("Comic Sans MS", 20, QFont::Bold, true));
    QLabel *nomColonne1 = new QLabel("Equipe");
    QLabel *nomColonne2 = new QLabel("Temps Brut");
    QLabel *nomColonne3 = new QLabel("Match ");
    layoutVerticalGauche->addWidget(nomColonne1, 0, 1);
    layoutVerticalGauche->addWidget(nomColonne2, 0, 2);
    layoutVerticalGauche->addWidget(nomColonne3, 0, 0);

    m_listeChampsTemps.clear();
    // m_listeChampsPenalite.clear();
    int p = 1;
    for (int i = 0; i < m_wallo->getEquipe().size(); i++)
    {
        int k = m_wallo->getEpreuve()[j]->getOrdreDePassage()[i];
        k = k - 1;

        QLabel *NomEquipe = new QLabel(m_wallo->getEquipe()[k]->getNomEquipe());

        if ((i % 2) == 0)
        {

            QLabel *NumeroMatch = new QLabel(QString("%1.").arg(p));
            layoutVerticalGauche->addWidget(NumeroMatch, i + 1, 0);
            p++;
        }

        /*QSpinBox *NouveauChampPenalite = new QSpinBox();
        NouveauChampPenalite->setButtonSymbols(QAbstractSpinBox::NoButtons);
        NouveauChampPenalite->setAlignment(Qt::AlignRight);
        NouveauChampPenalite->clear();
        m_listeChampsPenalite.append(NouveauChampPenalite); */

        QDoubleSpinBox *NouveauChampTempsBrut = new QDoubleSpinBox();
        NouveauChampTempsBrut->setMinimum(-1000);
        NouveauChampTempsBrut->setMaximum(1000);
        NouveauChampTempsBrut->setMaximumWidth(50);
        NouveauChampTempsBrut->setDecimals(2);
        NouveauChampTempsBrut->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        NouveauChampTempsBrut->setButtonSymbols(QAbstractSpinBox::NoButtons);
        NouveauChampTempsBrut->setAlignment(Qt::AlignRight);
        NouveauChampTempsBrut->clear();
        m_listeChampsTemps.append(NouveauChampTempsBrut);

        layoutVerticalGauche->addWidget(NomEquipe, i + 1, 1);
        layoutVerticalGauche->addWidget(NouveauChampTempsBrut, i + 1, 2);
        // layoutVerticalGauche->addWidget(NouveauChampPenalite,i+1,2);
    }

    layoutVerticalGaucheComplet->addLayout(layoutVerticalGauche);

    encoderResultats->setLayout(layoutVerticalGaucheComplet);

    layoutVerticalCentre->addWidget(classementPartiel);
    // layoutVerticalCentre->addWidget(listeEquipesRestantes);
    situationPartielle->setLayout(layoutVerticalCentre);

    layoutVerticalDroite->addWidget(classementFinal);
    classement->setLayout(layoutVerticalDroite);

    layoutHorizontalPrincipal->addWidget(encoderResultats);
    layoutHorizontalPrincipal->addWidget(situationPartielle);
    layoutHorizontalPrincipal->addWidget(classement);
    layoutPrincipal->addWidget(titre);
    layoutPrincipal->addLayout(layoutHorizontalPrincipal);
    page->setLayout(layoutPrincipal);
    MapTempsBrut.insert(j, m_listeChampsTemps);
    MapClassementPartiel.insert(j, classementPartiel);
    MapClassementFinal.insert(j, classementFinal);
}

void WindowEntrerResultat::updateResultsButtonClicked()

{

    QList<double> valeurs;
    QList<int> valeursPenalites;
    QList<int> valeursNiveau;
    QList<int> valeursPoints;
    QList<double> valeursPositives;
    QList<double> valeursNegatives;

    for (int j = 0; j < m_wallo->getEquipe().size(); j++)
    {
        m_wallo->getEquipe()[j]->resetTotalPoints();
        m_wallo->getEquipe()[j]->resetNombrePremierePlace();
        m_wallo->getEquipe()[j]->resetNombreDeuxiemePlace();
        m_wallo->getEquipe()[j]->resetNombreTroisiemePlace();
    }

    for (int i = 0; i < m_wallo->getEpreuve().size(); i++)
    {

        if (m_wallo->getEpreuve()[i]->getType() == 0)
        {
            valeurs.clear();
            valeursPenalites.clear();
            for (int j = 0; j < m_wallo->getEquipe().size(); j++)
            {
                if (MapTempsBrut[i][j]->text().isEmpty())
                {
                    valeurs.append(9999);
                }
                else
                {
                    valeurs.append(MapTempsBrut[i][j]->value());
                }

                if (MapPenalites[i][j]->text().isEmpty())
                {
                    valeursPenalites.append(0);
                }
                else
                {
                    valeursPenalites.append(MapPenalites[i][j]->value());
                }
            }
            // QMessageBox::information(this, "Update Results", QString(" i = %1 - j = %2").arg(i).arg(j));

            m_wallo->getEpreuve()[i]->setTempsBrut(valeurs);
            m_wallo->getEpreuve()[i]->setPenalites(valeursPenalites);

            QList<resultat> CurrentResultat;
            CurrentResultat.clear();
            for (int j = 0; j < m_wallo->getEquipe().size(); j++)
            {

                if (m_wallo->getEpreuve()[i]->getTempsBrut()[j] != 9999)
                {
                    resultat temporaire;
                    int k;
                    k = m_wallo->getEpreuve()[i]->getOrdreDePassage()[j];
                    k = k - 1;
                    temporaire.EquipeID = m_wallo->getEquipe()[k]->getID();
                    temporaire.NomEquipe = m_wallo->getEquipe()[k]->getNomEquipe();
                    temporaire.TempsBrut = m_wallo->getEpreuve()[i]->getTempsBrut()[j];
                    temporaire.nbrePenalites = m_wallo->getEpreuve()[i]->getPenalites()[j];
                    temporaire.TempsTotalSecondes = m_wallo->getEpreuve()[i]->minutes(temporaire.TempsBrut) * 60 + m_wallo->getEpreuve()[i]->secondes(temporaire.TempsBrut) + temporaire.nbrePenalites * m_wallo->getEpreuve()[i]->getNombreDeSecondeParPenalite();
                    CurrentResultat.append(temporaire);
                }
            }

            std::sort(CurrentResultat.begin(), CurrentResultat.end(), [](const resultat &a, const resultat &b)
                      { return a.TempsTotalSecondes < b.TempsTotalSecondes; });

            // update du classement/points
            for (int j = 0; j < CurrentResultat.size(); j++)
            {
                if (j == 0)
                {
                    CurrentResultat[j].Classement = 1;
                }
                else if (CurrentResultat[j].TempsTotalSecondes == CurrentResultat[j - 1].TempsTotalSecondes)
                {
                    CurrentResultat[j].Classement = CurrentResultat[j - 1].Classement;
                }
                else
                {
                    CurrentResultat[j].Classement = j + 1;
                }
            }
            m_wallo->getEpreuve()[i]->setResultatEpreuveTemps(CurrentResultat);

            for (int j = 0; j < CurrentResultat.size(); j++)
            {
                int k = CurrentResultat[j].EquipeID;
                k = k - 1;
                m_wallo->getEquipe()[k]->increaseTotalPoints(CurrentResultat[j].Classement);
                if (CurrentResultat[j].Classement == 1)
                {
                    m_wallo->getEquipe()[k]->increaseNombrePremierePlace();
                }

                if (CurrentResultat[j].Classement == 2)
                {
                    m_wallo->getEquipe()[k]->increaseNombreDeuxiemePlace();
                }
                if (CurrentResultat[j].Classement == 3)
                {
                    m_wallo->getEquipe()[k]->increaseNombreTroisiemePlace();
                }
            }

            if (m_wallo->getEpreuve()[i]->getResultatEpreuve().size() < m_wallo->getEquipe().size())
            {
                MapClassementPartiel[i]->clear();
                MapClassementPartiel[i]->setFont(QFont("consolas", 12));
                MapClassementPartiel[i]->addItem(" ");
                for (int j = 0; j < m_wallo->getEpreuve()[i]->getResultatEpreuve().size(); j++)
                {

                    int point = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].Classement;
                    QString ClassementStr = QString::number(point) + ".";
                    QString Equip = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].NomEquipe;
                    ClassementStr.insert(6, Equip);
                    int min;
                    float sec;
                    min = m_wallo->getEpreuve()[i]->minutes2(m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes);
                    sec = m_wallo->getEpreuve()[i]->secondes2(m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes);
                    int seconde = floor(sec);
                    int centieme = (round(sec * 100)) - (seconde * 100);
                    ClassementStr.insert(35, QString::number(min).rightJustified(2, '0') + "'" + QString::number(seconde).rightJustified(2, '0') + "\"" + QString::number(centieme).rightJustified(2, '0'));
                    MapClassementPartiel[i]->addItem(ClassementStr);
                }
            }

            else
            {
                MapClassementPartiel[i]->clear();
                MapClassementFinal[i]->clear();
                MapClassementFinal[i]->setFont(QFont("consolas", 12));
                MapClassementFinal[i]->addItem(" ");

                for (int j = 0; j < m_wallo->getEpreuve()[i]->getResultatEpreuve().size(); j++)
                {

                    int point = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].Classement;
                    QString ClassementStr = QString::number(point) + ".";
                    QString Equip = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].NomEquipe;
                    ClassementStr.insert(6, Equip);
                    int min;
                    float sec;
                    min = m_wallo->getEpreuve()[i]->minutes2(m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes);
                    sec = m_wallo->getEpreuve()[i]->secondes2(m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes);
                    int seconde = floor(sec);
                    int centieme = (round(sec * 100)) - (seconde * 100);
                    ClassementStr.insert(35, QString::number(min).rightJustified(2, '0') + "'" + QString::number(seconde).rightJustified(2, '0') + "\"" + QString::number(centieme).rightJustified(2, '0'));
                    MapClassementFinal[i]->addItem(ClassementStr);
                }
            }
        }

        if (m_wallo->getEpreuve()[i]->getType() == 1)
        {

            valeursPoints.clear();
            for (int j = 0; j < m_wallo->getEquipe().size(); j++)
            {
                if (MapPoints[i][j]->text().isEmpty())
                {
                    valeursPoints.append(-1);
                }
                else
                {
                    valeursPoints.append(MapPoints[i][j]->value());
                }
            }

            m_wallo->getEpreuve()[i]->setPoints(valeursPoints);

            QList<resultat> CurrentResultat;
            CurrentResultat.clear();
            for (int j = 0; j < m_wallo->getEquipe().size(); j++)
            {

                if (m_wallo->getEpreuve()[i]->getPoints()[j] != -1)
                {
                    resultat temporaire;
                    temporaire.EquipeID = m_wallo->getEquipe()[j]->getID();
                    temporaire.NomEquipe = m_wallo->getEquipe()[j]->getNomEquipe();
                    temporaire.NombrePoints = m_wallo->getEpreuve()[i]->getPoints()[j];
                    CurrentResultat.append(temporaire);
                }
            }

            std::sort(CurrentResultat.begin(), CurrentResultat.end(), [](const resultat &a, const resultat &b)
                      { return a.NombrePoints > b.NombrePoints; });

            for (int j = 0; j < CurrentResultat.size(); j++)
            {
                if (j == 0)
                {
                    CurrentResultat[j].Classement = 1;
                }
                else if (CurrentResultat[j].NombrePoints == CurrentResultat[j - 1].NombrePoints)
                {
                    CurrentResultat[j].Classement = CurrentResultat[j - 1].Classement;
                }
                else
                {
                    CurrentResultat[j].Classement = j + 1;
                }
            }

            m_wallo->getEpreuve()[i]->setResultatEpreuvePoints(CurrentResultat);

            for (int j = 0; j < CurrentResultat.size(); j++)
            {
                int k = CurrentResultat[j].EquipeID;
                k = k - 1;
                m_wallo->getEquipe()[k]->increaseTotalPoints(CurrentResultat[j].Classement);
                if (CurrentResultat[j].Classement == 1)
                {
                    m_wallo->getEquipe()[k]->increaseNombrePremierePlace();
                }

                if (CurrentResultat[j].Classement == 2)
                {
                    m_wallo->getEquipe()[k]->increaseNombreDeuxiemePlace();
                }
                if (CurrentResultat[j].Classement == 3)
                {
                    m_wallo->getEquipe()[k]->increaseNombreTroisiemePlace();
                }
            }

            if (m_wallo->getEpreuve()[i]->getResultatEpreuve().size() < m_wallo->getEquipe().size())
            {

                MapClassementPartiel[i]->clear();
                MapClassementPartiel[i]->setFont(QFont("consolas", 12));
                MapClassementPartiel[i]->addItem(" ");

                for (int j = 0; j < m_wallo->getEpreuve()[i]->getResultatEpreuve().size(); j++)
                {

                    int point = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].Classement;
                    QString ClassementStr = QString::number(point) + ".";
                    QString Equip = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].NomEquipe;
                    ClassementStr.insert(6, Equip);
                    int pointResultat = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].NombrePoints;
                    ClassementStr.insert(35, QString::number(pointResultat));
                    MapClassementPartiel[i]->addItem(ClassementStr);
                }
            }

            else
            {
                MapClassementPartiel[i]->clear();
                MapClassementFinal[i]->clear();
                MapClassementFinal[i]->setFont(QFont("consolas", 12));
                MapClassementFinal[i]->addItem(" ");

                for (int j = 0; j < m_wallo->getEpreuve()[i]->getResultatEpreuve().size(); j++)
                {

                    int point = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].Classement;
                    QString ClassementStr = QString::number(point) + ".";
                    QString Equip = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].NomEquipe;
                    ClassementStr.insert(6, Equip);
                    int pointResultat = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].NombrePoints;
                    ClassementStr.insert(35, QString::number(pointResultat));
                    MapClassementFinal[i]->addItem(ClassementStr);
                }
            }
        }

        if (m_wallo->getEpreuve()[i]->getType() == 2)
        {

            valeursPositives.clear();
            valeursNegatives.clear();

            for (int j = 0; j < m_wallo->getEquipe().size(); j++)
            {
                if (MapTempsBrut[i][j]->text().isEmpty())
                {
                    valeursPositives.append(9999);
                    valeursNegatives.append(-9999);
                }
                else
                {
                    if (MapTempsBrut[i][j]->value() < 0)
                    {
                        valeursNegatives.append(MapTempsBrut[i][j]->value());
                        valeursPositives.append(9999);
                    }
                    else
                    {
                        valeursPositives.append(MapTempsBrut[i][j]->value());
                        valeursNegatives.append(-9999);
                    }
                }
            }
            m_wallo->getEpreuve()[i]->setTempsBrutPositif(valeursPositives);
            m_wallo->getEpreuve()[i]->setTempsBrutNegatif(valeursNegatives);

            QList<resultat> CurrentResultatTempsPositif;
            QList<resultat> CurrentResultatTempsNegatif;
            QList<resultat> CurrentResultat;
            CurrentResultatTempsPositif.clear();
            CurrentResultatTempsNegatif.clear();
            CurrentResultat.clear();
            for (int j = 0; j < m_wallo->getEquipe().size(); j++)
            {

                if (m_wallo->getEpreuve()[i]->getTempsBrutPositif()[j] != 9999 || m_wallo->getEpreuve()[i]->getTempsBrutNegatif()[j] != -9999)
                {
                    resultat temporaire;
                    int k;
                    k = m_wallo->getEpreuve()[i]->getOrdreDePassage()[j];
                    k = k - 1;
                    temporaire.EquipeID = m_wallo->getEquipe()[k]->getID();
                    temporaire.NomEquipe = m_wallo->getEquipe()[k]->getNomEquipe();
                    if (m_wallo->getEpreuve()[i]->getTempsBrutPositif()[j] != 9999)
                    {
                        temporaire.TempsBrut = m_wallo->getEpreuve()[i]->getTempsBrutPositif()[j];
                        temporaire.TempsTotalSecondes = m_wallo->getEpreuve()[i]->minutes(temporaire.TempsBrut) * 60 + m_wallo->getEpreuve()[i]->secondes(temporaire.TempsBrut);
                        CurrentResultatTempsPositif.append(temporaire);
                    }
                    else
                    {
                        temporaire.TempsBrut = m_wallo->getEpreuve()[i]->getTempsBrutNegatif()[j];
                        temporaire.TempsTotalSecondes = -1 * (m_wallo->getEpreuve()[i]->minutes(-1 * (temporaire.TempsBrut)) * 60 + m_wallo->getEpreuve()[i]->secondes(-1 * (temporaire.TempsBrut)));
                        CurrentResultatTempsNegatif.append(temporaire);
                    }
                }
            }

            std::sort(CurrentResultatTempsPositif.begin(), CurrentResultatTempsPositif.end(), [](const resultat &a, const resultat &b)
                      { return a.TempsTotalSecondes < b.TempsTotalSecondes; });

            std::sort(CurrentResultatTempsNegatif.begin(), CurrentResultatTempsNegatif.end(), [](const resultat &a, const resultat &b)
                      { return a.TempsTotalSecondes < b.TempsTotalSecondes; });

            int NbResTpsPos = CurrentResultatTempsPositif.size();
            int NbResTpsNeg = CurrentResultatTempsNegatif.size();

            for (int j = 0; j < NbResTpsPos; j++)
            {
                CurrentResultat.append(CurrentResultatTempsPositif[j]);
            }

            for (int j = 0; j < NbResTpsNeg; j++)
            {
                CurrentResultat.append(CurrentResultatTempsNegatif[j]);
            }

            for (int j = 0; j < NbResTpsPos; j++)
            {
                if (j == 0)
                {
                    CurrentResultat[j].Classement = 1;
                }
                else if (CurrentResultat[j].TempsTotalSecondes == CurrentResultat[j - 1].TempsTotalSecondes)
                {
                    CurrentResultat[j].Classement = CurrentResultat[j - 1].Classement;
                }
                else
                {
                    CurrentResultat[j].Classement = j + 1;
                }
            }

            for (int j = NbResTpsPos; j < NbResTpsPos + NbResTpsNeg; j++)
            {
                if (j == NbResTpsPos)
                {
                    CurrentResultat[j].Classement = CurrentResultat[j - 1].Classement + 1;
                }
                else if (CurrentResultat[j].TempsTotalSecondes == CurrentResultat[j - 1].TempsTotalSecondes)
                {
                    CurrentResultat[j].Classement = CurrentResultat[j - 1].Classement;
                }
                else
                {
                    CurrentResultat[j].Classement = j + 1;
                }
            }

            m_wallo->getEpreuve()[i]->setResultatEpreuvePosNeg(CurrentResultat);

            for (int j = 0; j < CurrentResultat.size(); j++)
            {
                int k = CurrentResultat[j].EquipeID;
                k = k - 1;
                m_wallo->getEquipe()[k]->increaseTotalPoints(CurrentResultat[j].Classement);
                if (CurrentResultat[j].Classement == 1)
                {
                    m_wallo->getEquipe()[k]->increaseNombrePremierePlace();
                }

                if (CurrentResultat[j].Classement == 2)
                {
                    m_wallo->getEquipe()[k]->increaseNombreDeuxiemePlace();
                }
                if (CurrentResultat[j].Classement == 3)
                {
                    m_wallo->getEquipe()[k]->increaseNombreTroisiemePlace();
                }
            }

            if (m_wallo->getEpreuve()[i]->getResultatEpreuve().size() < m_wallo->getEquipe().size())
            {
                MapClassementPartiel[i]->clear();
                MapClassementPartiel[i]->setFont(QFont("consolas", 12));
                MapClassementPartiel[i]->addItem(" ");
                for (int j = 0; j < m_wallo->getEpreuve()[i]->getResultatEpreuve().size(); j++)
                {

                    int point = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].Classement;
                    QString ClassementStr = QString::number(point) + ".";
                    QString Equip = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].NomEquipe;
                    ClassementStr.insert(6, Equip);
                    if (j < NbResTpsPos)
                    {

                        int min;
                        float sec;
                        min = m_wallo->getEpreuve()[i]->minutes2(m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes);
                        sec = m_wallo->getEpreuve()[i]->secondes2(m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes);
                        int seconde = floor(sec);
                        int centieme = (round(sec * 100)) - (seconde * 100);
                        ClassementStr.insert(35, QString::number(min).rightJustified(2, '0') + "'" + QString::number(seconde).rightJustified(2, '0') + "\"" + QString::number(centieme).rightJustified(2, '0'));
                    }
                    else
                    {
                        int min;
                        float sec;
                        min = m_wallo->getEpreuve()[i]->minutes2(-1 * (m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes));
                        sec = m_wallo->getEpreuve()[i]->secondes2(-1 * (m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes));
                        int seconde = floor(sec);
                        int centieme = (round(sec * 100)) - (seconde * 100);
                        ClassementStr.insert(34, "-" + QString::number(min).rightJustified(2, '0') + "'" + QString::number(seconde).rightJustified(2, '0') + "\"" + QString::number(centieme).rightJustified(2, '0'));
                    }

                    MapClassementPartiel[i]->addItem(ClassementStr);
                }
            }

            else
            {
                MapClassementPartiel[i]->clear();
                MapClassementFinal[i]->clear();
                MapClassementFinal[i]->setFont(QFont("consolas", 12));
                MapClassementFinal[i]->addItem(" ");

                for (int j = 0; j < m_wallo->getEpreuve()[i]->getResultatEpreuve().size(); j++)
                {

                    int point = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].Classement;
                    QString ClassementStr = QString::number(point) + ".";
                    QString Equip = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].NomEquipe;
                    ClassementStr.insert(6, Equip);
                    if (j < NbResTpsPos)
                    {

                        int min;
                        float sec;
                        min = m_wallo->getEpreuve()[i]->minutes2(m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes);
                        sec = m_wallo->getEpreuve()[i]->secondes2(m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes);
                        int seconde = floor(sec);
                        int centieme = (round(sec * 100)) - (seconde * 100);
                        ClassementStr.insert(35, QString::number(min).rightJustified(2, '0') + "'" + QString::number(seconde).rightJustified(2, '0') + "\"" + QString::number(centieme).rightJustified(2, '0'));
                    }
                    else
                    {
                        int min;
                        float sec;
                        min = m_wallo->getEpreuve()[i]->minutes2(-1 * (m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes));
                        sec = m_wallo->getEpreuve()[i]->secondes2(-1 * (m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes));
                        int seconde = floor(sec);
                        int centieme = (round(sec * 100)) - (seconde * 100);
                        ClassementStr.insert(34, "-" + QString::number(min).rightJustified(2, '0') + "'" + QString::number(seconde).rightJustified(2, '0') + "\"" + QString::number(centieme).rightJustified(2, '0'));
                    }

                    MapClassementFinal[i]->addItem(ClassementStr);
                }
            }
        }

        if (m_wallo->getEpreuve()[i]->getType() == 3)
        {

            valeurs.clear();
            valeursNiveau.clear();

            for (int j = 0; j < m_wallo->getEquipe().size(); j++)
            {
                if (MapTempsBrut[i][j]->text().isEmpty())
                {
                    valeurs.append(9999);
                }
                else
                {
                    valeurs.append(MapTempsBrut[i][j]->value());
                }

                if (MapNiveau[i][j]->text().isEmpty())
                {
                    valeursNiveau.append(-1);
                }
                else
                {
                    valeursNiveau.append(MapNiveau[i][j]->value());
                }
            }

            m_wallo->getEpreuve()[i]->setTempsBrut(valeurs);
            m_wallo->getEpreuve()[i]->setNiveau(valeursNiveau);

            QList<resultat> CurrentResultatTemps;
            QList<resultat> CurrentResultatNiveau;
            QList<resultat> CurrentResultat;
            CurrentResultatTemps.clear();
            CurrentResultatNiveau.clear();
            CurrentResultat.clear();
            for (int j = 0; j < m_wallo->getEquipe().size(); j++)
            {

                if (m_wallo->getEpreuve()[i]->getTempsBrut()[j] != 9999 || m_wallo->getEpreuve()[i]->getNiveau()[j] != -1)
                {
                    resultat temporaire;
                    int k;
                    k = m_wallo->getEpreuve()[i]->getOrdreDePassage()[j];
                    k = k - 1;
                    temporaire.EquipeID = m_wallo->getEquipe()[k]->getID();
                    temporaire.NomEquipe = m_wallo->getEquipe()[k]->getNomEquipe();
                    if (m_wallo->getEpreuve()[i]->getTempsBrut()[j] != 9999)
                    {
                        temporaire.TempsBrut = m_wallo->getEpreuve()[i]->getTempsBrut()[j];
                        temporaire.TempsTotalSecondes = m_wallo->getEpreuve()[i]->minutes(temporaire.TempsBrut) * 60 + m_wallo->getEpreuve()[i]->secondes(temporaire.TempsBrut);
                        CurrentResultatTemps.append(temporaire);
                    }
                    else
                    {
                        temporaire.Niveau = m_wallo->getEpreuve()[i]->getNiveau()[j];
                        CurrentResultatNiveau.append(temporaire);
                    }
                }
            }

            std::sort(CurrentResultatTemps.begin(), CurrentResultatTemps.end(), [](const resultat &a, const resultat &b)
                      { return a.TempsTotalSecondes < b.TempsTotalSecondes; });

            std::sort(CurrentResultatNiveau.begin(), CurrentResultatNiveau.end(), [](const resultat &a, const resultat &b)
                      { return a.Niveau > b.Niveau; });

            int NbResTps = CurrentResultatTemps.size();
            int NbResNiv = CurrentResultatNiveau.size();

            for (int j = 0; j < NbResTps; j++)
            {
                CurrentResultat.append(CurrentResultatTemps[j]);
            }

            for (int j = 0; j < NbResNiv; j++)
            {
                CurrentResultat.append(CurrentResultatNiveau[j]);
            }

            for (int j = 0; j < NbResTps; j++)
            {
                if (j == 0)
                {
                    CurrentResultat[j].Classement = 1;
                }
                else if (CurrentResultat[j].TempsTotalSecondes == CurrentResultat[j - 1].TempsTotalSecondes)
                {
                    CurrentResultat[j].Classement = CurrentResultat[j - 1].Classement;
                }
                else
                {
                    CurrentResultat[j].Classement = j + 1;
                }
            }

            for (int j = NbResTps; j < NbResTps + NbResNiv; j++)
            {
                if (j == NbResTps)
                {
                    CurrentResultat[j].Classement = CurrentResultat[j - 1].Classement + 1;
                }
                else if (CurrentResultat[j].Niveau == CurrentResultat[j - 1].Niveau)
                {
                    CurrentResultat[j].Classement = CurrentResultat[j - 1].Classement;
                }
                else
                {
                    CurrentResultat[j].Classement = j + 1;
                }
            }

            m_wallo->getEpreuve()[i]->setResultatEpreuveTempsouNiveau(CurrentResultat);

            for (int j = 0; j < CurrentResultat.size(); j++)
            {
                int k = CurrentResultat[j].EquipeID;
                k = k - 1;
                m_wallo->getEquipe()[k]->increaseTotalPoints(CurrentResultat[j].Classement);
                if (CurrentResultat[j].Classement == 1)
                {
                    m_wallo->getEquipe()[k]->increaseNombrePremierePlace();
                }

                if (CurrentResultat[j].Classement == 2)
                {
                    m_wallo->getEquipe()[k]->increaseNombreDeuxiemePlace();
                }
                if (CurrentResultat[j].Classement == 3)
                {
                    m_wallo->getEquipe()[k]->increaseNombreTroisiemePlace();
                }
            }

            if (m_wallo->getEpreuve()[i]->getResultatEpreuve().size() < m_wallo->getEquipe().size())
            {
                MapClassementPartiel[i]->clear();
                MapClassementPartiel[i]->setFont(QFont("consolas", 12));
                MapClassementPartiel[i]->addItem(" ");
                for (int j = 0; j < m_wallo->getEpreuve()[i]->getResultatEpreuve().size(); j++)
                {

                    int point = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].Classement;
                    QString ClassementStr = QString::number(point) + ".";
                    QString Equip = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].NomEquipe;
                    ClassementStr.insert(6, Equip);
                    if (j < NbResTps)
                    {

                        int min;
                        float sec;
                        min = m_wallo->getEpreuve()[i]->minutes2(m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes);
                        sec = m_wallo->getEpreuve()[i]->secondes2(m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes);
                        int seconde = floor(sec);
                        int centieme = (round(sec * 100)) - (seconde * 100);
                        ClassementStr.insert(35, QString::number(min).rightJustified(2, '0') + "'" + QString::number(seconde).rightJustified(2, '0') + "\"" + QString::number(centieme).rightJustified(2, '0'));
                    }
                    else
                    {
                        ClassementStr.insert(42, QString::number(m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].Niveau));
                    }

                    MapClassementPartiel[i]->addItem(ClassementStr);
                }
            }

            else
            {
                MapClassementPartiel[i]->clear();
                MapClassementFinal[i]->clear();
                MapClassementFinal[i]->setFont(QFont("consolas", 12));
                MapClassementFinal[i]->addItem(" ");

                for (int j = 0; j < m_wallo->getEpreuve()[i]->getResultatEpreuve().size(); j++)
                {

                    int point = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].Classement;
                    QString ClassementStr = QString::number(point) + ".";
                    QString Equip = m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].NomEquipe;
                    ClassementStr.insert(6, Equip);
                    if (j < NbResTps)
                    {

                        int min;
                        float sec;
                        min = m_wallo->getEpreuve()[i]->minutes2(m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes);
                        sec = m_wallo->getEpreuve()[i]->secondes2(m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].TempsTotalSecondes);
                        int seconde = floor(sec);
                        int centieme = (round(sec * 100)) - (seconde * 100);
                        ClassementStr.insert(35, QString::number(min).rightJustified(2, '0') + "'" + QString::number(seconde).rightJustified(2, '0') + "\"" + QString::number(centieme).rightJustified(2, '0'));
                    }
                    else
                    {
                        ClassementStr.insert(42, QString::number(m_wallo->getEpreuve()[i]->getResultatEpreuve()[j].Niveau));
                    }

                    MapClassementFinal[i]->addItem(ClassementStr);
                }
            }
        }
    }

    QList<CopyTeam> ListeEquipe;

    for (int i = 0; i < m_wallo->getEquipe().size(); i++)
    {
        CopyTeam temporaire;
        temporaire.EquipeID = m_wallo->getEquipe()[i]->getID();
        temporaire.NomEquipe = m_wallo->getEquipe()[i]->getNomEquipe();
        temporaire.TotalPoints = m_wallo->getEquipe()[i]->getTotalPoints();
        temporaire.nbrePremierePlace = m_wallo->getEquipe()[i]->getNbrePremierePlace();
        temporaire.nbreDeuxiemePlace = m_wallo->getEquipe()[i]->getNbreDeuxiemePlace();
        temporaire.nbreTroisiemePlace = m_wallo->getEquipe()[i]->getNbreTroisiemePlace();
        ListeEquipe.append(temporaire);
    }

    /*std::sort(ListeEquipe.begin(), ListeEquipe.end(), [](const CopyTeam& a, const CopyTeam& b) {
        return a.TotalPoints < b.TotalPoints;
    });*/

    std::sort(ListeEquipe.begin(), ListeEquipe.end(), [](const CopyTeam &a, const CopyTeam &b)
              {
                  // Premier critère : TotalPoints
                  if (a.TotalPoints != b.TotalPoints)
                  {
                      return a.TotalPoints < b.TotalPoints; // Tri croissant par TotalPoints
                  }

                  // Deuxième critère : NombrePremierePlace
                  if (a.nbrePremierePlace != b.nbrePremierePlace)
                  {
                      return a.nbrePremierePlace > b.nbrePremierePlace; // Tri décroissant
                  }

                  // Troisième critère : NombreDeuxiemePlace
                  if (a.nbreDeuxiemePlace != b.nbreDeuxiemePlace)
                  {
                      return a.nbreDeuxiemePlace > b.nbreDeuxiemePlace; // Tri décroissant
                  }

                  // Quatrième critère : NombreTroisiemePlace
                  if (a.nbreTroisiemePlace != b.nbreTroisiemePlace)
                  {
                      return a.nbreTroisiemePlace > b.nbreTroisiemePlace; // Tri décroissant
                  }

                  // Cinquième critère : Ordre alphabétique
                  return a.NomEquipe < b.NomEquipe; // Tri croissant
              });

    MapClassementFinal[m_wallo->getEpreuve().size()]->clear();
    MapClassementFinal[m_wallo->getEpreuve().size()]->addItem(" ");
    MapClassementFinal[m_wallo->getEpreuve().size()]->addItem(" ");
    int ranking = 1;
    for (int i = 0; i < ListeEquipe.size(); i++)
    {

        if (i == 0)
        {
            QString ClassementStr;
            ClassementStr.insert(47, QString::number(ranking) + ".");
            ClassementStr.insert(53, ListeEquipe[i].NomEquipe);
            ClassementStr.insert(82, QString::number(ListeEquipe[i].TotalPoints));
            MapClassementFinal[m_wallo->getEpreuve().size()]->addItem(ClassementStr);
        }
        else if (ListeEquipe[i].TotalPoints == ListeEquipe[i - 1].TotalPoints && ListeEquipe[i].nbrePremierePlace == ListeEquipe[i - 1].nbrePremierePlace && ListeEquipe[i].nbreDeuxiemePlace == ListeEquipe[i - 1].nbreDeuxiemePlace && ListeEquipe[i].nbreTroisiemePlace == ListeEquipe[i - 1].nbreTroisiemePlace)
        {
            QString ClassementStr;
            ClassementStr.insert(47, QString::number(ranking) + ".");
            ClassementStr.insert(53, ListeEquipe[i].NomEquipe);
            ClassementStr.insert(82, QString::number(ListeEquipe[i].TotalPoints));
            MapClassementFinal[m_wallo->getEpreuve().size()]->addItem(ClassementStr);
        }
        else
        {
            ranking = i + 1;
            QString ClassementStr;
            ClassementStr.insert(47, QString::number(ranking) + ".");
            ClassementStr.insert(53, ListeEquipe[i].NomEquipe);
            ClassementStr.insert(82, QString::number(ListeEquipe[i].TotalPoints));
            MapClassementFinal[m_wallo->getEpreuve().size()]->addItem(ClassementStr);
        }
    }

    emit updateResults();
}

void WindowEntrerResultat::resetCurrentTab()
{

    int k;
    k = this->getOnglets()->currentIndex();

    if (m_wallo->getEpreuve()[k]->getType() == 0)
    {
        for (int i = 0; i < m_wallo->getEquipe().size(); i++)
        {
            MapTempsBrut[k][i]->clear();
            MapPenalites[k][i]->clear();
        }
    }

    if (m_wallo->getEpreuve()[k]->getType() == 1)
    {
        for (int i = 0; i < m_wallo->getEquipe().size(); i++)
        {
            MapPoints[k][i]->clear();
        }
    }

    if (m_wallo->getEpreuve()[k]->getType() == 2)
    {
        for (int i = 0; i < m_wallo->getEquipe().size(); i++)
        {
            MapTempsBrut[k][i]->clear();
        }
    }

    if (m_wallo->getEpreuve()[k]->getType() == 3)
    {
        for (int i = 0; i < m_wallo->getEquipe().size(); i++)
        {
            MapTempsBrut[k][i]->clear();
            MapNiveau[k][i]->clear();
        }
    }
}

void WindowEntrerResultat::printCurrentTab()
{
    int k;
    k = this->getOnglets()->currentIndex();

    QPrinter printer;
    printer.setPageMargins(QMarginsF(0, 10, 0, 10)); // Remove printer margins

    QPrintDialog printDialog(&printer, this);

    if (printDialog.exec() == QDialog::Accepted)
    {
        if (k != m_wallo->getEpreuve().size())
        {
            QTextDocument doc;
            QString html;
            QString NomEpreuve = m_wallo->getEpreuve()[k]->getNomEpreuve();

            // Header
            html = "<html><head><title>" + NomEpreuve + "</title>";
            html += "<style>";
            html += "table { border-collapse: collapse; width: auto; display: inline-block; }";   // Table styling
            html += "th, td { border: 1px solid black; padding: 5px 10px; text-align: center; }"; // Cell styling
            html += "th { background-color: #f0f0f0; }";                                          // Header background color (optional)
            html += "</style>";
            html += "</head><body>";
            html += "<div style='text-align: center; margin-bottom: 20px;'><h1>" + NomEpreuve + "</h1></div>";
            html += "<br>";

            // Conteneur centré
            html += "<div style='text-align: center; width: 100%;'>";
            html += "<table>"; // Centrage optimisé

            // En-tête du tableau
            html += "<tr>";
            html += "<th>Classement</th>";
            html += "<th>Equipe</th>";

            if (m_wallo->getEpreuve()[k]->getType() == 0)
            {
                html += "<th>Temps</th>";
            }
            if (m_wallo->getEpreuve()[k]->getType() == 1)
            {
                html += "<th>Points</th>";
            }

            if (m_wallo->getEpreuve()[k]->getType() == 2)
            {
                html += "<th>Temps</th>";
            }

            if (m_wallo->getEpreuve()[k]->getType() == 3)
            {
                html += "<th>Temps / Niveau</th>";
            }

            html += "</tr>";

            // Corps du tableau
            for (int i = 1; i < m_wallo->getEpreuve()[k]->getResultatEpreuve().size() + 1; ++i)
            {
                // QString itemText = this->MapClassementFinal[k]->item(i)->text();
                QString itemText = this->getMapClassementFinal()[k]->item(i)->text(); // ui->listClassement->item(i)->text();
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
        else
        {
            QTextDocument doc;
            QString html;
            

            // Header
            html = "<html><head><title>Classement Général</title>";
            html += "<style>";
            html += "table { border-collapse: collapse; width: auto; display: inline-block; }";   // Table styling
            html += "th, td { border: 1px solid black; padding: 5px 10px; text-align: center; }"; // Cell styling
            html += "th { background-color: #f0f0f0; }";                                          // Header background color (optional)
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

            for (int i = 2; i < m_wallo->getEquipe().size()+2; i++)
            {
                // QString itemText = this->MapClassementFinal[k]->item(i)->text();
                QString itemText = this->getMapClassementFinal()[m_wallo->getEpreuve().size()]->item(i)->text(); // ui->listClassement->item(i)->text();
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
}

void WindowEntrerResultat::saveButtonClicked()
{
    m_main->on_actionEnregistrer_triggered();
}

void WindowEntrerResultat::openButtonClicked()
{
    m_main->on_actionOuvrir_triggered();
}
