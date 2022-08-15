/*---------------GUI----------------*/
/*
#if GUI
    #define SCREENOFF 0
    #define SCREENSTARTING 1
    #define SCREENON 2
    #define SCREENCONNECTING 3
    #define SCREENNOTCONNECTED 4
    #define SCREENSHUTTINGDOWN 5

    byte screenStatus = SCREENOFF; // 0 = OFF, 1 = ON, 2 = Establishing connection, 3 = Unable to establish connection
    byte handshakeRetries = 0; // stores n� of handshake attempts // max n� of attempts is stored in MAXHANDSHAKERETRIES
#endif
*/
/*---------------GUI----------------*/

/*-----------------GUI------------------*/

/*
// This function handles the screen system: communication, on/off, errors.
// It also checks and answer any request from the screen client if it is connected
void updateServer()
{
    switch (screenStatus)
    {
    case SCREENNOTCONNECTED:
    case SCREENSHUTTINGDOWN:
        debug(F("UpdateServer - Screen shutting down\n"));
        //TODO send shutdown command, wait for answer and disconnect the screen
        Serial1.end();
        screenStatus = SCREENOFF;

        delay(5000); // TODO adjust time

        output(screenRelay, 0);
        delay(1000);
        break;
    case SCREENSTARTING:
        debug(F("UpdateServer - Screen starting...\n"));
        output(screenRelay, 1);
        delay(1000);
        Serial1.begin(SCREENBAUDRATE);
        debug(F("UpdateServer - Connecting to screen...\n"));
        screenStatus = SCREENCONNECTING;
        handshakeRetries = 0;
        break;
    case SCREENCONNECTING:
        if (doServerHandshake())
        {
            debug(F("UpdateServer - Screen ready\n"));
            screenStatus = SCREENON;
        }
        else if (++handshakeRetries >= MAXHANDSHAKERETRIES)
        {
            screenStatus = SCREENNOTCONNECTED; // TODO what happens when the screen cannot connect?
            raise(ScreenNotConnectedError, F("Unable to communicate to the screen, double check the connections to it"));
        }

        break;
    case SCREENON:
        if (Serial1.available())
        {
            // TODO server side stuff and delete this
            #if SCREENBRIDGEMODE
                while (Serial1.available())
                {
                    Serial.write(Serial1.read());
                }
            #else
                ;
            #endif
        }

        #if !SCREENALWAYSON
            if (!digitalRead(screenSensor))
            {
                screenStatus = SCREENSHUTTINGDOWN;
            }
        #endif
        break;

    case SCREENOFF:
        if (digitalRead(screenSensor))
        {
            screenStatus = SCREENSTARTING;
        }
        #if SCREENALWAYSON
            screenStatus = SCREENSTARTING;
        #endif
        break;
    }
}
*/

/*-----------------GUI------------------*/