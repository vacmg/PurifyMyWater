// PROGRAM´S START
/*////////////////////////////////comments
Versión dev 1.1
Se necesita un arduino mega
////////////////////////////////comments*/

////////////////////////////////////////////////////code

////////////////////////////////settings
const bool debug = true;
const bool modoOutput = true;
unsigned int s = 5; // tiempo apertura grifo (seg)
unsigned const int d = 100; // delay serial
unsigned long interval_1 = 600; //(seg)
unsigned long interval_2 = 600; //(seg)
unsigned long interval_3 = 600; //(seg)

////////////////////////////////settings

////////////////////////////////statement
unsigned const int boyaSH = 2; // amarilla
unsigned const int boyaStartAr = 3; // naranja
unsigned const int boyaStartAb = 4; // rojo
unsigned const int boyaUVAr = 5; // negro
unsigned const int boyaUVAb = 6; // marron
unsigned const int boyaEndAr = 7; // verde
unsigned const int boyaEndAb = 8; // azul
unsigned const int pulsador = 9; // morado

unsigned const int bombaPozo = 47;
unsigned const int filtro = 39;
unsigned const int UV = 41;
unsigned const int bombaUV = 45;
unsigned const int grifo = 49;
unsigned const int vRele = 53;
//unsigned const int rRele = 43;
unsigned const int inversor = 51;

unsigned const int Led1No = 22;
unsigned const int Led1Ok = 24;
unsigned const int Led2No = 26;
unsigned const int Led2Ok = 28;
unsigned const int Led3No = 30;
unsigned const int Led3Ok = 32;
unsigned const int Led4No = 34;
unsigned const int Led4Ok = 36;

unsigned const int led = 13;

unsigned const int vSensor = A0;

bool eBoyaSH;
bool eBoyaStartAr;
bool eBoyaStartAb;
bool eBoyaUVAr;
bool eBoyaUVAb;
bool eBoyaEndAr;
bool eBoyaEndAb;
bool ePulsador;

bool eFiltro;
bool eUV;
bool eCuboEnd;
bool state = 0;

unsigned int ivolt;
float volt;

bool time1;
bool time3;

unsigned long btime1; // antes de comenzar operacion
unsigned long atime1; // al finalizar la operacion
unsigned long itime1; // intervalo de tiempo entre inicio y final
unsigned long btime2; // antes de comenzar operacion
unsigned long atime2; // al finalizar la operacion
unsigned long itime2; // intervalo de tiempo entre inicio y final
unsigned long btime3; // antes de comenzar operacion
unsigned long atime3; // al finalizar la operacion
unsigned long itime3; // intervalo de tiempo entre inicio y final


////////////////////////////////statement

////////////////////////////////setup

