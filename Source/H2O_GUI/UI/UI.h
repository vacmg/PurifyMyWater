//
// Created by Víctor on 16/06/2022.
//

#include <Arduino.h>
#include <LCDWIKI_KBV.h>
#include <LCDWIKI_GUI.h>
#include <TouchScreen.h>
#include <SimpleLCDTouchScreen.h>

#ifndef H2O_GUI_UI_H
#define H2O_GUI_UI_H

#ifndef H2O_GUI // H2O_GUI ID for shared files // todo check if it is necessary
    #define H2O_GUI true
#endif

#include "../Shared/SharedData.h"

#define SCREENHW 35 // 35 --> 3.5INCH / 39 --> 3.95INCH

#if SCREENHW == 35
#define SCREEN35ROTATIONOFFSET 2
#endif

    enum ScreenStatus {
        BOOTING = 0,
        LOADSTATUS,
        STATUS,
        LOADMENU,
        MENU,
        LOADSETTINGS,
        SETTINGS,
        LOADHELP,
        HELP,
        LOADENGINEERINGMODE,
        ENGINEERINGMODE,
        LOADEXTRAFUNCTIONS,
        EXTRAFUNCTIONS,
        LOADELECTRICITY,
        LOADPAGEELECTRICITY,
        ELECTRICITY,
        LOADINTERFACE,
        LOADPAGEINTERFACE,
        INTERFACE,
        LOADWATER,
        LOADPAGEWATER,
        WATER,
        LOADTEMPERATURE,
        LOADPAGETEMPERATURE,
        TEMPERATURE
    };

enum ScreenStatus screenStatus = BOOTING; // Must be initialized to BOOTING in order to show splash screen
enum Rotation {LANDSCAPE = 1, INVERTED_LANDSCAPE = 3};
enum Rotation ROTATION = LANDSCAPE; // Set rotation of the screen

enum Languages {ENGLISH = 0};
enum Languages LANGUAGE = ENGLISH;
unsigned long DATAREFRESHPERIOD = 5000; // Stored in ms, input in s (1s = 1000ms) // 0 < DATAREFRESHPERIOD

#if SCREENHW == 35
TouchScreenObject ts(9, A2, A3, 8, 300, 320, 480, (ROTATION + SCREEN35ROTATIONOFFSET) % 4, 177, 900, 157,
                     958); // for 3.5inch
#elif SCREENHW == 39
TouchScreenObject ts(8,A3,A2,9,300,320,480,ROTATION,924,111,58,935); // rx is the resistance between X+ and X- Use any multimeter to read it or leave it blanc
#endif

#if DEBUG

#define changeScreenStatus(newStatus) debug(F("screenStatus changed from '"));debug(modeToString(screenStatus));debug(F("' to '"));debug(modeToString(newStatus));debug(F("'\n")); screenStatus = newStatus

const char mode0[] PROGMEM = "BOOTING"; // in order (BOOTING = 0 ---> mode0 = "BOOTING" --> modeTable[0] = mode0)
const char mode1[] PROGMEM = "LOADSTATUS";
const char mode2[] PROGMEM = "STATUS";
const char mode3[] PROGMEM = "LOADMENU";
const char mode4[] PROGMEM = "MENU";
const char mode5[] PROGMEM = "LOADSETTINGS";
const char mode6[] PROGMEM = "SETTINGS";
const char mode7[] PROGMEM = "LOADHELP";
const char mode8[] PROGMEM = "HELP";
const char mode9[] PROGMEM = "LOADENGINEERINGMODE";
const char mode10[] PROGMEM = "ENGINEERINGMODE";
const char mode11[] PROGMEM = "LOADEXTRAFUNCTIONS";
const char mode12[] PROGMEM = "EXTRAFUNCTIONS";
const char mode13[] PROGMEM = "LOADELECTRICTY";
const char mode14[] PROGMEM = "LOADPAGEELECTRICITY";
const char mode15[] PROGMEM = "ELECTRICITY";
const char mode16[] PROGMEM = "LOADINTERFACE";
const char mode17[] PROGMEM = "LOADPAGEINTERFACE";
const char mode18[] PROGMEM = "INTERFACE";
const char mode19[] PROGMEM = "LOADWATER";
const char mode20[] PROGMEM = "LOADPAGEWATER";
const char mode21[] PROGMEM = "WATER";
const char mode22[] PROGMEM = "LOADTEMPERATURE";
const char mode23[] PROGMEM = "LOADPAGETEMPERATURE";
const char mode24[] PROGMEM = "TEMPERATURE";

