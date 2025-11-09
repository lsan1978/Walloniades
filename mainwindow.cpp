#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "W_EntrerEquipe.h"
#include "Equipe.h"
#include "Capitaine.h"
#include "Walloniade.h"
#include <QtWidgets>
#include <QDebug>
Walloniade * MainWindow::m_walloniade=NULL;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    m_walloniade = new Walloniade();
    m_WEE=NULL;


    //Menu

    //menuBar()->setNativeMenuBar(false);
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QAction *actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitter);
    actionQuitter->setIcon(QIcon("../Walloniades/quitter.png"));
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));

    //Barre d'outils

    QToolBar *toolBarFichier = addToolBar("Fichier");
    toolBarFichier->addAction(actionQuitter);
    toolBarFichier->addSeparator();

    //boutons

    m_boutonAjouterEquipe = new QPushButton("Ajouter Equipe", this);
    m_boutonAjouterEquipe->move(0,100);

    //connects

    QObject::connect(m_boutonAjouterEquipe, SIGNAL(clicked()), this, SLOT(ouvrirWindowEntrerEquipe()));
    QObject::connect(actionQuitter, SIGNAL(triggered()),this,SLOT(close()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ouvrirWindowEntrerEquipe()
{
    m_WEE = new WindowEntrerEquipe(this);
    m_WEE->show();
}





void MainWindow::ajouterEquipe(Equipe *NewTeam)
{
    m_walloniade->ajouterEquipe(NewTeam);
}

