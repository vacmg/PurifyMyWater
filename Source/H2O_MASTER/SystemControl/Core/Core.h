//
// Created by Victor on 07/08/2022.
//

#ifndef H2O_MASTER_CORE_H
#define H2O_MASTER_CORE_H

#include "../../Shared/SharedData.h"

enum PurificationStatus
{
    TRANSITIONTOIDLE,
    IDLE,
    TRANSITIONTOPUMPSWORKING,
    PUMPSWORKING,
    TRANSITIONTOFILTERWORKING,
    FILTERWORKING
};

enum PurificationStatus purificationStatus = TRANSITIONTOIDLE; // Purification current status is changed using this variable
unsigned long UVMillis = 0;
unsigned long workingTime = 0; // Time that UV pump is working (in ms) // Used to calculate the amount of purified water

#include "IO.h"
#include "Electricity.h"

// This is the core setup code, which no matter which module is enabled, those instructions must be executed
void coreSetup();

// This is the core loop code, which no matter which module is enabled, those instructions must be executed every main loop execution
void coreLoop();

// Quick shortcut to disconnect every pump or relay
void disconnectEverything();

// This function will check for hardware errors on the system
void errorCheck();

// This function will allow to notify the user about the error
// and redirect the execution to an "onlyVitalActivities" function if it is critical
// or resume the program if it is not
// This function is not completed yet
void raise(enum Errors error, const String& possibleExplanation);

#include "Core.cpp"

#endif //H2O_MASTER_CORE_H
