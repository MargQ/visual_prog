#include "mainwindow.h"
#include <QtWidgets>
#include <QPixmap>
#include <QPainter>
#include <time.h>
#include <math.h>
#include "obstacles.h"
#include "heatmap.h"

void obstacles::circle(QPainter *Pix, int X1, int Y1, int R)
{
            int x = 0;
            int y = R;
            int delta = 1 - 2 * R;
            int error = 0;
            if (concrete == true)
            {
                Pix->setPen(QColor(34, 34, 34, 255));
            }
            if (wood == true)
            {
                Pix->setPen(QColor(161, 104, 7, 255));
            }
            if (doubleglass == true)
            {
                Pix->setPen(QColor(77, 101, 110, 255));
            }
            if (irrglass == true)
            {
                Pix->setPen(QColor(190, 208, 215, 255));
            }
            while (y >= x)
            {
                DrawPixel(Pix, X1 + x, Y1 + y);
                DrawPixel(Pix, X1 + x, Y1 - y);
                DrawPixel(Pix, X1 - x, Y1 + y);
                DrawPixel(Pix, X1 - x, Y1 - y);
                DrawPixel(Pix, X1 + y, Y1 + x);
                DrawPixel(Pix, X1 + y, Y1 - x);
                DrawPixel(Pix, X1 - y, Y1 + x);
                DrawPixel(Pix, X1 - y, Y1 - x);
                error = 2 * (delta + y) - 1;
                if ((delta < 0) && (error <= 0))
                {
                    delta += 2 * ++x + 1;
                    continue;
                }
                if ((delta > 0) && (error > 0))
                {
                    delta -= 2 * --y + 1;
                    continue;
                }
                delta += 2 * (++x - --y);
        }
    }

void obstacles::line(QPainter *Pix, int x0, int x1, int y0, int y1)
{
    int deltax = abs(x1 - x0);
            int deltay = abs(y1 - y0);
            int signx = x0 < x1 ? 1 : -1;
            int signy = y0 < y1 ? 1 : -1;
            int error = deltax - deltay;
            if (concrete == true)
            {
                Pix->setPen(QColor(34, 34, 34, 255));
            }
            if (wood == true)
            {
                Pix->setPen(QColor(161, 104, 7, 255));
            }
            if (doubleglass == true)
            {
                Pix->setPen(QColor(77, 101, 110, 255));
            }
            if (irrglass == true)
            {
                Pix->setPen(QColor(190, 208, 215, 255));
            }
            DrawPixel(Pix, x1, y1);
            while (x0 != x1 || y0 != y1)
            {
                DrawPixel(Pix, x0, y0);
                int error2 = error*2;
                if (error2 > -deltay)
                {
                    error -= deltay;
                    x0 += signx;
                }
                if (error2 < deltax)
                {
                    error += deltax;
                    y0 += signy;
                }
            }
        }

void obstacles::square(QPainter *Pix, int x0, int x1, int y0, int y1)
{
    if (concrete == true)
            {
                Pix->setPen(QColor(34, 34, 34, 255));
            }
            if (wood == true)
            {
                Pix->setPen(QColor(161, 104, 7, 255));
            }
            if (doubleglass == true)
            {
                Pix->setPen(QColor(77, 101, 110, 255));
            }
            if (irrglass == true)
            {
                Pix->setPen(QColor(190, 208, 215, 255));
            }
            if (x0<x1)
            {
                for (int x=x0; x<x1; x++)
                {
                    DrawPixel(Pix, x, y0);
                    DrawPixel(Pix, x, y1);
                }
            }
            if (x1<x0)
            {
                for (int x=x1; x<x0; x++)
                {
                    DrawPixel(Pix, x, y0);
                    DrawPixel(Pix, x, y1);
                }
            }
            if (y0<y1)
            {
                for (int y=y0; y<y1; y++)
                {
                    DrawPixel(Pix, x0, y);
                    DrawPixel(Pix, x1, y);
                }
            }
            if (y1<y0)
            {
                for (int y=y1; y<y0; y++)
                {
                    DrawPixel(Pix, x0, y);
                    DrawPixel(Pix, x1, y);
                }
            }
        }
