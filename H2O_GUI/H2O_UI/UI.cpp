//
// Created by Víctor on 16/06/2022.
//

#include "UI.h"

void UISetup()
{
    my_lcd.set_sd_cs(53);
    pinMode(13,INPUT);
    pinMode(12,INPUT);
    pinMode(11,INPUT);
    pinMode(10,INPUT);

    my_lcd.Init_LCD();
    setRotation(ROTATION);

    //my_lcd.Fill_Screen(0);
    my_lcd.Fill_Screen(Color(255,255,255).to565());
}


void UI()
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
            changeStatus(STATUS);
            break;

        case LOADSTATUS:
            sw = true; // todo delete this
            drawStatusBackground();
            changeStatus(STATUS);
            break;

        case STATUS:
            if(sw) // todo delete this (change condition to update info labels)
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
            changeStatus(MENU);
            break;

        case MENU:
            if(backBtn.isPressed()) // Go to LOADSTATUS
            {
                debug(F("Back button pressed"));
                changeStatus(LOADSTATUS);
            }
            else
            {
                clickMenu();
            }
            break;

        case LOADSETTINGS:
            drawBackground();
            drawSettings();
            changeStatus(SETTINGS);
            break;

        case SETTINGS:
            if(backBtn.isPressed()) // Go to LOADMENU
            {
                debug(F("Back button pressed"));
                changeStatus(LOADMENU);
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
            debug(String(F("Loading page "))+page+" / "+maxPage);
            drawElectricity();
            changeStatus(ELECTRICITY);
            break;

        case ELECTRICITY:
            if(backBtn.isPressed()) // Go to LOADSETTINGS
            {
                debug(F("Back button pressed"));
                changeStatus(LOADSETTINGS);
            }
            else if(page>1&&btn7.isPressed()) // Previous
            {
                debug(F("Previous button pressed"));
                page--;
                changeStatus(LOADPAGEELECTRICITY);
            }
            else if(page<maxPage&&btn8.isPressed()) // Next
            {
                debug(F("Next button pressed"));
                page++;
                changeStatus(LOADPAGEELECTRICITY);
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
            debug(String(F("Loading page "))+page+" / "+maxPage);
            drawInterface();
            changeStatus(INTERFACE);
            break;

        case INTERFACE:
            if(backBtn.isPressed())
            {
                debug(F("Back button pressed"));
                changeStatus(LOADSETTINGS);
                // if back button is pressed you go to the previous page, so you start uploading the settings page
            }
            else if(page<maxPage&&btn8.isPressed()) // Next page
            {
                debug(F("Next page button pressed"));
                page++;
                changeStatus(LOADPAGEINTERFACE);
                // if you press this button, and it's not the last page, change to the next page and load the page by changing to LOADPAGEINTERFACE
            }
            else if(page!=1&&btn7.isPressed())
            {
                debug(F("Previous page button pressed"));
                page--;
                changeStatus(LOADPAGEINTERFACE);
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
            debug(String(F("Loading page "))+page+" / "+maxPage);
            drawTemperature();
            changeStatus(TEMPERATURE);
            break;

        case TEMPERATURE:
            if(backBtn.isPressed())
            {
                debug(F("Back button pressed"));
                changeStatus(LOADSETTINGS);
                // if back button is pressed you go to the previous page, so you start uploading the settings page
            }
            else if(page<maxPage&&btn8.isPressed()) // Next page
            {
                debug(F("Next page button pressed"));
                page++;
                changeStatus(LOADPAGETEMPERATURE);
            }
            else if(page>1&&btn7.isPressed())
            {
                debug(F("Previous page button pressed"));
                page--;
                changeStatus(LOADPAGETEMPERATURE);
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
            debug(String(F("Loading page "))+page+" / "+maxPage);
            drawWater();
            changeStatus(WATER);
            break;
        case WATER:
            if (backBtn.isPressed())    // Go to LOADSETTINGS
            {
                debug(F("Back Page button pressed"));
                changeStatus(LOADSETTINGS);
            }
            else if(page<maxPage && btn8.isPressed())   // Go to LOADPAGEWATER on next page
            {
                debug(F("Next page button pressed"));
                page++;
                changeStatus(LOADPAGEWATER);
            }
            else if(page>1 && btn7.isPressed())    // Go to LOADPAGEWATER on previous page
            {
                debug(F("Previous page button pressed"));
                page--;
                changeStatus(LOADPAGEWATER);
            }
            else
                clickWater();
            break;

        case LOADEXTRAFUNCTIONS:
            drawBackground();
            page = 0;
            drawExtraFunctions();
            changeStatus(EXTRAFUNCTIONS);
            break;
        case EXTRAFUNCTIONS:
            if(backBtn.isPressed())
            {
                debug(F("Back Page button pressed"));
                changeStatus(LOADMENU);
            }
            else
            {
                clickExtraFunctions();
            }
            break;
            //case LOADHELP:
            //case HELP:
            //case LOADENGINEERINGMODE:
            //case ENGINEERINGMODE:
            //case LOADEXTRAFUNCTIONS:
    }
}
