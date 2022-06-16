//
// Created by Víctor on 16/06/2022.
//

#include "Temperature.h"

void drawTemperature() {
    titleLabel.setString("Temperature");
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    switch (page)
    {
        case 1:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(F("Temp. Refresh Rate "), F("System Stop Temp."), F("PSU Fan Start Temp."), String(((double)TEMPCHECKTIME)/1000) + "s", String((double)STOPWORKINGTEMP) + "C", String((double)STARTPSUTEMP) + "C",
                               true, true, true, fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(F("PSU Fan Stop Temp."), F("Case Fan Start Temp."), F("Case Fan Stop Temp."), String((double)STOPPSUTEMP)+"C", String((double)STARTCASETEMP)+"C",
                               String((double)STOPCASETEMP)+"C", true, true, true, fontSizes);
            break;
    }
}

void clickTemperature()
{
    double tempVal;
    if (btn4.isPressed())
    {
        switch (page)
        {
            case 1: // Temp. Refresh Rate
                tempVal = getNumInput("Temp. Refresh Rate", "s", TEMPCHECKTIME);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0)
                    {
                        debug(String(F("TEMPCHECKTIME UPDATED: ")) + TEMPCHECKTIME + String(F(" --> ")) +
                              tempVal);
                        TEMPCHECKTIME = tempVal * 1000;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2: //PSU Fan Stop Temp.
                tempVal = getNumInput("PSU Fan Stop Temp.", "C", STOPPSUTEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal < STARTPSUTEMP)
                    {
                        debug(String(F("STOPPSUTEMP UPDATED: ")) + STOPPSUTEMP + String(F(" --> ")) +
                              tempVal);
                        STOPPSUTEMP = (double)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
    else if (btn5.isPressed())
    {
        switch (page)
        {
            case 1: // System Stop Temp.
                tempVal = getNumInput("Temp. Refresh Rate", "C", STOPWORKINGTEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal>STARTPSUTEMP && tempVal>STARTCASETEMP)
                    {
                        debug(String(F("STOPWORKINGTEMP UPDATED: ")) + STOPWORKINGTEMP + String(F(" --> ")) +
                              tempVal);
                        STOPWORKINGTEMP = (double)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2: // Case Fan Start Temp.
                tempVal = getNumInput("Case Fan Start Temp.", "C", STARTCASETEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0  && tempVal > STOPCASETEMP  && tempVal < STOPWORKINGTEMP)
                    {
                        debug(String(F("STARTCASETEMP UPDATED: ")) + STARTCASETEMP + String(F(" --> ")) +
                              tempVal);
                        STARTCASETEMP = (double)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
    else if (btn6.isPressed())
    {
        switch (page)
        {
            case 1: // PSU Fan Start Temp.
                tempVal = getNumInput("PSU Fan Start Temp.", "C", STARTPSUTEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0  && tempVal > STOPPSUTEMP  && tempVal < STOPWORKINGTEMP)
                    {
                        debug(String(F("STARTPSUTEMP UPDATED: ")) + STARTPSUTEMP + String(F(" --> ")) +
                              tempVal);
                        STARTPSUTEMP = (double)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2: //Case Fan Stop Temp.
                tempVal = getNumInput("Case Fan Stop Temp.", "C", STOPCASETEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal < STARTCASETEMP)
                    {
                        debug(String(F("STOPPSUTEMP UPDATED: ")) + STOPCASETEMP + String(F(" --> ")) +
                              tempVal);
                        STOPCASETEMP = (double)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }

}
