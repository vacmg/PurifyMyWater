#include <Arduino.h>
#include <LCDWIKI_KBV.h>
#include <LCDWIKI_GUI.h>
#include <TouchScreen.h>
#include <SimpleLCDTouchScreen.h>

#define DEBUG true

#define ROTATION 3 // sets screen rotation
#define SCREENHW 35 // 35 --> 3.5INCH / 39 --> 3.95INCH

#define BOOTING 0
#define LOADSTATUS 1
#define STATUS 2
#define LOADMENU 3
#define MENU 4
#define LOADSETTINGS 5
#define SETTINGS 6
#define LOADHELP 7
#define HELP 8
#define LOADENGINEERINGMODE 9
#define ENGINEERINGMODE 10
#define LOADEXTRAFUNCTIONS 11
#define EXTRAFUNCTIONS 12
#define LOADELECTRICITY 13
#define LOADPAGEELECTRICITY 14
#define ELECTRICITY 15
#define LOADINTERFACE 16
#define LOADPAGEINTERFACE 17
#define INTERFACE 18
#define LOADTEMPERATURE 19
#define LOADPAGETEMPERATURE 20
#define TEMPERATURE 21

// ON/OFF BTN STATUS
#define ON 1
#define OFF 0
#define ERROR -1


#if SCREENHW == 35
#define SCREEN35ROTATIONOFFSET 2
TouchScreenObject ts(9,A2,A3,8,300,320,480,(ROTATION+SCREEN35ROTATIONOFFSET)%4,177,900,157,958); // for 3.5inch
#elif SCREENHW == 39
TouchScreenObject ts(8,A3,A2,9,300,320,480,ROTATION,924,111,58,935); // rx is the resistance between X+ and X- Use any multimeter to read it or leave it blanc
#endif

SimpleLCDTouchScreen my_lcd(ST7796S, A3, A2, A1, A0, A4); //model,cs,cd,wr,rd,reset
char mainSwitchSt = OFF;
byte mode = LOADINTERFACE;


#if DEBUG
const char mode0[] PROGMEM = "BOOTING"; // in order (BOOTING = 0 ---> mode0 = "BOOTING" --> modeTable[0] = mode0)
const char mode1[] PROGMEM = "LOADSTATUS";
const char mode2[] PROGMEM = "STATUS";
const char mode3[] PROGMEM = "LOADMENU";
const char mode4[] PROGMEM = "MENU";
const char mode5[] PROGMEM = "LOADSETTINGS";
const char mode6[] PROGMEM = "SETTINGS";
const char mode7[] PROGMEM = "LOADHELP";
const char mode8[] PROGMEM = "HELP";
const char mode9[] PROGMEM = "LOADENGINEERINGMODE";
const char mode10[] PROGMEM = "ENGINEERINGMODE";
const char mode11[] PROGMEM = "LOADEXTRAFUNCTIONS";
const char mode12[] PROGMEM = "EXTRAFUNCTIONS";
const char mode13[] PROGMEM = "LOADELECTRICTY";
const char mode14[] PROGMEM = "LOADPAGEELECTRICITY";
const char mode15[] PROGMEM = "ELECTRICITY";
const char mode16[] PROGMEM = "LOADINTERFACE";
const char mode17[] PROGMEM = "LOADPAGEINTERFACE";
const char mode18[] PROGMEM = "INTERFACE";
const char mode19[] PROGMEM = "LOADTEMPERATURE";
const char mode20[] PROGMEM = "LOADPAGETEMPERATURE";
const char mode21[] PROGMEM = "TEMPERATURE";



const char *const modeTable[] PROGMEM = {mode0, mode1, mode2, mode3, mode4, mode5, mode6, mode7, mode8, mode9, mode10, mode11, mode12, mode13, mode14, mode15, mode16, mode17, mode18, mode19, mode20,mode21};
char printModeBuff[20]; // Max size of any modeX string

char* modeToString(byte pMode)
{
    strcpy_P(printModeBuff, (char *)pgm_read_word(&(modeTable[pMode])));
    return printModeBuff;
}
#endif

char auxBuffer[32] = ""; // TODO when using progmem, use it as a buffer to print each label

byte page = 0;
byte maxPage = 0;

#if DEBUG
#define debug(data) Serial.println(String(data))
#define changeMode(newMode) debug(String(F("Mode changed from '")) +String(modeToString(mode))+String(F("' to '"))+String(modeToString(newMode))+String(F("'"))); mode = newMode
#else
#define debug(data) ;
    #define changeMode(newMode) mode = newMode
#endif

