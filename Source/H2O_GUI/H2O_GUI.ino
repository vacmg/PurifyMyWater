// Visual Micro

/*
    Name:       H2O_MASTER.ino
    Created:	24/08/2020 14:11:50
    Author:     vacmg
*/

#include <Arduino.h>

char VERSION[] PROGMEM = "2.0-alpha-1";

/*------------Config----------------*/

#define DEBUG true
#define DISABLEUI false
#define DISABLECOMM false
#define SETDEFAULTSCREENCONFIG false
#define USEVOLATILECONFIG true

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

#if !DISABLEUI
    UISetup();
#endif

    setDefaultConfig(); // TODO read config from master

    debug('\n');
    //todo Test code after this line



    //while (true); // TODO delete or comment this

    //todo Test code before this line

    debug(F("\nSetup Done\n\n"));
    delay(50);
}

void loop()
{
#if !DISABLEUI
    UILoop();
#endif
}
