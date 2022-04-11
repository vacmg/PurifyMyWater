#include "Communications.h"

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial.begin(115200);
  delay(500);
  Serial.println("READY_CLIENT");

  //Serial1.println("patata");
  //Serial.println("patata");
  Serial.println(sendMessage("patata", Serial1));
  Serial.println("END");
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
