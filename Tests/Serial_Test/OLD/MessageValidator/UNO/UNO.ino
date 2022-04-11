/*  This test checks the ability to receive data from other arduino (from now MEGA) and verify the integrity of it using a CRC8 algorythm
 *  This code is for the Slave arduino (from now UNO)
 */
void setup() 
{
  Serial.begin(9600); // connect to MEGA
}

void loop() {} // not used in this example

void serialEvent() // this special function runs when Serial.available() returns True (so, when serial data is received)
{
  delay(100); // wait a little to receive all the data (this value can be reduced to optimize the function)
  char input = Serial.read(); // get the message header
  if (input == 'M') // if it is a normal message
  {
    char message[32]; // create a string to store it
    byte i = 0;
    while (Serial.available())
    {
      message[i] = Serial.read(); // and store it
      i++;
    }
    message[i] = '\0'; // don't forget the c string null terminator in the last used position
    if (verify(message)) // verify the message and remove crc from it
    {
      Serial.println(F("CRC MATCHED"));
    }
    else
    {
      Serial.println(F("CRC MISMATCH"));
    }
  }
  else if (input == 'A') // send pong if ping is received
  {
    Serial.print('Z');
  }
  else // yep, it that happens it means that the data sent is not recognizable
  {
    Serial.println(F("NICE BUG BRO!!!\n What I have received is: "));
    while(Serial.available())
    {
      Serial.write(Serial.read()); // send the received data for you to check what the message received contains
    }
    Serial.println();
  }
}

// This function checks the message and delete the crc from it
bool verify(char* message)
{
  Serial.print(F("ORIGINAL: "));
  Serial.println(message);
  delay(100);
  size_t tam = strlen(message); // get the size of the message
  message = strtok(message, "C"); // split the message into message and crc and update message string with only the message
  int crc = (int)CRC8(message,strlen(message)); // compute crc of the message w/out crc
  int prevcrc;
  sscanf(strtok(NULL,'\n'), "%i", &prevcrc); // get crc from message and store it as an integer
  Serial.print(F("AFTER STRTOK: "));
  Serial.println(message);
  delay(100);
  Serial.print(F("CRC: "));
  Serial.println(crc);
  delay(100);
  Serial.print(F("ORIGINAL CRC: "));
  Serial.println(prevcrc);
  delay(100);
  return (crc == prevcrc); // compare the calculated crc with the original one and return the resoult
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