//Status Variable
Label label(200,10,"Menu",3,Color(0,0,0)); //general label
Rectangle rectangle(300,234,420,290, Color(0,0,0), Color(255,255,255),&label);
/*
RectangleButton recOn_OFF(300,234,420,290, Color(0,0,0), Color(255,255,255),&label,true,&ts);
RectangleButton recMenu(135,234,260,290, Color(0,0,0), Color(255,255,255),&label,true,&ts);*/

//Rectangle Buttons
RectangleButton btn1(30,120,230,200,Color(0,0,0),Color(255,255,255),&label,&ts);//todo disable autosize & enable again in the cases that is needed
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

//Auxiliary functions

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
void draw4ButtonsLayout(char* topLeft, char* topRight, char* bottomLeft, char* bottomRight, const byte* fontSize)
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
    label.setString(topLeft);
    btn1.setCoords(30,120);
    btn1.setCoords1(230,200);
    my_lcd.draw(&btn1);
    btn1.setDisableAutoSize(false);

    // Top right button
    if (validFontSize) label.setFontSize(fontSize[1]);
    label.setString(topRight);
    btn2.setCoords(250,120);
    btn2.setCoords1(440,200);
    my_lcd.draw(&btn2);
    btn2.setDisableAutoSize(false);

    // Bottom left button
    if (validFontSize) label.setFontSize(fontSize[2]);
    label.setString(bottomLeft);
    btn3.setCoords(30,220);
    btn3.setCoords1(230,300);
    my_lcd.draw(&btn3);
    btn3.setDisableAutoSize(false);

    // Bottom right button
    if (validFontSize) label.setFontSize(fontSize[3]);
    label.setString(bottomRight);
    btn4.setCoords(250,220);
    btn4.setCoords1(440,300);
    my_lcd.draw(&btn4);
    btn4.setDisableAutoSize(false);
}

void draw4ButtonsLayout(char* topLeft, char* topRight, char* bottomLeft, char* bottomRight)
{
    draw4ButtonsLayout(topLeft, topRight, bottomLeft, bottomRight, NULL);
}

// btn1 --> topLeft; btn2 --> centerLeft; btn3 --> bottomLeft; btn4 --> topRight; btn5 --> centerRight; btn6 --> bottomRight; btn7 --> Previous; btn8 --> Next; btn9 --> topHelp; btn10 --> centerHelp; btn11 --> bottomHelp; If fontSize = NULL, autoFontSize; len(fontSize) = 6
void draw6ButtonsLayout(char* topLeft, char* centerLeft, char* bottomLeft, char* topRight, char* centerRight, char* bottomRight, bool topHelp, bool centerHelp, bool bottomHelp, const byte* fontSize)
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
    label.setString(topLeft);
    if (validFontSize) label.setFontSize(fontSize[0]);
    btn1.setCoords(25,95);
    btn1.setCoords1(195,135);
    my_lcd.draw(&btn1);

    label.setString(centerLeft);
    if (validFontSize) label.setFontSize(fontSize[1]);
    btn3.setCoords(25,155);
    btn3.setCoords1(195,195);
    my_lcd.draw(&btn3);

    label.setString(bottomLeft);
    if (validFontSize) label.setFontSize(fontSize[2]);
    btn5.setCoords(25,215);
    btn5.setCoords1(195,255);
    my_lcd.draw(&btn5);

    label.setString(topRight);
    if (validFontSize) label.setFontSize(fontSize[3]);
    btn2.setCoords(280,95);
    btn2.setCoords1(450,135);
    my_lcd.draw(&btn2);

    label.setString(centerRight);
    if (validFontSize) label.setFontSize(fontSize[4]);
    btn4.setCoords(280,155);
    btn4.setCoords1(450,195);
    my_lcd.draw(&btn4);

    label.setString(bottomRight);
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

    if(topHelp)
    {
        btn9.setCoords(218,95);
        btn9.setCoords1(258,135);
        label.setString("?");
        my_lcd.draw(&btn9);
    }

    if(centerHelp)
    {
        btn10.setCoords(218,155);
        btn10.setCoords1(258,195);
        label.setString("?");
        my_lcd.draw(&btn10);
    }

    if(bottomHelp)
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

