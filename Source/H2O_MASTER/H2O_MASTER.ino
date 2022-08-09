// Visual Micro

/*
    Name:       H2O_MASTER.ino
    Created:	24/08/2020 14:11:50
    Author:     vacmg
*/

#include <Arduino.h>

/*------------Config----------------*/

#define DEBUG true

#define USEVOLATILECONFIG true // used to disable EEPROM writes due to saving configuration in the persistent storage
#define SETDEFAULTCONFIG false // used to set the config to the default config

#define DISABLEHARDWARECHECKS true // used to disable check routines to detect faulty hardware
#define DISABLEPURIFICATION true // used to disable purification control systems
#define DISABLETEMPERATURE true // used to disable temperature control systems

#define OVERRRIDEMAXVOLTAGE false // useful to check some functions without powering all the system

/*------------Config----------------*/

/*------------Libraries-------------*/

#include "Shared/SharedData.h"
#include "Storage/Storage.h"
#include "Communications/ComManager.h"
#include "SystemControl/Core/Core.h"
#if !DISABLETEMPERATURE
#include "SystemControl/Temperature.h"
#endif
#if !DISABLEPURIFICATION
#include "SystemControl/Purification.h"
#endif
#include <Filters.h>

/*------------Libraries-------------*/


#if DEBUG
void readAllSensors();
#endif

// The setup() function runs once each time the microcontroller starts
// This function starts serial communication if defined, configures every input and output, set any other variable that needs to and waits for enough voltage in the capacitors to start operating
void setup()
{
#if DEBUG
    Serial.begin(115200);
    delay(200);
    debug(F("Setup - Booting...\n"));
    delay(50);
    debug(F("Purification system version: "));debug((__FlashStringHelper*)VERSION);debug(F("\n\n"));
    delay(50);
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
    {
#if USEVOLATILECONFIG
        setDefaultConfig();
#endif
        debug(F("Configuration successfully load\n"));
    }
#endif

    coreSetup();
#if !DISABLETEMPERATURE
    tempSetup();
#endif
#if !DISABLEPURIFICATION
    purificationSetup();
#endif

//todo Test code after this line

    ComManager comManager(&Serial1);
    comManager.commSetup();

    //while (true); // TODO delete or comment this

    //todo Test code before this line

    debug(F("Setup - Ready\n\n"));
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

    coreLoop();
#if !DISABLETEMPERATURE
    tempLoop();
#endif
#if !DISABLEPURIFICATION
    purificationLoop();
#endif

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

#if !DISABLETEMPERATURE
    float temp[3];
    getSensorsTemp(temp);
#endif
    bool escreenSensor;
    escreenSensor = digitalRead(screenSensor);
    1 + 1; //todo remove this :D en serio
}
#endif
