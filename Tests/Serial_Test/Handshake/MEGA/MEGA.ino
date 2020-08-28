#define tout 5000 // 5 seconds

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial.println(F("HELLO"));
Serial1.begin(9600);
handshake(tout);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void handshake(unsigned long timeout)
{
  unsigned long pmillis = millis();
  while (!Serial1.available() && (millis() < (pmillis + timeout)))
  {
    Serial1.print('A');
    delay(300);
  }
  bool ok = 0;
  while(Serial1.available())
  {
    if (Serial1.read() == 'Z')
    {
      ok = 1;
    }
  }
  if (ok)
  {
    Serial.println(F("SUCCESSFUL HANDSHAKE"));
  }
  else
  {
    Serial.println(F("HANDSHAKE ERROR"));
    while(1);
  }
}
