//
// Created by jst83 on 22/09/2022.
//

#include "Calibration.h"
#include "Interface.h"

#include <TouchScreen.h> //touch library
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library

#define TOUCH_ORIENTATION  screenConfig.ROTATION
#define TITLE "Screen Calibration"
#define MEGA true

//if the IC model is known or the modules is unreadable,you can use this constructed function
//if the IC model is not known and the modules is readable,you can use this constructed function
//LCDWIKI_KBV my_lcd(320,480,A3,A2,A1,A0,A4);//width,height,cs,cd,wr,rd,reset

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

TouchScreen mytouch(XP, YP, XM, YM, 300);
TSPoint tp;//Touchscreen_due branch uses Point

void loadScreenCalibration()
{
    drawBackground();

    //PAGE TITLE
    titleLabel.setString(TITLE);
    title.setLabel(&titleLabel);
    title.enableAutoSize(true);
    my_lcd.draw(&title);
    title.enableAutoSize(false);

    //TODO insert txt with the text "#define NUMSAMPLES 3 in Library. Use a stylus or something similar to touch as close to the center of the highlighted crosshair as possible. Keep as still as possible and keep holding until the highlight is until the highlight is removed. Repeat for all crosshairs in sequence."
    TextBox screenCalibrationTxt(25,90,455,160,"textPath",&label);
    my_lcd.draw(&screenCalibrationTxt);

    //PUSH TO START BUTTON
    btn11.ScreenObject::setCoords(180,280);
    btn11.setCoords1(300,310);
    label.setString("PRESS TO START"); //TODO use languajes
    btn11.setLabel(&label);
    my_lcd.draw(&btn11);
}

void show_string(uint8_t *str,int16_t x,int16_t y,uint8_t csize,uint16_t fc, uint16_t bc,boolean mode)
{
    my_lcd.Set_Text_Mode(mode);
    my_lcd.Set_Text_Size(csize);
    my_lcd.Set_Text_colour(fc);
    my_lcd.Set_Text_Back_colour(bc);
    my_lcd.Print_String(str,x,y);
}

void Read_Resistive(void)
{
    tp = mytouch.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
}

bool is_pressed(void)
{
    bool state;
    Read_Resistive();
    state = (tp.z > 20 && tp.z < 1000);
    return state;
}

uint32_t cx, cy;
uint32_t rx[8], ry[8];
int32_t clx, crx, cty, cby;
float px, py;
int dispx, dispy, text_y_center, swapxy;
uint32_t calx, caly, cals;
char buf[13];

void drawCrossHair(int x, int y, unsigned int color)
{
    my_lcd.Set_Draw_color(color);
    my_lcd.Draw_Rectangle(x - 10, y - 10, x + 10, y + 10);
    my_lcd.Draw_Fast_VLine(x, y-5, 11);
    my_lcd.Draw_Fast_HLine(x-5, y, 11);
}

void readCoordinates()
{
    int iter = 5000;
    int failcount = 0;
    int cnt = 0;
    uint32_t tx = 0;
    uint32_t ty = 0;
    boolean OK = false;

    while (OK == false)
    {
        my_lcd.Set_Draw_color(0);
        my_lcd.Fill_Rectangle(my_lcd.Get_Display_Width()/2-33, text_y_center, my_lcd.Get_Display_Width()/2+33, text_y_center+8);
        show_string("*  PRESS  *",CENTER,text_y_center,1,GREEN, BLACK,1);
        while (is_pressed() == false) {}
        my_lcd.Set_Draw_color(0);
        my_lcd.Fill_Rectangle(my_lcd.Get_Display_Width()/2-33, text_y_center, my_lcd.Get_Display_Width()/2+33, text_y_center+8);
        show_string("*  HOLD!  *",CENTER,text_y_center,1,RED, BLACK,1);
        cnt = 0;
        iter = 400;
        do
        {
            Read_Resistive();
            // showpoint();
            if (tp.z > 20 && tp.z < 1000)
            {
                tx += tp.x;
                ty += tp.y;
                cnt++;
            }
            else
                failcount++;
        } while ((cnt < iter) && (failcount < 10000));
        if (cnt >= iter)
        {
            OK = true;
        }
        else
        {
            tx = 0;
            ty = 0;
            cnt = 0;
        }
        if (failcount >= 10000)
            fail();
    }

    cx = tx / iter;
    cy = ty / iter;
}

