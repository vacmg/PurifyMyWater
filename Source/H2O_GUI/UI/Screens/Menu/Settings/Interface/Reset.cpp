//
// Created by 34611 on 10/09/2022.
//

#include "Reset.h"

void drawReset()
{
    debug(F("getPath: "));debug(getPath(ResetPopup_PATH));debug('\n');
    drawBoolPopup(getString(Interface_ResetStart_STR), getPath(ResetPopup_PATH), getString(YES_STR),getString(NO_STR));
}

void clickReset()
{
    if(btn1.isPressed()) // Yes, do reset
    {
        performReset();
    }
    else if(btn2.isPressed()) // No, load interface
    {
        changeScreenStatus(LOADPAGEINTERFACE);
        drawBackground();
    }
}

void performReset() //TODO perform reset
{
    debug(F("Se acaba de hacer el reset(TODO)\n"));
}