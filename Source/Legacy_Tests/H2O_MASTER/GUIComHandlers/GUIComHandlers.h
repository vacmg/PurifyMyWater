//
// Created by Victor on 15/08/2022.
//

#ifndef H2O_MASTER_GUICOMMHANDLERS_H
#define H2O_MASTER_GUICOMMHANDLERS_H

#include "../Shared/SharedData.h"
#include "../Shared/Communications/ComManager.h"

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

void GUISetup();
void GUILoop();

#if DEBUG

#define changeGUIStatus(newStatus) debug(F("GUIStatus changed from '"));debug(GUIModeToString(guiStatus));debug(F("' to '"));debug(GUIModeToString(newStatus));debug(F("'\n")); guiStatus = newStatus

const char gmode0[] PROGMEM = "GUI_ERROR_ST";
const char gmode1[] PROGMEM = "GUI_DISABLED_ST";
const char gmode2[] PROGMEM = "GUI_OFF_ST";
const char gmode3[] PROGMEM = "GUI_COOLDOWN_ST";
const char gmode4[] PROGMEM = "GUI_CONNECTED_ST";
const char gmode5[] PROGMEM = "GUI_SHUTTING_DOWN_ST";
const char gmode6[] PROGMEM = "GUI_RECONNECTING_ST";
const char gmode7[] PROGMEM = "GUI_BUSY_ST";

const char *const debugGUIModeTable[] PROGMEM = {gmode0, gmode1, gmode2, gmode3, gmode4, gmode5, gmode6, gmode7};

char* GUIModeToString(enum GUIStatus status)
{
    strcpy_P(debugBuff, (char *)pgm_read_word(&(debugGUIModeTable[status])));
    return debugBuff;
}

#else

#define changeGUIStatus(newStatus) guiStatus = newStatus

#endif

ComManager guiComManager(&Serial1, nullptr, nullptr, nullptr);

// Use sendGUIMessage to send a message from outside GUILoop()
#define sendGUIMessage(payload) (guiStatus == GUI_CONNECTED_ST) && guiComManager.sendMessage(payload)

#include "../SystemControl/Core/Core.h"
#include "../Storage/Storage.h"

#include "Handlers/sendMessageHandler.h"
#include "Handlers/requestMessageHandler.h"
#include "Handlers/requestAnswerMessageHandler.h"

#define GUICOOLDOWNTIME (SCREENSHUTDOWNDELAY+5000) // GUI minimum delay between a shutdown and the next start

#include "GUIComHandlers.cpp"

#endif //H2O_MASTER_GUICOMMHANDLERS_H
