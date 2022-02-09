//
// Created by Víctor on 19/09/2021.
//

#include "ScreenObjectWithSecondaryColor.h"

ScreenObjectWithSecondaryColor::ScreenObjectWithSecondaryColor(int x, int y, Color mainColor, Color secondaryColor): ScreenObject(x, y, mainColor)
{
    this->secondaryColor = secondaryColor;
    this->validSecondaryColor = true;
}

ScreenObjectWithSecondaryColor::ScreenObjectWithSecondaryColor(int x, int y, Color mainColor): ScreenObject(x, y, mainColor)
{
    this->secondaryColor = Color(0,0,0);
    this->validSecondaryColor = false;
}

ScreenObjectWithSecondaryColor::ScreenObjectWithSecondaryColor()
{
    this->secondaryColor = Color(0,0,0);
    this->validSecondaryColor = false;
}

Color ScreenObjectWithSecondaryColor::getSecondaryColor()
{
    return secondaryColor;
}

bool ScreenObjectWithSecondaryColor::isAValidSecondaryColor()
{
    return validSecondaryColor;
}

void ScreenObjectWithSecondaryColor::setSecondaryColor(Color secondaryColor)
{
    this->secondaryColor = secondaryColor;
    validSecondaryColor = true;
}

void ScreenObjectWithSecondaryColor::setSecondaryColor(uint8_t r, uint8_t g, uint8_t b)
{
    this->secondaryColor = Color(r, g, b);
    validSecondaryColor = true;
}

void ScreenObjectWithSecondaryColor::disableSecondaryColor()
{
    validSecondaryColor = false;
}
