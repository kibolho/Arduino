#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX | TX

const int buttonPin = 10;  //LOW on digital pin enables mouse
const int buttonLeft = 11;
const int buttonRight = 12;
const int potXPin = 0;    // analog pins for pots
const int potYPin = 1;

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(buttonLeft, INPUT);
  pinMode(buttonRight, INPUT);
  // HC-05 default serial speed for AT mode is 38400
  BTserial.begin(38400);
}

void loop()
{
  int x = (512 - analogRead(potXPin)) / 4;  // range is -127 to +127
  int y = (512 - analogRead(potYPin)) / 4;
  Serial.print("Data,");
  Serial.print(x,DEC);
  Serial.print(",");
  Serial.print(y,DEC);  
  Serial.print(",");
  if(digitalRead(buttonPin) == LOW)
    Serial.print(1);  // send 1 when button pressed
  else  
    Serial.print(0); 
  Serial.println(","); 
  delay(100); // send position 20 times a second
}