void draw6ButtonsLayout(char* topLeft, char* centerLeft, char* bottomLeft, char* topRight, char* centerRight, char* bottomRight, bool topHelp, bool centerHelp, bool bottomHelp)
{
    draw6ButtonsLayout(topLeft,centerLeft,bottomLeft,topRight,centerRight,bottomRight,topHelp,centerHelp,bottomHelp,NULL);
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

float getNumInput(char* title, char* unit)
{

    return 0.0;
}

//Auxiliary functions

//Main Functions

void bootAnimation()
{
    Picture bigLogo(157,25,"PMWBL.bmp");
    my_lcd.draw(&bigLogo);
}

void drawStatusColors(bool wellPump, bool endPump, bool UVRelay, bool filterRelay, char well, char surfaceTank, char filteredTank, char purifiedTank, bool endTank) // TODO rectangles // false --> OFF, true -->ON, <0 --> LOW, = 0 --> Half, >0 --> FULL
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
    rec1.setCoords1(78,258); // Rectangle at the let of the valve
    rec1.setCoords(28,230);
    my_lcd.draw(&rec1);
    rec1.setCoords1(89,254); // Small Rectangle under valve
    rec1.setCoords(78,259);
    my_lcd.draw(&rec1);
    rec1.setCoords(85,245); // Small rectangle right of the tube
    rec1.setCoords1(89,230);
    my_lcd.draw(&rec1);
    rec1.setCoords(78,245); // Small rectangle left of the tube
    rec1.setCoords1(80,230);
    my_lcd.draw(&rec1);


    //Filter
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
    recFilter.setCoords(200,136); // Tube right
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
    rec4.setCoords(374,201); // Tube up
    rec4.setCoords1(375,81);
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
    rec5.setCoords1(462,186);
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

void drawStatusBackground(bool dontFillScreen)
{
    if(!dontFillScreen)
        my_lcd.Fill_Screen(0xFFFF);

    Label loading(165,85,"Loading...",3,Color(0,70,200));
    my_lcd.draw(&loading);

    titleLabel.setString("Status"); // Title
    my_lcd.draw(&title);

    Picture statusBackground(14,74,"schArd.bmp");
    my_lcd.draw(&statusBackground);
    Rectangle rec(225,60,249,73, Color(255,255,255), Color(255,255,255));
    my_lcd.draw(&rec);

    //Small logo
    Picture logoPhoto(400,10,"PMWSL.bmp");
    my_lcd.draw(&logoPhoto);
    btn1.setDisableAutoSize(true);
    label.setFontSize(2);
    label.setString("Menu"); // Label Menu
    btn1.setCoords(135,234);
    btn1.setCoords1(260,290);
    my_lcd.draw(&btn1);
    btn1.setDisableAutoSize(false);

    /*btn2.setDisableAutoSize(true);
    label.setFontSize(2);
    label.setString("ON/OFF"); //Label ON/OFF
    btn2.setCoords(300,234);
    btn2.setCoords1(420,290);
    my_lcd.draw(&btn2);
    btn2.setDisableAutoSize(false);*/
}

void drawStatusBackground()
{
    drawStatusBackground(false);
}

// Draw voltage & amount of purified water
void drawStatusForeground(char* voltage, char* waterAmount)//TODO add water levels & other indicators
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
    draw4ButtonsLayout("Settings","Help","Engineering Mode","Extra functions",fontSize);
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
    draw4ButtonsLayout("Electricity","Water","Interface","Temperature",fontSize);
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
            draw6ButtonsLayout("Start Charging Voltage","Stop Charging Voltage","UV light est. Current","12.5V","15.5V","1A",true,true,true,fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes, 1,1,1,2,2,2);
            draw6ButtonsLayout("Start Working Voltage","Stop Working Voltage","AC Inverter Frequency","15.2V","11.9V","50Hz",true,true,true, fontSizes);
            break;
        case 3:
            setFontSizeArray(fontSizes, 1,1,1,2,2,2);
            draw6ButtonsLayout("AC Ammeter Sensitivity","AC Ammeter Zero","DC Ammeter Sensitivity","1.856","3.678","1.567",true,true,true,fontSizes);
            break;
        case 4:
            setFontSizeArray(fontSizes, 1,1,1,2,1,1);
            draw6ButtonsLayout("DC Ammeter Zero","","","4.678","","",true,false,false,fontSizes);
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
            draw6ButtonsLayout("Language","Screen Rotation","Screen Calibration","English","Inverted Landscape","Calibrate",true,true,true, fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes,2,2,2,2,2,2);
            draw6ButtonsLayout("Refresh Rate","Reset","","5s","Perform Reset","",true,true,false, fontSizes);
            break;
    }

}

void drawTemperature() {
    titleLabel.setString("Temperature");
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    byte fontSizes[6];
    switch (page) {
        case 1:
            setFontSizeArray(fontSizes, 1, 1, 1, 1, 1, 1);
            draw6ButtonsLayout("Temp. Refresh Rate", "System Stop Temp.", "PSU Fan Start Temp.", "20s", "65ºC", "40ºC",
                               true, true, true, fontSizes);
            break;
        case 2:
            setFontSizeArray(fontSizes, 2, 2, 2, 2, 2, 2);
            draw6ButtonsLayout("PSU Fan Stop Temp.", "Case Fan Start Temp.", "Case Fan Stop Temp.", "35ºC", "38ºC",
                               "34ºC", true, true, true, fontSizes);
            break;
    }
}

