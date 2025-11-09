#include <C:\C++\Walloniades\Walloniade.h>
#include <QDebug>

Walloniade::Walloniade()
{

    m_epreuves.append(NULL);
    m_equipes.append(NULL);
}


Walloniade::~Walloniade()
{

}

void Walloniade::ajouterEquipe(Equipe * newTeam)
{
  if (m_equipes.isEmpty())
  {
      m_equipes.append(newTeam);
  }
  else
  {
  if(m_equipes[0]==NULL)
  {
      m_equipes[0]=newTeam;
  }
  else
  {
      m_equipes.append(newTeam);
  }
  }
}

void Walloniade::ajouterEpreuve(Epreuve * newEpreuve)
{
  if (m_epreuves.isEmpty())
  {
      m_epreuves.append(newEpreuve);
  }
  else
  {
  if(m_epreuves[0]==NULL)
  {
      m_epreuves[0]=newEpreuve;
  }
  else
  {
      m_epreuves.append(newEpreuve);
  }
  }
}

QList<Equipe *>& Walloniade::getEquipe()
{
return m_equipes;
}

QList<Epreuve *>& Walloniade::getEpreuve()
{
return m_epreuves;
}

void Walloniade::supprimerEquipe(int i)
{
    m_equipes[i]->supprimerCapitaine();
    int indiceDeFin=m_equipes[i]->getListeParticipants().size();
    for (int j=0; j<indiceDeFin; j++)
    {
        m_equipes[i]->supprimerParticipant(indiceDeFin-j-1);
    }

    delete this->m_equipes[i];
    m_equipes.removeAt(i);

}

void Walloniade::supprimerEquipe(QString NomEquipe)
{
    int i=0;
    while (m_equipes[i]->getNomEquipe()!=NomEquipe)
    {
        i++;
    }

    m_equipes[i]->supprimerCapitaine();
    int indiceDeFin=m_equipes[i]->getListeParticipants().size();
    for (int j=0; j<indiceDeFin; j++)
    {
        m_equipes[i]->supprimerParticipant(indiceDeFin-j-1);
    }

    delete this->m_equipes[i];
    m_equipes.removeAt(i);

}

void Walloniade::supprimerEpreuve(QString NomEpreuve)
{
    int i=0;
    while (m_epreuves[i]->getNomEpreuve()!=NomEpreuve)
    {
        i++;
    }



    delete this->m_epreuves[i];
    m_epreuves.removeAt(i);

}
