//
// Created by Víctor on 19/09/2021.
//

#include "Label.h"

Label::Label(int x, int y, char* string, int fontSize, Color mainColor, Color secondaryColor):ScreenObjectWithSecondaryColor(x, y, mainColor, secondaryColor), ScreenObject(x, y, mainColor)
{
    this->string = string;
    this->fontSize = fontSize;
}

Label::Label(int x, int y, char* string, int fontSize, Color mainColor):ScreenObjectWithSecondaryColor(x, y, mainColor), ScreenObject(x, y, mainColor)
{
    this->string = string;
    this->fontSize = fontSize;
}

Label::Label()
{
    this->string = "";
    this->fontSize = 0;
}

char *Label::getString()
{
    return string;
}

int Label::getFontSize()
{
    return fontSize;
}

void Label::setString(char *string)
{
    this->string = string;
}

void Label::setFontSize(int fontSize)
{
    this->fontSize = fontSize;
}
