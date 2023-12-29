#include "PrivSettings.h"
#include "SettingsParser.h"
#include "StoragePartitionManager.h"

bool Settings::initialized = false;
bool Settings::disablePersistentStorage = false;
Settings::SettingsMap_t* Settings::settingsMap = nullptr;

Settings::SettingError_t Settings::initialize()
{
    settingsMap = SettingsParser::readFromFile(SETTINGS_FILE_NAME);
    if(settingsMap != nullptr)
    {
        const char* buff = getSettingsTree("");
        ESP_LOGI(SETTINGS_STORAGE_COMPONENT_TAG, "Settings map retrieved. Loaded config:\n----------\n%s\n----------",buff);
        free((void*) buff);
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
                        ESP_LOGE(SETTINGS_STORAGE_COMPONENT_TAG, AT "This code should not be reached");
                }
            }
            break;
        default:
            ESP_LOGE(SETTINGS_STORAGE_COMPONENT_TAG, AT "This code should not be reached");
    }
    return CORRUPTED_SETTINGS_FILE_ERROR;
}

Settings::SettingError_t Settings::initWithoutReadFromPersistentStorage()
{
    settingsMap = new SettingsMap_t();
    initialized = true;
    return CORRUPTED_SETTINGS_FILE_ERROR;
}

void Settings::finalize()
{

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
    ESP_LOGE(SETTINGS_STORAGE_COMPONENT_TAG,"Test begin");

    // Place test code here

    ESP_LOGE(SETTINGS_STORAGE_COMPONENT_TAG,"Test end");
}
