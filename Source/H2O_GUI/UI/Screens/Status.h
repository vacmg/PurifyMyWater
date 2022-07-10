//
// Created by Víctor on 16/06/2022.
//

#ifndef H2O_GUI_STATUS_H
#define H2O_GUI_STATUS_H

#include "Screens.h"

void drawStatusBackgroundPhoto();
void drawStatusBackground(bool dontFillScreen);
void drawStatusBackground();
void drawStatusForeground(const char* voltage, const char* waterAmount);
void drawStatusColors(bool wellPump, bool endPump, bool UVRelay, bool filterRelay, char well, char surfaceTank, char filteredTank, char purifiedTank, bool endTank); // false --> OFF, true -->ON, <0 --> LOW, = 0 --> Half, >0 --> FULL
void clickStatus();

#include "Status.cpp"

#endif //H2O_GUI_STATUS_H
