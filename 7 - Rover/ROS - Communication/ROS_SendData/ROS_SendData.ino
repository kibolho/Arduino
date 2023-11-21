/*
 * rosserial Temperature Sensor Example
 * 
 * This tutorial demonstrates the usage of the
 * Sparkfun TMP102 Digital Temperature Breakout board
 * http://www.sparkfun.com/products/9418
 * 
 * Source Code Based off of:
 * http://wiring.org.co/learning/libraries/tmp102sparkfun.html
 */

#include <Wire.h>
#include <ros.h>
#include "SensorsData.h"

ros::NodeHandle  nh;

location_monitor::SensorsData sensors_data;

ros::Publisher pub_data("SensorsData", &sensors_data);


void setup()
{
  Wire.begin();        // join i2c bus (address optional for master) 
  
  nh.initNode();
  nh.advertise(pub_data);
  
}

long publisher_timer;

void loop()
{
  
  if (millis() > publisher_timer) {

      sensors_data.yaw.data = 1;
      sensors_data.distance.data = 2;
      sensors_data.gps_degree.data = 3;
      sensors_data.gps_minute.data = 4;
      sensors_data.gps_second.data = 5;

      pub_data.publish(&sensors_data);
      
      publisher_timer = millis() + 1000;
  }
  
  nh.spinOnce();
}
