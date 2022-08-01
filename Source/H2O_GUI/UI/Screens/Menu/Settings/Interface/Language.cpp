//
// Created by Victor on 01/08/2022.
//

#include "Language.h"

//This function set and draw the title, set the font size and draws the buttons in all pages.
void drawLanguage()
{
    titleLabel.setString(getString(Language_Title_STR));
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    switch (page)
    {
        case 1:
            setFontSizeArray(fontSizes, 2, 2, 2, 2, 2, 2);
            draw6ButtonsLayout(getString(Lang_STR,ENGLISH), getString(Lang_STR,FRENCH),"", getString(Lang_STR,SPANISH),"", "",false, false, false, fontSizes); // TODO implement interface logic
            break;
        default:debug(F("Page selected is out of bounds (page>1 || page<0)"));
    }
}

//This function is used to handle click events in Language screen
void clickLanguage()
{
    if (btn1.isPressed())
    {
        switch (page)
        {
            case 1: // English
                debug(F("LANGUAGE UPDATED: "));debug(getString(Lang_STR));debug(F(" --> "));debug(getString(Lang_STR, ENGLISH));debug('\n');
                screenConfig.LANGUAGE = ENGLISH;
                updateScreenConfig();
                changeScreenStatus(LOADINTERFACE); // reload page with new config value
                break;
        }
    }
    else if (btn2.isPressed())
    {
        switch (page)
        {
            case 1: // French
                debug(F("LANGUAGE UPDATED: "));debug(getString(Lang_STR));debug(F(" --> "));debug(getString(Lang_STR, FRENCH));debug('\n');
                screenConfig.LANGUAGE = FRENCH;
                updateScreenConfig();
                changeScreenStatus(LOADINTERFACE); // reload page with new config value
                break;
        }
    }
    else if (btn4.isPressed())
    {
        switch (page)
        {
            case 1: // French
                debug(F("LANGUAGE UPDATED: "));debug(getString(Lang_STR));debug(F(" --> "));debug(getString(Lang_STR, SPANISH));debug('\n');
                screenConfig.LANGUAGE = SPANISH;
                updateScreenConfig();
                changeScreenStatus(LOADINTERFACE); // reload page with new config value
                break;
        }
    }
}
