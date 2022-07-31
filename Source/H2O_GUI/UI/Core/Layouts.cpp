//
// Created by Víctor on 16/06/2022.
//

#include "Layouts.h"

void drawBackground()
{
    my_lcd.Fill_Screen(0xFFFF); // White color

    //Back button todo replace with pictureButton
    Line separator(0,80,480,80,Color(0,0,0));
    my_lcd.draw(&separator);
    label.setString("<--");
    my_lcd.draw(&backBtn);

    //Small logo
    Picture logoPhoto(426,10,"PMWSL.bmp");
    my_lcd.draw(&logoPhoto);

}

//btn1 --> topLeft; btn2 --> topRight; btn3 --> bottomLeft; btn4 --> bottomRight
void draw4ButtonsLayout(const String& topLeft, const String& topRight, const String& bottomLeft, const String& bottomRight, const byte* fontSize)
{
    bool validFontSize = fontSize!=nullptr;
    if(validFontSize)
    {
        if(fontSize[0] != 0) btn1.enableAutoSize(false);
        if(fontSize[1] != 0) btn2.enableAutoSize(false);
        if(fontSize[2] != 0) btn3.enableAutoSize(false);
        if(fontSize[3] != 0) btn4.enableAutoSize(false);
    }

    // Top left button
    if (validFontSize)
        label.setFontSize(fontSize[0]);
    label.setString(topLeft.c_str());
    btn1.setCoords(30,120);
    btn1.setCoords1(230,200);
    my_lcd.draw(&btn1);
    btn1.enableAutoSize(true);

    // Top right button
    if (validFontSize)
        label.setFontSize(fontSize[1]);
    label.setString(topRight.c_str());
    btn2.setCoords(250,120);
    btn2.setCoords1(440,200);
    my_lcd.draw(&btn2);
    btn2.enableAutoSize(true);
;

    // Bottom left button
    if (validFontSize)
        label.setFontSize(fontSize[2]);
    label.setString(bottomLeft.c_str());
    btn3.setCoords(30,220);
    btn3.setCoords1(230,300);
    my_lcd.draw(&btn3);
    btn3.enableAutoSize(true);
;

    // Bottom right button
    if (validFontSize)
        label.setFontSize(fontSize[3]);
    label.setString(bottomRight.c_str());
    btn4.setCoords(250,220);
    btn4.setCoords1(440,300);
    my_lcd.draw(&btn4);
    btn4.enableAutoSize(true);
;
}

//btn1 --> topLeft; btn2 --> topRight; btn3 --> bottomLeft; btn4 --> bottomRight
void draw4ButtonsLayout(String topLeft, String topRight, String bottomLeft, String bottomRight)
{
    draw4ButtonsLayout(topLeft, topRight, bottomLeft, bottomRight, nullptr);
}

// btn1 --> topLeft; btn2 --> centerLeft; btn3 --> bottomLeft; btn4 --> topRight; btn5 --> centerRight; btn6 --> bottomRight; btn7 --> Previous; btn8 --> Next; btn9 --> topHelp; btn10 --> centerHelp; btn11 --> bottomHelp; If fontSize = NULL, autoFontSize; len(fontSize) = 6
void draw6ButtonsLayout(String topLeftBtn1, String centerLeftBtn2, String bottomLeftBtn3, String topRightBtn4, String centerRightBtn5, String bottomRightBtn6, bool topHelpBtn9, bool centerHelpBtn10, bool bottomHelpBtn11, const byte* fontSize)
{
    bool validFontSize = fontSize!=nullptr;
    if(validFontSize)
    {
        if(fontSize[0] != 0) btn1.enableAutoSize(false);
        if(fontSize[1] != 0) btn2.enableAutoSize(false);
        if(fontSize[2] != 0) btn3.enableAutoSize(false);
        if(fontSize[3] != 0) btn4.enableAutoSize(false);
        if(fontSize[4] != 0) btn5.enableAutoSize(false);
        if(fontSize[5] != 0) btn6.enableAutoSize(false);
    }
    label.setString(topLeftBtn1.c_str());
    if (validFontSize)
        label.setFontSize(fontSize[0]);
    btn1.setCoords(25,95);
    btn1.setCoords1(195,135);
    my_lcd.draw(&btn1);
    btn1.enableAutoSize(true);

    label.setString(centerLeftBtn2.c_str());
    if (validFontSize)
        label.setFontSize(fontSize[1]);
    btn2.setCoords(25,155);
    btn2.setCoords1(195,195);
    my_lcd.draw(&btn2);
    btn2.enableAutoSize(true);

    label.setString(bottomLeftBtn3.c_str());
    if (validFontSize)
        label.setFontSize(fontSize[2]);
    btn3.setCoords(25,215);
    btn3.setCoords1(195,255);
    my_lcd.draw(&btn3);
    btn3.enableAutoSize(true);

    label.setString(topRightBtn4.c_str());
    if (validFontSize)
        label.setFontSize(fontSize[3]);
    btn4.setCoords(280,95);
    btn4.setCoords1(450,135);
    my_lcd.draw(&btn4);
    btn4.enableAutoSize(true);

    label.setString(centerRightBtn5.c_str());
    if (validFontSize)
        label.setFontSize(fontSize[4]);
    btn5.setCoords(280,155);
    btn5.setCoords1(450,195);
    my_lcd.draw(&btn5);
    btn5.enableAutoSize(true);

    label.setString(bottomRightBtn6.c_str());
    if (validFontSize)
        label.setFontSize(fontSize[5]);
    btn6.setCoords(280,215);
    btn6.setCoords1(450,255);
    my_lcd.draw(&btn6);
    btn6.enableAutoSize(true);

    if(topHelpBtn9)
    {
        btn9.setCoords(218,95);
        btn9.setCoords1(258,135);
        label.setString("?");
        my_lcd.draw(&btn9);
    }

    if(centerHelpBtn10)
    {
        btn10.setCoords(218,155);
        btn10.setCoords1(258,195);
        label.setString("?");
        my_lcd.draw(&btn10);
    }

    if(bottomHelpBtn11)
    {
        btn11.setCoords(218,215);
        btn11.setCoords1(258,255);
        label.setString("?");
        my_lcd.draw(&btn11);
    }
    if(page>0 && maxPage>1)
    {
        Rectangle auxRec(0,268,480,320,Color(0), Color(255,255,255)); // Rectangle auxRec(229,284,249,304,Color(0),&label);
        my_lcd.draw(&auxRec);

        sprintf(auxBuffer,"%d",page);
        label.setString(auxBuffer);
        auxRec.setCoords(229,284);
        auxRec.setCoords1(249,304);
        auxRec.setLabel(&label);
        my_lcd.draw(&auxRec);

        if(page>1)
        {
            btn7.enableAutoSize(false);
            label.setFontSize(3);
            label.setString(getString(Previous_STR));
            btn7.setCoords(35,278);
            btn7.setCoords1(190,308);
            my_lcd.draw(&btn7);
            btn7.enableAutoSize(true);
        }
        if (page<maxPage)
        {
            btn8.enableAutoSize(false);
            label.setFontSize(3);
            label.setString(getString(Next_STR));
            btn8.setCoords(290,278);
            btn8.setCoords1(440,308);
            my_lcd.draw(&btn8);
            btn8.enableAutoSize(true);
        }
    }

}

