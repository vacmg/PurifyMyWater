//
// Created by Víctor on 16/06/2022.
//

#ifndef H2O_GUI_INTERFACE_H
#define H2O_GUI_INTERFACE_H

#include "Settings.h"

//This function set and draw the title, set the font size and draws the buttons in all pages.
void drawInterface();

//this function is used for select some value related to the interface and allows you to select between different
//options each headland has.
void clickInterface(); // TODO implement language, screen rotation, screen calibration & reset

#include "Interface.cpp"

#endif //H2O_GUI_INTERFACE_H
