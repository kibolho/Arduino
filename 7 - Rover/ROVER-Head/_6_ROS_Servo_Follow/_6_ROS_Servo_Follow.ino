
#include <Servo.h>
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
Servo servo3;  // create servo object to control a servo

#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>

float AngIniRoll=71.63, AngIniPitch = 41.60, AngIniYaw = 40.75;
float AngIniServoRoll=80, AngIniServoPitch = 70, AngIniServoYaw = 93;
//Use to modify the center
float AngModServoRoll  = AngIniServoRoll;
float AngModServoPitch = AngIniServoPitch;
float AngModServoYaw   = AngIniServoYaw;
//Use to write in servos
float angleServoRoll  = AngIniServoRoll;
float angleServoPitch = AngIniServoPitch;
float angleServoYaw   = AngIniServoYaw;

//ros::NodeHandle nh;
ros::NodeHandle_<ArduinoHardware, 2, 2, 512, 512> nh;
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
  
    servo1.write(AngModServoRoll);  
    servo2.write(AngModServoPitch);  
    servo3.write(AngModServoYaw);  
  }
}
ros::Subscriber<std_msgs::String> pos_rec("Pos_Change", pos_change);

void setup() {
  Serial.begin(115200);
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
  
  //ROS Configuration
  nh.initNode();
  nh.subscribe(pos_rec);
  delay(100);
}

void loop(){
  nh.spinOnce();
  delay(100);
}
