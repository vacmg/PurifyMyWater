#include <Arduino.h>
#include <LCDWIKI_KBV.h>
#include <LCDWIKI_GUI.h>
#include <TouchScreen.h>
#include <SimpleLCDTouchScreen.h>

#define DEBUG true

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


const char *const modeTable[] PROGMEM = {mode0, mode1, mode2, mode3, mode4, mode5, mode6, mode7, mode8, mode9, mode10, mode11, mode12};
char printModeBuff[20]; // Max size of any modeX string

char* modeToString(byte pMode)
{
    strcpy_P(printModeBuff, (char *)pgm_read_word(&(modeTable[pMode])));
    return printModeBuff;
}
#endif

byte mode = BOOTING;
SimpleLCDTouchScreen my_lcd(ST7796S, A3, A2, A1, A0, A4); //model,cs,cd,wr,rd,reset
TouchScreenObject ts(8,A3,A2,9,300,320,480,3,924,111,58,935); // rx is the resistance between X+ and X- Use any multimeter to read it or leave it blanc

#if DEBUG
#define debug(data) Serial.println(String(data))
#define changeMode(newMode) debug(String(F("Mode changed from '")) +String(modeToString(mode))+String(F("' to '"))+String(modeToString(newMode))+String(F("'"))); mode = newMode
#else
#define debug(data) ;
#define changeMode(newMode) mode = newMode
#endif

//Status Variable
Label label(200,10,"Menu",3,Color(0,0,0)); //general label
Rectangle rectangle(300,234,420,290, Color(0,0,0), Color(255,255,255),&label,&ts);
/*
RectangleButton recOn_OFF(300,234,420,290, Color(0,0,0), Color(255,255,255),&label,true,&ts);
RectangleButton recMenu(135,234,260,290, Color(0,0,0), Color(255,255,255),&label,true,&ts);*/

//Rectangle Buttons
RectangleButton btn1(30,120,230,200,Color(0,0,0),Color(255,255,255),&label,true,&ts);
RectangleButton btn2(250,120,440,200,Color(0,0,0),Color(255,255,255),&label,true,&ts);
RectangleButton btn3(30,220,230,300,Color(0,0,0),Color(255,255,255),&label,true,&ts);
RectangleButton btn4(250,220,440,300,Color(0,0,0),Color(255,255,255),&label,true,&ts);

// Frequently used ScreenObjects
RectangleButton backBtn(20,20,60,60,Color(0,0,0),Color(255,255,255),&label,&ts);
Label titleLabel(0,0,"Menu",5,Color(0),Color(255,255,255));
Rectangle title(65,5,415,75,Color(0xFFFF),/*Color(255,0,0),*/&titleLabel,true);
//395

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

//Auxiliary functions

//Main Functions
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

    label.setFontSize(2);
    label.setString("Menu"); // Label Menu
    btn1.setCoords(135,234);
    btn1.setCoords1(260,290);
    my_lcd.draw(&btn1);

    label.setString("ON/OFF"); //Label ON/OFF todo button mechanic (ON(green) || OFF(red))
    btn2.setCoords(300,234);
    btn2.setCoords1(420,290);
    my_lcd.draw(&btn2);
}
void drawStatusBackground()
{
    drawStatusBackground(false);
}

// Draw voltage & amount of purified water
void drawStatusForeground(char* voltage, char* waterAmount)//TODO add water levels & other indicators
{
    debug("Voltage: "+String(voltage)+"\tWater amount: "+waterAmount);

    label.setString(voltage);
    label.setFontSize(1);
    rectangle.setCoords(20,115);
    rectangle.setCoords1(70,135);
    my_lcd.draw(&rectangle);

    label.setString(waterAmount);
    rectangle.setCoords(400,195);
    rectangle.setCoords1(440,215);
    my_lcd.draw(&rectangle);
}

// Buttons mapped to: btn1 --> Settings, btn2 --> Help, btn3 --> Engineering Mode, btn4 --> Extra Functions
void drawMenu()
{
    //Title Menu
    titleLabel.setString("Menu");
    my_lcd.draw(&title);

    // Settings button
    label.setFontSize(3);
    label.setString("Settings");
    btn1.setCoords(30,120);
    btn1.setCoords1(230,200);
    my_lcd.draw(&btn1);

    // Help button
    label.setString("Help");
    btn2.setCoords(250,120);
    btn2.setCoords1(440,200);
    my_lcd.draw(&btn2);

    // Engineering Mode button
    label.setFontSize(2);
    label.setString("Engineering Mode");
    btn3.setCoords(30,220);
    btn3.setCoords1(230,300);
    my_lcd.draw(&btn3);

    // Extra Functions button
    label.setString("Extra Functions");
    btn4.setCoords(250,220);
    btn4.setCoords1(440,300);
    my_lcd.draw(&btn4);
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
    my_lcd.Set_Rotation(3);
    ts.setRotation(3);

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
                debug(F("Button ON/OFF pressed"));
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
                changeMode(LOADSTATUS);
                break;
            }
            else if(btn1.isPressed()) //Settings
            {
                changeMode(LOADSETTINGS);
            }
            else if(btn2.isPressed()) //Help
            {
                changeMode(LOADHELP);
            }
            else if(btn3.isPressed()) //Engineering Mode
            {
                changeMode(LOADENGINEERINGMODE);
            }
            else if(btn4.isPressed()) //Extra Functions
            {
                changeMode(LOADEXTRAFUNCTIONS);
            }
    }//*/
}