const char *const modeTable[] PROGMEM = {mode0, mode1, mode2, mode3, mode4, mode5, mode6, mode7, mode8, mode9, mode10, mode11, mode12, mode13, mode14, mode15, mode16, mode17, mode18, mode19, mode20, mode21, mode22, mode23, mode24};

char* modeToString(ScreenStatus status)
{
    strcpy_P(debugBuff, (char *)pgm_read_word(&(modeTable[status])));
    return debugBuff;
}

const char rotationLandscape_STR[] PROGMEM = "Landscape";
const char rotationInvertedLandscape_STR[] PROGMEM = "Inverted landscape";

const char *const debugUITable[] PROGMEM = {rotationLandscape_STR, rotationInvertedLandscape_STR};

char* rotationToString(enum Rotation rotation)
{
    strcpy_P(debugBuff, (char *)pgm_read_word(&(debugUITable[rotation==LANDSCAPE?0:1])));
    return debugBuff;
}

#ifdef debugConfig()
#undef debugConfig()
// TODO change debug(LANGUAGE); to debug(getString(Lang_STR)); in the line below
#define debugConfig() printConfiguration(); debug(F("Rotation: ")); debug(rotationToString(ROTATION)); debug(F("\nLanguage: ")); debug(LANGUAGE); debug(F("\nDATAREFRESHPERIOD: ")); debug(DATAREFRESHPERIOD); debug('\n')
#endif
#else

#define changeScreenStatus(newStatus) screenStatus = newStatus

#endif

//Global Variables
char auxBuffer[32] = ""; // TODO when using progmem, use it as a buffer to print each label

byte page = 0;
byte maxPage = 0;

SimpleLCDTouchScreen my_lcd(ST7796S, A3, A2, A1, A0, A4); //model,cs,cd,wr,rd,reset

Label label(200, 10, "Menu", 3, Color(0, 0, 0)); //general label
Rectangle rectangle(300, 234, 420, 290, Color(0, 0, 0), Color(255, 255, 255), &label);

//Rectangle Buttons
RectangleButton btn1(30, 120, 230, 200, Color(0, 0, 0), Color(255, 255, 255), &label,&ts);
RectangleButton btn2(250, 120, 440, 200, Color(0, 0, 0), Color(255, 255, 255), &label, &ts);
RectangleButton btn3(30, 220, 230, 300, Color(0, 0, 0), Color(255, 255, 255), &label, &ts);
RectangleButton btn4(250, 220, 440, 300, Color(0, 0, 0), Color(255, 255, 255), &label, &ts);
RectangleButton btn5(30, 220, 230, 300, Color(0, 0, 0), Color(255, 255, 255), &label, &ts);
RectangleButton btn6(250, 220, 440, 300, Color(0, 0, 0), Color(255, 255, 255), &label, &ts);
RectangleButton btn7(250, 220, 440, 300, Color(0, 0, 0), Color(255, 255, 255), &label, &ts);
RectangleButton btn8(30, 220, 230, 300, Color(0, 0, 0), Color(255, 255, 255), &label, &ts);

//Rectangle Button Help
RectangleButton btn9(250, 220, 440, 300, Color(0, 0, 0), Color(255, 255, 255), &label, &ts);
RectangleButton btn10(30, 220, 230, 300, Color(0, 0, 0), Color(255, 255, 255), &label, &ts);
RectangleButton btn11(250, 220, 440, 300, Color(0, 0, 0), Color(255, 255, 255), &label, &ts);

