//W_EntrerResultats.h
#ifndef W_ENTRERRESULTATS_H
#define W_ENTRERRESULTATS_H

#include <QWidget>
#include <QTabWidget>
#include "Walloniade.h"
#include "Equipe.h"
#include <QList>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QMap> // Added for QMap
#include <QListWidget> // Added for QListWidget

class MainWindowDesigner; // Forward declaration

class WindowEntrerResultat : public QWidget
{
    Q_OBJECT
public:
    WindowEntrerResultat(QWidget * parent, Walloniade * Walloniade);
    QTabWidget *getOnglets();
    QList<QDoubleSpinBox*> getListeChampsTemps();
    QMap<int, QListWidget*> getMapClassementFinal();
    void initialiserLayoutEpreuveTemps(QWidget *page, int j);
    void initialiserLayoutEpreuveTempsOuNiveau(QWidget *page, int j);
    void initialiserLayoutEpreuvePoints(QWidget *page, int j);
    void initialiserLayoutEpreuveTempsPosNeg(QWidget *page, int j);
    void initialiserLayoutClassementGeneral(QWidget *page, int j);
    

private slots:
   
    void resetCurrentTab();
    void printCurrentTab();
    void saveButtonClicked();
    void openButtonClicked();

public slots:

    void updateResultsButtonClicked();

signals:
    void updateResults();

public:
QMap<int, QList<QDoubleSpinBox*>> MapTempsBrut;
QMap<int, QList<QSpinBox*>> MapPenalites;
QMap<int, QList<QSpinBox*>> MapPoints;
QMap<int, QList<QSpinBox*>> MapNiveau;
QMap<int, QListWidget*> MapClassementPartiel;
QMap<int, QListWidget*> MapClassementFinal;

    
private:
    Walloniade *m_wallo;
    MainWindowDesigner *m_main;
    QTabWidget *onglets;
     QList<QDoubleSpinBox*> m_listeChampsTemps;
     QList<QSpinBox*> m_listeChampsPenalite;
     QList<QSpinBox*> m_listeChampsPoints;
     QList<QSpinBox*> m_listeChampsNiveau;
     

};

#endif

