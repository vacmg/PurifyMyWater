//
// Created by Víctor on 16/06/2022.
//

#ifndef H2O_GUI_UTILS_H
#define H2O_GUI_UTILS_H


#include "Core.h"

extern void setFontSizeArray(byte* fontSizeArray, byte tl, byte cl, byte bl, byte tr, byte cr, byte br);
extern void setFontSizeArray(byte* fontSizeArray, byte tl, byte tr, byte bl, byte br);
extern double getNumInput(String titleNumInput, String unit, double value);
extern void setRotation(byte rotation);


#endif //H2O_GUI_UTILS_H
