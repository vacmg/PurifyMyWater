//
// Created by jst83 on 22/09/2022.
//

#ifndef H2O_GUI_CALIBRATION_H
#define H2O_GUI_CALIBRATION_H

#include "Interface.h"
void loadScreenCalibrationStartup();
void show_string(uint8_t *str,int16_t x,int16_t y,uint8_t csize,uint16_t fc, uint16_t bc,boolean mode);
void Read_Resistive(void);
bool is_pressed(void);
void drawCrossHair(int x, int y, unsigned int color);
void readCoordinates();
void calibrate(int x, int y, int i);
void clickCalibrationScreen();
void showNumI(char *msg, uint32_t val, int x, int y);
void done();
void fail();
void loopCalibration();

#include "Calibration.cpp"

#endif //H2O_GUI_CALIBRATION_H
