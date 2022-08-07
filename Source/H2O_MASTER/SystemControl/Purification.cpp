//
// Created by Victor on 05/08/2022.
//

#include "Purification.h"


// This is the purification setup code, which sets the system to a well known status to start with the purification
void purificationSetup()
{
    debug(F("Setup - Waiting for "));debug(config.STARTCHARGINGVOLTAGE - 1);debug(F(" V\n"));
    output(voltRelay, 1);
    waitForVoltage(config.STARTCHARGINGVOLTAGE - 1);
    output(voltRelay, 0);
}

// This is the purification loop code, which holds the purification algorithm
void purificationLoop()
{
#if !ONLYVITALACTIVITYALLOWED
    switch (purificationStatus)
    {
        case TRANSITIONTOIDLE: // Transition to OFF
            output(wellPump, 0);
            output(endPump, 0);
            output(UVPump, 0);
            output(filterRelay, 0);
            output(ACInverter, 0);
            delay(1000);
            output(UVRelay, 0);
            output(voltSSRelay, 1);
            setColor(UNDERVOLTAGECOLOR);
            purificationStatus = IDLE;
            break;

        case IDLE: // OFF
            #if !OVERRRIDEMAXVOLTAGE
            if (voltRead() > config.STARTWORKINGVOLTAGE)
            #endif
                purificationStatus = TRANSITIONTOPUMPSWORKING;
            break;

        case TRANSITIONTOPUMPSWORKING: // Transition to Pumps Working
            output(ACInverter, 0);
            setColor(WORKINGCOLOR);
            purificationStatus = PUMPSWORKING;
            break;

        case PUMPSWORKING: // Pumps Working
            #if !OVERRRIDEMAXVOLTAGE
            if (voltRead() < config.STOPWORKINGVOLTAGE)
                purificationStatus = TRANSITIONTOIDLE;
            #endif

            if (!data.wellPumpSt && !data.highSurfaceBuoySt && data.secBuoySt)
            {
                output(wellPump, 1);
                wellPumpPrevMillis = millis();
            }


            if (data.wellPumpSt && (data.highSurfaceBuoySt || !data.secBuoySt))
            {
                output(wellPump, 0);
            }


            if (!data.lowFilteredBuoySt && data.highSurfaceBuoySt)
                purificationStatus = TRANSITIONTOFILTERWORKING;

            if (!data.UVPumpSt && !data.highPurifiedBuoySt && data.lowFilteredBuoySt)
            {
                output(ACInverter, 1);
                delay(250);
                output(UVRelay, 1);

                #if !DISABLEHARDWARECHECKS
                // check if UV is working
                for (int i = 0; i < 100; i++)
                {
                    logACAmps();
                    delay(10);
                }
                data.ACUVAmps = getACAmps();

                if (data.ACUVAmps < config.ESTIMATEDUVAMPERAGE)
                {
                    raise(UVLightNotWorkingError, String(F("The UV amperage sensor detected "))+String(data.ACUVAmps)+String(F("A. The UV light must be either broken or disconnected. Check the connections and if it persists, replace the UV light")));
                }
                #endif

                UVPumpPrevMillis = millis();
                UVMillis = UVPumpPrevMillis;
                output(UVPump, 1);
            }
            if (data.UVPumpSt) // if UV is on and each 800ms
            {
                workingTime += millis() - UVMillis; // Add this time to workingTime
                data.purifiedWater = ((float)workingTime * config.UVPUMPFLOW) / 3600000.00; // calculate the amount of purified water
                UVMillis = millis();
            }

            if (data.UVPumpSt && (!data.lowFilteredBuoySt || data.highPurifiedBuoySt))
            {
                output(UVPump, 0);
                workingTime += millis() - UVMillis; // Add this time to workingTime
                data.purifiedWater = ((float)workingTime * config.UVPUMPFLOW) / 3600000.00; // calculate the amount of purified water
                delay(1000);
                output(UVRelay, 0);
                delay(250);
                output(ACInverter, 0);
            }

            if (!data.endPumpSt && !data.endBuoySt && data.lowPurifiedBuoySt)
            {
                output(endPump, 1);
                endPumpPrevMillis = millis();
            }

            if (data.endPumpSt && (!data.lowPurifiedBuoySt || data.endBuoySt))
            {
                output(endPump, 0);
            }

            break;

        case TRANSITIONTOFILTERWORKING: // Transition to filter working
            output(wellPump, 0);
            output(endPump, 0);
            output(UVPump, 0);

            output(ACInverter, 1);
            delay(1000);
            output(UVRelay, 0);
            #if !OVERRRIDEMAXVOLTAGE
            if (voltRead() < config.STOPWORKINGVOLTAGE)
                purificationStatus = TRANSITIONTOIDLE;
            #endif

            waitForVoltage(config.STARTWORKINGVOLTAGE);
            filterPumpPrevMillis = millis();
            output(filterRelay, 1);

            purificationStatus = FILTERWORKING;
            break;

        case FILTERWORKING: // Filter Working
            #if !OVERRRIDEMAXVOLTAGE
            if (voltRead() < config.STOPWORKINGVOLTAGE)
                purificationStatus = TRANSITIONTOIDLE;
            #endif

            if (data.highFilteredBuoySt || !data.lowSurfaceBuoySt)
            {
                output(filterRelay, 0);
                purificationStatus = TRANSITIONTOPUMPSWORKING;
            }
            break;
    }
#endif
}
