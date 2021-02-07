/*This code works with ACS712 Current sensor, it permits to read the raw data
  It's better to use it with Serial Plotter
  More details on www.surtrtech.com
*/

#define Current_sensor A1  //The sensor analog input pin

float i;

const int voltPin = A0;   // seleccionar la entrada para el sensor
int volt;         // variable que almacena el valor raw (0 a 1023)
float fvolt;            // variable que almacena el voltaje (0.0 a 25.0)
const int rele = 49;
const bool cargar = 1;

void setup() {

Serial.begin(9600);
pinMode(A0, INPUT);
  //pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(37,OUTPUT);
  digitalWrite(37,0);
  pinMode(35,OUTPUT);
  digitalWrite(35,0);
  pinMode(45,OUTPUT);
  digitalWrite(45,0);
  pinMode(22,OUTPUT);
  digitalWrite(22,0);
  pinMode(24,OUTPUT);
  digitalWrite(24,0);
  pinMode(26,OUTPUT);
  digitalWrite(26,0);
pinMode(Current_sensor, INPUT);
pinMode(rele, OUTPUT);

}

void loop() {
  volt = analogRead(voltPin);          // realizar la lectura
    fvolt = floatmap(volt, 0, 1023, 0.0, 25.0);   // cambiar escala a 0.0 - 25.0
    
  if (cargar == 0)
    {
     fvolt = 20;
    }
    //Serial.println(fvolt);
    if (fvolt <= 14.5)
    {
     digitalWrite(rele,1); //invertido
    }
    if (fvolt >= 15.75)
    {
     digitalWrite(rele,0);
    }
  i = analogRead(Current_sensor);
  Serial.println(i);
  delay(50);                     //Modifying or removing the delay will change the way the signal is shown 
                                  //set it until you get the correct sinewave shap

}

// cambio de escala entre floats
float floatmap(float x, float in_min, float in_max, float out_min, float out_max)
{
   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