// Frequently used ScreenObjects
RectangleButton backBtn(20, 20, 60, 60, Color(0, 0, 0), Color(255, 255, 255), &label, &ts);
Label titleLabel(0, 0, "Menu", 5, Color(0), Color(255, 255, 255));
Rectangle title(65, 5, 415, 75, Color(0xFFFF),/*Color(255,0,0),*/&titleLabel, true);

//Rectangle Button GetNumInput
RectangleButton oKBtn(250, 270, 410, 310, Color(0, 0, 0), Color(255, 255, 255), &label, &ts);
RectangleButton dotBtn(425, 95, 475, 145, Color(0, 0, 0), Color(255, 255, 255), &label, true, &ts);
RectangleButton signBtn(5, 95, 55, 145, Color(0, 0, 0), Color(255, 255, 255), &label, &ts);
//Global Variables End

bool sw = true; // todo delete this

#include "Core/Core.h"
#include "Screens/Screens.h"


void UISetup()
{
    debug(F("Starting UI...\n"));
    my_lcd.set_sd_cs(53); // Set SD pin

    // Set touchScreen pins as input
    pinMode(13, INPUT);
    pinMode(12, INPUT);
    pinMode(11, INPUT);
    pinMode(10, INPUT);

    my_lcd.Init_LCD();
    setRotation(ROTATION);

    //my_lcd.Fill_Screen(0);
    my_lcd.Fill_Screen(Color(255, 255, 255).to565());
    debug(F("UI Ready\n"));
}


