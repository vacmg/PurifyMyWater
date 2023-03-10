#include "Communications/ComManager.h"

char mensaje[30];

ComManager server(&Serial1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(9600);

  delay(250);

  Serial.println("Server ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.messageManager();
}
