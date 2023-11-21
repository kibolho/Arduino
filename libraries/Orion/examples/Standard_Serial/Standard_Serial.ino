//RoboClaw Standard Serial Test
//Switch settings: SW2=ON and SW5=ON
//Make sure Arduino and Robo Claw share common GND!
#include “BMSerial.h”

BMSerial mySerial(5,6);

void setup() {
  mySerial.begin(19200);
} 
void loop() {
  mySerial.write(1);
  mySerial.write(-1);
  delay(2000);
  mySerial.write(127);
  mySerial.write(-127);
  delay(2000);
} 