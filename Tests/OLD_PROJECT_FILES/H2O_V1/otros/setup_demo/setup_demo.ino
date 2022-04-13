unsigned const int button = 38;

unsigned const int positivo = 11;

unsigned const int dotPin = 33;
unsigned const int downRight = 31;
unsigned const int down = 29;
unsigned const int downLeft = 27;
unsigned const int center = 25;
unsigned const int up = 35;
unsigned const int upLeft = 23;
unsigned const int upRight = 37;

//setup
float bootTime = 1.5;
//setup

bool eButton;
bool set_up = 0;

void setup()
{
  pinMode(button,INPUT);

  pinMode(positivo,OUTPUT);

  pinMode(up,OUTPUT);
  pinMode(upRight,OUTPUT);
  pinMode(upLeft,OUTPUT);
  pinMode(center,OUTPUT);
  pinMode(down,OUTPUT);
  pinMode(downRight,OUTPUT);
  pinMode(downLeft,OUTPUT);
  pinMode(dotPin,OUTPUT);
  // boot statements
  digitalWrite(positivo,1);
  letter('b');
  bootTime = bootTime * 100 + 1;
  delay(1500);
  clrdsp();
  delay(750);
  dot(1);
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
  // boot statements
}

void loop()
{
  letter('p');
}

void Setup()
{
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
  delay(1000);
  number(0);
  eButton = digitalRead(button);
  while( eButton == 0)
  {
    eButton = digitalRead(button);
  }
  number(1);
  // well buoy check && voltage check
  delay(2000);
  number(2);
  // refilling proccess
  delay(10000);
  number(3);
  eButton = digitalRead(button);
  while( eButton == 0)
  {
    eButton = digitalRead(button);
  }
  number(4);
  // voltage test
  delay(2000);
  number(5);
  // filter tank refill proccess
  delay(10000);
  number(6);
  eButton = digitalRead(button);
  while( eButton == 0)
  {
    eButton = digitalRead(button);
  }
  clrdsp();
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
}

// 7 display functions
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
// 7 display functions
