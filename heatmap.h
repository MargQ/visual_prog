#ifndef HEATMAP_H
#define HEATMAP_H

#include "mainwindow.h"
#include <iostream>
#include <QtWidgets>
#include <QPixmap>
#include <QPainter>
#include <time.h>
//int maxX=1000, maxY=1000;

//int onePixDistance = 100; //m
//int TxPower = 23;
//int antGain = 12;
//float freq=2.5;

int DrawPixel(QPainter* Pix, int x, int y);


class heatmap
{
public:
    int* N_of_obstructions(QPainter* Pix, QPixmap* Map, int *Number, int x0, int x1, int y0, int y1);
    void fill_field(QPainter* p, QPixmap* map,QImage* image, int cellPosX, int cellPosY, int onePixDistance, int TxPower, int antGain, float freq);
    void Pen_Color (QPainter* p,float sigPower);

};

#endif // HEATMAP_H
