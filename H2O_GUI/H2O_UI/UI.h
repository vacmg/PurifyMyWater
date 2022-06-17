//
// Created by Víctor on 16/06/2022.
//

#ifndef H2O_GUI_UI_H
#define H2O_GUI_UI_H

#ifndef H2O_GUI // H2O_GUI ID for shared files // todo check if it is necessary
    #define H2O_GUI true
#endif

#include <Arduino.h>
#include <LCDWIKI_KBV.h>
#include <LCDWIKI_GUI.h>
#include <TouchScreen.h>
#include <SimpleLCDTouchScreen.h>

#include "sharedData.h"
#include "Core/Core.h"
#include "Screens/Screens.h"

#define SCREENHW 35 // 35 --> 3.5INCH / 39 --> 3.95INCH

#if SCREENHW == 35
    #define SCREEN35ROTATIONOFFSET 2
#endif

#if DEBUG
    extern const char *const modeTable[];
    extern char printModeBuff[20]; // Max size of any modeX string
    extern char* modeToString(ScreenStatus status);
#endif // H20_GUI ONLY

enum ScreenStatus {BOOTING = 0, LOADSTATUS, STATUS, LOADMENU, MENU, LOADSETTINGS, SETTINGS, LOADHELP, HELP, LOADENGINEERINGMODE, ENGINEERINGMODE, LOADEXTRAFUNCTIONS, EXTRAFUNCTIONS, LOADELECTRICITY, LOADPAGEELECTRICITY, ELECTRICITY, LOADINTERFACE, LOADPAGEINTERFACE, INTERFACE, LOADWATER, LOADPAGEWATER, WATER, LOADTEMPERATURE, LOADPAGETEMPERATURE, TEMPERATURE};
// ON/OFF BTN STATUS
enum BtnStatus {OFF, ON, ERROR};

extern BtnStatus mainSwitchSt;
extern ScreenStatus screenStatus; // Must be initialized to BOOTING in order to show splash screen
extern byte ROTATION;

extern TouchScreenObject ts;

//Global Variables
extern char auxBuffer[32]; // TODO when using progmem, use it as a buffer to print each label

extern byte page;
extern byte maxPage;

extern SimpleLCDTouchScreen my_lcd; //model,cs,cd,wr,rd,reset

extern Label label; //general label
extern Rectangle rectangle;

//Rectangle Buttons
extern RectangleButton btn1;
extern RectangleButton btn2;
extern RectangleButton btn3;
extern RectangleButton btn4;
extern RectangleButton btn5;
extern RectangleButton btn6;
extern RectangleButton btn7;
extern RectangleButton btn8;

//Rectangle Button Help
extern RectangleButton btn9;
extern RectangleButton btn10;
extern RectangleButton btn11;

// Frequently used ScreenObjects
extern RectangleButton backBtn;
extern Label titleLabel;
extern Rectangle title;

//Rectangle Button GetNumInput
extern RectangleButton oKBtn;
extern RectangleButton dotBtn;
extern RectangleButton signBtn;
//Global Variables End

extern bool sw; // todo delete this
extern void UISetup();
extern void UI();


#endif //H2O_GUI_UI_H
