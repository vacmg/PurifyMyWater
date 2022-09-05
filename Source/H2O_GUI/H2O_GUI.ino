// Visual Micro

/*
    Name:       H2O_MASTER.ino
    Created:	24/08/2020 14:11:50
    Author:     vacmg
*/

#include <Arduino.h>

/*------------Config----------------*/

#define DEBUG true // Used to display debug information messages through Serial port

#define DISABLEUI true  // Used to disable the UI screen module
#define DISABLECOMM false // Used to disable communications module

#define SETDEFAULTSCREENCONFIG false // Used to set the screenConfig to the default screenConfig
#define USEVOLATILECONFIG true // Used to disable EEPROM writes due to saving configuration in the persistent storage

#if !DEBUG && (USEVOLATILECONFIG || SETDEFAULTSCREENCONFIG || DISABLEUI || DISABLECOMM)
#undef DEBUG
#define DEBUG true
#endif

/*------------Config----------------*/

#include "Shared/SharedData.h"

#if !DISABLEUI
#include "UI/UI.h"
#endif

#if !DISABLECOMM
#include "MasterComHandlers/MasterComHandlers.h"
#endif


//Main Functions

void setup()
{
    Serial.begin(9600);
    delay(200);
#if DEBUG
    debug(F("Setup - Booting...\n"));
    delay(50);
#endif
    Serial.print(F("PurifyMyWater UI version: "));Serial.print((__FlashStringHelper*)VERSION);Serial.print('\n');
#if DEBUG
    debug(F("Build date: "));debug((F(__TIMESTAMP__)));debug(F("\n\n"));
    delay(50);
#endif

    debug(F("\nCAUTION: NEVER use debug features on a deployed system, there is risk of IRREVERSIBLE DAMAGE to the system\n\nUsing those debug features:\n"));

    debug(F("DEBUG\t\t\t- Used to display debug information messages through Serial port\n"));
#if DISABLEUI
    debug(F("DISABLEUI\t\t- Used to disable the UI screen module\n"));
#endif
#if DISABLECOMM
    debug(F("DISABLECOMM\t\t- Used to disable communications module\n"));
#endif
#if SETDEFAULTSCREENCONFIG
    debug(F("SETDEFAULTSCREENCONFIG\t- Used to set the screenConfig to the default screenConfig\n"));
#endif
#if USEVOLATILECONFIG
    debug(F("USEVOLATILECONFIG\t- Used to disable EEPROM writes due to saving configuration in the persistent storage\n"));
#endif
    debug('\n');
    delay(50);

#if !DISABLEUI
    UISetup();
#endif

    setDefaultConfig(); // TODO read config from master

    //todo Test code after this line

    //while (true); // TODO delete or comment this

    //todo Test code before this line

    debug(F("Setup - Ready\n\n"));
    delay(50);
}

void loop()
{
#if !DISABLECOMM
    masterComLoop();
#endif
#if !DISABLEUI
    UILoop();
#endif
}
