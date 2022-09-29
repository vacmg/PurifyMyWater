//
// Created by Victor on 01/08/2022.
//

#include "ScreenSettings.h"

// This function set default screenConfig parameters
void setDefaultScreenConfig()
{
    screenConfig.ROTATION = INVERTED_LANDSCAPE; // INVERTED_LANDSCAPE // LANDSCAPE
    screenConfig.LANGUAGE = ENGLISH;
}

// This function returns the crc32 value of the config structure stored in EEPROM
unsigned long screenConfigCRC32()
{
    const unsigned long crc_table[16] = {
            0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
            0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
            0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
            0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
    };
    unsigned long crc = ~0L;

    for (unsigned int index = 4 ; index < sizeof (screenConfig)+4; index++) // screenConfig starts at position 4
    {

        crc = crc_table[(crc ^ EEPROM[index]) & 0x0f] ^ (crc >> 4);

        crc = crc_table[(crc ^ (EEPROM[index] >> 4)) & 0x0f] ^ (crc >> 4);

        crc = ~crc;

    }
    return crc;
}

// This function read Config stored in EEPROM & validates it against a CRC32 checksum precalculated
// It returns true if the config is updated to RAM (checksum check was OK) and false otherwise
bool readScreenConfig()
{
    unsigned long crc;
    EEPROM.get(0,crc);
    if(crc == screenConfigCRC32())
    {
        EEPROM.get(4, screenConfig); // screenConfig is at position 4
        return true;
    }
    return false;
}

// This function saves the current config to EEPROM with its respective CRC32 code to verify it later
void updateScreenConfig()
{
#if !USEVOLATILECONFIG
    EEPROM.put(4, screenConfig); // save screenConfig at position 4
    unsigned long crc = screenConfigCRC32();
    debug(F("Configuration saved to EEPROM\n"));
    debugConfig();
    EEPROM.put(0, crc);
#endif
}

// This function checks if enough time has passed since last time config was changed
void updateConfigLoop()
{
    if(saveScreenConfigTimerEnabled && saveScreenConfigMillis+SAVESCREENCONFIGDELAY<millis())
    {
        saveScreenConfigTimerEnabled = false;
        updateScreenConfig();
    }
}