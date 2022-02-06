//
// Created by Víctor on 19/09/2021.
//

#include "ScreenObjectWithXtraCoords.h"

ScreenObjectWithXtraCoords::ScreenObjectWithXtraCoords(int x, int y, int x1, int y1, Color mainColor): ScreenObject(x, y, mainColor)
{
    if (x1<x)
    {
        this->x1 = x;
        setCoords(x1, y);
    }
    else
        this->x1 = x1;
    if (y1<y)
    {
        this->y1 = y;
        setCoords(x, y1);
    }
    else
        this->y1 = y1;
}

ScreenObjectWithXtraCoords::ScreenObjectWithXtraCoords()
{
    if (0<getx())
    {
        this->x1 = getx();
        setCoords(0, gety());
    }
    else
        this->x1 = 0;
    if (0<gety())
    {
        this->y1 = gety();
        setCoords(getx(), 0);
    }
    else
        this->y1 = 0;
}

int ScreenObjectWithXtraCoords::getx1()
{
    return x1;
}

int ScreenObjectWithXtraCoords::gety1()
{
    return y1;
}

int ScreenObjectWithXtraCoords::setCoords1(int x1, int y1)
{
    if (x1<getx())
    {
        this->x1 = getx();
        setCoords(x1, gety());
    }
    else
        this->x1 = x1;
    if (y1<gety())
    {
        this->y1 = gety();
        setCoords(getx(), y1);
    }
    else
        this->y1 = y1;
}

