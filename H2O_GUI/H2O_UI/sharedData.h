//
// Created by Víctor on 30/04/2022.
//

#ifndef H2O_GUI_SHAREDDATA_H
#define H2O_GUI_SHAREDDATA_H

#include <Arduino.h>

// Hardware constants

#define MAXCAPACITORSALLOWEDVOLTAGE 16
#define MINSYSTEMALLOWEDVOLTAGE 12

// Hardware constants

// Default Settings

// Electricity settings
float STARTCHARGINGVOLTAGE = 13; // STOPWORKINGVOLTAGE < STARTCHARGINGVOLTAGE < STOPCHARGINGVOLTAGE
float STOPCHARGINGVOLTAGE = 15.75; // STARTCHARGINGVOLTAGE < STOPCHARGINGVOLTAGE < MAXCAPACITORSALLOWEDVOLTAGE // leave at least 1 volt of margin between STARTCHARGINGVOLTAGE & STOPCHARGINGVOLTAGE
float STARTWORKINGVOLTAGE = 15; // STARTCHARGINGVOLTAGE < STARTWORKINGVOLTAGE < STOPCHARGINGVOLTAGE
float STOPWORKINGVOLTAGE = 12; // MINSYSTEMALLOWEDVOLTAGE < STOPWORKINGVOLTAGE < STARTCHARGINGVOLTAGE // // leave at least 1 volt of margin between STOPWORKINGVOLTAGE && STARTCHARGINGVOLTAGE

double DCAMPSENSITIVITY = 0.1135; //sensor sensitivity in Volts/Amps // 5.4A for 60w test load
double DCAMPZERO = 2.4956; // sensor voltage for 0 Amps current

double ACAMPZERO = -0.07157; // sensor calibration correction value
double ACAMPSENSITIVITY = 0.033; // sensor sensitivity in Volts/Amps // 0.25A for 60w test load
byte ACFREQUENCY = 50; // AC signal frequency (Hz)

float ESTIMATEDUVAMPERAGE = 1.0; // Minimum estimated current that the UV light uses // todo place real value

// Water settings
unsigned long WELLPUMPTIMEOUT = 60000;
unsigned long UVPUMPTIMEOUT = 60000;
unsigned long ENDPUMPTIMEOUT = 60000;
unsigned long FILTERTIMEOUT = 60000;
unsigned int UVPUMPFLOW = 55;

// Temperature settings
unsigned long TEMPCHECKTIME = 10000;
byte STOPWORKINGTEMP = 65;
byte MAXCASETEMP = 40;
byte MINCASETEMP = 38;
byte MAXPSUTEMP = 40;
byte MINPSUTEMP = 38;

#ifdef H2O_GUI
    // Interface settings
    enum Languages {ENGLISH = 0};
    Languages LANGUAGE = ENGLISH;
    unsigned long DATAREFRESHPERIOD = 5000;
#endif

// Default Settings

// Debug Functions

#if DEBUG
    #define debug(data) Serial.println(data)
    #define changeStatus(newStatus) debug(String(F("Mode changed from '")) +String(modeToString(screenStatus))+String(F("' to '"))+String(modeToString(newStatus))+String(F("'"))); screenStatus = newStatus
#else
    #define debug(data) ;
    #define changeStatus(newStaus) screenStatus = newStatus
#endif

#if H2O_GUI && DEBUG // H20_GUI ONLY
    const char mode0[] PROGMEM = "BOOTING"; // in order (BOOTING = 0 ---> mode0 = "BOOTING" --> modeTable[0] = mode0)
    const char mode1[] PROGMEM = "LOADSTATUS";
    const char mode2[] PROGMEM = "STATUS";
    const char mode3[] PROGMEM = "LOADMENU";
    const char mode4[] PROGMEM = "MENU";
    const char mode5[] PROGMEM = "LOADSETTINGS";
    const char mode6[] PROGMEM = "SETTINGS";
    const char mode7[] PROGMEM = "LOADHELP";
    const char mode8[] PROGMEM = "HELP";
    const char mode9[] PROGMEM = "LOADENGINEERINGMODE";
    const char mode10[] PROGMEM = "ENGINEERINGMODE";
    const char mode11[] PROGMEM = "LOADEXTRAFUNCTIONS";
    const char mode12[] PROGMEM = "EXTRAFUNCTIONS";
    const char mode13[] PROGMEM = "LOADELECTRICTY";
    const char mode14[] PROGMEM = "LOADPAGEELECTRICITY";
    const char mode15[] PROGMEM = "ELECTRICITY";
    const char mode16[] PROGMEM = "LOADINTERFACE";
    const char mode17[] PROGMEM = "LOADPAGEINTERFACE";
    const char mode18[] PROGMEM = "INTERFACE";
    const char mode19[] PROGMEM = "LOADWATER";
    const char mode20[] PROGMEM = "LOADPAGEWATER";
    const char mode21[] PROGMEM = "WATER";
    const char mode22[] PROGMEM = "LOADTEMPERATURE";
    const char mode23[] PROGMEM = "LOADPAGETEMPERATURE";
    const char mode24[] PROGMEM = "TEMPERATURE";

    const char *const modeTable[] PROGMEM = {mode0, mode1, mode2, mode3, mode4, mode5, mode6, mode7, mode8, mode9, mode10, mode11, mode12, mode13, mode14, mode15, mode16, mode17, mode18, mode19, mode20, mode21, mode22, mode23, mode24};
    char printModeBuff[20]; // Max size of any modeX string

    char* modeToString(ScreenStatus status)
    {
        strcpy_P(printModeBuff, (char *)pgm_read_word(&(modeTable[status])));
        return printModeBuff;
    }
#endif // H20_GUI ONLY

// Debug Functions

#endif //H2O_GUI_SHAREDDATA_H
