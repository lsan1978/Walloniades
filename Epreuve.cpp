#include "Epreuve.h"
//#include "TempsResultEntry.h" // Add this include

Epreuve::Epreuve(QString Nom, int type)
{
    m_NomEpreuve=Nom;
    m_type = type;
    m_pageEntrerResultat = new QWidget;
    
}



Epreuve::~Epreuve()
{

}

void Epreuve::setOrdreDePassage(QList<int> nouvelOrdre)
{
    m_OrdreDePassage=nouvelOrdre;
}

void Epreuve::setTempsBrut(QList<double> nouveauTempsBrut)
{
    m_TempsBrut=nouveauTempsBrut;
}

void Epreuve::setTempsBrutPositif(QList<double> nouveauTempsBrutPositif)
{
    m_TempsBrutPositif=nouveauTempsBrutPositif;
}

void Epreuve::setTempsBrutNegatif(QList<double> nouveauTempsBrutNegatif)
{
    m_TempsBrutNegatif=nouveauTempsBrutNegatif;
}

void Epreuve::setPenalites(QList<int> nouveauPenalites)
{
    m_Penalites=nouveauPenalites;
}

void Epreuve::setPoints(QList<int> nouveauPoints)
{
    m_Points=nouveauPoints;
}

void Epreuve::setNiveau(QList<int> nouveauNiveau)
{
    m_Niveau=nouveauNiveau;

}

void Epreuve::setResultatEpreuveTemps(QVector<resultat> resultatEpreuve)
{
    m_ResultatEpreuve=resultatEpreuve;
}
    
void Epreuve::setResultatEpreuvePoints(QVector<resultat> resultatEpreuve)
{
    m_ResultatEpreuve=resultatEpreuve;
}
    
void Epreuve::setResultatEpreuvePosNeg(QVector<resultat> resultatEpreuve)
{
    m_ResultatEpreuve=resultatEpreuve;
}

void Epreuve::setResultatEpreuveTempsouNiveau(QVector<resultat> resultatEpreuve)
{
    m_ResultatEpreuve=resultatEpreuve;
}

void Epreuve::setPageEntrerResultat(QWidget *pageEntrerResultat)
{
    m_pageEntrerResultat = pageEntrerResultat;
}

void Epreuve::setNombreDeSecondeParPenalite(int nombre)
{
    m_NombreDeSecondeParPenalite=nombre;
}



QList<int> Epreuve::getOrdreDePassage()
{
    return m_OrdreDePassage;
}

QList<double> Epreuve::getTempsBrut()
{
    return m_TempsBrut;
}

QList<double> Epreuve::getTempsBrutPositif()
{
    return m_TempsBrutPositif;
}

QList<double> Epreuve::getTempsBrutNegatif()
{
    return m_TempsBrutNegatif;
}


QList<int> Epreuve::getPenalites()
{
    return m_Penalites;
}


QList<int> Epreuve::getNiveau()
{
    return m_Niveau;
}

QList<int> Epreuve::getPoints()
{
    return m_Points;
}

int Epreuve::getType()
{
    return m_type;
}

int Epreuve::getNombreDeSecondeParPenalite()
{
    return m_NombreDeSecondeParPenalite;
}

QList<resultat> Epreuve::getResultatEpreuve()
{
    return m_ResultatEpreuve;
}

QWidget *Epreuve::getPageEntrerResultat()
{
    return m_pageEntrerResultat;
}

QString Epreuve::getNomEpreuve()
{
    return m_NomEpreuve;
}

int Epreuve::minutes(float TpsBrut)
{
int m=0;
while (TpsBrut>=100)
{
    TpsBrut=TpsBrut-100;
    m++;
}
return m;
}

float Epreuve::secondes(float TpsBrut)
{
    float s=TpsBrut;
    while (s>=100)
    {
        s=s-100;
    }
    return s;
}

int Epreuve::minutes2(float Tpssecondes)
{
    int m=0;
    while (Tpssecondes>=60)
    {
        Tpssecondes=Tpssecondes-60;
        m++;
    }
    return m;

}

float Epreuve::secondes2(float Tpssecondes)
{
    float s=Tpssecondes;
    while (s>=60)
    {
        s=s-60;
    }
    return s;
}



/*ResultEntry* Epreuve::getResultEntry()
{
    return m_resultEntry;
}*/


