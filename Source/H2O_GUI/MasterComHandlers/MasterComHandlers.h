//
// Created by Victor on 15/08/2022.
//

#ifndef H2O_GUI_MASTERCOMMHANDLERS_H
#define H2O_GUI_MASTERCOMMHANDLERS_H

#include "../Shared/SharedData.h"
#include "../Shared/Communications/ComManager.h"

#if !DISABLEUI
#include "../UI/UI.h"
#endif

enum GUIStatus{
    GUI_CONNECTING_ST = 0,
    GUI_CONNECTED_ST,
    GUI_SHUTTING_DOWN_ST,
    GUI_READY_TO_SHUTDOWN_ST,
    GUI_DISABLED_ST,
};

enum GUIStatus guiStatus = (enum GUIStatus)0;

#if DEBUG

#define changeGUIStatus(newStatus) debug(F("GUIStatus changed from '"));debug(GUIModeToString(guiStatus));debug(F("' to '"));debug(GUIModeToString(newStatus));debug(F("'\n")); guiStatus = newStatus

const char gmode0[] PROGMEM = "GUI_CONNECTING_ST";
const char gmode1[] PROGMEM = "GUI_CONNECTED_ST";
const char gmode2[] PROGMEM = "GUI_SHUTTING_DOWN_ST";
const char gmode3[] PROGMEM = "GUI_READY_TO_SHUTDOWN_ST";
const char gmode4[] PROGMEM = "GUI_DISABLED_ST";

const char *const debugGUIModeTable[] PROGMEM = {gmode0, gmode1, gmode2, gmode3, gmode4};

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

ComManager masterComManager(&Serial1,&sendMessageHandler,&requestMessageHandler,&requestAnswerMessageHandler);

void masterComLoop();

#include "MasterComHandlers.cpp"

#endif //H2O_GUI_MASTERCOMMHANDLERS_H
