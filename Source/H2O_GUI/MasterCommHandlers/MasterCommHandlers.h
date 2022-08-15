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


ComManager master(&Serial1,&sendMessageHandler,&requestMessageHandler,&requestAnswerMessageHandler);

void GUILoop();

#include "MasterCommHandlers.cpp"

#endif //H2O_GUI_MASTERCOMMHANDLERS_H
