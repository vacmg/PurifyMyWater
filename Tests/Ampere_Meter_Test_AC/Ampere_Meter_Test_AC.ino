/* This code works with ACS712 current sensor, it permits the calculation of the signal TRMS
 * Visit www.surtrtech.com for more details
 */

#include <Filters.h>                      //This library does a massive work check it's .cpp file

#define ACS_Pin A2                        //Sensor data pin on A0 analog input

//Please check the ACS712 Tutorial video by SurtrTech to see how to get them because it depends on your sensor, or look below
float intercept = -0.0741; // to be adjusted based on calibration testing
float slope = 0.0327; // to be adjusted based on calibration testing // 0.25A for 60w test load

float ACS_Value;                              //Here we keep the raw data valuess
float testFrequency = 50;                    // test signal frequency (Hz)
float windowLength = 40.0/testFrequency;     // how long to average the signal, for statistist

const int voltPin = A0;   // seleccionar la entrada para el sensor
int volt;         // variable que almacena el valor raw (0 a 1023)
float fvolt;            // variable que almacena el voltaje (0.0 a 25.0)
const int rele = 49;
const bool cargar = 1;
                      
RunningStatistics inputStats;                 // create statistics to look at the raw test signal
float Amps_TRMS; // estimated actual current in amps

unsigned long printPeriod = 1000; // in milliseconds
// Track time in milliseconds since last reading 
unsigned long previousMillis = 0;
unsigned long pMillis = 0;

void setup() {
  Serial.begin( 115200 );    // Start the serial port
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(37,OUTPUT);
  digitalWrite(37,0);
  pinMode(35,OUTPUT);
  digitalWrite(35,0);
  pinMode(45,OUTPUT);
  digitalWrite(45,0);
  pinMode(22,OUTPUT);
  digitalWrite(22,1);
  pinMode(24,OUTPUT);
  digitalWrite(24,1);
  pinMode(26,OUTPUT);
  digitalWrite(26,1);
  pinMode(rele,OUTPUT); 
  inputStats.setWindowSecs( windowLength );     //Set the window length
}

void loop() {
    volt = analogRead(voltPin);          // realizar la lectura
    fvolt = floatmap(volt, 0, 1023, 0.0, 25.0);   // cambiar escala a 0.0 - 25.0
    if((unsigned long)(millis() - pMillis) >= printPeriod) { //every second we do the calculation
      pMillis = millis();   // update time
      //Serial.print(fvolt);  
    }// mostrar el valor por serial
    if (cargar == 0)
    {
     fvolt = 20;
    }
    if (fvolt <= 14)
    {
     digitalWrite(rele,1); //invertido
    }
    if (fvolt >= 15.75)
    {
     digitalWrite(rele,0);
    }
    
    ACS_Value = analogRead(ACS_Pin);  // read the analog in value:
    inputStats.input(ACS_Value);  // log to Stats function
        
    if((unsigned long)(millis() - previousMillis) >= printPeriod) { //every second we do the calculation
      previousMillis = millis();   // update time
      
      Amps_TRMS = intercept + slope * inputStats.sigma();

      Serial.print( "No_Calib: " ); 
      Serial.print( inputStats.sigma() , 4);
      Serial.print( "\t Amps: " ); 
      Serial.println( Amps_TRMS , 4);

    }
}

// cambio de escala entre floats
float floatmap(float x, float in_min, float in_max, float out_min, float out_max)
{
   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* About the slope and intercept
 * First you need to know that all the TRMS calucations are done by functions from the library, it's the "inputStats.sigma()" value
 * At first you can display that "inputStats.sigma()" as your TRMS value, then try to measure using it when the input is 0.00A
 * If the measured value is 0 like I got you can keep the intercept as 0, otherwise you'll need to add or substract to make that value equal to 0
 * In other words " remove the offset"
 * Then turn on the power to a known value, for example use a bulb or a led that ou know its power and you already know your voltage, so a little math you'll get the theoritical amps
 * you divide that theory value by the measured value and here you got the slope, now place them or modify them
 */
