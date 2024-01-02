#include "PrivSettings.h"
#include "SettingsParser.h"
#include "StoragePartitionManager.h"

#if CONFIG_SETTINGS_DISABLE_WRITE_TO_FLASH
#define DISABLE_PERSISTENT_STORAGE_DEFAULT true
#else
#define DISABLE_PERSISTENT_STORAGE_DEFAULT false
#endif

bool Settings::initialized = false;
bool Settings::disablePersistentStorage = DISABLE_PERSISTENT_STORAGE_DEFAULT;
Settings::SettingsMap_t* Settings::settingsMap = nullptr;


Settings::SettingError_t Settings::initialize()
{
    if(!initialized)
    {
        ESP_LOGI(SETTINGS_STORAGE_COMPONENT_TAG, "Initializing settings module...");
        settingsMap = SettingsParser::readFromFile(SETTINGS_FILE_NAME);
        if(settingsMap != nullptr)
        {
            const char* buff = getSettingsTree("");
            if(buff == nullptr)
            {
                ESP_LOGW(SETTINGS_STORAGE_COMPONENT_TAG, "There is not enough memory to print the settings map");
            }
            else
            {
                ESP_LOGI(SETTINGS_STORAGE_COMPONENT_TAG, "Settings map retrieved. Loaded config:\n----------\n%s\n----------",buff);
                free((void*) buff);
            }

            initialized = true;
            return NO_ERROR;
        }
        ESP_LOGW(SETTINGS_STORAGE_COMPONENT_TAG, "Unable to parse settings from file " SETTINGS_FILE_NAME ". Reason: %s", SettingsParser::getErrorMessage());

        esp_err_t ret;
        switch (SettingsParser::getErrorCode())
        {
            case SettingsParser::INVALID_MAP_ERROR:
            case SettingsParser::INVALID_PATH_ERROR:
                ESP_LOGI(SETTINGS_STORAGE_COMPONENT_TAG, "Initializing new settings map...");
                return initWithoutReadFromPersistentStorage();

            case SettingsParser::FILESYSTEM_ERROR:
                StoragePartitionManager::unmount();
                ret = StoragePartitionManager::mount();
                if(ret == ESP_ERR_NOT_FOUND || ret == ESP_ERR_INVALID_STATE || ret == ESP_ERR_NO_MEM)
                {
                    ESP_LOGE(SETTINGS_STORAGE_COMPONENT_TAG, AT "Irrecoverable error: %s. " CONFIG_STORAGE_PARTITION_LABEL
                            " partition is unusable: Falling back to volatile settings mode", esp_err_to_name(ret));
                    disablePersistentStorage = true;
                    return initWithoutReadFromPersistentStorage();
                }
                else if (ret == ESP_FAIL)
                {
                    ESP_LOGW(SETTINGS_STORAGE_COMPONENT_TAG, "Unable to mount filesystem. Formatting partition...");
                    if(StoragePartitionManager::format() == ESP_OK)
                    {
                        ESP_LOGI(SETTINGS_STORAGE_COMPONENT_TAG, "Formatting successful. Initializing new settings map...");
                        return initWithoutReadFromPersistentStorage();
                    }
                    else
                    {
                        ESP_LOGE(SETTINGS_STORAGE_COMPONENT_TAG, AT "Irrecoverable error: %s. " CONFIG_STORAGE_PARTITION_LABEL
                                " partition is unusable: Falling back to volatile settings mode", esp_err_to_name(ret));
                        disablePersistentStorage = true;
                        return initWithoutReadFromPersistentStorage();
                    }
                }
                else // ESP_OK
                {
                    ESP_LOGI(SETTINGS_STORAGE_COMPONENT_TAG, "Filesystem mounted. Initializing settings map...");
                    if(settingsMap != nullptr)
                    {
                        const char* buff = getSettingsTree("");
                        ESP_LOGI(SETTINGS_STORAGE_COMPONENT_TAG, "Settings map retrieved. Loaded config:\n----------\n%s\n----------",buff);
                        free((void*) buff);
                        initialized = true;
                        return NO_ERROR;
                    }
                    ESP_LOGW(SETTINGS_STORAGE_COMPONENT_TAG, "Unable to parse settings from file " SETTINGS_FILE_NAME ". Reason: %s", SettingsParser::getErrorMessage());
                    switch (SettingsParser::getErrorCode())
                    {
                        case SettingsParser::INVALID_MAP_ERROR:
                        case SettingsParser::INVALID_PATH_ERROR:
                            ESP_LOGI(SETTINGS_STORAGE_COMPONENT_TAG, "Initializing new settings map...");
                            return initWithoutReadFromPersistentStorage();
                        case SettingsParser::FILESYSTEM_ERROR:
                            ESP_LOGE(SETTINGS_STORAGE_COMPONENT_TAG, AT "Irrecoverable error: %s. " CONFIG_STORAGE_PARTITION_LABEL
                                    " partition is unusable: Falling back to volatile settings mode", esp_err_to_name(ret));
                            disablePersistentStorage = true;
                            return initWithoutReadFromPersistentStorage();
                        case SettingsParser::NO_ERROR:
                            assert(false); // This code should not be reached if SettingsParser::readFromFile() works fine
                    }
                }
                break;
            case SettingsParser::NO_ERROR:
                assert(false); // This code should not be reached if SettingsParser::readFromFile() works fine
        }
        return CORRUPTED_SETTINGS_FILE_ERROR;
    }
    else
    {
        ESP_LOGE(SETTINGS_STORAGE_COMPONENT_TAG, "Settings module is already initialized");
        return NO_ERROR;
    }
}


