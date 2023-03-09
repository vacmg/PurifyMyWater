//
// Created by Victor on 15/08/2022.
//

#ifndef H2O_GUI_REQUESTANSWERMESSAGEHANDLER_H
#define H2O_GUI_REQUESTANSWERMESSAGEHANDLER_H

#include "../MasterComHandlers.h"

void requestAnswerMessageHandler(enum VariableIDs variableID, char* value, enum FunctionIDs functionID, byte step);

#include "requestAnswerMessageHandler.cpp"

#endif //H2O_GUI_REQUESTANSWERMESSAGEHANDLER_H
