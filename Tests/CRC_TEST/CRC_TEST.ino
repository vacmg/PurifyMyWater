void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial.println(F("READY"));
}

void loop() {
  // put your main code here, to run repeatedly:

}

void serialEvent()
{
  delay(200);
  size_t tam = Serial.available(); // el \n se cambia por \0 --> 4 char + \0 --> tam = 5
  char datos[tam];
  unsigned int i = 0;
  while (Serial.available())
  {
    datos[i] = Serial.read();
    Serial.print(F("datos["));
    Serial.print(i);
    Serial.print(F("] = "));
    Serial.println(datos[i]);
    i++;
  }
  datos[i-1] = '\0'; //change \n with null terminator
  Serial.print(F("tam: "));
  Serial.println(tam);
  Serial.println(datos);
  Serial.println(CRC8(datos, tam));
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
