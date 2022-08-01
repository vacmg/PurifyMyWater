//
// Created by Víctor on 16/06/2022.
//

#ifndef H2O_GUI_INTERFACE_H
#define H2O_GUI_INTERFACE_H

#include "../Settings.h"
#include "Language.h"

//This function set and draw the title, set the font size and draws the buttons in all pages.
void drawInterface();

//This function is used to handle click events in Interface screen
void clickInterface(); // TODO implement language, screen calibration & reset

#include "Interface.cpp"

#endif //H2O_GUI_INTERFACE_H
