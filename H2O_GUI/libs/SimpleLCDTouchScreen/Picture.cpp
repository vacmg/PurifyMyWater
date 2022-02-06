//
// Created by Víctor on 29/09/2021.
//

#include "Picture.h"

Picture::Picture(): ScreenObjectWithXtraCoords(0,0,0,0, Color(0,0,0)), ScreenObject(0, 0, Color(0,0,0))
{
    this->picturePath = nullptr;
    this->bmpOffset = 0;
    this->bmpWidth = 0;
    this->bmpHeight = 0;
    this->ignoreBytes = 0;
    this->readyToUse = false;
}

Picture::Picture(int x, int y, char *picturePath): ScreenObjectWithXtraCoords(x,y,x,y, Color(0,0,0)), ScreenObject(x, y, Color(0,0,0))
{
    this->picturePath = picturePath;
    this->bmpOffset = 0;
    this->bmpWidth = 0;
    this->bmpHeight = 0;
    this->ignoreBytes = 0;
    this->readyToUse = false;
}

Picture::Picture(int x, int y, char *picturePath, Color mainColor): ScreenObject(x, y, mainColor)
{
    this->picturePath = picturePath;
    this->bmpOffset = 0;
    this->bmpWidth = 0;
    this->bmpHeight = 0;
    this->ignoreBytes = 0;
    this->readyToUse = false;
}

char* Picture::getPicturePath()
{
    return picturePath;
}

bool Picture::setPicturePath(char *picturePath)
{
    this->picturePath = picturePath;
    return init();
}

// Call it before accessing any of its members
bool Picture::init()
{
    if(!readyToUse)
        readyToUse = bmpHeaderAnalysis();
    return readyToUse;
}

bool Picture::bmpHeaderAnalysis()
{
    if(picturePath == nullptr)
        return false;
    File file = SD.open(picturePath,FILE_READ);
    if(!file)
        return false;
    if(read_16(file) != 0x4D42) // If it's not a .bmp file return false
    {
        return false;
    }
    //get bpm size
    read_32(file);
    //get creator information
    read_32(file);
    //get offset information
    bmpOffset = read_32(file);
    //get DIB information
    read_32(file);
    //get width and height information
    bmpWidth = read_32(file);
    bmpHeight = read_32(file);
    if(read_16(file) != 1)
    {
        return false;
    }
    read_16(file);
    if(read_32(file) != 0)
    {
        return false;
    }
    ignoreBytes = (4 - ((bmpWidth * 3) % 4)) % 4;
    file.close();
    this->setCoords1(bmpWidth+getx(), bmpHeight+gety());
    return true;
}

uint16_t Picture::read_16(File file)
{
    uint8_t low;
    uint16_t high;
    low = file.read();
    high = file.read();
    return (high<<8)|low;
}

uint32_t Picture::read_32(File file)
{
    uint16_t low;
    uint32_t high;
    low = read_16(file);
    high = read_16(file);
    return (high<<8)|low;
}

uint32_t Picture::getBmpOffset()
{
    if(bmpOffset==0)
        bmpHeaderAnalysis();
    return bmpOffset;
}

uint32_t Picture::getBmpWidth()
{
    if(bmpWidth==0)
        init();
    return bmpWidth;
}

uint32_t Picture::getBmpHeight()
{
    if(bmpHeight==0)
        init();
    return bmpHeight;
}

uint32_t Picture::getIgnoreBytes()
{
    if(ignoreBytes==0)
        init();
    return ignoreBytes;
}

bool Picture::isReadyToUse()
{
    return readyToUse;
}
