//
// Created by Victor on 24/07/2022.
//

#include "Languages.h"

// Returns the string identified by the id in the language selected by enum Languages LANGUAGE variable
char* getString(enum StringIDs stringId)
{
    strcpy_P(languageBuff, (const char*) pgm_read_word( &((const uint16_t*) pgm_read_word(&langs[LANGUAGE])) [stringId] )); // Internal pgm_read_word gets the array (16 but address) which holds the strings in the specified language & external pgm_read_word gets the desired string from the current language array
    return languageBuff;
}

