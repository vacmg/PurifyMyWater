//
// Created by Víctor on 16/06/2022.
//

#include "Status.h"

void drawStatusBackgroundPhoto()
{
    Rectangle backRec(15, 70, 420, 320, Color(255, 255, 255), Color(255, 255, 255));
    my_lcd.draw(&backRec);
    backRec.setCoords(160, 62);
    backRec.setCoords1(260, 70);
    my_lcd.draw(&backRec);

    Rectangle rec(56, 200, 62, 220, Color(0, 0, 0));
    my_lcd.draw(&rec);
    //rectangle around the page
    RoundRectangle Rrec(15, 75, 465, 302, 1, Color(0, 0, 0));
    my_lcd.draw(&Rrec);

    //rectangle around the Menu and ON/OFF buttons
    Rrec.setCoords(15, 220);
    Rrec.setCoords1(465, 302);
    my_lcd.draw(&Rrec);
    Rrec.setCoords(117, 220);
    Rrec.setCoords1(435, 302);
    my_lcd.draw(&Rrec);

    //SolarPanel
    Line line(64, 100, 80, 200, Color(0, 0, 0));
    my_lcd.draw(&line);
    line.setCoords(84, 100);
    line.setCoords1(100, 200);
    my_lcd.draw(&line);
    line.setCoords(84, 100);
    line.setCoords1(100, 200);
    my_lcd.draw(&line);
    line.setCoords(44, 100);
    line.setCoords1(60, 200);
    my_lcd.draw(&line);
    line.setCoords(24, 100);
    line.setCoords1(40, 200);
    my_lcd.draw(&line);
    line.setCoords(4, 100);
    line.setCoords1(20, 200);
    my_lcd.draw(&line);

    line.setCoords(20, 200);
    line.setCoords1(100, 200);
    my_lcd.draw(&line);
    line.setCoords(4, 100);
    line.setCoords1(84, 100);
    my_lcd.draw(&line);
    line.setCoords(4, 120);
    line.setCoords1(92, 120);
    my_lcd.draw(&line);
    line.setCoords(4, 140);
    line.setCoords1(90, 140);
    my_lcd.draw(&line);
    line.setCoords(4, 160);
    line.setCoords1(94, 160);
    my_lcd.draw(&line);
    line.setCoords(17, 180);
    line.setCoords1(96, 180);
    my_lcd.draw(&line);

    rec.setCoords(79, 246);
    rec.setCoords1(90, 253);
    my_lcd.draw(&rec);

    Rectangle aux(0, 0, 14, 270, Color(255, 255, 255), Color(255, 255, 255));
    my_lcd.draw(&aux);

    //wellPump
    my_lcd.draw(&rec); // Pump

    Rrec.setCoords(81, 119); // Tube up
    Rrec.setCoords1(84, 246);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(81, 117);// Tube right
    Rrec.setCoords1(122, 120);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(119, 117);// Tube down
    Rrec.setCoords1(122, 153);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(27, 220);// well
    Rrec.setCoords1(90, 302);
    my_lcd.draw(&Rrec);

    //Filter
    Rrec.setCoords(200, 135);// tube right
    Rrec.setCoords1(220, 138);
    my_lcd.draw(&Rrec);

    Rrec.setRadius(4);
    Rrec.setCoords(157, 130);// filter
    Rrec.setCoords1(200, 152);
    my_lcd.draw(&Rrec);

    Rrec.setRadius(6);
    Rrec.setCoords(157, 152);// filter
    Rrec.setCoords1(200, 220);
    my_lcd.draw(&Rrec);
    Rrec.setRadius(1);

    Rrec.setCoords(217, 135);// tube down
    Rrec.setCoords1(220, 164);
    my_lcd.draw(&Rrec);

    //SurfaceTank
    rec.setCoords(134, 200);// valve
    rec.setCoords1(145, 207);
    my_lcd.draw(&rec);

    Rrec.setCoords(137, 135);// tube up
    Rrec.setCoords1(140, 200);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(138, 135);// tube right
    Rrec.setCoords1(157, 138);
    my_lcd.draw(&Rrec);

    rec.setCoords(98, 152);//tank
    rec.setCoords1(145, 220);
    my_lcd.draw(&rec);

    //filtered tank
    rec.setCoords(212, 162);// tank
    rec.setCoords1(259, 220);
    my_lcd.draw(&rec);

    rec.setCoords(212, 162);// valve
    rec.setCoords1(259, 220);
    my_lcd.draw(&rec);

    Rrec.setCoords(252, 147);// tube up
    Rrec.setCoords1(255, 202);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(252, 147);// tube right
    Rrec.setCoords1(279, 150);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(276, 148);//tube down
    Rrec.setCoords1(279, 168);
    my_lcd.draw(&Rrec);

    //UV
    Rrec.setCoords(252, 147);// tube right
    Rrec.setCoords1(255, 202);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(252, 147);// tube up
    Rrec.setCoords1(279, 150);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(276, 148);// tube right
    Rrec.setCoords1(279, 200);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(271, 200);//tube down
    Rrec.setCoords1(324, 211);
    my_lcd.draw(&Rrec);

    //UV_2
    Rrec.setCoords(316, 147);// tube up
    Rrec.setCoords1(319, 200);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(317, 147);// tube right
    Rrec.setCoords1(345, 150);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(342, 148);// tube down
    Rrec.setCoords1(345, 165);
    my_lcd.draw(&Rrec);

    rec.setCoords(248, 202);// UV
    rec.setCoords1(259, 209);
    my_lcd.draw(&rec);

    Line legs(272, 220, 292, 210, Color(0, 0, 0));
    my_lcd.draw(&legs);
    Line legs1(302, 210, 322, 220, Color(0, 0, 0));
    my_lcd.draw(&legs1);

    //PurifiedTank

    Rrec.setCoords(338, 164);// tank
    Rrec.setCoords1(380, 220);
    my_lcd.draw(&Rrec);

    rec.setCoords(369, 202);// valve
    rec.setCoords1(380, 209);
    my_lcd.draw(&rec);

    Rrec.setCoords(373, 204);// tube up - endTank
    Rrec.setCoords1(376, 80);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(374, 80); //tube right - endTank
    Rrec.setCoords1(403, 83);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(400, 80); //tube down - endTank
    Rrec.setCoords1(403, 109);
    my_lcd.draw(&Rrec);

    //End tank
    Rrec.setCoords(426, 156);// tube down
    Rrec.setCoords1(431, 183);
    my_lcd.draw(&Rrec);

    Rrec.setCoords(426, 182);// tube right
    Rrec.setCoords1(465, 187);
    my_lcd.draw(&Rrec);

    rec.setCoords(395, 91);//tank
    rec.setCoords1(453, 158);
    my_lcd.draw(&rec);
}

