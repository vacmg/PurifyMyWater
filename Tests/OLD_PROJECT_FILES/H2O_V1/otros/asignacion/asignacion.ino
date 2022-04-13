int pin = 23;
void setup() {
  for (pin; pin <= 37; pin = pin+2){
  // put your setup code here, to run once:
  pinMode(pin,OUTPUT);
  digitalWrite(pin,1);
  delay(3000);}
}

void loop() {
  // put your main code here, to run repeatedly:

}
