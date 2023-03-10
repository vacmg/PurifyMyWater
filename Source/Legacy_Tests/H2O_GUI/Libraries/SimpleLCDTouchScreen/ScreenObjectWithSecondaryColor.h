//
// Created by Víctor on 19/09/2021.
//

#ifndef SIMPLELCDTOUCHSCREEN_SCREENOBJECTWITHSECONDARYCOLOR_H
#define SIMPLELCDTOUCHSCREEN_SCREENOBJECTWITHSECONDARYCOLOR_H
#include "ScreenObject.h"

class ScreenObjectWithSecondaryColor : virtual public ScreenObject
{
public:
    ScreenObjectWithSecondaryColor(int x, int y, Color mainColor, Color secondaryColor);
    ScreenObjectWithSecondaryColor(int x, int y, Color mainColor);
    ScreenObjectWithSecondaryColor(); // Do not use, only for virtual keyword purposes
    bool isAValidSecondaryColor();
    Color getSecondaryColor();
    void setSecondaryColor(Color secondaryColor);
    void setSecondaryColor(uint8_t r, uint8_t g, uint8_t b);
    void disableSecondaryColor();
private:
    Color secondaryColor;
    bool validSecondaryColor;
};


#endif //SIMPLELCDTOUCHSCREEN_SCREENOBJECTWITHSECONDARYCOLOR_H
