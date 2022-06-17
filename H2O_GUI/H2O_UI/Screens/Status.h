//
// Created by Víctor on 16/06/2022.
//

#ifndef H2O_GUI_STATUS_H
#define H2O_GUI_STATUS_H

#include "Screens.h"


extern void drawStatusBackgroundPhoto();
extern void drawStatusBackground(bool dontFillScreen);
extern void drawStatusBackground();
extern void drawStatusForeground(const char* voltage, const char* waterAmount); // TODO add water levels & other indicators
extern void drawStatusColors(bool wellPump, bool endPump, bool UVRelay, bool filterRelay, char well, char surfaceTank, char filteredTank, char purifiedTank, bool endTank); // false --> OFF, true -->ON, <0 --> LOW, = 0 --> Half, >0 --> FULL
extern void clickStatus();

#endif //H2O_GUI_STATUS_H
