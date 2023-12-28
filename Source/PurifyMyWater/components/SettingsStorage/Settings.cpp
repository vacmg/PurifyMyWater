#include "PrivSettings.h"

bool Settings::initialized = false;

Settings::SettingError_t Settings::initialize()
{
    return NO_ERROR;
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
    return NO_ERROR;
}

Settings::SettingError_t Settings::putSetting(const std::string& key, float value)
{
    return NO_ERROR;
}

Settings::SettingError_t Settings::putSetting(const std::string& key, const char* value)
{
    return NO_ERROR;
}

Settings::SettingError_t Settings::addSetting(const std::string& key)
{
    return NO_ERROR;
}

const char* Settings::getSettingsTree(const std::string& key)
{
    return nullptr;
}

bool Settings::writeSettingsToPersistentStorage()
{
    return false;
}

void Settings::test()
{
    ESP_LOGI(SETTINGS_STORAGE_COMPONENT_TAG,"hello world!");
}
