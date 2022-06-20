//
// Created by Víctor on 30/09/2021.
//

#ifndef SIMPLELCDTOUCHSCREEN_PICTUREBUTTON_H
#define SIMPLELCDTOUCHSCREEN_PICTUREBUTTON_H
#include "Picture.h"
#include "ScreenObjectWithTouch.h"

class PictureButton: virtual public Picture, virtual public ScreenObjectWithTouch
{
public:
    PictureButton(int x, int y, char *picturePath, TouchScreenObject* ts);
    bool isPressed();
};


#endif //SIMPLELCDTOUCHSCREEN_PICTUREBUTTON_H
