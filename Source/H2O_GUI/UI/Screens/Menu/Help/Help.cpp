//
// Created by jst83 on 08/09/2022.
//

#include "Help.h"

void drawHelpMenu()
{
    drawBackground();
    // Title Menu
    titleLabel.setString("Help");
    my_lcd.draw(&title);
    // Layout6buttons
    // btn1 --> topLeft; btn2 --> centerLeft; btn3 --> bottomLeft; btn4 --> topRight; btn5 --> centerRight; btn6 --> bottomRight; btn7 --> Previous; btn8 --> Next; btn9 --> topHelp; btn10 --> centerHelp; btn11 --> bottomHelp; If fontSize = NULL, autoFontSize; len(fontSize) = 6
    draw6ButtonsLayout("topic1","topic2","topic3","topic4","topic5","topic6",false,false,false);
}

void drawHelpTopic()
{
    drawBackground(); //TODO pintar de forma inteligente
    // Title Menu
    titleLabel.setString("Help");
    my_lcd.draw(&title);
    // TextBoxTopic
    Label helpLabel(1,1,"",1,Color());
    Rectangle frame(0,0,0,0,Color());
    TextBox helpTextbox(25,100,455,300,helpPath,&frame ,&helpLabel);
    my_lcd.draw(&helpTextbox);
}

void clickHelp()
{
    switch (page) {
        case 1:
            if(btn1.isPressed())
            {
                strcpy(helpPath,getPath(HelpTopic1_PATH));
                debug("HelpTopic1");
                changeScreenStatus(LOADHELPTOPIC);
            }
            else if (btn2.isPressed())
            {
                strcpy(helpPath,getPath(HelpTopic2_PATH));
                debug("HelpTopic2");
                changeScreenStatus(LOADHELPTOPIC);
            }
            else if (btn3.isPressed())
            {
                strcpy(helpPath,getPath(HelpTopic3_PATH));
                debug("HelpTopic3");
                changeScreenStatus(LOADHELPTOPIC);
            }
            else if (btn4.isPressed())
            {
                strcpy(helpPath,getPath(HelpTopic4_PATH));
                debug("HelpTopic4");
                changeScreenStatus(LOADHELPTOPIC);
            }
            else if (btn5.isPressed())
            {
                strcpy(helpPath,getPath(HelpTopic5_PATH));
                debug("HelpTopic5");
                changeScreenStatus(LOADHELPTOPIC);
            }
            else if (btn6.isPressed())
            {
                strcpy(helpPath,getPath(HelpTopic6_PATH));
                debug("HelpTopic6");
                changeScreenStatus(LOADHELPTOPIC);
            }
    }
}

void clickHelpTopic()
{
//TODO hata aqui
}
