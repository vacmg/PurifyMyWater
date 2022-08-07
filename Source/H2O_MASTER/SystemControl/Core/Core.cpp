//
// Created by Victor on 07/08/2022.
//

#include "Core.h"

/*------------Error Control-------------*/

// This function will allow to notify the user about the error
// and redirect the execution to an "onlyVitalActivities" function if it is critical
// or resume the program if it is not
// This function is not completed yet
void raise(enum Errors error, const String& possibleExplanation)
{
    data.currentError = error;
    bool critical = true;
    ledAnimation* prevAnimation = currentAnimation;
    setColor(RED);

    switch (error)
    {
#if GUI
        case SCREENNOTCONNECTEDERROR:
            critical = false;
            setColor(255, 30, 0); // orange
            break;
#endif
        default:
            currentAnimation = &defaultErrorAnimation;
            break;
    }

    if (critical)
    {
        disconnectEverything();
        delay(1000);
        voltControl();
#if DEBUG
        debug(F("RAISE --- CRITICAL Error "));debug(errorToString(error));debug(F(": "));debug(possibleExplanation);debug('\n');
            delay(2000);
#endif

        unsigned long pm = millis();
        while (true)
        {
            if (pm + 1000 < millis())
            {
                voltControl();
                pm = millis();
            }
            updateAnimation();
        }
    }
    else
    {
#if DEBUG
        debug(F("RAISE --- CRITICAL Error "));debug(error);debug(F(": "));debug(possibleExplanation);debug('\n');
            delay(3000);
#endif
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
    if (!data.lowSurfaceBuoySt && data.highSurfaceBuoySt)
    {
        raise(BuoyIncongruenceError, F("An incongruence has been detected with either lowSurfaceBuoy or highSurfaceBuoy. Please check the connections to those sensors"));
    }
    if (!data.lowFilteredBuoySt && data.highFilteredBuoySt)
    {
        raise(BuoyIncongruenceError, F("An incongruence has been detected with either lowFilteredBuoy or highFilteredBuoy. Please check the connections to those sensors"));
    }
    if (!data.lowPurifiedBuoySt && data.highPurifiedBuoySt)
    {
        raise(BuoyIncongruenceError, F("An incongruence has been detected with either lowPurifiedBuoy or highPurifiedBuoy. Please check the connections to those sensors"));
    }

    // Check for pumps timeout
    if (data.wellPumpSt && millis() > wellPumpPrevMillis + config.WELLPUMPTIMEOUT)
    {
        raise(PumpTimeoutError, String(F("Well pump has been working for more than ")) + String(config.WELLPUMPTIMEOUT) + String(F("ms. Either the pump doesn't work or there is a leakage in the well pump's circuit")));
    }
    if (data.UVPumpSt && millis() > UVPumpPrevMillis + config.UVPUMPTIMEOUT)
    {
        raise(PumpTimeoutError, String(F("UV pump has been working for more than ")) + String(config.UVPUMPTIMEOUT) + String(F("ms. Either the pump doesn't work or there is a leakage in UV the pump's circuit")));
    }
    if (data.endPumpSt && millis() > endPumpPrevMillis + config.ENDPUMPTIMEOUT)
    {
        raise(PumpTimeoutError, String(F("Well pump has been working for more than ")) + String(config.ENDPUMPTIMEOUT) + String(F("ms. Either the pump doesn't work or there is a leakage in the end pump's circuit")));
    }
    if (data.filterPumpSt && millis() > filterPumpPrevMillis + config.FILTERTIMEOUT)
    {
        raise(PumpTimeoutError, String(F("Filter has been working for more than ")) + String(config.FILTERTIMEOUT) + String(F("ms. Either the filter doesn't work or there is a leakage in the filter's circuit")));
    }
}

// Quick shortcut to disconnect every pump or relay
void disconnectEverything()
{
    output(voltSSRelay, 0);
    output(voltRelay, 0);
    output(ACInverter, 0);
    output(wellPump, 0);
    output(UVPump, 0);
    output(endPump, 0);
    output(UVRelay, 0);
    output(filterRelay, 0);

    debug(F("DisconnectEverything - Done\n"));
}

/*------------Error Control-------------*/

// This is the core setup code, which no matter which module is enabled, those instructions must be executed
void coreSetup()
{
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

    inputStats.setWindowSecs(40.0F / config.ACFREQUENCY); //Set AC Ammeter frequency
}

// This is the core loop code, which no matter which module is enabled, those instructions must be executed every main loop execution
void coreLoop()
{
    voltControl();
    logACAmps();
    getBuoyStatus();

#if !DISABLEHARDWARECHECKS
    errorCheck();
#endif

    updateAnimation();
}
