//
// Created by Víctor on 16/06/2022.
//

#ifndef H2O_GUI_SETTINGS_H
#define H2O_GUI_SETTINGS_H

#include "../Menu.h"
#include "Electricity.h"
#include "Interface/Interface.h"
#include "Temperature.h"
#include "Water.h"

//This function set and draw the title, set the font size and draws the buttons.
void drawSettings();

//This function leads you to the four different settings you can manage. It works in a single page,
//and after you pressed one of the four buttons, the function change the status to load page.
void clickSettings();

#include "Settings.cpp"

#endif //H2O_GUI_SETTINGS_H
