#include <Servo.h>
#include <Wire.h>
#include <MPU6050.h>
//These are variables that hold the servo IDs.
char PitchChannel=0, YawChannel=1, LaserChannel = 2;

//These are the objects for each servo.
Servo servoRoll1;  // create servo object to control a servo
Servo servoPitch2;  // create servo object to control a servo
Servo servoYaw3;  // create servo object to control a servo

MPU6050 mpu; // create mpu object to control the mpu 6050

//This is a character that will hold data from the Serial port.
char serialChar=0;

//Timers
unsigned long timer = 0;
float timeStep = 0.01;

int AngIniServoRoll=68, AngIniServoPitch = 60, AngIniServoYaw = 93;
float pitch = 0;
float roll = 0;
float yaw = 0;

String inString = "";

void setup(){
  Serial.begin(115200);  //Set up a serial connection for 57600 bps.

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)){
    Serial.println("Could no find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro(); // calibrate gyroscope
  mpu.setThreshold(1); // Set threshold sensivty

  Serial3.begin(19200);
  servoRoll1.attach(9);  // attaches the servo on pin 9 to the servo object
  servoPitch2.attach(10);  // attaches the servo on pin 10 to the servo object
  servoYaw3.attach(11);  // attaches the servo on pin 911 to the servo object
  servoRoll1.write(AngIniServoRoll);  
  servoPitch2.write(AngIniServoPitch);   
  servoYaw3.write(AngIniServoYaw);   
  
  
}

void loop(){
  timer = millis();
  Vector norm = mpu.readNormalizeGyro(); // Read normalized values

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;

  // Output raw
  /*Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);  
  Serial.print(" Yaw = ");
  Serial.println(yaw);
  
  delay((timeStep*1000) - (millis() - timer)); // Wait to full timeStep period*/
  
  if(Serial.available()>0){  //Wait for a character on the serial port.
    serialChar = Serial.read();     //Copy the character from the serial port to the variable
    if(serialChar == PitchChannel){  //Check to see if the character is the servo ID for the tilt servo
      while(Serial.available() <=0);  //Wait for the second command byte from the serial port.
        servoPitch2.write(Serial.read()+18);  //Set the tilt servo position to the value of the second command byte received on the serial port
    }else if(serialChar == YawChannel){ //Check to see if the initial serial character was the servo ID for the pan servo.
      while(Serial.available() <= 0);  //Wait for the second command byte from the serial port.
        servoYaw3.write(Serial.read()+18);   //Set the pan servo position to the value of the second command byte received from the serial port.
    }else if(serialChar == LaserChannel){
      Serial3.print('D');
    }
  }
  while(Serial3.available()> 0){
    serialChar =Serial3.read();
    Serial.print(serialChar);
  }
}
