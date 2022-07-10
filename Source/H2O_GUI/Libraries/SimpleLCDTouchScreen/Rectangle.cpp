//
// Created by Víctor on 19/09/2021.
//

#include "Rectangle.h"

Rectangle::Rectangle(int x, int y, int x1, int y1, Color mainColor, Color secondaryColor, Label* label, bool autoSizeEnabled): ScreenObjectWithLabel(x,y, mainColor, label, autoSizeEnabled), ScreenObjectWithSecondaryColor(x, y, mainColor, secondaryColor), ScreenObjectWithXtraCoords(x, y, x1, y1, mainColor), ScreenObject(x, y, mainColor)
{
    setMargin(margin);
    updateLabelLocation(getMargin());
}

Rectangle::Rectangle(int x, int y, int x1, int y1, Color mainColor, Color secondaryColor, Label* label): ScreenObjectWithLabel(x,y, mainColor, label), ScreenObjectWithSecondaryColor(x, y, mainColor, secondaryColor), ScreenObjectWithXtraCoords(x, y, x1, y1, mainColor), ScreenObject(x, y, mainColor)
{
    setMargin(margin);
    updateLabelLocation(getMargin());
}

Rectangle::Rectangle(int x, int y, int x1, int y1, Color mainColor, Color secondaryColor): ScreenObjectWithLabel(x,y, mainColor), ScreenObjectWithSecondaryColor(x, y, mainColor, secondaryColor), ScreenObjectWithXtraCoords(x, y, x1, y1, mainColor), ScreenObject(x, y, mainColor)
{
    setMargin(margin);
    updateLabelLocation(getMargin());
}

Rectangle::Rectangle(int x, int y, int x1, int y1, Color mainColor, Label* label, bool autoSizeEnabled): ScreenObjectWithLabel(x,y, mainColor, label, autoSizeEnabled), ScreenObjectWithSecondaryColor(x, y, mainColor), ScreenObjectWithXtraCoords(x, y, x1, y1, mainColor), ScreenObject(x, y, mainColor)
{
    setMargin(margin);
    updateLabelLocation(getMargin());
}

Rectangle::Rectangle(int x, int y, int x1, int y1, Color mainColor, Label* label): ScreenObjectWithLabel(x,y, mainColor, label), ScreenObjectWithSecondaryColor(x, y, mainColor), ScreenObjectWithXtraCoords(x, y, x1, y1, mainColor), ScreenObject(x, y, mainColor)
{
    setMargin(margin);
    updateLabelLocation(getMargin());
}

Rectangle::Rectangle(int x, int y, int x1, int y1, Color mainColor): ScreenObjectWithLabel(x,y, mainColor), ScreenObjectWithSecondaryColor(x, y, mainColor), ScreenObjectWithXtraCoords(x, y, x1, y1, mainColor), ScreenObject(x, y, mainColor)
{
    setMargin(margin);
    updateLabelLocation(getMargin());
}
