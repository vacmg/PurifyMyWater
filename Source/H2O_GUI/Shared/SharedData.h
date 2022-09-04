//
// Created by Víctor on 30/04/2022.
//

#ifndef H2O_GUI_SHAREDDATA_H
#define H2O_GUI_SHAREDDATA_H

#include <Arduino.h>

// Hardware constants

#define MAXCAPACITORSALLOWEDVOLTAGE 16
#define MINSYSTEMALLOWEDVOLTAGE 12
#define MAXUVAMPERAGE 10

// Hardware constants

// Global data types

#define MAXVERSIONSIZE 16
const char VERSION[] PROGMEM = "v2-alpha-1"; // MAXIMUN size is 16 bytes

// It must have a maximum of 254 members
enum VariableIDs {VERSION_ID = 1, OK_CMD, SHUTDOWN_CMD, SHUTDOWN_OK_CMD, SHUTDOWN_CANCEL_CMD, BUSY_CMD, AVAILABLE_CMD, // Other messages/commands are self-contained here
        voltage_ID, ACUVAmps_ID, DCAmps_ID, purifiedWater_ID, wellPumpSt_ID, UVPumpSt_ID, endPumpSt_ID, filterPumpSt_ID, secBuoySt_ID, lowSurfaceBuoySt_ID, highSurfaceBuoySt_ID, lowFilteredBuoySt_ID, highFilteredBuoySt_ID, lowPurifiedBuoySt_ID, highPurifiedBuoySt_ID, endBuoySt_ID, screenSensorSt_ID, // Data
    systemStatus_ID, workingMode_ID, STARTCHARGINGVOLTAGE_ID, STOPCHARGINGVOLTAGE_ID, STARTWORKINGVOLTAGE_ID, STOPWORKINGVOLTAGE_ID, DCAMMSENSITIVITY_ID, DCAMMZERO_ID, ACAMMSENSITIVITY_ID, ACAMMZERO_ID, ACFREQUENCY_ID, ESTIMATEDUVAMPERAGE_ID, WELLPUMPTIMEOUT_ID, UVPUMPTIMEOUT_ID, ENDPUMPTIMEOUT_ID, FILTERTIMEOUT_ID, UVPUMPFLOW_ID, TEMPCHECKTIME_ID, STOPWORKINGTEMP_ID, STARTCASETEMP_ID, STOPCASETEMP_ID, STARTPSUTEMP_ID, STOPPSUTEMP_ID // Config
};

// It must have a maximum of 254 members
enum FunctionIDs {};

enum Errors {
    NoError = 0, BuoyIncongruenceError, PumpTimeoutError,
    UVLightNotWorkingError, ScreenNotConnectedError, TempSensorsAmountError,
    HotTempError,
    HandshakeError, MCUsIncompatibleVersionError, DestinationMCUNotRespondingError, GUICannotSafelyShutdownError,
    ScreenNotImplementedError
    }; // Used to process different errors

enum SystemStatus {SYSTEM_OFF = 0, SYSTEM_ON = 1}; // This struct stores if the system is working or not (think about it like a master switch)

enum WorkingMode {Purification_Mode, DCPSU_Mode, ACPSU_Mode}; // This struct stores the system working mode which can be the default purification mode and some alternative uses of the system

// This struct stores all the system configuration
struct Configuration // TODO create a toStr & toStruct functions to send the whole config (union?)
{
    enum SystemStatus systemStatus; // Used to store whether the purification system is on or off // TODO implement this
    enum WorkingMode workingMode; // Used to store the current system mode // TODO implement this

    // Electricity settings
    float STARTCHARGINGVOLTAGE; // STOPWORKINGVOLTAGE < STARTCHARGINGVOLTAGE < STOPCHARGINGVOLTAGE
    float STOPCHARGINGVOLTAGE; // STARTCHARGINGVOLTAGE+1 < STOPCHARGINGVOLTAGE < MAXCAPACITORSALLOWEDVOLTAGE // leave at least 1 volt of margin between STARTCHARGINGVOLTAGE & STOPCHARGINGVOLTAGE
    float STARTWORKINGVOLTAGE; // STARTCHARGINGVOLTAGE < STARTWORKINGVOLTAGE < STOPCHARGINGVOLTAGE
    float STOPWORKINGVOLTAGE; // MINSYSTEMALLOWEDVOLTAGE < STOPWORKINGVOLTAGE < STARTCHARGINGVOLTAGE-1 // // leave at least 1 volt of margin between STOPWORKINGVOLTAGE && STARTCHARGINGVOLTAGE
    double DCAMMSENSITIVITY; //sensor sensitivity in Volts/Amps // 5.4A for 60w test load // No limits
    double DCAMMZERO; // sensor voltage for 0 Amps current // No limits
    double ACAMMSENSITIVITY; // sensor sensitivity in Volts/Amps // 0.25A for 60w test load // No limits
    double ACAMMZERO; // sensor calibration correction value // No limits
    byte ACFREQUENCY; // AC signal frequency (Hz) 50 <= ACFREQUENCY <= 60
    float ESTIMATEDUVAMPERAGE; // Minimum estimated current that the UV light uses // 0 < ESTIMATEDUVAMPERAGE < MAXUVAMPERAGE // todo place real value