void setup()
{
  digitalWrite(bombaPozo,modoOutput); // apagado
  digitalWrite(filtro,modoOutput); // apagado
  digitalWrite(UV,modoOutput); // apagado
  digitalWrite(bombaUV,modoOutput); // apagado
  digitalWrite(grifo,modoOutput); // apagado
  digitalWrite(vRele,modoOutput); // apagado
  digitalWrite(inversor,modoOutput); // apagado

  pinMode(Led1Ok,OUTPUT);
  pinMode(Led1No,OUTPUT);
  pinMode(Led2Ok,OUTPUT);
  pinMode(Led2No,OUTPUT);
  pinMode(Led3Ok,OUTPUT);
  pinMode(Led3No,OUTPUT);
  pinMode(Led4Ok,OUTPUT);
  pinMode(Led4No,OUTPUT);
  pinMode(vRele,OUTPUT); //0-25
  
  digitalWrite(vRele,0); // no carga
  
  if (debug == 1)
  {
    Serial.begin(9600);
    delay(500);
    Serial.print("BOOTING");
    delay(250);
    Serial.print(".");
    delay(250);
    Serial.print(".");
    delay(250);
    Serial.print(".");
    delay(250);
    Serial.print(".");
    delay(250);
    Serial.println(".");
    delay(500);
    Serial.println("");
  }

  digitalWrite(Led1Ok,1);
  delay(150);
  digitalWrite(Led3Ok,1);
  delay(150);
  digitalWrite(Led2Ok,1);
  delay(150);
  digitalWrite(Led4Ok,1);
  delay(150);
  digitalWrite(Led3Ok,0);
  delay(150);
  digitalWrite(Led1Ok,0);
  delay(150);
  digitalWrite(Led4Ok,0);
  delay(150);
  digitalWrite(Led2Ok,0);
  delay(500);
  
  pinMode(boyaSH,INPUT);
  pinMode(boyaStartAr,INPUT);
  pinMode(boyaStartAb,INPUT);
  pinMode(boyaUVAr,INPUT);
  pinMode(boyaUVAb,INPUT);
  pinMode(boyaEndAr,INPUT);
  pinMode(boyaEndAb,INPUT);
  pinMode(pulsador,INPUT);

  pinMode(bombaPozo,OUTPUT); //12
  pinMode(filtro,OUTPUT); //220
  pinMode(UV,OUTPUT); //220
  pinMode(bombaUV,OUTPUT); //12
  pinMode(grifo,OUTPUT); //12
  pinMode(inversor,OUTPUT); //12
  //pinMode(vRele,OUTPUT); //0-25 // is declared before bootanimation

  pinMode(led,OUTPUT);
  
  //////////////////////////////boot statements
  vital();
  s=(s*100)+1;
  interval_1 = interval_1*1000;
  interval_2 = interval_2*1000;
  interval_3 = interval_3*1000;
  while(volt <= 12)
  {
    if (debug == 1)
    {
     Serial.println("");
     delay(d);
     Serial.println("GETTING 12V...");
     delay(d);
    }
    vital();
    LOff();
  }
  //////////////////////////////boot statements
  
  if (debug == 1)
  {
    Serial.println("READY");
  }
  delay(1000);
}

////////////////////////////////setup

////////////////////////////////loop

