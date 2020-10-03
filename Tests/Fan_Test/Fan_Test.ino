const int voltPin = A0;   // seleccionar la entrada para el sensor
int volt;         // variable que almacena el valor raw (0 a 1023)
float fvolt;            // variable que almacena el voltaje (0.0 a 25.0)
const int rele = 53;
const bool cargar = 1;
bool sw = 1;
byte rl;
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
   delay(150);
}
 
// cambio de escala entre floats
float floatmap(float x, float in_min, float in_max, float out_min, float out_max)
{
   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup()
{
  for (int i = 22;i<=26;i+=2)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,0);
  }
  pinMode(13,OUTPUT);
  pinMode(53,OUTPUT);
  Serial.begin(115200);
  Serial.println(F("Selecciona un ventilador y enciendelo o apagalo\n1 - fan 1\n2 - fan 2\n3 fan 3\na - todos los ventiladores"));
}

void serialEvent()
{
  char data = Serial.read();
  if (sw)
  {
    sw = 0;
    switch (data)
    {
      case '1':
      rl = 22; // bomba UV
      break; 
      case '2':
      rl = 24; // rele UV
      break;
      case '3':
      rl = 26; // rele filtro
      break;
      case 'a': // todos on
      sw = 1;
      delay(10);
      while (!Serial.available()){}
      bool mode = 0;
      data = Serial.read();
      for (int i = 22;i<=26;i+=2)
      {
        digitalWrite(i,mode);
        delay(300);
      }
      break;
      default:
      rl = 13; // fallo
      Serial.println(F("Eso no es un rele"));
    }
  }
  else
  {
    sw = 1;
    if (data == '1') // encender
    {
      digitalWrite(rl,1); // va invertido
    }
    else if (data == '0')
    {
      digitalWrite(rl,0);
    }
    else
    {
      Serial.println(F("Dude wtf!!!"));
    }
  }
}
