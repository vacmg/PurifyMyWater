//
// Created by Víctor on 19/09/2021.
//

#include "ScreenObjectWithXtraCoords.h"

ScreenObjectWithXtraCoords::ScreenObjectWithXtraCoords(int x, int y, int x1, int y1, Color mainColor): ScreenObject(x, y, mainColor)
{
    if (x1<getx())
    {
        this->x1 = getx();
        this->y1 = gety();
        ScreenObject::setCoords(x1, y1);
    }
    else
    {
        this->x1 = x1;
        this->y1 = y1;
    }
}

ScreenObjectWithXtraCoords::ScreenObjectWithXtraCoords()
{
    if (0<getx())
    {
        this->x1 = getx();
        this->y1 = gety();
        ScreenObject::setCoords(0, 0);
    }
    else
    {
        this->x1 = 0;
        this->y1 = 0;
    }
}

int ScreenObjectWithXtraCoords::getx1()
{
    return x1;
}

int ScreenObjectWithXtraCoords::gety1()
{
    return y1;
}

void ScreenObjectWithXtraCoords::setCoords(int x, int y)
{
    if(x>x1)
    {
        ScreenObject::setCoords(x1,y1);
        this->x1 = x;
        this->y1 = y;
    }
    else
    {
        ScreenObject::setCoords(x,y);
    }
}

void ScreenObjectWithXtraCoords::setCoords1(int x1, int y1)
{
    if (x1<getx())
    {
        this->x1 = getx();
        this->y1 = gety();
        ScreenObject::setCoords(x1, y1);
    }
    else
    {
        this->x1 = x1;
        this->y1 = y1;
    }
}

