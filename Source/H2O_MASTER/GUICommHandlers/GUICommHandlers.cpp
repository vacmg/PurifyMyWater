//
// Created by Victor on 15/08/2022.
//

#include "GUICommHandlers.h"

void GUILoop()
{
    data.screenSensorSt = readDigitalSensor(screenSensor);
    screenPowerManager.loop();
    switch (guiStatus)
    {
        case GUI_ERROR_ST:
            switch (data.currentError)
            {
                case GUICannotSafelyShutdownError:
                    delay(1000);
                    // TODO send shutdown command
                    // TODO wait for OK
                    bool ok;
                    if(ok)
                    {
                        screenPowerManager.setScreen(0);
                    }
                    else
                    {
                        screenPowerManager.setScreen(1);
                        data.currentError = GUINotRespondingError;
                        guiStatus = GUI_ERROR_ST;
                    }
                    break;

                case GUINotRespondingError:
                    screenPowerManager.forceScreen(0);
                    gui.commDisabler();
                    data.currentError=NoError;
                    guiStatus = GUI_OFF_ST;
                    delay(1500);
                    break;

                case MCUsIncompatibleVersionError:
                    if(!data.screenSensorSt)
                    {
                        shutdownScreen();
                    }
                    break;

                case HandshakeError:
                    guiStatus = GUI_DISABLED_ST;
                    break;
            }
            break;

        case GUI_DISABLED_ST:
            switch (data.currentError)
            {
                case HandshakeError:
                    if(!data.screenSensorSt)
                    {
                        screenPowerManager.setScreen(0);
                        gui.commDisabler();
                    }
                    break;
            }
            break;

        case GUI_SHUTTING_DOWN_ST:
            if(screenPowerManager.isScreenOn())
            {
                if(data.screenSensorSt)
                {
                    screenPowerManager.setScreen(1);
                    // TODO send shutdown cancel command
                    // TODO wait for OK
                }
            }
            else
            {
                guiStatus = GUI_OFF_ST;
                gui.commDisabler();
            }
            break;

        case GUI_OFF_ST:
            if(data.screenSensorSt)
            {
                screenPowerManager.setScreen(1);
                delay(250);
                if(gui.commSetup())
                {
                    guiStatus = GUI_CONNECTING_ST;
                }
                else
                {
                    guiStatus = GUI_ERROR_ST;
                }

            }
            break;

        case GUI_CONNECTING_ST:
            if(gui.commSetup())
            {
                guiStatus = GUI_CONNECTED_ST;
            }
            else
                guiStatus = GUI_ERROR_ST;
            break;

        case GUI_CONNECTED_ST:
            gui.commLoop();
            if(!data.screenSensorSt)
            {
                shutdownScreen();
            }
            break;
    }
}

void shutdownScreen()
{
    guiStatus = GUI_SHUTTING_DOWN_ST;
    if(!data.screenSensorSt)
    {
        // TODO send shutdown command
        // TODO wait for OK
        bool ok;
        if(ok)
        {
            screenPowerManager.setScreen(0);
        }
        else
        {
            data.currentError = GUICannotSafelyShutdownError;
            guiStatus = GUI_ERROR_ST;
        }
    }
}
