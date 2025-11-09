#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "W_EntrerEquipe.h"

#include "Walloniade.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     static Walloniade *m_walloniade;


public slots:

    void ouvrirWindowEntrerEquipe();
    void ajouterEquipe(Equipe * NewTeam);

private:
    Ui::MainWindow *ui;
    QPushButton *m_boutonAjouterEquipe;

    WindowEntrerEquipe *m_WEE;

    //Walloniade *m_walloniade;




};
#endif // MAINWINDOW_H