void calibrate(int x, int y, int i)
{
    drawCrossHair(x, y,WHITE);
    readCoordinates();
    my_lcd.Set_Draw_color(0);
    my_lcd.Fill_Rectangle(my_lcd.Get_Display_Width()/2-33, text_y_center, my_lcd.Get_Display_Width()/2+33, text_y_center+8);
    show_string("* RELEASE *",CENTER,text_y_center,1,BLUE, BLACK,1);
    delay(1500);
    drawCrossHair(x, y,0x528A);
    rx[i] = cx;
    ry[i] = cy;
    Serial.print("\r\ncx="); Serial.print(cx);
    Serial.print(" cy="); Serial.print(cy);
    while (is_pressed() == true) {}
}



void showNumI(char *msg, uint32_t val, int x, int y)
{
    show_string(msg,x,y,1,MAGENTA, BLACK,1);
    my_lcd.Set_Text_colour(GREEN);
    my_lcd.Print_Number_Int(val, x+50, y, 0, ' ',10);
}

void done()
{
    uint16_t TS_LEFT, TS_RT, TS_TOP, TS_BOT, TS_WID, TS_HT, TS_SWAP;
    int16_t tmp;
    my_lcd.Fill_Screen(BLACK);
    my_lcd.Set_Draw_color(255, 0, 0);
    my_lcd.Fill_Rectangle(0, 0, dispx - 1, 13);
    my_lcd.Set_Draw_color(255, 255, 255);
    my_lcd.Draw_Line(0, 14, dispx - 1, 14);
    show_string(TITLE,CENTER,1,1,WHITE, BLACK,1);
    my_lcd.Print_String("To use the new calibration", LEFT, 30);
    my_lcd.Print_String("settings you must map the values", LEFT, 42);
    my_lcd.Print_String("from Point p = mytouch.getPoint() e.g. ", LEFT, 54);
    my_lcd.Print_String("x = map(p.x, LEFT, RT, 0, lcd.width());", LEFT, 66);
    my_lcd.Print_String("y = map(p.y, TOP, BOT, 0, lcd.height());", LEFT, 78);
    my_lcd.Print_String("swap p.x and p.y if diff ORIENTATION", LEFT, 90);

    //.kbv show human values
    TS_LEFT = (calx >> 14) & 0x3FFF;
    TS_RT   = (calx >>  0) & 0x3FFF;
    TS_TOP  = (caly >> 14) & 0x3FFF;
    TS_BOT  = (caly >>  0) & 0x3FFF;
    TS_WID  = ((cals >> 12) & 0x0FFF) + 1;
    TS_HT   = ((cals >>  0) & 0x0FFF) + 1;
    TS_SWAP = (cals >> 31);
    if (TOUCH_ORIENTATION != 0) {
        my_lcd.Print_String("Sketch is LANDSCAPE", 0, 126);
        my_lcd.Print_Number_Int(TS_WID, 150, 126, 0, ' ',10);
        my_lcd.Print_String("x", 174, 126);
        my_lcd.Print_Number_Int(TS_HT, 186, 126, 0, ' ',10);
        showNumI("LEFT ", TS_LEFT, 0, 138);
        showNumI("RT   ", TS_RT, 100, 138);
        showNumI("TOP  ", TS_TOP, 0, 150);
        showNumI("BOT  ", TS_BOT, 100, 150);
        switch (TOUCH_ORIENTATION) {
            case 1:
                tmp = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = TS_RT, TS_RT = TS_BOT, TS_BOT = tmp;
                tmp = TS_WID, TS_WID = TS_HT, TS_HT = tmp;
                break;
        }
    }
    my_lcd.Print_String("PORTRAIT CALIBRATION", 0, 174);
    my_lcd.Print_Number_Int(TS_WID, 150, 174, 0, ' ',10);
    my_lcd.Print_String("x", 174, 174);
    my_lcd.Print_Number_Int(TS_HT, 186, 174, 0, ' ',10);
    showNumI("LEFT ", TS_LEFT, 0, 186);
    showNumI("RT   ", TS_RT, 100, 186);
    my_lcd.Print_Number_Float(((float)TS_RT - TS_LEFT) / TS_WID, 2, 200, 186, '.', 0, ' ');
    showNumI("TOP  ", TS_TOP, 0, 198);
    showNumI("BOT  ", TS_BOT, 100, 198);
    my_lcd.Print_Number_Float(((float)TS_BOT - TS_TOP) / TS_HT, 2, 200, 198, '.', 0, ' ');
    my_lcd.Print_String("Touch Pin Wiring is ", 0, 222);
    my_lcd.Print_String((cals >> 31) ? "SWAPXY" : "PORTRAIT", 170, 222);

#if SCREENHW == 39
    ts.setCalibration(TS_LEFT,TS_RT, TS_BOT,TS_TOP);
#elif SCREENHW == 35
    ts.setCalibration(TS_RT,TS_LEFT, TS_BOT,TS_TOP);
#endif

    debug('\n');
    debugStatement(TS_LEFT);
    debug('\n');
    debugStatement(TS_RT);
    debug('\n');
    debugStatement(TS_TOP);
    debug('\n');
    debugStatement(TS_BOT);
    debug('\n');
}

