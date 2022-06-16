//
// Created by Víctor on 16/06/2022.
//

#include "Electricity.h"

void clickElectricity()
{
    double tempVal;
    if(btn4.isPressed())
    {
        switch (page)
        {
            case 1: // Start charging voltage
                tempVal = getNumInput("Start charging Voltage","V",STARTCHARGINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if(STOPWORKINGVOLTAGE<tempVal && tempVal<STOPCHARGINGVOLTAGE)
                    {
                        debug(String(F("STARTCHARGINGVOLTAGE UPDATED: "))+STARTCHARGINGVOLTAGE+String(F(" --> "))+tempVal);
                        STARTCHARGINGVOLTAGE = tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2: //page 2
                tempVal = getNumInput("Start Working Voltage","V",STARTWORKINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if(STARTCHARGINGVOLTAGE<tempVal && tempVal<STOPCHARGINGVOLTAGE)// STARTCHARGINGVOLTAGE < STARTWORKINGVOLTAGE < STOPCHARGINGVOLTAGE
                    {
                        debug(String(F("STARTCHARGINGVOLTAGE UPDATED: "))+STARTWORKINGVOLTAGE+String(F(" --> "))+tempVal);
                        STARTWORKINGVOLTAGE = tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 3:
                tempVal = getNumInput("AC Ammeter Sensitivity","",ACAMPSENSITIVITY);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(String(F("ACAMPSENSITIVITY UPDATED: "))+ACAMPSENSITIVITY+String(F(" --> "))+tempVal);
                    ACAMPSENSITIVITY = tempVal;
                    // TODO send new setting

                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 4:
                tempVal = getNumInput("DC Ammeter Zero","",DCAMPZERO);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(String(F(" UPDATED: DCAMPZERO"))+DCAMPZERO+String(F(" --> "))+tempVal);
                    DCAMPZERO = tempVal;
                    // TODO send new setting

                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }

    }
    else if(btn5.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput("Stop Charging Voltage","V",STOPCHARGINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if(STARTCHARGINGVOLTAGE+1<tempVal && tempVal<MAXCAPACITORSALLOWEDVOLTAGE)// STARTCHARGINGVOLTAGE+1 < STOPCHARGINGVOLTAGE < MAXCAPACITORSALLOWEDVOLTAGE
                    {
                        debug(String(F("STOPCHARGINGVOLTAGE UPDATED: "))+STOPCHARGINGVOLTAGE+String(F(" --> "))+tempVal);
                        STOPCHARGINGVOLTAGE = tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2:
                tempVal = getNumInput("Stop Working Voltage","V",STOPWORKINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if(MINSYSTEMALLOWEDVOLTAGE<tempVal && tempVal<STARTCHARGINGVOLTAGE-1)// MINSYSTEMALLOWEDVOLTAGE < STOPWORKINGVOLTAGE < STARTCHARGINGVOLTAGE-1
                    {
                        debug(String(F("STOPWORKINGVOLTAGE UPDATED: "))+STOPWORKINGVOLTAGE+String(F(" --> "))+tempVal);
                        STOPWORKINGVOLTAGE = tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 3:
                tempVal = getNumInput("AC Ammeter Zero","",ACAMPZERO);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(String(F("ACAMPZERO UPDATED: "))+ACAMPZERO+String(F(" --> "))+tempVal);
                    ACAMPZERO = tempVal;
                    // TODO send new setting

                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
    else if(btn6.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput("UV light est. Current","A",ESTIMATEDUVAMPERAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if(0<tempVal && tempVal<MAXUVAMPERAGE)//0 < ESTIMATEDUVAMPERAGE < MAXUVAMPERAGE
                    {
                        debug(String(F("ESTIMATEDUVAMPERAGE UPDATED: "))+ESTIMATEDUVAMPERAGE+String(F(" --> "))+tempVal);
                        ESTIMATEDUVAMPERAGE = tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 2:
                tempVal = getNumInput("AC Inverter Frequency","Hz",ACFREQUENCY);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if(50<tempVal && tempVal<60)// 50 <= ACFREQUENCY <= 60
                    {
                        debug(String(F("ACFREQUENCY UPDATED: "))+ACFREQUENCY+String(F(" --> "))+tempVal);
                        ACFREQUENCY = tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;

            case 3:
                tempVal = getNumInput("DC Ammeter Sensitivity","",DCAMPSENSITIVITY);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(String(F("DCAMPSENSITIVITY UPDATED: "))+DCAMPSENSITIVITY+String(F(" --> "))+tempVal);
                    DCAMPSENSITIVITY = tempVal;
                    // TODO send new setting
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
}

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
            setFontSizeArray(fontSizes, 1,1,1,2,2,2);
            draw6ButtonsLayout(F("Start Charging Voltage"),F("Stop Charging Voltage"),F("UV light est. Current"),String(STARTCHARGINGVOLTAGE)+F("V"),String(STOPCHARGINGVOLTAGE)+F("V"),String(ESTIMATEDUVAMPERAGE)+F("A"),true,true,true,fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes, 1,1,1,2,2,2);
            draw6ButtonsLayout(F("Start Working Voltage"),F("Stop Working Voltage"),F("AC Inverter Frequency"),String(STARTWORKINGVOLTAGE)+F("V"),String(STOPWORKINGVOLTAGE)+F("V"),String(ACFREQUENCY)+F("Hz"),true,true,true, fontSizes);
            break;
        case 3:
            setFontSizeArray(fontSizes, 1,1,1,2,2,2);
            draw6ButtonsLayout(F("AC Ammeter Sensitivity"),F("AC Ammeter Zero"),F("DC Ammeter Sensitivity"),String(ACAMPSENSITIVITY, 4),String(ACAMPZERO,4),String(DCAMPSENSITIVITY,4),true,true,true,fontSizes);
            break;
        case 4:
            setFontSizeArray(fontSizes, 1,1,1,2,1,1);
            draw6ButtonsLayout(F("DC Ammeter Zero"),"","",String(DCAMPZERO,4),"","",true,false,false,fontSizes);
            break;
    }
}