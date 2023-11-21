
#include "I2Cdev.h"
#include <Servo.h>

#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high
double angle=0;
double oldAngle=angle;

#define INTERRUPT_PIN 18  // use pin 2 on Arduino Uno & most boards
#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
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
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

//
//
//HEAD
//
//
//These are variables that hold the servo IDs.
char PitchChannel=0, YawChannel=1, LaserChannel = 2, motorAngleChannel = 3, motorDistanceChannel = 4;

//These are the objects for each servo.
Servo servoRoll1;  // create servo object to control a servo
Servo servoPitch2;  // create servo object to control a servo
Servo servoYaw3;  // create servo object to control a servo

int AngIniServoRoll=80, AngIniServoPitch = 50, AngIniServoYaw = 93;

//This is a character that will hold data from the Serial port.
char serialChar=0;
String inString = "";
float distanceTarget = 0;
//
//
//MOTORS
//
//
Servo gaucheAvant, gaucheArriere, droitAvant, droitArriere;

// Inicial Position of each Servo
int zeroDegreeGaucheAvant = 60;
int zeroDegreeGaucheArriere = 65;
int zeroDegreeDroitAvant = 90;
int zeroDegreeDroitArriere = 80;

void getAngles(){
  // if programming failed, don't try to do anything
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
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

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        //Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

        // display Euler angles in degrees
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

        angle = ypr[0] * 180 / M_PI;
        if (angle < 0) {
          angle = -angle;
          angle = map(angle, 0, 180, 180, 0);
          angle = angle + 180;
        }

        
        //Serial.println(angle);
        // blink LED to indicate activity
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
    }
}

// Fonction to have the ROVER rotating *********************************************************************************
void rotateGauche(int speed=100, int degree=45,int degreeMove = 0 ){ 
  //Positioning Servo
  gaucheAvant.write(zeroDegreeGaucheAvant-degree);
  gaucheArriere.write(zeroDegreeGaucheArriere+degree);
  droitAvant.write(zeroDegreeDroitAvant+degree);
  droitArriere.write(zeroDegreeDroitArriere-degree);
  delay(3000);

  //SETUP MOTORS-------------------------------------------------
  for (int i=8;i<=10;i++){//dir gauche
    digitalWrite(i,LOW);

  }
  for (int i=11;i<=13;i++){//dir droit
    digitalWrite(i,HIGH);
  }

  for (int i=2;i<=7;i++){//pwm
    analogWrite(i,speed);
  }
  getAngles();
 
  int angleInit = angle;
  double angleFinal = angleInit-degreeMove;
  while(abs(angleFinal-angle)>1){
    Serial.print("Angle Init  = ");
    Serial.println(angleInit);
    Serial.print("Angle       = ");
    Serial.println(angle);
    Serial.print("Angle Final = ");
    Serial.println(angleFinal);
    getAngles();
  }
  //Keep motors ON for TIME ms
  Serial.print("Target");
  //TURN OFF MOTORS-------------------------------------------------
  for (int i=2;i<=7;i++){//pwm
    analogWrite(i,0);
  }
  rotateZero();
}
// Fonction to have the HOVER rotating*********************************************************************************
void rotateDroit(int speed=100, int degree=45,int degreeMove = 0){
  //Positioning Servo
  gaucheAvant.write(zeroDegreeGaucheAvant-degree);
  gaucheArriere.write(zeroDegreeGaucheArriere+degree);
  droitAvant.write(zeroDegreeDroitAvant+degree);
  droitArriere.write(zeroDegreeDroitArriere-degree);
  delay(3000);

  //SETUP MOTORS-------------------------------------------------
  for (int i=8;i<=10;i++){//dir gauche
    digitalWrite(i,HIGH);

  }
  for (int i=11;i<=13;i++){//dir droit
    digitalWrite(i,LOW);
  }

  for (int i=2;i<=7;i++){//pwm
    analogWrite(i,speed);
  }
  getAngles();
 
  int angleInit = angle;
  double angleFinal = angleInit+degreeMove;
  while(abs(angleFinal-angle)>1){
    Serial.print("Angle Init  = ");
    Serial.println(angleInit);
    Serial.print("Angle       = ");
    Serial.println(angle);
    Serial.print("Angle Final = ");
    Serial.println(angleFinal);
    getAngles();
  }
  //Keep motors ON for TIME ms
  Serial.print("Target");
  //TURN OFF MOTORS-------------------------------------------------
  for (int i=2;i<=7;i++){//pwm
    analogWrite(i,0);
  }
  rotateZero();
}


//*********************************************************************************
void rotateZero(){
  
  //Positioning Servo-------------------------------------------------
  gaucheAvant.write(zeroDegreeGaucheAvant);
  gaucheArriere.write(zeroDegreeGaucheArriere);
  droitAvant.write(zeroDegreeDroitAvant);
  droitArriere.write(zeroDegreeDroitArriere);
  delay(1000);
}

//*********************************************************************************
void left(int degree=45){
  //Positioning Servo-------------------------------------------------
  gaucheAvant.write(zeroDegreeGaucheAvant+degree);
  gaucheArriere.write(zeroDegreeGaucheArriere-degree);
  droitAvant.write(zeroDegreeDroitAvant+degree);
  droitArriere.write(zeroDegreeDroitArriere-degree);
}

