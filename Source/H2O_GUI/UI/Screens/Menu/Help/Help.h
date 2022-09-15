//
// Created by jst83 on 08/09/2022.
//

#ifndef H2O_GUI_HELP_H
#define H2O_GUI_HELP_H

#include "../Menu.h"

void drawHelpMenu();

void drawHelpTopic();

void clickHelp();

void clickHelpTopic();

char helpPath[50]="";
char topicNumber[10]="";
#include "Help.cpp"

#endif //H2O_GUI_HELP_H
