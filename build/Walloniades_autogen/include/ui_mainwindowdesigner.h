/********************************************************************************
** Form generated from reading UI file 'mainwindowdesigner.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWDESIGNER_H
#define UI_MAINWINDOWDESIGNER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowDesigner
{
public:
    QAction *actionQuitter;
    QAction *actionEquipe;
    QAction *actionEpreuve;
    QAction *actionDefinir_Tirage_au_Sort;
    QAction *actiondoubleClicItemListEquipe;
    QAction *actionOuvrir;
    QAction *actionEnregistrer;
    QAction *actionImprimer;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *boutonQuitter;
    QPushButton *boutonAjouterEpreuve;
    QLabel *labelClassement;
    QPushButton *boutonAjouterEquipe;
    QLabel *labelEpreuves;
    QListWidget *listEpreuves;
    QListWidget *listClassement;
    QListWidget *listEquipes;
    QLabel *labelEquipes;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QMenu *menuNouvelle;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindowDesigner)
    {
        if (MainWindowDesigner->objectName().isEmpty())
            MainWindowDesigner->setObjectName("MainWindowDesigner");
        MainWindowDesigner->resize(675, 462);
        actionQuitter = new QAction(MainWindowDesigner);
        actionQuitter->setObjectName("actionQuitter");
        actionEquipe = new QAction(MainWindowDesigner);
        actionEquipe->setObjectName("actionEquipe");
        actionEpreuve = new QAction(MainWindowDesigner);
        actionEpreuve->setObjectName("actionEpreuve");
        actionDefinir_Tirage_au_Sort = new QAction(MainWindowDesigner);
        actionDefinir_Tirage_au_Sort->setObjectName("actionDefinir_Tirage_au_Sort");
        actiondoubleClicItemListEquipe = new QAction(MainWindowDesigner);
        actiondoubleClicItemListEquipe->setObjectName("actiondoubleClicItemListEquipe");
        actionOuvrir = new QAction(MainWindowDesigner);
        actionOuvrir->setObjectName("actionOuvrir");
        actionEnregistrer = new QAction(MainWindowDesigner);
        actionEnregistrer->setObjectName("actionEnregistrer");
        actionImprimer = new QAction(MainWindowDesigner);
        actionImprimer->setObjectName("actionImprimer");
        centralwidget = new QWidget(MainWindowDesigner);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        boutonQuitter = new QPushButton(centralwidget);
        boutonQuitter->setObjectName("boutonQuitter");

        gridLayout->addWidget(boutonQuitter, 2, 2, 1, 1);

        boutonAjouterEpreuve = new QPushButton(centralwidget);
        boutonAjouterEpreuve->setObjectName("boutonAjouterEpreuve");

        gridLayout->addWidget(boutonAjouterEpreuve, 2, 1, 1, 1);

        labelClassement = new QLabel(centralwidget);
        labelClassement->setObjectName("labelClassement");
        labelClassement->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(labelClassement, 0, 2, 1, 1);

        boutonAjouterEquipe = new QPushButton(centralwidget);
        boutonAjouterEquipe->setObjectName("boutonAjouterEquipe");

        gridLayout->addWidget(boutonAjouterEquipe, 2, 0, 1, 1);

        labelEpreuves = new QLabel(centralwidget);
        labelEpreuves->setObjectName("labelEpreuves");
        labelEpreuves->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(labelEpreuves, 0, 1, 1, 1);

        listEpreuves = new QListWidget(centralwidget);
        listEpreuves->setObjectName("listEpreuves");

        gridLayout->addWidget(listEpreuves, 1, 1, 1, 1);

        listClassement = new QListWidget(centralwidget);
        listClassement->setObjectName("listClassement");

        gridLayout->addWidget(listClassement, 1, 2, 1, 1);

        listEquipes = new QListWidget(centralwidget);
        listEquipes->setObjectName("listEquipes");

        gridLayout->addWidget(listEquipes, 1, 0, 1, 1);

        labelEquipes = new QLabel(centralwidget);
        labelEquipes->setObjectName("labelEquipes");
        labelEquipes->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(labelEquipes, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindowDesigner->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindowDesigner);
        statusbar->setObjectName("statusbar");
        MainWindowDesigner->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindowDesigner);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 675, 26));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName("menuFichier");
        menuNouvelle = new QMenu(menuFichier);
        menuNouvelle->setObjectName("menuNouvelle");
        MainWindowDesigner->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindowDesigner);
        toolBar->setObjectName("toolBar");
        MainWindowDesigner->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menuBar->addAction(menuFichier->menuAction());
        menuFichier->addAction(actionOuvrir);
        menuFichier->addAction(actionEnregistrer);
        menuFichier->addAction(menuNouvelle->menuAction());
        menuFichier->addAction(actionDefinir_Tirage_au_Sort);
        menuFichier->addAction(actionQuitter);
        menuFichier->addAction(actionImprimer);
        menuNouvelle->addAction(actionEquipe);
        menuNouvelle->addAction(actionEpreuve);

        retranslateUi(MainWindowDesigner);

        QMetaObject::connectSlotsByName(MainWindowDesigner);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowDesigner)
    {
        MainWindowDesigner->setWindowTitle(QCoreApplication::translate("MainWindowDesigner", "Walloniades by Laurent Sancinito", nullptr));
        actionQuitter->setText(QCoreApplication::translate("MainWindowDesigner", "Quitter", nullptr));
        actionEquipe->setText(QCoreApplication::translate("MainWindowDesigner", "Equipe", nullptr));
        actionEpreuve->setText(QCoreApplication::translate("MainWindowDesigner", "Epreuve", nullptr));
        actionDefinir_Tirage_au_Sort->setText(QCoreApplication::translate("MainWindowDesigner", "D\303\251finir Tirage au Sort", nullptr));
        actiondoubleClicItemListEquipe->setText(QCoreApplication::translate("MainWindowDesigner", "doubleClicItemListEquipe", nullptr));
#if QT_CONFIG(tooltip)
        actiondoubleClicItemListEquipe->setToolTip(QCoreApplication::translate("MainWindowDesigner", "Ouvrir la fen\303\252tre de consultation/\303\251dition de l'\303\251quipe", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOuvrir->setText(QCoreApplication::translate("MainWindowDesigner", "Ouvrir", nullptr));
        actionEnregistrer->setText(QCoreApplication::translate("MainWindowDesigner", "Enregistrer", nullptr));
        actionImprimer->setText(QCoreApplication::translate("MainWindowDesigner", "Imprimer...", nullptr));
        boutonQuitter->setText(QCoreApplication::translate("MainWindowDesigner", "Quitter", nullptr));
        boutonAjouterEpreuve->setText(QCoreApplication::translate("MainWindowDesigner", "Nouvelle Epreuve", nullptr));
        labelClassement->setText(QCoreApplication::translate("MainWindowDesigner", "Classement", nullptr));
        boutonAjouterEquipe->setText(QCoreApplication::translate("MainWindowDesigner", "Nouvelle Equipe", nullptr));
        labelEpreuves->setText(QCoreApplication::translate("MainWindowDesigner", "Epreuves", nullptr));
        labelEquipes->setText(QCoreApplication::translate("MainWindowDesigner", "Equipes", nullptr));
        menuFichier->setTitle(QCoreApplication::translate("MainWindowDesigner", "Fichier", nullptr));
        menuNouvelle->setTitle(QCoreApplication::translate("MainWindowDesigner", "Nouvelle...", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindowDesigner", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowDesigner: public Ui_MainWindowDesigner {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWDESIGNER_H
