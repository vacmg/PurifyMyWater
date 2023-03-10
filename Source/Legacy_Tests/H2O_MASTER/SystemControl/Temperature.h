//
// Created by Victor on 07/08/2022.
//

#ifndef H2O_MASTER_TEMPERATURE_H
#define H2O_MASTER_TEMPERATURE_H

#include "Core/Core.h"
#include <OneWire.h>
#include <DallasTemperature.h>

unsigned long tempMillis = 0;
// Set up a oneWire instance to communicate with any OneWire device
OneWire oneWire(tempPin);
// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

enum TempSensors {OUTSENSOR=0,PSUSENSOR=1,INSENSOR=2};

// Used to control the temperature of the main control unit
void tempControl();

// Used to get temperature in celsius of the 3 temperature sensors
// It modifies the given array that MUST be of length 3
void getSensorsTemp(float* temp);

// This is the temperature setup code, which initializes all the objects needed to measure & control the system temperature
void tempSetup();

// This is the temperature loop code, which handles all the instructions needed to measure & control the system temperature
void tempLoop();

#include "Temperature.cpp"

#endif //H2O_MASTER_TEMPERATURE_H
