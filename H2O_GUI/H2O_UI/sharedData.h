//
// Created by Víctor on 30/04/2022.
//

#ifndef H2O_GUI_SHAREDDATA_H
#define H2O_GUI_SHAREDDATA_H

#include <Arduino.h>

namespace UI {
// Hardware constants

#define MAXCAPACITORSALLOWEDVOLTAGE 16
#define MINSYSTEMALLOWEDVOLTAGE 12
#define MAXUVAMPERAGE 10

// Hardware constants

// Default Settings

// Electricity settings
    extern float STARTCHARGINGVOLTAGE; // STOPWORKINGVOLTAGE < STARTCHARGINGVOLTAGE < STOPCHARGINGVOLTAGE
    extern float STOPCHARGINGVOLTAGE; // STARTCHARGINGVOLTAGE+1 < STOPCHARGINGVOLTAGE < MAXCAPACITORSALLOWEDVOLTAGE // leave at least 1 volt of margin between STARTCHARGINGVOLTAGE & STOPCHARGINGVOLTAGE
    extern float STARTWORKINGVOLTAGE; // STARTCHARGINGVOLTAGE < STARTWORKINGVOLTAGE < STOPCHARGINGVOLTAGE
    extern float STOPWORKINGVOLTAGE; // MINSYSTEMALLOWEDVOLTAGE < STOPWORKINGVOLTAGE < STARTCHARGINGVOLTAGE-1 // // leave at least 1 volt of margin between STOPWORKINGVOLTAGE && STARTCHARGINGVOLTAGE

    extern double DCAMPSENSITIVITY; //sensor sensitivity in Volts/Amps // 5.4A for 60w test load // No limits
    extern double DCAMPZERO; // sensor voltage for 0 Amps current // No limits

    extern double ACAMPZERO; // sensor calibration correction value // No limits
    extern double ACAMPSENSITIVITY; // sensor sensitivity in Volts/Amps // 0.25A for 60w test load // No limits
    extern byte ACFREQUENCY; // AC signal frequency (Hz) 50 <= ACFREQUENCY <= 60

    extern float ESTIMATEDUVAMPERAGE; // Minimum estimated current that the UV light uses // 0 < ESTIMATEDUVAMPERAGE < MAXUVAMPERAGE // todo place real value

// Water settings
    extern unsigned long WELLPUMPTIMEOUT; // Stored in ms, input in s (1s = 1000ms) // 0 < WELLPUMPTIMEOUT
    extern unsigned long UVPUMPTIMEOUT; // Stored in ms, input in s (1s = 1000ms) // 0 < UVPUMPTIMEOUT
    extern unsigned long ENDPUMPTIMEOUT; // Stored in ms, input in s (1s = 1000ms) // 0 < ENDPUMPTIMEOUT
    extern unsigned long FILTERTIMEOUT; // Stored in ms, input in s (1s = 1000ms) // 0 < FILTERTIMEOUT
    extern unsigned int UVPUMPFLOW; // L/H

// Temperature settings
    extern unsigned long TEMPCHECKTIME; // Stored in ms, input in s (1s = 1000ms) // 0 < TEMPCHECKTIME
    extern byte STOPWORKINGTEMP; // in Cº // 0 < STARTCASETEMP, STARTPSUTEMP < STOPWORKINGTEMP
    extern byte STARTCASETEMP; // in Cº // 0 < STOPCASETEMP < STARTCASETEMP
    extern byte STOPCASETEMP; // in Cº // 0 < STOPCASETEMP < STARTCASETEMP
    extern byte STARTPSUTEMP; // in Cº // 0 < STOPPSUTEMP < STARTPSUTEMP
    extern byte STOPPSUTEMP; // in Cº // 0 < STOPPSUTEMP < STARTPSUTEMP

#ifdef H2O_GUI
    // Interface settings
    enum Languages {ENGLISH = 0};
    extern Languages LANGUAGE;
    extern unsigned long DATAREFRESHPERIOD; // Stored in ms, input in s (1s = 1000ms) // 0 < DATAREFRESHPERIOD
#endif

// Default Settings

// Debug Functions

#if DEBUG
#define debug(data) Serial.println(data)
#define changeStatus(newStatus) debug(String(F("Mode changed from '")) +String(modeToString(screenStatus))+String(F("' to '"))+String(modeToString(newStatus))+String(F("'"))); screenStatus = newStatus
#else
#define debug(data) ;
#define changeStatus(newStatus) screenStatus = newStatus
#endif

// Debug Functions
}

#endif //H2O_GUI_SHAREDDATA_H
