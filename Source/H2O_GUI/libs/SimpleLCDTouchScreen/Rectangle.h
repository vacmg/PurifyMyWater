//
// Created by Víctor on 19/09/2021.
//

#ifndef SIMPLELCDTOUCHSCREEN_RECTANGLE_H
#define SIMPLELCDTOUCHSCREEN_RECTANGLE_H
#include "ScreenObjectWithSecondaryColor.h"
#include "ScreenObjectWithLabel.h"
#include "ScreenObjectWithXtraCoords.h"

class Rectangle: virtual public ScreenObjectWithSecondaryColor, virtual public ScreenObjectWithLabel
{
public:
    Rectangle(int x, int y, int x1, int y1, Color mainColor, Color secondaryColor, Label* label);
    Rectangle(int x, int y, int x1, int y1, Color mainColor, Color secondaryColor, Label* label, bool disableAutoSize);
    Rectangle(int x, int y, int x1, int y1, Color mainColor, Color secondaryColor);
    Rectangle(int x, int y, int x1, int y1, Color mainColor, Label* label);
    Rectangle(int x, int y, int x1, int y1, Color mainColor, Label* label, bool disableAutoSize);
    Rectangle(int x, int y, int x1, int y1, Color mainColor);
private:
    const int margin = 32;

};


#endif //SIMPLELCDTOUCHSCREEN_RECTANGLE_H
