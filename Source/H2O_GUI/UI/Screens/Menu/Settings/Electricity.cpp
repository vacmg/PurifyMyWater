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
                debug(F("STOPWORKINGVOLTAGE: "));debug(configStorage.config.STOPWORKINGVOLTAGE);debug(F("--> STOPCHARGINGVOLTAGE: "));debug(configStorage.config.STOPCHARGINGVOLTAGE);
                tempVal = getNumInput(getString(Electricity_StartChargingVoltage_STR), F("V"), configStorage.config.STARTCHARGINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (configStorage.config.STOPWORKINGVOLTAGE < tempVal && tempVal < configStorage.config.STOPCHARGINGVOLTAGE)
                    {
                        debug(F("STARTCHARGINGVOLTAGE UPDATED: "));debug(configStorage.config.STARTCHARGINGVOLTAGE);debug(F(" --> "));debug(tempVal);debug('\n');
                        configStorage.config.STARTCHARGINGVOLTAGE = (float)tempVal;
                        // TODO send new setting
                        changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                        drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                    }
                    else if(tempVal <= configStorage.config.STOPWORKINGVOLTAGE )
                    {
                        debug(F("Low Value error Start Charging Voltage"));
                        prevScreenStatus  = LOADPAGEELECTRICITY;
                        changeError(InnerLimitReachedError);
                        changeScreenStatus(LOADERROR);

                    }
                    else if(tempVal >= configStorage.config.STOPCHARGINGVOLTAGE)
                    {
                        debug(F("Up Value error Start Charging Voltage"));
                        prevScreenStatus = LOADPAGEELECTRICITY;
                        changeError(UpperLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }
                }
                break;

            case 2: //page 2
                debug(F("STARTCHARGINGVOLTAGE: "));debug(configStorage.config.STARTCHARGINGVOLTAGE);debug(F("--> STOPCHARGINGVOLTAGE: "));debug(configStorage.config.STOPCHARGINGVOLTAGE);
                tempVal = getNumInput(getString(Electricity_StartWorkingVoltage_STR), F("V"), configStorage.config.STARTWORKINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (configStorage.config.STARTCHARGINGVOLTAGE < tempVal && tempVal < configStorage.config.STOPCHARGINGVOLTAGE)// STARTCHARGINGVOLTAGE < STARTWORKINGVOLTAGE < STOPCHARGINGVOLTAGE
                    {
                        debug(F("STOPCHARGINGVOLTAGE: ")); debug(configStorage.config.STOPCHARGINGVOLTAGE);
                        debug(F("STARTWORKINGVOLTAGE UPDATED: "));debug(configStorage.config.STARTWORKINGVOLTAGE);debug(F(" --> "));debug(tempVal);debug('\n');
                        configStorage.config.STARTWORKINGVOLTAGE = (float)tempVal;

                        // TODO send new setting
                        changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                        drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                    }

                    else if(tempVal <=  configStorage.config.STARTCHARGINGVOLTAGE)
                    {
                        debug(F("Low Value error Start Charging Voltage"));
                        prevScreenStatus = LOADPAGEELECTRICITY;
                        changeError(InnerLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }
                    else if(tempVal >= configStorage.config.STOPCHARGINGVOLTAGE)
                    {
                        debug(F("Up Value error Start Charging Voltage"));
                        prevScreenStatus = LOADPAGEELECTRICITY;
                        changeError(UpperLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }

                }
                break;

            case 3:
                tempVal = getNumInput(getString(Electricity_ACAmmeterSensitivity_STR), F(""), configStorage.config.ACAMMSENSITIVITY,4);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(F("ACAMMSENSITIVITY UPDATED: "));debug(configStorage.config.ACAMMSENSITIVITY);debug(F(" --> "));debug(tempVal);debug('\n');
                    configStorage.config.ACAMMSENSITIVITY = tempVal;
                    // TODO send new setting
                }
                changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 4:
                tempVal = getNumInput(getString(Electricity_DCAmmeterZero_STR), F(""), configStorage.config.DCAMMZERO,4);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(F(" UPDATED: DCAMMZERO"));debug(configStorage.config.DCAMMZERO);debug(F(" --> "));debug(tempVal);debug('\n');
                    configStorage.config.DCAMMZERO = tempVal;
                    // TODO send new setting
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
                debug(F("STARTCHARGINGVOLTAGE+1: "));debug(configStorage.config.STARTCHARGINGVOLTAGE +1);debug(F("--> MAXCAPACITORSALLOWEDVOLTAGE: "));debug(MAXCAPACITORSALLOWEDVOLTAGE);
                tempVal = getNumInput(getString(Electricity_StopChargingVoltage_STR), F("V"), configStorage.config.STOPCHARGINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (configStorage.config.STARTCHARGINGVOLTAGE + 1 < tempVal && tempVal <MAXCAPACITORSALLOWEDVOLTAGE)// STARTCHARGINGVOLTAGE+1 < STOPCHARGINGVOLTAGE < MAXCAPACITORSALLOWEDVOLTAGE
                    {
                        debug(F("STOPCHARGINGVOLTAGE UPDATED: "));debug(configStorage.config.STOPCHARGINGVOLTAGE);debug(F(" --> "));debug(tempVal);debug('\n');
                        configStorage.config.STOPCHARGINGVOLTAGE = (float)tempVal;
                        // TODO send new setting
                        changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                        drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too

                    }
                    else if(tempVal <=  configStorage.config.STARTCHARGINGVOLTAGE + 1)
                    {
                        debug(F("Low Value error Start Charging Voltage"));
                        prevScreenStatus  = LOADPAGEELECTRICITY;
                        changeError(InnerLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }
                    else if(tempVal >= MAXCAPACITORSALLOWEDVOLTAGE)
                    {
                        debug(F("Up Value error Start Charging Voltage"));
                        prevScreenStatus  = LOADPAGEELECTRICITY;
                        changeError(UpperLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }
                }
                break;

            case 2:
                debug(F("MINSYSTEMALLOWEDVOLTAGE: "));debug(MINSYSTEMALLOWEDVOLTAGE);debug(F("--> STARTCHARGINGVOLTAGE -1: "));debug(configStorage.config.STARTCHARGINGVOLTAGE -1);
                tempVal = getNumInput(getString(Electricity_StopWorkingVoltage_STR), F("V"), configStorage.config.STOPWORKINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (MINSYSTEMALLOWEDVOLTAGE < tempVal && tempVal < configStorage.config.STARTCHARGINGVOLTAGE - 1)// MINSYSTEMALLOWEDVOLTAGE < STOPWORKINGVOLTAGE < STARTCHARGINGVOLTAGE-1
                    {
                        debug(F("STOPWORKINGVOLTAGE UPDATED: "));debug(configStorage.config.STOPWORKINGVOLTAGE);debug(F(" --> "));debug(tempVal);debug('\n');
                        configStorage.config.STOPWORKINGVOLTAGE = (float)tempVal;
                        // TODO send new setting
                        changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                        drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too

                    }
                    else if(tempVal <=  MINSYSTEMALLOWEDVOLTAGE)
                    {
                        debug(F("Low Value error Start Charging Voltage"));
                        prevScreenStatus  = LOADPAGEELECTRICITY;
                        changeError(InnerLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }
                    else if(tempVal >= configStorage.config.STARTCHARGINGVOLTAGE - 1)
                    {
                        debug(F("Up Value error Start Charging Voltage"));
                        prevScreenStatus  = LOADPAGEELECTRICITY;
                        changeError(UpperLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }
                }
                break;

            case 3:
                tempVal = getNumInput(getString(Electricity_ACAmmeterZero_STR), F(""), configStorage.config.ACAMMZERO,4);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(F("ACAMMZERO UPDATED: "));debug(configStorage.config.ACAMMZERO);debug(F(" --> "));debug(tempVal);debug('\n');
                    configStorage.config.ACAMMZERO = tempVal;
                    // TODO send new setting
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
                debug(F("-->"));debug(F("MAXUVAMPERAGE: "));debug(MAXUVAMPERAGE);
                tempVal = getNumInput(getString(Electricity_UVCurrent_STR), F("A"), configStorage.config.ESTIMATEDUVAMPERAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < tempVal && tempVal < MAXUVAMPERAGE)//0 < ESTIMATEDUVAMPERAGE < MAXUVAMPERAGE
                    {
                        debug(F("ESTIMATEDUVAMPERAGE UPDATED: "));debug(configStorage.config.ESTIMATEDUVAMPERAGE);debug(F(" --> "));debug(tempVal);debug('\n');
                        configStorage.config.ESTIMATEDUVAMPERAGE = (float)tempVal;
                        // TODO send new setting
                        changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                        drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                    }
                    else if(tempVal <=  0)
                    {
                        debug(F("Low Value error Start Charging Voltage"));
                        prevScreenStatus  = LOADPAGEELECTRICITY;
                        changeError(InnerLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }
                    else if(tempVal >= MAXUVAMPERAGE)
                    {
                        debug(F("Up Value error Start Charging Voltage"));
                        prevScreenStatus  = LOADPAGEELECTRICITY;
                        changeError(UpperLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }
                }
                break;

            case 2:
                debug(F("50: "));debug(F("--> 60: "));
                tempVal = getNumInput(getString(Electricity_ACInverterFrequency_STR), F("Hz"), configStorage.config.ACFREQUENCY);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (50 < tempVal && tempVal < 60)// 50 <= ACFREQUENCY <= 60
                    {
                        debug(F("ACFREQUENCY UPDATED: "));debug(configStorage.config.ACFREQUENCY);debug(F(" --> "));debug(tempVal);debug('\n');
                        configStorage.config.ACFREQUENCY = (byte)tempVal;
                        // TODO send new setting
                        changeScreenStatus(LOADPAGEELECTRICITY); // reload page with new config value
                        drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too

                    }
                    else if(tempVal <=  50)
                    {
                        debug(F("Low Value error Start Charging Voltage"));
                        prevScreenStatus  = LOADPAGEELECTRICITY;
                        changeError(InnerLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }
                    else if(tempVal >= 60)
                    {
                        debug(F("Up Value error Start Charging Voltage"));
                        prevScreenStatus  = LOADPAGEELECTRICITY;
                        changeError(UpperLimitReachedError);
                        changeScreenStatus(LOADERROR);
                    }
                }
                break;

            case 3:
                tempVal = getNumInput(getString(Electricity_DCAmmeterSensitivity_STR), F(""), configStorage.config.DCAMMSENSITIVITY,4);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(F("DCAMMSENSITIVITY UPDATED: "));debug(configStorage.config.DCAMMSENSITIVITY);debug(F(" --> "));debug(tempVal);debug('\n');
                    configStorage.config.DCAMMSENSITIVITY = tempVal;
                    // TODO send new setting
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
