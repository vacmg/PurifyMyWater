//
// Created by Víctor on 19/09/2021.
//

#include "ScreenObjectWithLabel.h"

ScreenObjectWithLabel::ScreenObjectWithLabel(int x, int y, Color mainColor, Label* label, bool disableAutoSize):ScreenObject(x, y, mainColor)
{
    this->label = label;
    this->validLabel = true;
    this->margin = defaultMargin;
    this->disableAutoSize = disableAutoSize;
}

ScreenObjectWithLabel::ScreenObjectWithLabel(int x, int y, Color mainColor, Label* label):ScreenObject(x, y, mainColor)
{
    this->label = label;
    this->validLabel = true;
    this->margin = defaultMargin;
    this->disableAutoSize = false;
}

ScreenObjectWithLabel::ScreenObjectWithLabel(int x, int y, Color mainColor):ScreenObject(x, y, mainColor)
{
    this->label = nullptr;
    this->validLabel = false;
    this->margin = defaultMargin;
    this->disableAutoSize = false;
}

ScreenObjectWithLabel::ScreenObjectWithLabel()
{
    this->label = nullptr;
    this->validLabel = false;
    this->margin = defaultMargin;
    this->disableAutoSize = false;
}

Label* ScreenObjectWithLabel::getLabel()
{
    return label;
}

bool ScreenObjectWithLabel::isAValidLabel()
{
    return validLabel;
}

void ScreenObjectWithLabel::setLabel(Label* label)
{
    this->label = label;
}

// This function dynamicly set rectangle's label position and font size
// The algorythm used is a little bit complex: the first part uses a predefined scheme of making the label to use 3/4 parts of the rectangle
// With that scheme, it gets the fontSize. The second part of the algorythm uses the fontSize to get the coords used to draw the label
void ScreenObjectWithLabel::updateLabelLocation(uint8_t margin)
{
    int wlen = strlen(getLabel()->getString());
    int sizeX = getx1()-getx();
    int sizeY = gety1()-gety();
    int borderX = sizeX/margin;
    int borderY = sizeY/margin;
    int wordSizeX = sizeX-2*borderX;
    int wordSizeY = sizeY-2*borderY;
    int fontSizeX = wordSizeX/((wlen-1)*(blockSizeX+1)+blockSizeX);
    int fontSizeY = wordSizeY/blockSizeY;
    int fontSize = disableAutoSize ? getLabel()->getFontSize() : (fontSizeX<fontSizeY?fontSizeX:fontSizeY);

    wordSizeX = ((wlen-1)*(blockSizeX+1)+blockSizeX)*fontSize;
    wordSizeY = blockSizeY*fontSize;

    borderX = (sizeX - wordSizeX)/2;
    borderY = (sizeY - wordSizeY)/2;

    label->setCoords(getx()+borderX,gety()+borderY);
    label->setFontSize(fontSize);
}

int ScreenObjectWithLabel::getMargin()
{
    return margin;
}

void ScreenObjectWithLabel::setMargin(int margin)
{
    this->margin = margin;
}

void ScreenObjectWithLabel::setCoords(int x, int y)
{
    ScreenObject::setCoords(x, y);
    updateLabelLocation(margin);
}

void ScreenObjectWithLabel::setCoords1(int x, int y)
{
    ScreenObjectWithXtraCoords::setCoords1(x, y);
    updateLabelLocation(margin);
}

bool ScreenObjectWithLabel::isAutoSizeDisabled()
{
    return disableAutoSize;
}


