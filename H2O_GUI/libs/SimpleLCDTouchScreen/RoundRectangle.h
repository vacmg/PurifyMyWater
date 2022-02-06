//
// Created by Víctor on 05/10/2021.
//

#ifndef SIMPLELCDTOUCHSCREEN_ROUNDRECTANGLE_H
#define SIMPLELCDTOUCHSCREEN_ROUNDRECTANGLE_H

#include "Rectangle.h"

class RoundRectangle: virtual public ScreenObjectWithXtraCoords, virtual public ScreenObjectWithSecondaryColor, virtual  public ScreenObjectWithLabel
{
public:
    RoundRectangle(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Color secondaryColor, Label* label);
    RoundRectangle(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Color secondaryColor, Label* label, bool disableAutoSize);
    RoundRectangle(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Color secondaryColor);
    RoundRectangle(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Label* label);
    RoundRectangle(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Label* label, bool disableAutoSize);
    RoundRectangle(int x, int y, int x1, int y1, uint8_t radius, Color mainColor);

    uint8_t getRadius();
    void setRadius(uint8_t radius);
private:
    const int margin = 32;
    uint8_t radius;
};


#endif //SIMPLELCDTOUCHSCREEN_ROUNDRECTANGLE_H
