#include "W_DefinirTirage.h"
#include "Walloniade.h"
#include <algorithm>
#include <QMessageBox>

WindowDefinirTirage::WindowDefinirTirage(QWidget *parent,Walloniade * Walloniade)
 {
     setWindowTitle("Tirage au sort...");
     setMinimumWidth(220);
     m_wallo=Walloniade;

     for (int i=0; i<m_wallo->getEquipe().size(); i++)
     {
         m_ListeNom.append(m_wallo->getEquipe()[i]->getNomEquipe());
     }
     m_ListeNom.sort();
     QFormLayout *layout = new QFormLayout;
     QVBoxLayout *layout3 = new QVBoxLayout;
     QHBoxLayout *layout2 = new QHBoxLayout;
     QPushButton *annuler = new QPushButton("Annuler");
     QPushButton *accepter = new QPushButton("Ok");
     layout2->addWidget(annuler);
     layout2->addWidget(accepter);

     for (int i=0; i<m_wallo->getEquipe().size(); i++)
     {
         QSpinBox *NouveauChamp = new QSpinBox();
         NouveauChamp->setButtonSymbols(QAbstractSpinBox::NoButtons);
         NouveauChamp->setAlignment(Qt::AlignRight);
         NouveauChamp->clear();
         m_listeChamps.append(NouveauChamp);

     }
     for (int i=0; i<m_wallo->getEquipe().size(); i++)
     {
       layout->addRow(m_ListeNom[i] +" : ",m_listeChamps[i]);
     }
     layout3->addLayout(layout);
     layout3->addLayout(layout2);
     this->setLayout(layout3);
     QObject::connect(annuler, SIGNAL(clicked()),this,SLOT(close()));
     QObject::connect(accepter, SIGNAL(clicked()),this,SLOT(acceptAndClose()));
     //QObject::connect(this, SIGNAL(TirageAcquired(QList<QString>,QList<int>)),parent, SLOT(ajouterTirage(QList<QString>,QList<int>)));
     //QObject::connect(this, SIGNAL(TirageAcquiredBis(int)),parent, SLOT(genererTableaux(int)));

 }

 void WindowDefinirTirage::acceptAndClose()
 {
     for (int i=0;i<m_ListeNom.size(); i++)
     {
         m_ListeNumeros.append(m_listeChamps[i]->value());
     }
     

     // Assign IDs to teams
    for (int i = 0; i < m_ListeNom.size(); ++i) {
    
        int k=0;
        while (k<m_wallo->getEquipe().size() && m_wallo->getEquipe()[k]->getNomEquipe() != m_ListeNom[i])
        {
            k++;
        }
        if (k == m_wallo->getEquipe().size())
        {
          QMessageBox::critical(this, "Error", QString("Team %1 not found!").arg(m_ListeNom[i]));
          return;
        }
        m_wallo->getEquipe()[k]->setID(m_ListeNumeros[i]);
    }
    
    

    // Sort m_equipes in Walloniade by ID
    // std::sort(m_wallo->getEquipe().begin(), m_wallo->getEquipe().end(), [](Equipe* a, Equipe* b) {
    //     return a->getID() < b->getID();
    // });

    int n = m_wallo->getEquipe().size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (m_wallo->getEquipe()[j]->getID() > m_wallo->getEquipe()[j + 1]->getID()) {
                // Swap pointers
                Equipe* temp = m_wallo->getEquipe()[j];
                m_wallo->getEquipe()[j] = m_wallo->getEquipe()[j + 1];
                m_wallo->getEquipe()[j + 1] = temp;
                swapped = true;
            }
        }
        // If no two elements were swapped in inner loop, the array is sorted
        if (swapped == false)
            break;
    }
    
    //for (int i = 0; i < m_wallo->getEquipe().size(); ++i) {
    //    QMessageBox::information(this, "Information", QString("Equipe %1 - ID : %2").arg(m_wallo->getEquipe()[i]->getNomEquipe()).arg(m_wallo->getEquipe()[i]->getID()));
    //}

    //QMessageBox::information(this, "Information", QString("This team list contains %1 items").arg(m_wallo->getEquipe()[0]->getNomEquipe()));


     emit TirageAcquired(m_ListeNom,m_ListeNumeros);
     emit TirageAcquiredBis(m_ListeNom.size());

     close();
 }
