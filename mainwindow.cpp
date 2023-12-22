#include "mainwindow.h"
#include <iostream>
#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtMath>
#include <stdio.h>

using namespace std;

//PathLose
float PL(float f, float d){
    return 28 + 22 * log10(f) + 20* log10(d);
}

double Glass(double freq){
    return (2 + 0.2*freq)/10;
}

double Glass_IRR(double freq){
    return (23 + 3.0 * freq)/10;
}
double Concrete(double freq){
    return (5 + 4.0 * freq)/10;
}
double Wood(double freq){
    return (4.85 + 0.12 * freq)/10;
}

// Функция для алгоритма Брезенхэма, определяющего количество препятствий
int countObstacles(int x1, int y1, int x2, int y2, QGraphicsScene* scene)
{
    int obstacles = 0;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (x1 != x2 || y1 != y2)
    {
        int currentX = x1;
        int currentY = y1;

        //пересекает ли луч препятствие
        if (scene->itemAt(currentX, currentY, QTransform()) != nullptr)
        {
            obstacles++;
        }

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
    return obstacles;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QGraphicsScene* scene = new QGraphicsScene();
    int maxX = 1000; //1000
    int maxY = 1000;
    int onePixDistance = 100; //[m]
    int TxPower = 23; // [dBm]
    int antGain = 12; // [dBi]
    float freq = 2.5; // [GHz]
    int cellPosX = 500;
    int cellPosY = 500;
    QPixmap map(maxX, maxY); // создаем карту для рисования
    QPainter p(&map);
    for(int i = 0; i < maxX; i++)
    {
        for(int j = 0; j < maxY; j++)
        {
            float distance = 0;
            distance = sqrt(pow(abs(cellPosX - i),2) + pow(abs(cellPosY - j),2)); // [pix]
            distance *= onePixDistance; // [meters]
            float sigPower = TxPower + antGain - PL(freq, distance);
            int x1 = cellPosX;
            int y1 = cellPosY;
            int x2 = i;
            int y2 = j;
            int n = n + countObstacles(x1, y1, x2, y2, scene);
            if(sigPower < -44 && sigPower >= -54)
            {
                p.setPen(QColor(255, 0, 0, 255)); // <-- задание цвета
            } else if  (sigPower < -54 && sigPower >= -64) {
                p.setPen(QColor(255, 123, 7, 255)); }// <-- задание цвета

              else if  (sigPower < -64 && sigPower >= -74) {
                    p.setPen(QColor(255, 173, 7, 255)); }// <-- задание цвета

              else if  (sigPower < -74 && sigPower >= -84) {
                    p.setPen(QColor(248, 255, 7, 255)); }// <-- задание цвета

              else if  (sigPower < -84 && sigPower >= -94) {
                    p.setPen(QColor(173, 255, 7, 255)); }// <-- задание цвета

              else if  (sigPower < -94 && sigPower >= -104) {
                    p.setPen(QColor(65, 255, 7, 255)); }// <-- задание цвета

              else if  (sigPower < -104 && sigPower >= -114) {
                    p.setPen(QColor(7, 255, 73, 255)); }// <-- задание цвета

              else if  (sigPower < -114 && sigPower >= -124) {
                    p.setPen(QColor(7, 255, 223, 255)); }// <-- задание цвета

              else if  (sigPower < -124 && sigPower >= -134) {
                    p.setPen(QColor(7, 115, 255, 255)); }// <-- задание цвета

              else if  (sigPower < -134 && sigPower >= -144) {
                    p.setPen(QColor(15, 7, 255, 255)); }// <-- задание цвета
            p.drawPoint(i, j);
        }
    }


   // cout<<"Количество препятствий =" <<countObstacles(x1, y1, x2, y2, scene);
    p.end();
    scene->addPixmap(map);
    QGraphicsView* view = new QGraphicsView(scene);
    setCentralWidget(view);


    view->show();

}

MainWindow::~MainWindow()
{
}
