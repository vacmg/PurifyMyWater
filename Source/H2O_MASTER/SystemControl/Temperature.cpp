//
// Created by Victor on 07/08/2022.
//

#include "Temperature.h"

/*------------Temp Control--------------*/

// Used to get temperature in celsius of the 3 temperature sensors
// It modifies the given array that MUST be of length 3
void getSensorsTemp(float* temp)
{
    sensors.requestTemperatures();
    for (int i = 0; i < 3; i++)
    {
        temp[i] = sensors.getTempCByIndex(i);
    }
}

// Used to control the temperature of the main control unit
void tempControl()
{
    float temp[3];
    getSensorsTemp(temp);

    // Start or stop fans according to external and internal temperature
    if (temp[INSENSOR] > configStorage.config.STARTCASETEMP && temp[OUTSENSOR] < temp[INSENSOR])
    {
        output(inFan, 1);
        output(outFan, 1);
    }
    else if (temp[INSENSOR] < configStorage.config.STOPCASETEMP || temp[OUTSENSOR] >= temp[INSENSOR])
    {
        output(inFan, 0);
        output(outFan, 0);
    }

    if (temp[PSUSENSOR] > configStorage.config.STARTPSUTEMP && temp[INSENSOR] < temp[PSUSENSOR])
    {
        output(PSUFan, 1);
    }
    else if (temp[PSUSENSOR] < configStorage.config.STOPPSUTEMP || temp[INSENSOR] >= temp[PSUSENSOR])
    {
        output(PSUFan, 0);
    }

#if !DISABLEHARDWARECHECKS
    // check for extreme temperatures
    bool ok = true;
    for (byte i = 0; i < 3 && ok; i++)
    {
        if (temp[i] > configStorage.config.STOPWORKINGTEMP)
        {
            ok = false;
        }
    }
    if (!ok)
    {
        raise(HotTempError, String(F("Current temps are: ")) + String(temp[0]) + String(F(", ")) + String(temp[1]) + String(F(", ")) + String(temp[2]));
    }
#endif
}

/*------------Temp Control--------------*/

// This is the temperature setup code, which initializes all the objects needed to measure & control the system temperature
void tempSetup()
{
    sensors.begin();
#if !DISABLEHARDWARECHECKS
    byte num = sensors.getDeviceCount();
    if (num != 3)
    {
        raise(TempSensorsAmountError, String(F("Setup - A different amount from 3 sensors were connected.\nNumber of sensors detected: "))+num);
    }
#endif

    pinMode(outFan, OUTPUT);
    pinMode(PSUFan, OUTPUT);
    pinMode(inFan, OUTPUT);
    output(outFan, 1);
    output(PSUFan, 1);
    output(inFan, 1);

    tempControl();
}

// This is the temperature loop code, which handles all the instructions needed to measure & control the system temperature
void tempLoop()
{
    if (millis() > tempMillis + configStorage.config.TEMPCHECKTIME)
    {
        tempControl();
        tempMillis = millis();
    }
}
