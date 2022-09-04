//
// Created by Victor on 15/08/2022.
//

#include "sendMessageHandler.h"

void sendMessageHandler(enum VariableIDs variableID, char* value)
{
    switch (variableID) {
        case systemStatus_ID: //TODO implement this
            configStorage.config.systemStatus = (SystemStatus)atoi(value);
            break;

        case workingMode_ID: //TODO implement this
            configStorage.config.workingMode = (WorkingMode)atoi(value);
            break;

        case STARTCHARGINGVOLTAGE_ID:
            configStorage.config.STARTCHARGINGVOLTAGE = atof(value);
            break;

        case STOPCHARGINGVOLTAGE_ID:
            configStorage.config.STOPCHARGINGVOLTAGE = atof(value);
            break;

        case STARTWORKINGVOLTAGE_ID:
            configStorage.config.STARTWORKINGVOLTAGE = atof(value);
            break;

        case STOPWORKINGVOLTAGE_ID:
            configStorage.config.STOPWORKINGVOLTAGE = atof(value);
            break;

        case DCAMMSENSITIVITY_ID:
            configStorage.config.DCAMMSENSITIVITY = atof(value);
            break;

        case DCAMMZERO_ID:
            configStorage.config.DCAMMZERO = atof(value);
            break;

        case ACAMMSENSITIVITY_ID:
            configStorage.config.ACAMMSENSITIVITY = atof(value);
            break;

        case ACAMMZERO_ID:
            configStorage.config.ACAMMZERO = atof(value);
            break;

        case ACFREQUENCY_ID:
            configStorage.config.ACFREQUENCY = (byte)atoi(value);
            break;

        case ESTIMATEDUVAMPERAGE_ID:
            configStorage.config.ESTIMATEDUVAMPERAGE = atof(value);
            break;

        case WELLPUMPTIMEOUT_ID:
            configStorage.config.WELLPUMPTIMEOUT = atol(value);
            break;

        case UVPUMPTIMEOUT_ID:
            configStorage.config.UVPUMPTIMEOUT = atol(value);
            break;

        case ENDPUMPTIMEOUT_ID:
            configStorage.config.ENDPUMPTIMEOUT = atol(value);
            break;

        case FILTERTIMEOUT_ID:
            configStorage.config.FILTERTIMEOUT = atol(value);
            break;

        case UVPUMPFLOW_ID:
            configStorage.config.UVPUMPFLOW = atof(value);
            break;

        case TEMPCHECKTIME_ID:
            configStorage.config.TEMPCHECKTIME = atol(value);
            break;

        case STOPWORKINGTEMP_ID:
            configStorage.config.STOPWORKINGTEMP = (byte)atoi(value);
            break;

        case STARTCASETEMP_ID:
            configStorage.config.STARTCASETEMP = (byte)atoi(value);
            break;

        case STOPCASETEMP_ID:
            configStorage.config.STOPCASETEMP = (byte)atoi(value);
            break;

        case STARTPSUTEMP_ID:
            configStorage.config.STARTPSUTEMP = (byte)atoi(value);
            break;

        case STOPPSUTEMP_ID:
            configStorage.config.STOPPSUTEMP = (byte)atoi(value);
            break;

        case voltage_ID:
            dataStorage.data.voltage = atof(value);
            break;

        case ACUVAmps_ID:
            dataStorage.data.ACUVAmps = atof(value);
            break;

        case DCAmps_ID:
            dataStorage.data.DCAmps = atof(value);
            break;

        case purifiedWater_ID:
            dataStorage.data.purifiedWater = atof(value);
            break;

        case wellPumpSt_ID:
            dataStorage.data.wellPumpSt = atoi(value);
            break;

        case UVPumpSt_ID:
            dataStorage.data.UVPumpSt = atoi(value);
            break;

        case endPumpSt_ID:
            dataStorage.data.endPumpSt = atoi(value);
            break;

        case filterPumpSt_ID:
            dataStorage.data.filterPumpSt = atoi(value);
            break;

        case secBuoySt_ID:
            dataStorage.data.secBuoySt = atoi(value);
            break;

        case lowSurfaceBuoySt_ID:
            dataStorage.data.lowSurfaceBuoySt = atoi(value);
            break;

        case highSurfaceBuoySt_ID:
            dataStorage.data.highSurfaceBuoySt = atoi(value);
            break;

        case lowFilteredBuoySt_ID:
            dataStorage.data.lowFilteredBuoySt = atoi(value);
            break;

        case highFilteredBuoySt_ID:
            dataStorage.data.highFilteredBuoySt = atoi(value);
            break;

        case lowPurifiedBuoySt_ID:
            dataStorage.data.lowPurifiedBuoySt = atoi(value);
            break;

        case highPurifiedBuoySt_ID:
            dataStorage.data.highPurifiedBuoySt = atoi(value);
            break;

        case endBuoySt_ID:
            dataStorage.data.endPumpSt = atoi(value);
            break;

        case screenSensorSt_ID:
            dataStorage.data.screenSensorSt = atoi(value);
            break;

        default:
            debug(F("sendMessageHandler: Unknown Variable ID"));
    }
}
