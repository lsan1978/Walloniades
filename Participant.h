#ifndef PARTICIPANT_H
#define PARTICIPANT_H
#include <QString>
#include <QObject>

class Participant : public QObject
{
Q_GADGET
public:
    Participant(QString const& nom, QString const& prenom, int age, QChar sexe);
    ~Participant();
    QString getNomParticipant();
    QString getPrenomParticipant();
    int getAgeParticipant();
    QChar getSexeParticipant();
protected:

    QString m_nom;
    QString m_prenom;
    int m_age;
    QChar m_sexe;
};

#endif // PARTICIPANT_H
