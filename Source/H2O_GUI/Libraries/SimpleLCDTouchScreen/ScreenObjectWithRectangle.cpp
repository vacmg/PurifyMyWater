//
// Created by Víctor on 03/06/2022.
//

#include "ScreenObjectWithRectangle.h"

Rectangle *ScreenObjectWithRectangle::getRectangle()
{
    return rectangle;
}


bool ScreenObjectWithRectangle::isAValidRectangle()
{
    return validRectangle;
}

void ScreenObjectWithRectangle::setRectangle(Rectangle *rectangle)
{
    validRectangle = rectangle != nullptr;
    this->rectangle = rectangle;
}

ScreenObjectWithRectangle::ScreenObjectWithRectangle(): ScreenObject(0, 0, Color())
{
    validRectangle = false;
    rectangle = nullptr;
}

ScreenObjectWithRectangle::ScreenObjectWithRectangle(Rectangle *rectangle): ScreenObject(0, 0, Color())
{
    validRectangle = rectangle != nullptr;
    this->rectangle = rectangle;
}

ScreenObjectWithRectangle::ScreenObjectWithRectangle(int x, int y, Color mainColor, Rectangle *rectangle): ScreenObject(x, y, mainColor)
{
    validRectangle = rectangle != nullptr;
    this->rectangle = rectangle;
}
