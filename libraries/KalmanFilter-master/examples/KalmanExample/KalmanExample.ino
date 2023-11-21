/* https://github.com/bachagas/Kalman
 */
#include <KalmanFilter.h>

//Creates the variables:
double measurement, filteredMeasurement;
Kalman myFilter(0.125,32,1023,0); //suggested initial values for high noise filtering
void setup() {

}
void loop() {

  //reads measurement and filter it
  measurement = (double) analogRead(A1); //read new value from sensor in analog pin A1, for example
  filteredMeasurement = myFilter.getFilteredValue(measurement);
}