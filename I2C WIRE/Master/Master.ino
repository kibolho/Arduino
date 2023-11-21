#include <Wire.h>

#define SLAVE_ADDRESS 0x60
int x = 0;

void setup()
{
  Wire.begin(); 
  Serial.begin(9600); 
  Serial.println("Mestre Configurado");
}

void loop()
{
  x = 180;
  Serial.print("Sent: ");
  Serial.print(x);
  Serial.print("\n");
  Wire.beginTransmission(0x60);   
  Wire.write((char)x);                
  Wire.endTransmission();   
  delay(500);
  Serial.println("Requesting Data"); 
  Wire.requestFrom(SLAVE_ADDRESS, 1);

  int bytes = Wire.available();
  Serial.print("Slave sent ");
  Serial.print(bytes);
  Serial.print(" of information\n");
  for(int i = 0; i< bytes; i++)
  {
    x = (int)Wire.read();
    Serial.print("Slave Sent: ");
    Serial.print(x);
    Serial.print("\n");
  }  
  delay(500);
}
