//
// Created by Victor on 05/08/2022.
//

#include "Purification.h"

/*------------Temp Control--------------*/
#if TEMPERATURE

// Used to get temperature in celsius of the 3 temperature sensors
// It modifies the given array that MUST be of length 3
void getSensorsTemp(float* temp)
{
    sensors.requestTemperatures();
    for (int i = 0; i < 3; i++)
    {
        temp[i] = sensors.getTempCByIndex(i);
    }
}

// Used to control the temperature of the main control unit
void tempControl()
{
    float temp[3];
    getSensorsTemp(temp);

    // Start or stop fans according to external and internal temperature
    if (temp[INSENSOR] > config.STARTCASETEMP && temp[OUTSENSOR] < temp[INSENSOR])
    {
        output(inFan, 1);
        output(outFan, 1);
    }
    else if (temp[INSENSOR] < config.STOPCASETEMP || temp[OUTSENSOR] >= temp[INSENSOR])
    {
        output(inFan, 0);
        output(outFan, 0);
    }

    if (temp[PSUSENSOR] > config.STARTPSUTEMP && temp[INSENSOR] < temp[PSUSENSOR])
    {
        output(PSUFan, 1);
    }
    else if (temp[PSUSENSOR] < config.STOPPSUTEMP || temp[INSENSOR] >= temp[PSUSENSOR])
    {
        output(PSUFan, 0);
    }

    // check for extreme temperatures
    bool ok = true;
    for (byte i = 0; i < 3 && ok; i++)
    {
        if (temp[i] > config.STOPWORKINGTEMP)
        {
            ok = false;
        }
    }
    if (!ok)
    {
        raise(EXTREMEHOTTEMPERROR, String(F("Current temps are: ")) + String(temp[0]) + String(F(", ")) + String(temp[1]) + String(F(", ")) + String(temp[2]));
    }
}
#endif
/*------------Temp Control--------------*/

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

/*------------Voltage Control-----------*/

// used to scale any float value (Thales theorem)
float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// This function reads from a 0-25V DC sensor and returns its voltage
float voltRead()
{
    float f = fmap(analogRead(voltSensor), 0, 1023, 0.0, 25.0);   // read from sensor and adjust the scale to 0-25V
    return f - loadOffset();
}

// This function generates an offset to correctly measure real voltage under heavy loads
float loadOffset()
{
    float load = getDCAmps(200); // get current load
    //float formula = load * -0.65; // one big pump // 1.5A
    //float formula = load * -0.375; // two big pumps // 3A
    //float formula = load * -0.50; // 1 pump + UV // 2.5A
    //float formula = load * -0.80; // UV // 1A
    //float formula = load * -0.3; // 2 big pumps + UV // 4A
    //float formula = load * -0.20; // Filter // 5.4A
    //float formula = load * 0.00 - 1.00; // no load // 0A

    // Using some known pairs of current and difference from real to arduino measured voltage, here we used least square roots to approximate to the formula of a straight line
    float formula = -0.9487 - (0.0453 * load); // f(I)=-0.9487-0.0453*I
    return formula;
}

// This function maintains the voltage in the super-capacitors between STARTCHARGINGVOLTAGE and STOPCHARGINGVOLTAGE
// It MUST be called at least one time each 2 seconds
void voltControl()
{
    float voltage = voltRead();
    //debug(voltage);
    if (voltage < config.STARTCHARGINGVOLTAGE)
    {
        output(voltSSRelay, 1);
    }
    else if (voltage > config.STOPCHARGINGVOLTAGE)
    {
        output(voltSSRelay, 0);
    }
}

// This functions blocks the code execution until a certain voltage is reached inside the super-capacitors
void waitForVoltage(float volts)
{
    float voltage = voltRead();
#if OVERRRIDEMAXVOLTAGE
    voltage = volts + 1;
#endif
    if (voltage < volts)
    {
        output(voltSSRelay, 1);
        while (voltage < volts)
        {
            voltage = voltRead();
        }
        output(voltSSRelay, 0);
    }
}

/*------------Voltage Control-----------*/

/*------------Amperage Control----------*/

// This function returns the amperage of the main sensor
float getDCAmps(int samples)
{
    double sensorVolts;
    double current = 0;
    for (int i = 0; i < samples; i++)
    {
        sensorVolts = analogRead(mainAmpSensor) * (5.0 / 1023.0); // sensor reading
        current = current + (sensorVolts - config.DCAMMZERO) / config.DCAMMSENSITIVITY; // Process input to get Amperage
    }
    current = current / samples;
    return(current >= 0 ? (float)current : 0);
}

