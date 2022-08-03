//
// Created by Victor on 24/07/2022.
//

#include "Languages.h"

// Returns the string identified by the id in the language selected by the specified language
char* getString(enum StringIDs stringId, Languages language)
{
    return strcpy_P(languageBuff, (const char*) pgm_read_word( &((const uint16_t*) pgm_read_word(&langs[language])) [stringId] )); // Internal pgm_read_word gets the array (16-bit address) which holds the strings in the specified language & external pgm_read_word gets the desired string from the current language array
}

// Returns the string identified by the id in the language selected by enum Languages LANGUAGE variable
char* getString(enum StringIDs stringId)
{
    return getString(stringId, screenConfig.LANGUAGE); // Internal pgm_read_word gets the array (16 but address) which holds the strings in the specified language & external pgm_read_word gets the desired string from the current language array
}

// Returns the path to a localized file identified by the id in the language selected by the specified language
char* getPath(enum PathIDs pathID, Languages language)
{
    return strcpy_P(languageBuff, (const char*) pgm_read_word( &((const uint16_t*) pgm_read_word(&paths[language])) [pathID] )); // Internal pgm_read_word gets the array (16-bit address) which holds the strings in the specified language & external pgm_read_word gets the desired string from the current language array
}

// Returns the path to a localized file identified by the id in the language selected by enum Languages LANGUAGE variable
char* getPath(enum PathIDs pathID)
{
    return getPath(pathID, screenConfig.LANGUAGE); // Internal pgm_read_word gets the array (16 but address) which holds the strings in the specified language & external pgm_read_word gets the desired string from the current language array
}
