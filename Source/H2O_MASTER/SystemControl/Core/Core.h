//
// Created by Victor on 07/08/2022.
//

#ifndef H2O_MASTER_CORE_H
#define H2O_MASTER_CORE_H

#include "../../Shared/SharedData.h"
#include "../../Storage/Storage.h"

#if !DISABLECOMM
#include "../../GUIComHandlers/GUIComHandlers.h"
#endif

enum PurificationStatus
{
    TRANSITIONTOIDLE,
    IDLE,
    TRANSITIONTOPUMPSWORKING,
    PUMPSWORKING,
    TRANSITIONTOFILTERWORKING,
    FILTERWORKING
};

enum PurificationStatus purificationStatus = TRANSITIONTOIDLE; // Purification current status is changed using this variable
unsigned long UVMillis = 0;
#if !DISABLECOMM
unsigned long sendVoltageMillis = 0;
#endif
unsigned long workingTime = 0; // Time that UV pump is working (in ms) // Used to calculate the amount of purified water

#if DEBUG

#define changePurificationStatus(newStatus) debug(F("purificationStatus changed from '"));debug(purificationModeToString(purificationStatus));debug(F("' to '"));debug(purificationModeToString(newStatus));debug(F("'\n")); purificationStatus = newStatus

const char pmode0[] PROGMEM = "TRANSITIONTOIDLE";
const char pmode1[] PROGMEM = "IDLE";
const char pmode2[] PROGMEM = "TRANSITIONTOPUMPSWORKING";
const char pmode3[] PROGMEM = "PUMPSWORKING";
const char pmode4[] PROGMEM = "TRANSITIONTOFILTERWORKING";
const char pmode5[] PROGMEM = "FILTERWORKING";

const char *const debugPurificationModeTable[] PROGMEM = {pmode0, pmode1, pmode2, pmode3, pmode4, pmode5};

char* purificationModeToString(enum PurificationStatus status)
{
    strcpy_P(debugBuff, (char *)pgm_read_word(&(debugPurificationModeTable[status])));
    return debugBuff;
}

#else

#define changePurificationStatus(newStatus) purificationStatus = newStatus

#endif

#include "IO.h"
#include "Electricity.h"

// This is the core setup code, which no matter which module is enabled, those instructions must be executed
void coreSetup();

// This is the core loop code, which no matter which module is enabled, those instructions must be executed every main loop execution
void coreLoop();

// Quick shortcut to disconnect every pump or relay
void disconnectEverything();
void disconnectEverything(bool withVoltage);

// This function will check for hardware errors on the system
void errorCheck();

#if !DISABLECOMM
// This function will send periodically the voltage to the screen MCU
void sendVoltage();
#endif

// This function will allow to notify the user about the error
// and redirect the execution to an "onlyVitalActivities" function if it is critical
// or resume the program if it is not
// This function is not completed yet
void raiseFn(enum Errors error, const String& possibleExplanation, const String& file, const uint16_t line);
#define raise(error, possibleExplanation) raiseFn(error, possibleExplanation, F(__FILE__), __LINE__)

#include "Core.cpp"

#endif //H2O_MASTER_CORE_H
