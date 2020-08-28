void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial.println(F("CONNECTING..."));
Serial1.begin(9600);
handshake(5000);
Serial.println(F("\nPress enter to start the test\n"));
while (!Serial.available());
while (Serial.available())
{
  Serial.read();
}

test();

}

void test()
{
  char message[32]; // fixed max size
  sprintf(message, "%c%u,%s,%d", 'f', (unsigned int)45039, "patata", 2); // that is the way of building a message
  
  Serial.print(F("Message w/out crc: "));
  Serial.print(message);
  
  unsigned int tam = strlen(message); // calculate size to use it for the crc (tam does not include null)
  byte crc = CRC8(message,tam); // the null is excluded
  char temp[4];
  sprintf(temp, "C%d", (int)crc);
  strcat(message, temp);
  
  Serial.print(F(" CRC: "));
  Serial.println(crc);
  Serial.print(F("Message to send: M"));
  Serial.println(message);
  delay(1500);
  Serial1.print('M'); // message init char
  Serial1.print(message); // do not forget the ln for the line new terminator char
  Serial.println(F("Message sent, going into mirror mode\n\n"));
}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial1.available()) // Mirror UNO output
{
  Serial.write(Serial1.read());
}
//else
//{
//  Serial.println(F("NOTHING TO MIRROR"));
//  Serial1.print('A');
//}
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
    while(1); // instead perform error actions
  }
}

//CRC-8 - based on the CRC8 formulas by Dallas/Maxim
//code released under the terms of the GNU GPL 3.0 license
byte CRC8(const byte *data, size_t dataLength)
{
  byte crc = 0x00;
  while (dataLength--) 
  {
    byte extract = *data++;
    for (byte tempI = 8; tempI; tempI--)
   {
      byte sum = (crc ^ extract) & 0x01;
      crc >>= 1;
      if (sum)
     {
        crc ^= 0x8C;
      }
      extract >>= 1;
    }
  }
  return crc;
}
