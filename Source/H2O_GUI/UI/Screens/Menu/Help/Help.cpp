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
    draw6ButtonsLayout("topic1","topic2","topic3","topic4","topic5","topic6",false,false,false);
}
void drawHelpTopic()
{
    drawBackground();
    // Title Menu
    titleLabel.setString("Help");
    my_lcd.draw(&title);
    // TextBoxTopic
    Label helpLabel(1,1,"",1,Color());
    Rectangle frame(0,0,0,0,Color());
    TextBox helpTextbox(25,100,455,300,"test.txt",&frame ,&helpLabel);
    my_lcd.draw(&helpTextbox);
}