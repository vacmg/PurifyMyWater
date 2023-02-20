//
// Created by Víctor on 16/06/2022.
//

#ifndef H2O_GUI_UI_H
#define H2O_GUI_UI_H

#include <Arduino.h>
#include <LCDWIKI_KBV.h>
#include <LCDWIKI_GUI.h>
#include <TouchScreen.h>
#include <SimpleLCDTouchScreen.h>

#include "../Shared/SharedData.h"
#include "Settings/ScreenSettings.h"

#ifndef SCREENHW
#define SCREENHW 39 // 35 --> 3.5INCH / 39 --> 3.95INCH
#endif

#if SCREENHW == 35
#define SCREEN35ROTATIONOFFSET 2
#endif

    enum ScreenStatus{
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
        LOADLANGUAGE,
        LOADPAGELANGUAGE,
        LANGUAGE,
        LOADWATER,
        LOADPAGEWATER,
        WATER,
        LOADTEMPERATURE,
        LOADPAGETEMPERATURE,
        TEMPERATURE,
        LOADERROR,
        ERROR,
        LOADRESET,
        RESET,
    };
enum ScreenStatus screenStatus = LOADWATER; // Must be initialized to BOOTING in order to show the splash screen
enum ScreenStatus prevScreenStatus = LOADMENU;


#include "Languages/Languages.h"

#if SCREENHW == 35
TouchScreenObject ts(9, A2, A3, 8, 300, 320, 480, (screenConfig.ROTATION + SCREEN35ROTATIONOFFSET) % 4, 177, 900, 157,
                     958); // for 3.5inch
#elif SCREENHW == 39
TouchScreenObject ts(8,A3,A2,9,300,320,480,screenConfig.ROTATION,924,111,58,935); // rx is the resistance between X+ and X- Use any multimeter to read it or leave it blanc
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
const char mode19[] PROGMEM = "LOADLANGUAGE";
const char mode20[] PROGMEM = "LOADPAGELANGUAGE";
const char mode21[] PROGMEM = "LANGUAGE";
const char mode22[] PROGMEM = "LOADWATER";
const char mode23[] PROGMEM = "LOADPAGEWATER";
const char mode24[] PROGMEM = "WATER";
const char mode25[] PROGMEM = "LOADTEMPERATURE";
const char mode26[] PROGMEM = "LOADPAGETEMPERATURE";
const char mode27[] PROGMEM = "TEMPERATURE";
const char mode28[] PROGMEM = "LOADERROR";
const char mode29[] PROGMEM = "ERROR";
const char mode30[] PROGMEM = "LOADRESET";
const char mode31[] PROGMEM = "RESET";

const char *const modeTable[] PROGMEM = {mode0, mode1, mode2, mode3, mode4, mode5, mode6, mode7, mode8, mode9, mode10, mode11, mode12, mode13, mode14, mode15, mode16, mode17, mode18, mode19, mode20, mode21, mode22, mode23, mode24, mode25, mode26, mode27, mode28, mode29, mode30, mode31};

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
#define debugConfig() printConfiguration(); debug(F("Rotation: ")); debug(rotationToString(screenConfig.ROTATION)); debug(F("\nLanguage: ")); debug(getString(Lang_STR)); debug('\n')
#endif
#else

#define changeScreenStatus(newStatus) screenStatus = newStatus

#endif

//Global Variables

byte page = 0;
byte maxPage = 0;
bool updateStatusForeground = true;

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

Label titleLabel(0, 0, "", 5, Color(0), Color(255, 255, 255));
Rectangle title(65, 5, 415, 75, Color(0xFFFF),&titleLabel, false);

//Rectangle Button GetNumInput
RectangleButton oKBtn(250, 270, 410, 310, Color(0, 0, 0), Color(255, 255, 255), &label, &ts);
RectangleButton dotBtn(425, 95, 475, 145, Color(0, 0, 0), Color(255, 255, 255), &label, false, &ts);
RectangleButton signBtn(5, 95, 55, 145, Color(0, 0, 0), Color(255, 255, 255), &label, &ts);

//Global Variables End

#include "Core/Core.h"
#include "Screens/Screens.h"

