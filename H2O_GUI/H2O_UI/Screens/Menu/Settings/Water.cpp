//
// Created by Víctor on 16/06/2022.
//

#include "Water.h"

void clickWater()
{
    double tempVal;
    if (btn4.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput("Well Pump max time on", "s", WELLPUMPTIMEOUT);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < WELLPUMPTIMEOUT)// 0 < WELLPUMPTIMEOUT
                    {
                        debug(String(F("WELLPUMPTIMEOUT UPDATED: ")) + WELLPUMPTIMEOUT + String(F(" --> ")) +tempVal);
                        WELLPUMPTIMEOUT = (long) tempVal * 1000;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
            case 2:
                tempVal = getNumInput("Filter max time on", "s", FILTERTIMEOUT);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < FILTERTIMEOUT)// 0 < FILTERTIMEOUT
                    {
                        debug(String(F("FILTERTIMEOUT UPDATED: ")) + FILTERTIMEOUT + String(F(" --> ")) + tempVal);
                        FILTERTIMEOUT = (long) tempVal * 1000;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
    else if (btn5.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput("UV Pump max time on", "s", UVPUMPTIMEOUT);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < UVPUMPTIMEOUT)// 0 < UVPUMPTIMEOUT
                    {
                        debug(String(F("UVPUMPTIMEOUT UPDATED: ")) + UVPUMPTIMEOUT + String(F(" --> ")) + tempVal);
                        UVPUMPTIMEOUT = (long) tempVal * 1000;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2: //TODO: por hacer
                tempVal = getNumInput("UV Pump flow", "L/H", UVPUMPFLOW);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(String(F("UVPUMPFLOW UPDATED: ")) + UVPUMPFLOW + String(F(" --> ")) + tempVal);
                    UVPUMPFLOW = (long) tempVal;
                    // TODO send new setting
                }
                changeStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
    else if (btn6.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput("End Pump max time on", "s", ENDPUMPTIMEOUT);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < ENDPUMPTIMEOUT)// 0 < ENDPUMPTIMEOUT
                    {
                        debug(String(F("ENDPUMPTIMEOUT UPDATED: ")) + ENDPUMPTIMEOUT + String(F(" --> ")) + tempVal);
                        ENDPUMPTIMEOUT = (long) tempVal * 1000;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }

}

void drawWater()
{
    titleLabel.setString("Water Settings");
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    switch (page)
    {
        case 1:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(F("Well Pump max time ON"), F("UV Pump max time ON"), F("End Pump max time ON"),String(((double) WELLPUMPTIMEOUT) / 1000) + F("s"),String(((double) UVPUMPTIMEOUT) / 1000) + F("s"),String(((double) ENDPUMPTIMEOUT) / 1000) + F("s"), true, true, true, fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(F("Filter max time ON"), F("UV Pump flow"), "",String(((double) FILTERTIMEOUT) / 1000) + F("s"), String(UVPUMPFLOW) + F("L/H"), "",true, true, true, fontSizes);
            break;
    }
}
