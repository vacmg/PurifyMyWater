//
// Created by Victor on 02/09/2022.
//

#include "Error.h"


// TODO
//  HandshakeError
//  MCUsIncompatibleVersionError
//

void drawError()
{
    my_lcd.Fill_Screen(0xFFFF);
    char str[9] = "Error ";
    strcat(str,String(currentError).c_str());
    Label messageLabel(0,0,str,0,Color(255,0,0));
    Rectangle message(50,50,430,270,Color(),&messageLabel);

    my_lcd.draw(&message);
}

void clickError()
{

}
