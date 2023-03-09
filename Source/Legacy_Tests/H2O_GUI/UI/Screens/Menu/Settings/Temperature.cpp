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
            draw6ButtonsLayout(getString(Temp_RefreshInterval_STR), getString(Temp_SystemStopTemp_STR), getString(Temp_PSUFanStartTemp_STR),String(((double) configStorage.config.TEMPCHECKTIME) / 1000.0) + "s",String((double) configStorage.config.STOPWORKINGTEMP) + "C", String((double) configStorage.config.STARTPSUTEMP) + "C",true, true, true, fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(getString(Temp_PSUFanStopTemp_STR), getString(Temp_CaseFanStartTemp_STR), getString(Temp_CaseFanStopTemp_STR),String((double) configStorage.config.STOPPSUTEMP) + "C", String((double) configStorage.config.STARTCASETEMP) + "C",String((double) configStorage.config.STOPCASETEMP) + "C", true, true, true, fontSizes);
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
                tempVal = getNumInput(getString(Temp_RefreshInterval_STR), F("s"), (double)configStorage.config.TEMPCHECKTIME/1000.0);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    tempVal = (tempVal * 1000);
                    if (tempVal > 0)
                    {
                        #if !DISABLECOMM
                            char payload[20];
                            Communications::createSendMessage(payload, TEMPCHECKTIME_ID, String(tempVal).c_str());
                            if (masterComManager.sendMessage(payload))
                            {
                        #endif
                                debug(F("TEMPCHECKTIME UPDATED: "));debug(configStorage.config.TEMPCHECKTIME);debug(F(" --> "));debug(tempVal);debug('\n');
                                configStorage.config.TEMPCHECKTIME = (unsigned long)tempVal;
                        #if !DISABLECOMM
                            }
                        else
                            {
                                debug(F("ERROR: Could not send the TEMPCHECKTIME update")); //TODO error message
                            }
                        #endif
                    }
                }
                changeScreenStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2: //PSU Fan Stop Temp.
                tempVal = getNumInput(getString(Temp_PSUFanStopTemp_STR), F("C"), configStorage.config.STOPPSUTEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal < configStorage.config.STARTPSUTEMP)
                    {
                        #if !DISABLECOMM
                            char payload[20];
                            Communications::createSendMessage(payload, STOPPSUTEMP_ID, String(tempVal).c_str());
                            if (masterComManager.sendMessage(payload))
                            {
                        #endif
                                debug(F("STOPPSUTEMP UPDATED: "));debug(configStorage.config.STOPPSUTEMP);debug(F(" --> "));debug(tempVal);debug('\n');
                                configStorage.config.STOPPSUTEMP = (byte) tempVal;
                        #if !DISABLECOMM
                            }
                            else
                            {
                                debug(F("ERROR: Could not send the STOPPSUTEMP update")); //TODO error message
                            }
                        #endif
                    }
                }
                changeScreenStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
    else if (btn5.isPressed())
    {
        switch (page)
        {
            case 1: // System Stop Temp.
                tempVal = getNumInput(getString(Temp_RefreshInterval_STR), F("C"), configStorage.config.STOPWORKINGTEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal > configStorage.config.STARTPSUTEMP && tempVal > configStorage.config.STARTCASETEMP)
                    {
                        #if !DISABLECOMM
                            char payload[20];
                            Communications::createSendMessage(payload, STOPWORKINGTEMP_ID, String(tempVal).c_str());
                            if (masterComManager.sendMessage(payload))
                            {
                        #endif
                                debug(F("STOPWORKINGTEMP UPDATED: "));debug(configStorage.config.STOPWORKINGTEMP);debug(F(" --> "));debug(tempVal);debug('\n');
                                configStorage.config.STOPWORKINGTEMP = (byte) tempVal;
                        #if !DISABLECOMM
                            }
                            else
                            {
                                debug(F("ERROR: Could not send the STOPWORKINGTEMP update")); //TODO message error
                            }
                        #endif
                        // TODO send new setting
                    }
                }
                changeScreenStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2: // Case Fan Start Temp.
                tempVal = getNumInput(getString(Temp_CaseFanStartTemp_STR), F("C"), configStorage.config.STARTCASETEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal > configStorage.config.STOPCASETEMP && tempVal < configStorage.config.STOPWORKINGTEMP)
                    {
                        #if !DISABLECOMM
                            char payload[20];
                            Communications::createSendMessage(payload, STARTCASETEMP_ID, String(tempVal).c_str());
                            if (masterComManager.sendMessage(payload))
                            {
                        #endif
                                debug(F("STARTCASETEMP UPDATED: "));debug(configStorage.config.STARTCASETEMP);debug(F(" --> "));debug(tempVal);debug('\n');
                                configStorage.config.STARTCASETEMP = (byte) tempVal;
                        #if !DISABLECOMM
                            }
                            else
                            {
                            debug(F("ERROR: Could not send the STARTCASETEMP update")); //TODO error message
                            }
                        #endif

                    }
                }
                changeScreenStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
    else if (btn6.isPressed())
    {
        switch (page)
        {
            case 1: // PSU Fan Start Temp.
                tempVal = getNumInput(getString(Temp_PSUFanStartTemp_STR), F("C"), configStorage.config.STARTPSUTEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal > configStorage.config.STOPPSUTEMP && tempVal < configStorage.config.STOPWORKINGTEMP)
                    {
                        #if !DISABLECOMM
                            char payload[20];
                            Communications::createSendMessage(payload, STARTPSUTEMP_ID, String(tempVal).c_str());
                            if (masterComManager.sendMessage(payload))
                            {
                        #endif
                                debug(F("STARTPSUTEMP UPDATED: "));debug(configStorage.config.STARTPSUTEMP);debug(F(" --> "));debug(tempVal);debug('\n');
                                configStorage.config.STARTPSUTEMP = (byte) tempVal;
                        #if !DISABLECOMM
                            }
                            else
                            {
                                debug(F("ERROR: Could not send the STARTPSUTEMP update")); //TODO error message
                            }
                        #endif

                    }
                }
                changeScreenStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2: //Case Fan Stop Temp.
                tempVal = getNumInput(getString(Temp_CaseFanStopTemp_STR), F("C"), configStorage.config.STOPCASETEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal < configStorage.config.STARTCASETEMP)
                    {
                        #if !DISABLECOMM
                            char payload[20];
                            Communications::createSendMessage(payload, STOPCASETEMP_ID, String(tempVal).c_str());
                            if (masterComManager.sendMessage(payload))
                            {
                        #endif
                                debug(F("STOPPSUTEMP UPDATED: "));debug(configStorage.config.STOPCASETEMP);debug(F(" --> "));debug(tempVal);debug('\n');
                                configStorage.config.STOPCASETEMP = (byte) tempVal;
                        #if !DISABLECOMM
                            }
                            else
                            {
                                debug(F("ERROR: Could not send the STOPPSUTEMP update")); //TODO error message
                            }
                        #endif
                        
                    }
                }
                changeScreenStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
}
