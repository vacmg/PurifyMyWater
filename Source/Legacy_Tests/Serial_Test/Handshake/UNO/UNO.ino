void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
handshake();
}

void loop() {
  // put your main code here, to run repeatedly:
}

void handshake() // slave handshake // note: the ability to answer to 'A' must be present in all the program
{
  while(!Serial.available());
  if (Serial.read() == 'A')
  {
    Serial.print('Z');
  }
  else
  {
    Serial.print('F');
  }
  delay(500);
  while(Serial.available())
  {
    Serial.read();
  }
}
