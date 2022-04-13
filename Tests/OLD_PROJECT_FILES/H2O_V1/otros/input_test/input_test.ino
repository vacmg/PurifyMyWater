unsigned const int boyaSH = 2;
unsigned const int boyaStartAr = 3;
unsigned const int boyaStartAb = 4;
unsigned const int boyaUVAr = 5;
unsigned const int boyaUVAb = 6;
unsigned const int boyaEndAr = 7;
unsigned const int boyaEndAb = 8;
unsigned const int pulsador = 9;
unsigned const int button = 38;
unsigned const int d = 100;
unsigned const int positivo = 11;
bool eBoyaSH;
bool eBoyaStartAr;
bool eBoyaStartAb;
bool eBoyaUVAr;
bool eBoyaUVAb;
bool eBoyaEndAr;
bool eBoyaEndAb;
bool ePulsador;
bool eButton;
const int rele = 53;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(boyaSH,INPUT);
  pinMode(boyaStartAr,INPUT);
  pinMode(boyaStartAb,INPUT);
  pinMode(boyaUVAr,INPUT);
  pinMode(boyaUVAb,INPUT);
  pinMode(boyaEndAr,INPUT);
  pinMode(boyaEndAb,INPUT);
  pinMode(pulsador,INPUT);
  pinMode(rele,OUTPUT);
  pinMode(positivo,OUTPUT);
  pinMode(button,OUTPUT);
  digitalWrite(rele,0);
  delay(100);
  digitalWrite(positivo,1);
}

void loop() {
  // put your main code here, to run repeatedly:
  eBoyaSH = digitalRead(boyaSH);
  eBoyaStartAr = digitalRead(boyaStartAr);
  eBoyaStartAb = digitalRead(boyaStartAb);
  eBoyaUVAr = digitalRead(boyaUVAr);
  eBoyaUVAb = digitalRead(boyaUVAb);
  eBoyaEndAr = digitalRead(boyaEndAr);
  eBoyaEndAb = digitalRead(boyaEndAb);
  ePulsador = digitalRead(pulsador);
  eButton = digitalRead(button);

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
  Serial.print("boton: ");
  Serial.println(eButton);
  delay(d);
}


