//
// Created by Víctor on 16/06/2022.
//

#include "Menu.h"

//This function set and draw the title, set the font size and draws the buttons.
// Buttons mapped to: btn1 --> Settings, btn2 --> Help, btn3 --> Engineering Mode, btn4 --> Extra Functions
void drawMenu()
{
    //Title Menu
    titleLabel.setString(getString(Menu_Title_STR));
    my_lcd.draw(&title);
    //Layout4Buttons
    byte fontSize[4];
    setFontSizeArray(fontSize, 2, 2, 2, 2);
    draw4ButtonsLayout(getString(SettingsBtn_STR), getString(HelpBtn_STR), getString(EngineeringBtn_STR), getString(ExtraFunctionsBtn), fontSize);
}

//This function switch pages after you click a button.
//btn1 --> Settings, btn2 --> Help, btn3 --> Engineering Mode, btn4 --> Extra Functions.
void clickMenu()
{
    if (btn1.isPressed()) //Settings
    {
        debug(F("Settings button pressed\n"));
        changeScreenStatus(LOADSETTINGS);
    }
    else if (btn2.isPressed()) //Help
    {
        debug(F("Help button pressed\n"));
        changeScreenStatus(LOADHELP);
    }
    else if (btn3.isPressed()) //Engineering Mode
    {
        debug(F("Engineering mode button pressed\n"));
        changeScreenStatus(LOADENGINEERINGMODE);
    }
    else if (btn4.isPressed()) //Extra Functions
    {
        debug(F("Extra functions button pressed\n"));
        changeScreenStatus(LOADEXTRAFUNCTIONS);
    }
}
