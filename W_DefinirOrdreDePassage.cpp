#include "W_DefinirOrdreDePassage.h"
#include "Walloniade.h"
#include "Epreuve.h"
#include <algorithm>
#include <QMessageBox>
#include <QSet>
#include <QtWidgets>

#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QPageLayout>
#include <QPageSize>

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <QtGui/QPrinter>
#include <QtGui/QPrintDialog>
#include <QtGui/QPainter>
#include <QtGui/QTextDocument>
#include <QtGui/QAbstractTextDocumentLayout>
#endif

WindowDefinirOrdreDePassage::WindowDefinirOrdreDePassage(QWidget *parent, Walloniade *Walloniade, QString NomEpreuve)
{
    setWindowTitle("Définir ordre de passage...");
    setMinimumWidth(300);
    m_wallo = Walloniade;
    m_NomEpreuve = NomEpreuve;

    for (int i = 0; i < m_wallo->getEquipe().size(); i++)
    {
        m_ListeNom.append(m_wallo->getEquipe()[i]->getNomEquipe());
    }

    QGridLayout *mainLayout = new QGridLayout;
    QVBoxLayout *buttonLayout = new QVBoxLayout;

    // Epreuve Name Label
    QLabel *epreuveNameLabel = new QLabel(m_NomEpreuve);
    epreuveNameLabel->setAlignment(Qt::AlignCenter);
    QFont font = epreuveNameLabel->font();
    font.setPointSize(16); // Set a larger font size
    font.setBold(true);    // Make it bold
    epreuveNameLabel->setFont(font);
    mainLayout->addWidget(epreuveNameLabel, 0, 0, 1, 2); // Span across both columns

    QLabel *positionLabel = new QLabel("Passage en position :");
    QLabel *equipeLabel = new QLabel("Equipe Numéro :");

    mainLayout->addWidget(positionLabel, 1, 0); // Shifted down by one row
    mainLayout->addWidget(equipeLabel, 1, 1);   // Shifted down by one row

    QPushButton *annuler = new QPushButton("Annuler");
    QPushButton *accepter = new QPushButton("Ok");
    QPushButton *Aleatoire = new QPushButton("Aléatoire");
    QPushButton *imprimer = new QPushButton("Imprimer..."); // Print button

    // Add button to button layout
    buttonLayout->addWidget(Aleatoire);
    buttonLayout->addWidget(annuler);
    buttonLayout->addWidget(accepter);
    buttonLayout->addWidget(imprimer); // add the print button

    QObject::connect(Aleatoire, SIGNAL(clicked()), this, SLOT(setRandomOrder()));

    // Find the Epreuve
    int epreuveIndex = -1;
    for (int i = 0; i < m_wallo->getEpreuve().size(); ++i)
    {
        if (m_wallo->getEpreuve()[i]->getNomEpreuve() == m_NomEpreuve)
        {
            epreuveIndex = i;
            break;
        }
    }

    if (epreuveIndex == -1)
    {
        QMessageBox::critical(this, "Erreur", "Epreuve not found!");
        close();
        return;
    }

    // QObject::connect(imprimer, SIGNAL(clicked()), this, SLOT(printOrder(epreuveIndex))); // Connect print button
    QObject::connect(imprimer, &QPushButton::clicked, this, [this, epreuveIndex]()
                     { printOrder(epreuveIndex); });

    QList<int> currentOrder = m_wallo->getEpreuve()[epreuveIndex]->getOrdreDePassage();
    bool orderDefined = (currentOrder.size() == m_wallo->getEquipe().size());

    for (int i = 0; i < m_wallo->getEquipe().size(); i++)
    {
        QLabel *position = new QLabel(QString::number(i + 1));
        position->setAlignment(Qt::AlignCenter);

        QSpinBox *NouveauChamp = new QSpinBox();
        NouveauChamp->setButtonSymbols(QAbstractSpinBox::NoButtons);
        NouveauChamp->setAlignment(Qt::AlignRight);
        NouveauChamp->setMinimum(1);
        NouveauChamp->setMaximum(m_wallo->getEquipe().size());
        NouveauChamp->clear();
        if (m_wallo->getEpreuve()[epreuveIndex]->getType() == 1)
        {
            NouveauChamp->setValue(i + 1);
            // NouveauChamp->setEnabled(false);
        }

        m_listeChamps.append(NouveauChamp);

        mainLayout->addWidget(position, i + 2, 0);     // Shifted down by two rows
        mainLayout->addWidget(NouveauChamp, i + 2, 1); // Shifted down by two rows

        if (orderDefined)
        {
            NouveauChamp->setValue(currentOrder[i]);
        }
    }
    // add the button layout to the main layout
    mainLayout->addLayout(buttonLayout, m_wallo->getEquipe().size() + 2, 0, 1, 2); // Shifted down by two rows

    this->setLayout(mainLayout);
    QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(accepter, SIGNAL(clicked()), this, SLOT(acceptAndClose()));
}

