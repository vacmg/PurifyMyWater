// https://lastminuteengineers.com/multiple-ds18b20-arduino-tutorial/

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 52

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

int deviceCount = 0;
float tempC;

byte Thermometer[8];

void setup(void)
{
  sensors.begin();  // Start up the library
  Serial.begin(9600);
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");
  
  Serial.println("Printing addresses...");
  for (int i = 0;  i < deviceCount;  i++)
  {
    Serial.print("Sensor ");
    Serial.print(i+1);
    Serial.print(" : ");
    sensors.getAddress(Thermometer, i);
    printAddress(Thermometer);
    Serial.println("");
  }
}

void printAddress(byte deviceAddress[8])
{ 
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print("0x");
    if (deviceAddress[i] < 0x10) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
    if (i < 7) Serial.print(", ");
  }
  Serial.println("");
}

void loop(void)
{ 
  // Send command to all the sensors for temperature conversion
  sensors.requestTemperatures(); 
  
  // Display temperature from each sensor
  for (int i = 0;  i < deviceCount;  i++)
  {
    Serial.print("Sensor ");
    Serial.print(i+1);
    Serial.print(" : ");
    tempC = sensors.getTempCByIndex(i);
    Serial.print(tempC);
    //Serial.print((char)176);//shows degrees character
    Serial.print(" C  |  ");
    Serial.print(DallasTemperature::toFahrenheit(tempC));
    //Serial.print((char)176);//shows degrees character
    Serial.println(" F");
  }
  
  Serial.println("");
  delay(1000);
}

// SI SE USA ADDRESS

//#include <OneWire.h>
//#include <DallasTemperature.h>
//
//// Data wire is plugged into port 2 on the Arduino
//#define ONE_WIRE_BUS 2
//
//// Setup a oneWire instance to communicate with any OneWire devices
//OneWire oneWire(ONE_WIRE_BUS);
//
//// Pass our oneWire reference to Dallas Temperature.
//DallasTemperature sensors(&oneWire);
//
//// Addresses of 3 DS18B20s
//uint8_t sensor1[8] = { 0x28, 0xEE, 0xD5, 0x64, 0x1A, 0x16, 0x02, 0xEC };
//uint8_t sensor2[8] = { 0x28, 0x61, 0x64, 0x12, 0x3C, 0x7C, 0x2F, 0x27 };
//uint8_t sensor3[8] = { 0x28, 0x61, 0x64, 0x12, 0x3F, 0xFD, 0x80, 0xC6 };
//
//void setup(void)
//{
//  Serial.begin(9600);
//  sensors.begin();
//}
//
//void loop(void)
//{
//  sensors.requestTemperatures();
//  
//  Serial.print("Sensor 1: ");
//  printTemperature(sensor1);
//  
//  Serial.print("Sensor 2: ");
//  printTemperature(sensor2);
//  
//  Serial.print("Sensor 3: ");
//  printTemperature(sensor3);
//  
//  Serial.println();
//  delay(1000);
//}
//
//void printTemperature(DeviceAddress deviceAddress)
//{
//  float tempC = sensors.getTempC(deviceAddress);
//  Serial.print(tempC);
//  Serial.print((char)176);
//  Serial.print("C  |  ");
//  Serial.print(DallasTemperature::toFahrenheit(tempC));
//  Serial.print((char)176);
//  Serial.println("F");
//}
