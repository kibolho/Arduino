#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;

#include <Servo.h>
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
Servo servo3;  // create servo object to control a servo

float Angini1=70, Angini2 = 72, Angini3 = 93;
float angle1=Angini1, angle2=Angini2, angle3=Angini3;

#include <SoftwareSerial.h>
SoftwareSerial Laser(7,8);//RX TX
char b;
char c;
float dis=0;

float roll=0;
float pitch=0;

void setup() {
  Serial.begin(115200);

  servo1.attach(9);  // attaches the servo on pin 9 to the servo object
  servo2.attach(10);  // attaches the servo on pin 10 to the servo object
  servo3.attach(11);  // attaches the servo on pin 911 to the servo object
  
  Serial.println("Initialize MPU6050");
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);  }
    
  servo1.write(angle1);  
  delay(20); 
  servo2.write(angle2);   
  delay(20); 
  servo3.write(angle3);   
  delay(20); 
      
  Laser.begin(19200);
  Serial.println("Arduino A : je suis pret a recevoir/emettre");
  }

void loop(){
  
  if (Serial.available()) {
    
    b=Serial.read();
    Laser.print('D');
   }

  if (Laser.available()) {
    for (int i = 0 ; i < 4 ; i++){
      if(i==2){
        dis=Laser.parseFloat();
        if(dis>0){
          Serial.println(dis);
        }
      }else{
        Laser.parseFloat();
      }
    }
    
  }

 for (int i = 0; i < 10; i++) {
    Vector normAccel = mpu.readNormalizeAccel();
    roll = roll + (0.1*((atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI));
    pitch = pitch + (0.1*(-(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI));
 }

 for (int j = 0; j < 10; j++) {
    angle1=Angini1-(0.1*j*roll);
    angle2=Angini2-(0.1*j*pitch);
 }
  servo2.write(angle2);   
  servo1.write(angle1);    
  delay(20); 
  roll=0;
  pitch=0;
  
}


