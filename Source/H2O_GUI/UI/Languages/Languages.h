//
// Created by Victor on 24/07/2022.
//

#ifndef H2O_GUI_LANGUAGES_H
#define H2O_GUI_LANGUAGES_H

#include "../UI.h"

enum StringIDs{Lang_STR = 0, ON_STR, OFF_STR};

#include "EN_Lang.h"
#include "ES_Lang.h"

const char* const* const langs[] PROGMEM = {langEN, langES}; // Follow the same order as enum Languages (UI.h)

char languageBuff[50] = ""; // Max size of any language string

// Returns the string identified by the id in the language selected by enum Languages LANGUAGE variable
char* getString(enum StringIDs stringId);

#include "Languages.cpp"

#endif //H2O_GUI_LANGUAGES_H
