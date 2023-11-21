/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social groups:              http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example runs directly on ESP8266 chip.
 *
 * You need to install this for ESP8266 development:
 *   https://github.com/esp8266/Arduino
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 *
 **************************************************************/

//#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//NORMAL
//char auth[] = "f1cc0a757a4544a796b2b937367cb612";
//RELAY
char auth[] = "ae62df068fe64171bbd7dc5a87d5a572";
#define buttonPin 0    // the number of the pushbutton pin
#define ledPin 5      // the number of the LED pin
WidgetLED STAT(2);
// Variables will change:
int ledState = LOW;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
String sent = "NaN";
void setup()
{
  Serial.begin(9600);
  //pinMode(2,INPUT_PULLUP);
  Blynk.begin(auth, "Azevedos", "S1E6547970");
  while(!Blynk.connect()){
    //Wait until connected
  }
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
}

void loop()
{
  Blynk.run();
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  // set the LED:
  digitalWrite(ledPin, ledState);
  if (ledState == LOW){
     STAT.off();
  }else{
     STAT.on();
  }
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
  
 // if(digitalRead(2)){
  //  Blynk.push_notification("PRESSED");
  //    Serial.println("1");
  //}else{
  //  Serial.println("0");
 // }
}
BLYNK_READ(0){ 
  int sensorValue = analogRead(A0);
  float volt = (sensorValue/1024.0) * 5;
  int tempC2 = (volt) * 100;
  int tempC1 = (volt) * 10;
  tempC1 = tempC1 * 10;
  tempC2 = tempC2 - tempC1;
  sent = String(tempC1/10) + "," + String(tempC2);
  sent = sent + " ℃";
  Blynk.virtualWrite(0, sent);
}
BLYNK_READ(3){ 
  Blynk.virtualWrite(3, sent);
}
// Update status to virtual pin 1
BLYNK_WRITE(1) {
  //int v1 = param.asInt();
  //ledState = bool(v1);
  int v1 = param.asInt();
  if(bool(v1)==true){
    ledState = !ledState;
  }
}