// This function uses all the data logged by logACAmps() and calculates an RMS Amperage value for the UV sensor
float getACAmps()
{
    double amps = config.ACAMMZERO + config.ACAMMSENSITIVITY * inputStats.sigma();
    return(amps >= 0 ? (float)amps : 0); // calculate RMS Amperage
}

// To measure AC current, arduino must log sensor data all the time. This function read and log one value per call
void logACAmps()
{
    inputStats.input(analogRead(UVAmpSensor));  // log to Stats function
}

/*------------Amperage Control----------*/

/*------------Error Control-------------*/

// This function will allow to notify the user about the error
// and redirect the execution to an "onlyVitalActivities" function if it is critical
// or resume the program if it is not
// This function is not completed yet
void raise(byte error, const String& possibleExplanation)
{
    bool critical = true;
    ledAnimation* prevAnimation = currentAnimation;
    setColor(RED);

    switch (error)
    {
#if GUI
        case SCREENNOTCONNECTEDERROR:
            critical = false;
            setColor(255, 30, 0); // orange
            break;
#endif
        default:
            currentAnimation = &defaultErrorAnimation;
            break;
    }

    if (critical)
    {
        disconnectEverything();
        delay(1000);
        voltControl();
#if DEBUG
        debug(F("RAISE --- CRITICAL Error "));debug(error);debug(F(": "));debug(possibleExplanation);debug('\n');
            delay(2000);
#endif

        unsigned long pm = millis();
        while (true)
        {
            if (pm + 1000 < millis())
            {
                voltControl();
                pm = millis();
            }
            updateAnimation();
        }
    }
    else
    {
#if DEBUG
        debug(F("RAISE --- CRITICAL Error "));debug(error);debug(F(": "));debug(possibleExplanation);debug('\n');
            delay(3000);
#endif
        switch (mode) // set back normal color
        {
            case TRANSITIONTOIDLE:
            case IDLE:
                setColor(UNDERVOLTAGECOLOR);
                break;
            default:
                setColor(WORKINGCOLOR);
        }
        currentAnimation = prevAnimation;
        voltControl();
    }
}

// This function will check for hardware errors on the system
void errorCheck()
{
    // Check for incongruent buoys
    if (!digitalRead(lowSurfaceBuoy) && digitalRead(highSurfaceBuoy))
    {
        raise(BUOYINCONGRUENCEERROR, F("An incongruence has been detected with either lowSurfaceBuoy or highSurfaceBuoy. Please check the connections to those sensors"));
    }
    if (!digitalRead(lowFilteredBuoy) && digitalRead(highFilteredBuoy))
    {
        raise(BUOYINCONGRUENCEERROR, F("An incongruence has been detected with either lowFilteredBuoy or highFilteredBuoy. Please check the connections to those sensors"));
    }
    if (!digitalRead(lowPurifiedBuoy) && digitalRead(highPurifiedBuoy))
    {
        raise(BUOYINCONGRUENCEERROR, F("An incongruence has been detected with either lowPurifiedBuoy or highPurifiedBuoy. Please check the connections to those sensors"));
    }

    // Check for pumps timeout
    if (pumpSt[0] && millis() > pumpPrevMillis[0] + config.WELLPUMPTIMEOUT)
    {
        raise(PUMPTIMEOUTERROR, String(F("Well pump has been working for more than ")) + String(config.WELLPUMPTIMEOUT) + String(F("ms. Either the pump doesn't work or there is a leakage in the well pump's circuit")));
    }
    if (pumpSt[1] && millis() > pumpPrevMillis[1] + config.UVPUMPTIMEOUT)
    {
        raise(PUMPTIMEOUTERROR, String(F("UV pump has been working for more than ")) + String(config.UVPUMPTIMEOUT) + String(F("ms. Either the pump doesn't work or there is a leakage in UV the pump's circuit")));
    }
    if (pumpSt[2] && millis() > pumpPrevMillis[2] + config.ENDPUMPTIMEOUT)
    {
        raise(PUMPTIMEOUTERROR, String(F("Well pump has been working for more than ")) + String(config.ENDPUMPTIMEOUT) + String(F("ms. Either the pump doesn't work or there is a leakage in the end pump's circuit")));
    }
    if (pumpSt[3] && millis() > pumpPrevMillis[3] + config.FILTERTIMEOUT)
    {
        raise(PUMPTIMEOUTERROR, String(F("Filter has been working for more than ")) + String(config.FILTERTIMEOUT) + String(F("ms. Either the filter doesn't work or there is a leakage in the filter's circuit")));
    }
}

