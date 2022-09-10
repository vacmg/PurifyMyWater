//
// Created by 34611 on 10/09/2022.
//

#include "Reset.h"

void drawReset(){
    drawBoolPopup(getString(Interface_ResetStart_STR), getPath(ResetPopUp), getString(YES_STR),getString(NO_STR));
}

void clickReset(){
    if(btn1.isPressed()){
        performReset();
    }
    else if(btn2.isPressed()){
        changeScreenStatus(LOADPAGEINTERFACE);
        drawBackground();
    }
}

void performReset(){ //TODO

}