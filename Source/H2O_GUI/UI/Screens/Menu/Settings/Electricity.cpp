//
// Created by Víctor on 16/06/2022.
//

#include "Electricity.h"

//this function is used for select some value related to the electricity and changing his values.
//after you click a button, the function looks which page you are, then calls the "getNumInput" function,
//and you check if the value you write after calling this last function is valid. If it is, you change
//the value, if it´s not, the value stays the same. At last, it reloads the page so the change can be seen.
void clickElectricity()
{
    double tempVal;
    if (btn4.isPressed())
    {
        switch (page)
        {
            case 1: // Start charging voltage
            prevScreenStatus = LOADPAGEELECTRICITY;
                tempVal = getNumInput(getString(Electricity_StartChargingVoltage_STR), F("V"), configStorage.config.STARTCHARGINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (configStorage.config.STOPWORKINGVOLTAGE < tempVal && tempVal < configStorage.config.STOPCHARGINGVOLTAGE)
                    {
                    #if !DISABLECOMM
                        char payload[20];
                        Communications::createSendMessage(payload, STARTCHARGINGVOLTAGE_ID, String(tempVal).c_str());
                        if (masterComManager.sendMessage(payload))
                        {
                    #endif
                            debug(F("STARTCHARGINGVOLTAGE UPDATED: "));debug(configStorage.config.STARTCHARGINGVOLTAGE);debug(F(" --> "));debug(tempVal);debug('\n');
                            configStorage.config.STARTCHARGINGVOLTAGE = (float) tempVal;
                    #if !DISABLECOMM
                        }
                        else
                        {
                            debug(F("ERROR: Could not send the STARTCHARGINGVOLTAGE update")); // TODO: error message
                        }
                    #endif
                    }
                }
                changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2: //page 2
                tempVal = getNumInput(getString(Electricity_StartWorkingVoltage_STR), F("V"), configStorage.config.STARTWORKINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (configStorage.config.STARTCHARGINGVOLTAGE < tempVal && tempVal < configStorage.config.STOPCHARGINGVOLTAGE)// STARTCHARGINGVOLTAGE < STARTWORKINGVOLTAGE < STOPCHARGINGVOLTAGE
                    {
                    #if !DISABLECOMM
                        char payload[20];
                        Communications::createSendMessage(payload, STARTWORKINGVOLTAGE_ID, String(tempVal).c_str());
                        if (masterComManager.sendMessage(payload))
                        {
                    #endif
                            debug(F("STARTWORKINGVOLTAGE UPDATED: "));debug(configStorage.config.STARTWORKINGVOLTAGE);debug(F(" --> "));debug(tempVal);debug('\n');
                            configStorage.config.STARTWORKINGVOLTAGE = (float)tempVal;
                    #if !DISABLECOMM
                        }
                        else
                        {
                            debug(F("ERROR: Could not send the STARTWORKINGVOLTAGE update")); // TODO: error message
                        }
                    #endif
                    }
                }
                changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 3:
                tempVal = getNumInput(getString(Electricity_ACAmmeterSensitivity_STR), F(""), configStorage.config.ACAMMSENSITIVITY,4);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                #if !DISABLECOMM
                    char payload[20];
                    Communications::createSendMessage(payload, ACAMMSENSITIVITY_ID, String(tempVal).c_str());
                    if (masterComManager.sendMessage(payload))
                    {
                #endif
                        debug(F("ACAMMSENSITIVITY UPDATED: "));debug(configStorage.config.ACAMMSENSITIVITY);debug(F(" --> "));debug(tempVal);debug('\n');
                        configStorage.config.ACAMMSENSITIVITY = tempVal;
                #if !DISABLECOMM
                    }
                    else
                    {
                        debug(F("ERROR: Could not send the ACAMMSENSITIVITY update")); // TODO: error message
                    }
                #endif
                }
                changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 4:
                tempVal = getNumInput(getString(Electricity_DCAmmeterZero_STR), F(""), configStorage.config.DCAMMZERO,4);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                #if !DISABLECOMM
                    char payload[20];
                    Communications::createSendMessage(payload, DCAMMZERO_ID, String(tempVal).c_str());
                    if (masterComManager.sendMessage(payload))
                    {
                #endif
                        debug(F(" UPDATED: DCAMMZERO"));debug(configStorage.config.DCAMMZERO);debug(F(" --> "));debug(tempVal);debug('\n');
                        configStorage.config.DCAMMZERO = tempVal;
                #if !DISABLECOMM
                    }
                    else
                    {
                        debug(F("ERROR: Could not send the DCAMMZERO update")); // TODO: error message
                    }
                #endif
                }
                changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }

    }
    else if (btn5.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput(getString(Electricity_StopChargingVoltage_STR), F("V"), configStorage.config.STOPCHARGINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (configStorage.config.STARTCHARGINGVOLTAGE + 1 < tempVal && tempVal <MAXCAPACITORSALLOWEDVOLTAGE)// STARTCHARGINGVOLTAGE+1 < STOPCHARGINGVOLTAGE < MAXCAPACITORSALLOWEDVOLTAGE
                    {
                    #if !DISABLECOMM
                        char payload[20];
                        Communications::createSendMessage(payload, STOPCHARGINGVOLTAGE_ID, String(tempVal).c_str());
                        if (masterComManager.sendMessage(payload))
                        {
                    #endif
                            debug(F("STOPCHARGINGVOLTAGE UPDATED: "));debug(configStorage.config.STOPCHARGINGVOLTAGE);debug(F(" --> "));debug(tempVal);debug('\n');
                            configStorage.config.STOPCHARGINGVOLTAGE = (float)tempVal;
                    #if !DISABLECOMM
                        }
                        else
                        {
                            debug(F("ERROR: Could not send the STOPCHARGINGVOLTAGE update")); // TODO: error message
                        }
                    #endif
                    }
                }
                changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2:
                tempVal = getNumInput(getString(Electricity_StopWorkingVoltage_STR), F("V"), configStorage.config.STOPWORKINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (MINSYSTEMALLOWEDVOLTAGE < tempVal && tempVal < configStorage.config.STARTCHARGINGVOLTAGE - 1)// MINSYSTEMALLOWEDVOLTAGE < STOPWORKINGVOLTAGE < STARTCHARGINGVOLTAGE-1
                    {
                    #if !DISABLECOMM
                        char payload[20];
                        Communications::createSendMessage(payload, STOPWORKINGVOLTAGE_ID, String(tempVal).c_str());
                        if (masterComManager.sendMessage(payload))
                        {
                    #endif
                            debug(F("STOPWORKINGVOLTAGE UPDATED: "));debug(configStorage.config.STOPWORKINGVOLTAGE);debug(F(" --> "));debug(tempVal);debug('\n');
                            configStorage.config.STOPWORKINGVOLTAGE = (float)tempVal;
                    #if !DISABLECOMM
                        }
                        else
                        {
                            debug(F("ERROR: Could not send the STOPWORKINGVOLTAGE update")); // TODO: error message
                        }
                    #endif
                    }
                }
                changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 3:
                tempVal = getNumInput(getString(Electricity_ACAmmeterZero_STR), F(""), configStorage.config.ACAMMZERO,4);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                #if !DISABLECOMM
                    char payload[20];
                    Communications::createSendMessage(payload, ACAMMZERO_ID, String(tempVal).c_str());
                    if (masterComManager.sendMessage(payload))
                    {
                #endif
                        debug(F("ACAMMZERO UPDATED: "));debug(configStorage.config.ACAMMZERO);debug(F(" --> "));debug(tempVal);debug('\n');
                        configStorage.config.ACAMMZERO = tempVal;
                #if !DISABLECOMM
                    }
                    else
                    {
                        debug(F("ERROR: Could not send the ACAMMZERO update")); // TODO: error message
                    }
                #endif
                }
                changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
    else if (btn6.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput(getString(Electricity_UVCurrent_STR), F("A"), configStorage.config.ESTIMATEDUVAMPERAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < tempVal && tempVal < MAXUVAMPERAGE)//0 < ESTIMATEDUVAMPERAGE < MAXUVAMPERAGE
                    {
                    #if !DISABLECOMM
                        char payload[20];
                        Communications::createSendMessage(payload, ESTIMATEDUVAMPERAGE_ID, String(tempVal).c_str());
                        if (masterComManager.sendMessage(payload))
                        {
                    #endif
                            debug(F("ESTIMATEDUVAMPERAGE UPDATED: "));debug(configStorage.config.ESTIMATEDUVAMPERAGE);debug(F(" --> "));debug(tempVal);debug('\n');
                            configStorage.config.ESTIMATEDUVAMPERAGE = (float)tempVal;
                    #if !DISABLECOMM
                        }
                        else
                        {
                            debug(F("ERROR: Could not send the ESTIMATEDUVAMPERAGE update")); // TODO: error message
                        }
                    #endif
                    }
                }
                changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2:
                tempVal = getNumInput(getString(Electricity_ACInverterFrequency_STR), F("Hz"), configStorage.config.ACFREQUENCY);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (50 < tempVal && tempVal < 60)// 50 <= ACFREQUENCY <= 60
                    {
                    #if !DISABLECOMM
                        char payload[20];
                        Communications::createSendMessage(payload, ACFREQUENCY_ID, String(tempVal).c_str());
                        if (masterComManager.sendMessage(payload))
                        {
                    #endif
                            debug(F("ACFREQUENCY UPDATED: "));debug(configStorage.config.ACFREQUENCY);debug(F(" --> "));debug(tempVal);debug('\n');
                            configStorage.config.ACFREQUENCY = (byte)tempVal;
                    #if !DISABLECOMM
                        }
                        else
                        {
                            debug(F("ERROR: Could not send the ACFREQUENCY update")); // TODO: error message
                        }
                    #endif
                    }
                }
                changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 3:
                tempVal = getNumInput(getString(Electricity_DCAmmeterSensitivity_STR), F(""), configStorage.config.DCAMMSENSITIVITY,4);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                #if !DISABLECOMM
                    char payload[20];
                    Communications::createSendMessage(payload, DCAMMSENSITIVITY_ID, String(tempVal).c_str());
                    if (masterComManager.sendMessage(payload))
                    {
                #endif
                        debug(F("DCAMMSENSITIVITY UPDATED: "));debug(configStorage.config.DCAMMSENSITIVITY);debug(F(" --> "));debug(tempVal);debug('\n');
                        configStorage.config.DCAMMSENSITIVITY = tempVal;
                #if !DISABLECOMM
                    }
                    else
                    {
                        debug(F("ERROR: Could not send the DCAMMSENSITIVITY update")); // TODO: error message
                    }
                #endif
                }
                changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
}