Settings::SettingError_t Settings::initWithoutReadFromPersistentStorage()
{
    settingsMap = new SettingsMap_t();
    initialized = true;
    return CORRUPTED_SETTINGS_FILE_ERROR;
}


void Settings::finalize()
{
    if(initialized)
    {
        ESP_LOGI(SETTINGS_STORAGE_COMPONENT_TAG, "Finalizing settings module...");
        writeSettingsToPersistentStorage();
        freeSettingsMap(settingsMap, "");
        initialized = false;
        disablePersistentStorage = DISABLE_PERSISTENT_STORAGE_DEFAULT;
    }
    else
    {
        ESP_LOGE(SETTINGS_STORAGE_COMPONENT_TAG, "Settings module is not initialized");
    }
}


void Settings::freeSettingsMap(Settings::SettingsMap_t* map, const char* mapName)
{
    ESP_LOGI(SETTINGS_STORAGE_COMPONENT_TAG, "Freeing settings map '%s'", mapName);
    for(const auto& entry: *map)
    {
        switch (entry.second.settingValueType)
        {
            case SETTING_LIST:
                ESP_LOGD(SETTINGS_STORAGE_COMPONENT_TAG, "Freeing setting '%s' (MAP)", entry.first.c_str());
                freeSettingsMap(entry.second.settingValueData.SETTING_MAP, fmt::format("{}/{}", mapName, entry.first).c_str());
                break;
            case STRING:
                ESP_LOGD(SETTINGS_STORAGE_COMPONENT_TAG, "Freeing setting '%s' (STRING) -> %s", entry.first.c_str(), entry.second.settingValueData.STRING->c_str());
                delete entry.second.settingValueData.STRING;
                break;
            case FLOAT:
                ESP_LOGD(SETTINGS_STORAGE_COMPONENT_TAG, "Freeing setting '%s' (FLOAT) -> %f", entry.first.c_str(), entry.second.settingValueData.FLOAT);
                break;
            case INT:
                ESP_LOGD(SETTINGS_STORAGE_COMPONENT_TAG, "Freeing setting '%s' (INT) -> %d", entry.first.c_str(), entry.second.settingValueData.INT);
                break;
            case VOID:
                ESP_LOGD(SETTINGS_STORAGE_COMPONENT_TAG, "Freeing setting '%s' (VOID)", entry.first.c_str());
                break;
        }
    }
    delete map;
    ESP_LOGI(SETTINGS_STORAGE_COMPONENT_TAG, "Settings map '%s' freed", mapName);
}


