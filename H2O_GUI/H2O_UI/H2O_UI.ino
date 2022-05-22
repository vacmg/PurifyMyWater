#define H2O_GUI true // H2O_GUI ID for shared files

#include <Arduino.h>
#include <LCDWIKI_KBV.h>
#include <LCDWIKI_GUI.h>
#include <TouchScreen.h>
#include <SimpleLCDTouchScreen.h>

#define DEBUG true
#define SCREENHW 39 // 35 --> 3.5INCH / 39 --> 3.95INCH

enum ScreenStatus {BOOTING = 0, LOADSTATUS, STATUS, LOADMENU, MENU, LOADSETTINGS, SETTINGS, LOADHELP, HELP, LOADENGINEERINGMODE, ENGINEERINGMODE, LOADEXTRAFUNCTIONS, EXTRAFUNCTIONS, LOADELECTRICITY, LOADPAGEELECTRICITY, ELECTRICITY, LOADINTERFACE, LOADPAGEINTERFACE, INTERFACE, LOADWATER, LOADPAGEWATER, WATER, LOADTEMPERATURE, LOADPAGETEMPERATURE, TEMPERATURE};
// ON/OFF BTN STATUS
enum BtnStatus {OFF, ON, ERROR};

BtnStatus mainSwitchSt = OFF;
ScreenStatus screenStatus = BOOTING; // Must be initialized to BOOTING in order to show splash screen
byte ROTATION = 1;

#include "sharedData.h"

#if SCREENHW == 35
#define SCREEN35ROTATIONOFFSET 2
TouchScreenObject ts(9,A2,A3,8,300,320,480,(ROTATION+SCREEN35ROTATIONOFFSET)%4,177,900,157,958); // for 3.5inch
#elif SCREENHW == 39
TouchScreenObject ts(8,A3,A2,9,300,320,480,ROTATION,924,111,58,935); // rx is the resistance between X+ and X- Use any multimeter to read it or leave it blanc
#endif

//Global Variables
char auxBuffer[32] = ""; // TODO when using progmem, use it as a buffer to print each label

byte page = 0;
byte maxPage = 0;

SimpleLCDTouchScreen my_lcd(ST7796S, A3, A2, A1, A0, A4); //model,cs,cd,wr,rd,reset

Label label(200,10,"Menu",3,Color(0,0,0)); //general label
Rectangle rectangle(300,234,420,290, Color(0,0,0), Color(255,255,255),&label);

