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
                tempVal = getNumInput(F("Start charging Voltage"), F("V"), config.STARTCHARGINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (config.STOPWORKINGVOLTAGE < tempVal && tempVal < config.STOPCHARGINGVOLTAGE)
                    {
                        debug(F("STARTCHARGINGVOLTAGE UPDATED: "));debug(config.STARTCHARGINGVOLTAGE);debug(F(" --> "));debug(tempVal);debug('\n');
                        config.STARTCHARGINGVOLTAGE = (float)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2: //page 2
                tempVal = getNumInput(F("Start Working Voltage"), F("V"), config.STARTWORKINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (config.STARTCHARGINGVOLTAGE < tempVal && tempVal < config.STOPCHARGINGVOLTAGE)// STARTCHARGINGVOLTAGE < STARTWORKINGVOLTAGE < STOPCHARGINGVOLTAGE
                    {
                        debug(F("STARTWORKINGVOLTAGE UPDATED: "));debug(config.STARTWORKINGVOLTAGE);debug(F(" --> "));debug(tempVal);debug('\n');
                        config.STARTWORKINGVOLTAGE = (float)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 3:
                tempVal = getNumInput(F("AC Ammeter Sensitivity"), F(""), config.ACAMPSENSITIVITY,4);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(F("ACAMPSENSITIVITY UPDATED: "));debug(config.ACAMPSENSITIVITY);debug(F(" --> "));debug(tempVal);debug('\n');
                    config.ACAMPSENSITIVITY = tempVal;
                    // TODO send new setting
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 4:
                tempVal = getNumInput(F("DC Ammeter Zero"), F(""), config.DCAMPZERO,4);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(F(" UPDATED: DCAMPZERO"));debug(config.DCAMPZERO);debug(F(" --> "));debug(tempVal);debug('\n');
                    config.DCAMPZERO = tempVal;
                    // TODO send new setting
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }

    }
    else if (btn5.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput(F("Stop Charging Voltage"), F("V"), config.STOPCHARGINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (config.STARTCHARGINGVOLTAGE + 1 < tempVal && tempVal <MAXCAPACITORSALLOWEDVOLTAGE)// STARTCHARGINGVOLTAGE+1 < STOPCHARGINGVOLTAGE < MAXCAPACITORSALLOWEDVOLTAGE
                    {
                        debug(F("STOPCHARGINGVOLTAGE UPDATED: "));debug(config.STOPCHARGINGVOLTAGE);debug(F(" --> "));debug(tempVal);debug('\n');
                        config.STOPCHARGINGVOLTAGE = (float)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2:
                tempVal = getNumInput(F("Stop Working Voltage"), F("V"), config.STOPWORKINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (MINSYSTEMALLOWEDVOLTAGE < tempVal && tempVal < config.STARTCHARGINGVOLTAGE - 1)// MINSYSTEMALLOWEDVOLTAGE < STOPWORKINGVOLTAGE < STARTCHARGINGVOLTAGE-1
                    {
                        debug(F("STOPWORKINGVOLTAGE UPDATED: "));debug(config.STOPWORKINGVOLTAGE);debug(F(" --> "));debug(tempVal);debug('\n');
                        config.STOPWORKINGVOLTAGE = (float)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 3:
                tempVal = getNumInput(F("AC Ammeter Zero"), F(""), config.ACAMPZERO,4);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(F("ACAMPZERO UPDATED: "));debug(config.ACAMPZERO);debug(F(" --> "));debug(tempVal);debug('\n');
                    config.ACAMPZERO = tempVal;
                    // TODO send new setting
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
    else if (btn6.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput(F("UV light est. Current"), F("A"), config.ESTIMATEDUVAMPERAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (0 < tempVal && tempVal < MAXUVAMPERAGE)//0 < ESTIMATEDUVAMPERAGE < MAXUVAMPERAGE
                    {
                        debug(F("ESTIMATEDUVAMPERAGE UPDATED: "));debug(config.ESTIMATEDUVAMPERAGE);debug(F(" --> "));debug(tempVal);debug('\n');
                        config.ESTIMATEDUVAMPERAGE = (float)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2:
                tempVal = getNumInput(F("AC Inverter Frequency"), F("Hz"), config.ACFREQUENCY);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (50 < tempVal && tempVal < 60)// 50 <= ACFREQUENCY <= 60
                    {
                        debug(F("ACFREQUENCY UPDATED: "));debug(config.ACFREQUENCY);debug(F(" --> "));debug(tempVal);debug('\n');
                        config.ACFREQUENCY = (byte)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 3:
                tempVal = getNumInput(F("DC Ammeter Sensitivity"), F(""), config.DCAMPSENSITIVITY,4);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(F("DCAMPSENSITIVITY UPDATED: "));debug(config.DCAMPSENSITIVITY);debug(F(" --> "));debug(tempVal);debug('\n');
                    config.DCAMPSENSITIVITY = tempVal;
                    // TODO send new setting
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
}

//This function set and draw the title, set the font size and draws the buttons in all pages.
void drawElectricity() // TODO get settings real value
{
    //Title electricity
    titleLabel.setString("Electricity Settings");
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    switch (page)
    {
        case 1:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(F("Start Charging Voltage"), F("Stop Charging Voltage"), F("UV light est. Current"),String(config.STARTCHARGINGVOLTAGE) + F("V"), String(config.STOPCHARGINGVOLTAGE) + F("V"),String(config.ESTIMATEDUVAMPERAGE) + F("A"), true, true, true, fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(F("Start Working Voltage"), F("Stop Working Voltage"), F("AC Inverter Frequency"),String(config.STARTWORKINGVOLTAGE) + F("V"), String(config.STOPWORKINGVOLTAGE) + F("V"),String(config.ACFREQUENCY) + F("Hz"), true, true, true, fontSizes);
            break;
        case 3:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(F("AC Ammeter Sensitivity"), F("AC Ammeter Zero"), F("DC Ammeter Sensitivity"),String(config.ACAMPSENSITIVITY, 4), String(config.ACAMPZERO, 4), String(config.DCAMPSENSITIVITY, 4), true,true, true, fontSizes);
            break;
        case 4:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 1, 1);
            draw6ButtonsLayout(F("DC Ammeter Zero"), "", "", String(config.DCAMPZERO, 4), "", "", true, false, false,fontSizes);
            break;
    }
}
