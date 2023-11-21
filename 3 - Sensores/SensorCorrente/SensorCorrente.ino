
//http://helpdev.com.br/2014/01/01/arduino-sensor-de-corrente-acs712-em-ac-e-dc-monitoring-current-with-arduino-and-acs712/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd (8, 9, 4, 5, 6, 7);

int sensorPin =A5;
 
int sensorValue_aux = 0;
float sensorValue = 0;
float currentValue = 0;
float voltsporUnidade = 0.004887586;// 5%1023
 
void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
    // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Corrente:");
}
 
void loop() {
 
  for(int i=100; i>0; i--){
    sensorValue_aux = (analogRead(sensorPin) -511); // le o sensor na pino analogico A0 e ajusta o valor lido ja que a saída do sensor é (1023)vcc/2 para corrente =0
    sensorValue += pow(sensorValue_aux,2); // somam os quadrados das leituras.
  }
 
  sensorValue = (sqrt(sensorValue/ 100)) * voltsporUnidade; // finaliza o calculo da méida quadratica e ajusta o valor lido para volts
  currentValue = (sensorValue/0.185); // calcula a corrente considerando a sensibilidade do sernsor (185 mV por amper)
 
  // mostra o resultado no terminal
  Serial.print(currentValue,3);
  Serial.print(" A \n" ); 
  
   // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(currentValue);
  lcd.setCursor(7, 1);
  lcd.print("A");
  sensorValue =0;
  
 
  delay(100);
 
}