void loop()
{
  vital();
  if (volt < 11.5 )
  {
    off();
    if(state == 1)
    {
      LOff();
      state = 0;
    }
    if (volt > 9)
    {
      digitalWrite(Led4Ok,1);
      digitalWrite(Led4No,0);
    }
    else
    {
      digitalWrite(Led4Ok,0);
      digitalWrite(Led4No,1);
    }
    if (ePulsador == 1 && eBoyaEndAb == 1 && volt > 9)
    {
      eCuboEnd = 0;
      digitalWrite(grifo,0); // abre
      delay(500);
      for (int i = 0; i<s;i++) 
      {
        vital();
        if (ePulsador == 1)
        {
          i = i+s;
        }
        delay(10);
      }
      while( ePulsador == 1){vital();}
      digitalWrite(grifo,1); // cierra
    }

    if (eBoyaEndAr == 1)
    {
      eCuboEnd = 1;
    }
  }
  else
  {
    if(state == 0)
    {
      LOn();
      state = 1;
    }
    if (eBoyaStartAr == 0 && eBoyaSH == 1) 
    {
      if (time1 == 0)
      {
        btime1 = millis();
        time1 = 1;
      }
      atime1 = millis();
      digitalWrite(bombaPozo,0); // enciende
    }
    if (eBoyaStartAr == 1 || eBoyaSH == 0)
    {
      time1 = 0;
      digitalWrite(bombaPozo,1); // apaga
    }
    
    if ((eBoyaStartAr == 1 || eBoyaUVAb == 0) && eBoyaStartAb == 1)// filtro // poner voltaje min
    {
      if (volt > 12.5) // si no funciona, quitar
      {
        if (eBoyaUVAr == 0)
        {
          off();
          vital();
          eFiltro = 1;
          iControl();
          btime2 = millis();
          digitalWrite(filtro,0); // enciende
          atime2 = millis();
          bool x = 0;
          while(eBoyaStartAb == 1 && eBoyaUVAr == 0 && x == 0)
          {
            atime2 = millis();
            vital();
            if (volt < 11.5)
            {
              x = 1;
            }
          }
          digitalWrite(filtro,1); // apaga
          eFiltro = 0;
          iControl();
        }
      }
    }    
    if (eBoyaUVAb == 1 && eBoyaEndAr == 0)
    {
      search4();
      eUV = 1;
      iControl();
      if (time3 == 0)
      {
        btime3 = millis();
        time3 = 1;
      }
      atime3 = millis();
      digitalWrite(UV,0); // enciende
      delay(100);
      digitalWrite(bombaUV,0); // enciende
    }
    
    if (eBoyaUVAb == 0 || eBoyaEndAr == 1)
    {
      eUV = 0;
      time3 = 0;
      digitalWrite(bombaUV,1); // apaga
      delay(750);
      digitalWrite(UV,1); // apaga
      iControl();
    }
    
    if (ePulsador == 1 && eBoyaEndAb == 1)
    {
      eCuboEnd = 0;
      digitalWrite(grifo,0); // abre
      delay(500);
      for (int i = 0; i<s;i++) 
      {
        vital();
        if (eBoyaUVAb == 1 && eBoyaEndAr == 0)
    {
      search4();
      eUV = 1;
      iControl();
      if (time3 == 0)
      {
        btime3 = millis();
        time3 = 1;
      }
      atime3 = millis();
      digitalWrite(UV,0); // enciende
      delay(100);
      digitalWrite(bombaUV,0); // enciende
    }
    
    if (eBoyaUVAb == 0 || eBoyaEndAr == 1)
    {
      eUV = 0;
      time3 = 0;
      digitalWrite(bombaUV,1); // apaga
      delay(750);
      digitalWrite(UV,1); // apaga
      iControl();
    }
        if (ePulsador == 1)
        {
          i = i+s;
        }
        delay(10);
      }
      while( ePulsador == 1){vital();}
      digitalWrite(grifo,1); // cierra
    }

    if (eBoyaEndAr == 1)
    {
      eCuboEnd = 1;
    }
    
  }
}

////////////////////////////////loop

////////////////////////////////functions

void leer()
{
  eBoyaSH = digitalRead(boyaSH);
  eBoyaStartAr = digitalRead(boyaStartAr);
  eBoyaStartAb = digitalRead(boyaStartAb);
  eBoyaUVAr = digitalRead(boyaUVAr);
  eBoyaUVAb = digitalRead(boyaUVAb);
  eBoyaEndAr = digitalRead(boyaEndAr);
  eBoyaEndAb = digitalRead(boyaEndAb);
  ePulsador = digitalRead(pulsador);
  timing();
  voltRead();

  if (debug == 1)
  {
    printData();
  }
}

void timing()
{
  itime1 = atime1 - btime1;
  itime2 = atime2 - btime2;
  itime3 = atime3 - btime3;
}

