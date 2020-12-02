bool sw = 1;
byte rl;
void setup()
{
  for (int i = 37;i<=53;i+=2)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,1);
  }
  pinMode(13,OUTPUT);
  Serial.begin(115200);
  Serial.println(F("Selecciona un rele y enciendelo o apagalo\ns - SSR rele de voltaje\np - pantalla\ni - inversor\no - bomba pozo\nf - bomba fin\nu - bomba UV\nv - rele de UV\nl - rele de filtro\na - todos los reles"));
}

const int voltPin = A0;   // seleccionar la entrada para el sensor
int volt;         // variable que almacena el valor raw (0 a 1023)
float fvolt;            // variable que almacena el voltaje (0.0 a 25.0)
const int rele = 53;
const bool cargar = 1;
 
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

void serialEvent()
{
  char data = Serial.read();
  if (sw)
  {
    sw = 0;
    switch (data)
    {
      case 's':
      rl = 37; // rele voltaje SSR
      break;
//      case 't':
//      rl = 53; // rele voltaje
//      break;
      case 'p':
      rl = 51; // rele pantalla
      break;
      case 'i':
      rl = 49; // rele inversor
      break;
      case 'o':
      rl = 47; // bomba pozo
      break;
      case 'f':
      rl = 45; // bomba fin
      break;
      case 'u':
      rl = 43; // bomba UV
      break; 
      case 'v':
      rl = 41; // rele UV
      break;
      case 'l':
      rl = 39; // rele filtro
      break;
      case 'a': // todos on
      sw = 1;
      delay(10);
      while (!Serial.available()){}
      bool mode = 0;
      data = Serial.read();
      if (data == '0')
      {
        mode = 1;
      }
      for (int i = 39;i<=51;i+=2)
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
      digitalWrite(rl,0); // va invertido
    }
    else if (data == '0')
    {
      digitalWrite(rl,1);
    }
    else
    {
      Serial.println(F("Dude wtf!!!"));
    }
  }
}
