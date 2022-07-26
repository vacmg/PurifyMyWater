    //
// Created by Víctor on 16/06/2022.
//

#include "Water.h"

//this function is used for select some value related to the water and changing his values.
//after you click a button, the function looks which page you are, then calls the "getNumInput" function,
//and you check if the value you write after calling this last function is valid. If it is, you change
//the value, if it´s not, the value stays the same. At last, it reloads the page so the change can be seen.
void clickWater()
{
    double tempVal;
    if (btn4.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput(F("Well Pump max time on"), F("s"), (double)config.WELLPUMPTIMEOUT/1000.0);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < config.WELLPUMPTIMEOUT)// 0 < WELLPUMPTIMEOUT
                    {
                        debug(F("WELLPUMPTIMEOUT UPDATED: "));debug(config.WELLPUMPTIMEOUT);debug(F(" --> "));debug(tempVal);debug('\n');
                        config.WELLPUMPTIMEOUT = (unsigned long)(tempVal * 1000);
                        // TODO send new setting
                    }
                }
                changeScreenStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
            case 2:
                tempVal = getNumInput(F("Filter max time on"), F("s"), (double)config.FILTERTIMEOUT/1000.0);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < config.FILTERTIMEOUT)// 0 < FILTERTIMEOUT
                    {
                        debug(F("FILTERTIMEOUT UPDATED: "));debug(config.FILTERTIMEOUT);debug(F(" --> "));debug(tempVal);debug('\n');
                        config.FILTERTIMEOUT = (unsigned long)(tempVal * 1000);
                        // TODO send new setting
                    }
                }
                changeScreenStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
    else if (btn5.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput(F("UV Pump max time on"), F("s"), (double)config.UVPUMPTIMEOUT/1000.0);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < config.UVPUMPTIMEOUT)// 0 < UVPUMPTIMEOUT
                    {
                        debug(F("UVPUMPTIMEOUT UPDATED: "));debug(config.UVPUMPTIMEOUT);debug(F(" --> "));debug(tempVal);debug('\n');
                        config.UVPUMPTIMEOUT = (unsigned long)(tempVal * 1000);
                        // TODO send new setting
                    }
                }
                changeScreenStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2:
                tempVal = getNumInput(F("UV Pump flow"), F("L/H"), config.UVPUMPFLOW);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if(tempVal>=0) // 0 < UVPUMPFLOW
                    {
                        debug(F("UVPUMPFLOW UPDATED: "));debug(config.UVPUMPFLOW);debug(F(" --> "));debug(tempVal);debug('\n');
                        config.UVPUMPFLOW = (float) tempVal;
                        // TODO send new setting
                    }

                }
                changeScreenStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
    else if (btn6.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput(F("End Pump max time on"), F("s"), (double)config.ENDPUMPTIMEOUT/1000.0);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < config.ENDPUMPTIMEOUT)// 0 < ENDPUMPTIMEOUT
                    {
                        debug(F("ENDPUMPTIMEOUT UPDATED: "));debug(config.ENDPUMPTIMEOUT);debug(F(" --> "));debug(tempVal);debug('\n');
                        config.ENDPUMPTIMEOUT = (unsigned long)(tempVal * 1000);
                        // TODO send new setting
                    }
                }
                changeScreenStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }

}

//This function set and draw the title, set the font size and draws the buttons in all pages.
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
            draw6ButtonsLayout(F("Well Pump max time ON"), F("UV Pump max time ON"), F("End Pump max time ON"),String(((double) config.WELLPUMPTIMEOUT) / 1000.0) + F("s"),String(((double) config.UVPUMPTIMEOUT) / 1000.0) + F("s"),String(((double) config.ENDPUMPTIMEOUT) / 1000.0) + F("s"), true, true, true, fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(F("Filter max time ON"), F("UV Pump flow"), "",String(((double) config.FILTERTIMEOUT) / 1000.0) + F("s"), String(config.UVPUMPFLOW) + F("L/H"), "",true, true, true, fontSizes);
            break;
    }
}
