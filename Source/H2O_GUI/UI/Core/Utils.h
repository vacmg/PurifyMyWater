//
// Created by Víctor on 16/06/2022.
//

#ifndef H2O_GUI_UTILS_H
#define H2O_GUI_UTILS_H

#include "Core.h"

void setFontSizeArray(byte* fontSizeArray, byte tl, byte cl, byte bl, byte tr, byte cr, byte br);
void setFontSizeArray(byte* fontSizeArray, byte tl, byte tr, byte bl, byte br);
double getNumInput(const String& titleNumInput, const String& unit, double value, byte decimalPlaces);
double getNumInput(const String& titleNumInput, const String& unit, double value);
void setRotation(byte rotation);

bool loadLanguage();

#include "Utils.cpp"

#endif //H2O_GUI_UTILS_H
