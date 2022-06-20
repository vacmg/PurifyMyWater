//
// Created by Víctor on 16/06/2022.
//

#include "Utils.h"

namespace UI {
    void setFontSizeArray(byte *fontSizeArray, byte tl, byte cl, byte bl, byte tr, byte cr, byte br) {
        fontSizeArray[0] = tl;
        fontSizeArray[1] = cl;
        fontSizeArray[2] = bl;
        fontSizeArray[3] = tr;
        fontSizeArray[4] = cr;
        fontSizeArray[5] = br;
    }

    void setFontSizeArray(byte *fontSizeArray, byte tl, byte tr, byte bl, byte br) {
        fontSizeArray[0] = tl;
        fontSizeArray[1] = tr;
        fontSizeArray[2] = bl;
        fontSizeArray[3] = br;
    }

    double getNumInput(String titleNumInput, String unit, double value) {
        debug(String(F("getNumInput: ")) + titleNumInput + F(": ") + value + unit);
        drawNumInput(titleNumInput, unit);
        char string[15];
        bool negative; // sign switch
        Label outputLabel(0, 0, string, 5, Color(0, 0, 0));
        Rectangle output(60, 95, 370, 145, Color(), Color(255, 255, 255), &outputLabel);
        my_lcd.draw(&output);

        if (value > 0) {
            string[0] = ' ';
            string[1] = '\0';
            negative = false;
        } else {
            string[0] = '\0';
            negative = true;
        }
        strcat(string, String(value, 4).c_str());

        char exit = 0; // exit switch
        byte len = strlen(string); // size of the string
        bool decimalDotPlaced = true;


        my_lcd.draw(&output);


        while (exit == 0) {
            if (len < 14) // + NULL
            {
                if (btn1.isPressed()) {
                    len++;
                    strcat(string, "1");
                    my_lcd.draw(&output);
                    delay(200);
                } else if (btn2.isPressed()) {
                    len++;
                    strcat(string, "2");
                    my_lcd.draw(&output);
                    delay(200);
                } else if (btn3.isPressed()) {
                    len++;
                    strcat(string, "3");
                    my_lcd.draw(&output);
                    delay(200);
                } else if (btn4.isPressed()) {
                    len++;
                    strcat(string, "4");
                    my_lcd.draw(&output);
                    delay(200);
                } else if (btn5.isPressed()) {
                    len++;
                    strcat(string, "5");
                    my_lcd.draw(&output);
                    delay(200);
                } else if (btn6.isPressed()) {
                    len++;
                    strcat(string, "6");
                    my_lcd.draw(&output);
                    delay(200);
                } else if (btn7.isPressed()) {
                    len++;
                    strcat(string, "7");
                    my_lcd.draw(&output);
                    delay(200);
                } else if (btn8.isPressed()) {
                    len++;
                    strcat(string, "8");
                    my_lcd.draw(&output);
                    delay(200);
                } else if (btn9.isPressed()) {
                    len++;
                    strcat(string, "9");
                    my_lcd.draw(&output);
                    delay(200);
                } else if (btn10.isPressed()) {
                    len++;
                    strcat(string, "0");
                    my_lcd.draw(&output);
                    delay(200);
                }
            }

            if (btn11.isPressed() && len > 0) {
                if (string[len - 1] == '.')
                    decimalDotPlaced = false;
                if (len == 2) {
                    string[0] = ' ';
                    negative = false;
                }
                string[len - 1] = '\0';
                len--;

                my_lcd.draw(&output);
                delay(200);
            } else if (backBtn.isPressed()) { debug(F("Back button pressed"));
                exit = -1;
                delay(200);
            } else if (oKBtn.isPressed()) { debug(F("Ok button pressed"));
                exit = 1;
                delay(200);
            } else if (signBtn.isPressed()) {
                negative = (!negative);
                if (!negative) {
                    string[0] = ' ';
                } else {
                    string[0] = '-';
                }
                my_lcd.draw(&output);
                delay(200);
            }
            if (dotBtn.isPressed() && !decimalDotPlaced) {
                if (string[len - 1] >= '0' && string[len - 1] <= '9') {
                    len++;
                    strcat(string, ".");
                    decimalDotPlaced = true;
                    my_lcd.draw(&output);
                    delay(200);
                }
            }
        }

        if (exit == 1) { debug(String(F("getNumInput returned: ")) + atof(string));
            return atof(string);
        }

        debug(F("getNumInput was cancelled"));
        return NAN;
    }

    void setRotation(byte rotation) {
#if SCREENHW == 35
        my_lcd.Set_Rotation(rotation);
        ts.setRotation((rotation + SCREEN35ROTATIONOFFSET) % 4);
        ts.invertXAxis(true);
#elif SCREENHW == 39
        my_lcd.Set_Rotation(rotation);
        ts.setRotation(rotation);
#endif
    }
}