#ifndef EPREUVE_H
#define EPREUVE_H

#include <QList>
#include <QString>
#include <QMap>
#include <QtWidgets>
#include <QVector>
//#include "ResultEntry.h" //Add this include


typedef struct
{
    int EquipeID;
    QString NomEquipe;
    float TempsBrut;
	int nbrePenalites;
    int Niveau;
	float TempsTotalSecondes;
	int NombrePoints;
	float TempsBrutPositif;
	float TempsBrutnégatif;
    float TempsTotalSecondesPositif;
	float TempsTotalSecondesNegatif;
	int Classement;
	

} resultat;

class Epreuve
{
private:
    QString m_NomEpreuve;
    QList<int> m_OrdreDePassage;
    int m_type; // 0 = Temps, 1 = points, 2 = Temps Pos/Neg, 3 = Temps ou Niveau
    QList<resultat> m_ResultatEpreuve;
    QWidget *m_pageEntrerResultat;
    //ResultEntry *m_resultEntry; //Change QWidget to ResultEntry*
    QList<double> m_TempsBrut;
    QList<double> m_TempsBrutPositif;
    QList<double> m_TempsBrutNegatif;
    QList<int> m_Penalites;
    QList<int> m_Niveau;
    QList<int> m_Points;
    int m_NombreDeSecondeParPenalite;

public:
    Epreuve(QString Nom, int type); // Add a Walloniade pointer.
    ~Epreuve();
    QString getNomEpreuve();
    void setOrdreDePassage(QList<int> nouvelOrdre);
    void setTempsBrut(QList<double> nouveauTempsBrut);
    void setTempsBrutPositif(QList<double> nouveauTempsBrutPositif);
    void setTempsBrutNegatif(QList<double> nouveauTempsBrutNegatif);
    void setPenalites(QList<int> nouveauPenalites);
    void setNiveau(QList<int> nouveauNiveau);
    void setPoints(QList<int> nouveauPoints);
    void setNombreDeSecondeParPenalite(int nouveauNombreDeSecondeParPenalite);
    void setResultatEpreuveTemps(QVector<resultat> resultatEpreuve);
    void setResultatEpreuvePoints(QVector<resultat> resultatEpreuve);
    void setResultatEpreuvePosNeg(QVector<resultat> resultatEpreuve);
    void setResultatEpreuveTempsouNiveau(QVector<resultat> resultatEpreuve);
    void setPageEntrerResultat(QWidget *pageEntrerResultat);
    int minutes(float TpsBrut);
    float secondes(float TpsBrut);
    int minutes2(float Tpssecondes);
    float secondes2(float Tpssecondes);
    QList<int> getOrdreDePassage();
    QList<double> getTempsBrut();
    QList<double> getTempsBrutPositif();
    QList<double> getTempsBrutNegatif();
    QList<int> getPenalites();
    QList<int> getNiveau();
    QList<int> getPoints();
    QVector<resultat> getResultatEpreuve();
    QWidget *getPageEntrerResultat();
    int getType();
    int getNombreDeSecondeParPenalite();
    
    
    //ResultEntry* getResultEntry();

    

};

#endif // EPREUVE_H

