/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13. 
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead(). 
 
 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground
 
 * Note: because most Arduinos have a built-in LED attached 
 to pin 13 on the board, the LED is optional.
 
 
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe
 
 This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/AnalogInput
 
 */
#include <LiquidCrystal.h>
int sensorPin = A5;    // select the input pin for the potentiometer
int ledPin = 10;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
#define Contraste_PIN  6
int Contraste = 20;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

void setup() {
  pinMode(Contraste_PIN,OUTPUT); //define o pino como saída
  analogWrite(Contraste_PIN,Contraste); // Liga a luz do display.

    lcd.begin(16, 2);                            // Diz para o Arduino que o display é 16x2.
  lcd.print("Temperatura: ");           // Manda o texto para a tela do display
    // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    

  // stop the program for <sensorValue> milliseconds:
  delay(1000);          
   
  if(sensorValue<10){
      digitalWrite(ledPin, HIGH);  
  }
  else{
      digitalWrite(ledPin, LOW);  
  }  
  Serial.println(sensorValue); 
 lcd.setCursor(0, 1);           // Move o cursor do display para a segunda linha.
  lcd.print(sensorValue);    // Exibe o valor de temperatura no display.
}
