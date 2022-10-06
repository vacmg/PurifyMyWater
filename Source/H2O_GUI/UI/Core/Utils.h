//
// Created by Víctor on 16/06/2022.
//

#ifndef H2O_GUI_UTILS_H
#define H2O_GUI_UTILS_H

#include "Core.h"

void setFontSizeArray(byte* fontSizeArray, byte tl, byte cl, byte bl, byte tr, byte cr, byte br);
void setFontSizeArray(byte* fontSizeArray, byte tl, byte tr, byte bl, byte br);
double getNumInput(const String& titleNumInput, const String& unit, double value, byte decimalPlaces, double upperBound, double innerBound, enum ScreenStatus returnTo);
double getNumInput(const String& titleNumInput, const String& unit, double value, byte decimalPlaces);
double getNumInput(const String& titleNumInput, const String& unit, double value);
double getNumInput(const String& titleNumInput, const String& unit, double value, double upperBound, double innerBound, enum ScreenStatus returnTo);


void okPopup(const String& headerText, const String& messagePath, const String& btn1Text);
bool boolPopup(const String& headerText, const String& messagePath, const String& btn1TrueText, const String& btn2FalseText);

void setRotation(enum Rotation rotation);

#include "Utils.cpp"

#endif //H2O_GUI_UTILS_H
