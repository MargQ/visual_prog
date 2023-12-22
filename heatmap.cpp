#include "heatmap.h"
#include "materials.h"

//int maxX=1000, maxY=1000;

int DrawPixel(QPainter* Pix, int x, int y)
{
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

int* heatmap::N_of_obstructions(QPainter* Pix, QPixmap* Map, int *Number, int x0, int x1, int y0, int y1)
{
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

void heatmap::fill_field(QPainter* p, QPixmap* map,QImage* image, int cellPosX, int cellPosY, int onePixDistance, int TxPower, int antGain, float freq)
{
    int maxX=1000, maxY=1000;
    for(int i = 0; i < maxX; i++){
        for(int j = 0; j < maxY; j++){
            float distance = 0;
            distance =sqrt (pow(abs(cellPosX - i), 2) + pow(abs(cellPosY-j), 2));
            distance *= onePixDistance;
            propagation_model model;
            float sigPower = TxPower + antGain - model.PL(freq, distance);
            int NumObs[4]{}; //пустой массив препятствий
            heatmap n;
            n.N_of_obstructions(p, map, NumObs, cellPosX, i, cellPosY, j); //заполнение массива
            if (NumObs[0] > 0 || NumObs[1] > 0 || NumObs[2] > 0 || NumObs[3] > 0) {
                //затухание
                materials m;
                sigPower=sigPower-NumObs[0]*m.delay(freq,0)-NumObs[1]*m.delay(freq,1)-NumObs[2]*m.delay(freq,2)-NumObs[3]*m.delay(freq,3);
            }
            heatmap pen;
            pen.Pen_Color(p, sigPower);


            QRgb color=image->pixel(i, j); //оставляем нарисованные препятствия
            int red = qRed(color);
            int green = qGreen(color);
            int blue = qBlue(color);
            if (red==34 && green==34 && blue==34) {
                p->setPen(QColor(34, 34, 34, 255));
            }
            if (red==161 && green==104 && blue==7) {
                p->setPen(QColor(161, 104, 7, 255));
            }
            if (red==77 && green==101 && blue==110) {
                p->setPen(QColor(77, 101, 110, 255));
            }
            if (red==190 && green==208 && blue==215) {
                p->setPen(QColor(190, 208, 215, 255));
            }
            //рисуем пиксель
            p->drawPoint(i, j);
        }
    }
}

void heatmap::Pen_Color (QPainter* p,float sigPower)
{
    if(sigPower < -44 && sigPower >= -54)
    {
        p->setPen(QColor(255, 0, 0, 255)); // <-- задание цвета
    }
    else if (sigPower > -84 ) {
        p->setPen(QColor(255,((sigPower+44)*(-1.0)*6.375), 0)); // <-- задание цвета
    }

    else if (sigPower > -104 ) {
        p->setPen(QColor((255+((sigPower+84)*12.75)), 255,0)); // <-- задание цвета
    }
    else if (sigPower > -124 ) {
        p->setPen(QColor(0, 255, ((sigPower+104)*(-1.0)*12.75))); // <-- задание цвета
    }
    else if (sigPower > -144 ) {
        p->setPen(QColor(0, 255+((sigPower+124)*12.75), 255)); // <-- задание цвета
    }
}



