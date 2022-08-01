//
// Created by Víctor on 30/04/2022.
//

#ifndef H2O_GUI_SHAREDDATA_H
#define H2O_GUI_SHAREDDATA_H

#include <Arduino.h>

// Hardware constants

enum Errors {NoError = 0}; // Used to process different errors

#define MAXCAPACITORSALLOWEDVOLTAGE 16
#define MINSYSTEMALLOWEDVOLTAGE 12
#define MAXUVAMPERAGE 10

// Hardware constants

enum Errors currentError = NoError; // This variable stores the error that the system has in a particular time TODO join MASTER & GUI errors

// Purification status
enum PurificationStatus {OFF = 0, ON = 1};

typedef struct Configuration {
    enum PurificationStatus purificationStatus; // Used to store whether the purification system is on or off
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

} Config;

// This variable stores the system configuration

Config config = {};

void setDefaultConfig()
{
    config = {
            OFF,13,15.75,15,12,0.1135,2.4956,
            -0.07157,0.033,50,1.0,60000,60000,60000,60000,
            55,10000,65,40,38,40,38
    };
}

// Debug Functions

#ifndef debug(data)
    #if DEBUG
        #define debug(data) Serial.print(data)
    #else
        #define debug(data) ;
    #endif
#endif

#if DEBUG
    char debugBuff[50] = "";

    const char purificationStatusOFF_STR[] PROGMEM = "OFF";
    const char purificationStatusON_STR[] PROGMEM = "ON";

    const char *const debugConfigTable[] PROGMEM = {purificationStatusOFF_STR, purificationStatusON_STR};

    char* purificationStatusToString(enum PurificationStatus status)
    {
        strcpy_P(debugBuff, (char *)pgm_read_word(&(debugConfigTable[status])));
        return debugBuff;
    }

    void printConfiguration()
    {
        debug(F("Current config:\n"));
        Serial.print(F("Purification status:\t"));Serial.println(purificationStatusToString(config.purificationStatus));
        Serial.print(F("STARTCHARGINGVOLTAGE:\t"));Serial.println(config.STARTCHARGINGVOLTAGE);
        Serial.print(F("STOPCHARGINGVOLTAGE:\t"));Serial.println(config.STOPCHARGINGVOLTAGE);
        Serial.print(F("STARTWORKINGVOLTAGE:\t"));Serial.println(config.STARTWORKINGVOLTAGE);
        Serial.print(F("STOPWORKINGVOLTAGE:\t"));Serial.println(config.STOPWORKINGVOLTAGE);
        Serial.print(F("DCAMMSENSITIVITY:\t"));Serial.println(config.DCAMMSENSITIVITY);
        Serial.print(F("DCAMMZERO:\t"));Serial.println(config.DCAMMZERO);
        Serial.print(F("ACAMMSENSITIVITY:\t"));Serial.println(config.ACAMMSENSITIVITY);
        Serial.print(F("ACAMMZERO:\t"));Serial.println(config.ACAMMZERO);
        Serial.print(F("ACFREQUENCY:\t"));Serial.println(config.ACFREQUENCY);
        Serial.print(F("ESTIMATEDUVAMPERAGE:\t"));Serial.println(config.ESTIMATEDUVAMPERAGE);
        Serial.print(F("WELLPUMPTIMEOUT:\t"));Serial.println(config.WELLPUMPTIMEOUT);
        Serial.print(F("UVPUMPTIMEOUT:\t"));Serial.println(config.UVPUMPTIMEOUT);
        Serial.print(F("ENDPUMPTIMEOUT:\t"));Serial.println(config.ENDPUMPTIMEOUT);
        Serial.print(F("FILTERTIMEOUT:\t"));Serial.println(config.FILTERTIMEOUT);
        Serial.print(F("UVPUMPFLOW:\t"));Serial.println(config.UVPUMPFLOW);
        Serial.print(F("TEMPCHECKTIME:\t"));Serial.println(config.TEMPCHECKTIME);
        Serial.print(F("STOPWORKINGTEMP:\t"));Serial.println(config.STOPWORKINGTEMP);
        Serial.print(F("STARTCASETEMP:\t"));Serial.println(config.STARTCASETEMP);
        Serial.print(F("STOPCASETEMP:\t"));Serial.println(config.STOPCASETEMP);
        Serial.print(F("STARTPSUTEMP:\t"));Serial.println(config.STARTPSUTEMP);
        Serial.print(F("STOPPSUTEMP:\t"));Serial.println(config.STOPPSUTEMP);
        Serial.println();
    }

    #define debugConfig() printConfiguration()
#else
    #define debugConfig() ;
#endif

// Debug Functions

#endif //H2O_GUI_SHAREDDATA_H
