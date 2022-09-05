//
// Created by Victor on 05/08/2022.
//

#ifndef H2O_MASTER_PURIFICATION_H
#define H2O_MASTER_PURIFICATION_H

#include <Arduino.h>
#include "Core/Core.h"

// This is the purification setup code, which sets the system to a well known status to start with the purification
void purificationSetup();

// This is the purification loop code, which holds the purification algorithm
void purificationLoop();

#include "Purification.cpp"

#endif //H2O_MASTER_PURIFICATION_H