    // Water settings
    unsigned long WELLPUMPTIMEOUT; // Stored in ms, input in s (1s = 1000ms) // 0 < WELLPUMPTIMEOUT
    unsigned long UVPUMPTIMEOUT; // Stored in ms, input in s (1s = 1000ms) // 0 < UVPUMPTIMEOUT
    unsigned long ENDPUMPTIMEOUT; // Stored in ms, input in s (1s = 1000ms) // 0 < ENDPUMPTIMEOUT
    unsigned long FILTERTIMEOUT; // Stored in ms, input in s (1s = 1000ms) // 0 < FILTERTIMEOUT
    float UVPUMPFLOW; // Stored in ms, input in s (1s = 1000ms) // 0 < UVPUMPTIMEOUT

    // Temperature settings
    unsigned long TEMPCHECKTIME; // Stored in ms, input in s (1s = 1000ms) // 0 < TEMPCHECKTIME
    byte STOPWORKINGTEMP; // in Cº // 0 < STARTCASETEMP, STARTPSUTEMP < STOPWORKINGTEMP
    byte STARTCASETEMP; // in Cº // 0 < STOPCASETEMP < STARTCASETEMP
    byte STOPCASETEMP; // in Cº // 0 < STOPCASETEMP < STARTCASETEMP
    byte STARTPSUTEMP; // in Cº // 0 < STOPPSUTEMP < STARTPSUTEMP
    byte STOPPSUTEMP; // in Cº // 0 < STOPPSUTEMP < STARTPSUTEMP
};

#define DEFAULTCONFIG {SYSTEM_OFF,Purification_Mode,13,15.75,15,12,0.1135,2.4956,-0.07157,0.033,50,1.0,60000,60000,60000,60000,55,10000,65,40,38,40,38}

typedef union ConfigurationUnion
{
    struct Configuration config;
    char binConfig[sizeof(struct Configuration)];
}Config;

// This struct stores all the relevant data used to control the system
struct SharedData // TODO create a toStr & toStruct functions to send the whole config
{
    float voltage; // System current voltage
    float ACUVAmps; // UV current (AC 230V)
    float DCAmps; // System current (DC 12V)

    double purifiedWater; // Amount of water purified since the start of the machine (in L)

    // Used to store the status of each pump and also the filter where true is on and false is off
    bool wellPumpSt;
    bool UVPumpSt;
    bool endPumpSt;
    bool filterPumpSt;

    // Used to store the status of each particular sensor where true is activated and false is deactivated
    bool secBuoySt;
    bool lowSurfaceBuoySt;
    bool highSurfaceBuoySt;
    bool lowFilteredBuoySt;
    bool highFilteredBuoySt;
    bool lowPurifiedBuoySt;
    bool highPurifiedBuoySt;
    bool endBuoySt;
    bool screenSensorSt; // TODO remove from sharedData (variable is exclusive to master)

};

typedef union SharedDataUnion
{
    struct SharedData data;
    char binData[sizeof(struct SharedData)];
}Data;

// Global data types

// Global variables

// This variable stores the system configuration
Config configStorage = DEFAULTCONFIG;

// This variable stores all the relevant data used to control the system
Data dataStorage = {0.0F,0.0F,0.0F,0.0, false,false,false,false,false,false,false,false,false,false,false,false,false};

// This variable stores the error that the system has in a particular time
enum Errors currentError = NoError;

// Global variables

// Global functions

// This function restores the default configuration in the system
void setDefaultConfig()
{
    configStorage = DEFAULTCONFIG;
}

// Global functions

// Debug Functions

#ifndef debug(data)
    #if DEBUG
        #define debug(data) Serial.print(data)
        #define changeVariable(variable, value) debug(F(#variable));debug(F(" changed from "));debug(variable);debug(F(" to "));debug(value);debug('\n'); (variable) = value
    #else
        #define debug(data) ;
        #define changeVariable(variable, value) variable = value
    #endif
