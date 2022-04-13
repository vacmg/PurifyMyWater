// PROGRAM´S START
/*////////////////////////////////comments
Versión dev 1.2
Se incluye el sistema de configuración
Se necesita un arduino mega
////////////////////////////////comments*/

//////////////////////////////////settings

const bool debug = true;
const bool modoOutput = true;
unsigned int s = 5; // tiempo apertura grifo (seg)
unsigned const int d = 100; // delay serial
unsigned long interval_1 = 600; //(seg) // tiempo antes de error 1
unsigned long interval_2 = 600; //(seg) // tiempo antes de error 2
unsigned long interval_3 = 600; //(seg) // tiempo antes de error 3
float bootTime = 1.5; // tiempo de espera en inicio

//////////////////////////////////settings

///////////////////////////////////////I/O

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

unsigned const int dotPin = 37;
unsigned const int downRight = 35;
unsigned const int down = 33;
unsigned const int downLeft = 31;
unsigned const int center = 27;
unsigned const int up = 25;
unsigned const int upLeft = 29;
unsigned const int upRight = 23;

unsigned const int led = 13;
unsigned const int button = 38;

unsigned const int vSensor = A0;

///////////////////////////////////////I/O

/////////////////////////////////variables

bool eButton;
bool set_up = 0;

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

/////////////////////////////////variables

/////////////////////////////////////setup

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

  pinMode(button,INPUT);

  pinMode(up,OUTPUT);
  pinMode(upRight,OUTPUT);
  pinMode(upLeft,OUTPUT);
  pinMode(center,OUTPUT);
  pinMode(down,OUTPUT);
  pinMode(downRight,OUTPUT);
  pinMode(downLeft,OUTPUT);
  pinMode(dotPin,OUTPUT);
  
  digitalWrite(vRele,0); // no carga

  letter('b');

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
  
  /////////////////////////boot statements
  
  bootTime = bootTime * 100 + 1;
  s=(s*100)+1;
  interval_1 = interval_1*1000;
  interval_2 = interval_2*1000;
  interval_3 = interval_3*1000;

  clrdsp();
  delay(750);
  dot(1);
  if (debug == 1)
  {
    Serial.println("SEARCHING SETUP INPUT...");
  }
  for (int i=0;i<bootTime;i++)
  {
    eButton = digitalRead(button);
    if (eButton == 1)
    {
      i = i + bootTime;
      set_up = 1;
    }
    delay(10);
  }
  dot(0);
  delay(500);
  if (set_up == 1)
  {
    Setup();
  }
  if (debug == 1)
  {
    Serial.println("FINISHED");
  }
  letter('v');
  vital();
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
    //volt = 13;//////////////////////////////////////////////////////////////////////////
  }

  /////////////////////////boot statements

  if (debug == 1)
  {
    Serial.println("");
    Serial.println("READY");
  }
  delay(1000);
  letter('p');
  
}

/////////////////////////////////////setup

//////////////////////////////////////loop

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

//////////////////////////////////////loop

/////////////////////////////////functions

