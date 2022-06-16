//
// Created by Víctor on 16/06/2022.
//

#include "Settings.h"

void drawSettings()
{
    //Title Menu
    titleLabel.setString("Settings");
    my_lcd.draw(&title);
    //Layout4Buttons
    byte fontSize[4];
    setFontSizeArray(fontSize,2,2,2,2);
    draw4ButtonsLayout(F("Electricity"),F("Water"),F("Interface"),F("Temperature"),fontSize);
}

void clickSettings()
{
    if(btn1.isPressed())
    {
        debug(F("Electricity button pressed"));
        changeStatus(LOADELECTRICITY);
    }

    else if(btn2.isPressed())
    {
        debug(F("Water button pressed")); // Go to LOADWATER
        changeStatus(LOADWATER);
    }
    else if(btn3.isPressed()) // Go to LOADINTERFACE
    {
        debug(F("Interface button pressed"));
        changeStatus(LOADINTERFACE);
    }
    else if(btn4.isPressed())
    {
        changeStatus(LOADTEMPERATURE);
    }
}