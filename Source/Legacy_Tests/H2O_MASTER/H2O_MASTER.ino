// Visual Micro

/*
    Name:       H2O_MASTER.ino
    Created:	24/08/2020 14:11:50
    Author:     vacmg
*/

#include <Arduino.h>

/*------------Config----------------*/

#include "Compile_Flags.h"

/*------------Config----------------*/

/*------------Libraries-------------*/

#include "Shared/SharedData.h"
#include "Storage/Storage.h"

#if !DISABLECOMM
    #include "GUIComHandlers/GUIComHandlers.h"
#else
    #define sendGUIMessage(payload) ;
#endif

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
    Serial.begin(9600);
    delay(200);
#if DEBUG
    debug(F("Setup - Booting...\n"));
    delay(50);
#endif
    Serial.print(F("PurifyMyWater System version: "));Serial.print((__FlashStringHelper*)VERSION);Serial.print('\n');
#if DEBUG
    debug(F("Build date: "));debug((F(__TIMESTAMP__)));debug(F("\n\n"));
    delay(50);
#endif

    debug(F("\nCAUTION: NEVER use debug features on a deployed system, there is risk of IRREVERSIBLE DAMAGE to the system\n\nUsing those debug features:\n"));

    debug(F("DEBUG\t\t\t- Used to display debug information messages through Serial port\n"));
#if USEVOLATILECONFIG
    debug(F("USEVOLATILECONFIG\t- Used to disable EEPROM writes due to saving configuration in the persistent storage\n"));
#endif
#if SETDEFAULTCONFIG
    debug(F("SETDEFAULTCONFIG\t- Used to set the config to the default config\n"));
#endif
#if DISABLEHARDWARECHECKS
    debug(F("DISABLEHARDWARECHECKS\t- Used to disable check routines to detect faulty hardware\n"));
#endif
#if DISABLEPURIFICATION
    debug(F("DISABLEPURIFICATION\t- Used to disable purification control systems\n"));
#endif
#if DISABLECOMM
    debug(F("DISABLECOMM\t\t- Used to disable GUI management & Communications\n"));
#endif
#if OVERRRIDEMAXVOLTAGE
    debug(F("OVERRRIDEMAXVOLTAGE\t- Used to check some functions without powering all the system\n"));
#endif
#if SCREENALWAYSON
    debug(F("SCREENALWAYSON\t\t- Used to bypass screen sensor (screen sensor always report active (1))\n"));
#endif
    debug('\n');
    delay(50);

#if SETDEFAULTCONFIG
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
    debugConfig();

    coreSetup();
#if !DISABLETEMPERATURE
    tempSetup();
#endif
#if !DISABLEPURIFICATION
    purificationSetup(); // it must be the last setup (it waits for voltage for a long time)
#endif
#if !DISABLECOMM
    GUISetup();
#endif

    debug(F("Setup - Starting Test phase\n")); //todo delete Test code after this line

    //while (true); // TODO delete or comment this
    sendMessageHandler(STARTCHARGINGVOLTAGE_ID, "13.5");

    debug(F("Setup - Test phase finished\n")); //todo delete Test code before this line

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
    #endif // DEBUG
    coreLoop();
    updateConfigLoop();
#if !DISABLETEMPERATURE
    tempLoop();
#endif
#if !DISABLEPURIFICATION
    if(configStorage.config.workingMode==Purification_On_Mode)
        purificationLoop();
#endif
#if !DISABLECOMM
    GUILoop();
#endif

    #if DEBUG
        perf = millis() - prevmillis;
    #endif
}
