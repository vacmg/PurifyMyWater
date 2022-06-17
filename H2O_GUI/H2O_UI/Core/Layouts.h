//
// Created by Víctor on 16/06/2022.
//

#ifndef H2O_GUI_LAYOUTS_H
#define H2O_GUI_LAYOUTS_H

#include "Core.h"

extern void drawBackground();
extern void draw4ButtonsLayout(String topLeft, String topRight, String bottomLeft, String bottomRight, const byte* fontSize);
extern void draw4ButtonsLayout(String topLeft, String topRight, String bottomLeft, String bottomRight);
extern void draw6ButtonsLayout(String topLeftBtn1, String centerLeftBtn2, String bottomLeftBtn3, String topRightBtn4, String centerRightBtn5, String bottomRightBtn6, bool topHelpBtn9, bool centerHelpBtn10, bool bottomHelpBtn11, const byte* fontSize);
extern void drawNumInput (String titleNumInput, String unit);


#endif //H2O_GUI_LAYOUTS_H
