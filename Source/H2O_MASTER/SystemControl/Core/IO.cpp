//
// Created by Victor on 07/08/2022.
//

#include "IO.h"

/*------------Output Control------------*/

// This class handles Screen power management
ScreenPowerManager::ScreenPowerManager(byte screenRelay, unsigned long shutdownDelayMs)
{
    this->screenSt = false;
    this->desiredScreenSt = false;
    this->screenRelay = screenRelay;
    this->shutdownDelayMs = shutdownDelayMs;
    this->screenPowerMillis = 0;
    this->changing = false;
}

void ScreenPowerManager::setScreen(bool status)
{
    desiredScreenSt = status;
    debug(F("Set Screen MCU to "));debug(status?F("Boot\n"):F("Shutdown\n"));
    if(status == 1 && screenSt == 0)
    {
        debug(F("ScreenPowerManager: Booting Screen MCU\n"));
        output(screenRelay,1);
        screenSt = 1;
    }
}

void ScreenPowerManager::forceScreen(bool status)
{
    debug(F("Force Screen MCU to "));debug(status?F("Boot\n"):F("Shutdown\n"));
    desiredScreenSt = status;
    screenSt = status;
    output(screenRelay,status);
}

void ScreenPowerManager::loop()
{
    if(!changing && screenSt!=desiredScreenSt) // if not changing, and it should
    {
        debug(F("ScreenPowerManager: Screen MCU Shutdown timer started\n"));
        screenPowerMillis = millis();
        changing = true;
    }
    else if (changing && screenSt==desiredScreenSt) // If change was cancelled
    {
        debug(F("ScreenPowerManager: Screen MCU Shutdown timer cancelled\n"));
        changing = false;
    }
    else if(changing && screenPowerMillis+shutdownDelayMs<millis()) // if change is about to be performed
    {
        debug(F("ScreenPowerManager: Shutting down Screen MCU\n"));
        output(screenRelay,desiredScreenSt);
        screenSt = desiredScreenSt;
        changing = false;
    }
}

bool ScreenPowerManager::isScreenOn()
{
    return screenSt;
}

bool ScreenPowerManager::isDesiredScreenOn()
{
    return desiredScreenSt;
}


// Depending on the hardware used, relays are activated with high or low signals.
// To maintain readability, in this function we set what kind of signal we need to activate those relays.
// A true value means that the circuit is closed whereas a false means that the circuit is opened.
void output(byte pin, bool value)
{
    if (!(pin == redLed || pin == greenLed || pin == blueLed || pin == voltRelay || pin == outFan || pin == PSUFan || pin == inFan))
    {
        value = (!value);
    }
    switch (pin)
    {
        case wellPump:
            dataStorage.data.wellPumpSt = value;
            break;
        case UVPump:
            dataStorage.data.UVPumpSt = value;
            break;
        case endPump:
            dataStorage.data.endPumpSt = value;
            break;
        case filterRelay:
            dataStorage.data.filterPumpSt = value;
            break;
    }
    digitalWrite(pin, value);
}

// Used to set a color on the rgb status led by setting the amount of each color from 0 to 255
void setColor(byte color[3])
{
    analogWrite(redLed, color[0]);
    analogWrite(greenLed, color[1]);
    analogWrite(blueLed, color[2]);
}

// Used to set a color on the rgb status led by setting the amount of each color from 0 to 255
void setColor(byte r, byte g, byte b)
{
    analogWrite(redLed, r);
    analogWrite(greenLed, g);
    analogWrite(blueLed, b);
}

// This function is used to perform animations on the RGB status led.
// If an animation is loaded in currentAnimation and this function is called everytime, the animation will be displayed on the LED
void updateAnimation()
{
    if (currentAnimation != NULL && millis() > prevAnimationMillis + currentAnimation->frameDelay)
    {
        setColor(currentAnimation->animation[currentAnimation->currentFrame]);
        if (currentAnimation->currentFrame + 1 >= currentAnimation->animationSize)
        {
            currentAnimation->currentFrame = 0;
        }
        else
        {
            currentAnimation->currentFrame++;
        }
        prevAnimationMillis = millis();
    }
}

/*------------Output Control------------*/

/*------------Input Control-------------*/

// Depending on the hardware used, digital sensors send high or low signals upon detecting something or not.
// To maintain readability, in this function we set what kind of signal shows that the sensor is detecting something.
// A true value means that the sensor is detecting something whereas a false means that the sensor is not detecting anything.
bool readDigitalSensor(byte pin)
{
#if SCREENALWAYSON
    if(pin == screenSensor)
        return true;
#endif

    bool data = digitalRead(pin);
    /*if(pin == xxx || ...)
    {
        data = (!data);
    }*/
    return data;
}

// This function gets all buoys current status
void getBuoyStatus()
{
    dataStorage.data.secBuoySt = readDigitalSensor(secBuoy);
    dataStorage.data.lowSurfaceBuoySt = readDigitalSensor(lowSurfaceBuoy);
    dataStorage.data.highSurfaceBuoySt = readDigitalSensor(highSurfaceBuoy);
    dataStorage.data.lowFilteredBuoySt = readDigitalSensor(lowFilteredBuoy);
    dataStorage.data.highFilteredBuoySt = readDigitalSensor(highFilteredBuoy);
    dataStorage.data.lowPurifiedBuoySt = readDigitalSensor(lowPurifiedBuoy);
    dataStorage.data.highPurifiedBuoySt = readDigitalSensor(highPurifiedBuoy);
    dataStorage.data.endBuoySt = readDigitalSensor(endBuoy);
}

/*------------Input Control-------------*/