void Setup()
{
  if (debug == 1)
  {
    Serial.println("");
    Serial.println("LOADING SETUP...");
  }
  letter('s');
  delay(750);
  letter('e');
  delay(750);
  letter('t');
  delay(750);
  letter('u');
  delay(750);
  letter('p');
  delay(750);
  clrdsp();
  if (debug == 1)
  {
    Serial.println("SETUP READY");
    Serial.println("");
  }
  delay(1000);
  if (debug == 1)
  {
    Serial.println("WAITING FOR INPUT...");
    Serial.println("");
  }
  number(0);
  eButton = digitalRead(button);
  while( eButton == 0)
  {
    eButton = digitalRead(button);
  }
  number(1);
  if (debug == 1)
  {
    Serial.print("WELL BUOY CHECK: ");
  }
  // well buoy check
  check(0);
  // well buoy check
  delay(500);
  if (debug == 1)
  {
    Serial.println("DONE");
  }
  delay(500);
  if (debug == 1)
  {
    Serial.print("VOLTAGE CHECK: ");
  }
  // voltage check
  check(1);
  // voltage check
  delay(500);
  if (debug == 1)
  {
    Serial.println("DONE");
  }
  delay(500);
  number(2);
  if (debug == 1)
  {
    Serial.print("FILTER TANK REFILLING PROCCESS: ");
  }
  // filter tank refill proccess
  refill(0);
  // filter tank refill proccess
  delay(10000);
  if (debug == 1)
  {
    Serial.println("DONE");
    Serial.println("");
  }
  number(3);
  delay(750);
  if (debug == 1)
  {
    Serial.println("WAITING FOR INPUT...");
    Serial.println("");
  }
  eButton = digitalRead(button);
  while( eButton == 0)
  {
    eButton = digitalRead(button);
  }
  number(4);
  if (debug == 1)
  {
    Serial.print("VOLTAGE CHECK: ");
  }
  // voltage check
  check(1);
  // voltage check
  delay(500);
  if (debug == 1)
  {
    Serial.println("DONE");
  }
  delay(500);
  number(5);
  if (debug == 1)
  {
    Serial.print("UV TANK REFILLING PROCCESS: ");
  }
  // UV tank refill proccess
  refill(1);
  // UV tank refill proccess
  delay(10000);
  if (debug == 1)
  {
    Serial.println("DONE");
    Serial.println("");
  }
  number(6);
  delay(750);
  if (debug == 1)
  {
    Serial.println("WAITING FOR INPUT...");
    Serial.println("");
  }
  eButton = digitalRead(button);
  while( eButton == 0)
  {
    eButton = digitalRead(button);
  }
  clrdsp();
  if (debug == 1)
  {
    Serial.println("SETUP COMLETE");
    Serial.println("");
  }
  delay(750);
  letter('s');
  delay(750);
  letter('e');
  delay(750);
  letter('t');
  delay(750);
  letter('u');
  delay(750);
  letter('p');
  delay(750);
  clrdsp();
  delay(750);
  letter('d');
  delay(750);
  letter('o');
  delay(750);
  letter('n');
  delay(750);
  letter('e');
  delay(750);
  clrdsp();
  delay(1250);

  if (debug == 1)
  {
    Serial.print("SETUP ");
  }
}

void check(bool b)
{
  if (b == 0)
  {
    vital();
    while (eBoyaSH == 0)
    {
      vital();
    }
  }
  else
  {
    vital();
    while (volt <= 12.5)
    {
      vital();
    }
  }
}

void refill(bool r)
{
  if (r == 0)
  {
    digitalWrite(bombaPozo,0); // enciende
    vital();
    while (eBoyaStartAr == 0)
    {
      vital();
    }
    digitalWrite(bombaPozo,1); // apaga
  }
  else
  {
    digitalWrite(filtro,0); // enciende
    vital();
    while( eBoyaStartAb == 1)
    {
      vital();
    }
    digitalWrite(filtro,1); // apaga
  }
}

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
  if (volt >= 13)
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

