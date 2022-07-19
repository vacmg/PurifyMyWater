//
// Created by Víctor on 16/06/2022.
//

#ifndef H2O_GUI_ELECTRICITY_H
#define H2O_GUI_ELECTRICITY_H


#include "Settings.h"

//this function is used for select some value related to the electricity and changing his values.
//after you click a button, the function looks which page you are, then calls the "getNumInput" function,
//and you check if the value you write after calling this last function is valid. If it is, you change
//the value, if it´s not, the value stays the same. At last, it reloads the page so the change can be seen.
void clickElectricity();

//This function set and draw the title, set the font size and draws the buttons in all pages.
void drawElectricity();

#include "Electricity.cpp"

#endif //H2O_GUI_ELECTRICITY_H
