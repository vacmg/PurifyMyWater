#include "SettingsParser.h"

SettingsParser::ParserError_t SettingsParser::Errno = SettingsParser::NO_ERROR;

SettingsParser::ParserError_t SettingsParser::getErrorCode()
{
    return FILESYSTEM_ERROR;
}

const char* SettingsParser::getErrorMessage()
{
    return "";
}

bool SettingsParser::writeToFile(Settings::SettingsMap_t* map, const char* path)
{
    return false;
}

Settings::SettingsMap_t* SettingsParser::readFromFile(const char* path)
{
    return nullptr;
}

int SettingsParser::checksum(const char* data, size_t size)
{
    return 0;
}
