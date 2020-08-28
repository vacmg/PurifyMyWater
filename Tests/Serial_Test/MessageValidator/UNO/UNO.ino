void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println(F("Ready"));
}

void loop() {
  // put your main code here, to run repeatedly:

}

void serialEvent()
{
  delay(100);
  char input = Serial.read();
  if (input == 'M')
  {
    char message[32];
    byte i = 0;
    while (Serial.available())
    {
      message[i] = Serial.read();
      i++;
    }
    message[i] = '\0';
    if (verify(message))
    {
      Serial.println(F("CRC MATCHED"));
    }
    else
    {
      Serial.println(F("CRC MISMATCH"));
    }
  }
  else if (input == 'A')
  {
    Serial.print('Z');
  }
  else
  {
    Serial.println(F("NICE BUG BRO!!!"));
  }
}

bool verify(char* message)
{
  Serial.print(F("ORIGINAL: "));
  Serial.println(message);
  delay(100);
  size_t tam = strlen(message);
  message = strtok(message, "C"); // split the message into message and crc
  int crc = (int)CRC8(message,strlen(message)); // compute crc of the message w/out crc
  int prevcrc;
  sscanf(strtok(NULL,'\n'), "%i", &prevcrc);
  Serial.print(F("AFTER STRTOK: "));
  Serial.println(message);
  delay(100);
  Serial.print(F("CRC: "));
  Serial.println(crc);
  delay(100);
  Serial.print(F("ORIGINAL CRC: "));
  Serial.println(prevcrc);
  delay(100);
  return (crc == prevcrc);
}

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
