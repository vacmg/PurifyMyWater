//
// Created by Víctor on 13/09/2021.
//

#ifndef SIMPLELCDTOUCHSCREEN_COLOR_H
#define SIMPLELCDTOUCHSCREEN_COLOR_H

#include <Arduino.h>

class Color
{
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    Color()
    {
        r = 0;
        g = 0;
        b = 0;
    }
    Color(uint8_t r, uint8_t g, uint8_t b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    explicit Color(uint16_t rgb565)
    {
        unsigned int r5,g6,b5;
        r5 = (rgb565&0xF800)>>11;
        g6 = (rgb565&0x7E0)>>5;
        b5 = (rgb565&0x1F);
        r = ( r5 * 527 + 23 ) >> 6;
        g = ( g6 * 259 + 33 ) >> 6;
        b = ( b5 * 527 + 23 ) >> 6;
    }

    uint16_t to565() const
    {
        return ((r & 0xf8)<<8) + ((g & 0xfc)<<3)+(b>>3);
    }
};


#endif //SIMPLELCDTOUCHSCREEN_COLOR_H
