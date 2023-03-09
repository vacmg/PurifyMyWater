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
  Serial.println(F("Selecciona un rele y enciendelo o apagalo\ns - SSR rele de voltaje\nt - rele de voltaje\np - pantalla\ni - inversor\no - bomba pozo\nf - bomba fin\nu - bomba UV\nv - rele de UV\nl - rele de filtro\na - todos los reles"));
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
      case 's':
      rl = 33; // rele voltaje SSR
      break;
      case 't':
      rl = 49; // rele voltaje
      break;
      case 'p':
      rl = 47; // rele pantalla
      break;
      case 'i':
      rl = 45; // rele inversor
      break;
      case 'o':
      rl = 43; // bomba pozo
      break;
      case 'f':
      rl = 41; // bomba fin
      break;
      case 'u':
      rl = 39; // bomba UV
      break; 
      case 'v':
      rl = 37; // rele UV
      break;
      case 'l':
      rl = 35; // rele filtro
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
      for (int i = 37;i<=53;i+=2)
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