#endif

#if DEBUG
    bool printArray(const char* array, unsigned int len)
    {
        for(int i = 0;i<len;i++)
        {
            unsigned char c = array[i];
            if(c<10)
            {
                Serial.print("00");
            }
            else if (c<100)
            {
                Serial.print("0");
            }
            Serial.print((char)c,DEC);
            Serial.print(F(" "));
        }
        return true;
}

    char debugBuff[50] = "";

    const char systemStatusOFF_STR[] PROGMEM = "OFF";
    const char systemStatusON_STR[] PROGMEM = "ON";

    const char *const debugSystemStatusTable[] PROGMEM = {systemStatusOFF_STR, systemStatusON_STR};

    char* systemStatusToString(enum SystemStatus status)
    {
        strcpy_P(debugBuff, (char *)pgm_read_word(&(debugSystemStatusTable[status])));
        return debugBuff;
    }

    const char workingMode_Purification_Mode_STR[] PROGMEM = "Purification_Mode";
    const char workingMode_DCPSU_Mode_STR[] PROGMEM = "DCPSU_Mode";
    const char workingMode_ACPSU_Mode_STR[] PROGMEM = "ACPSU_Mode";

    const char *const debugWorkingModeTable[] PROGMEM = {workingMode_Purification_Mode_STR, workingMode_DCPSU_Mode_STR, workingMode_ACPSU_Mode_STR};

    char* workingModeToString(enum WorkingMode mode)
    {
        strcpy_P(debugBuff, (char *)pgm_read_word(&(debugWorkingModeTable[mode])));
        return debugBuff;
    }

    void printConfiguration()
    {
        debug(F("Current config:\n"));
        Serial.print(F("System status:\t"));Serial.println(systemStatusToString(configStorage.config.systemStatus));
        Serial.print(F("Working mode:\t"));Serial.println(workingModeToString(configStorage.config.workingMode));
        Serial.print(F("STARTCHARGINGVOLTAGE:\t"));Serial.println(configStorage.config.STARTCHARGINGVOLTAGE);
        Serial.print(F("STOPCHARGINGVOLTAGE:\t"));Serial.println(configStorage.config.STOPCHARGINGVOLTAGE);
        Serial.print(F("STARTWORKINGVOLTAGE:\t"));Serial.println(configStorage.config.STARTWORKINGVOLTAGE);
        Serial.print(F("STOPWORKINGVOLTAGE:\t"));Serial.println(configStorage.config.STOPWORKINGVOLTAGE);
        Serial.print(F("DCAMMSENSITIVITY:\t"));Serial.println(configStorage.config.DCAMMSENSITIVITY);
        Serial.print(F("DCAMMZERO:\t"));Serial.println(configStorage.config.DCAMMZERO);
        Serial.print(F("ACAMMSENSITIVITY:\t"));Serial.println(configStorage.config.ACAMMSENSITIVITY);
        Serial.print(F("ACAMMZERO:\t"));Serial.println(configStorage.config.ACAMMZERO);
        Serial.print(F("ACFREQUENCY:\t"));Serial.println(configStorage.config.ACFREQUENCY);
        Serial.print(F("ESTIMATEDUVAMPERAGE:\t"));Serial.println(configStorage.config.ESTIMATEDUVAMPERAGE);
        Serial.print(F("WELLPUMPTIMEOUT:\t"));Serial.println(configStorage.config.WELLPUMPTIMEOUT);
        Serial.print(F("UVPUMPTIMEOUT:\t"));Serial.println(configStorage.config.UVPUMPTIMEOUT);
        Serial.print(F("ENDPUMPTIMEOUT:\t"));Serial.println(configStorage.config.ENDPUMPTIMEOUT);
        Serial.print(F("FILTERTIMEOUT:\t"));Serial.println(configStorage.config.FILTERTIMEOUT);
        Serial.print(F("UVPUMPFLOW:\t"));Serial.println(configStorage.config.UVPUMPFLOW);
        Serial.print(F("TEMPCHECKTIME:\t"));Serial.println(configStorage.config.TEMPCHECKTIME);
        Serial.print(F("STOPWORKINGTEMP:\t"));Serial.println(configStorage.config.STOPWORKINGTEMP);
        Serial.print(F("STARTCASETEMP:\t"));Serial.println(configStorage.config.STARTCASETEMP);
        Serial.print(F("STOPCASETEMP:\t"));Serial.println(configStorage.config.STOPCASETEMP);
        Serial.print(F("STARTPSUTEMP:\t"));Serial.println(configStorage.config.STARTPSUTEMP);
        Serial.print(F("STOPPSUTEMP:\t"));Serial.println(configStorage.config.STOPPSUTEMP);
        Serial.println();
    }

    #define debugConfig() printConfiguration()

    const char errorNoError_STR[] PROGMEM = "NoError";
    const char errorBuoyIncongruenceError_STR[] PROGMEM = "BuoyIncongruenceError";
    const char errorPumpTimeoutError_STR[] PROGMEM = "PumpTimeoutError";
    const char errorUVLightNotWorkingError_STR[] PROGMEM = "UVLightNotWorkingError";
    const char errorScreenNotConnectedError_STR[] PROGMEM = "ScreenNotConnectedError";
    const char errorTempSensorsAmountError_STR[] PROGMEM = "TempSensorsAmountError";
    const char errorHotTempError_STR[] PROGMEM = "HotTempError";
    const char errorHandshakeError_STR[] PROGMEM = "HandshakeError";
    const char errorMCUsIncompatibleVersionError_STR[] PROGMEM = "MCUsIncompatibleVersionError";
    const char errorDestinationMCUNotRespondingError_STR[] PROGMEM = "DestinationMCUNotRespondingError";
    const char errorGUICannotSafelyShutdownError_STR[] PROGMEM = "GUICannotSafelyShutdownError";

    const char *const debugErrorsTable[] PROGMEM = {errorNoError_STR, errorBuoyIncongruenceError_STR, errorPumpTimeoutError_STR, errorUVLightNotWorkingError_STR, errorScreenNotConnectedError_STR, errorTempSensorsAmountError_STR, errorHotTempError_STR, errorHandshakeError_STR, errorMCUsIncompatibleVersionError_STR, errorDestinationMCUNotRespondingError_STR, errorGUICannotSafelyShutdownError_STR};

    char* errorToString(enum Errors error)
    {
        strcpy_P(debugBuff, (char *)pgm_read_word(&(debugErrorsTable[error])));
        return debugBuff;
    }

