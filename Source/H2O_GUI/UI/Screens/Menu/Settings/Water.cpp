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
                        char payload[10];
                        Communications::createSendMessage(payload, WELLPUMPTIMEOUT_ID, String(tempVal).c_str());
                        if (masterComManager.sendMessage(payload))
                        {
                            debug(F("WELLPUMPTIMEOUT UPDATED: "));debug(configStorage.config.WELLPUMPTIMEOUT);debug(F(" --> "));debug(tempVal);debug('\n');
                            configStorage.config.WELLPUMPTIMEOUT = (unsigned long)(tempVal * 1000);
                        }
                        else
                        {
                            debug(F("ERROR: Could not send the WELLPUMPTIMEOUT update")); // TODO: error message
                        }
                    }
                }
                changeScreenStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
            case 2:
                tempVal = getNumInput(getString(Water_FilterMaxTimeON_STR), F("s"), (double)configStorage.config.FILTERTIMEOUT/1000.0);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < configStorage.config.FILTERTIMEOUT)// 0 < FILTERTIMEOUT
                    {
                        char payload[10];
                        Communications::createSendMessage(payload, FILTERTIMEOUT_ID, String(tempVal).c_str());
                        if (masterComManager.sendMessage(payload))
                        {
                            debug(F("FILTERTIMEOUT UPDATED: "));debug(configStorage.config.FILTERTIMEOUT);debug(F(" --> "));debug(tempVal);debug('\n');
                            configStorage.config.FILTERTIMEOUT = (unsigned long)(tempVal * 1000);
                        }
                        else
                        {
                            debug(F("ERROR: Could not send the FILTERTIMEOUT update")); // TODO: error message
                        }
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
                tempVal = getNumInput(getString(Water_UVPumpMaxTimeON_STR), F("s"), (double)configStorage.config.UVPUMPTIMEOUT/1000.0);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < configStorage.config.UVPUMPTIMEOUT)// 0 < UVPUMPTIMEOUT
                    {
                        char payload[10];
                        Communications::createSendMessage(payload, UVPUMPTIMEOUT_ID, String(tempVal).c_str());
                        if (masterComManager.sendMessage(payload))
                        {
                            debug(F("UVPUMPTIMEOUT UPDATED: "));debug(configStorage.config.UVPUMPTIMEOUT);debug(F(" --> "));debug(tempVal);debug('\n');
                            configStorage.config.UVPUMPTIMEOUT = (unsigned long)(tempVal * 1000);
                        }
                        else
                        {
                            debug(F("ERROR: Could not send the UVPUMPTIMEOUT update")); // TODO: error message
                        }
                    }
                }
                changeScreenStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2:
                tempVal = getNumInput(getString(Water_UVPumpFlow_STR), F("L/H"), configStorage.config.UVPUMPFLOW);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if(tempVal>=0) // 0 < UVPUMPFLOW
                    {
                        char payload[10];
                        Communications::createSendMessage(payload, UVPUMPFLOW_ID, String(tempVal).c_str());
                        if (masterComManager.sendMessage(payload))
                        {
                            debug(F("UVPUMPFLOW UPDATED: "));debug(configStorage.config.UVPUMPFLOW);debug(F(" --> "));debug(tempVal);debug('\n');
                            configStorage.config.UVPUMPFLOW = (float) tempVal;
                        }
                        else
                        {
                            debug(F("ERROR: Could not send the UVPUMPFLOW update")); // TODO: error message
                        }
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
                tempVal = getNumInput(getString(Water_EndPumpMaxTimeON_STR), F("s"), (double)configStorage.config.ENDPUMPTIMEOUT/1000.0);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < configStorage.config.ENDPUMPTIMEOUT)// 0 < ENDPUMPTIMEOUT
                    {
                        char payload[10];
                        Communications::createSendMessage(payload, ENDPUMPTIMEOUT_ID, String(tempVal).c_str());
                        if (masterComManager.sendMessage(payload))
                        {
                            debug(F("ENDPUMPTIMEOUT UPDATED: "));debug(configStorage.config.ENDPUMPTIMEOUT);debug(F(" --> "));debug(tempVal);debug('\n');
                            configStorage.config.ENDPUMPTIMEOUT = (unsigned long)(tempVal * 1000);
                        }
                        else
                        {
                            debug(F("ERROR: Could not send the ENDPUMPTIMEOUT update")); // TODO: error message
                        }
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
