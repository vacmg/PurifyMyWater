//
// Created by Victor on 05/08/2022.
//

#include "Purification.h"


// This is the purification setup code, which sets the system to a well known status to start with the purification
void purificationSetup()
{
    debug(F("Setup - Purification - Waiting for "));debug(configStorage.config.STARTCHARGINGVOLTAGE - 1);debug(F(" V\n"));
    output(voltRelay, 1);
    waitForVoltage(configStorage.config.STARTCHARGINGVOLTAGE - 1);
    output(voltRelay, 0);
    debug(F("Setup - Purification - "));debug(configStorage.config.STARTCHARGINGVOLTAGE - 1);debug(F(" V reached\n"));
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
            delay(1000);
            output(UVRelay, 0);
            delay(250);
            output(ACInverter, 0);
            output(voltSSRelay, 1); // TODO check if this should be guarded if the system is manually shut down instead of undervoltage
            setColor(UNDERVOLTAGECOLOR);
            changePurificationStatus(IDLE);
            break;

        case IDLE: // OFF
            #if !OVERRRIDEMAXVOLTAGE
            if (voltRead() > configStorage.config.STARTWORKINGVOLTAGE)
            #endif
            changePurificationStatus(TRANSITIONTOPUMPSWORKING);
            break;

        case TRANSITIONTOPUMPSWORKING: // Transition to Pumps Working
            output(ACInverter, 0);
            setColor(WORKINGCOLOR);
            changePurificationStatus(PUMPSWORKING);
            break;

        case PUMPSWORKING: // Pumps Working
            #if !OVERRRIDEMAXVOLTAGE
            if (voltRead() < configStorage.config.STOPWORKINGVOLTAGE)
                changePurificationStatus(TRANSITIONTOIDLE);
            #endif

            if (!dataStorage.data.wellPumpSt && !dataStorage.data.highSurfaceBuoySt && dataStorage.data.secBuoySt)
            {
                output(wellPump, 1);
                wellPumpPrevMillis = millis();
            }


            if (dataStorage.data.wellPumpSt && (dataStorage.data.highSurfaceBuoySt || !dataStorage.data.secBuoySt))
            {
                output(wellPump, 0);
            }


            if (!dataStorage.data.lowFilteredBuoySt && dataStorage.data.highSurfaceBuoySt)
            {
                changePurificationStatus(TRANSITIONTOFILTERWORKING);
            }

            if (!dataStorage.data.UVPumpSt && !dataStorage.data.highPurifiedBuoySt && dataStorage.data.lowFilteredBuoySt)
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
                dataStorage.data.ACUVAmps = getACAmps();

                if (dataStorage.data.ACUVAmps < configStorage.config.ESTIMATEDUVAMPERAGE)
                {
                    raise(UVLightNotWorkingError, String(F("The UV amperage sensor detected "))+String(dataStorage.data.ACUVAmps)+String(F("A. The UV light must be either broken or disconnected. Check the connections and if it persists, replace the UV light")));
                }
                #endif

                UVPumpPrevMillis = millis();
                UVMillis = UVPumpPrevMillis;
                output(UVPump, 1);
            }

            if (dataStorage.data.UVPumpSt) // if UV is on and each 800ms
            {
                workingTime += millis() - UVMillis; // Add this time to workingTime
                dataStorage.data.purifiedWater = ((float)workingTime * configStorage.config.UVPUMPFLOW) / 3600000.00; // calculate the amount of purified water
                UVMillis = millis();
            }

            if (dataStorage.data.UVPumpSt && (!dataStorage.data.lowFilteredBuoySt || dataStorage.data.highPurifiedBuoySt))
            {
                output(UVPump, 0);
                workingTime += millis() - UVMillis; // Add this time to workingTime
                changeVariable(dataStorage.data.purifiedWater,((float)workingTime * configStorage.config.UVPUMPFLOW) / 3600000.00); // calculate the amount of purified water
                #if !DISABLECOMM
                    char purifiedWaterBuffer[10];
                    Communications::createSendMessage(purifiedWaterBuffer,purifiedWater_ID,String(dataStorage.data.purifiedWater).c_str());
                    sendGUIMessage(purifiedWaterBuffer);
                #endif
                delay(1000);
                output(UVRelay, 0);
                delay(250);
                output(ACInverter, 0);
            }

            if (!dataStorage.data.endPumpSt && !dataStorage.data.endBuoySt && dataStorage.data.lowPurifiedBuoySt)
            {
                debug(F("XD\n"));
                output(endPump, 1);
                endPumpPrevMillis = millis();
            }

            if (dataStorage.data.endPumpSt && (!dataStorage.data.lowPurifiedBuoySt || dataStorage.data.endBuoySt))
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
            if (voltRead() < configStorage.config.STOPWORKINGVOLTAGE)
                changePurificationStatus(TRANSITIONTOIDLE);
            #endif

            waitForVoltage(configStorage.config.STARTWORKINGVOLTAGE);
            filterPumpPrevMillis = millis();
            output(filterRelay, 1);

            changePurificationStatus(FILTERWORKING);
            break;

        case FILTERWORKING: // Filter Working
            #if !OVERRRIDEMAXVOLTAGE
            if (voltRead() < configStorage.config.STOPWORKINGVOLTAGE)
                changePurificationStatus(TRANSITIONTOIDLE);
            #endif

            if (dataStorage.data.highFilteredBuoySt || !dataStorage.data.lowSurfaceBuoySt)
            {
                output(filterRelay, 0);
                changePurificationStatus(TRANSITIONTOPUMPSWORKING);
            }
            break;
    }
#endif
}
