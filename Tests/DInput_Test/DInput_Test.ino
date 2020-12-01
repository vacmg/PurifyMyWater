void setup()
{
  Serial.begin(115200);
  for (int i = 2;i<=9;i++)
  {
    pinMode(i,INPUT);
  }
}

void loop()
{
  for (int i = 2; i<=9;i++)
  {
    Serial.println("Boya "+String(i)+": "+String(digitalRead(i)));
  }
  Serial.println("Entrada A0: "+String(analogRead(A0)));
  Serial.println("Entrada A1: "+String(analogRead(A1)));
  Serial.println("Entrada A2: "+String(analogRead(A2)));
  delay(200);
}
