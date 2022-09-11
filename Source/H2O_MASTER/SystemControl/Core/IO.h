//
// Created by Victor on 07/08/2022.
//

#ifndef H2O_MASTER_IO_H
#define H2O_MASTER_IO_H

#include "Core.h"

#define SCREENSHUTDOWNDELAY 15000

#if !DISABLECOMM
    #define wasChangedAndSet(variable, newValue) wasChangedAndSetFn(variable,newValue)
#else
    #define wasChangedAndSet(variable, newValue) (*variable=newVariable)||true
#endif

/*------------Input-----------------*/

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

// Used to check for PumpTimeoutError
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

// This class handles Screen power management
class ScreenPowerManager
{
public:
    ScreenPowerManager(byte screenRelay, unsigned long shutdownDelayMs);
    void setScreen(bool status);
    void forceScreen(bool status);
    bool isScreenOn() const;
    bool isDesiredScreenOn() const;
    void loop();

private:
    byte screenRelay;
    unsigned long shutdownDelayMs;
    unsigned long screenPowerMillis;
    bool screenSt;
    bool desiredScreenSt;
    bool changing;
};

ScreenPowerManager screenPowerManager(screenRelay,SCREENSHUTDOWNDELAY); // This object handles Screen power management

// This function is used to perform animations on the RGB status led.
// If an animation is loaded in currentAnimation and this function is called everytime, the animation will be displayed on the LED
void updateAnimation();

// Used to set a color on the rgb status led by setting the amount of each color from 0 to 255
void setColor(byte r, byte g, byte b);
void setColor(byte color[3]);

// Depending on the hardware used, relays are activated with high or low signals.
// To maintain readability, in this function we set what kind of signal we need to activate those relays.
// A true value means that the circuit is closed whereas a false means that the circuit is opened.
void output(byte pin, bool value);

// Depending on the hardware used, digital sensors send high or low signals upon detecting something or not.
// To maintain readability, in this function we set what kind of signal shows that the sensor is detecting something.
// A true value means that the sensor is detecting something whereas a false means that the sensor is not detecting anything.
bool readDigitalSensor(byte pin);

// This function gets all buoys current status
void getBuoyStatus();

#if !DISABLECOMM
// This auxiliary function checks if a variable value has changed & updates its value
bool wasChangedAndSetFn(bool* variable, bool newValue);
#endif

#include "IO.cpp"

#endif //H2O_MASTER_IO_H
