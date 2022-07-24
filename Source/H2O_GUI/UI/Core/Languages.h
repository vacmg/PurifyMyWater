//
// Created by Victor on 24/07/2022.
//

#ifndef H2O_GUI_LANGUAGES_H
#define H2O_GUI_LANGUAGES_H

const enum stringTypes{STRON = 0, STROFF};

const char EN_ON[] PROGMEM = "ON";
const char EN_OFF[] PROGMEM = "OFF";

const char ES_ON[] PROGMEM = "ENCENDER";
const char ES_OFF[] PROGMEM = "APAGAR";




const char *const langEN[] PROGMEM = {EN_ON, EN_OFF};
const char *const langES[] PROGMEM = {ES_ON, ES_OFF};

const char *const *langs[] PROGMEM = {langEN, langES};

char languageBuff[50] = ""; // Max size of any language string
char* langString(const enum stringTypes type)
{
    strcpy_P(languageBuff, (char *)pgm_read_word(&(langs[LANGUAGE][type]))); // TODO mirar si esto funciona (no creo xd)
    return languageBuff;
}

#endif //H2O_GUI_LANGUAGES_H