//This function set and draw the title, set the font size and draws the buttons in all pages.
void drawElectricity() // TODO get settings real value
{
    //Title electricity
    titleLabel.setString(getString(Electricity_Title_STR));
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    switch (page)
    {
        case 1:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(getString(Electricity_StartChargingVoltage_STR), getString(Electricity_StopChargingVoltage_STR), getString(Electricity_UVCurrent_STR),String(configStorage.config.STARTCHARGINGVOLTAGE) + F("V"), String(configStorage.config.STOPCHARGINGVOLTAGE) + F("V"),String(configStorage.config.ESTIMATEDUVAMPERAGE) + F("A"), true, true, true, fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(getString(Electricity_StartWorkingVoltage_STR), getString(Electricity_StopWorkingVoltage_STR),getString(Electricity_ACInverterFrequency_STR),String(configStorage.config.STARTWORKINGVOLTAGE) + F("V"), String(configStorage.config.STOPWORKINGVOLTAGE) + F("V"),String(configStorage.config.ACFREQUENCY) + F("Hz"), true, true, true, fontSizes);
            break;
        case 3:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(getString(Electricity_ACAmmeterSensitivity_STR), getString(Electricity_ACAmmeterZero_STR),getString(Electricity_DCAmmeterSensitivity_STR),String(configStorage.config.ACAMMSENSITIVITY, 4), String(configStorage.config.ACAMMZERO, 4), String(configStorage.config.DCAMMSENSITIVITY, 4), true,true, true, fontSizes);
            break;
        case 4:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 1, 1);
            draw6ButtonsLayout(getString(Electricity_DCAmmeterZero_STR), "", "", String(configStorage.config.DCAMMZERO, 4), "", "", true, false, false,fontSizes);
            break;
        default: debug(F("Page selected is out of bounds (page>4 || page<0)"));
    }
}