void drawStatusBackground(bool dontFillScreen)
{
    if (!dontFillScreen)
        my_lcd.Fill_Screen(0xFFFF);

    //Label loading(165,85,"Loading...",3,Color(0,70,200));
    //my_lcd.draw(&loading);

    titleLabel.setString("Status"); // Title
    my_lcd.draw(&title);
    Picture logoPhoto(400, 10, "PMWSL.bmp"); // logo
    my_lcd.draw(&logoPhoto);


    //Picture statusBackground(14,74,"schArd.bmp"); //Using p
    //my_lcd.draw(&statusBackground);

    drawStatusBackgroundPhoto();

    //Small logo
    btn1.enableAutoSize(false);
    label.setFontSize(2);
    label.setString("Menu"); // Label Menu
    btn1.setCoords(135, 234);
    btn1.setCoords1(260, 290);
    my_lcd.draw(&btn1);
    btn1.enableAutoSize(true);
}

void drawStatusBackground()
{
    drawStatusBackground(false);
}

// Draw voltage & amount of purified water
void drawStatusForeground(const char *voltage, const char *waterAmount)//TODO add water levels & other indicators
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

    btn2.enableAutoSize(false);
    label.setFontSize(2);
    btn2.setCoords(300, 234);
    btn2.setCoords1(420, 290);
    if (mainSwitchSt < 0) // ERROR
    {
        label.setString("FAILURE");
        btn2.setSecondaryColor(Color(239, 127, 26));
    }
    else if (mainSwitchSt == 0) // OFF
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
    btn2.enableAutoSize(true);

    drawStatusColors(0, 0, 0, 0, 0, 0, 0, 0, 0);
}

