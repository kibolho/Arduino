
#include <Servo.h>
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
Servo servo3;  // create servo object to control a servo
char readString[20];   // Too big for all of these??
int AngIniServoRoll=80, AngIniServoPitch = 70, AngIniServoYaw = 93;
//Use to modify the center
int AngModServoRoll  = AngIniServoRoll;
int AngModServoPitch = AngIniServoPitch;
int AngModServoYaw   = AngIniServoYaw;
int AngPitchBegin=0;
int AngYawBegin = 0;

void check(){
    char *ptr;
  int charsRead;

  //expect a string like     90,low,15.6,125*
  //                  or    130, hi, 7.2,389*

  if (Serial.available())  {
    charsRead = Serial.readBytesUntil('*', readString, sizeof(readString) - 1);
    readString[charsRead] = '\0';

    Serial.print("captured String is : ");
    Serial.println(readString); //prints string to serial port out

    AngPitchBegin = AngModServoPitch;
    AngYawBegin = AngModServoYaw;
    ptr = strtok(readString, ",");
    if (ptr != '\0') {
      strcpy(AngModServoPitch, ptr);
    }
    ptr = strtok('\0', ",");
    if (ptr != '\0') {
      strcpy(AngModServoYaw, ptr);
    }
    Serial.print("pitch = ");
    Serial.println(AngModServoPitch);
    Serial.print("yaw = ");
    Serial.println(AngModServoYaw);
    readString[0] = '\0'; //clears variable for new input

    if (AngModServoYaw > 130){
          AngModServoYaw=130;
        }else if (AngModServoYaw<20){
          AngModServoYaw=20;
        }
        if (AngModServoPitch > 100){
          AngModServoPitch=100;
        }else if (AngModServoPitch<40){
          AngModServoPitch=40;
        }
         char buffer [50];
        sprintf (buffer, "P:%d Y:%d", AngModServoPitch, AngModServoYaw);
        Serial.println(buffer);
        servo1.write(AngModServoRoll); 
        if (AngPitchBegin > AngModServoPitch){
          for(int i = AngPitchBegin; i>AngModServoPitch;i--){
            servo2.write(i);
            delay(10);
          }
        }else{
          for(int i = AngPitchBegin; i<AngModServoPitch;i++){
            servo2.write(i);
            delay(10);
          }
        }
        if (AngYawBegin > AngModServoYaw){
          for(int i = AngYawBegin; i>AngModServoYaw;i--){
            servo3.write(i);
            delay(10);
          }
        }else{
          for(int i = AngYawBegin; i<AngModServoYaw;i++){
            servo3.write(i);
            delay(10);
          }
        }
  }
}

void setup() {
  Serial.begin(9600);
  delay(100); 
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object
  servo2.attach(10);  // attaches the servo on pin 10 to the servo object
  servo3.attach(11);  // attaches the servo on pin 911 to the servo object
  
 
  servo1.write(AngIniServoRoll);  
  delay(20); 
  servo2.write(AngIniServoPitch);   
  delay(20); 
  servo3.write(AngIniServoYaw);   
  delay(20); 
  
  delay(100);
}

void loop(){
  check();
}
