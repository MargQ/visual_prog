#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "mainwindow.h"
#include <iostream>
#include <QtWidgets>
#include <QPixmap>
#include <QPainter>
#include <time.h>
#include <math.h>

class material
{
public:
    bool wood; //дерево
    bool concrete; //бетон
    bool irrglass; //IRR стекло
    bool doubleglass; //стеклопакет
};

class obstacles: public material
{
public: void line(QPainter* Pix, int x0, int x1, int y0, int y1);
        void square(QPainter* Pix, int x0, int x1, int y0, int y1);
        void circle(QPainter* Pix, int X1, int Y1, int R);
};


#endif // OBSTACLES_H
