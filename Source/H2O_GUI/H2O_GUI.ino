// Visual Micro

/*
    Name:       H2O_MASTER.ino
    Created:	24/08/2020 14:11:50
    Author:     vacmg
*/

//todo add eeprom config

/*------------Config----------------*/

#define DEBUG true
#define SETDEFAULTSCREENCONFIG false
#define USEVOLATILECONFIG true

#define SCREENBAUDRATE 115200
#define SCREENALWAYSON 1 // TODO auto on/off
#define MAXMESSAGERETRIES 3
#define MAXHANDSHAKERETRIES 3
#define HANDSHAKETIMEOUT 10000
#define MSGTIMEOUT 2500
#define SCREENTIMEOUT 120000


/*------------Config----------------*/

#include "UI/UI.h"


//Main Functions

void setup()
{
#if DEBUG
    Serial.begin(115200);
    delay(200);
    debug(F("Connected\n"));
    delay(50);
#endif

    UISetup();

    setDefaultConfig(); // TODO read config from master

    debug('\n');
    //todo Test code after this line

    drawBackground();
    drawMenu();
    drawBoolPopup("patataAlerta", F("test.txt"), getString(YES_STR),getString(NO_STR));

    while (true); // TODO delete or comment this

    //todo Test code before this line

    debug(F("\nSetup Done\n\n"));
    delay(50);
}

void loop()
{
    UILoop();
}
