#ifndef SETTINGSSTORAGE_SETTINGSPARSER_H
#define SETTINGSSTORAGE_SETTINGSPARSER_H

#include "PrivSettings.h"

class SettingsParser
{
    public:
        // Enum that stores the possible errors returned by the API Settings
        typedef enum{NO_ERROR = 0, INVALID_MAP_ERROR, INVALID_PATH_ERROR,
                     FILESYSTEM_ERROR} ParserError_t;

        // returns the errno attribute which corresponds to the exit status of the last 
        // call to any of the class methods
        static ParserError_t getErrorCode();

        // returns the current errno name as a constant string
        static const char* getErrorMessage();

        // This function parses the map to a JSON string using cJSON.h library, then calculate 
        // the checksum value of it and write the json string to {path}.json and the checksum to {path}.chk
        static bool writeToFile(Settings::SettingsMap_t* map, const char* path);

        // This function reads the files {path}.json and {path}.chk to retrieve the json settings.
        static Settings::SettingsMap_t* readFromFile(const char* path);

    private:
        static ParserError_t Errno;

        // performs a checksum calculation using CRC32 algorithm and returns the hashed value
        static int checksum(const char* data, size_t size);
        
};

#endif // SETTINGSSTORAGE_SETTINGSPARSER_H