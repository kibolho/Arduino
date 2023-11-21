#include <Wire.h>

#define SLAVE_ADDRESS 0x60
int x = 0;
void setup()
{
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
  Serial.println("Escravo Configurado");
}

void loop()
{
  delay(100);
}

void requestEvent() 
{
  Serial.print("Request from Master. Sending: ");
  Serial.print(x);
  Serial.print("\n");

  Wire.write((char)x);
}

void receiveEvent(int bytes)
{
  if(Wire.available() != 0)
  {
    for(int i = 0; i< bytes; i++)
    {
      x = (int)Wire.read();
      Serial.print("Received: ");
      Serial.print(x);
      Serial.print("\n");
    }
  }
}
