//
// Created by Victor on 15/08/2022.
//

#include "sendMessageHandler.h"

void sendMessageHandler(enum VariableIDs variableID, char* value)
{
    if(variableID == SHUTDOWN_CMD)
    {
        debug(F("SHUTDOWN COMMAND RECEIVED\n"));
        changeGUIStatus(GUI_SHUTTING_DOWN_ST);
    }
}
