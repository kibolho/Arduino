int ButtonPin = 12; // LED connected to pin 48 (on-board LED)
int ButtonPin2 = 11; // LED connected to pin 48 (on-board LED)

void setup() {

  pinMode(ButtonPin, INPUT);  // pin 48 (on-board LED) as OUTPUT
   pinMode(ButtonPin2, INPUT);  // pin 48 (on-board LED) as OUTPUT
  Serial.begin(9600);       // start serial communication at 9600bps
}

void loop() {
  if(digitalRead(ButtonPin)==1){
    Serial.print('H');
  }else if(digitalRead(ButtonPin2)==1){
          Serial.print('D');
  }
} 