Settings::SettingValue_t Settings::getSetting(const std::string& key)
{
    return VOID_VALUE;
}


Settings::SettingError_t Settings::putSetting(const std::string& key, int value)
{
    if(disablePersistentStorage)
    {
        // TODO tener en cuenta que si ese atributo es true, no se puede guardar en la particion de almacenamiento
    }
    return NO_ERROR;
}


Settings::SettingError_t Settings::putSetting(const std::string& key, float value)
{
    if(disablePersistentStorage)
    {
        // TODO tener en cuenta que si ese atributo es true, no se puede guardar en la particion de almacenamiento
    }
    return NO_ERROR;
}


Settings::SettingError_t Settings::putSetting(const std::string& key, const char* value)
{
    if(disablePersistentStorage)
    {
        // TODO tener en cuenta que si ese atributo es true, no se puede guardar en la particion de almacenamiento
    }
    return NO_ERROR;
}


Settings::SettingError_t Settings::addSetting(const std::string& key)
{
    if(disablePersistentStorage)
    {
        // TODO tener en cuenta que si ese atributo es true, no se puede guardar en la particion de almacenamiento
    }
    return NO_ERROR;
}


const char* Settings::getSettingsTree(const std::string& key)
{
    return nullptr;
}


bool Settings::writeSettingsToPersistentStorage()
{
    if(disablePersistentStorage)
    {
        // TODO tener en cuenta que si ese atributo es true, no se puede guardar en la particion de almacenamiento
    }
    return false;
}


void Settings::test()
{
    ESP_LOGW(SETTINGS_STORAGE_COMPONENT_TAG,"Test begin");

    // Place test code here


//    initialize();
//
//    (*settingsMap)["key1"] = {.settingValueType = INT, .settingValueData = {.INT = 1}};
//    (*settingsMap)["key2"] = {.settingValueType = FLOAT, .settingValueData = {.FLOAT = 2.0}};
//    (*settingsMap)["key3"] = {.settingValueType = STRING, .settingValueData = {.STRING = new std::string("3")}};
//    (*settingsMap)["key4"] = {.settingValueType = SETTING_LIST, .settingValueData = {.SETTING_MAP = new SettingsMap_t()}};
//    (*settingsMap)["key5"] = VOID_VALUE;
//    (*(*settingsMap)["key4"].settingValueData.SETTING_MAP)["key4.1"] = {.settingValueType = INT, .settingValueData = {.INT = 4}};
//    (*(*settingsMap)["key4"].settingValueData.SETTING_MAP)["key4.2"] = {.settingValueType = FLOAT, .settingValueData = {.FLOAT = 4.2}};
//    (*(*settingsMap)["key4"].settingValueData.SETTING_MAP)["key4.3"] = {.settingValueType = STRING, .settingValueData = {.STRING = new std::string("4.3")}};
//    (*(*settingsMap)["key4"].settingValueData.SETTING_MAP)["key4.4"] = {.settingValueType = SETTING_LIST, .settingValueData = {.SETTING_MAP = new SettingsMap_t()}};
//    (*(*(*settingsMap)["key4"].settingValueData.SETTING_MAP)["key4.4"].settingValueData.SETTING_MAP)["key4.4.1"] = {.settingValueType = INT, .settingValueData = {.INT = 4}};
//    (*(*(*settingsMap)["key4"].settingValueData.SETTING_MAP)["key4.4"].settingValueData.SETTING_MAP)["key4.4.2"] = {.settingValueType = FLOAT, .settingValueData = {.FLOAT = 4.42}};
//    (*(*(*settingsMap)["key4"].settingValueData.SETTING_MAP)["key4.4"].settingValueData.SETTING_MAP)["key4.4.3"] = {.settingValueType = STRING, .settingValueData = {.STRING = new std::string("4.4.3")}};
//
//    finalize();

    ESP_LOGW(SETTINGS_STORAGE_COMPONENT_TAG,"Test end");
}
