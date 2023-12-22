#include "mainwindow.h"

#include <QApplication>
const int maxX=1000;
const int maxY=1000;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.resize(maxX,maxY);
    w.show();
    return a.exec();
}
