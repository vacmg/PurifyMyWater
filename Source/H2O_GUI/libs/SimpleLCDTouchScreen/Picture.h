//
// Created by Víctor on 29/09/2021.
//

#ifndef SIMPLELCDTOUCHSCREEN_PICTURE_H
#define SIMPLELCDTOUCHSCREEN_PICTURE_H
#include <Arduino.h>
#include <SD.h>
//#include <SD/src/SD.h>
#include <SPI.h>
#include "ScreenObject.h"
#include "ScreenObjectWithXtraCoords.h"

class Picture: virtual public ScreenObjectWithXtraCoords, virtual public ScreenObject
{
public:
    Picture(int x, int y, char* picturePath);
    Picture(int x, int y, char* picturePath, Color mainColor);
    Picture();
    char* getPicturePath();
    bool setPicturePath(char* picturePath);
    bool init();
    uint32_t getBmpOffset();
    uint32_t getBmpWidth();
    uint32_t getBmpHeight();
    uint32_t getIgnoreBytes();
    bool isReadyToUse();
    void setCoords(int x, int y);
    int getx1();
    int gety1();

private:
    bool bmpHeaderAnalysis();
    uint32_t read_32(File file);
    uint16_t read_16(File file);
    bool readyToUse;
    char* picturePath;
    uint32_t bmpOffset;
    uint32_t bmpWidth;
    uint32_t bmpHeight;
    uint32_t ignoreBytes;

};


#endif //SIMPLELCDTOUCHSCREEN_PICTURE_H
