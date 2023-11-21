#include <Wire.h>
#include <HMC5883L.h>
 
HMC5883L compass;
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void setup()
{
   Wire.begin();
   Serial.begin(9600);
   compass = HMC5883L();
 
   Serial.println("Setting scale to +/- 1.3Ga");
   int error = compass.SetScale(1.3);
   if(error != 0)
     Serial.println(compass.GetErrorText(error));
 
   Serial.println("Setting measurement mode to continuous");
   error = compass.SetMeasurementMode(Measurement_Continuous);
   if(error != 0)
   Serial.println(compass.GetErrorText(error));
     for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}
 
void loop()
{
   MagnetometerRaw raw = compass.ReadRawAxis();
   float heading = atan2(raw.YAxis, raw.XAxis);
   float declinationAngle = -389.8/1000;
   heading += declinationAngle;
   if(heading < 0)
      heading += 2*PI;
   else if(heading>2*PI)
      heading -= 2*PI;
   float headingDegrees = heading * 180/M_PI;
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = headingDegrees;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  // calculate the average:
  average = total / numReadings;
   Serial.println(average);
   delay(100);
}