// Quick shortcut to disconnect every pump or relay
void disconnectEverything()
{
    output(voltSSRelay, 0);
    output(voltRelay, 0);
    output(ACInverter, 0);
    output(wellPump, 0);
    output(UVPump, 0);
    output(endPump, 0);
    output(UVRelay, 0);
    output(filterRelay, 0);
    debug(F("DisconnectEverything - Done\n"));
}

/*------------Error Control-------------*/

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
            raise(SCREENNOTCONNECTEDERROR, F("Unable to communicate to the screen, double check the connections to it"));
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



// The setup() function runs once each time the micro-controller starts
// This function starts serial communication if defined, configures every input and output, set any other variable that needs to and waits for enough voltage in the capacitors to start operating
void purificationSetup()
{
    pinMode(redLed, OUTPUT);
    pinMode(blueLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    setColor(BOOTINGCOLOR);

#if TEMPERATURE
    sensors.begin();
    byte num = sensors.getDeviceCount();
    if (num != 3)
    {
        raise(TEMPSENSORSAMOUNTERROR, String(F("Setup - A different amount from 3 sensors were connected.\nNumber of sensors detected: "))+num);
    }
#endif

    pinMode(secBuoy, INPUT);
    pinMode(lowSurfaceBuoy, INPUT);
    pinMode(highSurfaceBuoy, INPUT);
    pinMode(lowFilteredBuoy, INPUT);
    pinMode(highFilteredBuoy, INPUT);
    pinMode(lowPurifiedBuoy, INPUT);
    pinMode(highPurifiedBuoy, INPUT);
    pinMode(endBuoy, INPUT);

    pinMode(voltSSRelay, OUTPUT);
    pinMode(voltRelay, OUTPUT);
    pinMode(ACInverter, OUTPUT);
    pinMode(wellPump, OUTPUT);
    pinMode(UVPump, OUTPUT);
    pinMode(endPump, OUTPUT);
    pinMode(UVRelay, OUTPUT);
    pinMode(filterRelay, OUTPUT);

    output(voltSSRelay, 0);
    output(voltRelay, 1);
    output(ACInverter, 0);
    output(wellPump, 0);
    output(UVPump, 0);
    output(endPump, 0);
    output(UVRelay, 0);
    output(filterRelay, 0);

#if TEMPERATURE
    pinMode(outFan, OUTPUT);
    pinMode(PSUFan, OUTPUT);
    pinMode(inFan, OUTPUT);
    output(outFan, 1);
    output(PSUFan, 1);
    output(inFan, 1);
#endif

    pinMode(screenSensor, INPUT_PULLUP);
    pinMode(screenRelay, OUTPUT);
    output(screenRelay, 0);

#if ONLYVITALACTIVITYALLOWED
    currentAnimation = &testAnimation;
#else
#if TEMPERATURE
    tempControl();
#endif
    debug(F("Setup - Waiting for "));debug(config.STARTCHARGINGVOLTAGE - 1);debug(F(" V\n"));
    waitForVoltage(config.STARTCHARGINGVOLTAGE - 1);
#endif
    output(voltRelay, 0);

    // put setup code after this line

    inputStats.setWindowSecs(40.0F / config.ACFREQUENCY);     //Set AC Ammeter frequency

    mode = 0;
    debug(F("Setup - Ready\n"));
}

// Add the main program code into the continuous loop() function
// This function does things :D TODO make description
void purificationLoop()
{
    voltControl();
    logACAmps();

#if !ONLYVITALACTIVITYALLOWED
    errorCheck();
#endif

    updateAnimation();

#if TEMPERATURE
    if (millis() > tempMillis + config.TEMPCHECKTIME)
        {
            tempControl();
            tempMillis = millis();
        }
#endif

#if !ONLYVITALACTIVITYALLOWED
    switch (mode)
    {
        case TRANSITIONTOIDLE: // Transition to OFF
            output(wellPump, 0);
            output(endPump, 0);
            output(UVPump, 0);
            output(filterRelay, 0);
            output(ACInverter, 0);
            delay(1000);
            output(UVRelay, 0);
            output(voltSSRelay, 1);
            setColor(UNDERVOLTAGECOLOR);
            for (byte i = 0; i < 3; i++)
            {
                pumpSt[i] = false;
            }
            mode = IDLE;
            break;

        case IDLE: // OFF
#if !OVERRRIDEMAXVOLTAGE
            if (voltRead() > config.STARTWORKINGVOLTAGE)
#endif
                mode = TRANSITIONTOPUMPSWORKING;
            break;

        case TRANSITIONTOPUMPSWORKING: // Transition to Pumps Working
            output(ACInverter, 0);
            setColor(WORKINGCOLOR);
            for (byte i = 0; i < 3; i++)
            {
                pumpSt[i] = false;
            }
            mode = PUMPSWORKING;
            break;

        case PUMPSWORKING: // Pumps Working
#if !OVERRRIDEMAXVOLTAGE
            if (voltRead() < config.STOPWORKINGVOLTAGE)
                mode = TRANSITIONTOIDLE;
#endif

            if (!pumpSt[0] && !digitalRead(highSurfaceBuoy) && digitalRead(secBuoy))
            {
                output(wellPump, 1);
                pumpPrevMillis[0] = millis();
                pumpSt[0] = true;
            }


            if (pumpSt[0] && (digitalRead(highSurfaceBuoy) || !digitalRead(secBuoy)))
            {
                output(wellPump, 0);
                pumpSt[0] = false;
            }


            if (!digitalRead(lowFilteredBuoy) && digitalRead(highSurfaceBuoy))
                mode = TRANSITIONTOFILTERWORKING;

            if (!pumpSt[1] && !digitalRead(highPurifiedBuoy) && digitalRead(lowFilteredBuoy))
            {
                output(ACInverter, 1);
                delay(250);
                output(UVRelay, 1);

                // check if UV is working
                for (int i = 0; i < 100; i++)
                {
                    logACAmps();
                    delay(10);
                }
                float amps = getACAmps();

                if (amps < config.ESTIMATEDUVAMPERAGE)
                {
                    raise(UVLIGHTNOTWORKINGERROR, String(F("The UV amperage sensor detected "))+String(amps)+String(F("A. The UV light must be either broken or disconnected. Check the connections and if it persists, replace the UV light")));
                }

                pumpPrevMillis[1] = millis();
                UVMillis = pumpPrevMillis[1];
                output(UVPump, 1);
                pumpSt[1] = true;
            }
            if (pumpSt[1]) // if UV is on and each 800ms
            {
                workingTime += millis() - UVMillis; // Add this time to workingTime
                purifiedWater = (workingTime * config.UVPUMPFLOW) / 3600000.00; // calculate the amount of purified water
                UVMillis = millis();
            }

            if (pumpSt[1] && (!digitalRead(lowFilteredBuoy) || digitalRead(highPurifiedBuoy)))
            {
                output(UVPump, 0);
                workingTime += millis() - UVMillis; // Add this time to workingTime
                purifiedWater = (workingTime * config.UVPUMPFLOW) / 3600000.00; // calculate the amount of purified water
                delay(1000);
                output(UVRelay, 0);
                delay(250);
                output(ACInverter, 0);
                pumpSt[1] = false;
            }

            if (!pumpSt[2] && !digitalRead(endBuoy) && digitalRead(lowPurifiedBuoy))
            {
                output(endPump, 1);
                pumpPrevMillis[2] = millis();
                pumpSt[2] = true;
            }

            if (pumpSt[2] && (!digitalRead(lowPurifiedBuoy) || digitalRead(endBuoy)))
            {
                output(endPump, 0);
                pumpSt[2] = false;
            }

            break;

        case TRANSITIONTOFILTERWORKING: // Transition to filter working
            output(wellPump, 0);
            output(endPump, 0);
            output(UVPump, 0);

            output(ACInverter, 1);
            delay(1000);
            output(UVRelay, 0);
#if !OVERRRIDEMAXVOLTAGE
            if (voltRead() < config.STOPWORKINGVOLTAGE)
                mode = TRANSITIONTOIDLE;
#endif

            waitForVoltage(config.STARTWORKINGVOLTAGE);
            pumpSt[3] = true;
            pumpPrevMillis[3] = millis();
            output(filterRelay, 1);

            mode = FILTERWORKING;
            break;

        case FILTERWORKING: // Filter Working
#if !OVERRRIDEMAXVOLTAGE
            if (voltRead() < config.STOPWORKINGVOLTAGE)
                mode = TRANSITIONTOIDLE;
#endif

            if (digitalRead(highFilteredBuoy) || !digitalRead(lowSurfaceBuoy))
            {
                output(filterRelay, 0);
                pumpSt[3] = false;
                mode = TRANSITIONTOPUMPSWORKING;
            }
            break;
    }
#endif
}
