#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif
MPU6050 mpu;

// MPU control/status vars
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// relative ypr[x] usage based on sensor orientation when mounted, e.g. ypr[PITCH]
#define PITCH   1     // defines the position within ypr[x] variable for PITCH; may vary due to sensor orientation when mounted
#define ROLL  2     // defines the position within ypr[x] variable for ROLL; may vary due to sensor orientation when mounted
#define YAW   0     // defines the position within ypr[x] variable for YAW; may vary due to sensor orientation when mounted

//float mpuPitch = 0;
//float mpuRoll = 0;
float mpuYaw = 0;

int yawAngleCorrect =0;

void ConfigMPU6050(){

  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
    TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
  #endif

  mpu.initialize();

  devStatus = mpu.dmpInitialize();


  // INPUT CALIBRATED OFFSETS HERE; SPECIFIC FOR EACH UNIT AND EACH MOUNTING CONFIGURATION!!!!

  mpu.setXGyroOffset(118);
  mpu.setYGyroOffset(-44);
  mpu.setZGyroOffset(337);
  mpu.setXAccelOffset(-651);
  mpu.setYAccelOffset(670);
  mpu.setZAccelOffset(1895);

  // make sure it worked (returns 0 if so)
  if (devStatus == 0)
  {
    // turn on the DMP, now that it's ready
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
    mpuIntStatus = mpu.getIntStatus();

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  }
  else
  {
    // ERROR!
    // 1 = initial memory load failed, 2 = DMP configuration updates failed (if it's going to break, usually the code will be 1)
  }

}
// ================================================================
// ===                    PROCESS ACCEL/GYRO IF AVAILABLE       ===
// ================================================================
void processAccelGyro()
{
   // wait for MPU interrupt or extra packet(s) available
  while (fifoCount < packetSize) {
    // other program behavior stuff here
    // .
    // .
    // .
    // if you are really paranoid you can frequently test in between other
    // stuff to see if mpuInterrupt is true, and if so, "break;" from the
    // while() loop to immediately process the MPU data
    // .
    // .
    // .
  }
  // Get INT_STATUS byte
  mpuIntStatus = mpu.getIntStatus();

  // get current FIFO count
  fifoCount = mpu.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & 0x10) || fifoCount == 1024)
  {
    // reset so we can continue cleanly
    mpu.resetFIFO();
    return;
  }

  if (mpuIntStatus & 0x02)  // otherwise continue processing
  {
    // check for correct available data length
    if (fifoCount < packetSize)
      return; //  fifoCount = mpu.getFIFOCount();

    // read a packet from FIFO
    mpu.getFIFOBytes(fifoBuffer, packetSize);

    // track FIFO count here in case there is > 1 packet available
    fifoCount -= packetSize;

    // flush buffer to prevent overflow
    mpu.resetFIFO();

    // display Euler angles in degrees
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    //mpuPitch = ypr[PITCH] * 180 / M_PI +90;
    //mpuRoll = ypr[ROLL] * 180 / M_PI +90;
    mpuYaw  = ypr[YAW] * 180 / M_PI +90;

    // flush buffer to prevent overflow
    mpu.resetFIFO();

    //delay(10);

  } // if (mpuIntStatus & 0x02)
}  // processAccelGyro()

#include <Servo.h>
//These are variables that hold the servo IDs.
char PitchChannel=0, YawChannel=1, LaserChannel = 2;

//These are the objects for each servo.
Servo servoRoll1;  // create servo object to control a servo
Servo servoPitch2;  // create servo object to control a servo
Servo servoYaw3;  // create servo object to control a servo

//This is a character that will hold data from the Serial port.
char serialChar=0;

int AngIniServoRoll=80, AngIniServoPitch = 70, AngIniServoYaw = 93;

int pitchAngleReceived = AngIniServoPitch;
int yawAngleReceived = AngIniServoYaw;

String inString = "";

void setup(){
  servoRoll1.attach(9);  // attaches the servo on pin 9 to the servo object
  servoPitch2.attach(10);  // attaches the servo on pin 10 to the servo object
  servoYaw3.attach(11);  // attaches the servo on pin 911 to the servo object
  servoRoll1.write(AngIniServoRoll);  
  servoPitch2.write(AngIniServoPitch);   
  servoYaw3.write(AngIniServoYaw);   
  Serial3.begin(19200);
  Serial.begin(57600);  //Set up a serial connection for 57600 bps.

  pinMode(24,OUTPUT);
  pinMode(25,OUTPUT);
  digitalWrite(24,HIGH);
  digitalWrite(25,LOW);

  ConfigMPU6050();
  delay(1000);

}

void loop(){
    if(Serial.available()>0){  //Wait for a character on the serial port.
      serialChar = Serial.read();     //Copy the character from the serial port to the variable
      if(serialChar == PitchChannel){  //Check to see if the character is the servo ID for the tilt servo
          while(Serial.available() <=0);  //Wait for the second command byte from the serial port.
          pitchAngleReceived=Serial.read()+18;
          servoPitch2.write(pitchAngleReceived);  //Set the tilt servo position to the value of the second command byte received on the serial port
      }else if(serialChar == YawChannel){ //Check to see if the initial serial character was the servo ID for the pan servo.
          while(Serial.available() <= 0);  //Wait for the second command byte from the serial port.
          yawAngleReceived=Serial.read()+18;
          servoYaw3.write(yawAngleReceived);   //Set the pan servo position to the value of the second command byte received from the serial port.
      }else if(serialChar == LaserChannel){
        Serial3.print('D');
      }
    }
    while(Serial3.available()> 0){
      serialChar =Serial3.read();
      Serial.print(serialChar);
      /*
      int inChar = Serial3.read();
      if (inChar != 'm') { 
        if (inChar != ' '){
         inString += (char)inChar;
        }else{
          inString = "";
        }
      }
      else {
        //inString.toFloat();
        Serial.print(inString.toFloat());
        inString = "";
      }
      */
    }
    yawAngleCorrect=yawAngleReceived-AngIniServoYaw;
    Serial.println(yawAngleCorrect);
    while(Serial.available()<=0){
      processAccelGyro();
      Serial.println(mpuYaw);
    }
}
