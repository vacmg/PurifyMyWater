//
// Created by Víctor on 19/09/2021.
//

#ifndef SIMPLELCDTOUCHSCREEN_SCREENOBJECTWITHXTRACOORDS_H
#define SIMPLELCDTOUCHSCREEN_SCREENOBJECTWITHXTRACOORDS_H
#include "ScreenObject.h"


class ScreenObjectWithXtraCoords: virtual public ScreenObject
{
public:
    ScreenObjectWithXtraCoords(int x, int y, int x1, int y1, Color mainColor);
    ScreenObjectWithXtraCoords(); // Do not use, only for virtual keyword purposes
    int getx1();
    int gety1();
    void setCoords(int x, int y) override;
    void setCoords1(int x1, int y1);


private:
    int x1;
    int y1;
};


#endif //SIMPLELCDTOUCHSCREEN_SCREENOBJECTWITHXTRACOORDS_H
