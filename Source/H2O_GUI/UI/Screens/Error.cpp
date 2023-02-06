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
    switch (currentError)
    {
        case ScreenNotImplementedError:
        {
            my_lcd.Fill_Screen(0xFFFF);
            Label title(25, 25, getString(ScreenNotImplementedError_STR), 2, Color(255, 0, 0));
            Rectangle titleRec(25, 25, 455, 200, Color(255, 0, 0), &title,false);
            my_lcd.draw(&titleRec);
            btn1.setCoords(25, 255);
            btn1.setCoords1(455,305);
            label.setString(getString(OK_STR));
            my_lcd.draw(&btn1);
        }

            break;

        case InnerLimitReachedError:
        {
            drawOkPopup(getString(LowRangeValue_STR), getPath(LowRange_PATH), getString(OK_STR));
        }
            break;

        case UpperLimitReachedError:
        {
            drawOkPopup(getString(UpRangeValue_STR), getPath(UpRange_PATH), getString(OK_STR));
        }
            break;


        default:
            my_lcd.Fill_Screen(0xFFFF);
            char str[9] = "Error ";
            strcat(str,String(currentError).c_str());
            Label messageLabel(0,0,str,0,Color(255,0,0));
            Rectangle message(50,50,430,270,Color(),&messageLabel);

            my_lcd.draw(&message);
    }

}

void clickError()
{
    if(btn1.isPressed() && currentError == ScreenNotImplementedError)
    {
        changeError(NoError);
        changeScreenStatus(LOADMENU);
    }
    else if(btn1.isPressed() && currentError == InnerLimitReachedError)
    {
        changeError(NoError);
        changeScreenStatus(prevScreenStatus);
        drawBackground();
    }
    else if(btn1.isPressed() && currentError == UpperLimitReachedError)
    {
        changeError(NoError);
        changeScreenStatus(prevScreenStatus);
        drawBackground();
    }

}
