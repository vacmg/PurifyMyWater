//
// Created by Víctor on 17/06/2022.
//

#include "sharedData.h"

namespace UI {
// Default Settings

// Electricity settings
    float STARTCHARGINGVOLTAGE = 13; // STOPWORKINGVOLTAGE < STARTCHARGINGVOLTAGE < STOPCHARGINGVOLTAGE
    float STOPCHARGINGVOLTAGE = 15.75; // STARTCHARGINGVOLTAGE+1 < STOPCHARGINGVOLTAGE < MAXCAPACITORSALLOWEDVOLTAGE // leave at least 1 volt of margin between STARTCHARGINGVOLTAGE & STOPCHARGINGVOLTAGE
    float STARTWORKINGVOLTAGE = 15; // STARTCHARGINGVOLTAGE < STARTWORKINGVOLTAGE < STOPCHARGINGVOLTAGE
    float STOPWORKINGVOLTAGE = 12; // MINSYSTEMALLOWEDVOLTAGE < STOPWORKINGVOLTAGE < STARTCHARGINGVOLTAGE-1 // // leave at least 1 volt of margin between STOPWORKINGVOLTAGE && STARTCHARGINGVOLTAGE

    double DCAMPSENSITIVITY = 0.1135; //sensor sensitivity in Volts/Amps // 5.4A for 60w test load // No limits
    double DCAMPZERO = 2.4956; // sensor voltage for 0 Amps current // No limits

    double ACAMPZERO = -0.07157; // sensor calibration correction value // No limits
    double ACAMPSENSITIVITY = 0.033; // sensor sensitivity in Volts/Amps // 0.25A for 60w test load // No limits
    byte ACFREQUENCY = 50; // AC signal frequency (Hz) 50 <= ACFREQUENCY <= 60

    float ESTIMATEDUVAMPERAGE = 1.0; // Minimum estimated current that the UV light uses // 0 < ESTIMATEDUVAMPERAGE < MAXUVAMPERAGE // todo place real value

// Water settings
    unsigned long WELLPUMPTIMEOUT = 60000; // Stored in ms, input in s (1s = 1000ms) // 0 < WELLPUMPTIMEOUT
    unsigned long UVPUMPTIMEOUT = 60000; // Stored in ms, input in s (1s = 1000ms) // 0 < UVPUMPTIMEOUT
    unsigned long ENDPUMPTIMEOUT = 60000; // Stored in ms, input in s (1s = 1000ms) // 0 < ENDPUMPTIMEOUT
    unsigned long FILTERTIMEOUT = 60000; // Stored in ms, input in s (1s = 1000ms) // 0 < FILTERTIMEOUT
    unsigned int UVPUMPFLOW = 55; // L/H

// Temperature settings
    unsigned long TEMPCHECKTIME = 10000; // Stored in ms, input in s (1s = 1000ms) // 0 < TEMPCHECKTIME
    byte STOPWORKINGTEMP = 65; // in Cº // 0 < STARTCASETEMP, STARTPSUTEMP < STOPWORKINGTEMP
    byte STARTCASETEMP = 40; // in Cº // 0 < STOPCASETEMP < STARTCASETEMP
    byte STOPCASETEMP = 38; // in Cº // 0 < STOPCASETEMP < STARTCASETEMP
    byte STARTPSUTEMP = 40; // in Cº // 0 < STOPPSUTEMP < STARTPSUTEMP
    byte STOPPSUTEMP = 38; // in Cº // 0 < STOPPSUTEMP < STARTPSUTEMP

#ifdef H2O_GUI
    // Interface settings
        Languages LANGUAGE = ENGLISH;
        unsigned long DATAREFRESHPERIOD = 5000; // Stored in ms, input in s (1s = 1000ms) // 0 < DATAREFRESHPERIOD
#endif

// Default Settings
}
