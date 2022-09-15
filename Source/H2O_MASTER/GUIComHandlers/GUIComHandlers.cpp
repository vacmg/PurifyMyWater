//
// Created by Victor on 15/08/2022.
//

#include "GUIComHandlers.h"

// THIS FUNCTION MUST RUN BEFORE USING guiComManager
void GUISetup()
{
    guiComManager.setSendMessageHandler(sendMessageHandler);
    guiComManager.setRequestMessageHandler(requestMessageHandler);
    guiComManager.setRequestAnswerMessageHandler(requestAnswerMessageHandler);
}

void GUILoop() // TODO guard sendmessages from a guistatus different from GUI_CONNECTED_ST
{
    bool screenSensorSt = readDigitalSensor(screenSensor);
    //debug(F("screenSensorSt: "));debug(dataStorage.data.screenSensorSt);debug('\n');
    screenPowerManager.loop();

    switch (guiStatus)
    {
        case GUI_OFF_ST:
            if(screenSensorSt)
            {
                screenPowerManager.setScreen(1);
                delay(250);
                if(guiComManager.commSetup())
                {
                    changeGUIStatus(GUI_BUSY_ST);
                }
                else if (currentError == MCUsIncompatibleVersionError)
                {
                    changeGUIStatus(GUI_ERROR_ST);
                }
                else // HandshakeError
                {
                    screenPowerManager.setScreen(0);
                    changeGUIStatus(GUI_COOLDOWN_ST);
                    debug(F("Cooldown for "));debug(GUICOOLDOWNTIME);debug(F("ms\n"));
                    guiMillis = millis();
                }
            }
            break;

        case GUI_BUSY_ST:
        case GUI_CONNECTED_ST:
            guiComManager.commLoop(); // Handle all commands

            if((screenPowerManager.isDesiredScreenOn() && !screenSensorSt) || currentError == DestinationMCUNotRespondingError)
            {
                char message[3];
                Communications::createSendMessage(message,SHUTDOWN_CMD,"");
                guiComManager.sendMessage(message);

                changeGUIStatus(GUI_SHUTTING_DOWN_ST);
                guiMillis = millis();
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
                    screenPowerManager.setScreen(false);
                    guiSw = true;
                    changeGUIStatus(GUI_COOLDOWN_ST);
                    debug(F("Cooldown for "));debug(GUICOOLDOWNTIME);debug(F("ms\n"));
                    guiMillis = millis();
                }
                else // GUICannotSafelyShutdownError
                {
                    debug(F("Error detected: "));debug(errorToString(GUICannotSafelyShutdownError));debug('\n');
                    char message[3];
                    Communications::createSendMessage(message,SHUTDOWN_CMD,"");
                    guiComManager.sendMessage(message);

                    changeError(GUICannotSafelyShutdownError);
                    changeGUIStatus(GUI_ERROR_ST);
                    debug(F("Retrying...\n"));
                    guiMillis = millis();
                }
            }
            else if (guiMillis+(2*MSGTIMEOUT)<millis())
            {
                debug(F("Timeout! Error detected: "));debug(errorToString(GUICannotSafelyShutdownError));debug('\n');
                char message[3];
                Communications::createSendMessage(message,SHUTDOWN_CMD,"");
                guiComManager.sendMessage(message);

                changeError(GUICannotSafelyShutdownError);
                changeGUIStatus(GUI_ERROR_ST);
                debug(F("Retrying...\n"));
                guiMillis = millis();
            }
            break;

        case GUI_COOLDOWN_ST:
            if (guiMillis+SCREENSHUTDOWNDELAY-1000>=millis() && currentError!=HandshakeError && currentError!=DestinationMCUNotRespondingError && currentError !=GUICannotSafelyShutdownError && screenSensorSt) // cancel shutdown
            {
                debug(F("Reconnecting...\n"));
                screenPowerManager.setScreen(true);
                char message[3];
                Communications::createSendMessage(message,SHUTDOWN_CANCEL_CMD,"");
                guiComManager.sendMessage(message);
                changeGUIStatus(GUI_RECONNECTING_ST);
                guiMillis = millis();
            }
            else if (guiSw && guiMillis+SCREENSHUTDOWNDELAY-1000<millis())
            {
                guiSw = false;
                debug(F("Disabling communications...\n"));
                guiComManager.commDisabler();
            }
            if(guiMillis+GUICOOLDOWNTIME<millis())
            {
                if(currentError == DestinationMCUNotRespondingError || currentError == HandshakeError || currentError == GUICannotSafelyShutdownError)
                changeError(NoError);
                changeGUIStatus(GUI_OFF_ST);
            }
            break;

        case GUI_RECONNECTING_ST:
            if(guiComManager.dataAvailable())
            {
                char message[MAXMSGSIZE] = "";
                char data[MAXVALUESIZE] = "";
                enum VariableIDs variableID;
                Communications::getMessage(message,guiComManager.getSerial());
                if(message[0] == SENDMESSAGE_ID && Communications::extractSendMessage(message,&variableID,data) && variableID == SHUTDOWN_OK_CMD)
                {
                    changeGUIStatus(GUI_CONNECTED_ST);
                    debug(F("Screen MCU reconnected\n"));
                }
            }
            else if (guiMillis+(2*MSGTIMEOUT)<millis())
            {
                changeError(DestinationMCUNotRespondingError);
                debug(F("Cannot reconnect Screen MCU, shutting it down\n"));
                screenPowerManager.setScreen(false);
                changeGUIStatus(GUI_COOLDOWN_ST);
                debug(F("Cooldown for "));debug(GUICOOLDOWNTIME);debug(F("ms\n"));
                guiMillis = millis();
            }
            break;

        case GUI_ERROR_ST:
            switch (currentError)
            {
                case MCUsIncompatibleVersionError:
                    if(screenPowerManager.isDesiredScreenOn() && !screenSensorSt)
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
                            screenPowerManager.setScreen(false);
                        }
                        else // 2nd time GUICannotSafelyShutdownError
                        {
                            changeError(GUICannotSafelyShutdownError);
                            debug(F("Disabling communications...\n"));
                            guiComManager.commDisabler();
                            screenPowerManager.forceScreen(false);
                        }
                        changeGUIStatus(GUI_COOLDOWN_ST);
                        debug(F("Cooldown for "));debug(GUICOOLDOWNTIME);debug(F("ms\n"));
                        guiMillis = millis();
                    }
                    else if (guiMillis+(2*MSGTIMEOUT)<millis())
                    {
                        changeError(GUICannotSafelyShutdownError);
                        debug(F("Disabling communications...\n"));
                        guiComManager.commDisabler();

                        screenPowerManager.forceScreen(false);

                        changeGUIStatus(GUI_COOLDOWN_ST);
                        debug(F("Cooldown for "));debug(GUICOOLDOWNTIME);debug(F("ms\n"));
                        guiMillis = millis();
                    }
                    break;
            }
            break;
    }
}
