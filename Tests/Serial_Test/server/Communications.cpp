//
// Created by Víctor on 08/03/2022.
//

#include "Communications.h"

/*
 * [CRC][size][payload]\n
 * CRC: CRC8 code of [size][payload]
 * size: size in bytes of [size]+[payload]
 * payload: useful data of the message
 * \n: terminator character
 */


bool sendMessage(char* payload, HardwareSerial serial)
{
    byte payloadLength = strlen(payload);
    if(payloadLength>MAXMSGSIZE)
    {
        debug(Message(F("Payload exceeded maximum message size: ")+payloadLength+" > "+MAXMSGSIZE));
    }
    char message[MAXRAWMSGSIZE];
    message[1] = payloadLength+1; // set size of the message
    strcpy(&message[2],payload); // copy payload to message
    message[0] = CRC8((byte*)&message[1],message[1]); // set CRC of the message

    bool successfulSend = false;
    for(byte i = 0; !successfulSend && i<MAXMSGRETRIES; i++)
    {
        serial.println(message);//[CRC][size][payload]\n
        unsigned long startTime = millis();
        while (!successfulSend && millis()-startTime<MSGTIMEOUT)
        {
            if(serial.available() && serial.read()==ACK)
                successfulSend = true;
        }
        flush(serial);
    }
    return successfulSend;
}

bool getMessage(char* message, HardwareSerial serial)
{
    delay(1000);
    Serial.println(serial.available());
    delay(1000);
    bool messageReceived = false;
    for (byte i = 0; serial.available()&&!messageReceived&&i<MAXRAWMSGSIZE;i++)
    {
      char c = serial.read();
      if(c=='\n')
      {
        c = '\0';
        messageReceived = true;
        flush(serial);
      }
      message[i] = c;
    }
    
    Serial.println(message);
    flush(serial);
    printAsHex(message, 8);
    if (verifyMessage(message)) // verify message
    {
        Serial.write(ACK);
        return true;
    }
    return false;
}

bool verifyMessage(char* message)
{
    byte CRC = message[0]; // Origin CRC code
    byte size = message[1]; // size of [tam]+[message]
    byte realCRC = CRC8((byte*) &message[1],size); // get CRC8 of [tam][message]
    return CRC==realCRC;
}

//This function returns a CRC8 Checksum code from an array of any size
//CRC-8 Checksum - based on the CRC8 formulas by Dallas/Maxim
//code released under the terms of the GNU GPL 3.0 license
byte CRC8(const byte* data, size_t dataLength)
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

// This function flushes an input HardwareSerial and discards all data on the input buffer
void flush(HardwareSerial serial)
{
    while (serial.available())
    {
        serial.read();
    }
}

void printAsHex(char* string, int size)
{
  for(int i = 0; i<size;i++)
  {
    Serial.println(string[i],DEC);
  }
}
