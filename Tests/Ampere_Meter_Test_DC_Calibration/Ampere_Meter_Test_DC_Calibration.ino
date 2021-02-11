const int voltPin = A0;   // seleccionar la entrada para el sensor
int volt;         // variable que almacena el valor raw (0 a 1023)
float fvolt;            // variable que almacena el voltaje (0.0 a 25.0)
const int rele = 49;
const bool cargar = 1;

void setup() {
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
  digitalWrite(22,0);
  pinMode(24,OUTPUT);
  digitalWrite(24,0);
  pinMode(26,OUTPUT);
  digitalWrite(26,0);
  pinMode(rele,OUTPUT); 
  Serial.begin(115200);
}

void loop() {
volt = analogRead(voltPin);          // realizar la lectura
   fvolt = floatmap(volt, 0, 1023, 0.0, 25.0);   // cambiar escala a 0.0 - 25.0
   Serial.println(fvolt);                     // mostrar el valor por serial
   Serial.println(analogRead(A1));
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

  
  float voltajeSensor =get_voltage(25000);//obtenemos voltaje del sensor(10000 muestras) 
  Serial.print("Voltaje del sensor: ");
  Serial.println(voltajeSensor ,8);     
}


float get_voltage(int n_muestras)
{
  float voltage=0;
  
  for(int i=0;i<n_muestras;i++)
  {
    voltage =voltage+analogRead(A1) * (5.0 / 1023.0);    
  }
  voltage=voltage/n_muestras;
  return(voltage);
}

// cambio de escala entre floats
float floatmap(float x, float in_min, float in_max, float out_min, float out_max)
{
   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
