//
// Created by Victor on 15/08/2022.
//

#ifndef H2O_GUI_MASTERCOMMHANDLERS_H
#define H2O_GUI_MASTERCOMMHANDLERS_H

#include "../Shared/SharedData.h"
#include "../Shared/Communications/ComManager.h"

#include "Handlers/sendMessageHandler.h"
#include "Handlers/requestMessageHandler.h"
#include "Handlers/requestAnswerMessageHandler.h"

enum GUIStatus{
    GUI_CONNECTING_ST = 0,
    GUI_CONNECTED_ST,
    GUI_SHUTTING_DOWN_ST,
    GUI_READY_TO_SHUTDOWN_ST,
    GUI_ERROR_ST,
    GUI_DISABLED_ST,
};

enum GUIStatus guiStatus = (enum GUIStatus)0;

#if DEBUG

#define changeGUIStatus(newStatus) debug(F("GUIStatus changed from '"));debug(GUIModeToString(guiStatus));debug(F("' to '"));debug(GUIModeToString(newStatus));debug(F("'\n")); guiStatus = newStatus

const char mode0[] PROGMEM = "XXX_ST";
const char mode1[] PROGMEM = "XXX_ST";
const char mode2[] PROGMEM = "XXX_ST";
const char mode3[] PROGMEM = "XXX_ST";
const char mode4[] PROGMEM = "XXX_ST";
const char mode5[] PROGMEM = "XXX_ST";

const char *const debugGUIModeTable[] PROGMEM = {mode0, mode1, mode2, mode3, mode4, mode5};

char* GUIModeToString(enum GUIStatus status)
{
    strcpy_P(debugBuff, (char *)pgm_read_word(&(debugGUIModeTable[status])));
    return debugBuff;
}

#else

#define changeGUIStatus(newStatus) guiStatus = newStatus

#endif

ComManager masterComManager(&Serial1,&sendMessageHandler,&requestMessageHandler,&requestAnswerMessageHandler);

void MasterCommLoop(); // TODO implement this

#include "MasterCommHandlers.cpp"

#endif //H2O_GUI_MASTERCOMMHANDLERS_H
