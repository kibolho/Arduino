#include <Servo.h>
#define control_left A0
#define control_base A1
#define control_right A2 
#define timeupdate 1000

Servo myservo_left;  // create servo object to control a servo
Servo myservo_base;
Servo myservo_right;

long times=0;

int position_left=0;
int position_base=0;
int position_right=0;

void setup()
{
  myservo_left.attach(9); //attaches the 2nd servo on pin 10
  myservo_base.attach(10);  // attaches the servo on pin 9 to the servo object
  myservo_right.attach(11); //attaches the 2nd servo on pin 10
  
  myservo_left.write(90); //sets both servo's at 90 degrees
  myservo_base.write(90); 
  myservo_right.write(90); //sets both servo's at 90 degrees
  
  Serial.begin(9600); //start serial output at 9600
  times=millis();
  delay(1000);
}
   
void loop()
{
  position_left =analogRead(control_left);
  position_left = map(position_left, 0, 1023, 0, 180);
  position_base =analogRead(control_base);
  position_base = map(position_base, 0, 1023, 0, 180);
  position_right = analogRead(control_right);
  position_right = map(position_right, 0, 1023, 0, 180);
  if(millis()-times>timeupdate){
   Serial.print(position_left);
   Serial.print("  ");
   myservo_left.write(position_left);
   Serial.print(position_base);
   Serial.print("  ");
   myservo_base.write(position_base);
   Serial.println(position_right);
   myservo_right.write(position_right);
   times=millis();
  }
}