void clickElectricity()
{
    /*if(btnx.isPressed())
    {
        switch (page)
        {
            case 1:
            changeMode(XXXXX);
            break;
            case x:
                ...
        }
    }*/
}

void clickInterface()
{
    /*if(btnx.isPressed())
    {
        switch (page)
        {
            case 1:
            changeMode(XXXXX);
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
    switch (mode)
    {
        case BOOTING:
            bootAnimation();
            // Perform other boot stuff after this line
            delay(1000);
            // Perform other boot stuff before this line
            sw = true; // todo delete this
            drawStatusBackground(true);
            changeMode(STATUS);
            break;

        case LOADSTATUS:
            sw = true; // todo delete this
            drawStatusBackground();
            changeMode(STATUS);
            break;

        case STATUS:
            if(sw) // todo delete this (change condition to update info labels)
            {
                drawStatusForeground("15.4V", "320L");
                sw = false; // todo delete this
            }
            if(btn1.isPressed())
            {
                debug(F("Button MENU pressed"));
                changeMode(LOADMENU);
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
            break;

        case LOADMENU:
            drawBackground();
            drawMenu();
            changeMode(MENU);
            break;

        case MENU:
            if(backBtn.isPressed()) // Go to LOADSTATUS
            {
                debug(F("Back button pressed"));
                changeMode(LOADSTATUS);
            }
            else if(btn1.isPressed()) //Settings
            {
                debug(F("Settings button pressed"));
                changeMode(LOADSETTINGS);
            }
            else if(btn2.isPressed()) //Help
            {
                debug(F("Help button pressed"));
                changeMode(LOADHELP);
            }
            else if(btn3.isPressed()) //Engineering Mode
            {
                debug(F("Engineering mode button pressed"));
                changeMode(LOADENGINEERINGMODE);
            }
            else if(btn4.isPressed()) //Extra Functions
            {
                debug(F("Extra functions button pressed"));
                changeMode(LOADEXTRAFUNCTIONS);
            }
            break;

        case LOADSETTINGS:
            drawBackground();
            drawSettings();
            changeMode(SETTINGS);
            break;

        case SETTINGS:
            if(backBtn.isPressed()) // Go to LOADMENU
            {
                debug(F("Back button pressed"));
                changeMode(LOADMENU);
            }
            else if(btn1.isPressed())
            {
                debug(F("Electricity button pressed"));
                changeMode(LOADELECTRICITY);
            }
            /*
            else if(btn2.isPressed())
            {
                changeMode();
            }*/
            else if(btn3.isPressed()) // Go to LOADINTERFACE
            {
                debug(F("Interface button pressed"));
                changeMode(LOADINTERFACE);
            }
            /*
            else if(btn4.isPressed())
            {
                changeMode();
            }*/
            break;
        case LOADELECTRICITY:
            page = 1;
            maxPage = 4;
            drawBackground();
        case LOADPAGEELECTRICITY:
            debug(String(F("Loading page "))+page+" / "+maxPage);
            drawElectricity();
            changeMode(ELECTRICITY);
            break;
        case ELECTRICITY:
            if(backBtn.isPressed()) // Go to LOADSETTINGS
            {
                debug(F("Back button pressed"));
                changeMode(LOADSETTINGS);
            }
            else if(page>1&&btn7.isPressed()) // Previous
            {
                debug(F("Previous button pressed"));
                page--;
                changeMode(LOADPAGEELECTRICITY);
            }
            else if(page<maxPage&&btn8.isPressed()) // Next
            {
                debug(F("Next button pressed"));
                page++;
                changeMode(LOADPAGEELECTRICITY);
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
            changeMode(INTERFACE);
            break;
        case INTERFACE:
            if(backBtn.isPressed())
            {
                debug(F("Back button pressed"));
                changeMode(LOADSETTINGS);
                // if back button is pressed you go to the previous page, so you start uploading the settings page
            }
            else if(page<maxPage&&btn8.isPressed()) // Next page
            {
                debug(F("Next page button pressed"));
                page++;
                changeMode(LOADPAGEINTERFACE);
                // if you press this button, and it's not the last page, change to the next page and load the page by changing to LOADPAGEINTERFACE
            }
            else if(page!=1&&btn7.isPressed())
            {
                debug(F("Next page button pressed"));
                page--;
                changeMode(LOADPAGEINTERFACE);
                // if you press this button, and it's not the first page, change to the previous page and load the page by changing to LOADPAGEINTERFACE
            }
            else
                clickInterface();
            // if you click in one of the buttons of the page, you go to this function
            break;





            /*case LOADHELP:
            case HELP:
            case LOADENGINEERINGMODE:
            case ENGINEERINGMODE:
            case LOADEXTRAFUNCTIONS:
            case EXTRAFUNCTIONS:*/
    }//*/
}
