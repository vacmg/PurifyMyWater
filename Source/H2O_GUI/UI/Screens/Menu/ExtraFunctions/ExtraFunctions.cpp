//
// Created by Víctor on 16/06/2022.
//

#include "ExtraFunctions.h"

void drawExtraFunctions()
{
    titleLabel.setString(getString(ExtraFunctions_Title_STR));
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
    draw6ButtonsLayout(getString(ExtraFunctions_ACPSU_STR), getString(ExtraFunctions_DCPSU_STR), getString(ExtraFunctions_InstallWizard_STR), "ON/OFF", "ON/OFF",getString(ExtraFunctions_StartInstallWizard_STR),true, true, true, fontSizes); // TODO implement ExtraFunction logic
}

void clickExtraFunctions() // Todo implement extraFunctions
{
    /*if(btnx.isPressed())
    {
        switch (page)
        {
            case 1:
            changeStatus(XXXXX);
            break;
            case x:
                ...
        }
    }*/
}