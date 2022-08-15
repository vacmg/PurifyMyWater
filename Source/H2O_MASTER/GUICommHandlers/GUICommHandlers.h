//
// Created by Victor on 15/08/2022.
//

#ifndef H2O_MASTER_GUI_H
#define H2O_MASTER_GUI_H

#include "../Shared/SharedData.h"
#include "../Communications/ComManager.h"
#include "../SystemControl/Core/Core.h"

#include "Handlers/sendMessageHandler.h"
#include "Handlers/requestMessageHandler.h"
#include "Handlers/requestAnswerMessageHandler.h"

enum GUIStatus{
    GUI_ERROR_ST,
    GUI_DISABLED_ST,
    GUI_OFF_ST,
    GUI_CONNECTING_ST,
    GUI_CONNECTED_ST,
    GUI_SHUTTING_DOWN_ST
};

enum GUIStatus guiStatus = GUI_OFF_ST;

ComManager gui(&Serial1,&sendMessageHandler,&requestMessageHandler,&requestAnswerMessageHandler);

void GUILoop();

void shutdownScreen();

#include "GUICommHandlers.cpp"

#endif //H2O_MASTER_GUI_H
