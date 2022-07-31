//
// Created by Víctor on 16/06/2022.
//

#include "Temperature.h"

//This function set and draw the title, set the font size and draws the buttons in all pages.
void drawTemperature()
{
    titleLabel.setString(getString(Temp_Title_STR));
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    switch (page)
    {
        case 1:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(getString(Temp_RefreshInterval_STR), getString(Temp_SystemStopTemp_STR), getString(Temp_PSUFanStartTemp_STR),String(((double) config.TEMPCHECKTIME) / 1000.0) + "s",String((double) config.STOPWORKINGTEMP) + "C", String((double) config.STARTPSUTEMP) + "C",true, true, true, fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(getString(Temp_PSUFanStopTemp_STR), getString(Temp_CaseFanStartTemp_STR), getString(Temp_CaseFanStopTemp_STR),String((double) config.STOPPSUTEMP) + "C", String((double) config.STARTCASETEMP) + "C",String((double) config.STOPCASETEMP) + "C", true, true, true, fontSizes);
            break;
        default:debug(F("Page selected is out of bounds (page>2 || page<0)"));
    }
}

//this function is used for select some value related to the temperature and changing his values.
//after you click a button, the function looks which page you are, then calls the "getNumInput" function,
//and you check if the value you write after calling this last function is valid. If it is, you change
//the value, if it´s not, the value stays the same. At last, it reloads the page so the change can be seen.
void clickTemperature()
{
    double tempVal;
    if (btn4.isPressed())
    {
        switch (page)
        {
            case 1: // Temp. Refresh Rate
                tempVal = getNumInput(getString(Temp_RefreshInterval_STR), "s", (double)config.TEMPCHECKTIME/1000.0);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0)
                    {
                        debug(String(F("TEMPCHECKTIME UPDATED: ")) + config.TEMPCHECKTIME + String(F(" --> ")) +tempVal);
                        config.TEMPCHECKTIME = (unsigned long)(tempVal * 1000);
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2: //PSU Fan Stop Temp.
                tempVal = getNumInput(getString(Temp_PSUFanStopTemp_STR), "C", config.STOPPSUTEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal < config.STARTPSUTEMP)
                    {
                        debug(String(F("STOPPSUTEMP UPDATED: ")) + config.STOPPSUTEMP + String(F(" --> ")) +tempVal);
                        config.STOPPSUTEMP = (byte) tempVal;
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
                tempVal = getNumInput(getString(Temp_RefreshInterval_STR), "C", config.STOPWORKINGTEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal > config.STARTPSUTEMP && tempVal > config.STARTCASETEMP)
                    {
                        debug(String(F("STOPWORKINGTEMP UPDATED: ")) + config.STOPWORKINGTEMP + String(F(" --> ")) +tempVal);
                        config.STOPWORKINGTEMP = (byte) tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2: // Case Fan Start Temp.
                tempVal = getNumInput(getString(Temp_CaseFanStartTemp_STR), "C", config.STARTCASETEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal > config.STOPCASETEMP && tempVal < config.STOPWORKINGTEMP)
                    {
                        debug(String(F("STARTCASETEMP UPDATED: ")) + config.STARTCASETEMP + String(F(" --> ")) +tempVal);
                        config.STARTCASETEMP = (byte) tempVal;
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
                tempVal = getNumInput(getString(Temp_PSUFanStartTemp_STR), "C", config.STARTPSUTEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal > config.STOPPSUTEMP && tempVal < config.STOPWORKINGTEMP)
                    {
                        debug(String(F("STARTPSUTEMP UPDATED: ")) + config.STARTPSUTEMP + String(F(" --> ")) +tempVal);
                        config.STARTPSUTEMP = (byte) tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2: //Case Fan Stop Temp.
                tempVal = getNumInput(getString(Temp_CaseFanStopTemp_STR), "C", config.STOPCASETEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal < config.STARTCASETEMP)
                    {
                        debug(String(F("STOPPSUTEMP UPDATED: ")) + config.STOPCASETEMP + String(F(" --> ")) +tempVal);
                        config.STOPCASETEMP = (byte) tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
}
