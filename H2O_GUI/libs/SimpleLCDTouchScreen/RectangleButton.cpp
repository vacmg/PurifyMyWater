//
// Created by Víctor on 21/09/2021.
//

#include "RectangleButton.h"

RectangleButton::RectangleButton(int x, int y, int x1, int y1, Color mainColor, Color secondaryColor, Label* label, TouchScreenObject* ts): Rectangle(x, y, x1, y1, mainColor, secondaryColor, label), ScreenObjectWithTouch(x, y, x1, y1, mainColor, ts), ScreenObjectWithLabel(x,y,mainColor,label), ScreenObjectWithSecondaryColor(x,y,mainColor,secondaryColor), ScreenObjectWithXtraCoords(x,y,x1,y1,mainColor), ScreenObject(x,y,mainColor)
{

}

RectangleButton::RectangleButton(int x, int y, int x1, int y1, Color mainColor, Color secondaryColor, Label* label, bool disableAutoSize, TouchScreenObject* ts): Rectangle(x, y, x1, y1, mainColor, secondaryColor, label, disableAutoSize), ScreenObjectWithTouch(x, y, x1, y1, mainColor, ts), ScreenObjectWithLabel(x,y,mainColor,label, disableAutoSize), ScreenObjectWithSecondaryColor(x,y,mainColor,secondaryColor), ScreenObjectWithXtraCoords(x,y,x1,y1,mainColor), ScreenObject(x,y,mainColor)
{

}

RectangleButton::RectangleButton(int x, int y, int x1, int y1, Color mainColor, Color secondaryColor, TouchScreenObject* ts): Rectangle(x,y,x1,y1,mainColor,secondaryColor), ScreenObjectWithTouch(x, y, x1, y1, mainColor, ts), ScreenObjectWithLabel(x,y,mainColor), ScreenObjectWithSecondaryColor(x,y,mainColor,secondaryColor), ScreenObjectWithXtraCoords(x,y,x1,y1,mainColor), ScreenObject(x,y,mainColor)
{

}

RectangleButton::RectangleButton(int x, int y, int x1, int y1, Color mainColor, Label* label, TouchScreenObject* ts): Rectangle(x,y,x1,y1,mainColor,label), ScreenObjectWithTouch(x, y, x1, y1, mainColor, ts), ScreenObjectWithLabel(x,y,mainColor,label), ScreenObjectWithSecondaryColor(x,y,mainColor), ScreenObjectWithXtraCoords(x,y,x1,y1,mainColor), ScreenObject(x,y,mainColor)
{

}

RectangleButton::RectangleButton(int x, int y, int x1, int y1, Color mainColor, Label* label, bool disableAutoSize, TouchScreenObject* ts): Rectangle(x,y,x1,y1,mainColor,label, disableAutoSize), ScreenObjectWithTouch(x, y, x1, y1, mainColor, ts), ScreenObjectWithLabel(x,y,mainColor,label, disableAutoSize), ScreenObjectWithSecondaryColor(x,y,mainColor), ScreenObjectWithXtraCoords(x,y,x1,y1,mainColor), ScreenObject(x,y,mainColor)
{

}

RectangleButton::RectangleButton(int x, int y, int x1, int y1, Color mainColor, TouchScreenObject* ts): Rectangle(x,y,x1,y1,mainColor), ScreenObjectWithTouch(x, y, x1, y1, mainColor, ts), ScreenObjectWithLabel(x,y,mainColor), ScreenObjectWithSecondaryColor(x,y,mainColor), ScreenObjectWithXtraCoords(x,y,x1,y1,mainColor), ScreenObject(x,y,mainColor)
{

}
