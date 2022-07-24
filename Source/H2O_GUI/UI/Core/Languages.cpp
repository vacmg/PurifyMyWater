//
// Created by Victor on 24/07/2022.
//

#include "Languages.h"

char* langString(const enum stringTypes type)
{
    strcpy_P(languageBuff, (char *)pgm_read_word(&(langs[LANGUAGE][type]))); // TODO mirar si esto funciona (no creo xd)
    return languageBuff;
}
