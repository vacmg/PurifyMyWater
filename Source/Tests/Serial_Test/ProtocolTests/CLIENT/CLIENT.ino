#include "Communications/ComManager.h"
#include "Communications/Communications.h"
char mensaje[30];

ComManager server(&Serial1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(9600);

  delay(250);

  Serial.println("Client ready");

  Serial.println(Communications::createRequestMessage(mensaje, "var3", "fun4"));
  Serial.println(mensaje);
  Serial.println(server.sendMessage(mensaje));
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
