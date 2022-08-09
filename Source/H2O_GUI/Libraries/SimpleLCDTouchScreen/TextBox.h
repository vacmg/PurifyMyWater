//
// Created by Víctor on 10/04/2022.
//

#ifndef SIMPLELCDTOUCHSCREEN_TEXTBOX_H
#define SIMPLELCDTOUCHSCREEN_TEXTBOX_H
#include "ScreenObjectWithXtraCoords.h"
#include "ScreenObjectWithRectangle.h"
#include "ScreenObjectWithSecondaryColor.h"
#include "ScreenObjectWithLabel.h"
#include "Rectangle.h"
#include "RoundRectangle.h"

#include <SD.h>

class TextBox: virtual public ScreenObjectWithXtraCoords, virtual public ScreenObjectWithRectangle, virtual public ScreenObjectWithLabel
{
public:
    TextBox(int x, int y, int x1, int y1, const char* textPath, Rectangle* frame, Label* label);
    TextBox(int x, int y, int x1, int y1, const char* textPath, byte spacing, Rectangle* frame, Label* label);
    TextBox(int x, int y, int x1, int y1, const char* textPath, byte spacing, uint16_t marginX, uint16_t marginY, Rectangle* frame, Label *label);
    TextBox(int x, int y, int x1, int y1, const char* textPath, Rectangle* frame, Label* label, uint32_t beginOffset, uint32_t endOffset);
    TextBox(int x, int y, int x1, int y1, const char* textPath, byte spacing, Rectangle* frame, Label* label, uint32_t beginOffset, uint32_t endOffset);
    TextBox(int x, int y, int x1, int y1, const char* textPath, byte spacing, uint16_t marginX, uint16_t marginY, Rectangle* frame, Label *label, uint32_t beginOffset, uint32_t endOffset);

    TextBox(int x, int y, int x1, int y1, const char* textPath, Label* label);
    TextBox(int x, int y, int x1, int y1, const char* textPath, byte spacing, Label* label);
    TextBox(int x, int y, int x1, int y1, const char* textPath, byte spacing, uint16_t marginX, uint16_t marginY, Label *label);
    TextBox(int x, int y, int x1, int y1, const char* textPath, Label* label, uint32_t beginOffset, uint32_t endOffset);
    TextBox(int x, int y, int x1, int y1, const char* textPath, byte spacing, Label* label, uint32_t beginOffset, uint32_t endOffset);
    TextBox(int x, int y, int x1, int y1, const char* textPath, byte spacing, uint16_t marginX, uint16_t marginY, Label *label, uint32_t beginOffset, uint32_t endOffset);

    char* nextWord(File* file, uint32_t start, uint32_t end, uint32_t* length);
    bool printAsDrawn(HardwareSerial* serial, uint8_t font);
    bool printAsDrawn(HardwareSerial* serial);
    bool printAll(HardwareSerial* serial);
    bool print(HardwareSerial* serial);
    bool init();
    uint16_t maxAmountOfRows(uint16_t ypx,byte font);
    uint16_t charactersPerRow(uint16_t xpx, byte font);
    const char* getTextPath();
    uint16_t getSpacing();
    uint16_t getMarginX();
    uint16_t getMarginY();
    uint8_t getFontSize();
    uint32_t getBeginOffset();
    uint32_t getEndOffset();
    Label* getLabel();
    Rectangle* getFrame();
    void setSpacing(uint16_t spacing);
    void setMarginX(uint16_t marginX);
    void setMarginY(uint16_t marginY);
    void setCoords(int x, int y);
    void setCoords1(int x1, int y1);
    bool canBeDrawn();

private:
    bool checkIfFileExists();
    uint8_t calculateFontSize();
    const char* textPath;
    uint32_t beginOffset;
    uint32_t endOffset;
    uint16_t spacing;
    uint16_t marginX;
    uint16_t marginY;

    uint8_t fontSize; // 0 if invalid
    bool validFile;
};


#endif //SIMPLELCDTOUCHSCREEN_TEXTBOX_H