void WindowDefinirOrdreDePassage::acceptAndClose()
{
    m_ListeNumeros.clear();
    // Check for duplicates (Qt 4.x compatible)
    QList<int> values;
    for (QSpinBox *spinBox : m_listeChamps)
    {
        values.append(spinBox->value());
    }

    // Alternative method for duplicate checking for Qt4
    QSet<int> uniqueValues;
    bool hasDuplicates = false;
    for (int value : values)
    {
        if (uniqueValues.contains(value))
        {
            hasDuplicates = true;
            break;
        }
        uniqueValues.insert(value);
    }

    if (hasDuplicates)
    {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer des valeurs uniques dans chaque champ \"Equipe Numéro\".");
        return;
    }

    for (int i = 0; i < m_listeChamps.size(); i++)
    {
        m_ListeNumeros.append(m_listeChamps[i]->value());
    }

    int j = 0;
    while (m_wallo->getEpreuve()[j]->getNomEpreuve() != m_NomEpreuve)
    {
        j++;
    }

    m_wallo->getEpreuve()[j]->setOrdreDePassage(m_ListeNumeros);

    close();
}

void WindowDefinirOrdreDePassage::setRandomOrder()
{
    QList<int> randomNumbers;
    for (int i = 1; i <= m_ListeNom.size(); ++i)
    {
        randomNumbers.append(i);
    }
    std::random_shuffle(randomNumbers.begin(), randomNumbers.end());
    for (int i = 0; i < m_listeChamps.size(); ++i)
    {
        m_listeChamps[i]->setValue(randomNumbers[i]);
        m_listeChamps[i]->setReadOnly(true);
        m_listeChamps[i]->setStyleSheet("QSpinBox { background-color: lightgray; }");
    }
}

int WindowDefinirOrdreDePassage::getEpreuveIndex() const
{
    for (int i = 0; i < m_wallo->getEpreuve().size(); ++i)
    {
        if (m_wallo->getEpreuve()[i]->getNomEpreuve() == m_NomEpreuve)
        {
            return i;
        }
    }
    return -1;
}

int WindowDefinirOrdreDePassage::getTeamIndexByNumero(int numero) const
{
    for (int i = 0; i < m_wallo->getEquipe().size(); ++i)
    {
        if (m_wallo->getEquipe()[i]->getID() == numero)
        {
            return i;
        }
    }
    // If no matching team is found, return -1
    return -1;
}

