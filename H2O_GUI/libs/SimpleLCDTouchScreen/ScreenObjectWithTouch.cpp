//
// Created by Víctor on 21/09/2021.
//

#include "ScreenObjectWithTouch.h"

ScreenObjectWithTouch::ScreenObjectWithTouch(int x, int y, int x1, int y1, Color mainColor, TouchScreenObject* ts): ScreenObjectWithXtraCoords(x, y, x1, y1, mainColor)
{
    this->ts=ts;
}

// Be carefull to no NOT call this function BEFORE calling SimpleLCDTouchScreen::Init_TouchScreen()
bool ScreenObjectWithTouch::isPressed()
{
    TSPoint point = ts->getPoint();

    if(point.z > 50)
    {
        return (point.x > getx() && point.x < getx1() && point.y > gety() && point.y < gety1());
    }
    else return false;
}

void ScreenObjectWithTouch::setTouchScreenObject(TouchScreenObject* ts)
{
    this->ts = ts;
}
