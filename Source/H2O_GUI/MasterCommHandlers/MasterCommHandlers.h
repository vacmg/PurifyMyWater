//
// Created by Victor on 15/08/2022.
//

#ifndef H2O_GUI_MASTERCOMMHANDLERS_H
#define H2O_GUI_MASTERCOMMHANDLERS_H

#include "../Shared/SharedData.h"
#include "../Communications/ComManager.h"

#include "Handlers/sendMessageHandler.h"
#include "Handlers/requestMessageHandler.h"
#include "Handlers/requestAnswerMessageHandler.h"

enum GUIStatus{
    GUI_CONNECTING_ST,
    GUI_CONNECTED_ST,
    GUI_SHUTTING_DOWN_ST,
    GUI_READY_TO_SHUTDOWN_ST,
    GUI_ERROR_ST,
    GUI_DISABLED_ST,
};

ComManager master(&Serial1,&sendMessageHandler,&requestMessageHandler,&requestAnswerMessageHandler);

void MasterCommLoop(); // TODO implement this

#include "MasterCommHandlers.cpp"

#endif //H2O_GUI_MASTERCOMMHANDLERS_H
