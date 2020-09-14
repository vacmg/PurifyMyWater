bool sw = 1;
byte rl;
void setup()
{
  for (int i = 39;i<=53;i+=2)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,1);
  }
  pinMode(13,OUTPUT);
  Serial.begin(115200);
  Serial.println(F("Selecciona un rele y enciendelo o apagalo\nt - rele de voltaje\np - pantalla\ni - inversor\no - bomba pozo\nf - bomba fin\nu - bomba UV\nv - rele de UV\nl - rele de filtro\na - todos los reles"));
}

void loop(){}

void serialEvent()
{
  char data = Serial.read();
  if (sw)
  {
    sw = 0;
    switch (data)
    {
      case 't':
      rl = 39; // rele voltaje
      break;
      case 'p':
      rl = 41; // rele pantalla
      break;
      case 'i':
      rl = 43; // rele inversor
      break;
      case 'o':
      rl = 45; // bomba pozo
      break;
      case 'f':
      rl = 47; // bomba fin
      break;
      case 'u':
      rl = 49; // bomba UV
      break; 
      case 'v':
      rl = 51; // rele UV
      break;
      case 'l':
      rl = 53; // rele filtro
      break;
      case 'a': // todos on
      sw = 1;
      delay(10);
      while (!Serial.available()){}
      bool mode;
      data = Serial.read();
      if (data == '1') // encender
      {
        mode = 0;
      }
      else if (data == '0')
      {
        mode = 1;
      }
      else
      {
        Serial.println(F("1/0"));
      }
      for (int i = 39;i<=53;i+=2)
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
