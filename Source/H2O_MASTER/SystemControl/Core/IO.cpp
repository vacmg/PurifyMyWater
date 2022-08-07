//
// Created by Victor on 07/08/2022.
//

#include "IO.h"

/*------------Output Control------------*/

// Depending on the hardware used, relays are activated with high or low signals.
// To maintain readability, in this function we set what kind of signal we need to activate those relays
// A true value means that the circuit is closed whereas a false means that the circuit is opened
void output(byte pin, bool value)
{
    if (!(pin == redLed || pin == greenLed || pin == blueLed || pin == voltRelay || pin == outFan || pin == PSUFan || pin == inFan))
    {
        value = !value;
    }
    switch (pin)
    {
        case wellPump:
            data.wellPumpSt = value;
            break;
        case UVPump:
            data.UVPumpSt = value;
            break;
        case endPump:
            data.endPumpSt = value;
            break;
        case filterRelay:
            data.filterPumpSt = value;
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

// This function gets all buoys current status
void getBuoyStatus()
{
    data.secBuoySt = digitalRead(secBuoy);
    data.lowSurfaceBuoySt = digitalRead(lowSurfaceBuoy);
    data.highSurfaceBuoySt = digitalRead(highSurfaceBuoy);
    data.lowFilteredBuoySt = digitalRead(lowFilteredBuoy);
    data.highFilteredBuoySt = digitalRead(highFilteredBuoy);
    data.lowPurifiedBuoySt = digitalRead(lowPurifiedBuoy);
    data.highPurifiedBuoySt = digitalRead(highPurifiedBuoy);
    data.endBuoySt = digitalRead(endBuoy);

    data.screenSensorSt = digitalRead(screenSensor); // TODO get this value in communication's loop
}

/*------------Input Control-------------*/
