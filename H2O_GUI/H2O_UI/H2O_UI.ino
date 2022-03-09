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

// ERROR CODES (CODE<0)
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
byte mode = LOADELECTRICITY;


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


const char *const modeTable[] PROGMEM = {mode0, mode1, mode2, mode3, mode4, mode5, mode6, mode7, mode8, mode9, mode10, mode11, mode12, mode13, mode14, mode15};
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

void bootAnimation()
{
    Picture bigLogo(157,25,"PMWBL.bmp");
    my_lcd.draw(&bigLogo);
}
//Auxiliary functions

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

//btn1 --> str1; btn2 --> str2; btn3 --> str3; btn4 --> str4
void draw4ButtonsLayout(char* str1, char* str2, char* str3, char* str4)
{
    // Top left button
    btn1.setDisableAutoSize(true);
    label.setFontSize(2);
    label.setString(str1);
    btn1.setCoords(30,120);
    btn1.setCoords1(230,200);
    my_lcd.draw(&btn1);
    btn1.setDisableAutoSize(false);

    // Top right button
    btn2.setDisableAutoSize(true);
    label.setFontSize(2);
    label.setString(str2);
    btn2.setCoords(250,120);
    btn2.setCoords1(440,200);
    my_lcd.draw(&btn2);
    btn2.setDisableAutoSize(false);

    // Bottom left button
    btn3.setDisableAutoSize(true);
    label.setFontSize(2);
    label.setString(str3);
    btn3.setCoords(30,220);
    btn3.setCoords1(230,300);
    my_lcd.draw(&btn3);
    btn3.setDisableAutoSize(false);

    // Bottom right button
    btn4.setDisableAutoSize(true);
    label.setFontSize(2);
    label.setString(str4);
    btn4.setCoords(250,220);
    btn4.setCoords1(440,300);
    my_lcd.draw(&btn4);
    btn4.setDisableAutoSize(false);
}

