//
// Created by Víctor on 30/09/2021.
//

#include "ScreenObjectWithPicture.h"

ScreenObjectWithPicture::ScreenObjectWithPicture(int x, int y, Color mainColor, Picture* picture): ScreenObject(x,y,mainColor)
{
    this->picture = picture;
    validPicture = picture->init();
}

ScreenObjectWithPicture::ScreenObjectWithPicture()
{
    this->picture = nullptr;
    validPicture = false;
}

Picture* ScreenObjectWithPicture::getPicture()
{
    return picture;
}

void ScreenObjectWithPicture::setPicture(Picture* picture)
{
    this->picture = picture;
}

bool ScreenObjectWithPicture::isAValidPicture()
{
    return validPicture;
}
