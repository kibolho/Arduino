// Controlling two servo positions using a processing file
//Created by Jacob Unwin - http://www.jacob-unwin.com
  
#include <Servo.h>
   
Servo myservo_one;  // create servo object to control a servo
Servo myservo_two;
Servo myservo_three;
Servo myservo_four;

byte currentServo =1;
   
char val;
   
void setup()
{
  myservo_one.attach(8);  // attaches the servo on pin 9 to the servo object
  myservo_two.attach(9); //attaches the 2nd servo on pin 10
   myservo_three.attach(10);  // attaches the servo on pin 9 to the servo object
  myservo_four.attach(11); //attaches the 2nd servo on pin 10
  
  myservo_one.write(90); //sets both servo's at 90 degrees
  myservo_two.write(90); 
   myservo_three.write(90); //sets both servo's at 90 degrees
  myservo_four.write(90); 
   
  Serial.begin(9600); //start serial output at 9600
}
   
void loop()
{
    
  if(Serial.available()){
    val = Serial.read();
      
    if (val == '1'){ //if 1 has been pressed, current servo is 1
      currentServo = 1;
    } else if (val == '2'){ //else if 2 has been pressed, current servo is 2
      currentServo = 2;
    }
    else if (val == '3'){ //else if 2 has been pressed, current servo is 2
      currentServo = 3;
    }
     else if (val == '4'){ //else if 2 has been pressed, current servo is 2
      currentServo = 4;
    }
      
    if (val == 'l') { //if the last key press was l, rotates to 0 degrees
       if (currentServo == 1){
         myservo_one.write(0);
       }else if(currentServo == 2) {
         myservo_two.write(0);
       }else if(currentServo == 3) {
         myservo_three.write(0);
       }else if(currentServo == 4) {
         myservo_four.write(0);
       }
    }
      
    if (val == 'r') { //if the last key press was r, rotates to 180'
      if (currentServo == 1){
         myservo_one.write(180);
       } else if(currentServo == 2) {
         myservo_two.write(180);
       }else if(currentServo == 3) {
         myservo_three.write(180);
       }else if(currentServo == 4) {
         myservo_four.write(180);
       }
    }
      
    if (val == 's') { //if the last key press was s, returns to the center
      if (currentServo == 1){
         myservo_one.write(myservo_one.read());
       } else if(currentServo == 2) {
         myservo_two.write(myservo_two.read());
       }else if(currentServo == 3) {
         myservo_three.write(myservo_three.read());
       }else if(currentServo == 4) {
         myservo_four.write(myservo_four.read());
       }
    }
  }
}
