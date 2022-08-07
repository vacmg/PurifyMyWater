//
// Created by Victor on 05/08/2022.
//

#ifndef H2O_MASTER_PURIFICATION_H
#define H2O_MASTER_PURIFICATION_H

/*------------Libraries-------------*/

#include <Arduino.h>
#include "../Shared/SharedData.h"
#include <Filters.h>

#if TEMPERATURE
    #include <OneWire.h>
    #include <DallasTemperature.h>
#endif

/*------------Libraries-------------*/

/*------------Errors----------------*/

#define UNEXPECTEDBEHAVIORERROR 00 // The code is being executed in an unwanted way (a bug is being detected) // error code 00

#if TEMPERATURE
    #define TEMPSENSORSAMOUNTERROR 10 // Some temp sensors are not properly connected to the one-wire bus // error code 10
    #define EXTREMEHOTTEMPERROR 11 // Control system temperatures are extremely high, and it is dangerous to operate // error code 11
#endif

#define BUOYINCONGRUENCEERROR 20 // The system has detected an incongruent state with the readings of the buoy sensors (often caused by a non-connected or malfunctioning buoy) // error code 21
#define PUMPTIMEOUTERROR 21 // The system has spent so much time with a pump working. Probably the circuit has a leak or a pump is not working properly // error code 22
#define UVLIGHTNOTWORKINGERROR 22 // The UV amperage sensor didn't detect enough current. The UV light must be either broken or disconnected (check and replace the UV light) // error code 23

#define SCREENNOTCONNECTEDERROR 30 // Cannot handshake with the screen. Probably a broken or bad connected cable or the screen didn't have the correct firmware // error code 30

/*------------Errors----------------*/

/*------------FunctionHeaders-------*/

void purificationSetup();
void purificationLoop();

#if DEBUG
    void readAllSensors();
#endif

#if TEMPERATURE
    void tempControl();
    void getSensorsTemp(float* temp);
#endif

void disconnectEverything();
void errorCheck();
void raise(byte error, const String& possibleExplanation);
void logACAmps();
float getACAmps();
float getDCAmps(int samples);
void waitForVoltage(float volts);
void voltControl();
float loadOffset();
float voltRead();
float fmap(float x, float in_min, float in_max, float out_min, float out_max);
void updateAnimation();
void setColor(byte r, byte g, byte b);
void setColor(byte color[3]);
void output(byte pin, bool value);

/*------------FunctionHeaders-------*/

/*------------Const&vars------------*/

/*------------Input-----------------*/

const byte voltSensor = A0;
const byte mainAmpSensor = A1;
const byte UVAmpSensor = A2;

const byte secBuoy = 2;
const byte lowSurfaceBuoy = 3;
const byte highSurfaceBuoy = 4;
const byte lowFilteredBuoy = 5;
const byte highFilteredBuoy = 6;
const byte lowPurifiedBuoy = 7;
const byte highPurifiedBuoy = 8;
const byte endBuoy = 9;
const byte tempPin = 48;

const byte screenSensor = 23; // 1 = case open, 0 = case closed

RunningStatistics inputStats;                 // create statistics to look at the raw test signal
bool ACAmpsDoMeasurement = false; // boolean value used as a switch to begin measuring AC current

/*------------Input-----------------*/

/*------------Output----------------*/

#define BLACK 0, 0, 0
#define RED 255, 0 ,0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255
#define WHITE 255, 255, 255
#define YELLOW 255, 255, 0
#define CYAN 0, 255, 255
#define PURPLE 255, 0, 255

// Tie an action to a specific color
#define UNDERVOLTAGECOLOR PURPLE
#define WORKINGCOLOR CYAN
#define BOOTINGCOLOR YELLOW

const byte voltSSRelay = 33;
const byte voltRelay = 49;
const byte ACInverter = 45;
const byte wellPump = 43;
const byte UVPump = 39;
const byte endPump = 41;
const byte UVRelay = 37;
const byte filterRelay = 35;
const byte outFan = 22;
const byte PSUFan = 24;
const byte inFan = 26;
const byte redLed = 10;
const byte greenLed = 12;
const byte blueLed = 11;

const byte screenRelay = 47;

// Used to check for PUMPTIMEOUTERROR
unsigned long wellPumpPrevMillis = 0;
unsigned long UVPumpPrevMillis = 0; // UVPumpPrevMillis also stores UV working start time
unsigned long endPumpPrevMillis = 0;
unsigned long filterPumpPrevMillis = 0;

typedef struct ledAnimation
{
    int frameDelay; // Delay between frames (in ms)
    byte animationSize; // Number of used frames
    byte currentFrame; // Current frame
    byte animation[16][3]; // Up to 16 frames per animation
};

ledAnimation* currentAnimation; // Pointer to current animation
unsigned long prevAnimationMillis = 0;

ledAnimation testAnimation = { 1500,5,0,{{255,0,0},{0,255,0},{0,0,255},{255,255,255},{0,0,0}} };
ledAnimation defaultErrorAnimation = { 500,2,0,{{255,0,0},{0,0,0}} };

/*------------Output----------------*/

/*------------Temperature-----------*/
#if TEMPERATURE
unsigned long tempMillis = 0;

// Set up a oneWire instance to communicate with any OneWire device
OneWire oneWire(tempPin);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

#define INSENSOR 2
#define OUTSENSOR 0
#define PSUSENSOR 1
#endif
/*------------Temperature-----------*/

/*------------Other-----------------*/

// TODO change to enum
#define TRANSITIONTOIDLE 0
#define IDLE 1
#define TRANSITIONTOPUMPSWORKING 2
#define PUMPSWORKING 3
#define TRANSITIONTOFILTERWORKING 4
#define FILTERWORKING 5

byte mode = TRANSITIONTOIDLE; // Working mode is changed using this variable // TODO use enum instead of byte
unsigned long UVMillis = 0;
unsigned long workingTime = 0; // Time that UV pump is working (in ms) // Used to calculate the amount of purified water

/*------------Other-----------------*/

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

/*------------Const&vars------------*/


#include "Purification.cpp"

#endif //H2O_MASTER_PURIFICATION_H
