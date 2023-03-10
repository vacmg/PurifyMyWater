//
// Created by Víctor on 16/06/2022.
//

#include "Splash.h"

#if DEBUG
const char debugFlagsTitle[] PROGMEM = "CAUTION";
const char debugFlagsMessage1[] PROGMEM = "NEVER use debug features on a";
const char debugFlagsMessage2[] PROGMEM = "deployed system, there is risk of";
const char debugFlagsMessage3[] PROGMEM = "IRREVERSIBLE DAMAGE to the system";
const char debugFlagsMessage4[] PROGMEM = "Using those debug features:";
const char debugFlagsMessageDebug[] PROGMEM = "DEBUG - Used to display debug information messages through Serial port";
#endif
#if DISABLECOMM
const char debugFlagsMessageDisableComm[] PROGMEM = "DISABLECOMM - Used to disable communications module";
#endif
#if SETDEFAULTSCREENCONFIG
const char debugFlagsMessageSetDefaultScreenConfig[] PROGMEM = "SETDEFAULTSCREENCONFIG - Used to set the screenConfig to the default";
const char debugFlagsMessageSetDefaultScreenConfig2[] PROGMEM = "screenConfig";
#endif
#if USEVOLATILECONFIG
const char debugFlagsMessageUseVolatileConfig[] PROGMEM = "USEVOLATILECONFIG - Used to disable EEPROM writes due to saving";
const char debugFlagsMessageUseVolatileConfig2[] PROGMEM = "configuration in the persistent storage";

#endif

#if DEBUG
void drawDebugFlagsScreen()
{

    char debugFlagsBuff[104];
    Rectangle messageRec(15,15,465,305,Color(255,0,0));
    my_lcd.draw(&messageRec);

    strcpy_P(debugFlagsBuff,debugFlagsTitle);
    Label title(25,25,debugFlagsBuff,2,Color(255,0,0));
    Rectangle titleRec(25,25,455,75,Color(255,0,0),&title);
    my_lcd.draw(&titleRec);

    byte xcoord = 50;
    byte ycoord = 90;
    const byte yspacing = 10;

    strcpy_P(debugFlagsBuff,debugFlagsMessage1);
    Label message(xcoord,ycoord,debugFlagsBuff,2,Color(255,0,0));
    my_lcd.draw((&message));

    ycoord+=2*yspacing;
    strcpy_P(debugFlagsBuff,debugFlagsMessage2);
    message.setCoords(xcoord,ycoord);
    my_lcd.draw(&message);

    ycoord+=2*yspacing;
    strcpy_P(debugFlagsBuff,debugFlagsMessage3);
    message.setCoords(xcoord,ycoord);
    my_lcd.draw(&message);

    message.setMainColor(Color());
    ycoord+=4*yspacing;
    strcpy_P(debugFlagsBuff,debugFlagsMessage4);
    message.setCoords(xcoord,ycoord);
    my_lcd.draw(&message);

    message.setFontSize(1);
    xcoord-=10;

    ycoord+=2*yspacing;
    strcpy_P(debugFlagsBuff,debugFlagsMessageDebug);
    message.setCoords(xcoord,ycoord);
    my_lcd.draw(&message);

    #if DISABLECOMM
        ycoord+=yspacing;
        strcpy_P(debugFlagsBuff,debugFlagsMessageDisableComm);
        message.setCoords(xcoord,ycoord);
        my_lcd.draw(&message);
    #endif
    #if SETDEFAULTSCREENCONFIG
        ycoord+=yspacing;
        strcpy_P(debugFlagsBuff,debugFlagsMessageSetDefaultScreenConfig);
        message.setCoords(xcoord,ycoord);
        my_lcd.draw(&message);

        ycoord+=yspacing;
        strcpy_P(debugFlagsBuff,debugFlagsMessageSetDefaultScreenConfig2);
        message.setCoords(xcoord,ycoord);
        my_lcd.draw(&message);
    #endif
    #if USEVOLATILECONFIG
        ycoord+=yspacing;
        strcpy_P(debugFlagsBuff,debugFlagsMessageUseVolatileConfig);
        message.setCoords(xcoord,ycoord);
        my_lcd.draw(&message);

        ycoord+=yspacing;
        strcpy_P(debugFlagsBuff,debugFlagsMessageUseVolatileConfig2);
        message.setCoords(xcoord,ycoord);
        my_lcd.draw(&message);
    #endif
}
#endif

void drawSplashScreen()
{
#if DEBUG
    delay(8000);
    my_lcd.Fill_Screen(0xFFFF);
#endif
    Picture bigLogo(157, 25, "PMWBL.bmp");
    my_lcd.draw(&bigLogo);
    delay(1000);
}
