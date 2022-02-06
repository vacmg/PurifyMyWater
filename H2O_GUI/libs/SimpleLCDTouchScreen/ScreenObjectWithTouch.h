//
// Created by Víctor on 21/09/2021.
//

#ifndef SIMPLELCDTOUCHSCREEN_SCREENOBJECTWITHTOUCH_H
#define SIMPLELCDTOUCHSCREEN_SCREENOBJECTWITHTOUCH_H
#include <ScreenObjectWithXtraCoords.h>
#include <TouchScreen.h>
#include <TouchScreenObject.h>

class ScreenObjectWithTouch: virtual public ScreenObjectWithXtraCoords
{
public:
    ScreenObjectWithTouch(int x, int y, int x1, int y1, Color mainColor, TouchScreenObject* ts);
    void setTouchScreenObject(TouchScreenObject* ts);
    bool isPressed();

private:
    TouchScreenObject* ts;
};


#endif //SIMPLELCDTOUCHSCREEN_SCREENOBJECTWITHTOUCH_H
