//
// Created by Victor on 15/08/2022.
//

#ifndef H2O_MASTER_GUICOMMHANDLERS_H
#define H2O_MASTER_GUICOMMHANDLERS_H

#include "../Shared/SharedData.h"
#include "../Shared/Communications/ComManager.h"
#include "../SystemControl/Core/Core.h"

#define GUICOOLDOWNTIME SCREENSHUTDOWNDELAY+5000 // GUI minimum delay between a shutdown and the next start

enum GUIStatus{
    GUI_ERROR_ST = 0,
    GUI_DISABLED_ST,
    GUI_OFF_ST,
    GUI_COOLDOWN_ST,
    GUI_CONNECTED_ST,
    GUI_SHUTTING_DOWN_ST,
    GUI_RECONNECTING_ST,
    GUI_BUSY_ST
};

enum GUIStatus guiStatus = GUI_OFF_ST;
unsigned long guiMillis = 0;
bool guiSw = false;

#if DEBUG

#define changeGUIStatus(newStatus) debug(F("GUIStatus changed from '"));debug(GUIModeToString(guiStatus));debug(F("' to '"));debug(GUIModeToString(newStatus));debug(F("'\n")); guiStatus = newStatus

const char mode0[] PROGMEM = "GUI_ERROR_ST";
const char mode1[] PROGMEM = "GUI_DISABLED_ST";
const char mode2[] PROGMEM = "GUI_OFF_ST";
const char mode3[] PROGMEM = "GUI_COOLDOWN_ST";
const char mode4[] PROGMEM = "GUI_CONNECTED_ST";
const char mode5[] PROGMEM = "GUI_SHUTTING_DOWN_ST";
const char mode6[] PROGMEM = "GUI_RECONNECTING_ST";
const char mode7[] PROGMEM = "GUI_BUSY_ST";

const char *const debugGUIModeTable[] PROGMEM = {mode0, mode1, mode2, mode3, mode4, mode5, mode6, mode7};

char* GUIModeToString(enum GUIStatus status)
{
    strcpy_P(debugBuff, (char *)pgm_read_word(&(debugGUIModeTable[status])));
    return debugBuff;
}

#else

#define changeGUIStatus(newStatus) guiStatus = newStatus

#endif

#include "Handlers/sendMessageHandler.h"
#include "Handlers/requestMessageHandler.h"
#include "Handlers/requestAnswerMessageHandler.h"

ComManager guiComManager(&Serial1,&sendMessageHandler,&requestMessageHandler,&requestAnswerMessageHandler);

void GUILoop();

#include "GUIComHandlers.cpp"

#endif //H2O_MASTER_GUICOMMHANDLERS_H
