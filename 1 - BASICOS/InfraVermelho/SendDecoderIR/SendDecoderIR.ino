// This sketch will send out a Nikon D50 trigger signal (probably works with most Nikons)
// See the full tutorial at http://www.ladyada.net/learn/sensors/ir.html
// this code is public domain, please enjoy!
 
int IRledPin =  3;    // LED connected to digital pin 13
 
// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
 
  cli();  // this turns off any background interrupts
 
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei();  // this turns them back on
}
 
void setup() {
    // initialize the IR digital pin as an output:
  pinMode(IRledPin, OUTPUT);      
 
  Serial.begin(9600);

  // This is the code for my particular Nikon, for others use the tutorial
  // to 'grab' the proper code from the remote
pulseIR(8840);

delayMicroseconds(4380);

pulseIR(540);

delayMicroseconds(1640);

pulseIR(540);

delayMicroseconds(1640);

pulseIR(540);

delayMicroseconds(1660);

pulseIR(520);

delayMicroseconds(560);

pulseIR(520);

delayMicroseconds(580);

pulseIR(520);

delayMicroseconds(560);

pulseIR(520);

delayMicroseconds(580);

pulseIR(500);

delayMicroseconds(1680);

pulseIR(520);

delayMicroseconds(580);

pulseIR(500);

delayMicroseconds(1680);

pulseIR(520);

delayMicroseconds(1660);

pulseIR(520);

delayMicroseconds(1680);

pulseIR(520);

delayMicroseconds(1660);

pulseIR(520);

delayMicroseconds(580);

pulseIR(500);

delayMicroseconds(1680);

pulseIR(520);

delayMicroseconds(580);

pulseIR(500);

delayMicroseconds(580);

pulseIR(500);

delayMicroseconds(1680);

pulseIR(520);

delayMicroseconds(560);

pulseIR(540);

delayMicroseconds(560);

pulseIR(520);

delayMicroseconds(1660);

pulseIR(520);

delayMicroseconds(580);

pulseIR(520);

delayMicroseconds(560);

pulseIR(520);

delayMicroseconds(580);

pulseIR(500);

delayMicroseconds(1680);

pulseIR(520);

delayMicroseconds(560);

pulseIR(520);

delayMicroseconds(1680);

pulseIR(520);

delayMicroseconds(1660);

pulseIR(520);

delayMicroseconds(580);

pulseIR(500);

delayMicroseconds(1680);

pulseIR(520);

delayMicroseconds(1680);

pulseIR(500);

delayMicroseconds(1680);

pulseIR(520);

delayMicroseconds(38980);

pulseIR(8740);

delayMicroseconds(2220);

pulseIR(520);
}
void loop()                     
{

}
