const int voltPin = A0;   // seleccionar la entrada para el sensor
int volt;         // variable que almacena el valor raw (0 a 1023)
float fvolt;            // variable que almacena el voltaje (0.0 a 25.0)
const int rele = 33;
const bool cargar = 1;
 
void setup() {
  Serial.begin(115200);
  pinMode(rele,OUTPUT);
  pinMode(49,OUTPUT);
  digitalWrite(49,0); 
}
 
void loop() {
   volt = analogRead(voltPin);          // realizar la lectura
   Serial.println(volt);
   fvolt = floatmap(volt, 0, 1023, 0.0, 25.0);   // cambiar escala a 0.0 - 25.0
   Serial.println(fvolt);                     // mostrar el valor por serial
   if (cargar == 0)
   {
    fvolt = 20;
   }
   if (fvolt <= 14.5)
   {
    digitalWrite(rele,0); //invertido
   }
   if (fvolt >= 15.75)
   {
    digitalWrite(rele,1);
   }
   delay(150);
}
 
// cambio de escala entre floats
float floatmap(float x, float in_min, float in_max, float out_min, float out_max)
{
   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