// btn1 --> topLeft; btn2 --> centerLeft; btn3 --> bottomLeft; btn4 --> topRight; btn5 --> centerRight; btn6 --> bottomRight; btn7 --> Previous; btn8 --> Next; btn9 --> topHelp; btn10 --> centerHelp; btn11 --> bottomHelp
void draw6ButtonsLayout(String topLeftBtn1, String centerLeftBtn2, String bottomLeftBtn3, String topRightBtn4, String centerRightBtn5, String bottomRightBtn6, bool topHelpBtn9, bool centerHelpBtn10, bool bottomHelpBtn11)
{
    draw6ButtonsLayout(topLeftBtn1,centerLeftBtn2,bottomLeftBtn3,topRightBtn4,centerRightBtn5,bottomRightBtn6,topHelpBtn9,centerHelpBtn10,bottomHelpBtn11,nullptr);
}

void drawNumInput (String titleNumInput, String unit)
{
    drawBackground();
    title.enableAutoSize(false);
    titleLabel.setString(titleNumInput.c_str()); // title
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    title.enableAutoSize(true);
;

    //NUMERIC BUTTONS//
    label.setString("1"); // Button number 1
    btn1.setCoords(40,155);
    btn1.setCoords1(100,205);
    btn1.enableAutoSize(true);
;
    my_lcd.draw(&btn1);

    label.setString("2"); // Button number 2
    btn2.setCoords(125,155);
    btn2.setCoords1(185,205);
    btn2.enableAutoSize(true);
;
    my_lcd.draw(&btn2);

    label.setString("3"); // Button number 3
    btn3.setCoords(210,155);
    btn3.setCoords1(270,205);
    btn3.enableAutoSize(true);
;
    my_lcd.draw(&btn3);

    label.setString("4"); // Button number 4
    btn4.setCoords(295,155);
    btn4.setCoords1(355,205);
    btn4.enableAutoSize(true);
;
    my_lcd.draw(&btn4);

    label.setString("5"); // Button number 5
    btn5.setCoords(380,155);
    btn5.setCoords1(440,205);
    btn5.enableAutoSize(true);
;
    my_lcd.draw(&btn5);

    label.setString("6"); // Button number 6
    btn6.setCoords(40,215);
    btn6.setCoords1(100,265);
    btn6.enableAutoSize(true);
;
    my_lcd.draw(&btn6);

    label.setString("7"); // Button number 7
    btn7.setCoords(125,215);
    btn7.setCoords1(185,265);
    btn7.enableAutoSize(true);
;
    my_lcd.draw(&btn7);

    label.setString("8"); // Button number 8
    btn8.setCoords(210,215);
    btn8.setCoords1(270,265);
    btn8.enableAutoSize(true);
;
    my_lcd.draw(&btn8);

    label.setString("9"); // Button number 9
    btn9.setCoords(295,215);
    btn9.setCoords1(355,265);
    btn9.enableAutoSize(true);
;
    my_lcd.draw(&btn9);

    label.setString("0"); // Button number 0
    btn10.setCoords(380,215);
    btn10.setCoords1(440,265);
    btn10.enableAutoSize(true);
;
    my_lcd.draw(&btn10);

    //AUXILIARY BUTTONS//
    label.setString(getString(Delete_STR)); // Button Delete
    btn11.setCoords(60,270);
    btn11.setCoords1(230,310);
    my_lcd.draw(&btn11);

    label.setString(getString(OK_STR)); // Button OK
    my_lcd.draw(&oKBtn);

    label.setString("."); // Button DOT
    label.setFontSize(3);
    my_lcd.draw(&dotBtn);
    label.setFontSize(5);

    label.setString("+/-"); // Button Sign
    my_lcd.draw(&signBtn);

    Label unitLabel(0,0,unit.c_str(),5,Color(0,0,0));
    Rectangle outputUnit(370,95,420,145,Color(),Color(255,255,255),&unitLabel);
    my_lcd.draw(&outputUnit);
}