void error(unsigned int e)
{
  int i = 0;
  digitalWrite(vRele,0); // no carga
  off();
  while (i == 0)
  {
    letter('e');
    digitalWrite(led,1);
    delay(250);
    digitalWrite(led,0);
    delay(750);
    number(e);
    digitalWrite(led,1);
    delay(250);
    digitalWrite(led,0);
    delay(750);
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
    error(1);
}

void error2()
{
    if (debug == 1)
    {
      Serial.println("Error en zona 2");
    }
    digitalWrite(Led2Ok,0); // apaga ok led 2
    digitalWrite(Led2No,1); // enciende error led 2
    error(2);
}

void error3()
{
    if (debug == 1)
    {
      Serial.println("Error en zona 3");
    }
    digitalWrite(Led3Ok,0); // apaga ok led 3
    digitalWrite(Led3No,1); // enciende error led 3
    error(3);
}

void error4()
{
    if (debug == 1)
    {
      Serial.println("Error en zona 4");
    }
    digitalWrite(Led4Ok,0); // apaga ok led 4
    digitalWrite(Led4No,1); // enciende error led 4
    error(4);
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

/////////////////////////////////functions

/////////////////////////display functions

void number(int num)
{
  switch(num)
  {
    case 0:
      digitalWrite(up,1);
      digitalWrite(upRight,1);
      digitalWrite(upLeft,1);
      digitalWrite(center,0);
      digitalWrite(down,1);
      digitalWrite(downRight,1);
      digitalWrite(downLeft,1);
    break;
    
    case 1:
      digitalWrite(up,0);
      digitalWrite(upRight,1);
      digitalWrite(upLeft,0);
      digitalWrite(center,0);
      digitalWrite(down,0);
      digitalWrite(downRight,1);
      digitalWrite(downLeft,0);
    break;
    
    case 2:
      digitalWrite(up,1);
      digitalWrite(upRight,1);
      digitalWrite(upLeft,0);
      digitalWrite(center,1);
      digitalWrite(down,1);
      digitalWrite(downRight,0);
      digitalWrite(downLeft,1);
    break;
    
    case 3:
      digitalWrite(up,1);
      digitalWrite(upRight,1);
      digitalWrite(upLeft,0);
      digitalWrite(center,1);
      digitalWrite(down,1);
      digitalWrite(downRight,1);
      digitalWrite(downLeft,0);
    break;
    
    case 4:
      digitalWrite(up,0);
      digitalWrite(upRight,1);
      digitalWrite(upLeft,1);
      digitalWrite(center,1);
      digitalWrite(down,0);
      digitalWrite(downRight,1);
      digitalWrite(downLeft,0);
    break;
    
    case 5:
      digitalWrite(up,1);
      digitalWrite(upRight,0);
      digitalWrite(upLeft,1);
      digitalWrite(center,1);
      digitalWrite(down,1);
      digitalWrite(downRight,1);
      digitalWrite(downLeft,0);
    break;
    
    case 6:
      digitalWrite(up,1);
      digitalWrite(upRight,0);
      digitalWrite(upLeft,1);
      digitalWrite(center,1);
      digitalWrite(down,1);
      digitalWrite(downRight,1);
      digitalWrite(downLeft,1);
    break;
    
    case 7:
      digitalWrite(up,1);
      digitalWrite(upRight,1);
      digitalWrite(upLeft,0);
      digitalWrite(center,0);
      digitalWrite(down,0);
      digitalWrite(downRight,1);
      digitalWrite(downLeft,0);
    break;
    
    case 8:
      digitalWrite(up,1);
      digitalWrite(upRight,1);
      digitalWrite(upLeft,1);
      digitalWrite(center,1);
      digitalWrite(down,1);
      digitalWrite(downRight,1);
      digitalWrite(downLeft,1);
    break;
    
    case 9:
      digitalWrite(up,1);
      digitalWrite(upRight,1);
      digitalWrite(upLeft,1);
      digitalWrite(center,1);
      digitalWrite(down,1);
      digitalWrite(downRight,1);
      digitalWrite(downLeft,0);
    break;
  }
}
  
void dot(bool state)
{
  if( state == 1)
  {
    digitalWrite(dotPin,1);
  }
  else
  {
    digitalWrite(dotPin,0);
  }
}
  
void letter(char let)
{
  if (let == 'a')
  {
    digitalWrite(up,1);
    digitalWrite(upRight,1);
    digitalWrite(upLeft,1);
    digitalWrite(center,1);
    digitalWrite(down,0);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,1);
  }
    
  if (let == 'b')
  {
    digitalWrite(up,0);
    digitalWrite(upRight,0);
    digitalWrite(upLeft,1);
    digitalWrite(center,1);
    digitalWrite(down,1);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,1);
  }
    
  if (let == 'c')
  {
    digitalWrite(up,1);
    digitalWrite(upRight,0);
    digitalWrite(upLeft,1);
    digitalWrite(center,0);
    digitalWrite(down,1);
    digitalWrite(downRight,0);
    digitalWrite(downLeft,1);
  }
    
  if (let == 'd')
  {
    digitalWrite(up,0);
    digitalWrite(upRight,1);
    digitalWrite(upLeft,0);
    digitalWrite(center,1);
    digitalWrite(down,1);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,1);
  }
    
  if (let == 'e')
  {
    digitalWrite(up,1);
    digitalWrite(upRight,0);
    digitalWrite(upLeft,1);
    digitalWrite(center,1);
    digitalWrite(down,1);
    digitalWrite(downRight,0);
    digitalWrite(downLeft,1);
  }
    
  if (let == 'f')
  {
    digitalWrite(up,1);
    digitalWrite(upRight,0);
    digitalWrite(upLeft,1);
    digitalWrite(center,1);
    digitalWrite(down,0);
    digitalWrite(downRight,0);
    digitalWrite(downLeft,1);
  }

  if (let == 'g')
  {
    digitalWrite(up,1);
    digitalWrite(upRight,1);
    digitalWrite(upLeft,1);
    digitalWrite(center,1);
    digitalWrite(down,1);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,0);
  }

  if (let == 'h')
  {
    digitalWrite(up,0);
    digitalWrite(upRight,1);
    digitalWrite(upLeft,1);
    digitalWrite(center,1);
    digitalWrite(down,0);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,1);
  }

  if (let == 'i')
  {
    digitalWrite(up,0);
    digitalWrite(upRight,0);
    digitalWrite(upLeft,1);
    digitalWrite(center,0);
    digitalWrite(down,0);
    digitalWrite(downRight,0);
    digitalWrite(downLeft,1);
  }

  if (let == 'j')
  {
    digitalWrite(up,0);
    digitalWrite(upRight,1);
    digitalWrite(upLeft,0);
    digitalWrite(center,0);
    digitalWrite(down,1);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,1);
  }

  if (let == 'k')
  {
    digitalWrite(up,0);
    digitalWrite(upRight,1);
    digitalWrite(upLeft,1);
    digitalWrite(center,1);
    digitalWrite(down,0);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,1);
  }

  if (let == 'l')
  {
    digitalWrite(up,0);
    digitalWrite(upRight,0);
    digitalWrite(upLeft,1);
    digitalWrite(center,0);
    digitalWrite(down,1);
    digitalWrite(downRight,0);
    digitalWrite(downLeft,1);
  }

  if (let == 'm')
  {
    digitalWrite(up,1);
    digitalWrite(upRight,0);
    digitalWrite(upLeft,0);
    digitalWrite(center,0);
    digitalWrite(down,0);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,1);
  }

  if (let == 'n')
  {
    digitalWrite(up,0);
    digitalWrite(upRight,0);
    digitalWrite(upLeft,0);
    digitalWrite(center,1);
    digitalWrite(down,0);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,1);
  }

  if (let == 'o')
  {
    digitalWrite(up,1);
    digitalWrite(upRight,1);
    digitalWrite(upLeft,1);
    digitalWrite(center,0);
    digitalWrite(down,1);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,1);
  }

  if (let == 'p')
  {
    digitalWrite(up,1);
    digitalWrite(upRight,1);
    digitalWrite(upLeft,1);
    digitalWrite(center,1);
    digitalWrite(down,0);
    digitalWrite(downRight,0);
    digitalWrite(downLeft,1);
  }

  if (let == 'q')
  {
    digitalWrite(up,1);
    digitalWrite(upRight,1);
    digitalWrite(upLeft,1);
    digitalWrite(center,1);
    digitalWrite(down,0);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,0);
  }

  if (let == 'r')
  {
    digitalWrite(up,0);
    digitalWrite(upRight,0);
    digitalWrite(upLeft,0);
    digitalWrite(center,1);
    digitalWrite(down,0);
    digitalWrite(downRight,0);
    digitalWrite(downLeft,1);
  }

  if (let == 's')
  {
    digitalWrite(up,1);
    digitalWrite(upRight,0);
    digitalWrite(upLeft,1);
    digitalWrite(center,1);
    digitalWrite(down,1);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,0);
  }

  if (let == 't')
  {
    digitalWrite(up,0);
    digitalWrite(upRight,0);
    digitalWrite(upLeft,1);
    digitalWrite(center,1);
    digitalWrite(down,1);
    digitalWrite(downRight,0);
    digitalWrite(downLeft,1);
  }

  if (let == 'u')
  {
    digitalWrite(up,0);
    digitalWrite(upRight,1);
    digitalWrite(upLeft,1);
    digitalWrite(center,0);
    digitalWrite(down,1);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,1);
  }

  if (let == 'v')
  {
    digitalWrite(up,0);
    digitalWrite(upRight,0);
    digitalWrite(upLeft,0);
    digitalWrite(center,0);
    digitalWrite(down,1);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,1);
  }

  if (let == 'w')
  {
    digitalWrite(up,0);
    digitalWrite(upRight,1);
    digitalWrite(upLeft,1);
    digitalWrite(center,0);
    digitalWrite(down,1);
    digitalWrite(downRight,0);
    digitalWrite(downLeft,0);
  }

  if (let == 'x')
  {
    digitalWrite(up,0);
    digitalWrite(upRight,1);
    digitalWrite(upLeft,1);
    digitalWrite(center,1);
    digitalWrite(down,0);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,1);
  }

  if (let == 'y')
  {
    digitalWrite(up,0);
    digitalWrite(upRight,1);
    digitalWrite(upLeft,1);
    digitalWrite(center,1);
    digitalWrite(down,1);
    digitalWrite(downRight,1);
    digitalWrite(downLeft,0);
  }

  if (let == 'z')
  {
    digitalWrite(up,1);
    digitalWrite(upRight,1);
    digitalWrite(upLeft,0);
    digitalWrite(center,1);
    digitalWrite(down,1);
    digitalWrite(downRight,0);
    digitalWrite(downLeft,1);
  }
}

void clrdsp()
{
    digitalWrite(up,0);
    digitalWrite(upRight,0);
    digitalWrite(upLeft,0);
    digitalWrite(center,0);
    digitalWrite(down,0);
    digitalWrite(downRight,0);
    digitalWrite(downLeft,0);
    digitalWrite(dotPin,0);
}

/////////////////////////display functions
