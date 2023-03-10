//
// Created by Victor on 15/08/2022.
//

#ifndef H2O_GUI_SENDMESSAGEHANDLER_H
#define H2O_GUI_SENDMESSAGEHANDLER_H

#include "../MasterComHandlers.h"

#if DISABLEUI
#define updateStatusForeground(status) ;
#else
#define updateStatusForeground(status) updateStatusForeground = status;
#endif

void sendMessageHandler(enum VariableIDs variableID, char* value);

#include "sendMessageHandler.cpp"

#endif //H2O_GUI_SENDMESSAGEHANDLER_H
