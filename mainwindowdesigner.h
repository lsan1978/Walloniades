#ifndef MAINWINDOWDESIGNER_H
#define MAINWINDOWDESIGNER_H

#include <QMainWindow>
#include "W_EntrerEquipe.h"
#include "W_EntrerEpreuve.h"
#include "w_consultermodifierequipe.h"
#include "W_DefinirTirage.h"
#include "W_EntrerResultats.h"
#include "Walloniade.h"
#include "W_DefinirOrdreDePassage.h"
#include "W_DefinirTempsPenalite.h"



namespace Ui {
class MainWindowDesigner;
}

class MainWindowDesigner : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowDesigner(QWidget *parent = nullptr);
    ~MainWindowDesigner();
    static Walloniade *m_walloniade;
    void initListEquipe();
    void initListEpreuve();
    void initListClassementGeneral();
    void supprimerEquipeBis(QString NomEquipe);
    void supprimerEpreuveBis(QString NomEquipe);

public slots:
    void ouvrirWindowConsulterModifierEquipe(QListWidgetItem* item);
    void ouvrirWindowEntrerResultat(QListWidgetItem*);
    void ouvrirWindowEntrerEquipe();
    void ouvrirWindowEntrerEpreuve();
    void ajouterTirage(QList<QString> ListeNom,QList<int> ListeNumeros);
    void ajouterEquipe(Equipe * NewTeam);
    void ajouterEquipeDansListe(Equipe * NewTeam);
    void ajouterEpreuve(Epreuve * NewEpreuve);
    void ajouterEpreuveDansListe(Epreuve * NewEpreuve);
    void on_boutonAjouterEquipe_clicked();
    void on_boutonAjouterEpreuve_clicked();
    void on_actionEquipe_triggered();
    void on_actionEnregistrer_triggered();
    void on_actionDefinir_Tirage_au_Sort_triggered();
    void on_actionOuvrir_triggered();
    void on_actionQuitter_triggered();
    void on_boutonQuitter_clicked();
    void on_actionEpreuve_triggered();
    void on_actionImprimer_triggered();
    void ProvideContextMenu(const QPoint &);
    void ProvideContextMenuEpreuve(const QPoint &);
    void DefinirOrdreDePassage();
    void ouvrirWindowDefinirOrdreDePassage(QString NomEpreuve);
    void supprimerEquipeSelectionnee();
    void supprimerEpreuveSelectionnee();
    void DefinirTempsDePenalite();
    void ouvrirWindowDefinirTempsPenalite(QString NomEpreuve);
    //void PrintMainWindow();


private:
    Ui::MainWindowDesigner *ui;
    WindowEntrerEquipe *m_WEE;
    QStringListModel model;
    W_ConsulterModifierEquipe *WCME;
    int m_indice;
    QString m_nomEquipeSelectionee;
    QString m_nomEpreuveSelectionee;
    WindowEntrerEpreuve *m_WEEpreuve;
    WindowDefinirTirage *m_WDT;
    WindowEntrerResultat * m_WER;
    WindowDefinirOrdreDePassage * m_WDOP;
    WindowDefinirTempsPenalite * m_WDTP;
};

#endif // MAINWINDOWDESIGNER_H
