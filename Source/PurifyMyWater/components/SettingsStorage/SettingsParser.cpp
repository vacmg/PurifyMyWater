#include "SettingsParser.h"

SettingsParser::ParserError_t SettingsParser::Errno = SettingsParser::NO_ERROR;

SettingsParser::ParserError_t SettingsParser::getErrorCode()
{
    return NO_ERROR;
}

const char* SettingsParser::getErrorMessage()
{
    return nullptr;
}

bool SettingsParser::writeToFile(Settings::SettingsMap_t* map, char* path)
{
    return false;
}

Settings::SettingsMap_t* SettingsParser::readFromFile(char* path)
{
    return nullptr;
}

int SettingsParser::checksum(char* data, size_t size)
{
    return 0;
}
