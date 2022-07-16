// Visual Micro

/*
    Name:       H2O_MASTER.ino
    Created:	24/08/2020 14:11:50
    Author:     vacmg
*/

//todo add eeprom config

/*------------Config----------------*/

#define DEBUG true

#define SCREENBAUDRATE 115200
#define SCREENALWAYSON 1 // TODO auto on/off
#define MAXMESSAGERETRIES 3
#define MAXHANDSHAKERETRIES 3
#define HANDSHAKETIMEOUT 10000
#define MSGTIMEOUT 2500
#define SCREENTIMEOUT 120000


/*------------Config----------------*/

#include "UI/UI.h"
#include "Communications/ComManager.h"
#include "Communications/Communications.h"


//Main Functions

void setup()
{
#if DEBUG
    Serial.begin(115200);
    delay(200);
    Serial.println(F("Connected"));
    delay(50);
#endif
    UISetup();

    //todo Test code after this line

    //while (true); // TODO delete or comment this

    //todo Test code before this line

#if DEBUG
    Serial.println(F("\nSetup Done\n"));
    delay(50);
#endif
}

void loop()
{
    UILoop();
}
