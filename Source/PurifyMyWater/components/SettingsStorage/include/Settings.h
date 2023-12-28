#ifndef SETTINGSSTORAGE_SETTINGS_H
#define SETTINGSSTORAGE_SETTINGS_H

#include <string>
#include <unordered_map>
#include <esp_log.h>


class Settings
{
    public:
        // Enum that stores the possible errors returned by the API Settings
        typedef enum {NO_ERROR = 0, KEY_NOT_FOUND_ERROR, TYPE_MISMATCH_ERROR, 
                        KEY_EXISTS_ERROR, CORRUPTED_SETTINGS_FILE_ERROR} SettingError_t; 

        // Enum with the types of data that can be saved
        typedef enum {VOID = 0, SETTING_LIST, FLOAT, INT, STRING} SettingValueType_t;

        // Union with the types of data that can be saved
        typedef union {float FLOAT; int INT; std::string* STRING; 
                        std::unordered_map<std::string, struct SettingValue_t>* SETTING_MAP;} SettingValueData_t;

        // The value of each map element SettingsMap_t
        typedef struct SettingValue_t { SettingValueType_t settingValueType; SettingValueData_t settingValueData; } SettingValue_t;

        // The data type that stores a map of key string and struct value with the settings
        typedef std::unordered_map<std::string, SettingValue_t> SettingsMap_t;

        static void test(); //TODO: delete at the end of the module
        static SettingError_t initialize();
        static void finalize();
        static SettingValue_t getSetting(const std::string& key);
        static SettingError_t putSetting(const std::string& key, int value);
        static SettingError_t putSetting(const std::string& key, float value);
        static SettingError_t putSetting(const std::string& key, const char* value);
        static SettingError_t addSetting(const std::string& key);
        static const char* getSettingsTree(const std::string& key);
        static bool writeSettingsToPersistentStorage();

    private:
        static SettingsMap_t* settingsMap;
        static bool initialized;
        static constexpr SettingValue_t VOID_VALUE = {.settingValueType = VOID, .settingValueData = {0}};
};

#endif // SETTINGSSTORAGE_SETTINGS_H
