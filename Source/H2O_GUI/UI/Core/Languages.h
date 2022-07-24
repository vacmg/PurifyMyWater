//
// Created by Victor on 24/07/2022.
//

#ifndef H2O_GUI_LANGUAGES_H
#define H2O_GUI_LANGUAGES_H

enum stringTypes{ON_STR = 0, OFF_STR};

const char EN_ON[] PROGMEM = "ON";
const char EN_OFF[] PROGMEM = "OFF";

const char ES_ON[] PROGMEM = "ENCENDER";
const char ES_OFF[] PROGMEM = "APAGAR";


const char *const langEN[] PROGMEM = {EN_ON, EN_OFF};
const char *const langES[] PROGMEM = {ES_ON, ES_OFF};

const char *const *const langs[] PROGMEM = {langEN, langES};

char languageBuff[50] = ""; // Max size of any language string
char* langString(enum stringTypes type);

#include "Languages.cpp"

#endif //H2O_GUI_LANGUAGES_H