void printData()
{
  Serial.println("");
  delay(d);
  Serial.print("Boya SH: ");
  Serial.println(eBoyaSH);
  delay(d);
  Serial.print("Boya Start Arriba: ");
  Serial.println(eBoyaStartAr);
  delay(d);
  Serial.print("Boya Start Abajo: ");
  Serial.println(eBoyaStartAb);
  delay(d);
  Serial.print("Boya UV Arriba: ");
  Serial.println(eBoyaUVAr);
  delay(d);
  Serial.print("Boya UV Abajo: ");
  Serial.println(eBoyaUVAb);
  delay(d);
  Serial.print("Boya End Arriba: ");
  Serial.println(eBoyaEndAr);
  delay(d);
  Serial.print("Boya End Abajo: ");
  Serial.println(eBoyaEndAb);
  delay(d);
  Serial.print("Pulsador: ");
  Serial.println(ePulsador);
  delay(d);
  Serial.print("Voltaje: ");
  Serial.println(volt);
  delay(d);
  Serial.print("Tiempo zona 1: ");
  Serial.println(itime1);
  delay(d);
  Serial.print("Tiempo zona 2: ");
  Serial.println(itime2);
  delay(d);
  Serial.print("Tiempo zona 3: ");
  Serial.println(itime3);
  delay(d);
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void voltRead() 
{
   ivolt = analogRead(vSensor);          // realizar la lectura
   volt = fmap(ivolt, 0, 1023, 0.0, 25.0);   // cambiar escala a 0.0 - 25.0
}

void voltControl()
{
  if (volt <= 12)
  {
    digitalWrite(vRele,1); // carga
  }
  else
  {
    digitalWrite(vRele,0); // no carga
  }
}

void vital()
 {
    leer();
    voltControl();
    errorControl();
 }

void iControl()
{
  if ( eFiltro == 1 || eUV == 1)
  {
    digitalWrite(inversor,0); // enciende
  }
  if( eFiltro == 0 && eUV == 0)
  {
    digitalWrite(inversor,1); // apaga
  }
}
void errorControl() // search4() se activa desde loop()
{
  search1();
  search2();
  search3();
}

void error()
{
  int i = 0;
  digitalWrite(vRele,0); // no carga
  off();
  while (i == 0)
  {
    digitalWrite(led,1);
    delay(250);
    digitalWrite(led,0);
    delay(1000);
  }
}

void search1()
{
  if (itime1 > interval_1)
  {
    error1();
  }
}

void search2()
{
  if (itime2 > interval_2)
  {
    error2();
  }
}

void search3()
{
  if (itime3 > interval_3)
  {
    error3();
  }
}

void search4()
{
  if (eCuboEnd == 1)
  {
    error4();
  }
}

void error1()
{
    if (debug == 1)
    {
      Serial.println("Error en zona 1");
    }
    digitalWrite(Led1Ok,0); // apaga ok led 1
    digitalWrite(Led1No,1); // enciende error led 1
    error();
}

void error2()
{
    if (debug == 1)
    {
      Serial.println("Error en zona 2");
    }
    digitalWrite(Led2Ok,0); // apaga ok led 2
    digitalWrite(Led2No,1); // enciende error led 2
    error();
}

void error3()
{
    if (debug == 1)
    {
      Serial.println("Error en zona 3");
    }
    digitalWrite(Led3Ok,0); // apaga ok led 3
    digitalWrite(Led3No,1); // enciende error led 3
    error();
}

void error4()
{
    if (debug == 1)
    {
      Serial.println("Error en zona 4");
    }
    digitalWrite(Led4Ok,0); // apaga ok led 4
    digitalWrite(Led4No,1); // enciende error led 4
    error();
}

void off()
{
    digitalWrite(bombaPozo,modoOutput); // apagado
    digitalWrite(filtro,modoOutput); // apagado
    digitalWrite(bombaUV,modoOutput); // apagado
    digitalWrite(grifo,modoOutput); // apagado
    digitalWrite(inversor,modoOutput); // apagado
    delay(1500);
    digitalWrite(UV,modoOutput); // apagado  
}

void LOff()
{
  digitalWrite(Led1Ok,0);
  digitalWrite(Led2Ok,0);
  digitalWrite(Led3Ok,0);
  digitalWrite(Led4Ok,0);
  
  digitalWrite(Led1No,1);
  digitalWrite(Led2No,1);
  digitalWrite(Led3No,1);
  digitalWrite(Led4No,1);
}

void LOn()
{
  digitalWrite(Led1No,0);
  digitalWrite(Led2No,0);
  digitalWrite(Led3No,0);
  digitalWrite(Led4No,0);
  
  digitalWrite(Led1Ok,1);
  digitalWrite(Led2Ok,1);
  digitalWrite(Led3Ok,1);
  digitalWrite(Led4Ok,1);
}
////////////////////////////////functions

////////////////////////////////////////////////////code

// PROGRAM´S END
