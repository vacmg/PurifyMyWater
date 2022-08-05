// Visual Micro

/*
    Name:       H2O_MASTER.ino
    Created:	24/08/2020 14:11:50
    Author:     vacmg
*/

//todo add eeprom config

#include <Arduino.h>

/*------------Config----------------*/

#define DEBUG true
#define USEVOLATILECONFIG true // used to disable EEPROM writes due to saving configuration in persistent storage
#define SETDEFAULTCONFIG false // used to set the config to the default config
#define ONLYVITALACTIVITYALLOWED false // used to disable purification routines
#define TEMPERATURE true
#define OVERRRIDEMAXVOLTAGE false // useful to check some functions without powering all the system

/*------------Config----------------*/

/*------------Libraries-------------*/

#include "Shared/SharedData.h"
#include "Storage/Storage.h"
#include "Purification/Purification.h"
#include <Filters.h>

/*------------Libraries-------------*/

// The setup() function runs once each time the micro-controller starts
// This function starts serial communication if defined, configures every input and output, set any other variable that needs to and waits for enough voltage in the capacitors to start operating
void setup()
{
#if DEBUG
    Serial.begin(115200);
    delay(500);
    debug(F("Setup - Booting...\n"));
#endif

#if USEVOLATILECONFIG
    debug(F("Using volatile settings (DEBUG MODE)\n"));
#endif

#if SETDEFAULTCONFIG
    debug(F("Using default configuration (DEBUG MODE)\n"));
    setDefaultConfig(); // load default settings
    updateConfig(); // save default settings to EEPROM
#else
    if(!readConfig()) // Try to read config, if failure, load default
    {
        debug(F("Failure loading configuration, restoring to default...\t"));
        setDefaultConfig(); // load default settings
        updateConfig(); // save default settings to EEPROM
        debug(F("Done\n"));
    }
    else
        debug(F("Configuration successfully load\n"));
#endif

    purificationSetup();

    debug(F("Setup - Ready\n"));
}

#if DEBUG

// temp vars (remove after debug)
unsigned long prevmillis, perf;

#endif

// Add the main program code into the continuous loop() function
// This function does things :D TODO make description
void loop()
{
    #if DEBUG
        prevmillis = millis();
        readAllSensors(); // temporal debug function
    #endif // DEBUG

    purificationLoop();

    #if DEBUG
        perf = millis() - prevmillis;
    #endif
}

#if DEBUG
void readAllSensors()
{
    bool esecBuoy, elowSurfaceBuoy, ehighSurfaceBuoy, elowFilteredBuoy, ehighFilteredBuoy, elowPurifiedBuoy, ehighPurifiedBuoy, eendBuoy;
    esecBuoy = digitalRead(secBuoy);
    elowSurfaceBuoy = digitalRead(lowSurfaceBuoy);
    ehighSurfaceBuoy = digitalRead(highSurfaceBuoy);
    elowFilteredBuoy = digitalRead(lowFilteredBuoy);
    ehighFilteredBuoy = digitalRead(highFilteredBuoy);
    elowPurifiedBuoy = digitalRead(lowPurifiedBuoy);
    ehighPurifiedBuoy = digitalRead(highPurifiedBuoy);
    eendBuoy = digitalRead(endBuoy);

    float ACAmps;
    ACAmps = getACAmps();

    float temp[3];
#if TEMPERATURE
    getSensorsTemp(temp);
#endif
    bool escreenSensor;
    escreenSensor = digitalRead(screenSensor);
    1 + 1; //todo remove this :D en serio
}
#endif
