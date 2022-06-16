//
// Created by Víctor on 16/06/2022.
//

#include "Interface.h"

void drawInterface()
{
    titleLabel.setString("Interface");
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    switch (page)
    {
        case 1:
            setFontSizeArray(fontSizes,1,1,1,1,1,1);
            draw6ButtonsLayout(F("Language"),F("Screen Rotation"),F("Screen Calibration"),F("English"),F("Inverted Landscape"),F("Calibrate"),true,true,true, fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes,2,2,2,2,2,2);
            draw6ButtonsLayout(F("Refresh Period"),F("Reset"),"",(String)(((double)DATAREFRESHPERIOD)/1000)+"s","Perform Reset","",true,true,false, fontSizes);
            break;
    }

}

void clickInterface()
{

    if (btn4.isPressed())
    {
        switch (page)
        {
            case 2: // Refresh Period
                double tempVal = getNumInput("Refresh Period", "s", DATAREFRESHPERIOD);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0)
                    {
                        debug(String(F("DATAREFRESHPERIOD UPDATED: ")) + DATAREFRESHPERIOD + String(F(" --> ")) +
                              tempVal);
                        DATAREFRESHPERIOD = (long)tempVal*1000;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEINTERFACE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;
        }
    }
}