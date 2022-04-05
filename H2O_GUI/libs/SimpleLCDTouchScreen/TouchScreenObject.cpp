//
// Created by Víctor on 22/09/2021.
//

#include <Arduino.h>
#include "TouchScreenObject.h"

TouchScreenObject::TouchScreenObject(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, int DISPLAY_HEIGHT,
                                     int DISPLAY_WIDTH, int rotation): TouchScreen(xp, yp, xm, ym, 300)
 {
    this->CAL_LEFT = 0;
    this->CAL_TOP = 0;
    this->CAL_RIGHT = 1023;
    this->CAL_BOT = 1023;
    this->DISPLAY_HEIGHT = DISPLAY_HEIGHT;
    this->DISPLAY_WIDTH = DISPLAY_WIDTH;
    this->rotation = rotation;
    this->xm = xm;
    this->yp = yp;
    this->xAxisInverted = false;
}

TouchScreenObject::TouchScreenObject(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rx, int DISPLAY_HEIGHT,
                                     int DISPLAY_WIDTH, int rotation): TouchScreen(xp, yp, xm, ym, rx)
 {
    this->CAL_LEFT = 0;
    this->CAL_TOP = 0;
    this->CAL_RIGHT = 1023;
    this->CAL_BOT = 1023;
    this->DISPLAY_HEIGHT = DISPLAY_HEIGHT;
    this->DISPLAY_WIDTH = DISPLAY_WIDTH;
    this->rotation = rotation;
    this->xm = xm;
    this->yp = yp;
    this->xAxisInverted = false;
}

TouchScreenObject::TouchScreenObject(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, int DISPLAY_HEIGHT,
                                     int DISPLAY_WIDTH, int rotation, int CAL_LEFT, int CAL_RIGHT, int CAL_TOP, int CAL_BOT): TouchScreen(xp, yp, xm, ym, 300)
 {
    this->CAL_LEFT = CAL_LEFT;
    this->CAL_TOP = CAL_TOP;
    this->CAL_RIGHT = CAL_RIGHT;
    this->CAL_BOT = CAL_BOT;
    this->DISPLAY_HEIGHT = DISPLAY_HEIGHT;
    this->DISPLAY_WIDTH = DISPLAY_WIDTH;
    this->rotation = rotation;
    this->xm = xm;
    this->yp = yp;
    this->xAxisInverted = false;
}

TouchScreenObject::TouchScreenObject(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rx, int DISPLAY_HEIGHT,
                                     int DISPLAY_WIDTH, int rotation, int CAL_LEFT, int CAL_RIGHT, int CAL_TOP, int CAL_BOT): TouchScreen(xp, yp, xm, ym, rx)
 {
    this->CAL_LEFT = CAL_LEFT;
    this->CAL_TOP = CAL_TOP;
    this->CAL_RIGHT = CAL_RIGHT;
    this->CAL_BOT = CAL_BOT;
    this->DISPLAY_HEIGHT = DISPLAY_HEIGHT;
    this->DISPLAY_WIDTH = DISPLAY_WIDTH;
    this->rotation = rotation;
    this->xm = xm;
    this->yp = yp;
    this->xAxisInverted = false;
}

TouchScreenObject::TouchScreenObject(): TouchScreen(8, A3, A2, 9, 300)
{
    this->CAL_LEFT = 0;
    this->CAL_TOP = 0;
    this->CAL_RIGHT = 1023;
    this->CAL_BOT = 1023;
    this->DISPLAY_HEIGHT = 320;
    this->DISPLAY_WIDTH = 480;
    this->rotation = 0;
    this->xm = A2;
    this->yp = A3;
    this->xAxisInverted = false;
}

TSPoint TouchScreenObject::getPoint()
{
    TSPoint point = TouchScreen::getPoint();
    pinMode(xm, OUTPUT);
    pinMode(yp, OUTPUT);

    /*if(point.z>50)
        Serial.print("raw:\tx:"+String(point.x)+";\ty:"+point.y+'\t');//*/

    point.x = map(point.x, CAL_LEFT, CAL_RIGHT, 0, DISPLAY_HEIGHT); // long map(long x, long in_min, long in_max, long out_min, long out_max)
    point.y = map(point.y, CAL_TOP, CAL_BOT, 0, DISPLAY_WIDTH);

    if(xAxisInverted)
        point.x = DISPLAY_HEIGHT-point.x;

    /*if(point.z>50) //
        Serial.print("noRotation:\tx:"+String(point.x)+";\ty:"+point.y+'\t');//*/

    if (rotation == 1)
    {
        int aux = point.x;
        point.x = point.y;
        point.y = DISPLAY_HEIGHT-aux;
    }
    else if (rotation == 2)
    {
        point.y = DISPLAY_WIDTH-point.y;
        point.x = DISPLAY_HEIGHT-point.x;
    }
    else if(rotation == 3)
    {
        int aux = point.x;
        point.x = DISPLAY_WIDTH-point.y;
        point.y = aux;
    }

    /*if(point.z>50) // todo delete this
    Serial.print("point:\tx:"+String(point.x)+";\ty:"+point.y+'\n'); // todo delete this//*/
    return point;
}

int TouchScreenObject::getRotation()
{
    return rotation;
}
void TouchScreenObject::setRotation(int rotation)
{
    this->rotation = rotation;
}

void TouchScreenObject::invertXAxis(bool inverted)
{
    xAxisInverted = inverted;
}

bool TouchScreenObject::isXAxisInverted()
{
    return xAxisInverted;
}
