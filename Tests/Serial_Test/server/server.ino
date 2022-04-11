#include "Communications.h"

void setup() {
  Serial1.begin(115200);
  Serial.begin(115200);
  delay(500);
  Serial.println("READY_SERVER");

}
char message[64];
void loop() {
  if(Serial1.available())
  {
    Serial.println(getMessage(message,Serial1));
    //Serial.println(message);
    //printAsHex(message, 8);
  }

}
