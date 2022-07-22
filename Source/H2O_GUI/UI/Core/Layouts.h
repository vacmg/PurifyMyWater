//
// Created by Víctor on 16/06/2022.
//

#ifndef H2O_GUI_LAYOUTS_H
#define H2O_GUI_LAYOUTS_H

#include "Core.h"

void drawBackground();
void draw4ButtonsLayout(const String& topLeft, const String& topRight, const String& bottomLeft, const String& bottomRight, const byte* fontSize);
void draw4ButtonsLayout(const String& topLeft, const String& topRight, const String& bottomLeft, const String& bottomRight);
void draw6ButtonsLayout(const String& topLeftBtn1, const String& centerLeftBtn2, const String& bottomLeftBtn3, const String& topRightBtn4, const String& centerRightBtn5, const String& bottomRightBtn6, bool topHelpBtn9, bool centerHelpBtn10, bool bottomHelpBtn11, const byte* fontSize);
void drawNumInput(const String& titleNumInput, const String& unit);

#include "Layouts.cpp"

#endif //H2O_GUI_LAYOUTS_H