//Rectangle Buttons
RectangleButton btn1(30,120,230,200,Color(0,0,0),Color(255,255,255),&label,&ts); // todo disable autosize & enable again in the cases that is needed
RectangleButton btn2(250,120,440,200,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton btn3(30,220,230,300,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton btn4(250,220,440,300,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton btn5(30,220,230,300,Color(0,0,0),Color(255,255,255),&label, &ts);
RectangleButton btn6(250,220,440,300,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton btn7(250,220,440,300,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton btn8(30,220,230,300,Color(0,0,0),Color(255,255,255),&label,&ts);

//Rectangle Button Help
RectangleButton btn9(250,220,440,300,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton btn10(30,220,230,300,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton btn11(250,220,440,300,Color(0,0,0),Color(255,255,255),&label,&ts);

// Frequently used ScreenObjects
RectangleButton backBtn(20,20,60,60,Color(0,0,0),Color(255,255,255),&label,&ts);
Label titleLabel(0,0,"Menu",5,Color(0),Color(255,255,255));
Rectangle title(65,5,415,75,Color(0xFFFF),/*Color(255,0,0),*/&titleLabel,true);
//Global Variables End

//Auxiliary functions

//Rectangle Button GetNumInput
RectangleButton oKBtn(250,270,410,310,Color(0,0,0),Color(255,255,255),&label,&ts);
RectangleButton dotBtn(425,95,475,145,Color(0,0,0),Color(255,255,255),&label,true,&ts);
RectangleButton signBtn(5,95,55,145,Color(0,0,0),Color(255,255,255),&label,&ts);


void setRotation(byte rotation)
{
#if SCREENHW == 35
    my_lcd.Set_Rotation(rotation);
    ts.setRotation((rotation+SCREEN35ROTATIONOFFSET)%4);
    ts.invertXAxis(true);
#elif SCREENHW == 39
    my_lcd.Set_Rotation(rotation);
    ts.setRotation(rotation);
#endif
}

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
void draw4ButtonsLayout(String topLeft, String topRight, String bottomLeft, String bottomRight, const byte* fontSize)
{
    bool validFontSize = fontSize!=NULL;
    if(validFontSize)
    {
        if(fontSize[0] != 0) btn1.setDisableAutoSize(true);
        if(fontSize[1] != 0) btn2.setDisableAutoSize(true);
        if(fontSize[2] != 0) btn3.setDisableAutoSize(true);
        if(fontSize[3] != 0) btn4.setDisableAutoSize(true);
    }

    // Top left button
    if (validFontSize) label.setFontSize(fontSize[0]);
    label.setString(topLeft.c_str());
    btn1.setCoords(30,120);
    btn1.setCoords1(230,200);
    my_lcd.draw(&btn1);
    btn1.setDisableAutoSize(false);

    // Top right button
    if (validFontSize) label.setFontSize(fontSize[1]);
    label.setString(topRight.c_str());
    btn2.setCoords(250,120);
    btn2.setCoords1(440,200);
    my_lcd.draw(&btn2);
    btn2.setDisableAutoSize(false);

    // Bottom left button
    if (validFontSize) label.setFontSize(fontSize[2]);
    label.setString(bottomLeft.c_str());
    btn3.setCoords(30,220);
    btn3.setCoords1(230,300);
    my_lcd.draw(&btn3);
    btn3.setDisableAutoSize(false);

    // Bottom right button
    if (validFontSize) label.setFontSize(fontSize[3]);
    label.setString(bottomRight.c_str());
    btn4.setCoords(250,220);
    btn4.setCoords1(440,300);
    my_lcd.draw(&btn4);
    btn4.setDisableAutoSize(false);
}

//btn1 --> topLeft; btn2 --> topRight; btn3 --> bottomLeft; btn4 --> bottomRight
void draw4ButtonsLayout(String topLeft, String topRight, String bottomLeft, String bottomRight)
{
    draw4ButtonsLayout(topLeft, topRight, bottomLeft, bottomRight, NULL);
}

// btn1 --> topLeft; btn2 --> centerLeft; btn3 --> bottomLeft; btn4 --> topRight; btn5 --> centerRight; btn6 --> bottomRight; btn7 --> Previous; btn8 --> Next; btn9 --> topHelp; btn10 --> centerHelp; btn11 --> bottomHelp; If fontSize = NULL, autoFontSize; len(fontSize) = 6
void draw6ButtonsLayout(String topLeftBtn1, String centerLeftBtn2, String bottomLeftBtn3, String topRightBtn4, String centerRightBtn5, String bottomRightBtn6, bool topHelpBtn9, bool centerHelpBtn10, bool bottomHelpBtn11, const byte* fontSize)
{
    bool validFontSize = fontSize!=NULL;
    if(validFontSize)
    {
        if(fontSize[0] != 0) btn1.setDisableAutoSize(true);
        if(fontSize[1] != 0) btn2.setDisableAutoSize(true);
        if(fontSize[2] != 0) btn3.setDisableAutoSize(true);
        if(fontSize[3] != 0) btn4.setDisableAutoSize(true);
        if(fontSize[4] != 0) btn5.setDisableAutoSize(true);
        if(fontSize[5] != 0) btn6.setDisableAutoSize(true);
    }
    label.setString(topLeftBtn1.c_str());
    if (validFontSize) label.setFontSize(fontSize[0]);
    btn1.setCoords(25,95);
    btn1.setCoords1(195,135);
    my_lcd.draw(&btn1);

    label.setString(centerLeftBtn2.c_str());
    if (validFontSize) label.setFontSize(fontSize[1]);
    btn2.setCoords(25,155);
    btn2.setCoords1(195,195);
    my_lcd.draw(&btn2);

    label.setString(bottomLeftBtn3.c_str());
    if (validFontSize) label.setFontSize(fontSize[2]);
    btn3.setCoords(25,215);
    btn3.setCoords1(195,255);
    my_lcd.draw(&btn3);

    label.setString(topRightBtn4.c_str());
    if (validFontSize) label.setFontSize(fontSize[3]);
    btn4.setCoords(280,95);
    btn4.setCoords1(450,135);
    my_lcd.draw(&btn4);

    label.setString(centerRightBtn5.c_str());
    if (validFontSize) label.setFontSize(fontSize[4]);
    btn5.setCoords(280,155);
    btn5.setCoords1(450,195);
    my_lcd.draw(&btn5);

    label.setString(bottomRightBtn6.c_str());
    if (validFontSize) label.setFontSize(fontSize[5]);
    btn6.setCoords(280,215);
    btn6.setCoords1(450,255);
    my_lcd.draw(&btn6);

    btn1.setDisableAutoSize(false);
    btn2.setDisableAutoSize(false);
    btn3.setDisableAutoSize(false);
    btn4.setDisableAutoSize(false);
    btn5.setDisableAutoSize(false);
    btn6.setDisableAutoSize(false);

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
            label.setString("Previous");
            btn7.setCoords(35,278);
            btn7.setCoords1(190,308);
            my_lcd.draw(&btn7);
        }
        if (page<maxPage)
        {
            btn8.setDisableAutoSize(true);
            label.setFontSize(3);
            label.setString("Next");
            btn8.setCoords(290,278);
            btn8.setCoords1(440,308);
            my_lcd.draw(&btn8);
            btn8.setDisableAutoSize(false);
        }
    }

}

void drawNumInput (String titleNumInput, String unit)
{
    drawBackground();
    title.setDisableAutoSize(true);
    titleLabel.setString(titleNumInput.c_str()); // title
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    title.setDisableAutoSize(false);

    //NUMERIC BUTTONS//
    label.setString("1"); // Button number 1
    btn1.setCoords(40,155);
    btn1.setCoords1(100,205);
    btn1.setDisableAutoSize(false);
    my_lcd.draw(&btn1);

    label.setString("2"); // Button number 2
    btn2.setCoords(125,155);
    btn2.setCoords1(185,205);
    btn2.setDisableAutoSize(false);
    my_lcd.draw(&btn2);

    label.setString("3"); // Button number 3
    btn3.setCoords(210,155);
    btn3.setCoords1(270,205);
    btn3.setDisableAutoSize(false);
    my_lcd.draw(&btn3);

    label.setString("4"); // Button number 4
    btn4.setCoords(295,155);
    btn4.setCoords1(355,205);
    btn4.setDisableAutoSize(false);
    my_lcd.draw(&btn4);

    label.setString("5"); // Button number 5
    btn5.setCoords(380,155);
    btn5.setCoords1(440,205);
    btn5.setDisableAutoSize(false);
    my_lcd.draw(&btn5);

    label.setString("6"); // Button number 6
    btn6.setCoords(40,215);
    btn6.setCoords1(100,265);
    btn6.setDisableAutoSize(false);
    my_lcd.draw(&btn6);

    label.setString("7"); // Button number 7
    btn7.setCoords(125,215);
    btn7.setCoords1(185,265);
    btn7.setDisableAutoSize(false);
    my_lcd.draw(&btn7);

    label.setString("8"); // Button number 8
    btn8.setCoords(210,215);
    btn8.setCoords1(270,265);
    btn8.setDisableAutoSize(false);
    my_lcd.draw(&btn8);

    label.setString("9"); // Button number 9
    btn9.setCoords(295,215);
    btn9.setCoords1(355,265);
    btn9.setDisableAutoSize(false);
    my_lcd.draw(&btn9);

    label.setString("0"); // Button number 0
    btn10.setCoords(380,215);
    btn10.setCoords1(440,265);
    btn10.setDisableAutoSize(false);
    my_lcd.draw(&btn10);

    //AUXILIARY BUTTONS//
    label.setString("Delete"); // Button Delete
    btn11.setCoords(60,270);
    btn11.setCoords1(230,310);
    my_lcd.draw(&btn11);

    label.setString("OK"); // Button OK
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

/*void printBytes(void* ptr, int size)
{
    for(int i = 0;i<size;i++)
    {
        Serial.println((byte)ptr[i]);
    }
}*/

double getNumInput(String titleNumInput, String unit, double value)
{
    debug(String(F("getNumInput: "))+titleNumInput+F(": ")+value+unit);
    drawNumInput(titleNumInput,unit);
    char string[15];
    bool negative; // sign switch
    Label outputLabel(0,0,string,5,Color(0,0,0));
    Rectangle output(60,95,370,145,Color(),Color(255,255,255),&outputLabel);
    my_lcd.draw(&output);

    if(value>0)
    {
        string[0] = ' ';
        string[1] = '\0';
        negative=false;
    }
    else
    {
        string[0] = '\0';
        negative=true;
    }
    strcat(string,String(value,4).c_str());

    char exit=0; // exit switch
    byte len=strlen(string); // size of the string
    bool decimalDotPlaced = true;


    my_lcd.draw(&output);


    while(exit==0)
    {
        if (len<14) // + NULL
        {
            if(btn1.isPressed())
            {
                len++;
                strcat(string,"1");
                my_lcd.draw(&output);
                delay(200);
            }
            else if(btn2.isPressed())
            {
                len++;
                strcat(string,"2");
                my_lcd.draw(&output);
                delay(200);
            }
            else if(btn3.isPressed())
            {
                len++;
                strcat(string,"3");
                my_lcd.draw(&output);
                delay(200);
            }
            else if(btn4.isPressed())
            {
                len++;
                strcat(string,"4");
                my_lcd.draw(&output);
                delay(200);
            }
            else if(btn5.isPressed())
            {
                len++;
                strcat(string,"5");
                my_lcd.draw(&output);
                delay(200);
            }
            else if(btn6.isPressed())
            {
                len++;
                strcat(string,"6");
                my_lcd.draw(&output);
                delay(200);
            }
            else if(btn7.isPressed())
            {
                len++;
                strcat(string,"7");
                my_lcd.draw(&output);
                delay(200);
            }
            else if(btn8.isPressed())
            {
                len++;
                strcat(string,"8");
                my_lcd.draw(&output);
                delay(200);
            }
            else if(btn9.isPressed())
            {
                len++;
                strcat(string,"9");
                my_lcd.draw(&output);
                delay(200);
            }
            else if(btn10.isPressed())
            {
                len++;
                strcat(string,"0");
                my_lcd.draw(&output);
                delay(200);
            }
        }

        if(btn11.isPressed() && len>0)
        {
            if(string[len-1] == '.')
                decimalDotPlaced = false;
            if(len==2)
            {
                string[0] = ' ';
                negative = false;
            }
            string[len-1]='\0';
            len--;

            my_lcd.draw(&output);
            delay(200);
        }
        else if(backBtn.isPressed())
        {
            debug(F("Back button pressed"));
            exit=-1;
            delay(200);
        }
        else if(oKBtn.isPressed())
        {
            debug(F("Ok button pressed"));
            exit=1;
            delay(200);
        }
        else if(signBtn.isPressed())
        {
            negative=(!negative);
            if(!negative)
            {
                string[0]=' ';
            }
            else
            {
                string[0]='-';
            }
            my_lcd.draw(&output);
            delay(200);
        }
        if(dotBtn.isPressed() && !decimalDotPlaced)
        {
            if(string[len-1]>='0' && string[len-1]<= '9')
            {
                len++;
                strcat(string, ".");
                decimalDotPlaced = true;
                my_lcd.draw(&output);
                delay(200);
            }
        }
    }

    if (exit==1)
    {
        debug(String(F("getNumInput returned: "))+atof(string));
        return atof(string);
    }

    debug(F("getNumInput was cancelled"));
    return NAN;
}

// btn1 --> topLeft; btn2 --> centerLeft; btn3 --> bottomLeft; btn4 --> topRight; btn5 --> centerRight; btn6 --> bottomRight; btn7 --> Previous; btn8 --> Next; btn9 --> topHelp; btn10 --> centerHelp; btn11 --> bottomHelp
void draw6ButtonsLayout(String topLeftBtn1, String centerLeftBtn2, String bottomLeftBtn3, String topRightBtn4, String centerRightBtn5, String bottomRightBtn6, bool topHelpBtn9, bool centerHelpBtn10, bool bottomHelpBtn11)
{
    draw6ButtonsLayout(topLeftBtn1,centerLeftBtn2,bottomLeftBtn3,topRightBtn4,centerRightBtn5,bottomRightBtn6,topHelpBtn9,centerHelpBtn10,bottomHelpBtn11,NULL);
}

void setFontSizeArray(byte* fontSizeArray, byte tl, byte cl, byte bl, byte tr, byte cr, byte br)
{
    fontSizeArray[0] = tl;
    fontSizeArray[1] = cl;
    fontSizeArray[2] = bl;
    fontSizeArray[3] = tr;
    fontSizeArray[4] = cr;
    fontSizeArray[5] = br;
}

void setFontSizeArray(byte* fontSizeArray, byte tl, byte tr, byte bl, byte br)
{
    fontSizeArray[0] = tl;
    fontSizeArray[1] = tr;
    fontSizeArray[2] = bl;
    fontSizeArray[3] = br;
}

//Auxiliary functions

//Main Functions

void drawSplashScreen()
{
    Picture bigLogo(157,25,"PMWBL.bmp");
    my_lcd.draw(&bigLogo);
}

void drawStatusColors(bool wellPump, bool endPump, bool UVRelay, bool filterRelay, char well, char surfaceTank, char filteredTank, char purifiedTank, bool endTank) // false --> OFF, true -->ON, <0 --> LOW, = 0 --> Half, >0 --> FULL
{
    Color blue(81, 136, 223);
    Color white(0xFFFF);
    Color yellow(255,255,0);

    Rectangle rec1(80,247,89,252,white,white); // big rectangle under the valve
    //wellPump
    if(wellPump)
    {
        rec1.setMainColor(yellow);
        rec1.setSecondaryColor(yellow);
    }
    my_lcd.draw(&rec1);

    if(wellPump)
    {
        rec1.setMainColor(blue);
        rec1.setSecondaryColor(blue);
    }
    rec1.setCoords(82,120); // Tube up
    rec1.setCoords1(83,245);
    my_lcd.draw(&rec1);

    rec1.setCoords(82,118);// Tube right
    rec1.setCoords1(121,119);
    my_lcd.draw(&rec1);

    rec1.setCoords(120,118);// Tube down
    rec1.setCoords1(121,205);
    my_lcd.draw(&rec1);


    //well_low
    rec1.setMainColor(blue);
    rec1.setSecondaryColor(blue);
    rec1.setCoords(28,258);
    rec1.setCoords1(89,301);
    my_lcd.draw(&rec1);

    //well_high
    if(!well)
    {
        rec1.setMainColor(white);
        rec1.setSecondaryColor(white);
    }
    rec1.setCoords1(78,230); // Rectangle at the let of the valve
    rec1.setCoords(28,259);
    my_lcd.draw(&rec1);
    rec1.setCoords1(89,254); // Small Rectangle under valve
    rec1.setCoords(78,259);
    my_lcd.draw(&rec1);
    rec1.setCoords(85,230); // Small rectangle right of the tube
    rec1.setCoords1(89,245);
    my_lcd.draw(&rec1);
    rec1.setCoords(78,230); // Small rectangle left of the tube
    rec1.setCoords1(80,245);
    my_lcd.draw(&rec1);


    //SufaceTank
    Rectangle rec2(135,201,144,206,white,white);
    if(filterRelay)
    {
        rec2.setMainColor(yellow);
        rec2.setSecondaryColor(yellow);
    }
    my_lcd.draw(&rec2);

    //TubeSurfaceTank
    if(filterRelay)
    {
        rec2.setMainColor(blue);
        rec2.setSecondaryColor(blue);
    }
    rec2.setCoords(138,136); // Tube up
    rec2.setCoords1(139,199);
    my_lcd.draw(&rec2);
    rec2.setCoords(139,136); // Tube right
    rec2.setCoords1(156,137);
    my_lcd.draw(&rec2);


    //filter
    RoundRectangle recFilter(158,131,199,151,3,white,white);
    if(filterRelay)
    {
        recFilter.setMainColor(yellow);
        recFilter.setSecondaryColor(yellow);
    }
    my_lcd.draw(&recFilter);

    //TubeFilter
    if(filterRelay)
    {
        recFilter.setMainColor(blue);
        recFilter.setSecondaryColor(blue);
    }
    recFilter.setRadius(0);
    recFilter.setCoords(201,136); // Tube right
    recFilter.setCoords1(219,137);
    my_lcd.draw(&recFilter);
    recFilter.setCoords(218,136); // Tube down
    recFilter.setCoords1(219,215);
    my_lcd.draw(&recFilter);


    //surfaceTank_low
    rec2.setCoords(99, 211);
    rec2.setCoords1(144, 219);
    rec2.setMainColor(blue);
    rec2.setSecondaryColor(blue);
    my_lcd.draw(&rec2);

    //surfaceTank_medium
    if(surfaceTank == -1)
    {
        rec2.setMainColor(white);
        rec2.setSecondaryColor(white);
    }
    rec2.setCoords(99,208); // Small Rectangle under valve
    rec2.setCoords1(144,211);
    my_lcd.draw(&rec2);
    rec2.setCoords(99,180); // Rectangle at the left of the valve
    rec2.setCoords1(133,208);
    my_lcd.draw(&rec2);
    rec2.setCoords(133,180); // Small Rectangle at the left of the tube
    rec2.setCoords1(136,199);
    my_lcd.draw(&rec2);
    rec2.setCoords(141,180); // Small Rectangle at the right of the tube
    rec2.setCoords1(144,199);
    my_lcd.draw(&rec2);

    //surfaceTank_high
    if(surfaceTank == 0)
    {
        rec2.setMainColor(white);
        rec2.setSecondaryColor(white);
    }
    rec2.setCoords(99,153); // Big Rectangle at the top right of the tube
    rec2.setCoords1(136,180);
    my_lcd.draw(&rec2);
    rec2.setCoords(141,153); // Rectangle at the top left of the tube
    rec2.setCoords1(144,180);
    my_lcd.draw(&rec2);


    //UVPump
    Rectangle rec3(213,213,258,219,white,white);
    if(UVRelay)
    {
        rec3.setMainColor(yellow);
        rec3.setSecondaryColor(yellow);
    }
    rec3.setCoords(249,203);
    rec3.setCoords1(258,208);
    my_lcd.draw(&rec3);

    //TubeUVPump
    if(UVRelay)
    {
        rec3.setMainColor(blue);
        rec3.setSecondaryColor(blue);
    }
    rec3.setCoords(253,148); // Tube up
    rec3.setCoords1(254,201);
    my_lcd.draw(&rec3);
    rec3.setCoords(253,148); // Tube right
    rec3.setCoords1(278,149);
    my_lcd.draw(&rec3);
    rec3.setCoords(277,149); // Tube down
    rec3.setCoords1(278,199);
    my_lcd.draw(&rec3);

    //UV
    if(UVRelay)
    {
        recFilter.setMainColor(yellow);
        recFilter.setSecondaryColor(yellow);
    }
    else
    {
        recFilter.setMainColor(white);
        recFilter.setSecondaryColor(white);
    }
    recFilter.setRadius(2);
    recFilter.setCoords(272,201);
    recFilter.setCoords1(323,210);
    my_lcd.draw(&recFilter);

    //TubeUV
    recFilter.setRadius(0);
    if(UVRelay)
    {
        recFilter.setMainColor(blue);
        recFilter.setSecondaryColor(blue);
    }
    else
    {
        recFilter.setMainColor(white);
        recFilter.setSecondaryColor(white);
    }
    recFilter.setCoords(317,148); // Tube up
    recFilter.setCoords1(318,199);
    my_lcd.draw(&recFilter);
    recFilter.setCoords(318,148); // Tube right
    recFilter.setCoords1(344,149);
    my_lcd.draw(&recFilter);
    recFilter.setCoords(343,149); // Tube down
    recFilter.setCoords1(344,219);
    my_lcd.draw(&recFilter);


    //FilteredTank_low
    rec3.setCoords(213,213);
    rec3.setCoords1(258,219);
    rec3.setMainColor(blue);
    rec3.setSecondaryColor(blue);
    my_lcd.draw(&rec3);

    //FilteredTank_medium
    if(filteredTank == -1)
    {
        rec3.setMainColor(white);
        rec3.setSecondaryColor(white);
    }
    rec3.setCoords(213,210); // Large rectangle under valve
    rec3.setCoords1(258,213);
    my_lcd.draw(&rec3);
    rec3.setCoords(213,180); // Big bottom rectangle under valve
    rec3.setCoords1(247,210);
    my_lcd.draw(&rec3);
    rec3.setCoords(247,180); // Large bottom rectangle at the left of the tube
    rec3.setCoords1(251,201);
    my_lcd.draw(&rec3);
    rec3.setCoords(256,180); // Large bottom rectangle at the right of the tube
    rec3.setCoords1(258,201);
    my_lcd.draw(&rec3);

    //FilteredTank_high
    if(filteredTank == 0)
    {
        rec3.setMainColor(white);
        rec3.setSecondaryColor(white);
    }
    rec3.setCoords(213,163); // Big top rectangle under valve
    rec3.setCoords1(247,180);
    my_lcd.draw(&rec3);
    rec3.setCoords(247,163); // Large top rectangle at the left of the tube
    rec3.setCoords1(251,180);
    my_lcd.draw(&rec3);
    rec3.setCoords(256,163); // Large top rectangle at the right of the tube
    rec3.setCoords1(258,180);
    my_lcd.draw(&rec3);


    //EndPump
    Rectangle rec4(339,213,379,219,white,white);

    if(endPump)
    {
        rec4.setMainColor(yellow);
        rec4.setSecondaryColor(yellow);
    }
    rec4.setCoords(370,203);
    rec4.setCoords1(379,208);
    my_lcd.draw(&rec4);

    //TubeEndPump
    if(endPump)
    {
        rec4.setMainColor(blue);
        rec4.setSecondaryColor(blue);
    }
    rec4.setCoords(374,81); // Tube up
    rec4.setCoords1(375,201);
    my_lcd.draw(&rec4);
    rec4.setCoords(375,81); // Tube right
    rec4.setCoords1(402,82);
    my_lcd.draw(&rec4);
    rec4.setCoords(401,81); // Tube down
    rec4.setCoords1(402,136);
    my_lcd.draw(&rec4);


    //PurifiedTank_low
    rec4.setCoords(339,213);
    rec4.setCoords1(379,219);
    rec4.setMainColor(blue);
    rec4.setSecondaryColor(blue);
    my_lcd.draw(&rec4);

    //PurifiedTank_medium
    if(purifiedTank == -1)
    {
        rec4.setMainColor(white);
        rec4.setSecondaryColor(white);
    }
    rec4.setCoords(339,210); // Large rectangle under valve
    rec4.setCoords1(379,213);
    my_lcd.draw(&rec4);
    rec4.setCoords(339,180); // Big rectangle bottom left of the tube
    rec4.setCoords1(368,210);
    my_lcd.draw(&rec4);
    rec4.setCoords(368,180); // Large rectangle bottom left of the tube
    rec4.setCoords1(372,201);
    my_lcd.draw(&rec4);
    rec4.setCoords(377,180); // Large rectangle bottom right of the tube
    rec4.setCoords1(379,201);
    my_lcd.draw(&rec4);

    //PurifiedTank_high
    if(purifiedTank == 0)
    {
        rec4.setMainColor(white);
        rec4.setSecondaryColor(white);
    }
    rec4.setCoords(339,165); // Big rectangle top left of the tube
    rec4.setCoords1(368,180);
    my_lcd.draw(&rec4);
    rec4.setCoords(368,165); // Large rectangle top left of the tube
    rec4.setCoords1(372,180);
    my_lcd.draw(&rec4);
    rec4.setCoords(377,165); // Large rectangle top right of the tube
    rec4.setCoords1(379,180);
    my_lcd.draw(&rec4);


    //EndTank_low
    Rectangle rec5(396,135,452,157,blue,blue);// Big rectangle under valve
    my_lcd.draw(&rec5);

    //TubeEndTank
    rec5.setCoords(427,157); // Rectangle exit tube down
    rec5.setCoords1(430,182);
    my_lcd.draw(&rec5);
    rec5.setCoords(427,183); // Rectangle exit tube right
    rec5.setCoords1(465,186);
    my_lcd.draw(&rec5);


    //EndTank_high
    if(!endTank)
    {
        rec5.setMainColor(white);
        rec5.setSecondaryColor(white);
    }
    rec5.setCoords(396,92); // Big rectangle top of the tank
    rec5.setCoords1(452,135);
    my_lcd.draw(&rec5);
}

void drawStatusBackgroundPhoto()
{
    Rectangle backRec(15,70,420,320, Color(255,255,255),Color(255,255,255));
    my_lcd.draw(&backRec);
    backRec.setCoords(160,62);
    backRec.setCoords1(260,70);
    my_lcd.draw(&backRec);

    Rectangle rec (56,200,62,220, Color(0,0,0));
    my_lcd.draw(&rec);
    //rectangle around the page
    RoundRectangle Rrec( 15,75,465,302,1, Color(0,0,0));
    my_lcd.draw(&Rrec);

    //rectangle around the Menu and ON/OFF buttons
    Rrec.setCoords(15,220);
    Rrec.setCoords1(465,302);
    my_lcd.draw(&Rrec);
    Rrec.setCoords(117,220);
    Rrec.setCoords1(435,302);
    my_lcd.draw(&Rrec);

    //SolarPanel
    Line line(64,100,80,200,Color(0,0,0));
    my_lcd.draw(&line);
    line.setCoords(84,100);
    line.setCoords1(100,200);
    my_lcd.draw(&line);
    line.setCoords(84,100);
    line.setCoords1(100,200);
    my_lcd.draw(&line);
    line.setCoords(44,100);
    line.setCoords1(60,200);
    my_lcd.draw(&line);
    line.setCoords(24,100);
    line.setCoords1(40,200);
    my_lcd.draw(&line);
    line.setCoords(4,100);
    line.setCoords1(20,200);
    my_lcd.draw(&line);

    line.setCoords(20,200);
    line.setCoords1(100,200);
    my_lcd.draw(&line);
    line.setCoords(4,100);
    line.setCoords1(84,100);
    my_lcd.draw(&line);
    line.setCoords(4,120);
    line.setCoords1(92,120);
    my_lcd.draw(&line);
    line.setCoords(4,140);
    line.setCoords1(90,140);
    my_lcd.draw(&line);
    line.setCoords(4,160);
    line.setCoords1(94,160);
    my_lcd.draw(&line);
    line.setCoords(17,180);
    line.setCoords1(96,180);
    my_lcd.draw(&line);

    rec.setCoords(79,246);
    rec.setCoords1(90,253);
    my_lcd.draw(&rec);

    Rectangle aux(0,0,14,270,Color(255,255,255),Color(255,255,255));
    my_lcd.draw(&aux);

    //wellPump
    my_lcd.draw(&rec); // Pump

    Rrec.setCoords(81,119); // Tube up
    Rrec.setCoords1(84,246);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(81,117);// Tube right
    Rrec.setCoords1(122,120);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(119,117);// Tube down
    Rrec.setCoords1(122,153);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(27,220);// well
    Rrec.setCoords1(90,302);
    my_lcd.draw(&Rrec);

    //Filter
    Rrec.setCoords(200,135);// tube right
    Rrec.setCoords1(220,138);
    my_lcd.draw(&Rrec);

    Rrec.setRadius(4);
    Rrec.setCoords(157,130);// filter
    Rrec.setCoords1(200,152);
    my_lcd.draw(&Rrec);

    Rrec.setRadius(6);
    Rrec.setCoords(157,152);// filter
    Rrec.setCoords1(200,220);
    my_lcd.draw(&Rrec);
    Rrec.setRadius(1);

    Rrec.setCoords(217,135);// tube down
    Rrec.setCoords1(220,164);
    my_lcd.draw(&Rrec);

    //SurfaceTank
    rec.setCoords(134,200);// valve
    rec.setCoords1(145,207);
    my_lcd.draw(&rec);

    Rrec.setCoords(137,135);// tube up
    Rrec.setCoords1(140,200);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(138,135);// tube right
    Rrec.setCoords1(157,138);
    my_lcd.draw(&Rrec);

    rec.setCoords(98,152);//tank
    rec.setCoords1(145,220);
    my_lcd.draw(&rec);

    //filtered tank
    rec.setCoords(212,162);// tank
    rec.setCoords1(259,220);
    my_lcd.draw(&rec);

    rec.setCoords(212,162);// valve
    rec.setCoords1(259,220);
    my_lcd.draw(&rec);

    Rrec.setCoords(252,147);// tube up
    Rrec.setCoords1(255,202);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(252,147);// tube right
    Rrec.setCoords1(279,150);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(276,148);//tube down
    Rrec.setCoords1(279,168);
    my_lcd.draw(&Rrec);

    //UV
    Rrec.setCoords(252,147);// tube right
    Rrec.setCoords1(255,202);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(252,147);// tube up
    Rrec.setCoords1(279,150);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(276,148);// tube right
    Rrec.setCoords1(279,200);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(271,200);//tube down
    Rrec.setCoords1(324,211);
    my_lcd.draw(&Rrec);

    //UV_2
    Rrec.setCoords(316,147);// tube up
    Rrec.setCoords1(319,200);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(317,147);// tube right
    Rrec.setCoords1(345,150);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(342,148);// tube down
    Rrec.setCoords1(345,165);
    my_lcd.draw(&Rrec);

    rec.setCoords(248,202);// UV
    rec.setCoords1(259,209);
    my_lcd.draw(&rec);

    Line legs(272,220,292,210,Color(0,0,0));
    my_lcd.draw(&legs);
    Line legs1(302,210,322,220,Color(0,0,0));
    my_lcd.draw(&legs1);

    //PurifiedTank

    Rrec.setCoords(338,164);// tank
    Rrec.setCoords1(380,220);
    my_lcd.draw(&Rrec);

    rec.setCoords(369,202);// valve
    rec.setCoords1(380,209);
    my_lcd.draw(&rec);

    Rrec.setCoords(373,204);// tube up - endTank
    Rrec.setCoords1(376,80);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(374,80); //tube right - endTank
    Rrec.setCoords1(403,83);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(400,80); //tube down - endTank
    Rrec.setCoords1(403,109);
    my_lcd.draw(&Rrec);

    //End tank
    Rrec.setCoords(426,156);// tube down
    Rrec.setCoords1(431,183);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(426,182);// tube right
    Rrec.setCoords1(465,187);
    my_lcd.draw(&Rrec);

    rec.setCoords(395,91);//tank
    rec.setCoords1(453,158);
    my_lcd.draw(&rec);
}

void drawStatusBackground(bool dontFillScreen)
{
    if(!dontFillScreen)
        my_lcd.Fill_Screen(0xFFFF);

    //Label loading(165,85,"Loading...",3,Color(0,70,200));
    //my_lcd.draw(&loading);

    titleLabel.setString("Status"); // Title
    my_lcd.draw(&title);
    Picture logoPhoto(400,10,"PMWSL.bmp"); // logo
    my_lcd.draw(&logoPhoto);


    //Picture statusBackground(14,74,"schArd.bmp"); //Using p
    //my_lcd.draw(&statusBackground);

    drawStatusBackgroundPhoto();

    //Small logo
    btn1.setDisableAutoSize(true);
    label.setFontSize(2);
    label.setString("Menu"); // Label Menu
    btn1.setCoords(135,234);
    btn1.setCoords1(260,290);
    my_lcd.draw(&btn1);
    btn1.setDisableAutoSize(false);
}

void drawStatusBackground()
{
    drawStatusBackground(false);
}

// Draw voltage & amount of purified water
void drawStatusForeground(const char* voltage, const char* waterAmount)//TODO add water levels & other indicators
{
    debug("Voltage: " + String(voltage) + "\tWater amount: " + waterAmount);

    label.setString(voltage);
    rectangle.setCoords(20, 115);
    rectangle.setCoords1(70, 135);
    my_lcd.draw(&rectangle);

    label.setString(waterAmount);
    rectangle.setCoords(400, 195);
    rectangle.setCoords1(440, 215);
    my_lcd.draw(&rectangle);

    btn2.setDisableAutoSize(true);
    label.setFontSize(2);
    btn2.setCoords(300,234);
    btn2.setCoords1(420,290);
    if (mainSwitchSt < 0) // ERROR
    {
        label.setString("FAILURE");
        btn2.setSecondaryColor(Color(239, 127, 26));
    }
    else if(mainSwitchSt == 0) // OFF
    {
        label.setString("OFF");
        btn2.setSecondaryColor(Color(176, 54, 20));
    }
    else // ON
    {
        label.setString("ON");
        btn2.setSecondaryColor(Color(20, 150, 44));
    }
    my_lcd.draw(&btn2);
    btn2.setSecondaryColor(Color(255, 255, 255));
    btn2.setDisableAutoSize(false);

    drawStatusColors(0,0,0,0,0,0,0,0,0);
}

// Buttons mapped to: btn1 --> Settings, btn2 --> Help, btn3 --> Engineering Mode, btn4 --> Extra Functions
void drawMenu()
{
    //Title Menu
    titleLabel.setString("Menu");
    my_lcd.draw(&title);
    //Layout4Buttons
    byte fontSize[4];
    setFontSizeArray(fontSize,2,2,2,2);
    draw4ButtonsLayout(F("Settings"),F("Help"),F("Engineering Mode"),F("Extra functions"),fontSize);
}

// Buttons mapped to: btn1 --> Electricity, btn2 --> Water, btn3 --> Interface, btn4 --> Temperature
void drawSettings()
{
    //Title Menu
    titleLabel.setString("Settings");
    my_lcd.draw(&title);
    //Layout4Buttons
    byte fontSize[4];
    setFontSizeArray(fontSize,2,2,2,2);
    draw4ButtonsLayout(F("Electricity"),F("Water"),F("Interface"),F("Temperature"),fontSize);
}

void drawElectricity() // TODO get settings real value
{
    //Title electricity
    titleLabel.setString("Electricity Settings");
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    switch (page)
    {
        case 1:
            setFontSizeArray(fontSizes, 1,1,1,2,2,2);
            draw6ButtonsLayout(F("Start Charging Voltage"),F("Stop Charging Voltage"),F("UV light est. Current"),String(STARTCHARGINGVOLTAGE)+F("V"),String(STOPCHARGINGVOLTAGE)+F("V"),String(ESTIMATEDUVAMPERAGE)+F("A"),true,true,true,fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes, 1,1,1,2,2,2);
            draw6ButtonsLayout(F("Start Working Voltage"),F("Stop Working Voltage"),F("AC Inverter Frequency"),String(STARTWORKINGVOLTAGE)+F("V"),String(STOPWORKINGVOLTAGE)+F("V"),String(ACFREQUENCY)+F("Hz"),true,true,true, fontSizes);
            break;
        case 3:
            setFontSizeArray(fontSizes, 1,1,1,2,2,2);
            draw6ButtonsLayout(F("AC Ammeter Sensitivity"),F("AC Ammeter Zero"),F("DC Ammeter Sensitivity"),String(ACAMPSENSITIVITY, 4),String(ACAMPZERO,4),String(DCAMPSENSITIVITY,4),true,true,true,fontSizes);
            break;
        case 4:
            setFontSizeArray(fontSizes, 1,1,1,2,1,1);
            draw6ButtonsLayout(F("DC Ammeter Zero"),"","",String(DCAMPZERO,4),"","",true,false,false,fontSizes);
            break;
    }
}

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

void drawTemperature() {
    titleLabel.setString("Temperature");
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    switch (page) 
    {
        case 1:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(F("Temp. Refresh Rate "), F("System Stop Temp."), F("PSU Fan Start Temp."), String(((double)TEMPCHECKTIME)/1000) + "s", String((double)STOPWORKINGTEMP) + "C", String((double)STARTPSUTEMP) + "C",
                               true, true, true, fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes, 1, 1, 1, 2, 2, 2);
            draw6ButtonsLayout(F("PSU Fan Stop Temp."), F("Case Fan Start Temp."), F("Case Fan Stop Temp."), String((double)STOPPSUTEMP)+"C", String((double)STARTCASETEMP)+"C",
                               String((double)STOPCASETEMP)+"C", true, true, true, fontSizes);
            break;
    }
}

void drawWater()
{
    titleLabel.setString("Water Settings");
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    switch (page) 
    {
        case 1:
            setFontSizeArray(fontSizes,1,1,1,2,2,2);
            draw6ButtonsLayout(F("Well Pump max time ON"),F("UV Pump max time ON"),F("End Pump max time ON"), String(((double)WELLPUMPTIMEOUT)/1000)+F("s"),String(((double)UVPUMPTIMEOUT)/1000)+F("s"), String(((double)ENDPUMPTIMEOUT)/1000)+F("s"), true, true, true, fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes,1,1,1,2,2,2);
            draw6ButtonsLayout(F("Filter max time ON"),F("UV Pump flow"),"", String(((double)FILTERTIMEOUT)/1000)+F("s"),String(UVPUMPFLOW)+F("L/H"), "", true, true, true, fontSizes);
            break;
    }
}

void drawExtraFunctions()
{
    titleLabel.setString("Extra Functions");
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    setFontSizeArray(fontSizes,1,1,1,2,2,2);
    draw6ButtonsLayout(F("AC Power Supply"),F("DC Power Supply"),F("Install Wizard"), "ON/OFF","ON/OFF", "Start", true, true, true, fontSizes);
}

void clickStatus()
{
    if(btn1.isPressed())
    {
        debug(F("Button MENU pressed"));
        changeStatus(LOADMENU);
    }
    else if(btn2.isPressed())
    {
        if(mainSwitchSt == ON)
        {
            debug(F("Button OFF pressed"));
            mainSwitchSt = OFF; // TODO send off command
            drawStatusForeground("15.4V", "320L");
        }
        else if(mainSwitchSt == OFF)
        {
            debug(F("Button ON pressed"));
            mainSwitchSt = ON; // TODO send on command
            drawStatusForeground("15.4V", "320L");
        }
        else if(mainSwitchSt < 0)
        {
            debug(F("Button FAILURE pressed")); // TODO Draw ERROR message
        }
        delay(500);
    }
}

void clickMenu()
{
    if(btn1.isPressed()) //Settings
    {
        debug(F("Settings button pressed"));
        changeStatus(LOADSETTINGS);
    }
    else if(btn2.isPressed()) //Help
    {
        debug(F("Help button pressed"));
        changeStatus(LOADHELP);
    }
    else if(btn3.isPressed()) //Engineering Mode
    {
        debug(F("Engineering mode button pressed"));
        changeStatus(LOADENGINEERINGMODE);
    }
    else if(btn4.isPressed()) //Extra Functions
    {
        debug(F("Extra functions button pressed"));
        changeStatus(LOADEXTRAFUNCTIONS);
    }
}

void clickSettings()
{
    if(btn1.isPressed())
    {
        debug(F("Electricity button pressed"));
        changeStatus(LOADELECTRICITY);
    }

    else if(btn2.isPressed())
    {
        debug(F("Water button pressed")); // Go to LOADWATER
        changeStatus(LOADWATER);
    }
    else if(btn3.isPressed()) // Go to LOADINTERFACE
    {
        debug(F("Interface button pressed"));
        changeStatus(LOADINTERFACE);
    }
    else if(btn4.isPressed())
    {
        changeStatus(LOADTEMPERATURE);
    }
}

void clickElectricity()
{
    double tempVal;
    if(btn4.isPressed())
    {
        switch (page)
        {
            case 1: // Start charging voltage
                tempVal = getNumInput("Start charging Voltage","V",STARTCHARGINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if(STOPWORKINGVOLTAGE<tempVal && tempVal<STOPCHARGINGVOLTAGE)
                    {
                        debug(String(F("STARTCHARGINGVOLTAGE UPDATED: "))+STARTCHARGINGVOLTAGE+String(F(" --> "))+tempVal);
                        STARTCHARGINGVOLTAGE = tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
            break;

            case 2: //page 2
                tempVal = getNumInput("Start Working Voltage","V",STARTWORKINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if(STARTCHARGINGVOLTAGE<tempVal && tempVal<STOPCHARGINGVOLTAGE)// STARTCHARGINGVOLTAGE < STARTWORKINGVOLTAGE < STOPCHARGINGVOLTAGE
                    {
                        debug(String(F("STARTCHARGINGVOLTAGE UPDATED: "))+STARTWORKINGVOLTAGE+String(F(" --> "))+tempVal);
                        STARTWORKINGVOLTAGE = tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
            break;

            case 3:
                tempVal = getNumInput("AC Ammeter Sensitivity","",ACAMPSENSITIVITY);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(String(F("ACAMPSENSITIVITY UPDATED: "))+ACAMPSENSITIVITY+String(F(" --> "))+tempVal);
                    ACAMPSENSITIVITY = tempVal;
                    // TODO send new setting

                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
            break;

            case 4:
                tempVal = getNumInput("DC Ammeter Zero","",DCAMPZERO);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(String(F(" UPDATED: DCAMPZERO"))+DCAMPZERO+String(F(" --> "))+tempVal);
                    DCAMPZERO = tempVal;
                    // TODO send new setting

                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
            break;
        }

    }
    else if(btn5.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput("Stop Charging Voltage","V",STOPCHARGINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if(STARTCHARGINGVOLTAGE+1<tempVal && tempVal<MAXCAPACITORSALLOWEDVOLTAGE)// STARTCHARGINGVOLTAGE+1 < STOPCHARGINGVOLTAGE < MAXCAPACITORSALLOWEDVOLTAGE
                    {
                        debug(String(F("STOPCHARGINGVOLTAGE UPDATED: "))+STOPCHARGINGVOLTAGE+String(F(" --> "))+tempVal);
                        STOPCHARGINGVOLTAGE = tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
            break;

            case 2:
                tempVal = getNumInput("Stop Working Voltage","V",STOPWORKINGVOLTAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if(MINSYSTEMALLOWEDVOLTAGE<tempVal && tempVal<STARTCHARGINGVOLTAGE-1)// MINSYSTEMALLOWEDVOLTAGE < STOPWORKINGVOLTAGE < STARTCHARGINGVOLTAGE-1
                    {
                        debug(String(F("STOPWORKINGVOLTAGE UPDATED: "))+STOPWORKINGVOLTAGE+String(F(" --> "))+tempVal);
                        STOPWORKINGVOLTAGE = tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
            break;

            case 3:
                tempVal = getNumInput("AC Ammeter Zero","",ACAMPZERO);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(String(F("ACAMPZERO UPDATED: "))+ACAMPZERO+String(F(" --> "))+tempVal);
                    ACAMPZERO = tempVal;
                    // TODO send new setting

                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
            break;
        }
    }
    else if(btn6.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput("UV light est. Current","A",ESTIMATEDUVAMPERAGE);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if(0<tempVal && tempVal<MAXUVAMPERAGE)//0 < ESTIMATEDUVAMPERAGE < MAXUVAMPERAGE
                    {
                        debug(String(F("ESTIMATEDUVAMPERAGE UPDATED: "))+ESTIMATEDUVAMPERAGE+String(F(" --> "))+tempVal);
                        ESTIMATEDUVAMPERAGE = tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
            break;

            case 2:
                tempVal = getNumInput("AC Inverter Frequency","Hz",ACFREQUENCY);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if(50<tempVal && tempVal<60)// 50 <= ACFREQUENCY <= 60
                    {
                        debug(String(F("ACFREQUENCY UPDATED: "))+ACFREQUENCY+String(F(" --> "))+tempVal);
                        ACFREQUENCY = tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
            break;

            case 3:
                tempVal = getNumInput("DC Ammeter Sensitivity","",DCAMPSENSITIVITY);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(String(F("DCAMPSENSITIVITY UPDATED: "))+DCAMPSENSITIVITY+String(F(" --> "))+tempVal);
                    DCAMPSENSITIVITY = tempVal;
                    // TODO send new setting
                }
                changeStatus(LOADPAGEELECTRICITY); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
            break;
        }
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

void clickWater()
{
    double tempVal;
    if(btn4.isPressed())
    {
        switch (page)
        {
            case 1:
                tempVal = getNumInput("Well Pump max time on","s",WELLPUMPTIMEOUT);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if( 0 < WELLPUMPTIMEOUT)// 0 < WELLPUMPTIMEOUT
                    {
                        debug(String(F("WELLPUMPTIMEOUT UPDATED: "))+WELLPUMPTIMEOUT+String(F(" --> "))+tempVal);
                        WELLPUMPTIMEOUT = (long)tempVal*1000;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
            break;
            case 2:
                tempVal = getNumInput("Filter max time on","s",FILTERTIMEOUT);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if( 0 < FILTERTIMEOUT)// 0 < FILTERTIMEOUT
                    {
                        debug(String(F("FILTERTIMEOUT UPDATED: "))+FILTERTIMEOUT+String(F(" --> "))+tempVal);
                        FILTERTIMEOUT = (long)tempVal*1000;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
            break;
       }
    }

    else if(btn5.isPressed()){
        switch (page)
        {
            case 1:
                tempVal = getNumInput("UV Pump max time on","s",UVPUMPTIMEOUT);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if( 0 < UVPUMPTIMEOUT)// 0 < UVPUMPTIMEOUT
                    {
                        debug(String(F("UVPUMPTIMEOUT UPDATED: "))+UVPUMPTIMEOUT+String(F(" --> "))+tempVal);
                        UVPUMPTIMEOUT = (long)tempVal*1000;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
            break;

            case 2: //TODO: por hacer
                tempVal = getNumInput("UV Pump flow","L/H",UVPUMPFLOW);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    debug(String(F("UVPUMPFLOW UPDATED: "))+UVPUMPFLOW+String(F(" --> "))+tempVal);
                    UVPUMPFLOW = (long)tempVal;
                    // TODO send new setting
                }
                changeStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
            break;
        }
    }
    else if(btn6.isPressed()){
        switch (page)
        {
            case 1:
                tempVal = getNumInput("End Pump max time on","s",ENDPUMPTIMEOUT);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if( 0 < ENDPUMPTIMEOUT)// 0 < ENDPUMPTIMEOUT
                    {
                        debug(String(F("ENDPUMPTIMEOUT UPDATED: "))+ENDPUMPTIMEOUT+String(F(" --> "))+tempVal);
                        ENDPUMPTIMEOUT = (long)tempVal*1000;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGEWATER); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
            break;
        }
    }

}

void clickTemperature()
{
    if (btn4.isPressed())
    {
        switch (page)
        {
            case 1:{ // Temp. Refresh Rate
                double tempVal = getNumInput("Temp. Refresh Rate", "s", TEMPCHECKTIME);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0)
                    {
                        debug(String(F("TEMPCHECKTIME UPDATED: ")) + TEMPCHECKTIME + String(F(" --> ")) +
                              tempVal);
                        TEMPCHECKTIME = tempVal * 1000;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;}
            case 2:{ //PSU Fan Stop Temp.
                double tempVal = getNumInput("PSU Fan Stop Temp.", "C", STOPPSUTEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal < STARTPSUTEMP)
                    {
                        debug(String(F("STOPPSUTEMP UPDATED: ")) + STOPPSUTEMP + String(F(" --> ")) +
                              tempVal);
                        STOPPSUTEMP = (double)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;}
        }
    }

    else if (btn5.isPressed())
    {
        switch (page)
        {
            case 1:{ // System Stop Temp.
                double tempVal = getNumInput("Temp. Refresh Rate", "C", STOPWORKINGTEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal>STARTPSUTEMP && tempVal>STARTCASETEMP)
                    {
                        debug(String(F("STOPWORKINGTEMP UPDATED: ")) + STOPWORKINGTEMP + String(F(" --> ")) +
                              tempVal);
                        STOPWORKINGTEMP = (double)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;}

            case 2:{ // Case Fan Start Temp.
                double tempVal = getNumInput("Case Fan Start Temp.", "C", STARTCASETEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0  && tempVal > STOPCASETEMP  && tempVal < STOPWORKINGTEMP)
                    {
                        debug(String(F("STARTCASETEMP UPDATED: ")) + STARTCASETEMP + String(F(" --> ")) +
                              tempVal);
                        STARTCASETEMP = (double)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;}
        }
    }

    else if (btn6.isPressed())
    {
        switch (page)
        {
            case 1:{ // PSU Fan Start Temp.
                double tempVal = getNumInput("PSU Fan Start Temp.", "C", STARTPSUTEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0  && tempVal > STOPPSUTEMP  && tempVal < STOPWORKINGTEMP)
                    {
                        debug(String(F("STARTPSUTEMP UPDATED: ")) + STARTPSUTEMP + String(F(" --> ")) +
                              tempVal);
                        STARTPSUTEMP = (double)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;}

            case 2:{ //Case Fan Stop Temp.
                double tempVal = getNumInput("Case Fan Stop Temp.", "C", STOPCASETEMP);
                if (!isnan(tempVal)) // if getNumInput was not cancelled
                {
                    if (tempVal > 0 && tempVal < STARTCASETEMP)
                    {
                        debug(String(F("STOPPSUTEMP UPDATED: ")) + STOPCASETEMP + String(F(" --> ")) +
                              tempVal);
                        STOPCASETEMP = (double)tempVal;
                        // TODO send new setting
                    }
                }
                changeStatus(LOADPAGETEMPERATURE); // reload page with new config value
                drawBackground(); // to print again the page after calling getNumInput, we need to draw the background too
                break;}
        }
    }

}

void clickExtraFunctions()
{
    /*if(btnx.isPressed())
    {
        switch (page)
        {
            case 1:
            changeStatus(XXXXX);
            break;
            case x:
                ...
        }
    }*/
}

//Main Functions

void setup()
{
#if DEBUG
    Serial.begin(115200);
    delay(200);
    Serial.println(F("Connected"));
    delay(50);
#endif
    my_lcd.set_sd_cs(53);
    pinMode(13,INPUT);
    pinMode(12,INPUT);
    pinMode(11,INPUT);
    pinMode(10,INPUT);

    my_lcd.Init_LCD();
    setRotation(ROTATION);

    //my_lcd.Fill_Screen(0);
    my_lcd.Fill_Screen(Color(255,255,255).to565());

    //todo Test code after this line

    //while (true); // TODO delete or comment this

    //todo Test code before this line

#if DEBUG
    Serial.println(F("\nSetup Done\n"));
    delay(50);
#endif
}


bool sw = true; // todo delete this
void loop()
{
    switch (screenStatus)
    {
        case BOOTING:
            drawSplashScreen();
            // Perform other boot stuff after this line
            delay(1000);
            // Perform other boot stuff before this line
            sw = true; // todo delete this
            drawStatusBackground(true);
            changeStatus(STATUS);
            break;

        case LOADSTATUS:
            sw = true; // todo delete this
            drawStatusBackground();
            changeStatus(STATUS);
            break;

        case STATUS:
            if(sw) // todo delete this (change condition to update info labels)
            {
                drawStatusForeground("15.4V", "320L");
                sw = false; // todo delete this
            }
            else
            {
                clickStatus();
            }
            break;

        case LOADMENU:
            drawBackground();
            drawMenu();
            changeStatus(MENU);
            break;

        case MENU:
            if(backBtn.isPressed()) // Go to LOADSTATUS
            {
                debug(F("Back button pressed"));
                changeStatus(LOADSTATUS);
            }
            else
            {
                clickMenu();
            }
            break;

        case LOADSETTINGS:
            drawBackground();
            drawSettings();
            changeStatus(SETTINGS);
            break;

        case SETTINGS:
            if(backBtn.isPressed()) // Go to LOADMENU
            {
                debug(F("Back button pressed"));
                changeStatus(LOADMENU);
            }
            else
            {
                clickSettings();
            }
            break;
        
        case LOADELECTRICITY:
            page = 1;
            maxPage = 4;
            drawBackground();
        case LOADPAGEELECTRICITY:
            debug(String(F("Loading page "))+page+" / "+maxPage);
            drawElectricity();
            changeStatus(ELECTRICITY);
            break;
        
        case ELECTRICITY:
            if(backBtn.isPressed()) // Go to LOADSETTINGS
            {
                debug(F("Back button pressed"));
                changeStatus(LOADSETTINGS);
            }
            else if(page>1&&btn7.isPressed()) // Previous
            {
                debug(F("Previous button pressed"));
                page--;
                changeStatus(LOADPAGEELECTRICITY);
            }
            else if(page<maxPage&&btn8.isPressed()) // Next
            {
                debug(F("Next button pressed"));
                page++;
                changeStatus(LOADPAGEELECTRICITY);
            }
            else
                clickElectricity();
            break;
        
        case LOADINTERFACE:
            page = 1;
            maxPage = 2;
            drawBackground();
        
        case LOADPAGEINTERFACE:
            // in this case you draw the interface
            debug(String(F("Loading page "))+page+" / "+maxPage);
            drawInterface();
            changeStatus(INTERFACE);
            break;
        
        case INTERFACE:
            if(backBtn.isPressed())
            {
                debug(F("Back button pressed"));
                changeStatus(LOADSETTINGS);
                // if back button is pressed you go to the previous page, so you start uploading the settings page
            }
            else if(page<maxPage&&btn8.isPressed()) // Next page
            {
                debug(F("Next page button pressed"));
                page++;
                changeStatus(LOADPAGEINTERFACE);
                // if you press this button, and it's not the last page, change to the next page and load the page by changing to LOADPAGEINTERFACE
            }
            else if(page!=1&&btn7.isPressed())
            {
                debug(F("Previous page button pressed"));
                page--;
                changeStatus(LOADPAGEINTERFACE);
                // if you press this button, and it's not the first page, change to the previous page and load the page by changing to LOADPAGEINTERFACE
            }
            else
                clickInterface();
            // if you click in one of the buttons of the page, you go to this function
            break;
        
        case LOADTEMPERATURE:
            page = 1;
            maxPage = 2;
            drawBackground();
        case LOADPAGETEMPERATURE:
            debug(String(F("Loading page "))+page+" / "+maxPage);
            drawTemperature();
            changeStatus(TEMPERATURE);
            break;
        
        case TEMPERATURE:
            if(backBtn.isPressed())
            {
                debug(F("Back button pressed"));
                changeStatus(LOADSETTINGS);
                // if back button is pressed you go to the previous page, so you start uploading the settings page
            }
            else if(page<maxPage&&btn8.isPressed()) // Next page
            {
                debug(F("Next page button pressed"));
                page++;
                changeStatus(LOADPAGETEMPERATURE);
            }
            else if(page>1&&btn7.isPressed())
            {
                debug(F("Previous page button pressed"));
                page--;
                changeStatus(LOADPAGETEMPERATURE);
            }
            else
            {
                clickTemperature();
            }

            break;

        case LOADWATER:
            page = 1;
            maxPage = 2;
            drawBackground();
        case LOADPAGEWATER:
            debug(String(F("Loading page "))+page+" / "+maxPage);
            drawWater();
            changeStatus(WATER);
            break;
        case WATER:
            if (backBtn.isPressed())    // Go to LOADSETTINGS
            {
                debug(F("Back Page button pressed"));
                changeStatus(LOADSETTINGS);
            }
            else if(page<maxPage && btn8.isPressed())   // Go to LOADPAGEWATER on next page
            {
                debug(F("Next page button pressed"));
                page++;
                changeStatus(LOADPAGEWATER);
            }
            else if(page>1 && btn7.isPressed())    // Go to LOADPAGEWATER on previous page
            {
                debug(F("Previous page button pressed"));
                page--;
                changeStatus(LOADPAGEWATER);
            }
            else
                clickWater();       
            break;

        case LOADEXTRAFUNCTIONS:
            drawBackground();
            page = 0;
            drawExtraFunctions();
            changeStatus(EXTRAFUNCTIONS);
            break;
        case EXTRAFUNCTIONS:
            if(backBtn.isPressed())
            {
                debug(F("Back Page button pressed"));
                changeStatus(LOADMENU);
            }
            else
            {
                clickExtraFunctions();
            }
            break;
        /*case LOADHELP:
        case HELP:
        case LOADENGINEERINGMODE:
        case ENGINEERINGMODE:
        case LOADEXTRAFUNCTIONS:*/
    }//*/
}