void printSharedData()
{
    debug(F("Current data:\n"));
    Serial.print(F("Current Error:\t"));Serial.println(errorToString(currentError));
    Serial.print(F("\nvoltage:\t"));Serial.println(dataStorage.data.voltage);
    Serial.print(F("ACUVAmps:\t"));Serial.println(dataStorage.data.ACUVAmps);
    Serial.print(F("DCAmps:\t"));Serial.println(dataStorage.data.DCAmps);
    Serial.print(F("\npurifiedWater:\t"));Serial.println(dataStorage.data.purifiedWater);
    Serial.print(F("\nwellPumpSt:\t"));Serial.println(dataStorage.data.wellPumpSt);
    Serial.print(F("UVPumpSt:\t"));Serial.println(dataStorage.data.UVPumpSt);
    Serial.print(F("endPumpSt:\t"));Serial.println(dataStorage.data.endPumpSt);
    Serial.print(F("filterPumpSt:\t"));Serial.println(dataStorage.data.filterPumpSt);
    Serial.print(F("\nsecBuoySt:\t"));Serial.println(dataStorage.data.secBuoySt);
    Serial.print(F("lowSurfaceBuoySt:\t"));Serial.println(dataStorage.data.lowSurfaceBuoySt);
    Serial.print(F("highSurfaceBuoySt:\t"));Serial.println(dataStorage.data.highSurfaceBuoySt);
    Serial.print(F("lowFilteredBuoySt:\t"));Serial.println(dataStorage.data.lowFilteredBuoySt);
    Serial.print(F("highFilteredBuoySt:\t"));Serial.println(dataStorage.data.highFilteredBuoySt);
    Serial.print(F("lowPurifiedBuoySt:\t"));Serial.println(dataStorage.data.lowPurifiedBuoySt);
    Serial.print(F("highPurifiedBuoySt:\t"));Serial.println(dataStorage.data.highPurifiedBuoySt);
    Serial.print(F("endBuoySt:\t"));Serial.println(dataStorage.data.endBuoySt);
    Serial.print(F("screenSensorSt:\t"));Serial.println(dataStorage.data.screenSensorSt);
    Serial.println();
}

#define debugData() printSharedData()

#else
    #define debugConfig() ;
    #define debugData() ;
#endif

// Debug Functions

#endif //H2O_GUI_SHAREDDATA_H
