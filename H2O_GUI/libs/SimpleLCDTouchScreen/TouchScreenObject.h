//
// Created by Víctor on 22/09/2021.
//

#ifndef SIMPLELCDTOUCHSCREEN_TOUCHSCREENOBJECT_H
#define SIMPLELCDTOUCHSCREEN_TOUCHSCREENOBJECT_H
#include <TouchScreen.h>

class TouchScreenObject: public TouchScreen
{
public:
    TouchScreenObject();
    TouchScreenObject(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, int DISPLAY_HEIGHT, int DISPLAY_WIDTH, int rotation);
    TouchScreenObject(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rx, int DISPLAY_HEIGHT, int DISPLAY_WIDTH, int rotation);
    TouchScreenObject(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, int DISPLAY_HEIGHT, int DISPLAY_WIDTH, int rotation, int CAL_LEFT, int CAL_RIGHT, int CAL_TOP, int CAL_BOT);
    TouchScreenObject(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rx, int DISPLAY_HEIGHT, int DISPLAY_WIDTH, int rotation, int CAL_LEFT, int CAL_RIGHT, int CAL_TOP, int CAL_BOT);
    TSPoint getPoint();
    int getRotation();
    void setRotation(int rotation);

private:
    int CAL_LEFT;
    int CAL_TOP;
    int CAL_RIGHT;
    int CAL_BOT;
    int DISPLAY_HEIGHT;
    int DISPLAY_WIDTH;
    int rotation;
    uint8_t xm, yp;
};


#endif //SIMPLELCDTOUCHSCREEN_TOUCHSCREENOBJECT_H
