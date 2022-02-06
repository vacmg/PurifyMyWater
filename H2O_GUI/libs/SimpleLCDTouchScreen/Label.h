//
// Created by Víctor on 19/09/2021.
//

#ifndef SIMPLELCDTOUCHSCREEN_LABEL_H
#define SIMPLELCDTOUCHSCREEN_LABEL_H
#include "ScreenObjectWithSecondaryColor.h"


class Label: public ScreenObjectWithSecondaryColor
{
public:
    Label(int x, int y, char* string, int fontSize, Color mainColor, Color secondaryColor);
    Label(int x, int y, char* string, int fontSize, Color mainColor);
    Label(); // Do not use, only for virtual keyword purposes
    char* getString();
    int getFontSize();
    void setString(char* string);
    void setFontSize(int fontSize);

private:
    char* string;
    int fontSize; // length of each square that compounds any symbol in px
};


#endif //SIMPLELCDTOUCHSCREEN_LABEL_H
