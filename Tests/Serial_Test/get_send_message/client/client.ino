#include "Communications.h"

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial.begin(115200);
  delay(500);
  Serial.println("READY_CLIENT");

  //Serial1.println("patata");
  //Serial.println("patata");
  /*Serial1.write(-23);
  Serial1.write(7);
  Serial1.write('p');
  Serial1.write('a');
  Serial1.write('t');
  Serial1.write('a');
  Serial1.write('t');
  Serial1.write('a');
  Serial1.write('\n');*/
  //Serial.println("END");
  

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Input message: ");
  while(!Serial.available());
  Serial.println(sendMessage(Serial.readStringUntil('\n').c_str(), &Serial1));
}
