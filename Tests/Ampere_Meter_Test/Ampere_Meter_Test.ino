const int voltPin = A0;   // seleccionar la entrada para el sensor
int volt;         // variable que almacena el valor raw (0 a 1023)
float fvolt;            // variable que almacena el voltaje (0.0 a 25.0)
const int rele = 53;
const bool cargar = 0;

// Sensibilidad del sensor en V/A
float SENSIBILITY5A = 0.185;   // Modelo 5A
float SENSIBILITY20A = 0.100; // Modelo 20A
//float SENSIBILITY = 0.066; // Modelo 30A
 
int SAMPLESNUMBER = 100;
 
void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(49,OUTPUT);
  digitalWrite(49,0);
  pinMode(41,OUTPUT);
  digitalWrite(41,0);
  pinMode(39,OUTPUT);
  digitalWrite(39,0);
  pinMode(rele,OUTPUT); 
}
 
void loop() {
   volt = analogRead(voltPin);          // realizar la lectura
   fvolt = floatmap(volt, 0, 1023, 0.0, 25.0);   // cambiar escala a 0.0 - 25.0
   Serial.println(fvolt);                     // mostrar el valor por serial
   if (cargar == 0)
   {
    fvolt = 20;
   }
   if (fvolt <= 14.5)
   {
    digitalWrite(rele,1); //invertido
   }
   if (fvolt >= 15.75)
   {
    digitalWrite(rele,0);
   }
   float current = getCorriente(A1, SAMPLESNUMBER, SENSIBILITY20A);
   float currentRMS = 0.707 * current;
   float power = fvolt * currentRMS;
 
   printMeasure("Intensidad A1: ", current, "A ,");
   printMeasure("Irms A1: ", currentRMS, "A ,");
   printMeasure("Potencia A1: ", power, "W");
   current = getCorriente(A2, SAMPLESNUMBER, SENSIBILITY5A);
   currentRMS = 0.707 * current;
   power = fvolt * currentRMS;
 
   printMeasure("Intensidad A2: ", current, "A ,");
   printMeasure("Irms A2: ", currentRMS, "A ,");
   printMeasure("Potencia A2: ", power, "W");
   delay(150);
}
 
// cambio de escala entre floats
float floatmap(float x, float in_min, float in_max, float out_min, float out_max)
{
   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
 
void printMeasure(String prefix, float value, String postfix)
{
   Serial.print(prefix);
   Serial.print(value, 3);
   Serial.println(postfix);
}
 
float getCorriente(int sensor, int samplesNumber, float sensibility)
{
   float voltage;
   float corrienteSum = 0;
   for (int i = 0; i < samplesNumber; i++)
   {
      voltage = analogRead(sensor) * 5.0 / 1023.0;
      corrienteSum += (voltage - 2.5) / sensibility;
   }
   return(corrienteSum / samplesNumber);
}