void UILoop()
{
    switch (screenStatus)
    {
        case BOOTING:
            drawSplashScreen();
            // Perform other boot stuff after this line
            delay(1000);
            // Perform other boot stuff before this line
            sw = true; // todo delete this
            drawStatusBackground(true);
            changeScreenStatus(STATUS);
            break;

        case LOADSTATUS:
            sw = true; // todo delete this
            drawStatusBackground();
            changeScreenStatus(STATUS);
            break;

        case STATUS: // todo implement real logic with real values
            if (sw) // todo delete this (change condition to update info labels)
            {
                drawStatusForeground("15.4V", "320L");
                sw = false; // todo delete this
            }
            else
            {
                clickStatus();
            }
            break;

        case LOADMENU:
            drawBackground();
            drawMenu();
            changeScreenStatus(MENU);
            break;

        case MENU:
            if (backBtn.isPressed()) // Go to LOADSTATUS
            {
                debug(F("Back button pressed\n"));
                changeScreenStatus(LOADSTATUS);
            }
            else
            {
                clickMenu();
            }
            break;

        case LOADSETTINGS:
            drawBackground();
            drawSettings();
            changeScreenStatus(SETTINGS);
            break;

        case SETTINGS:
            if (backBtn.isPressed()) // Go to LOADMENU
            {
                debug(F("Back button pressed\n"));
                changeScreenStatus(LOADMENU);
            }
            else
            {
                clickSettings();
            }
            break;

        case LOADELECTRICITY:
            page = 1;
            maxPage = 4;
            drawBackground();
        case LOADPAGEELECTRICITY:
            debug(F("Loading page "));debug(page);debug(F(" / "));debug(maxPage);debug('\n');
            drawElectricity();
            changeScreenStatus(ELECTRICITY);
            break;

        case ELECTRICITY:
            if (backBtn.isPressed()) // Go to LOADSETTINGS
            {
                debug(F("Back button pressed\n"));
                changeScreenStatus(LOADSETTINGS);
            }
            else if (page > 1 && btn7.isPressed()) // Previous
            {
                debug(F("Previous button pressed\n"));
                page--;
                changeScreenStatus(LOADPAGEELECTRICITY);
            }
            else if (page < maxPage && btn8.isPressed()) // Next
            {
                debug(F("Next button pressed\n"));
                page++;
                changeScreenStatus(LOADPAGEELECTRICITY);
            }
            else
                clickElectricity();
            break;

        case LOADINTERFACE:
            page = 1;
            maxPage = 2;
            drawBackground();

        case LOADPAGEINTERFACE:
            // in this case you draw the interface
            debug(F("Loading page "));debug(page);debug(F(" / "));debug(maxPage);debug('\n');
            drawInterface();
            changeScreenStatus(INTERFACE);
            break;

        case INTERFACE:
            if (backBtn.isPressed())
            {
                debug(F("Back button pressed\n"));
                changeScreenStatus(LOADSETTINGS);
                // if back button is pressed you go to the previous page, so you start uploading the settings page
            }
            else if (page < maxPage && btn8.isPressed()) // Next page
            {
                debug(F("Next page button pressed\n"));
                page++;
                changeScreenStatus(LOADPAGEINTERFACE);
                // if you press this button, and it's not the last page, change to the next page and load the page by changing to LOADPAGEINTERFACE
            }
            else if (page != 1 && btn7.isPressed())
            {
                debug(F("Previous page button pressed\n"));
                page--;
                changeScreenStatus(LOADPAGEINTERFACE);
                // if you press this button, and it's not the first page, change to the previous page and load the page by changing to LOADPAGEINTERFACE
            }
            else
                clickInterface();
            // if you click in one of the buttons of the page, you go to this function
            break;

        case LOADTEMPERATURE:
            page = 1;
            maxPage = 2;
            drawBackground();
        case LOADPAGETEMPERATURE:
            debug(F("Loading page "));debug(page);debug(F(" / "));debug(maxPage);debug('\n');
            drawTemperature();
            changeScreenStatus(TEMPERATURE);
            break;

        case TEMPERATURE:
            if (backBtn.isPressed())
            {
                debug(F("Back button pressed\n"));
                changeScreenStatus(LOADSETTINGS);
                // if back button is pressed you go to the previous page, so you start uploading the settings page
            }
            else if (page < maxPage && btn8.isPressed()) // Next page
            {
                debug(F("Next page button pressed\n"));
                page++;
                changeScreenStatus(LOADPAGETEMPERATURE);
            }
            else if (page > 1 && btn7.isPressed())
            {
                debug(F("Previous page button pressed\n"));
                page--;
                changeScreenStatus(LOADPAGETEMPERATURE);
            }
            else
            {
                clickTemperature();
            }
            break;

        case LOADWATER:
            page = 1;
            maxPage = 2;
            drawBackground();
        case LOADPAGEWATER:
            debug(F("Loading page "));debug(page);debug(F(" / "));debug(maxPage);debug('\n');
            drawWater();
            changeScreenStatus(WATER);
            break;
        case WATER:
            if (backBtn.isPressed())    // Go to LOADSETTINGS
            {
                debug(F("Back Page button pressed\n"));
                changeScreenStatus(LOADSETTINGS);
            }
            else if (page < maxPage && btn8.isPressed())   // Go to LOADPAGEWATER on next page
            {
                debug(F("Next page button pressed\n"));
                page++;
                changeScreenStatus(LOADPAGEWATER);
            }
            else if (page > 1 && btn7.isPressed())    // Go to LOADPAGEWATER on previous page
            {
                debug(F("Previous page button pressed\n"));
                page--;
                changeScreenStatus(LOADPAGEWATER);
            }
            else
                clickWater();
            break;

        case LOADEXTRAFUNCTIONS:
            drawBackground();
            page = 0;
            drawExtraFunctions();
            changeScreenStatus(EXTRAFUNCTIONS);
            break;
        case EXTRAFUNCTIONS:
            if (backBtn.isPressed())
            {
                debug(F("Back Page button pressed\n"));
                changeScreenStatus(LOADMENU);
            }
            else
            {
                clickExtraFunctions(); // TODO implement extraFunctions logic
            }
            break;
            //case LOADHELP: // TODO implement help menu
            //case HELP:
            //case LOADENGINEERINGMODE: // TODO implement engineering mode
            //case ENGINEERINGMODE:
    }
}

#endif //H2O_GUI_UI_H
