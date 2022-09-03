//
// Created by Victor on 15/08/2022.
//

#include "GUIComHandlers.h"

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

        case GUI_CONNECTED_ST:
            guiComManager.commLoop(); // Handle all commands

            if((screenPowerManager.isDesiredScreenOn() && !dataStorage.data.screenSensorSt) || currentError == DestinationMCUNotRespondingError)
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
                    screenPowerManager.setScreen(0);
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

                    currentError = GUICannotSafelyShutdownError;
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

                currentError = GUICannotSafelyShutdownError;
                changeGUIStatus(GUI_ERROR_ST);
                debug(F("Retrying...\n"));
                guiMillis = millis();
            }
            break;

        case GUI_COOLDOWN_ST:
            if (guiMillis+SCREENSHUTDOWNDELAY-1000>=millis() && currentError!=HandshakeError && currentError!=DestinationMCUNotRespondingError && currentError !=GUICannotSafelyShutdownError && dataStorage.data.screenSensorSt) // cancel shutdown
            {
                debug(F("Reconnecting...\n"));
                guiSw = true;
                screenPowerManager.setScreen(1);
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
                    currentError = NoError;
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
                currentError = DestinationMCUNotRespondingError;
                debug(F("Cannot reconnect Screen MCU, shutting it down\n"));
                screenPowerManager.setScreen(0);
                changeGUIStatus(GUI_COOLDOWN_ST);
                debug(F("Cooldown for "));debug(GUICOOLDOWNTIME);debug(F("ms\n"));
                guiMillis = millis();
            }
            break;

        case GUI_ERROR_ST:
            switch (currentError)
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
                            currentError = GUICannotSafelyShutdownError;
                            debug(F("Disabling communications...\n"));
                            guiComManager.commDisabler();
                            screenPowerManager.forceScreen(0);
                        }
                        changeGUIStatus(GUI_COOLDOWN_ST);
                        debug(F("Cooldown for "));debug(GUICOOLDOWNTIME);debug(F("ms\n"));
                        guiMillis = millis();
                    }
                    else if (guiMillis+(2*MSGTIMEOUT)<millis())
                    {
                        currentError = GUICannotSafelyShutdownError;
                        debug(F("Disabling communications...\n"));
                        guiComManager.commDisabler();

                        screenPowerManager.forceScreen(0);

                        changeGUIStatus(GUI_COOLDOWN_ST);
                        debug(F("Cooldown for "));debug(GUICOOLDOWNTIME);debug(F("ms\n"));
                        guiMillis = millis();
                    }
                    break;
            }
            break;
    }
}
