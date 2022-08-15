//
// Created by Victor on 15/08/2022.
//

#ifndef H2O_MASTER_REQUESTANSWERMESSAGEHANDLER_H
#define H2O_MASTER_REQUESTANSWERMESSAGEHANDLER_H

#include "../GUICommHandlers.h"

void requestAnswerMessageHandler(enum VariableIDs variableID, char* value, enum FunctionIDs functionID, byte step);

#include "requestAnswerMessageHandler.cpp"

#endif //H2O_MASTER_REQUESTANSWERMESSAGEHANDLER_H
