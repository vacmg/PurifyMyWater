const int voltPin = A0;   // seleccionar la entrada para el sensor
int volt;         // variable que almacena el valor raw (0 a 1023)
float fvolt;            // variable que almacena el voltaje (0.0 a 25.0)
const int rele = 49;
const bool cargar = 1;

void setup()
{
  Serial.begin(115200);
  for (int i = 2;i<10;i++)
  {
    pinMode(i,INPUT);
  }
  pinMode(23,INPUT_PULLUP);
  
  pinMode(22,OUTPUT);
  digitalWrite(22,1);
  pinMode(24,OUTPUT);
  digitalWrite(24,1);
  pinMode(26,OUTPUT);
  digitalWrite(26,1);
  pinMode(rele,OUTPUT); 
}

void loop()
{
  volt = analogRead(voltPin);          // realizar la lectura
    fvolt = floatmap(volt, 0, 1023, 0.0, 25.0);   // cambiar escala a 0.0 - 25.0
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

    
  for (int i = 2; i<10;i++)
  {
    Serial.println("Boya "+String(i)+": "+String(digitalRead(i)));
  }
  Serial.println("Proximidad: "+String(digitalRead(23)));
  Serial.println("Entrada A0: "+String(analogRead(A0)));
  Serial.println("Entrada A1: "+String(analogRead(A1)));
  Serial.println("Entrada A2: "+String(analogRead(A2)));
  delay(200);
}



// cambio de escala entre floats
float floatmap(float x, float in_min, float in_max, float out_min, float out_max)
{
   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
