//
// Created by Víctor on 30/09/2021.
//

#ifndef SIMPLELCDTOUCHSCREEN_SCREENOBJECTWITHPICTURE_H
#define SIMPLELCDTOUCHSCREEN_SCREENOBJECTWITHPICTURE_H
#include "Picture.h"
#include "ScreenObject.h"

class ScreenObjectWithPicture: virtual public ScreenObject
{
    ScreenObjectWithPicture(int x, int y, Color mainColor, Picture* picture);
    ScreenObjectWithPicture();
    Picture* getPicture();
    void setPicture(Picture* picture);
    bool isAValidPicture();
private:
    Picture* picture;
    bool validPicture;
};


#endif //SIMPLELCDTOUCHSCREEN_SCREENOBJECTWITHPICTURE_H
