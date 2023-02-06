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
                tempVal = getNumInput(getString(Water_WellPumpMaxTimeON_STR), F("s"), (double)configStorage.config.WELLPUMPTIMEOUT/1000.0);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < configStorage.config.WELLPUMPTIMEOUT)// 0 < WELLPUMPTIMEOUT
                    {
                        debug(F("WELLPUMPTIMEOUT UPDATED: "));debug(configStorage.config.WELLPUMPTIMEOUT);debug(F(" --> "));debug(tempVal);debug('\n');
                        configStorage.config.WELLPUMPTIMEOUT = (unsigned long)(tempVal * 1000);
                        // TODO send new setting
                        changeScreenStatus(LOADPAGEWATER); // reload page with new config value
                        drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too

                    }
                    else if(0 >= configStorage.config.WELLPUMPTIMEOUT)
                    {
                        prevScreenStatus = LOADPAGEWATER;
                        changeError(InnerLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }
                }
                break;
            case 2:
                tempVal = getNumInput(getString(Water_FilterMaxTimeON_STR), F("s"), (double)configStorage.config.FILTERTIMEOUT/1000.0);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < configStorage.config.FILTERTIMEOUT)// 0 < FILTERTIMEOUT
                    {
                        debug(F("FILTERTIMEOUT UPDATED: "));debug(configStorage.config.FILTERTIMEOUT);debug(F(" --> "));debug(tempVal);debug('\n');
                        configStorage.config.FILTERTIMEOUT = (unsigned long)(tempVal * 1000);
                        // TODO send new setting
                        changeScreenStatus(LOADPAGEWATER); // reload page with new config value
                        drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too

                    }
                    else if(0 >= configStorage.config.FILTERTIMEOUT)
                    {
                        prevScreenStatus = LOADPAGEWATER;
                        changeError(InnerLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }
                }
                break;
        }
    }
    else if (btn5.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput(getString(Water_UVPumpMaxTimeON_STR), F("s"), (double)configStorage.config.UVPUMPTIMEOUT/1000.0);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < configStorage.config.UVPUMPTIMEOUT)// 0 < UVPUMPTIMEOUT
                    {
                        debug(F("UVPUMPTIMEOUT UPDATED: "));debug(configStorage.config.UVPUMPTIMEOUT);debug(F(" --> "));debug(tempVal);debug('\n');
                        configStorage.config.UVPUMPTIMEOUT = (unsigned long)(tempVal * 1000);
                        // TODO send new setting
                        changeScreenStatus(LOADPAGEWATER); // reload page with new config value
                        drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too

                    }
                    else if(0 >= configStorage.config.UVPUMPTIMEOUT)
                    {
                        prevScreenStatus = LOADPAGEWATER;
                        changeError(InnerLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }
                }
                break;

            case 2:
                tempVal = getNumInput(getString(Water_UVPumpFlow_STR), F("L/H"), configStorage.config.UVPUMPFLOW);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if(tempVal>=0) // 0 < UVPUMPFLOW
                    {
                        debug(F("UVPUMPFLOW UPDATED: "));debug(configStorage.config.UVPUMPFLOW);debug(F(" --> "));debug(tempVal);debug('\n');
                        configStorage.config.UVPUMPFLOW = (float) tempVal;
                        // TODO send new setting
                        changeScreenStatus(LOADPAGEWATER); // reload page with new config value
                        drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                    }
                    else if( tempVal < 0)
                    {
                        prevScreenStatus = LOADPAGEWATER;
                        changeError(InnerLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }

                }
                break;
        }
    }
    else if (btn6.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput(getString(Water_EndPumpMaxTimeON_STR), F("s"), (double)configStorage.config.ENDPUMPTIMEOUT/1000.0);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < configStorage.config.ENDPUMPTIMEOUT)// 0 < ENDPUMPTIMEOUT
                    {
                        debug(F("ENDPUMPTIMEOUT UPDATED: "));debug(configStorage.config.ENDPUMPTIMEOUT);debug(F(" --> "));debug(tempVal);debug('\n');
                        configStorage.config.ENDPUMPTIMEOUT = (unsigned long)(tempVal * 1000);
                        // TODO send new setting
                        changeScreenStatus(LOADPAGEWATER); // reload page with new config value
                        drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                    }
                    else if(0 >= configStorage.config.ENDPUMPTIMEOUT)
                    {
                        prevScreenStatus = LOADPAGEWATER;
                        changeError(InnerLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }
                }
                break;
        }
    }

}

//This function set and draw the title, set the font size and draws the buttons in all pages.
void drawWater()
{
    titleLabel.setString(getString(Water_Title_STR));
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    switch (page)
    {
        case 1:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(getString(Water_WellPumpMaxTimeON_STR), getString(Water_UVPumpMaxTimeON_STR), getString(Water_EndPumpMaxTimeON_STR),String(((double) configStorage.config.WELLPUMPTIMEOUT) / 1000.0) + F("s"),String(((double) configStorage.config.UVPUMPTIMEOUT) / 1000.0) + F("s"),String(((double) configStorage.config.ENDPUMPTIMEOUT) / 1000.0) + F("s"), true, true, true, fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(getString(Water_FilterMaxTimeON_STR), getString(Water_UVPumpFlow_STR), "",String(((double) configStorage.config.FILTERTIMEOUT) / 1000.0) + F("s"), String(configStorage.config.UVPUMPFLOW) + F("L/H"), "",true, true, true, fontSizes);
            break;
        default:debug(F("Page selected is out of bounds (page>2 || page<0)"));
    }
}
