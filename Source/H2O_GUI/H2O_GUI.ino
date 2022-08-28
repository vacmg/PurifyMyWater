// Visual Micro

/*
    Name:       H2O_MASTER.ino
    Created:	24/08/2020 14:11:50
    Author:     vacmg
*/

#include <Arduino.h>

/*------------Config----------------*/

#define DEBUG true

#define DISABLEUI true  // used to disable the UI screen module
#define DISABLECOMM false // used to disable communications module // TODO implement it

#define SETDEFAULTSCREENCONFIG false // used to set the screenConfig to the default screenConfig
#define USEVOLATILECONFIG true // used to disable EEPROM writes due to saving configuration in the persistent storage

/*------------Config----------------*/

#include "Shared/SharedData.h"

#if !DISABLEUI
#include "UI/UI.h"
#endif

#if !DISABLECOMM
#include "Shared/Communications/ComManager.h"
#include "MasterCommHandlers/MasterCommHandlers.h"
#else
// TODO create ';' macros to disable communication functions
#endif


// TODO delete this
void testSendMessageHandler(enum VariableIDs variableID, char* value);
ComManager com(&Serial1, &testSendMessageHandler, nullptr, nullptr);
void testSendMessageHandler(enum VariableIDs variableID, char* value)
{
    if(variableID==SHUTDOWN_CMD)
    {
        debug(F("Shutdown cmd received\n"));
        char message[3];
        Communications::createSendMessage(message,SHUTDOWN_OK_CMD,"");
        com.sendMessage(message);
    }
}

//Main Functions

void setup()
{
#if DEBUG
    Serial.begin(9600);
    delay(200);
    debug(F("Setup - Booting...\n"));
    delay(50);
    debug(F("PurifyMyWater UI version: "));debug((__FlashStringHelper*)VERSION);debug(F("\n\n"));
    delay(50);
#endif

#if !DISABLEUI
    UISetup();
#endif

    setDefaultConfig(); // TODO read config from master

    //todo Test code after this line

    com.commSetup();

    while (true)
    {
        com.commLoop();
    }

    /*Serial1.begin(COMMANAGERBAUDRATE);
    debug(F("Starting mirror mode\n\n"));
    delay(100);
    while (true)
    {
        if(Serial1.available())
            Serial.write(Serial1.read());
    }*/

    while (true); // TODO delete or comment this

    //todo Test code before this line

    debug(F("Setup - Ready\n\n"));
    delay(50);
}

void loop()
{
#if !DISABLEUI
    UILoop();
#endif
}
