//
// Created by Victor on 15/08/2022.
//

#ifndef H2O_MASTER_REQUESTMESSAGEHANDLER_H
#define H2O_MASTER_REQUESTMESSAGEHANDLER_H

#include "../GUICommHandlers.h"

void requestMessageHandler(enum VariableIDs variableID, enum FunctionIDs functionID, byte step);

#include "requestMessageHandler.cpp"

#endif //H2O_MASTER_REQUESTMESSAGEHANDLER_H
