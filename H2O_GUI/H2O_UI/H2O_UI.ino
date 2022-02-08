#include <Arduino.h>
#include <LCDWIKI_KBV.h>
#include <LCDWIKI_GUI.h>
#include <TouchScreen.h>
#include <SimpleLCDTouchScreen.h>

#define DEBUG true

#define BOOTING 0
#define LOADSTATUS 1
#define STATUS 2

#if DEBUG
    const char mode0[] PROGMEM = "BOOTING"; // in order (BOOTING = 0 ---> mode0 = "BOOTING" --> modeTable[0] = mode0)
    const char mode1[] PROGMEM = "LOADSTATUS";
    const char mode2[] PROGMEM = "STATUS";

    const char *const modeTable[] PROGMEM = {mode0, mode1, mode2};
    char printModeBuff[11]; // Max size of any modeX string

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

void bootAnimation()
{
    Picture bigLogo(157,25,"PMWBL.bmp");
    my_lcd.draw(&bigLogo);
    Label loading(165,85,"Loading...",3,Color(0,70,200));
    my_lcd.draw(&loading);
}

void drawStatusBackground()
{
    Picture menuBackground(14,74,"schArd.bmp");
    my_lcd.draw(&menuBackground);
    Rectangle rec(216,0,249,73, Color(255,255,255), Color(255,255,255));
    my_lcd.draw(&rec);
}

void drawStatusForeground()
{

    Label lab(200,10,"Menu",3,Color(0,0,0)); //Label MENU
    RectangleButton recOn_OFF(135,234,260,290, Color(0,0,0), Color(255,255,255),&lab,true,&ts);
    RectangleButton recMenu(300,234,420,290, Color(0,0,0), Color(255,255,255),&lab,true,&ts);
    my_lcd.draw(&recMenu);
    lab.setString("ON/OFF"); //Label ON/OFF
    my_lcd.draw(&recOn_OFF);

    Rectangle rec(300,234,420,290, Color(0,0,0), Color(255,255,255),&lab,&ts);
    lab.setString("Logo"); //todo add logo 60*60
    lab.setFontSize(2);
    rec.ScreenObject::setCoords(400,10);
    rec.setCoords1(460,70);
    my_lcd.draw(&rec);


    lab.setString("15.4 V"); //todo add Voltage
    lab.setFontSize(1);
    rec.ScreenObject::setCoords(20,115);
    rec.setCoords1(70,135);
    my_lcd.draw(&rec);

    lab.setString("200 L"); //todo add Liters
    rec.ScreenObject::setCoords(400,195);
    rec.setCoords1(440,215);
    my_lcd.draw(&rec);

    lab.setCoords(150,20);
    lab.setFontSize(5);
    lab.setString("status");
    my_lcd.draw(&lab);
}

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

void loop()
{
    switch (mode)
    {
        case BOOTING:
            bootAnimation();
            changeMode(LOADSTATUS);
            break;
        case LOADSTATUS:
            drawStatusBackground();
            changeMode(STATUS);
            break;
        case STATUS:
            drawStatusForeground();
            while(1);
            break;
    }
}
