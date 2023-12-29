#ifndef SETTINGSSTORAGE_SETTINGS_H
#define SETTINGSSTORAGE_SETTINGS_H

#include <string>
#include <unordered_map>
#include "LogUtils.h"


class Settings
{
    public:
        // Enum that stores the possible errors returned by the API Settings
        typedef enum {NO_ERROR = 0, KEY_NOT_FOUND_ERROR, TYPE_MISMATCH_ERROR, 
                        KEY_EXISTS_ERROR, CORRUPTED_SETTINGS_FILE_ERROR} SettingError_t; 

        // Enum with the types of data that can be saved
        typedef enum {VOID = 0, SETTING_LIST, FLOAT, INT, STRING} SettingValueType_t;

        struct SettingValue_t;

        // Union with the types of data that can be saved
        typedef union {float FLOAT; int INT; std::string* STRING; 
                        std::unordered_map<std::string, SettingValue_t>* SETTING_MAP;} SettingValueData_t;

        // The value of each map element SettingsMap_t
        typedef struct SettingValue_t { SettingValueType_t settingValueType; SettingValueData_t settingValueData; } SettingValue_t;

        // The data type that stores a map of key string and struct value with the settings
        typedef std::unordered_map<std::string, SettingValue_t> SettingsMap_t;

        static void test(); //TODO: delete at the end of the module

        /**
         * This function initializes the settings map and reads the settings from the persistent storage.
         * Even if it returns an error, the settings map is initialized either by cleaning the settings map or
         * by limiting the use of the settings map to the volatile mode.
         * @return NO_ERROR if the initialization was successful;
         * CORRUPTED_SETTINGS_FILE_ERROR if the settings file is corrupted.
         */
        static SettingError_t initialize();

        /**
         * This function frees the memory used by the settings map and writes the settings to the persistent storage.
         * All the memory allocated by the settings map is freed, including the memory allocated for the strings or other values stored.
         */
        static void finalize();
        static SettingValue_t getSetting(const std::string& key);
        static SettingError_t putSetting(const std::string& key, int value);
        static SettingError_t putSetting(const std::string& key, float value);
        static SettingError_t putSetting(const std::string& key, const char* value);
        static SettingError_t addSetting(const std::string& key);
        static const char* getSettingsTree(const std::string& key);
        static bool writeSettingsToPersistentStorage();

    private:
        static void freeSettingsMap(Settings::SettingsMap_t* map);
        static SettingError_t initWithoutReadFromPersistentStorage();
        static SettingsMap_t* settingsMap;
        static bool initialized;

        /**
         * This attribute is used to disable the persistent settings storage in case of an irrecoverable error mounting or using the storage partition.
         */
        static bool disablePersistentStorage;
        static constexpr SettingValue_t VOID_VALUE = {.settingValueType = VOID, .settingValueData = {0}};
};

#endif // SETTINGSSTORAGE_SETTINGS_H
