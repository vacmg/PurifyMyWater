//
// Created by Víctor on 19/09/2021.
//

#ifndef SIMPLELCDTOUCHSCREEN_LINE_H
#define SIMPLELCDTOUCHSCREEN_LINE_H
#include "ScreenObjectWithXtraCoords.h"


class Line: public ScreenObjectWithXtraCoords
{
public:
    Line(int x, int y, int x1, int y1, Color mainColor);

private:
};


#endif //SIMPLELCDTOUCHSCREEN_LINE_H
