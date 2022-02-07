//
// Created by Víctor on 06/10/2021.
//

#ifndef SIMPLELCDTOUCHSCREEN_ROUNDRECTANGLEBUTTON_H
#define SIMPLELCDTOUCHSCREEN_ROUNDRECTANGLEBUTTON_H
#include "ScreenObjectWithTouch.h"
#include "Label.h"
#include "RoundRectangle.h"

class RoundRectangleButton: virtual public RoundRectangle, virtual public ScreenObjectWithTouch, virtual public ScreenObjectWithLabel, virtual public ScreenObjectWithSecondaryColor, virtual public ScreenObjectWithXtraCoords, virtual public ScreenObject
{
public:
    RoundRectangleButton(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Color secondaryColor, Label* label, TouchScreenObject* ts);
    RoundRectangleButton(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Color secondaryColor, Label* label, bool disableAutoSize, TouchScreenObject* ts);
    RoundRectangleButton(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Color secondaryColor, TouchScreenObject* ts);
    RoundRectangleButton(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Label* label, TouchScreenObject* ts);
    RoundRectangleButton(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Label* label, bool disableAutoSize, TouchScreenObject* ts);
    RoundRectangleButton(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, TouchScreenObject* ts);
};


#endif //SIMPLELCDTOUCHSCREEN_ROUNDRECTANGLEBUTTON_H
