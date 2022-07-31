//
// Created by Víctor on 16/06/2022.
//

#include "Settings.h"

//This function set and draw the title, set the font size and draws the buttons.
void drawSettings()
{
    //Title Menu
    titleLabel.setString(getString(Settings_Title_STR));
    my_lcd.draw(&title);
    //Layout4Buttons
    byte fontSize[4];
    setFontSizeArray(fontSize, 2, 2, 2, 2);
    draw4ButtonsLayout(getString(Settings_ElectricityBtn_STR), getString(Settings_WaterBtn_STR), getString(Settings_InterfaceBtn_STR),getString(Settings_TemperatureBtn_STR), fontSize);
}

//This function leads you to the four different settings you can manage. It works in a single page,
//and after you pressed one of the four buttons, the function change the status to load page.
void clickSettings()
{
    if (btn1.isPressed()) // Go to LOADELECTRICITY
    {
        debug(F("Electricity button pressed"));
        changeStatus(LOADELECTRICITY);
    }
    else if (btn2.isPressed()) // Go to LOADWATER
    {
        debug(F("Water button pressed"));
        changeStatus(LOADWATER);
    }
    else if (btn3.isPressed()) // Go to LOADINTERFACE
    {
        debug(F("Interface button pressed"));
        changeStatus(LOADINTERFACE);
    }
    else if (btn4.isPressed()) // Go to LOADTEMPERATURE
    {
        debug(F("Temperature button pressed"));
        changeStatus(LOADTEMPERATURE);
    }
}
