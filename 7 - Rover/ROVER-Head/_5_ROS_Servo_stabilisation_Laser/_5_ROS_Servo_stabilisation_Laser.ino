/*
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

float mpuPitch = 0;
float mpuRoll = 0;
float mpuYaw = 0;
*/

#include <Servo.h>
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
Servo servo3;  // create servo object to control a servo

/*
#include <SoftwareSerial.h>
SoftwareSerial Laser(7,8);//RX TX
String inString = "";
*/

#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>

//float AngIniRoll=71.63, AngIniPitch = 41.60, AngIniYaw = 40.75;
int AngIniServoRoll=80, AngIniServoPitch = 70, AngIniServoYaw = 93;
//Use to modify the center
int AngModServoRoll  = AngIniServoRoll;
int AngModServoPitch = AngIniServoPitch;
int AngModServoYaw   = AngIniServoYaw;
//Use to write in servos
int angleServoRoll  = AngIniServoRoll;
int angleServoPitch = AngIniServoPitch;
int angleServoYaw   = AngIniServoYaw;

//ros::NodeHandle_<HardwareType, MAX_PUBLISHERS=25, MAX_SUBSCRIBERS=25, IN_BUFFER_SIZE=512, OUT_BUFFER_SIZE=512> nh;
//ros::NodeHandle_<ArduinoHardware, 2, 2, 150, 150> nh;
ros::NodeHandle nh;

/*
std_msgs::Float32 dis_msg;
ros::Publisher send_dis("Send_Distance", &dis_msg);
*/

//std_msgs::String pos_msg;
//ros::Publisher send_pos("Send_Position", &pos_msg);

/*
//Subscribe to Send CHAR pour active the LASER
void activeLaser( const std_msgs::Empty& active_laser){
  Laser.print('D');
}

ros::Subscriber<std_msgs::Empty> act_laser("Active_Laser", &activeLaser );
*/
//Subscribe to RECEIVE the modify position of the Head
void pos_change(const std_msgs::String& cmd_msg){
  nh.loginfo("POSITION RECEIVED");
  nh.loginfo(cmd_msg.data);
  nh.loginfo("DEBUG");
  if(strcmp(cmd_msg.data, "reset") == 0){
    nh.loginfo("RESET");
    nh.loginfo(cmd_msg.data);
    AngModServoRoll=AngIniServoRoll;
    AngModServoPitch=AngIniServoPitch;
    AngModServoYaw=AngIniServoYaw;  
  }else{
    /*
    if(strcmp(cmd_msg.data, "r") == 0){
      //SET THE SERVOS VALUES
      for(int i=0;i<20;i++){
        AngModPitch--;
        servo2.write(AngModPitch);  
        delay(20);
      }    
      char result[8]; // Buffer big enough for 7-character float
      dtostrf(AngModPitch, 6, 2, result); // Leave room for too large numbers!
      nh.loginfo(result);
    }else if(strcmp(cmd_msg.data, "l") == 0){
      for(int i=0;i<20;i++){
        AngModPitch++;
        servo2.write(AngModPitch);  
        delay(20);
      }    
      //AngModRoll=AngModRoll+20;
      char result[8]; // Buffer big enough for 7-character float
      dtostrf(AngModPitch, 6, 2, result); // Leave room for too l
       nh.loginfo(result);
    }
    */
  
    char buf[3];
    int j=0;
    int size_msg = strlen( (const char* ) cmd_msg.data);
    //float AngYawBegin = AngModServoYaw;
    //float AngPitchBegin = AngModServoPitch;
    for (int i=0;i<size_msg;i++){
      if (cmd_msg.data[i]=='a'){
        AngModServoRoll=atof(buf);
        j=0;
        memset(buf, 0, sizeof(buf));
        char result1[8]; // Buffer big enough for 7-character float
        dtostrf(AngModServoRoll, 6, 2, result1); // Leave room for too l
       nh.loginfo(result1);
      }else if (cmd_msg.data[i]=='b'){
        AngModServoPitch=atof(buf);
        j=0;
        memset(buf, 0, sizeof(buf));
        char result2[8]; // Buffer big enough for 7-character float
        dtostrf(AngModServoPitch, 6, 2, result2); // Leave room for too l
       nh.loginfo(result2);
      }else if(cmd_msg.data[i]=='c'){
        AngModServoYaw=atof(buf);
        char result3[8]; // Buffer big enough for 7-character float
        dtostrf(AngModServoYaw, 6, 2, result3); // Leave room for too l
        nh.loginfo(result3);
      }else{
        buf[j]=cmd_msg.data[i];
        j++;
      }
    }
    if (AngModServoYaw > 130){
      AngModServoYaw=130;
    }else if (AngModServoYaw<20){
      AngModServoYaw=20;
    }
    if (AngModServoPitch > 100){
      AngModServoPitch=100;
    }else if (AngModServoPitch<20){
      AngModServoPitch=20;
    }
    /*
    if(AngModServoYaw<AngYawBegin){
      for(int i=AngYawBegin;i>AngModServoYaw;i--){
        servo3.write(i);  
        delay(20);
      }    
    }else{
      for(int i=AngYawBegin;i<AngModServoYaw;i++){
        servo3.write(i);  
        delay(20);
      }   
    }
    if(AngModServoPitch<AngPitchBegin){
      for(int i=AngPitchBegin;i>AngModServoPitch;i--){
        servo2.write(i);  
        delay(20);
      }    
    }else{
      for(int i=AngPitchBegin;i<AngModServoPitch;i++){
        servo2.write(i);  
        delay(20);
      }   
    }
    */
    servo1.write(AngModServoRoll);  
    servo2.write(AngModServoPitch);  
    servo3.write(AngModServoYaw);  
    //processAccelGyro();
    //AngIniPitch=mpuPitch;
    //AngIniYaw=mpuYaw;
    delay(100);
  }
}
ros::Subscriber<std_msgs::String> pos_rec("Pos_Change", pos_change);
/*
void ConfigMPU6050(){

  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
    TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
  #endif

  Serial.begin(115200);
  while (!Serial);      // wait for Leonardo enumeration, others continue immediately

  // initialize device
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();

  // verify connection
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

  // load and configure the DMP
  Serial.println(F("Initializing DMP"));
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
    Serial.println(F("Enabling DMP"));
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)"));
    mpuIntStatus = mpu.getIntStatus();

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  }
  else
  {
    // ERROR!
    // 1 = initial memory load failed, 2 = DMP configuration updates failed (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed code = "));
    Serial.println(devStatus);
  }

}
*/
void setup() {
  //Serial.begin(115200);
  delay(100); 
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object
  servo2.attach(10);  // attaches the servo on pin 10 to the servo object
  servo3.attach(11);  // attaches the servo on pin 911 to the servo object
  
 
  servo1.write(angleServoRoll);  
  delay(20); 
  servo2.write(angleServoPitch);   
  delay(20); 
  servo3.write(angleServoYaw);   
  delay(20); 
  //Laser.begin(19200);
  //ConfigMPU6050();
  /*
  double timeSetup = millis(); //Tempo para estabilizar leituras
  while (millis() - timeSetup < 10000) {
    //Serial.println(millis()-tempo); // Imprime o tempo passado
    processAccelGyro();
    /*
    char buffer[80];
    char rollValue[8];
    char pitchValue[8];
    char yawValue[8];
    dtostrf(mpuRoll, 3, 2, rollValue);
    dtostrf(mpuPitch, 3, 2, pitchValue);
    dtostrf(mpuYaw, 3, 2, yawValue);
    snprintf(buffer, sizeof(buffer), "Calibrating %s,%s,%s", rollValue,pitchValue,yawValue);
    pos_msg.data = buffer;
    send_pos.publish(&pos_msg);
    
  }
  */
  /*
  AngIniRoll=mpuRoll;
  AngIniPitch=mpuPitch;
  AngIniYaw=mpuYaw;
  */
  //ROS Configuration
  nh.initNode();
  //nh.subscribe(act_laser);
  nh.subscribe(pos_rec);
  //nh.advertise(send_dis);
  //nh.advertise(send_pos);
  delay(100);
}

