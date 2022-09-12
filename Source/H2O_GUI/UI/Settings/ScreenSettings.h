//
// Created by Victor on 01/08/2022.
//

#ifndef H2O_GUI_SCREENSETTINGS_H
#define H2O_GUI_SCREENSETTINGS_H
#include <EEPROM.h>



enum Rotation {LANDSCAPE = 1, INVERTED_LANDSCAPE = 3};
enum Languages {ENGLISH = 0, SPANISH = 1, FRENCH = 2};

typedef struct ScreenConfiguration {
    enum Rotation ROTATION; // Current screen rotation
    enum Languages LANGUAGE; // current UI language
} ScreenConfig;

ScreenConfig screenConfig = {}; // ScreenConfiguration structure used to store current UI related config


// This function set default screenConfig parameters
void setDefaultScreenConfig();

// This function returns the crc32 value of the config structure stored in EEPROM
unsigned long screenConfigCRC32();

// This function read Config stored in EEPROM & validates it against a CRC32 checksum precalculated
// It returns true if the config is updated to RAM (checksum check was OK) and false otherwise
bool readScreenConfig();

// This function saves the current config to EEPROM with its respective CRC32 code to verify it later
void updateScreenConfig();

#include "ScreenSettings.cpp"

#endif //H2O_GUI_SCREENSETTINGS_H
