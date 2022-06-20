//
// Created by Víctor on 16/06/2022.
//

#include "Splash.h"


void drawSplashScreen()
{
    Picture bigLogo(157, 25, "PMWBL.bmp");
    my_lcd.draw(&bigLogo);
}