void drawStatusColors(bool wellPump, bool endPump, bool UVRelay, bool filterRelay, char well, char surfaceTank,char filteredTank, char purifiedTank,bool endTank) // false --> OFF, true -->ON, <0 --> LOW, = 0 --> Half, >0 --> FULL
{
    Color blue(81, 136, 223);
    Color white(0xFFFF);
    Color yellow(255, 255, 0);

    Rectangle rec1(80, 247, 89, 252, white, white); // big rectangle under the valve
    //wellPump
    if (wellPump)
    {
        rec1.setMainColor(yellow);
        rec1.setSecondaryColor(yellow);
    }
    my_lcd.draw(&rec1);

    if (wellPump)
    {
        rec1.setMainColor(blue);
        rec1.setSecondaryColor(blue);
    }
    rec1.setCoords(82, 120); // Tube up
    rec1.setCoords1(83, 245);
    my_lcd.draw(&rec1);

    rec1.setCoords(82, 118);// Tube right
    rec1.setCoords1(121, 119);
    my_lcd.draw(&rec1);

    rec1.setCoords(120, 118);// Tube down
    rec1.setCoords1(121, 205);
    my_lcd.draw(&rec1);


    //well_low
    rec1.setMainColor(blue);
    rec1.setSecondaryColor(blue);
    rec1.setCoords(28, 258);
    rec1.setCoords1(89, 301);
    my_lcd.draw(&rec1);

    //well_high
    if (!well)
    {
        rec1.setMainColor(white);
        rec1.setSecondaryColor(white);
    }
    rec1.setCoords1(78, 230); // Rectangle at the let of the valve
    rec1.setCoords(28, 259);
    my_lcd.draw(&rec1);
    rec1.setCoords1(89, 254); // Small Rectangle under valve
    rec1.setCoords(78, 259);
    my_lcd.draw(&rec1);
    rec1.setCoords(85, 230); // Small rectangle right of the tube
    rec1.setCoords1(89, 245);
    my_lcd.draw(&rec1);
    rec1.setCoords(78, 230); // Small rectangle left of the tube
    rec1.setCoords1(80, 245);
    my_lcd.draw(&rec1);


    //SufaceTank
    Rectangle rec2(135, 201, 144, 206, white, white);
    if (filterRelay)
    {
        rec2.setMainColor(yellow);
        rec2.setSecondaryColor(yellow);
    }
    my_lcd.draw(&rec2);

    //TubeSurfaceTank
    if (filterRelay)
    {
        rec2.setMainColor(blue);
        rec2.setSecondaryColor(blue);
    }
    rec2.setCoords(138, 136); // Tube up
    rec2.setCoords1(139, 199);
    my_lcd.draw(&rec2);
    rec2.setCoords(139, 136); // Tube right
    rec2.setCoords1(156, 137);
    my_lcd.draw(&rec2);


    //filter
    RoundRectangle recFilter(158, 131, 199, 151, 3, white, white);
    if (filterRelay)
    {
        recFilter.setMainColor(yellow);
        recFilter.setSecondaryColor(yellow);
    }
    my_lcd.draw(&recFilter);

    //TubeFilter
    if (filterRelay)
    {
        recFilter.setMainColor(blue);
        recFilter.setSecondaryColor(blue);
    }
    recFilter.setRadius(0);
    recFilter.setCoords(201, 136); // Tube right
    recFilter.setCoords1(219, 137);
    my_lcd.draw(&recFilter);
    recFilter.setCoords(218, 136); // Tube down
    recFilter.setCoords1(219, 215);
    my_lcd.draw(&recFilter);


    //surfaceTank_low
    rec2.setCoords(99, 211);
    rec2.setCoords1(144, 219);
    rec2.setMainColor(blue);
    rec2.setSecondaryColor(blue);
    my_lcd.draw(&rec2);

    //surfaceTank_medium
    if (surfaceTank == -1)
    {
        rec2.setMainColor(white);
        rec2.setSecondaryColor(white);
    }
    rec2.setCoords(99, 208); // Small Rectangle under valve
    rec2.setCoords1(144, 211);
    my_lcd.draw(&rec2);
    rec2.setCoords(99, 180); // Rectangle at the left of the valve
    rec2.setCoords1(133, 208);
    my_lcd.draw(&rec2);
    rec2.setCoords(133, 180); // Small Rectangle at the left of the tube
    rec2.setCoords1(136, 199);
    my_lcd.draw(&rec2);
    rec2.setCoords(141, 180); // Small Rectangle at the right of the tube
    rec2.setCoords1(144, 199);
    my_lcd.draw(&rec2);

    //surfaceTank_high
    if (surfaceTank == 0)
    {
        rec2.setMainColor(white);
        rec2.setSecondaryColor(white);
    }
    rec2.setCoords(99, 153); // Big Rectangle at the top right of the tube
    rec2.setCoords1(136, 180);
    my_lcd.draw(&rec2);
    rec2.setCoords(141, 153); // Rectangle at the top left of the tube
    rec2.setCoords1(144, 180);
    my_lcd.draw(&rec2);


    //UVPump
    Rectangle rec3(213, 213, 258, 219, white, white);
    if (UVRelay)
    {
        rec3.setMainColor(yellow);
        rec3.setSecondaryColor(yellow);
    }
    rec3.setCoords(249, 203);
    rec3.setCoords1(258, 208);
    my_lcd.draw(&rec3);

    //TubeUVPump
    if (UVRelay)
    {
        rec3.setMainColor(blue);
        rec3.setSecondaryColor(blue);
    }
    rec3.setCoords(253, 148); // Tube up
    rec3.setCoords1(254, 201);
    my_lcd.draw(&rec3);
    rec3.setCoords(253, 148); // Tube right
    rec3.setCoords1(278, 149);
    my_lcd.draw(&rec3);
    rec3.setCoords(277, 149); // Tube down
    rec3.setCoords1(278, 199);
    my_lcd.draw(&rec3);

    //UV
    if (UVRelay)
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
    recFilter.setCoords(272, 201);
    recFilter.setCoords1(323, 210);
    my_lcd.draw(&recFilter);

    //TubeUV
    recFilter.setRadius(0);
    if (UVRelay)
    {
        recFilter.setMainColor(blue);
        recFilter.setSecondaryColor(blue);
    }
    else
    {
        recFilter.setMainColor(white);
        recFilter.setSecondaryColor(white);
    }
    recFilter.setCoords(317, 148); // Tube up
    recFilter.setCoords1(318, 199);
    my_lcd.draw(&recFilter);
    recFilter.setCoords(318, 148); // Tube right
    recFilter.setCoords1(344, 149);
    my_lcd.draw(&recFilter);
    recFilter.setCoords(343, 149); // Tube down
    recFilter.setCoords1(344, 219);
    my_lcd.draw(&recFilter);


    //FilteredTank_low
    rec3.setCoords(213, 213);
    rec3.setCoords1(258, 219);
    rec3.setMainColor(blue);
    rec3.setSecondaryColor(blue);
    my_lcd.draw(&rec3);

    //FilteredTank_medium
    if (filteredTank == -1)
    {
        rec3.setMainColor(white);
        rec3.setSecondaryColor(white);
    }
    rec3.setCoords(213, 210); // Large rectangle under valve
    rec3.setCoords1(258, 213);
    my_lcd.draw(&rec3);
    rec3.setCoords(213, 180); // Big bottom rectangle under valve
    rec3.setCoords1(247, 210);
    my_lcd.draw(&rec3);
    rec3.setCoords(247, 180); // Large bottom rectangle at the left of the tube
    rec3.setCoords1(251, 201);
    my_lcd.draw(&rec3);
    rec3.setCoords(256, 180); // Large bottom rectangle at the right of the tube
    rec3.setCoords1(258, 201);
    my_lcd.draw(&rec3);

    //FilteredTank_high
    if (filteredTank == 0)
    {
        rec3.setMainColor(white);
        rec3.setSecondaryColor(white);
    }
    rec3.setCoords(213, 163); // Big top rectangle under valve
    rec3.setCoords1(247, 180);
    my_lcd.draw(&rec3);
    rec3.setCoords(247, 163); // Large top rectangle at the left of the tube
    rec3.setCoords1(251, 180);
    my_lcd.draw(&rec3);
    rec3.setCoords(256, 163); // Large top rectangle at the right of the tube
    rec3.setCoords1(258, 180);
    my_lcd.draw(&rec3);


    //EndPump
    Rectangle rec4(339, 213, 379, 219, white, white);

    if (endPump)
    {
        rec4.setMainColor(yellow);
        rec4.setSecondaryColor(yellow);
    }
    rec4.setCoords(370, 203);
    rec4.setCoords1(379, 208);
    my_lcd.draw(&rec4);

    //TubeEndPump
    if (endPump)
    {
        rec4.setMainColor(blue);
        rec4.setSecondaryColor(blue);
    }
    rec4.setCoords(374, 81); // Tube up
    rec4.setCoords1(375, 201);
    my_lcd.draw(&rec4);
    rec4.setCoords(375, 81); // Tube right
    rec4.setCoords1(402, 82);
    my_lcd.draw(&rec4);
    rec4.setCoords(401, 81); // Tube down
    rec4.setCoords1(402, 136);
    my_lcd.draw(&rec4);


    //PurifiedTank_low
    rec4.setCoords(339, 213);
    rec4.setCoords1(379, 219);
    rec4.setMainColor(blue);
    rec4.setSecondaryColor(blue);
    my_lcd.draw(&rec4);

    //PurifiedTank_medium
    if (purifiedTank == -1)
    {
        rec4.setMainColor(white);
        rec4.setSecondaryColor(white);
    }
    rec4.setCoords(339, 210); // Large rectangle under valve
    rec4.setCoords1(379, 213);
    my_lcd.draw(&rec4);
    rec4.setCoords(339, 180); // Big rectangle bottom left of the tube
    rec4.setCoords1(368, 210);
    my_lcd.draw(&rec4);
    rec4.setCoords(368, 180); // Large rectangle bottom left of the tube
    rec4.setCoords1(372, 201);
    my_lcd.draw(&rec4);
    rec4.setCoords(377, 180); // Large rectangle bottom right of the tube
    rec4.setCoords1(379, 201);
    my_lcd.draw(&rec4);

    //PurifiedTank_high
    if (purifiedTank == 0)
    {
        rec4.setMainColor(white);
        rec4.setSecondaryColor(white);
    }
    rec4.setCoords(339, 165); // Big rectangle top left of the tube
    rec4.setCoords1(368, 180);
    my_lcd.draw(&rec4);
    rec4.setCoords(368, 165); // Large rectangle top left of the tube
    rec4.setCoords1(372, 180);
    my_lcd.draw(&rec4);
    rec4.setCoords(377, 165); // Large rectangle top right of the tube
    rec4.setCoords1(379, 180);
    my_lcd.draw(&rec4);


    //EndTank_low
    Rectangle rec5(396, 135, 452, 157, blue, blue);// Big rectangle under valve
    my_lcd.draw(&rec5);

    //TubeEndTank
    rec5.setCoords(427, 157); // Rectangle exit tube down
    rec5.setCoords1(430, 182);
    my_lcd.draw(&rec5);
    rec5.setCoords(427, 183); // Rectangle exit tube right
    rec5.setCoords1(465, 186);
    my_lcd.draw(&rec5);


    //EndTank_high
    if (!endTank)
    {
        rec5.setMainColor(white);
        rec5.setSecondaryColor(white);
    }
    rec5.setCoords(396, 92); // Big rectangle top of the tank
    rec5.setCoords1(452, 135);
    my_lcd.draw(&rec5);
}

void clickStatus()
{
    if (btn1.isPressed()) { debug(F("Button MENU pressed"));
        changeStatus(LOADMENU);
    }
    else if (btn2.isPressed())
    {
        if (purificationStatus == ON)
        {
            debug(F("Button OFF pressed"));
            purificationStatus = OFF; // TODO send off command
            drawStatusForeground("15.4V", "320L");
        }
        else if (purificationStatus == OFF)
        {
            debug(F("Button ON pressed"));
            purificationStatus = ON; // TODO send on command
            drawStatusForeground("15.4V", "320L");
        }
        else if (purificationStatus < 0)
        {
            debug(F("Button FAILURE pressed")); // TODO Draw ERROR message
        }
        delay(500);
    }
}
