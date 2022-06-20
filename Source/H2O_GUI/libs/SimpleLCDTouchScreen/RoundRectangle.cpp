//
// Created by Víctor on 05/10/2021.
//

#include "RoundRectangle.h"

RoundRectangle::RoundRectangle(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Color secondaryColor, Label* label, bool disableAutoSize): ScreenObjectWithLabel(x,y, mainColor, label, disableAutoSize), ScreenObjectWithSecondaryColor(x, y, mainColor, secondaryColor), ScreenObjectWithXtraCoords(x, y, x1, y1, mainColor), ScreenObject(x, y, mainColor)
{
    this->radius = radius;
    setMargin(margin);
    updateLabelLocation(getMargin());
}

RoundRectangle::RoundRectangle(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Color secondaryColor, Label* label): ScreenObjectWithLabel(x,y, mainColor, label), ScreenObjectWithSecondaryColor(x, y, mainColor, secondaryColor), ScreenObjectWithXtraCoords(x, y, x1, y1, mainColor), ScreenObject(x, y, mainColor)
{
    this->radius = radius;
    setMargin(margin);
    updateLabelLocation(getMargin());
}

RoundRectangle::RoundRectangle(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Color secondaryColor): ScreenObjectWithLabel(x,y, mainColor), ScreenObjectWithSecondaryColor(x, y, mainColor, secondaryColor), ScreenObjectWithXtraCoords(x, y, x1, y1, mainColor), ScreenObject(x, y, mainColor)
{
    this->radius = radius;
    setMargin(margin);
    updateLabelLocation(getMargin());
}

RoundRectangle::RoundRectangle(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Label* label, bool disableAutoSize): ScreenObjectWithLabel(x,y, mainColor, label, disableAutoSize), ScreenObjectWithSecondaryColor(x, y, mainColor), ScreenObjectWithXtraCoords(x, y, x1, y1, mainColor), ScreenObject(x, y, mainColor)
{
    this->radius = radius;
    setMargin(margin);
    updateLabelLocation(getMargin());
}

RoundRectangle::RoundRectangle(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Label* label): ScreenObjectWithLabel(x,y, mainColor, label), ScreenObjectWithSecondaryColor(x, y, mainColor), ScreenObjectWithXtraCoords(x, y, x1, y1, mainColor), ScreenObject(x, y, mainColor)
{
    this->radius = radius;
    setMargin(margin);
    updateLabelLocation(getMargin());
}

RoundRectangle::RoundRectangle(int x, int y, int x1, int y1, uint8_t radius, Color mainColor): ScreenObjectWithLabel(x,y, mainColor), ScreenObjectWithSecondaryColor(x, y, mainColor), ScreenObjectWithXtraCoords(x, y, x1, y1, mainColor), ScreenObject(x, y, mainColor)
{
    this->radius = radius;
    setMargin(margin);
    updateLabelLocation(getMargin());
}

uint8_t RoundRectangle::getRadius()
{
    return radius;
}

void RoundRectangle::setRadius(uint8_t radius)
{
    this->radius = radius;
}
