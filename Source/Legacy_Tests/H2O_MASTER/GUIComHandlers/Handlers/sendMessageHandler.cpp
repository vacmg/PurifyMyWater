//
// Created by Victor on 15/08/2022.
//

#include "sendMessageHandler.h"

void sendMessageHandler(enum VariableIDs variableID, char* value)
{
    //disconnectEverything();
    switch (variableID)
    {
        case BUSY_CMD:
            changeGUIStatus(GUI_BUSY_ST);
            debug(F("GUI is BUSY\n"));
            break;

        case AVAILABLE_CMD:
            changeGUIStatus(GUI_CONNECTED_ST);
            debug(F("GUI is READY\n"));
            break;

        case workingMode_ID:
            changeVariable(configStorage.config.workingMode,(WorkingMode)atoi(value));

            disconnectEverything();
            switch (configStorage.config.workingMode) // TODO trabajo aqui
            {
                case Purification_Off_Mode:
                    break;
                case DCPSU_Mode:
                    output(DCPSURelay, 1);
                    break;
                case ACPSU_Mode:
                    output(ACInverter, 1);
                    delay(500);
                    output(UVRelay, 1);
                    break;
                case Purification_On_Mode:
                    purificationStatus = IDLE;
                    break;
            }
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case STARTCHARGINGVOLTAGE_ID:
            changeVariable(configStorage.config.STARTCHARGINGVOLTAGE,atof(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case STOPCHARGINGVOLTAGE_ID:
            changeVariable(configStorage.config.STOPCHARGINGVOLTAGE,atof(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case STARTWORKINGVOLTAGE_ID:
            changeVariable(configStorage.config.STARTWORKINGVOLTAGE,atof(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case STOPWORKINGVOLTAGE_ID:
            changeVariable(configStorage.config.STOPWORKINGVOLTAGE,atof(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case DCAMMSENSITIVITY_ID:
            changeVariable(configStorage.config.DCAMMSENSITIVITY,atof(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case DCAMMZERO_ID:
            changeVariable(configStorage.config.DCAMMZERO,atof(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case ACAMMSENSITIVITY_ID:
            changeVariable(configStorage.config.ACAMMSENSITIVITY,atof(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case ACAMMZERO_ID:
            changeVariable(configStorage.config.ACAMMZERO,atof(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case ACFREQUENCY_ID:
            changeVariable(configStorage.config.ACFREQUENCY,(byte)atoi(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case ESTIMATEDUVAMPERAGE_ID:
            changeVariable(configStorage.config.ESTIMATEDUVAMPERAGE,atof(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case WELLPUMPTIMEOUT_ID:
            changeVariable(configStorage.config.WELLPUMPTIMEOUT,atol(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case UVPUMPTIMEOUT_ID:
            changeVariable(configStorage.config.UVPUMPTIMEOUT,atol(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case ENDPUMPTIMEOUT_ID:
            changeVariable(configStorage.config.ENDPUMPTIMEOUT,atol(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case FILTERTIMEOUT_ID:
            changeVariable(configStorage.config.FILTERTIMEOUT,atol(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case UVPUMPFLOW_ID:
            changeVariable(configStorage.config.UVPUMPFLOW,atof(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case TEMPCHECKTIME_ID:
            changeVariable(configStorage.config.TEMPCHECKTIME,atol(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case STOPWORKINGTEMP_ID:
            changeVariable(configStorage.config.STOPWORKINGTEMP,(byte)atoi(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case STARTCASETEMP_ID:
            changeVariable(configStorage.config.STARTCASETEMP,(byte)atoi(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case STOPCASETEMP_ID:
            changeVariable(configStorage.config.STOPCASETEMP,(byte)atoi(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case STARTPSUTEMP_ID:
            changeVariable(configStorage.config.STARTPSUTEMP,(byte)atoi(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case STOPPSUTEMP_ID:
            changeVariable(configStorage.config.STOPPSUTEMP,(byte)atoi(value));
            saveConfigMillis = millis();
            saveConfigTimerEnabled = true;
            break;

        case voltage_ID:
            changeVariable(dataStorage.data.voltage,atof(value));
            break;

        case ACUVAmps_ID:
            changeVariable(dataStorage.data.ACUVAmps,atof(value));
            break;

        case DCAmps_ID:
            changeVariable(dataStorage.data.DCAmps,atof(value));
            break;

        case purifiedWater_ID:
            changeVariable(dataStorage.data.purifiedWater,atof(value));
            break;

        case wellPumpSt_ID:
            changeVariable(dataStorage.data.wellPumpSt,atoi(value));
            break;

        case UVPumpSt_ID:
            changeVariable(dataStorage.data.UVPumpSt,atoi(value));
            break;

        case endPumpSt_ID:
            changeVariable(dataStorage.data.endPumpSt,atoi(value));
            break;

        case filterPumpSt_ID:
            changeVariable(dataStorage.data.filterPumpSt,atoi(value));
            break;

        case secBuoySt_ID:
            changeVariable(dataStorage.data.secBuoySt,atoi(value));
            break;

        case lowSurfaceBuoySt_ID:
            changeVariable(dataStorage.data.lowSurfaceBuoySt,atoi(value));
            break;

        case highSurfaceBuoySt_ID:
            changeVariable(dataStorage.data.highSurfaceBuoySt,atoi(value));
            break;

        case lowFilteredBuoySt_ID:
            changeVariable(dataStorage.data.lowFilteredBuoySt,atoi(value));
            break;

        case highFilteredBuoySt_ID:
            changeVariable(dataStorage.data.highFilteredBuoySt,atoi(value));
            break;

        case lowPurifiedBuoySt_ID:
            changeVariable(dataStorage.data.lowPurifiedBuoySt,atoi(value));
            break;

        case highPurifiedBuoySt_ID:
            changeVariable(dataStorage.data.highPurifiedBuoySt,atoi(value));
            break;

        case endBuoySt_ID:
            changeVariable(dataStorage.data.endBuoySt,atoi(value));
            break;

        case DATAREFRESHPERIOD_ID:
            changeVariable(configStorage.config.DATAREFRESHPERIOD, atol(value));
            break;

        default:
            debug(F("sendMessageHandler: Unknown variableID: "));debug(variableID);debug('\n');
    }
}
