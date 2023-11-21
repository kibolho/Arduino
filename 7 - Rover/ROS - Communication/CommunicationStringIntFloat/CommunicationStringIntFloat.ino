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

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>

ros::NodeHandle  nh;

Servo servo;

std_msgs::String str_msg;
std_msgs::UInt16 int_msg;
std_msgs::Float32 float_msg;

ros::Publisher chatterString("chatterString", &str_msg);
ros::Publisher chatterInt("chatterInt", &int_msg);
ros::Publisher chatterFloat("chatterFloat", &float_msg);

char msg[10] = "Hello!";

void string_received(const std_msgs::String& cmd_msg){
 chatterString.publish( &cmd_msg);
}
void int_received( const std_msgs::UInt16& cmd_msg){
  servo.write(cmd_msg.data); //set servo angle, should be from 0-180  
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led 
  chatterInt.publish( &cmd_msg );
}
void float_received( const std_msgs::Float32& cmd_msg){
  chatterFloat.publish( &cmd_msg );
}
ros::Subscriber<std_msgs::String> sub_str("string", string_received);
ros::Subscriber<std_msgs::UInt16> sub_int("int", int_received);
ros::Subscriber<std_msgs::Float32> sub_float("float", float_received);

void setup(){
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  nh.initNode();
  nh.subscribe(sub_str);
  nh.subscribe(sub_int);
  nh.subscribe(sub_float);
  nh.advertise(chatterString);
  nh.advertise(chatterInt);
  nh.advertise(chatterFloat);
  servo.attach(9); //attach it to pin 9
}

void loop(){
  nh.spinOnce();
  delay(1);
}
