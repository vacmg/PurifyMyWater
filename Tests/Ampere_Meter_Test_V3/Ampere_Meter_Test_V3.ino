float Sensibilidad=0.122; //sensibilidad en V/A para nuestro sensor
float offset=0.154; // Equivale a la amplitud del ruido
void setup() {
  
  Serial.begin(9600);
}

void loop() {
  
  float Ip=get_corriente();//obtenemos la corriente pico
  float Irms=Ip*0.707; //Intensidad RMS = Ipico/(2^1/2)
  float P=Irms*230.0; // P=IV watts
  Serial.print("Ip: ");
  Serial.print(Ip,3);
  Serial.print("A , Irms: ");
  Serial.print(Irms,3);
  Serial.print("A, Potencia: ");
  Serial.print(P,3);  
  Serial.println("W");
  delay(500);     
}

float get_corriente()
{
  float voltajeSensor;
  float corriente=0;
  long tiempo=millis();
  float Imax=0;
  float Imin=0;
  while(millis()-tiempo<500)//realizamos mediciones durante 0.5 segundos
  { 
    voltajeSensor = analogRead(A0) * (5.0 / 1023.0);//lectura del sensor
    corriente=0.9*corriente+0.1*((voltajeSensor-2.527)/Sensibilidad); //Ecuación  para obtener la corriente
    if(corriente>Imax)Imax=corriente;
    if(corriente<Imin)Imin=corriente;
  }
  return(((Imax-Imin)/2)-offset);
}


//void setup() {
//  
//  Serial.begin(9600);
//}
//
//void loop() {
//  
//  float voltajeSensor =get_voltage(10000);//obtenemos voltaje del sensor(10000 muestras) 
//  Serial.print("Voltaje del sensor: ");
//  Serial.println(voltajeSensor ,3);     
//}
//
//
//float get_voltage(int n_muestras)
//{
//  float voltage=0;
//  
//  for(int i=0;i<n_muestras;i++)
//  {
//    voltage =voltage+analogRead(A0) * (5.0 / 1023.0);    
//  }
//  voltage=voltage/n_muestras;
//  return(voltage);
//}
