/*  This test checks the ability to send data to other arduino (from now UNO) and verify the integrity of it using a CRC8 algorythm
 *  This code is for the Master arduino (from now MEGA)
 */

void setup() 
{
  Serial.begin(115200); // connect to computer
  Serial.println(F("CONNECTING..."));
  Serial1.begin(9600); // connect to UNO
  if (handshake(5000)) // As on UNO/NANO/MEGA boards if (Serial) returns always true, is necessary to use a workarround and implement a ping command to see if UNO is available
  {
    Serial.println(F("SUCCESSFUL HANDSHAKE"));
  }
  else
  {
    Serial.println(F("HANDSHAKE ERROR"));
    while(1); // in a final version, perform error actions instead of while(1)
  }
  Serial.println(F("\nPress enter in the serial com (or send any value) to start the test\n"));
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
  sprintf(message, "%c%u,%s,%d", 'f', (unsigned int)45039, "patata", 2); // that is the way of building a message with the command f and the values 45039, patata,2 
  
  Serial.print(F("Message w/out crc and header: "));
  Serial.print(message);
  
  unsigned int tam = strlen(message); // calculate size to use it for the crc (tam does not include neither the header nor the null)
  byte crc = CRC8(message,tam); // compute CRC8 of the message
  char temp[4]; // create a temporal string to include the crc into the message
  sprintf(temp, "C%d", (int)crc); // encode the crc into a string
  strcat(message, temp); // include the crc string into the message
  
  Serial.print(F(" CRC: "));
  Serial.println(crc);
  Serial.print(F("Message to send: M"));
  Serial.println(message);
  delay(2500); // wait some time for you to review the info
  Serial1.print('M'); // send message initializer
  Serial1.print(message); // send message
  Serial.println(F("Message sent, going into mirror mode\n\n"));
}

void loop() // after the test, mirror UNO's output to receive debug data
{
  if (Serial1.available()) // Mirror UNO output
  {
    Serial.write(Serial1.read());
  }
}

bool handshake(unsigned long timeout)
{
  unsigned long pmillis = millis(); // used to store the start time of the handshake
  while (!Serial1.available() && (millis() < (pmillis + timeout))) // wait for timeout or data from UNO and send a ping message
  {
    Serial1.print('A');
    delay(300);
  }
  bool ok = 0; // used to store the resoult of the handsake: if the pong message is received, it changes to 1
  while(Serial1.available()) // determine if pong message is in the received buffer and clean it
  {
    if (Serial1.read() == 'Z')
    {
      ok = 1;
    }
  }
  return ok; // return resoult of the handshake
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
