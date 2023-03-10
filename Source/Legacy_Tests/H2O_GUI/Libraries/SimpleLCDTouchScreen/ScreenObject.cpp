//
// Created by Víctor on 18/09/2021.
//

#include "ScreenObject.h"

ScreenObject::ScreenObject(int x, int y, Color mainColor)
{
    this->x = x;
    this->y = y;
    this->mainColor = mainColor;
}

ScreenObject::ScreenObject()
{
    this->x = 0;
    this->y = 0;
    this->mainColor = Color(0,0,0);
}

int ScreenObject::getx()
{
    return x;
}

int ScreenObject::gety()
{
    return y;
}

Color ScreenObject::getMainColor()
{
    return mainColor;
}

void ScreenObject::setCoords(int x, int y)
{
    this->x = x;
    this->y = y;
}

void ScreenObject::setMainColor(Color mainColor)
{
    this->mainColor = mainColor;
}

void ScreenObject::setMainColor(uint8_t r, uint8_t g, uint8_t b)
{
    this->mainColor = Color(r, g, b);
}