// btn1 --> topLeft; btn2 --> centerLeft; btn3 --> bottomLeft; btn4 --> topRight; btn5 --> centerRight; btn6 --> bottomRight; btn7 --> Previous; btn8 --> Next; btn9 --> topHelp; btn10 --> centerHelp; btn11 --> bottomHelp;
void draw6ButtonsLayout(char* topLeft, char* centerLeft, char* bottomLeft, char* topRight, char* centerRight, char* bottomRight, bool topHelp, bool centerHelp, bool bottomHelp, byte maxPage)
{
    label.setString(topLeft);
    btn1.setCoords(25,95);
    btn1.setCoords1(195,135);
    my_lcd.draw(&btn1);

    label.setString(topRight);
    btn2.setCoords(280,95);
    btn2.setCoords1(450,135);
    my_lcd.draw(&btn2);

    label.setString(centerLeft);
    btn3.setCoords(25,155);
    btn3.setCoords1(195,195);
    my_lcd.draw(&btn3);

    label.setString(centerRight);
    btn4.setCoords(280,155);
    btn4.setCoords1(450,195);
    my_lcd.draw(&btn4);

    label.setString(bottomLeft);
    btn5.setCoords(25,215);
    btn5.setCoords1(195,255);
    my_lcd.draw(&btn5);

    label.setString(bottomRight);
    btn6.setCoords(280,215);
    btn6.setCoords1(450,255);
    my_lcd.draw(&btn6);

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

//Auxiliary functions

//Main Functions
void drawStatusColors(bool wellPump, bool UVPump, bool endPump, bool UVRelay, bool filterRelay, char well, char tank1, char tank2, char tank3, bool endTank) // TODO rectangles // false --> OFF, true -->ON, <0 --> LOW, = 0 --> Half, >0 --> FULL
{
    //todo change delays for conditions of the buoys

    //tank1
    Rectangle Rec1(28,258,89,301,Color(81, 136, 223),Color(81, 136, 223)); // big rectangle under valve
    my_lcd.draw(&Rec1);
    //tank1_1
    delay(1000);
    Rec1.setCoords1(78,258); // Rectangle at the let of the valve
    Rec1.setCoords(28,230);
    my_lcd.draw(&Rec1);
    Rec1.setCoords1(89,254); // Small Rectangle under valve
    Rec1.setCoords(78,259);
    my_lcd.draw(&Rec1);
    Rec1.setCoords(85,245); // Small rectangle right of the tube
    Rec1.setCoords1(89,230);
    my_lcd.draw(&Rec1);
    Rec1.setCoords(78,245); // Small rectangle left of the tube
    Rec1.setCoords1(80,230);
    my_lcd.draw(&Rec1);

    //ValveTank1
    delay(1000);
    Rec1.setMainColor(Color(255,255,0));
    Rec1.setSecondaryColor(Color(255,255,0));
    Rec1.setCoords(91,254); // Valve
    Rec1.setCoords1(80,247);
    my_lcd.draw(&Rec1);

    //TubeTank1
    //delay(1000);
    //Rec1.setMainColor(Color(81, 136, 223));
    // Rec1.setSecondaryColor(Color(81, 136, 223));
    //Rec1.setCoords1(83,170); // Tube
    //Rec1.setCoords(81,2);
    //my_lcd.draw(&Rec1);

    //tank2
    delay(1000);
    Rectangle Rec2(99,211,144,219,Color(81, 136, 223),Color(81, 136, 223));
    my_lcd.draw(&Rec2);
    //tank2_1
    delay(1000);
    Rec2.setCoords(99,208); // Small Rectangle under valve
    Rec2.setCoords1(144,211);
    my_lcd.draw(&Rec2);
    Rec2.setCoords(99,180); // Rectangle at the left of the valve
    Rec2.setCoords1(133,208);
    my_lcd.draw(&Rec2);
    Rec2.setCoords(133,180); // Small Rectangle at the left of the tube
    Rec2.setCoords1(136,199);
    my_lcd.draw(&Rec2);
    Rec2.setCoords(141,180); // Small Rectangle at the right of the tube
    Rec2.setCoords1(144,199);
    my_lcd.draw(&Rec2);
    //tank2_2
    delay(1000);
    Rec2.setCoords(99,153); // Big Rectangle at the top right of the tube
    Rec2.setCoords1(136,180);
    my_lcd.draw(&Rec2);
    Rec2.setCoords(141,153); // Rectangle at the top left of the tube
    Rec2.setCoords1(144,180);
    my_lcd.draw(&Rec2);

    //tank3
    delay(1000);
    Rectangle Rec3(213,213,258,219,Color(81, 136, 223),Color(81, 136, 223)); // Big rectangle under valve
    my_lcd.draw(&Rec3);
    //tan3_1
    delay(1000);
    Rec3.setCoords(213,210); // Large rectangle under valve
    Rec3.setCoords1(258,213);
    my_lcd.draw(&Rec3);
    Rec3.setCoords(213,180); // Big bottom rectangle under valve
    Rec3.setCoords1(247,210);
    my_lcd.draw(&Rec3);
    Rec3.setCoords(247,180); // Large bottom rectangle at the left of the tube
    Rec3.setCoords1(251,201);
    my_lcd.draw(&Rec3);
    Rec3.setCoords(256,180); // Large bottom rectangle at the right of the tube
    Rec3.setCoords1(258,201);
    my_lcd.draw(&Rec3);
    //tank3_2
    delay(1000);
    Rec3.setCoords(213,163); // Big top rectangle under valve
    Rec3.setCoords1(247,180);
    my_lcd.draw(&Rec3);
    Rec3.setCoords(247,163); // Large top rectangle at the left of the tube
    Rec3.setCoords1(251,180);
    my_lcd.draw(&Rec3);
    Rec3.setCoords(256,163); // Large top rectangle at the right of the tube
    Rec3.setCoords1(258,180);
    my_lcd.draw(&Rec3);


    //tank4
    delay(1000);
    Rectangle Rec4(339,213,379,219,Color(81, 136, 223),Color(81, 136, 223));// Big rectangle under valve
    my_lcd.draw(&Rec4);
    //tank4_1
    delay(1000);
    Rec4.setCoords(339,210); // Large rectangle under valve
    Rec4.setCoords1(379,213);
    my_lcd.draw(&Rec4);
    Rec4.setCoords(339,180); // Big rectangle bottom left of the tube
    Rec4.setCoords1(368,210);
    my_lcd.draw(&Rec4);
    Rec4.setCoords(368,180); // Large rectangle bottom left of the tube
    Rec4.setCoords1(372,201);
    my_lcd.draw(&Rec4);
    Rec4.setCoords(377,180); // Large rectangle bottom right of the tube
    Rec4.setCoords1(379,201);
    my_lcd.draw(&Rec4);
    //tank4_2
    delay(1000);
    Rec4.setCoords(339,165); // Big rectangle top left of the tube
    Rec4.setCoords1(368,180);
    my_lcd.draw(&Rec4);
    Rec4.setCoords(368,165); // Large rectangle top left of the tube
    Rec4.setCoords1(372,180);
    my_lcd.draw(&Rec4);
    Rec4.setCoords(377,165); // Large rectangle top right of the tube
    Rec4.setCoords1(379,180);
    my_lcd.draw(&Rec4);


    //tank5
    delay(1000);
    Rectangle Rec5(396,135,452,157,Color(81, 136, 223),Color(81, 136, 223));// Big rectangle under valve
    my_lcd.draw(&Rec5);
    Rec5.setCoords(427,157); // Rectangle on the tube
    Rec5.setCoords1(430,182);
    my_lcd.draw(&Rec5);
    Rec5.setCoords(427,183); // Rectangle on the tube
    Rec5.setCoords1(462,186);
    my_lcd.draw(&Rec5);
    //tank5_1
    delay(1000);
    Rec5.setCoords(396,92); // Big rectangle top top of the tank
    Rec5.setCoords1(452,135);
    my_lcd.draw(&Rec5);
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

    drawStatusColors(0,0,0,0,0,0,0,0,0,0);
}

// Buttons mapped to: btn1 --> Settings, btn2 --> Help, btn3 --> Engineering Mode, btn4 --> Extra Functions
void drawMenu()
{
    //Title Menu
    titleLabel.setString("Menu");
    my_lcd.draw(&title);
    //Layout4Buttons
    draw4ButtonsLayout("Settings","Help","Engineering Mode","Extra functions");
}

// Buttons mapped to: btn1 --> Electricity, btn2 --> Water, btn3 --> Interface, btn4 --> Temperature
void drawSettings()
{
    //Title Menu
    titleLabel.setString("Settings");
    my_lcd.draw(&title);
    //Layout4Buttons
    draw4ButtonsLayout("Electricity","Water","Interface","Temperature");
}

void drawElectricity() // TODO get settings real value
{
    //Title electricity
    titleLabel.setString("Electricity Settings");
    titleLabel.setFontSize(2);
    my_lcd.draw(&title);
    titleLabel.setFontSize(5);
    switch (page)
    {
        case 1:
            draw6ButtonsLayout("Start Charging Voltage","Stop Charging Voltage","UV light est. Current","12.5V","15.5V","1A",true,true,true, maxPage);
            break;
        case 2:
            draw6ButtonsLayout("Start Working Voltage","Stop Working Voltage","AC Inverter Frequency","15.2V","11.9V","50Hz",true,true,true, maxPage);
            break;
        case 3:
            draw6ButtonsLayout("AC Ammeter Sensitivity","AC Ammeter Zero","DC Ammeter Sensitivity","1.856","3.678","1.567",true,true,true, maxPage);
            break;
        case 4:
            draw6ButtonsLayout("DC Ammeter Zero","","","4.678","","",true,false,false, maxPage);
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
            }
            else if(btn3.isPressed())
            {
                changeMode();
            }
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



            /*case LOADHELP:
            case HELP:
            case LOADENGINEERINGMODE:
            case ENGINEERINGMODE:
            case LOADEXTRAFUNCTIONS:
            case EXTRAFUNCTIONS:*/
    }//*/
}
