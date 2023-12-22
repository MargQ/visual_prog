#include "mainwindow.h"
#include <QApplication>

//int maxX=1000, maxY=1000;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
