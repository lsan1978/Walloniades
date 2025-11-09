#include "mainwindowdesigner.h"
#include <QApplication>
#include <QDebug>
#include <QIcon>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/fdwlogo.ico"));
    MainWindowDesigner w;
    w.show();
    return a.exec();
}
