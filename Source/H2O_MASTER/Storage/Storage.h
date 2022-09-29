//
// Created by Víctor on 20/06/2022.
//

#ifndef H2O_GUI_STORAGE_H
#define H2O_GUI_STORAGE_H

#include "../Shared/SharedData.h"
#include <EEPROM.h>

#define SAVECONFIGDELAY 300000 // 5 min

unsigned long saveConfigMillis = 0;
bool saveConfigTimerEnabled = false;

// This function returns the crc32 value of the config structure stored in EEPROM
unsigned long configCRC32();

// This function read Config stored in EEPROM & validates it against a CRC32 checksum precalculated
// It returns true if the config is updated to RAM (checksum check was OK) and false otherwise
bool readConfig();

// This function saves the current config to EEPROM with its respective CRC32 code to verify it later
void updateConfig();

// This function checks if enough time has passed since last time config was changed
void updateConfigLoop();

#include "Storage.cpp"


#endif //H2O_GUI_STORAGE_H
