//
// Created by Víctor on 18/09/2021.
//

#ifndef SIMPLELCDTOUCHSCREEN_SCREENOBJECT_H
#define SIMPLELCDTOUCHSCREEN_SCREENOBJECT_H

#include <Color.h>

class ScreenObject
{
public:
    ScreenObject(int x, int y, Color mainColor);
    ScreenObject();
    int getx();
    int gety();
    Color getMainColor();
    void setCoords(int x, int y);
    void setMainColor(Color mainColor);
    void setMainColor(uint8_t r, uint8_t g, uint8_t b);

private:
    int x;
    int y;
    Color mainColor;
};


#endif //SIMPLELCDTOUCHSCREEN_SCREENOBJECT_H
