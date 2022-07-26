//
// Created by Víctor on 16/06/2022.
//

#include "ExtraFunctions.h"

void drawExtraFunctions()
{
    titleLabel.setString("Extra Functions");
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
    draw6ButtonsLayout(F("AC Power Supply"), F("DC Power Supply"), F("Install Wizard"), "ON/OFF", "ON/OFF", "Start",true, true, true, fontSizes);
}

void clickExtraFunctions() // Todo implement extraFunctions
{
    /*if(btnx.isPressed())
    {
        switch (page)
        {
            case 1:
            changeScreenStatus(XXXXX);
            break;
            case x:
                ...
        }
    }*/
}