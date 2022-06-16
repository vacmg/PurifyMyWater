//
// Created by Víctor on 16/06/2022.
//

#ifndef H2O_GUI_H2O_UI_H
#define H2O_GUI_H2O_UI_H

#ifndef H2O_GUI // H2O_GUI ID for shared files // todo check if it is necessary
    #define H2O_GUI true
#endif

#include <Arduino.h>
#include <LCDWIKI_KBV.h>
#include <LCDWIKI_GUI.h>
#include <TouchScreen.h>
#include <SimpleLCDTouchScreen.h>

#include "sharedData.h" // todo mirar si va aqui o va en el .ino
#include "Core/Core.h"
#include "Screens/Screens.h"

#ifndef DEBUG
    #define DEBUG true
#endif
#define SCREENHW 35 // 35 --> 3.5INCH / 39 --> 3.95INCH

enum ScreenStatus {BOOTING = 0, LOADSTATUS, STATUS, LOADMENU, MENU, LOADSETTINGS, SETTINGS, LOADHELP, HELP, LOADENGINEERINGMODE, ENGINEERINGMODE, LOADEXTRAFUNCTIONS, EXTRAFUNCTIONS, LOADELECTRICITY, LOADPAGEELECTRICITY, ELECTRICITY, LOADINTERFACE, LOADPAGEINTERFACE, INTERFACE, LOADWATER, LOADPAGEWATER, WATER, LOADTEMPERATURE, LOADPAGETEMPERATURE, TEMPERATURE};
// ON/OFF BTN STATUS
enum BtnStatus {OFF, ON, ERROR};

BtnStatus mainSwitchSt = OFF;
ScreenStatus screenStatus = BOOTING; // Must be initialized to BOOTING in order to show splash screen
byte ROTATION = 1;

#if SCREENHW == 35
#define SCREEN35ROTATIONOFFSET 2
TouchScreenObject ts(9,A2,A3,8,300,320,480,(ROTATION+SCREEN35ROTATIONOFFSET)%4,177,900,157,958); // for 3.5inch
#elif SCREENHW == 39
TouchScreenObject ts(8,A3,A2,9,300,320,480,ROTATION,924,111,58,935); // rx is the resistance between X+ and X- Use any multimeter to read it or leave it blanc
#endif

//Global Variables
char auxBuffer[32] = ""; // TODO when using progmem, use it as a buffer to print each label

byte page = 0;
byte maxPage = 0;

SimpleLCDTouchScreen my_lcd(ST7796S, A3, A2, A1, A0, A4); //model,cs,cd,wr,rd,reset

Label label(200,10,"Menu",3,Color(0,0,0)); //general label
Rectangle rectangle(300,234,420,290, Color(0,0,0), Color(255,255,255),&label);

//Rectangle Buttons
RectangleButton btn1(30,120,230,200,Color(0,0,0),Color(255,255,255),&label,&ts); // todo disable autosize & enable again in the cases that is needed
RectangleButton btn2(250,120,440,200,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton btn3(30,220,230,300,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton btn4(250,220,440,300,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton btn5(30,220,230,300,Color(0,0,0),Color(255,255,255),&label, &ts);
RectangleButton btn6(250,220,440,300,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton btn7(250,220,440,300,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton btn8(30,220,230,300,Color(0,0,0),Color(255,255,255),&label,&ts);

//Rectangle Button Help
RectangleButton btn9(250,220,440,300,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton btn10(30,220,230,300,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton btn11(250,220,440,300,Color(0,0,0),Color(255,255,255),&label,&ts);

// Frequently used ScreenObjects
RectangleButton backBtn(20,20,60,60,Color(0,0,0),Color(255,255,255),&label,&ts);
Label titleLabel(0,0,"Menu",5,Color(0),Color(255,255,255));
Rectangle title(65,5,415,75,Color(0xFFFF),/*Color(255,0,0),*/&titleLabel,true);

//Rectangle Button GetNumInput
RectangleButton oKBtn(250,270,410,310,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton dotBtn(425,95,475,145,Color(0,0,0),Color(255,255,255),&label,true,&ts);
RectangleButton signBtn(5,95,55,145,Color(0,0,0),Color(255,255,255),&label,&ts);
//Global Variables End

bool sw = true; // todo delete this
void UISetup();
void UI();


#endif //H2O_GUI_H2O_UI_H
