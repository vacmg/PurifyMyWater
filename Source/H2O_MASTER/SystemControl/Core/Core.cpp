//
// Created by Victor on 07/08/2022.
//

#include "Core.h"

/*------------Error Control-------------*/

// This function will allow to notify the user about the error
// and redirect the execution to an "onlyVitalActivities" function if it is critical
// or resume the program if it is not
// This function is not completed yet
void raiseFn(enum Errors error, const String& possibleExplanation, const String& file, const uint16_t line)
{
    currentError = error;
    bool critical = true;
    ledAnimation* prevAnimation = currentAnimation;
    setColor(RED);

    /*switch (error)
    {
        default:*/
            currentAnimation = &defaultErrorAnimation;
            /*break;
    }*/

    debug(critical?F("RAISE --- CRITICAL Error "):F("RAISE --- Error "));debug(errorToString(error));debug(F(" in file "));debug(file);debug(F(" at line "));debug(line);debug(F(": "));debug(possibleExplanation);debug('\n');

    if (critical)
    {
        disconnectEverything();
        unsigned long pm = millis();
        while (true)
        {
            if (pm + 1000 < millis())
            {
                coreLoop();
                #if !DISABLECOMM
                    GUILoop(); // TODO disable some of those loops if required
                #endif
                #if !DISABLETEMPERATURE
                    tempLoop();
                #endif
                pm = millis();
            }
        }
    }
    else
    {
        delay(5000);
        switch (purificationStatus) // set back normal color
        {
            case TRANSITIONTOIDLE:
            case IDLE:
                setColor(UNDERVOLTAGECOLOR);
                break;
            default:
                setColor(WORKINGCOLOR);
        }
        currentAnimation = prevAnimation;
        voltControl();
    }
}

// This function will check for hardware errors on the system
void errorCheck()
{
    // Check for incongruent buoys
    if (!dataStorage.data.lowSurfaceBuoySt && dataStorage.data.highSurfaceBuoySt)
    {
        raise(BuoyIncongruenceError, F("An incongruence has been detected with either lowSurfaceBuoy or highSurfaceBuoy. Please check the connections to those sensors"));
    }
    if (!dataStorage.data.lowFilteredBuoySt && dataStorage.data.highFilteredBuoySt)
    {
        raise(BuoyIncongruenceError, F("An incongruence has been detected with either lowFilteredBuoy or highFilteredBuoy. Please check the connections to those sensors"));
    }
    if (!dataStorage.data.lowPurifiedBuoySt && dataStorage.data.highPurifiedBuoySt)
    {
        raise(BuoyIncongruenceError, F("An incongruence has been detected with either lowPurifiedBuoy or highPurifiedBuoy. Please check the connections to those sensors"));
    }

    // Check for pumps timeout
    if (dataStorage.data.wellPumpSt && millis() > wellPumpPrevMillis + configStorage.config.WELLPUMPTIMEOUT)
    {
        raise(PumpTimeoutError, String(F("Well pump has been working for more than ")) + String(configStorage.config.WELLPUMPTIMEOUT) + String(F("ms. Either the pump doesn't work or there is a leakage in the well pump's circuit")));
    }
    if (dataStorage.data.UVPumpSt && millis() > UVPumpPrevMillis + configStorage.config.UVPUMPTIMEOUT)
    {
        raise(PumpTimeoutError, String(F("UV pump has been working for more than ")) + String(configStorage.config.UVPUMPTIMEOUT) + String(F("ms. Either the pump doesn't work or there is a leakage in UV the pump's circuit")));
    }
    if (dataStorage.data.endPumpSt && millis() > endPumpPrevMillis + configStorage.config.ENDPUMPTIMEOUT)
    {
        raise(PumpTimeoutError, String(F("Well pump has been working for more than ")) + String(configStorage.config.ENDPUMPTIMEOUT) + String(F("ms. Either the pump doesn't work or there is a leakage in the end pump's circuit")));
    }
    if (dataStorage.data.filterPumpSt && millis() > filterPumpPrevMillis + configStorage.config.FILTERTIMEOUT)
    {
        raise(PumpTimeoutError, String(F("Filter has been working for more than ")) + String(configStorage.config.FILTERTIMEOUT) + String(F("ms. Either the filter doesn't work or there is a leakage in the filter's circuit")));
    }
}

void disconnectEverything()
{
    disconnectEverything(false);
}

// Quick shortcut to disconnect every pump or relay
void disconnectEverything(bool withVoltage)
{
    if (withVoltage)
    {
        output(voltSSRelay, 0);
        output(voltRelay, 0);
    }
    output(wellPump, 0);
    output(endPump, 0);
    output(UVPump, 0);
    output(filterRelay, 0);
    delay(1000);
    output(UVRelay, 0);
    delay(250);
    output(ACInverter, 0);

    debug(F("DisconnectEverything - Done\n"));
}

/*------------Error Control-------------*/

// This is the core setup code, which no matter which module is enabled, those instructions must be executed
void coreSetup()
{
    debug(F("Setup - Core - Setting up I/O\n"));

    pinMode(redLed, OUTPUT);
    pinMode(blueLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    setColor(BOOTINGCOLOR);

    pinMode(secBuoy, INPUT);
    pinMode(lowSurfaceBuoy, INPUT);
    pinMode(highSurfaceBuoy, INPUT);
    pinMode(lowFilteredBuoy, INPUT);
    pinMode(highFilteredBuoy, INPUT);
    pinMode(lowPurifiedBuoy, INPUT);
    pinMode(highPurifiedBuoy, INPUT);
    pinMode(endBuoy, INPUT);

    pinMode(voltSSRelay, OUTPUT);
    pinMode(voltRelay, OUTPUT);
    pinMode(ACInverter, OUTPUT);
    pinMode(wellPump, OUTPUT);
    pinMode(UVPump, OUTPUT);
    pinMode(endPump, OUTPUT);
    pinMode(UVRelay, OUTPUT);
    pinMode(filterRelay, OUTPUT);

    output(voltSSRelay, 0);
    output(voltRelay, 0);
    output(ACInverter, 0);
    output(wellPump, 0);
    output(UVPump, 0);
    output(endPump, 0);
    output(UVRelay, 0);
    output(filterRelay, 0);

    pinMode(screenSensor, INPUT_PULLUP);
    pinMode(screenRelay, OUTPUT);
    output(screenRelay, 0);

    inputStats.setWindowSecs(40.0F / configStorage.config.ACFREQUENCY); //Set AC Ammeter frequency

    debug(F("Setup - Core - I/O ready\n"));
}

#if !DISABLECOMM
void sendVoltage()
{
    if (sendVoltageMillis + configStorage.config.DATAREFRESHPERIOD < millis())
    {
        char temp[10];
        Communications::createSendMessage(temp,voltage_ID,String(dataStorage.data.voltage).c_str());
        sendGUIMessage(temp);
        sendVoltageMillis = millis();
    }
}
#endif

// This is the core loop code, which no matter which module is enabled, those instructions must be executed every main loop execution
void coreLoop()
{
    voltControl();
    logACAmps();
    getBuoyStatus();

#if !DISABLEHARDWARECHECKS
    errorCheck();
#endif
#if !DISABLECOMM
    sendVoltage();
#endif
    updateAnimation();
}
