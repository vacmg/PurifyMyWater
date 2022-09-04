//
// Created by Victor on 15/08/2022.
//

#include "MasterComHandlers.h"

bool sendBusyCommand()
{
    char availableMessage[3];
    Communications::createSendMessage(availableMessage,BUSY_CMD,"");
    return masterComManager.sendMessage(availableMessage);
}

bool sendAvailableCommand()
{
    char availableMessage[3];
    Communications::createSendMessage(availableMessage,AVAILABLE_CMD,"");
    return masterComManager.sendMessage(availableMessage);
}

void masterComLoop()
{
    switch (guiStatus)
    {
        case GUI_CONNECTING_ST:
            if(masterComManager.commSetup())
            {
                #if DISABLEUI
                sendAvailableCommand();
                #endif
                changeGUIStatus(GUI_CONNECTED_ST);
            }
            else // HandshakeError || MCUsIncompatibleVersionError
            {
                #if !DISABLEUI
                    changeScreenStatus(LOADERROR);
                #endif
                changeGUIStatus(GUI_DISABLED_ST);
            }
            break;

        case GUI_DISABLED_ST:
            masterComManager.commDisabler();
            break;

        case GUI_CONNECTED_ST:
            masterComManager.commLoop();
            break;

        case GUI_SHUTTING_DOWN_ST:

            // place all pre-shutdown instructions before this line // todo draw shutdown message (using error?) & DISABLE SD card
            char message[3];
            Communications::createSendMessage(message,SHUTDOWN_OK_CMD,"");
            masterComManager.sendMessage(message);
            changeGUIStatus(GUI_READY_TO_SHUTDOWN_ST);
            break;

        case GUI_READY_TO_SHUTDOWN_ST:
            if(masterComManager.dataAvailable())
            {
                char message[MAXMSGSIZE] = "";
                char data[MAXVALUESIZE] = "";
                enum VariableIDs variableID;
                Communications::getMessage(message, masterComManager.getSerial());
                if (message[0] == SENDMESSAGE_ID && Communications::extractSendMessage(message, &variableID, data) && variableID == SHUTDOWN_CANCEL_CMD)
                {
                    Communications::createSendMessage(message,SHUTDOWN_OK_CMD,"");
                    masterComManager.sendMessage(message);
                    changeGUIStatus(GUI_CONNECTED_ST);
                }
            }
            break;
    }
}
