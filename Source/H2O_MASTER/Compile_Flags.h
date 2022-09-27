//
// Created by Victor on 11/09/2022.
//

#ifndef H2O_COMPILE_FLAGS_H
#define H2O_COMPILE_FLAGS_H

#define DEBUG true // Used to display debug information messages through Serial port

#define USEVOLATILECONFIG true // Used to disable EEPROM writes due to saving configuration in the persistent storage
#define SETDEFAULTCONFIG false // Used to set the config to the default config

#define DISABLEHARDWARECHECKS true // Used to disable check routines to detect faulty hardware
#define DISABLEPURIFICATION !true // Used to disable purification control systems
#define DISABLETEMPERATURE true // Used to disable temperature control systems
#define DISABLECOMM true // Used to disable GUI management & Communications

#define OVERRRIDEMAXVOLTAGE true // Used to check some functions without powering all the system
#define SCREENALWAYSON true // Used to bypass screen sensor (screen sensor always report active (1))

#if !DEBUG && (USEVOLATILECONFIG || SETDEFAULTCONFIG || DISABLEHARDWARECHECKS || DISABLEPURIFICATION || DISABLECOMM || OVERRRIDEMAXVOLTAGE || SCREENALWAYSON)
#undef DEBUG
#define DEBUG true
#endif

#endif //H2O_COMPILE_FLAGS_H
