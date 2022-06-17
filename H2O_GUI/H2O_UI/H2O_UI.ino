#include "UI.h"

#define DEBUG true

//Main Functions

void setup()
{
#if DEBUG
    Serial.begin(115200);
    delay(200);
    Serial.println(F("Connected"));
    delay(50);
#endif
    UISetup();

    //todo Test code after this line

    //while (true); // TODO delete or comment this

    //todo Test code before this line

#if DEBUG
    Serial.println(F("\nSetup Done\n"));
    delay(50);
#endif
}

void loop()
{
    UI();
}
