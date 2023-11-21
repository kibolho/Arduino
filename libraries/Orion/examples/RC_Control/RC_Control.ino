//Basic Micro RoboClaw RC Mode. Control RoboClaw
//with servo pulses from a microcontroller.
//Mode settings: Mode 2 with Option 4.
#include <Servo.h>
Servo myservo1;  // create servo object to control a RoboClaw channel
Servo myservo2;  // create servo object to control a RoboClaw channel
int pos = 0;    // variable to store the servo position

void setup()
{ 
	myservo1.attach(5);  // attaches the RC signal on pin 5 to the servo object
	myservo2.attach(6);  // attaches the RC signal on pin 6 to the servo object
} 
void loop()
{ 
  myservo1.writeMicroseconds(1500);  //Stop
  myservo2.writeMicroseconds(1500);  //Stop
  delay(2000);
  myservo1.writeMicroseconds(1250);  //full forward
  delay(1000);
  myservo1.writeMicroseconds(1500);  //stop
  delay(2000);
  myservo1.writeMicroseconds(1750);  //full reverse
  delay(1000);
  myservo1.writeMicroseconds(1500);  //Stop
  delay(2000);
  myservo2.writeMicroseconds(1250);  //full forward
  delay(1000);
  myservo2.writeMicroseconds(1500);  //Stop
  delay(2000);
  myservo2.writeMicroseconds(1750);  //full reverse
  delay(1000);
} 