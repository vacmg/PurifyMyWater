unsigned const int bombaPozo = 47;
unsigned const int filtro = 39;
unsigned const int UV = 41;
unsigned const int bombaUV = 45;
unsigned const int grifo = 49;
unsigned const int vRele = 53;
unsigned const int inversor = 51;
unsigned const int ssr = 10;
const bool modoOutput = 0;
unsigned const int Led1No = 22;
unsigned const int Led1Ok = 24;
unsigned const int Led2No = 26;
unsigned const int Led2Ok = 28;
unsigned const int Led3No = 30;
unsigned const int Led3Ok = 32;
unsigned const int Led4No = 34;
unsigned const int Led4Ok = 36;
void setup() {
  // put your setup code here, to run once:
  pinMode(bombaPozo,OUTPUT); //12
  pinMode(filtro,OUTPUT); //220
  pinMode(UV,OUTPUT); //220
  pinMode(bombaUV,OUTPUT); //12
  pinMode(grifo,OUTPUT); //12
  pinMode(inversor,OUTPUT); //12
  pinMode(vRele,OUTPUT); //0-21
  pinMode(Led1No,OUTPUT);
  pinMode(Led1Ok,OUTPUT);
  pinMode(Led2No,OUTPUT);
  pinMode(Led2Ok,OUTPUT);
  pinMode(Led3No,OUTPUT);
  pinMode(Led3Ok,OUTPUT);
  pinMode(Led4No,OUTPUT);
  pinMode(Led4Ok,OUTPUT);
  pinMode(ssr,OUTPUT);
  digitalWrite(ssr,0);
  digitalWrite(bombaPozo,1); // apagado
  digitalWrite(filtro,1); // apagado
  digitalWrite(UV,1); // apagado
  digitalWrite(bombaUV,1); // apagado
  digitalWrite(grifo,1); // apagado
  digitalWrite(vRele,1); // apagado
  digitalWrite(inversor,1); // apagado
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Led1Ok,1);
  delay(5000);
  digitalWrite(Led1Ok,0);
  digitalWrite(Led2Ok,1);
  delay(5000);
  digitalWrite(Led2Ok,0);
  digitalWrite(Led3Ok,1);
  delay(5000);
  digitalWrite(Led3Ok,0);
  digitalWrite(Led4Ok,1);
  delay(5000);
  digitalWrite(Led4Ok,0);
  digitalWrite(Led1No,1);
  delay(5000);
  digitalWrite(Led1No,0);
  digitalWrite(Led2No,1);
  delay(5000);
  digitalWrite(Led2No,0);
  digitalWrite(Led3No,1);
  delay(5000);
  digitalWrite(Led3No,0);
  digitalWrite(Led4No,1);
  delay(5000);
  digitalWrite(ssr,1);
  digitalWrite(Led4No,0);
  delay(5000);
  digitalWrite(bombaPozo,0);
  digitalWrite(ssr,0);
  delay(5000);
  digitalWrite(bombaPozo,1); 
  digitalWrite(filtro,0);
  delay(5000);
  digitalWrite(filtro,1);
  digitalWrite(UV,0);
  delay(5000);
  digitalWrite(UV,1);
  digitalWrite(bombaUV,0);
  delay(5000);
  digitalWrite(bombaUV,1);
  digitalWrite(grifo,0);
  delay(5000);
  digitalWrite(grifo,1);
  digitalWrite(vRele,0);
  delay(5000);
  digitalWrite(vRele,1);
  digitalWrite(inversor,0);
  delay(5000);
  digitalWrite(inversor,1);
  
}
