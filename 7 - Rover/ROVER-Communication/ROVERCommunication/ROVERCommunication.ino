/*
 * rosserial Servo Control Example
 *
 * This sketch demonstrates the control of hobby R/C servos
 * using ROS and the arduiono
 * 
 * For the full tutorial write up, visit
 * www.ros.org/wiki/rosserial_arduino_demos
 *
 * For more information on the Arduino Servo Library
 * Checkout :
 * http://www.arduino.cc/en/Reference/Servo
 */

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include "I2Cdev.h"
#include "MPU6050.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

#include <ros.h>
#include <ros/time.h>
#include <tiny_msgs/tinyVector.h>
#include <tiny_msgs/tinyIMU.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>

ros::NodeHandle  nh;

MPU6050 accelgyro;
int16_t ax, ay, az, gx, gy, gz;



uint32_t seq;

std_msgs::String str_msg;
tiny_msgs::tinyIMU imu_msg;
ros::Publisher imu_pub("tinyImuArduino", &imu_msg);
ros::Publisher chatterString("chatterString", &str_msg);

char msg[10] = "Hello!";

void string_received(const std_msgs::String& cmd_msg){
 chatterString.publish( &cmd_msg);
}

ros::Subscriber<std_msgs::String> sub_str("string", string_received);

void setup(){
  pinMode(13, OUTPUT);
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
  nh.initNode();
  nh.advertise(chatterString);
  nh.advertise(imu_pub);
  nh.subscribe(sub_str);
  
  
  accelgyro.initialize();
  seq = 0;
  delay(500);
}

void loop(){
  seq++;
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  imu_msg.header.stamp = nh.now();
  imu_msg.header.frame_id = 0;
  imu_msg.header.seq = seq;

  imu_msg.accel.x = ax;
  imu_msg.accel.y = ay;
  imu_msg.accel.z = az;
  imu_msg.gyro.x = gx;
  imu_msg.gyro.y = gy;
  imu_msg.gyro.z = gz;

  imu_pub.publish( &imu_msg );
  nh.spinOnce();
  delay(1);
}
