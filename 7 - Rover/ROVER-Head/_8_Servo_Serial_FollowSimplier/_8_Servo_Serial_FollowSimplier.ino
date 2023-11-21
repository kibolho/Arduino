#include <Servo.h>
//These are variables that hold the servo IDs.
char PitchChannel=0, YawChannel=1;

//These are the objects for each servo.
Servo servoRoll1;  // create servo object to control a servo
Servo servoPitch2;  // create servo object to control a servo
Servo servoYaw3;  // create servo object to control a servo

//This is a character that will hold data from the Serial port.
char serialChar=0;

int AngIniServoRoll=80, AngIniServoPitch = 70, AngIniServoYaw = 93;

int AngModServoRoll  = AngIniServoRoll;
int AngModServoPitch = AngIniServoPitch;
int AngModServoYaw   = AngIniServoYaw;

int AngPitchBegin=0;
int AngYawBegin = 0;

void setup(){
  servoRoll1.attach(9);  // attaches the servo on pin 9 to the servo object
  servoPitch2.attach(10);  // attaches the servo on pin 10 to the servo object
  servoYaw3.attach(11);  // attaches the servo on pin 911 to the servo object
  servoRoll1.write(AngIniServoRoll);  
  servoPitch2.write(AngIniServoPitch);   
  servoYaw3.write(AngIniServoYaw);   

  Serial.begin(57600);  //Set up a serial connection for 57600 bps.
}

void loop(){
    while(Serial.available() <=0);  //Wait for a character on the serial port.
    serialChar = Serial.read();     //Copy the character from the serial port to the variable
    if(serialChar == PitchChannel){  //Check to see if the character is the servo ID for the tilt servo
        while(Serial.available() <=0);  //Wait for the second command byte from the serial port.
        servoPitch2.write(Serial.read()+18);  //Set the tilt servo position to the value of the second command byte received on the serial port
    }else if(serialChar == YawChannel){ //Check to see if the initial serial character was the servo ID for the pan servo.
        while(Serial.available() <= 0);  //Wait for the second command byte from the serial port.
        servoYaw3.write(Serial.read()+18);   //Set the pan servo position to the value of the second command byte received from the serial port.
    }
}
