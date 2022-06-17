// Visual Micro

/*
    Name:       H2O_MASTER.ino
    Created:	24/08/2020 14:11:50
    Author:     vacmg
*/

//todo add eeprom config

#include <Arduino.h>
#include "H2O_UI/UI.h"

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

