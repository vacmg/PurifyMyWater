//
// Created by Victor on 15/08/2022.
//

#include "GUICommHandlers.h"

void GUILoop()
{
    dataStorage.data.screenSensorSt = readDigitalSensor(screenSensor);
    //debug(F("screenSensorSt: "));debug(dataStorage.data.screenSensorSt);debug('\n');
    screenPowerManager.loop();

    switch (guiStatus)
    {
        case GUI_OFF_ST:
            if(dataStorage.data.screenSensorSt)
            {
                screenPowerManager.setScreen(1);
                delay(250);
                if(guiComManager.commSetup())
                {
                    changeGUIStatus(GUI_CONNECTED_ST);
                }
                else if (dataStorage.data.currentError == MCUsIncompatibleVersionError)
                {
                    changeGUIStatus(GUI_ERROR_ST);
                }
                else // HandshakeError
                {
                    screenPowerManager.forceScreen(0);
                    changeGUIStatus(GUI_COOLDOWN_ST);
                    debug(F("Cooldown for "));debug(GUICOOLDOWNTIME);debug(F("ms\n"));
                    guiMillis = millis();
                }
            }
            break;

        case GUI_CONNECTED_ST:
            guiComManager.commLoop(); // Handle all commands

            if((screenPowerManager.isDesiredScreenOn() && !dataStorage.data.screenSensorSt) || dataStorage.data.currentError == GUINotRespondingError)
            {
                char message[3];
                Communications::createSendMessage(message,SHUTDOWN_OK_CMD,"");
                guiComManager.sendMessage(message);

                changeGUIStatus(GUI_SHUTTING_DOWN_ST);
            }
            break;

        case GUI_SHUTTING_DOWN_ST:
            if(guiComManager.dataAvailable())
            {
                char message[MAXMSGSIZE] = "";
                char data[MAXVALUESIZE] = "";
                enum VariableIDs variableID;
                Communications::getMessage(message,guiComManager.getSerial());
                if(message[0] == SENDMESSAGE_ID && Communications::extractSendMessage(message,&variableID,data) && variableID == SHUTDOWN_OK_CMD)
                {
                    screenPowerManager.setScreen(0);
                    changeGUIStatus(GUI_COOLDOWN_ST);
                    debug(F("Cooldown for "));debug(GUICOOLDOWNTIME);debug(F("ms\n"));
                    guiMillis = millis();
                }
                else // GUICannotSafelyShutdownError
                {
                    dataStorage.data.currentError = GUICannotSafelyShutdownError;

                    char message[3];
                    Communications::createSendMessage(message,SHUTDOWN_OK_CMD,"");
                    guiComManager.sendMessage(message);

                    changeGUIStatus(GUI_ERROR_ST);
                }
            }
            break;

        case GUI_COOLDOWN_ST:
            if(guiMillis+GUICOOLDOWNTIME<millis())
            {
                changeGUIStatus(GUI_OFF_ST);
            }
            break;

        case GUI_ERROR_ST:
            switch (dataStorage.data.currentError)
            {
                case MCUsIncompatibleVersionError:
                    if(screenPowerManager.isDesiredScreenOn() && !dataStorage.data.screenSensorSt)
                    {
                        screenPowerManager.setScreen(0);
                        changeGUIStatus(GUI_DISABLED_ST);
                    }
                    break;

                case GUICannotSafelyShutdownError:
                    if(guiComManager.dataAvailable())
                    {
                        char message[MAXMSGSIZE] = "";
                        char data[MAXVALUESIZE] = "";
                        enum VariableIDs variableID;
                        Communications::getMessage(message,guiComManager.getSerial());
                        if(message[0] == SENDMESSAGE_ID && Communications::extractSendMessage(message,&variableID,data) && variableID == SHUTDOWN_OK_CMD)
                        {
                            screenPowerManager.setScreen(0);
                        }
                        else // 2nd time GUICannotSafelyShutdownError
                        {
                            screenPowerManager.forceScreen(0);
                        }
                        dataStorage.data.currentError = NoError;
                        changeGUIStatus(GUI_COOLDOWN_ST);
                        debug(F("Cooldown for "));debug(GUICOOLDOWNTIME);debug(F("ms\n"));
                        guiMillis = millis();
                    }
                    break;
            }
            break;
    }
}
