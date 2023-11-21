//Usando os solenoides com pregos para tocar uma musica
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int tone1 = 9;
int tone2 = 10;
int tone3 = 11;
int tone4 = 12;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(tone1, OUTPUT);    
   pinMode(tone2, OUTPUT); 
    pinMode(tone3, OUTPUT); 
     pinMode(tone4, OUTPUT); 
     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(tone1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(tone1, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
  digitalWrite(tone2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(tone2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
  digitalWrite(tone3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(tone4, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}