#if !DISABLECOMM
#include "../MasterComHandlers/MasterComHandlers.h"
#endif


void UISetup()
{
    debug(F("Starting UI...\n"));
    my_lcd.set_sd_cs(53); // Set SD pin

    // Set touchScreen pins as input
    pinMode(13, INPUT);
    pinMode(12, INPUT);
    pinMode(11, INPUT);
    pinMode(10, INPUT);

#if USEVOLATILECONFIG
    debug(F("Using volatile UI settings (DEBUG MODE)\n"));
#endif

#if SETDEFAULTSCREENCONFIG
    debug(F("Using default UI configuration (DEBUG MODE)\n"));
    setDefaultScreenConfig(); // load default settings
    updateScreenConfig(); // save default settings to EEPROM
#else
    if(!readScreenConfig()) // Try to read screenConfig, if failure, load default
    {
        debug(F("Failure loading UI configuration, restoring to default...\t"));
        setDefaultScreenConfig(); // load default settings
        updateScreenConfig(); // save default settings to EEPROM
        debug(F("Done\n"));
    }
    else
    {
#if USEVOLATILECONFIG
        setDefaultScreenConfig();
#endif
        debug(F("UI configuration successfully load\n"));
    }
#endif

    debug(F("Using language: ")); debug(getString(Lang_STR));debug('\n');


    my_lcd.Init_LCD();
    setRotation(screenConfig.ROTATION);

    //my_lcd.Fill_Screen(0);
    my_lcd.Fill_Screen(Color(255, 255, 255).to565());
#if DEBUG
    drawDebugFlagsScreen();
#endif
    debug(F("UI Ready\n"));
}


void UILoop()
{
    switch (screenStatus)
    {
        case BOOTING:
            drawSplashScreen();
            drawStatusBackground(true);
            #if !DISABLECOMM
            sendAvailableCommand();
            #endif
            changeScreenStatus(STATUS);
            break;

        case LOADERROR:
            drawError();
            changeScreenStatus(ERROR);
            break;

        case ERROR:
            clickError();
            break;

        case LOADSTATUS:
            updateStatusForeground = true;
            drawStatusBackground();
            changeScreenStatus(STATUS);
            break;

        case STATUS:
            if (updateStatusForeground)
            {
                drawStatusForeground();
                delay(500);
                updateStatusForeground = false;
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

        case LOADRESET:
            drawReset();
            changeScreenStatus(RESET);
            break;

        case RESET:
            clickReset();
            break;

        case LOADLANGUAGE:
            page = 1;
            maxPage = 1;
            drawBackground();

        case LOADPAGELANGUAGE:
            // in this case you draw the interface
            debug(F("Loading page "));debug(page);debug(F(" / "));debug(maxPage);debug('\n');
            drawLanguage();
            changeScreenStatus(LANGUAGE);
            break;

        case LANGUAGE:
            if (backBtn.isPressed())
            {
                debug(F("Back button pressed\n"));
                changeScreenStatus(LOADINTERFACE);
                // if back button is pressed you go to the previous page, so you start uploading the settings page
            }
            else if (page < maxPage && btn8.isPressed()) // Next page
            {
                debug(F("Next page button pressed\n"));
                page++;
                changeScreenStatus(LOADPAGELANGUAGE);
                // if you press this button, and it's not the last page, change to the next page and load the page by changing to LOADPAGEINTERFACE
            }
            else if (page != 1 && btn7.isPressed())
            {
                debug(F("Previous page button pressed\n"));
                page--;
                changeScreenStatus(LOADPAGELANGUAGE);
                // if you press this button, and it's not the first page, change to the previous page and load the page by changing to LOADPAGEINTERFACE
            }
            else
                clickLanguage();
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

        case LOADHELP: // TODO implement help menu
            changeError(ScreenNotImplementedError);
            changeScreenStatus(LOADERROR);
        break;

        //case HELP:

        case LOADENGINEERINGMODE: // TODO implement engineering mode
            changeError(ScreenNotImplementedError);
            changeScreenStatus(LOADERROR);
        break;

        //case ENGINEERINGMODE:
    }
}

#endif //H2O_GUI_UI_H
