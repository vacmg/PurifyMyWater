//
// Created by Víctor on 16/06/2022.
//

#ifndef H2O_GUI_MENU_H
#define H2O_GUI_MENU_H

#include "../Screens.h"
#include "Settings/Settings.h"
#include "ExtraFunctions/ExtraFunctions.h"

//This function set and draw the title, set the font size and draws the buttons.
// Buttons mapped to: btn1 --> Settings, btn2 --> Help, btn3 --> Engineering Mode, btn4 --> Extra Functions
void drawMenu();

//This function switch pages after you click a button.
//btn1 --> Settings, btn2 --> Help, btn3 --> Engineering Mode, btn4 --> Extra Functions.
void clickMenu();

#include "Menu.cpp"

#endif //H2O_GUI_MENU_H