void fail() {
    my_lcd.Fill_Screen(BLACK);
    my_lcd.Set_Draw_color(255, 0, 0);
    my_lcd.Fill_Rectangle(0, 0, dispx - 1, 13);
    my_lcd.Set_Draw_color(255, 255, 255);
    my_lcd.Draw_Line(0, 14, dispx - 1, 14);
    show_string("Touch Calibration FAILED", CENTER, 1, 1, WHITE, BLACK, 1);

    my_lcd.Print_String("Unable to read the position", LEFT, 30);
    my_lcd.Print_String("of the press. This is a", LEFT, 42);
    my_lcd.Print_String("hardware issue and can", LEFT, 54);
    my_lcd.Print_String("not be corrected in", LEFT, 66);
    my_lcd.Print_String("software.", LEFT, 78);
    my_lcd.Print_String("check XP, XM pins with a multimeter", LEFT, 102);
    my_lcd.Print_String("check YP, YM pins with a multimeter", LEFT, 114);
    my_lcd.Print_String("should be about 300 ohms", LEFT, 126);

}

void loopCalibration()
{
    //SETUP
    digitalWrite(A0, HIGH);
    pinMode(A0, OUTPUT);
#if MEGA
    pinMode(13,INPUT); // TODO revertir pinout
    pinMode(12,INPUT);
    pinMode(11,INPUT);
    pinMode(10,INPUT);
#endif
    my_lcd.Fill_Screen(BLACK);
    dispx = my_lcd.Get_Display_Width();
    dispy = my_lcd.Get_Display_Height();
    text_y_center = (dispy / 2) - 6;

    drawCrossHair(dispx - 11, 10,0x528A); //TODO AQUI
    drawCrossHair(dispx / 2, 10,0x528A);
    drawCrossHair(10, 10,0x528A);
    drawCrossHair(dispx - 11, dispy / 2,0x528A);
    drawCrossHair(10, dispy / 2,0x528A);
    drawCrossHair(dispx - 11, dispy - 11,0x528A);
    drawCrossHair(dispx / 2, dispy - 11,0x528A);
    drawCrossHair(10, dispy - 11,0x528A);

    show_string("***********",CENTER,text_y_center - 12,1,WHITE, BLACK,1);
    show_string("***********",CENTER,text_y_center + 12,1,WHITE, BLACK,1);

    calibrate(10, 10, 0);
    calibrate(10, dispy / 2, 1);
    calibrate(10, dispy - 11, 2);
    calibrate(dispx / 2, 10, 3);
    calibrate(dispx / 2, dispy - 11, 4);
    calibrate(dispx - 11, 10, 5);
    calibrate(dispx - 11, dispy / 2, 6);
    calibrate(dispx - 11, dispy - 11, 7);

    cals = (long(dispx - 1) << 12) + (dispy - 1);
    if (TOUCH_ORIENTATION == 0) swapxy = rx[2] - rx[0];
    else swapxy = ry[2] - ry[0];
    swapxy = (swapxy < -500 || swapxy > 500);
    if ((TOUCH_ORIENTATION == 0) ^ (swapxy != 0)) {
        clx = (rx[0] + rx[1] + rx[2]) / 3;
        crx = (rx[5] + rx[6] + rx[7]) / 3;
        cty = (ry[0] + ry[3] + ry[5]) / 3;
        cby = (ry[2] + ry[4] + ry[7]) / 3;
    } else {
        clx = (ry[0] + ry[1] + ry[2]) / 3;
        crx = (ry[5] + ry[6] + ry[7]) / 3;
        cty = (rx[0] + rx[3] + rx[5]) / 3;
        cby = (rx[2] + rx[4] + rx[7]) / 3;
    }
    px = float(crx - clx) / (dispx - 20);
    py = float(cby - cty) / (dispy - 20);
    //  px = 0;
    clx -= px * 10;
    crx += px * 10;
    cty -= py * 10;
    cby += py * 10;

    calx = (long(clx) << 14) + long(crx);
    caly = (long(cty) << 14) + long(cby);
    if (swapxy)
        cals |= (1L << 31);

    done();
}