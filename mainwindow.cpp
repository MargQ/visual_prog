#include "mainwindow.h"
#include <QtWidgets>
#include <QPixmap>
#include <QPainter>
#include <time.h>
#include <math.h>
#include <QDebug>

int maxX=1000, maxY=1000;

float PL(float f, float d){
    return 28 + 22 * log10(d) + 20*log10(f);
}
float delay(int N, float f) { //N-номер места в массиве за определённый материал
    if (N == 3) {
        return 23+0.3*f;
    }
    if (N == 2) {
        return 2+0.2*f;
    }
    if (N == 0) {
        return 5+4*f;
    }
    if (N == 1) {
        return 4.85+0.12*f;
    }
    else {
        return 0;
    }
}
int DrawPixel(QPainter* Pix, int x, int y) {
    Pix->drawPoint(x + 1, y + 1);
    Pix->drawPoint(x + 1, y - 1);
    Pix->drawPoint(x - 1, y + 1);
    Pix->drawPoint(x - 1, y - 1);
    Pix->drawPoint(x, y);
    Pix->drawPoint(x, y - 1);
    Pix->drawPoint(x, y + 1);
    Pix->drawPoint(x - 1, y);
    Pix->drawPoint(x + 1, y);
    return 0;
}
int* N_of_obstructions(QPainter* Pix, QPixmap* Map, int *Number, int x0, int x1, int y0, int y1) {
    Q_UNUSED( Pix )
    QImage image = Map->toImage();
    int deltax = abs(x1 - x0);
    int deltay = abs(y1 - y0);
    int signx = x0 < x1 ? 1 : -1;
    int signy = y0 < y1 ? 1 : -1;
    int error = deltax - deltay;

    int Xless=-50;
    int Yless=-50;

    QRgb color1=image.pixel(x1, y1);
    int red1 = qRed(color1);
    int green1 = qGreen(color1);
    int blue1 = qBlue(color1);
    if (red1==34 && green1==34 && blue1==34) { // бетон
        Number[0]+=1;
        Xless=x1;
        Yless=y1;
    }
    if (red1==161 && green1==104 && blue1==7) { // дерево
        Number[1]+=1;
        Xless=x1;
        Yless=y1;
    }
    if (red1==77 && green1==101 && blue1==110) { // IRR стекло
        Number[2]+=1;
        Xless=x1;
        Yless=y1;
    }
    if (red1==190 && green1==208 && blue1==215) { // стеклопакет
        Number[3]+=1;
        Xless=x1;
        Yless=y1;
    }
    while (x0 != x1 || y0 != y1) {

        QRgb color2=image.pixel(x0, y0);
        int red2 = qRed(color2);
        int green2 = qGreen(color2);
        int blue2 = qBlue(color2);

        if (red2==34 && green2==34 && blue2==34) { // бетон
            if ((Xless==-50) && (Yless==-50)) {
                Number[0]+=1;
                Xless=x0;
                Yless=y0;
            }
            if (((x0-1==Xless) || (x0+1==Xless) || (x0==Xless)) && ((y0==Yless) || (y0-1==Yless) || (y0+1==Yless))) {
            Xless=x0;
            Yless=y0;
            }
            else {
            Number[0]+=1;
            }
        }
        if (red2==161 && green2==104 && blue2==7) { // дерево
            if ((Xless==-50) && (Yless==-50)) {
            Number[1]+=1;
            Xless=x0;
            Yless=y0;
            }
            if (((x0-1==Xless) || (x0+1==Xless) || (x0==Xless)) && ((y0==Yless) || (y0-1==Yless) || (y0+1==Yless))) {
            Xless=x0;
            Yless=y0;
            }
            else {
            Number[1]+=1;
            }
        }
        if (red2==77 && green2==101 && blue2==110) { // IRR стекло
            if ((Xless==-50) && (Yless==-50)) {
            Number[2]+=1;
            Xless=x0;
            Yless=y0;
            }
            if (((x0-1==Xless) || (x0+1==Xless) || (x0==Xless)) && ((y0==Yless) || (y0-1==Yless) || (y0+1==Yless))) {
            Xless=x0;
            Yless=y0;
            }
            else {
            Number[2]+=1;
            }
        }
        if (red2==190 && green2==208 && blue2==215) { // стеклопакет
            if ((Xless==-50) && (Yless==-50)) {
            Number[3]+=1;
            Xless=x0;
            Yless=y0;
            }
            if (((x0-1==Xless) || (x0+1==Xless) || (x0==Xless)) && ((y0==Yless) || (y0-1==Yless) || (y0+1==Yless))) {
            Xless=x0;
            Yless=y0;
            }
            else {
            Number[3]+=1;
            }
        }

        int error2 = error*2;
        if (error2 > -deltay) {
            error -= deltay;
            x0 += signx;
        }
        if (error2 < deltax) {
            error += deltax;
            y0 += signy;
        }
    }
    return Number;
}
struct Obstruction { //препятствия
    bool irrgrass; //IRR стекло
    bool doublegrass; //стеклопакет
    bool concrete; //бетон
    bool wood; //дерево
    int line(QPainter* Pix, int x0, int x1, int y0, int y1) {
        int deltax = abs(x1 - x0);
        int deltay = abs(y1 - y0);
        int signx = x0 < x1 ? 1 : -1;
        int signy = y0 < y1 ? 1 : -1;
        int error = deltax - deltay;
        if (concrete == true) {
            Pix->setPen(QColor(34, 34, 34, 255));
        }
        if (wood == true) {
            Pix->setPen(QColor(161, 104, 7, 255));
        }
        if (doublegrass == true) {
            Pix->setPen(QColor(77, 101, 110, 255));
        }
        if (irrgrass == true) {
            Pix->setPen(QColor(190, 208, 215, 255));
        }
        DrawPixel(Pix, x1, y1);
        while (x0 != x1 || y0 != y1) {
            DrawPixel(Pix, x0, y0);
            int error2 = error*2;
            if (error2 > -deltay) {
                error -= deltay;
                x0 += signx;
            }
            if (error2 < deltax) {
                error += deltax;
                y0 += signy;
            }
        }
        return 0;
    }
    int circle(QPainter* Pix, int X1, int Y1, int R) {
        int x = 0;
        int y = R;
        int delta = 1 - 2 * R;
        int error = 0;
        if (concrete == true) {
            Pix->setPen(QColor(34, 34, 34, 255));
        }
        if (wood == true) {
            Pix->setPen(QColor(161, 104, 7, 255));
        }
        if (doublegrass == true) {
            Pix->setPen(QColor(77, 101, 110, 255));
        }
        if (irrgrass == true) {
            Pix->setPen(QColor(190, 208, 215, 255));
        }
        while (y >= x) {
            DrawPixel(Pix, X1 + x, Y1 + y);
            DrawPixel(Pix, X1 + x, Y1 - y);
            DrawPixel(Pix, X1 - x, Y1 + y);
            DrawPixel(Pix, X1 - x, Y1 - y);
            DrawPixel(Pix, X1 + y, Y1 + x);
            DrawPixel(Pix, X1 + y, Y1 - x);
            DrawPixel(Pix, X1 - y, Y1 + x);
            DrawPixel(Pix, X1 - y, Y1 - x);
            error = 2 * (delta + y) - 1;
            if ((delta < 0) && (error <= 0)) {
                delta += 2 * ++x + 1;
                continue;
            }
            if ((delta > 0) && (error > 0)) {
                delta -= 2 * --y + 1;
                continue;
            }
            delta += 2 * (++x - --y);
        }
        return 0;
    }
    int square(QPainter* Pix, int x0, int x1, int y0, int y1) {
        if (concrete == true) {
            Pix->setPen(QColor(34, 34, 34, 255));
        }
        if (wood == true) {
            Pix->setPen(QColor(161, 104, 7, 255));
        }
        if (doublegrass == true) {
            Pix->setPen(QColor(77, 101, 110, 255));
        }
        if (irrgrass == true) {
            Pix->setPen(QColor(190, 208, 215, 255));
        }
        if (x0<x1) {
            for (int x=x0; x<x1; x++) {
                DrawPixel(Pix, x, y0);
                DrawPixel(Pix, x, y1);
            }
        }
        if (x1<x0) {
            for (int x=x1; x<x0; x++) {
                DrawPixel(Pix, x, y0);
                DrawPixel(Pix, x, y1);
            }
        }
        if (y0<y1) {
            for (int y=y0; y<y1; y++) {
                DrawPixel(Pix, x0, y);
                DrawPixel(Pix, x1, y);
            }
        }
        if (y1<y0) {
            for (int y=y1; y<y0; y++) {
                DrawPixel(Pix, x0, y);
                DrawPixel(Pix, x1, y);
            }
        }
        return 0;
    }
};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QGraphicsScene* scene = new QGraphicsScene();

    int onePixDistance = 100; //m
    int TxPower = 23;
    int antGain = 12;
    float freq=2.5;
    srand(time(NULL)); //установка точки доступа
    int cellPosX =rand()%599;
    int cellPosY=rand()%599;
    QPixmap map(maxX, maxY); // создаем карту для рисования
    QPainter p(&map);

    struct Obstruction office1; //модель офиса1
    office1.doublegrass = true;
    office1.square(&p, 50, 200, 150, 300);

    struct Obstruction wall; // бетонная стена
    wall.concrete = true;
    wall.circle(&p, 500, 450, 80);

    struct Obstruction fencing; // модель забора
    fencing.wood = true;
    fencing.line(&p, 200, 700, 150, 50);

    struct Obstruction office2; //модель офиса2
    office2.irrgrass = true;
    office2.square(&p, 400, 500, 600, 700);

    QImage image = map.toImage();

    for(int i = 0; i < maxX; i++){
        for(int j = 0; j < maxY; j++){
            float distance = 0;
            distance =sqrt (pow(abs(cellPosX - i), 2) + pow(abs(cellPosY-j), 2));
            distance *= onePixDistance;
            float sigPower = TxPower + antGain - PL(freq, distance);
            int NumObs[4]{}; //пустой массив препятствий
            N_of_obstructions(&p, &map, NumObs, cellPosX, i, cellPosY, j); //заполнение массива
            if (NumObs[0] > 0 || NumObs[1] > 0 || NumObs[2] > 0 || NumObs[3] > 0) {
                //затухание
                sigPower=sigPower-NumObs[0]*delay(0, freq)-NumObs[1]*delay(1, freq)-NumObs[2]*delay(2, freq)-NumObs[3]*delay(3, freq);
            }
            if(sigPower < -44 && sigPower >= -54)
            {
                p.setPen(QColor(255, 0, 0, 255)); // <-- задание цвета
            }
            else if (sigPower > -84 ) {
                p.setPen(QColor(255,((sigPower+44)*(-1.0)*6.375), 0)); // <-- задание цвета
            }

            else if (sigPower > -104 ) {
                p.setPen(QColor((255+((sigPower+84)*12.75)), 255,0)); // <-- задание цвета
            }
            else if (sigPower > -124 ) {
                p.setPen(QColor(0, 255, ((sigPower+104)*(-1.0)*12.75))); // <-- задание цвета
            }
            else if (sigPower > -144 ) {
                p.setPen(QColor(0, 255+((sigPower+124)*12.75), 255)); // <-- задание цвета
            }

            QRgb color=image.pixel(i, j); //оставляем нарисованные препятствия
            int red = qRed(color);
            int green = qGreen(color);
            int blue = qBlue(color);
            if (red==34 && green==34 && blue==34) {
                p.setPen(QColor(34, 34, 34, 255));
            }
            if (red==161 && green==104 && blue==7) {
                p.setPen(QColor(161, 104, 7, 255));
            }
            if (red==77 && green==101 && blue==110) {
                p.setPen(QColor(77, 101, 110, 255));
            }
            if (red==190 && green==208 && blue==215) {
                p.setPen(QColor(190, 208, 215, 255));
            }
            //рисуем пиксель
            p.drawPoint(i, j);
        }
    }
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