//*********************************************************************************
void right(int degree=45){
  //Positioning Servo-------------------------------------------------
  gaucheAvant.write(zeroDegreeGaucheAvant-degree);
  gaucheArriere.write(zeroDegreeGaucheArriere+degree);
  droitAvant.write(zeroDegreeDroitAvant-degree);
  droitArriere.write(zeroDegreeDroitArriere+degree);
}

//*********************************************************************************
void backward(int speed=100,int time=10000){
    
  //SETUP MOTORS-------------------------------------------------
  for (int i=8;i<=10;i++){//dir gauche
    digitalWrite(i,LOW);
  }
  for (int i=11;i<=13;i++){//dir droit
    digitalWrite(i,LOW);
  }
  
  //TURN ON MOTORS-------------------------------------------------
  for (int i=2;i<=7;i++){
  //pwm file:///C|/Users/Pascal/AppData/Local/Temp/MainSoftware.ino.txt[02/11/2017 18:28:17]
    analogWrite(i,speed);
  }
  
  //Keep motors ON for TIME ms-------------------------------------------------
  delay(time);
  
  //TURN OFF MOTORS-------------------------------------------------
  for (int i=2;i<=7;i++){//pwm
  analogWrite(i,0);
  }
}

//*********************************************************************************
void forward(int speed=100,int time=10000){
  rotateZero();
  //SETUP MOTORS-------------------------------------------------
  for (int i=8;i<=10;i++){//dir gauche
  digitalWrite(i,HIGH);
  }
  for (int i=11;i<=13;i++){//dir droit
  digitalWrite(i,HIGH);
  }
  
  //TURN ON MOTORS-------------------------------------------------
  for (int i=2;i<=7;i++){//pwm
  analogWrite(i,speed);
  }
  
  //Keep motors ON for TIME ms-------------------------------------------------
  delay(time);//mÃªme vitesse pendant time secondes
  
  //TURN OFF MOTORS-------------------------------------------------
  for (int i=2;i<=7;i++){//pwm
    analogWrite(i,0);
  }
}

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
    //
    //MOTORS
    //
    gaucheAvant.attach(29);
    gaucheArriere.attach(28);
    droitAvant.attach(30);
    droitArriere.attach(31); 
    
    //
    //HEAD
    //
    servoRoll1.attach(32);  // attaches the servo on pin 9 to the servo object
    servoPitch2.attach(33);  // attaches the servo on pin 10 to the servo object
    servoYaw3.attach(34);  // attaches the servo on pin 911 to the servo object
    servoRoll1.write(AngIniServoRoll);  
    servoPitch2.write(AngIniServoPitch);   
    servoYaw3.write(AngIniServoYaw);   

    //
    //LASER
    //
    Serial3.begin(19200);
  

    // CONFIGURE MOTORS
    for (int i=2;i<=7;i++){//pwm
      pinMode(i,OUTPUT);
    }
    for (int i=8;i<=13;i++){//dir
      pinMode(i,OUTPUT);
    }

    rotateZero();

    //
    //MPU6050
    //
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    // initialize serial communication
    // (115200 chosen because it is required for Teapot Demo output, but it's
    // really up to you depending on your project)
    Serial.begin(57600);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately

    // NOTE: 8MHz or slower host processors, like the Teensy @ 3.3V or Arduino
    // Pro Mini running at 3.3V, cannot handle this baud rate reliably due to
    // the baud timing being too misaligned with processor ticks. You must use
    // 38400 or slower in these cases, or use some kind of external separate
    // crystal solution for the UART timer.

    // initialize device
    //Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);

    // verify connection
    //Serial.println(F("Testing device connections..."));
    //Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // load and configure the DMP
    //Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        //Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        //Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        //Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        //Serial.print(F("DMP Initialization failed (code "));
        //Serial.print(devStatus);
        //Serial.println(F(")"));
    }

    // configure LED for output
    pinMode(LED_PIN, OUTPUT);

    double tempo = millis(); //Tempo para estabilizar leituras
    while (millis() - tempo < 15000) {
      Serial.println(millis()-tempo); // Imprime o tempo passado
      getAngles();
    }
    oldAngle=angle;
  
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
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
      }else if(serialChar == motorAngleChannel){
        char inputBuffer[4];
        int index = 0;
        while(Serial.available()>0){
          inputBuffer[index]=Serial.read();
          index = index + 1;
        }
        char * strtokIndx; // this is used by strtok() as an index
        strtokIndx = strtok(inputBuffer,"");      // get the first part - the string
        int angleTarget = atoi(strtokIndx);     // convert this part to an integer

        //int angleTarget = int(Serial.read());
        Serial.print("Angle Received to Rotate: ");
        Serial.println(angleTarget);
        if (angleTarget>0){
          rotateGauche(100,45,angleTarget);
        }else{
          rotateDroit(100,45,-angleTarget);
        }
        Serial.print("Distance Received: ");
        Serial.println(distanceTarget);
        Serial.println("target ok");
      }else if(serialChar == motorDistanceChannel){
        forward(100,distanceTarget*10);
      }
    }
    while(Serial3.available()> 0){
      //serialChar =Serial3.read();
      //Serial.print(serialChar);
      int inChar = Serial3.read();
      //Serial.print(inChar);
      if (inChar != 'm') { 
        if (inChar != ' '){
         inString += (char)inChar;
        }else{
          inString = "";
        }
      }
      else {
        //inString.toFloat();
        distanceTarget=inString.toFloat();
        Serial.print("Distance Received From Sensor: ");
        Serial.println(distanceTarget);
        inString = "";
      }
    }
    
}
