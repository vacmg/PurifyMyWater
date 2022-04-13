void setup()
{
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  Serial.begin(115200);
  delay(2500);
  Serial.println("ON\n");
  //digitalWrite(3,1);
  digitalWrite(5,1);
  //digitalWrite(6,1);
  delay(5000);
  Serial.println("OFF\n");
  digitalWrite(3,0);
  digitalWrite(5,0);
  digitalWrite(6,0);
  delay(5000);
//  for (int i=0;i<=255;i++)
//  {
//    //analogWrite(3,i);
//    analogWrite(5,i);
//    //analogWrite(6,i);
//    Serial.println(i);
//    delay(100);
//  }
//  delay(2500);
//  for (int i=255;i>=0;i--)
//  {
//    //analogWrite(3,i);
//    analogWrite(5,i);
//    //analogWrite(6,i);
//    Serial.println(i);
//    delay(100);
//  }
}

void loop()
{
  
}

void serialEvent()
{
  delay(100);
  Serial.println("LEO");
  String s = Serial.readStringUntil('\n');
  int num = s.toInt();
  Serial.println(num);
  analogWrite(5,num);
}
