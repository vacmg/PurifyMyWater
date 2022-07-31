//
// Created by Víctor on 21/09/2021.
//

#ifndef SIMPLELCDTOUCHSCREEN_RECTANGLEBUTTON_H
#define SIMPLELCDTOUCHSCREEN_RECTANGLEBUTTON_H
#include "ScreenObjectWithTouch.h"
#include "Label.h"
#include "Rectangle.h"

class RectangleButton: virtual public Rectangle, virtual public ScreenObjectWithTouch, virtual public ScreenObjectWithLabel, virtual public ScreenObjectWithSecondaryColor, virtual public ScreenObjectWithXtraCoords, virtual public ScreenObject
{
public:
    RectangleButton(int x, int y, int x1, int y1, Color mainColor, Color secondaryColor, Label* label, TouchScreenObject* ts);
    RectangleButton(int x, int y, int x1, int y1, Color mainColor, Color secondaryColor, Label* label, bool autoSizeEnabled, TouchScreenObject* ts);
    RectangleButton(int x, int y, int x1, int y1, Color mainColor, Color secondaryColor, TouchScreenObject* ts);
    RectangleButton(int x, int y, int x1, int y1, Color mainColor, Label* label, TouchScreenObject* ts);
    RectangleButton(int x, int y, int x1, int y1, Color mainColor, Label* label, bool autoSizeEnabled, TouchScreenObject* ts);
    RectangleButton(int x, int y, int x1, int y1, Color mainColor, TouchScreenObject* ts);
};


#endif //SIMPLELCDTOUCHSCREEN_RECTANGLEBUTTON_H