void loop(){
  nh.spinOnce();
  delay(100);
  //processAccelGyro();
  /*IF Laser send something
  while (Laser.available()>0) {
    int inChar = Laser.read();
    if (inChar != 'm') { 
      if (inChar != ' '){
       inString += (char)inChar;
      }else{
        inString = "";
      }
    }
    else {
      dis_msg.data=inString.toFloat();
      //SEND distance value with PUBLISH
      send_dis.publish(&dis_msg);
      inString = "";
    }
  }
  */
  

  /*STABILIZATION
  angleServoRoll = AngModServoRoll+1.5*(AngIniRoll-mpuRoll);
  angleServoPitch = AngModServoPitch-1.5*(AngIniPitch-mpuPitch);
  angleServoYaw = AngModServoYaw -1.5*(AngIniYaw-mpuYaw);
  
  servo1.write(AngModServoRoll);  
  servo2.write(AngModServoPitch);  
  servo3.write(AngModServoYaw);  
  */
  //SEND WITH PUBLISH TOPIC
  /*
  char rollValue[8];
  char pitchValue[8];
  char yawValue[8];
  dtostrf(mpuRoll, 3, 2, rollValue);
  dtostrf(mpuPitch, 3, 2, pitchValue);
  dtostrf(mpuYaw, 3, 2, yawValue);
  
  char rollServo[8];
  char pitchServo[8];
  char yawServo[8];
  dtostrf(AngModServoRoll, 3, 2, rollServo);
  dtostrf(AngModServoPitch, 3, 2, pitchServo);
  dtostrf(AngModServoYaw, 3, 2, yawServo);
  */
  /*
  char rollServo0[6];
  char pitchServo0[6];
  char yawServo0[6];
  dtostrf(angleServoRoll, 3, 2, rollServo0);
  dtostrf(angleServoPitch, 3, 2, pitchServo0);
  dtostrf(angleServoYaw, 3, 2, yawServo0);
  snprintf(buffer, sizeof(buffer), "G: %s,%s,%s S: %s,%s,%s S0: %s,%s,%s", rollValue,pitchValue,yawValue,rollServo,pitchServo,yawServo,rollServo0,pitchServo0,yawServo0);
  */
  //char buffer[80];
  //snprintf(buffer, sizeof(buffer), "G: %s,%s,%s S: %s,%s,%s", rollValue,pitchValue,yawValue,rollServo,pitchServo,yawServo);
  //pos_msg.data = buffer;
  //send_pos.publish(&pos_msg);
}



// ================================================================
// ===                    PROCESS ACCEL/GYRO IF AVAILABLE       ===
// ================================================================
/*
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
    Serial.println(F("FIFO overflow!"));
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
    mpuPitch = ypr[PITCH] * 180 / M_PI +90;
    mpuRoll = ypr[ROLL] * 180 / M_PI +90;
    mpuYaw  = ypr[YAW] * 180 / M_PI +90;

    // flush buffer to prevent overflow
    mpu.resetFIFO();

    //delay(10);

  } // if (mpuIntStatus & 0x02)
}  // processAccelGyro()
*/
