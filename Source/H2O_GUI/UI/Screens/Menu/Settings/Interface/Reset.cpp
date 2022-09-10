//
// Created by 34611 on 10/09/2022.
//

#include "Reset.h"

void drawReset(){
    drawBoolPopup("Reset",String("test.txt"),"YES","N0");
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