//
// Created by Víctor on 16/06/2022.
//

#include "ExtraFunctions.h"

void drawExtraFunctionsForeground()
{
    if(configStorage.config.workingMode==ACPSU_Mode)
    {
        btn4.setSecondaryColor(0,255,0);
        btn5.setSecondaryColor(255,0,0);
    }
    else if (configStorage.config.workingMode==DCPSU_Mode)
    {
        btn4.setSecondaryColor(255,0,0);
        btn5.setSecondaryColor(0,255,0);
    }
    else if(configStorage.config.workingMode==Purification_On_Mode || configStorage.config.workingMode==Purification_Off_Mode)
    {
        btn4.setSecondaryColor(255,0,0);
        btn5.setSecondaryColor(255,0,0);
    }
    btn4.enableAutoSize(false);
    btn5.enableAutoSize(false);

    label.setString(configStorage.config.workingMode==ACPSU_Mode?getString(ON_STR):getString(OFF_STR));
    label.setFontSize(2);
    btn4.setCoords(280,95);
    btn4.setCoords1(450,135);
    my_lcd.draw(&btn4);
    btn4.enableAutoSize(true);

    label.setString(configStorage.config.workingMode==DCPSU_Mode?getString(ON_STR):getString(OFF_STR));
    label.setFontSize(2);
    btn5.setCoords(280,155);
    btn5.setCoords1(450,195);
    my_lcd.draw(&btn5);
    btn5.enableAutoSize(true);

    btn4.setSecondaryColor(255,255,255);
    btn5.setSecondaryColor(255,255,255);
}

void drawExtraFunctionsBackground()
{
    titleLabel.setString(getString(ExtraFunctions_Title_STR));
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
    draw6ButtonsLayout(getString(ExtraFunctions_ACPSU_STR), getString(ExtraFunctions_DCPSU_STR), getString(ExtraFunctions_InstallWizard_STR),"", "",getString(ExtraFunctions_StartInstallWizard_STR),true, true, true, fontSizes); // TODO implement ExtraFunction logic
    drawExtraFunctionsForeground();
}

void clickExtraFunctions()
{
    if (btn4.isPressed()) // ACPSU button
    {
        debug("ACPSU Button Pressed\n");
        if (configStorage.config.workingMode!=ACPSU_Mode)
        {
            debug(F("configStorage.config.workingMode changed from "));debug(workingModeToString(configStorage.config.workingMode));debug(F(" to "));debug(workingModeToString(ACPSU_Mode));debug('\n');
            configStorage.config.workingMode = ACPSU_Mode; //TODO send warning message & send message to master
        }
        else if (configStorage.config.workingMode==ACPSU_Mode)
        {
            debug(F("configStorage.config.workingMode changed from "));debug(workingModeToString(configStorage.config.workingMode));debug(F(" to "));debug(workingModeToString(Purification_Off_Mode));debug('\n');
            configStorage.config.workingMode = Purification_Off_Mode; //TODO send warning message & send message to master
        }
        drawExtraFunctionsForeground();

    }
    else if (btn5.isPressed()) // DCPSUButton
    {
        debug("DCPSU Button Pressed\n");
        if (configStorage.config.workingMode!=DCPSU_Mode)
        {
            debug(F("configStorage.config.workingMode changed from "));debug(workingModeToString(configStorage.config.workingMode));debug(F(" to "));debug(workingModeToString(DCPSU_Mode));debug('\n');
            configStorage.config.workingMode = DCPSU_Mode; //TODO send warning message & send message to master
        }
        else if (configStorage.config.workingMode==DCPSU_Mode)
        {
            debug(F("configStorage.config.workingMode changed from "));debug(workingModeToString(configStorage.config.workingMode));debug(F(" to "));debug(workingModeToString(Purification_Off_Mode));debug('\n');
            configStorage.config.workingMode = Purification_Off_Mode; //TODO send warning message & send message to master
        }
        drawExtraFunctionsForeground();
    }
    /*else if (btn6.isPressed()) // Start Install Wizard button
    {

    }*/
}