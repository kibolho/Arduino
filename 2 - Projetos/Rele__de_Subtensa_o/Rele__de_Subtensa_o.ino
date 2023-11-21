/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int rele = 5;
int led = 10;
int pot = A0;
float setpoint = 2.5;

const int numReadings = 20;

float readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
float total = 0;                  // the running total
float average = 0;                // the average

// the setup routine runs once when you press reset:
void setup() {  
  // initialize serial communication with computer:
  Serial.begin(9600);          
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
    pinMode(rele, OUTPUT); 
   pinMode(pot, INPUT);       
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    
     for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;        
}

// the loop routine runs over and over again forever:
void loop() {
 // subtract the last reading:
  total= total - readings[index];         
  // read from the sensor:  
  int sensorValue = analogRead(pot);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (4.55 / 1023.0);
     
  readings[index] = voltage; 
  // add the reading to the total:
  total= total + readings[index];       
  // advance to the next position in the array:  
  index = index + 1;                    

  // if we're at the end of the array...
  if (index >= numReadings)              
    // ...wrap around to the beginning: 
    index = 0;                           

  // calculate the average:
  average = total / numReadings;         
  // send it to the computer as ASCII digits
  Serial.println(average);   
  delay(1);        // delay in between reads for stability     
  
  if(average < setpoint){
      digitalWrite(rele, LOW);   // turn the LED on (HIGH is the voltage level)
  }else{
      digitalWrite(rele, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
}
