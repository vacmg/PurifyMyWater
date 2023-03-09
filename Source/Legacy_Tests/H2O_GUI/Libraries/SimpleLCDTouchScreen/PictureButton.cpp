//
// Created by Víctor on 30/09/2021.
//

#include "PictureButton.h"

PictureButton::PictureButton(int x, int y, char *picturePath, TouchScreenObject* ts): Picture(x,y,picturePath), ScreenObjectWithTouch(x,y,x,y,Color(0,0,0),ts)
{

}

bool PictureButton::isPressed()
{
    return init() && ScreenObjectWithTouch::isPressed();
}
