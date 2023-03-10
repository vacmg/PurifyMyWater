//
// Created by Víctor on 03/06/2022.
//

#ifndef SIMPLELCDTOUCHSCREEN_SCREENOBJECTWITHRECTANGLE_H
#define SIMPLELCDTOUCHSCREEN_SCREENOBJECTWITHRECTANGLE_H

#include "ScreenObject.h"
#include "Rectangle.h"

class ScreenObjectWithRectangle: virtual public ScreenObject
{
public:
    ScreenObjectWithRectangle();
    ScreenObjectWithRectangle(Rectangle* rectangle);
    ScreenObjectWithRectangle(int x, int y, Color mainColor, Rectangle* rectangle);
    Rectangle* getRectangle();
    bool isAValidRectangle();
    void setRectangle(Rectangle* rectangle);
private:
    bool validRectangle;
    Rectangle* rectangle;
};


#endif //SIMPLELCDTOUCHSCREEN_SCREENOBJECTWITHRECTANGLE_H
