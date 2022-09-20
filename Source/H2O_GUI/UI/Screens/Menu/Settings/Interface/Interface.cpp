//
// Created by Víctor on 16/06/2022.
//

#include "Interface.h"

//This function set and draw the title, set the font size and draws the buttons in all pages.
void drawInterface()
{
    titleLabel.setString(getString(Interface_Title_STR));
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    switch (page)
    {
        case 1:
            setFontSizeArray(fontSizes, 1, 1, 1, 1, 1, 1);
            draw6ButtonsLayout(getString(Interface_LanguageTitle_STR), getString(Interface_RotationTitle_STR),getString(Interface_CalibrationTitle_STR),getString(Lang_STR),getString(screenConfig.ROTATION==LANDSCAPE?Interface_RotationLandscape_STR:Interface_RotationInvertedLandscape_STR), getString(Interface_CalibrationStart_STR), true, true, true, fontSizes); // TODO implement interface logic
            break;
        case 2:
            setFontSizeArray(fontSizes, 1, 2, 2, 2, 2, 2);
            draw6ButtonsLayout(getString(Interface_RefreshInterval_STR), getString(Interface_ResetTitle_STR), "",(String) ((double) configStorage.config.DATAREFRESHPERIOD/1000.0) + "s", getString(Interface_ResetStart_STR), "", true,true, false, fontSizes);
            break;
        default:debug(F("Page selected is out of bounds (page>2 || page<0)"));
    }
}

//this function is used for select some value related to the interface and allows you to select between different
//options each headland has.
void clickInterface()
{
    if (btn4.isPressed())
    {
        switch (page)
        {
            case 1: // Language
            changeScreenStatus(LOADLANGUAGE);
                break;
            case 2: // Refresh Period
                double tempVal = getNumInput(getString(Interface_RefreshInterval_STR), F("s"), (double)configStorage.config.DATAREFRESHPERIOD/1000.0);
                debug(tempVal);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0)
                    {
                    #if !DISABLECOMM
                        char payload[10];
                        Communications::createSendMessage(payload, DATAREFRESHPERIOD_ID, String(tempVal).c_str());
                        if (masterComManager.sendMessage(payload))
                        {
                    #endif
                            debug(F("DATAREFRESHPERIOD UPDATED: "));debug(configStorage.config.DATAREFRESHPERIOD);debug(F(" --> "));debug(tempVal);debug('\n');
                            configStorage.config.DATAREFRESHPERIOD = (unsigned long)(tempVal * 1000);
                    #if !DISABLECOMM
                        }
                        else
                        {
                            debug(F("ERROR: Could not send the DATAREFRESHPERIOD update")); // TODO: error message
                        }
                    #endif
                    }
                }
                changeScreenStatus(LOADPAGEINTERFACE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
    else if (btn5.isPressed())
    {
        switch (page)
        {
            case 1: // Rotation
                screenConfig.ROTATION = (screenConfig.ROTATION==LANDSCAPE?INVERTED_LANDSCAPE:LANDSCAPE); // Change rotation variable
                updateScreenConfig();
                setRotation(screenConfig.ROTATION); // Set the rotation in the screen & touch module
                changeScreenStatus(LOADINTERFACE); // Reload interface menu to repaint the screen
                break;
            case 2: // Reset
                changeScreenStatus(LOADRESET);
                break;

        }
    }
}
