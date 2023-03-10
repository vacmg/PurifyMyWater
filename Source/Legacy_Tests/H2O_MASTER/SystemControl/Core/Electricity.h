//
// Created by Victor on 07/08/2022.
//

#ifndef H2O_MASTER_ELECTRICITY_H
#define H2O_MASTER_ELECTRICITY_H

#include "Core.h"
#include <Filters.h>

const byte voltSensor = A0;
const byte mainAmpSensor = A1;
const byte UVAmpSensor = A2;

RunningStatistics inputStats; // create statistics to look at the raw test signal

// To measure AC current, arduino must log sensor data all the time. This function read and log one value per call
void logACAmps();

// This function uses all the data logged by logACAmps() and calculates an RMS Amperage value for the UV sensor
float getACAmps();

// This function returns the amperage of the main sensor
float getDCAmps(int samples);

// This functions blocks the code execution until a certain voltage is reached inside the super-capacitors
void waitForVoltage(float volts);

// This function maintains the voltage in the super-capacitors between STARTCHARGINGVOLTAGE and STOPCHARGINGVOLTAGE
// It MUST be called at least one time each 2 seconds
void voltControl();

// This function generates an offset to correctly measure real voltage under heavy loads
float loadOffset();

// This function reads from a 0-25V DC sensor and returns its voltage
float voltRead();

// This function is used to scale any float value (Thales theorem)
float fmap(float x, float in_min, float in_max, float out_min, float out_max);

#include "Electricity.cpp"

#endif //H2O_MASTER_ELECTRICITY_H
