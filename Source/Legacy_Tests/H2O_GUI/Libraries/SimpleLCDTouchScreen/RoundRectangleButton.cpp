//
// Created by Víctor on 06/10/2021.
//

#include "RoundRectangleButton.h"

RoundRectangleButton::RoundRectangleButton(int x, int y, int x1, int y1, uint8_t radius, Color mainColor,Color secondaryColor, Label* label, TouchScreenObject* ts): RoundRectangle(x,y,x1,y1,radius,mainColor,secondaryColor,label), ScreenObjectWithTouch(x, y, x1, y1, mainColor, ts), ScreenObjectWithLabel(x,y,mainColor,label), ScreenObjectWithSecondaryColor(x,y,mainColor,secondaryColor), ScreenObjectWithXtraCoords(x,y,x1,y1,mainColor), ScreenObject(x,y,mainColor)
{

}

RoundRectangleButton::RoundRectangleButton(int x, int y, int x1, int y1, uint8_t radius, Color mainColor,Color secondaryColor, Label* label, bool autoSizeEnabled, TouchScreenObject* ts): RoundRectangle(x,y,x1,y1,radius,mainColor,secondaryColor,label, autoSizeEnabled), ScreenObjectWithTouch(x, y, x1, y1, mainColor, ts), ScreenObjectWithLabel(x,y,mainColor,label, autoSizeEnabled), ScreenObjectWithSecondaryColor(x,y,mainColor,secondaryColor), ScreenObjectWithXtraCoords(x,y,x1,y1,mainColor), ScreenObject(x,y,mainColor)
{

}

RoundRectangleButton::RoundRectangleButton(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Color secondaryColor, TouchScreenObject* ts): RoundRectangle(x,y,x1,y1,radius,mainColor,secondaryColor), ScreenObjectWithTouch(x, y, x1, y1, mainColor, ts), ScreenObjectWithLabel(x,y,mainColor), ScreenObjectWithSecondaryColor(x,y,mainColor,secondaryColor), ScreenObjectWithXtraCoords(x,y,x1,y1,mainColor), ScreenObject(x,y,mainColor)
{

}

RoundRectangleButton::RoundRectangleButton(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Label* label, TouchScreenObject* ts): RoundRectangle(x,y,x1,y1,radius,mainColor,label), ScreenObjectWithTouch(x, y, x1, y1, mainColor, ts), ScreenObjectWithLabel(x,y,mainColor,label), ScreenObjectWithSecondaryColor(x,y,mainColor), ScreenObjectWithXtraCoords(x,y,x1,y1,mainColor), ScreenObject(x,y,mainColor)
{

}

RoundRectangleButton::RoundRectangleButton(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, Label* label, bool autoSizeEnabled, TouchScreenObject* ts): RoundRectangle(x,y,x1,y1,radius,mainColor,label,autoSizeEnabled), ScreenObjectWithTouch(x, y, x1, y1, mainColor, ts), ScreenObjectWithLabel(x,y,mainColor,label,autoSizeEnabled), ScreenObjectWithSecondaryColor(x,y,mainColor), ScreenObjectWithXtraCoords(x,y,x1,y1,mainColor), ScreenObject(x,y,mainColor)
{

}

RoundRectangleButton::RoundRectangleButton(int x, int y, int x1, int y1, uint8_t radius, Color mainColor, TouchScreenObject* ts): RoundRectangle(x,y,x1,y1,radius,mainColor), ScreenObjectWithTouch(x, y, x1, y1, mainColor, ts), ScreenObjectWithLabel(x,y,mainColor), ScreenObjectWithSecondaryColor(x,y,mainColor), ScreenObjectWithXtraCoords(x,y,x1,y1,mainColor), ScreenObject(x,y,mainColor)
{

}