void WindowDefinirOrdreDePassage::printOrder(int m)
{

    QPrinter printer;
    printer.setPageMargins(QMarginsF(0, 5, 0, 5)); // Supprime les marges du printer

    QPrintDialog printDialog(&printer, this);

    if (printDialog.exec() == QDialog::Accepted)
    {

        if (m_wallo->getEpreuve()[m]->getType() == 0)
        {

            QTextDocument doc;
            QString html;

            // Header
            html += "<html><head><title>Ordre de Passage</title></head><body>";
            html += QString("<div style='text-align: center; margin-bottom: 20px;'><h1>Ordre de Passage - %1</h1></div>").arg(m_NomEpreuve);
            html += "<br>";
            // Conteneur centré
            html += "<div style='text-align: center; width: 100%;'>";
            html += "<table style='border-collapse: collapse; width: auto; display: inline-block; border: 1px solid black;'>"; // Centrage optimisé

            // En-tête du tableau
            html += "<tr style='height: 0.5cm;'>";
            html += "<th style='width: 20%; padding: 10px; text-align: center; border: 1px solid black;'>Position</th>";
            html += "<th style='width: 20%; padding: 10px; text-align: center; border: 1px solid black;'>Eq. Num.</th>";
            html += "<th style='width: 30%; padding: 10px; text-align: center; border: 1px solid black;'>Nom Equipe</th>";
            html += "<th style='width: 15%; padding: 10px; text-align: center; border: 1px solid black;'>Temps (min'sec''cent)</th>"; // New column header
            html += "<th style='width: 15%; padding: 10px; text-align: center; border: 1px solid black;'>Pénalité</th>";              // New column header
            html += "</tr>";

            // Corps du tableau
            bool orderDefined = m_wallo->getEpreuve()[getEpreuveIndex()]->getOrdreDePassage().size() == m_wallo->getEquipe().size();
            QList<int> order;
            if (orderDefined)
            {
                order = m_wallo->getEpreuve()[getEpreuveIndex()]->getOrdreDePassage();
            }

            for (int i = 0; i < m_listeChamps.size(); ++i)
            {
                html += "<tr style='height: 0.5cm;'>";
                html += QString("<td style='text-align: center; padding: 5px 10px; border: 1px solid black;'>%1</td>").arg(i + 1);

                if (orderDefined)
                {
                    html += QString("<td style='text-align: center; padding: 5px 10px; border: 1px solid black;'>%1</td>").arg(order[i]);
                    html += QString("<td style='text-align: center; padding: 5px 10px; border: 1px solid black;'>%1</td>").arg(m_wallo->getEquipe()[order[i] - 1]->getNomEquipe());
                }
                else
                {
                    html += QString("<td style='text-align: center; padding: 10px; border: 1px solid black;'>%1</td>").arg(m_listeChamps[i]->value());
                    int teamIndex = getTeamIndexByNumero(m_listeChamps[i]->value());
                    if (teamIndex != -1)
                    {
                        html += QString("<td style='text-align: center; padding: 10px; border: 1px solid black;'>%1</td>").arg(m_wallo->getEquipe()[teamIndex]->getNomEquipe());
                    }
                    else
                    {
                        html += "<td style='text-align: center; padding: 10px; border: 1px solid black;'>Error: Team not found.</td>";
                    }
                }
                html += "<td style='text-align: center; padding: 5px 10px; border: 1px solid black;'></td>"; // Empty "Temps" cell
                html += "<td style='text-align: center; padding: 5px 10px; border: 1px solid black;'></td>"; // Empty "Pénalité" cell
                html += "</tr>";
            }

            html += "</table></div>"; // Ferme le div
            html += "</body></html>";

            doc.setHtml(html);
            doc.setPageSize(printer.pageRect(QPrinter::Point).size()); // Empêche QTextDocument d'ajouter des marges cachées
            doc.print(&printer);
        }

        if (m_wallo->getEpreuve()[m]->getType() == 1)
        {
            QTextDocument doc;
            QString html;
            
            // Header (inchangé sauf suppression du <br>)
            html += "<html><head><title>Ordre de Passage</title></head>";
            html += "<body style='font-family: Arial; font-size: 10pt; margin:0; padding:0;'>";
            html += QString("<div style='text-align: center; margin-bottom: 10px;'><h1>Ordre de Passage - %1</h1></div>").arg(m_NomEpreuve);
            html += "<br>";

            // Tableau centré et étendu
            html += "<div style='text-align: center; width: 100%; margin:0; padding:0;'>";
            html += "<table style='border-collapse: collapse; width: 680px ; margin: 0 auto; border: 1px solid black;'>";
            
            // En-tête du tableau
            html += "<tr style='height: 0.4cm;'>";
            html += "<th style='padding: 3.5px; border: 1px solid black; width: 7%;'>Position</th>";
            html += "<th style='padding: 3.5px; border: 1px solid black; width: 25%;'>Nom Equipe</th>";
            for (int i = 1; i <= 10; ++i) {
                QString numero = "&nbsp;&nbsp;&nbsp;"+  QString::number(i)+"&nbsp;&nbsp;&nbsp;";
                html += QString("<th style='padding: 3.5px; border: 1px solid black; width: 6%;'>%1</th>").arg(numero);
            }
            html += "<th style='padding: 3.5px; border: 1px solid black; width : 8%;'>Total</th>";
            html += "</tr>";
            
            // Corps du tableau
            bool orderDefined = m_wallo->getEpreuve()[getEpreuveIndex()]->getOrdreDePassage().size() == m_wallo->getEquipe().size();
            QList<int> order;
            if (orderDefined) {
                order = m_wallo->getEpreuve()[getEpreuveIndex()]->getOrdreDePassage();
            }
            
            for (int i = 0; i < m_listeChamps.size(); ++i) {
                html += "<tr style='height: 0.4cm;'>";
                html += QString("<td style='text-align: center; padding: 3.5px; border: 1px solid black;'>%1</td>").arg(i + 1);
            
                QString nomEquipe;
                if (orderDefined) {
                    nomEquipe = m_wallo->getEquipe()[order[i] - 1]->getNomEquipe();
                } else {
                    int teamIndex = getTeamIndexByNumero(m_listeChamps[i]->value());
                    nomEquipe = (teamIndex != -1) ? m_wallo->getEquipe()[teamIndex]->getNomEquipe() : "Error: Team not found.";
                }
                html += QString("<td style='text-align: left; padding: 3.5px; border: 1px solid black;'>%1</td>").arg(nomEquipe);
            
                for (int j = 0; j < 10; ++j) {
                    html += "<td style='padding: 3.5px; border: 1px solid black;'></td>";
                }
                html += "<td style='padding: 3.5px; border: 1px solid black;'></td>"; // Colonne Total
                html += "</tr>";
            }
            
            html += "</table></div>"; // Fin tableau
            html += "</body></html>";
            
            printer.setPageSize(QPageSize(QPageSize::A4));
            printer.setPageOrientation(QPageLayout::Landscape);
            doc.setHtml(html);
            doc.setPageSize(printer.pageRect(QPrinter::Point).size());
            doc.print(&printer);
            
        }

        if (m_wallo->getEpreuve()[m]->getType() == 2)
        {

            QTextDocument doc;
            QString html;

            // Header
            html += "<html><head><title>Ordre de Passage</title></head><body>";
            html += QString("<div style='text-align: center; margin-bottom: 20px;'><h1>Ordre de Passage - %1</h1></div>").arg(m_NomEpreuve);
            html += "<br>";
            // Conteneur centré
            html += "<div style='text-align: center; width: 100%;'>";
            html += "<table style='border-collapse: collapse; width: auto; display: inline-block; border: 1px solid black;'>"; // Centrage optimisé

            // En-tête du tableau
            html += "<tr style='height: 0.5cm;'>";
            html += "<th style='width: 20%; padding: 10px; text-align: center; border: 1px solid black;'>Position</th>";
            html += "<th style='width: 20%; padding: 10px; text-align: center; border: 1px solid black;'>Eq. Num.</th>";
            html += "<th style='width: 30%; padding: 10px; text-align: center; border: 1px solid black;'>Nom Equipe</th>";
            html += "<th style='width: 15%; padding: 10px; text-align: center; border: 1px solid black;'>Vainqueur (Tps +)</th>"; // New column header
            html += "<th style='width: 15%; padding: 10px; text-align: center; border: 1px solid black;'>Perdant (Tps -)</th>";   // New column header
            html += "</tr>";

            // Corps du tableau
            bool orderDefined = m_wallo->getEpreuve()[getEpreuveIndex()]->getOrdreDePassage().size() == m_wallo->getEquipe().size();
            QList<int> order;
            if (orderDefined)
            {
                order = m_wallo->getEpreuve()[getEpreuveIndex()]->getOrdreDePassage();
            }

            for (int i = 0; i < m_listeChamps.size(); ++i)
            {
                html += "<tr style='height: 0.5cm;'>";
                html += QString("<td style='text-align: center; padding: 5px 10px; border: 1px solid black;'>%1</td>").arg(i + 1);

                if (orderDefined)
                {
                    html += QString("<td style='text-align: center; padding: 5px 10px; border: 1px solid black;'>%1</td>").arg(order[i]);
                    html += QString("<td style='text-align: center; padding: 5px 10px; border: 1px solid black;'>%1</td>").arg(m_wallo->getEquipe()[order[i] - 1]->getNomEquipe());
                }
                else
                {
                    html += QString("<td style='text-align: center; padding: 10px; border: 1px solid black;'>%1</td>").arg(m_listeChamps[i]->value());
                    int teamIndex = getTeamIndexByNumero(m_listeChamps[i]->value());
                    if (teamIndex != -1)
                    {
                        html += QString("<td style='text-align: center; padding: 10px; border: 1px solid black;'>%1</td>").arg(m_wallo->getEquipe()[teamIndex]->getNomEquipe());
                    }
                    else
                    {
                        html += "<td style='text-align: center; padding: 10px; border: 1px solid black;'>Error: Team not found.</td>";
                    }
                }
                html += "<td style='text-align: center; padding: 5px 10px; border: 1px solid black;'></td>"; // Empty "Temps" cell
                html += "<td style='text-align: center; padding: 5px 10px; border: 1px solid black;'></td>"; // Empty "Pénalité" cell
                html += "</tr>";
            }

            html += "</table></div>"; // Ferme le div
            html += "</body></html>";

            doc.setHtml(html);
            doc.setPageSize(printer.pageRect(QPrinter::Point).size()); // Empêche QTextDocument d'ajouter des marges cachées
            doc.print(&printer);
        }

        if (m_wallo->getEpreuve()[m]->getType() == 3)
        {

            QTextDocument doc;
            QString html;

            // Header
            html += "<html><head><title>Ordre de Passage</title></head><body>";
            html += QString("<div style='text-align: center; margin-bottom: 20px;'><h1>Ordre de Passage - %1</h1></div>").arg(m_NomEpreuve);
            html += "<br>";
            // Conteneur centré
            html += "<div style='text-align: center; width: 100%;'>";
            html += "<table style='border-collapse: collapse; width: auto; display: inline-block; border: 1px solid black;'>"; // Centrage optimisé

            // En-tête du tableau
            html += "<tr style='height: 0.5cm;'>";
            html += "<th style='width: 20%; padding: 10px; text-align: center; border: 1px solid black;'>Position</th>";
            html += "<th style='width: 20%; padding: 10px; text-align: center; border: 1px solid black;'>Eq. Num.</th>";
            html += "<th style='width: 30%; padding: 10px; text-align: center; border: 1px solid black;'>Nom Equipe</th>";
            html += "<th style='width: 15%; padding: 10px; text-align: center; border: 1px solid black;'>Temps (min'sec''cent)</th>"; // New column header
            html += "<th style='width: 15%; padding: 10px; text-align: center; border: 1px solid black;'>Niveau (0-4)</th>";          // New column header
            html += "</tr>";

            // Corps du tableau
            bool orderDefined = m_wallo->getEpreuve()[getEpreuveIndex()]->getOrdreDePassage().size() == m_wallo->getEquipe().size();
            QList<int> order;
            if (orderDefined)
            {
                order = m_wallo->getEpreuve()[getEpreuveIndex()]->getOrdreDePassage();
            }

            for (int i = 0; i < m_listeChamps.size(); ++i)
            {
                html += "<tr style='height: 0.5cm;'>";
                html += QString("<td style='text-align: center; padding: 5px 10px; border: 1px solid black;'>%1</td>").arg(i + 1);

                if (orderDefined)
                {
                    html += QString("<td style='text-align: center; padding: 5px 10px; border: 1px solid black;'>%1</td>").arg(order[i]);
                    html += QString("<td style='text-align: center; padding: 5px 10px; border: 1px solid black;'>%1</td>").arg(m_wallo->getEquipe()[order[i] - 1]->getNomEquipe());
                }
                else
                {
                    html += QString("<td style='text-align: center; padding: 10px; border: 1px solid black;'>%1</td>").arg(m_listeChamps[i]->value());
                    int teamIndex = getTeamIndexByNumero(m_listeChamps[i]->value());
                    if (teamIndex != -1)
                    {
                        html += QString("<td style='text-align: center; padding: 10px; border: 1px solid black;'>%1</td>").arg(m_wallo->getEquipe()[teamIndex]->getNomEquipe());
                    }
                    else
                    {
                        html += "<td style='text-align: center; padding: 10px; border: 1px solid black;'>Error: Team not found.</td>";
                    }
                }
                html += "<td style='text-align: center; padding: 5px 10px; border: 1px solid black;'></td>"; // Empty "Temps" cell
                html += "<td style='text-align: center; padding: 5px 10px; border: 1px solid black;'></td>"; // Empty "Pénalité" cell
                html += "</tr>";
            }

            html += "</table></div>"; // Ferme le div
            html += "</body></html>";

            doc.setHtml(html);
            doc.setPageSize(printer.pageRect(QPrinter::Point).size()); // Empêche QTextDocument d'ajouter des marges cachées
            doc.print(&printer);
        }
    }
}
