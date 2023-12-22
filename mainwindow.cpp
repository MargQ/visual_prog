#include "mainwindow.h"
#include "propagation_model.h"
#include "materials.h"
#include "obstacles.h"
#include "heatmap.h"
#include <QtWidgets>
#include <QPixmap>
#include <QPainter>
#include <time.h>
#include <math.h>
#include <QDebug>

int maxX=1000, maxY=1000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QGraphicsScene* scene = new QGraphicsScene();

//    int onePixDistance = 100; //m
//    int TxPower = 23;
//    int antGain = 12;
//    float freq=2.5;
    srand(time(NULL)); //установка точки доступа
    int cellPosX =rand()%599;
    int cellPosY=rand()%599;
    QPixmap map(maxX, maxY); // создаем карту для рисования
    QPainter p(&map);

    //obstacles mt;
    obstacles office1; //модель офиса1
    office1.doubleglass = true;
    office1.square(&p, 50, 200, 150, 300);

    obstacles wall; // бетонная стена
    wall.irrglass = true;
    wall.circle(&p, 500, 450, 80);

    obstacles fencing; // модель забора
    fencing.wood = true;
    fencing.line(&p, 200, 700, 150, 50);

    obstacles office2; //модель офиса2
    office2.concrete = true;
    office2.square(&p, 400, 500, 600, 700);

    QImage image = map.toImage();

    p.setPen(QColor(255, 255, 255, 255)); //точка доступа(белый цвет)
    p.drawPoint(cellPosX, cellPosY);

    p.end();
    scene->addPixmap(map);
    QGraphicsView* view = new QGraphicsView(scene);
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
}
