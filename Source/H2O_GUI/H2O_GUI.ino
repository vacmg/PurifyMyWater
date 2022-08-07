// Visual Micro

/*
    Name:       H2O_MASTER.ino
    Created:	24/08/2020 14:11:50
    Author:     vacmg
*/

#include <Arduino.h>

/*------------Config----------------*/

#define DEBUG true

#define DISABLEUI false  // used to disable the UI screen module
#define DISABLECOMM false // used to disable communications module

#define SETDEFAULTSCREENCONFIG false // used to set the screenConfig to the default screenConfig
#define USEVOLATILECONFIG true // used to disable EEPROM writes due to saving configuration in the persistent storage

/*------------Config----------------*/

#include "Shared/SharedData.h"
#if !DISABLEUI
#include "UI/UI.h"
#endif

//Main Functions

void setup()
{
#if DEBUG
    Serial.begin(115200);
    delay(200);
    debug(F("Connected\n"));
    delay(50);
#endif

#if !DISABLEUI
    UISetup();
#endif

    setDefaultConfig(); // TODO read config from master

    debug('\n');
    //todo Test code after this line



    //while (true); // TODO delete or comment this

    //todo Test code before this line

    debug(F("\nSetup Done\n\n"));
    delay(50);
}

void loop()
{
#if !DISABLEUI
    UILoop();
#endif
}
