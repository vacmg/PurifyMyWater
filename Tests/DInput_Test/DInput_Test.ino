void setup()
{
  Serial.begin(115200);
  for (int i = 2;i<=9;i++)
  {
    pinMode(i,INPUT);
  }
  pinMode(10,INPUT_PULLUP);
}

void loop()
{
  for (int i = 2; i<=10;i++)
  {
    Serial.println("Boya "+String(i)+": "+String(digitalRead(i)));
  }
  Serial.println("Entrada A0: "+String(analogRead(A0)));
  Serial.println("Entrada A1: "+String(analogRead(A1)));
  Serial.println("Entrada A2: "+String(analogRead(A2)));
  delay(200);
}
