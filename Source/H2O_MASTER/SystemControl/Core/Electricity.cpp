//
// Created by Victor on 07/08/2022.
//

#include "Electricity.h"

/*------------Voltage Control-----------*/

// This function is used to scale any float value (Thales theorem)
float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// This function reads from a 0-25V DC sensor and returns its voltage
float voltRead()
{
    float f = fmap(analogRead(voltSensor), 0, 1023, 0.0, 25.0);   // read from sensor and adjust the scale to 0-25V
    dataStorage.data.voltage = f - loadOffset();
    return dataStorage.data.voltage;
}

// This function generates an offset to correctly measure real voltage under heavy loads
float loadOffset()
{
    dataStorage.data.DCAmps = getDCAmps(200); // get current load
    //float formula = load * -0.65; // one big pump // 1.5A
    //float formula = load * -0.375; // two big pumps // 3A
    //float formula = load * -0.50; // 1 pump + UV // 2.5A
    //float formula = load * -0.80; // UV // 1A
    //float formula = load * -0.3; // 2 big pumps + UV // 4A
    //float formula = load * -0.20; // Filter // 5.4A
    //float formula = load * 0.00 - 1.00; // no load // 0A

    // Using some known pairs of current and difference from real to arduino measured voltage, here we used least square roots to approximate to the formula of a straight line
    float formula = -0.9487F - (0.0453F * dataStorage.data.DCAmps); // f(I)=-0.9487-0.0453*I
    return formula;
}

// This function maintains the voltage in the super-capacitors between STARTCHARGINGVOLTAGE and STOPCHARGINGVOLTAGE
// It MUST be called at least one time each 2 seconds
void voltControl()
{
    voltRead();
    //debug(voltage);
    if (dataStorage.data.voltage < configStorage.config.STARTCHARGINGVOLTAGE)
    {
        output(voltSSRelay, 1);
    }
    else if (dataStorage.data.voltage > configStorage.config.STOPCHARGINGVOLTAGE)
    {
        output(voltSSRelay, 0);
    }
}

// This functions blocks the code execution until a certain voltage is reached inside the super-capacitors
void waitForVoltage(float volts)
{
    voltRead();
#if OVERRRIDEMAXVOLTAGE
    dataStorage.data.voltage = volts + 1;
#endif
    if (dataStorage.data.voltage < volts)
    {
        output(voltSSRelay, 1);
        while (dataStorage.data.voltage < volts)
        {
            voltRead();
        }
        output(voltSSRelay, 0);
    }
#if OVERRRIDEMAXVOLTAGE
    voltRead();
#endif
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
        current = current + (sensorVolts - configStorage.config.DCAMMZERO) / configStorage.config.DCAMMSENSITIVITY; // Process input to get Amperage
    }
    current = current / samples;
    return(current >= 0 ? (float)current : 0);
}

// This function uses all the data logged by logACAmps() and calculates an RMS Amperage value for the UV sensor
float getACAmps()
{
    double amps = configStorage.config.ACAMMZERO + configStorage.config.ACAMMSENSITIVITY * inputStats.sigma();
    return(amps >= 0 ? (float)amps : 0); // calculate RMS Amperage
}

// To measure AC current, arduino must log sensor data all the time. This function read and log one value per call
void logACAmps()
{
    inputStats.input(analogRead(UVAmpSensor));  // log to Stats function
}

/*------------Amperage Control----------*/
