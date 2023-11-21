#include <VirtualWire.h>
char *controller;
#define SensorPin 8
int sound = 4;
void setup() {
    Serial.begin(9600);
  pinMode(SensorPin, INPUT);
    pinMode(13, OUTPUT);
        pinMode(sound, OUTPUT);
  vw_set_ptt_inverted(true); //
    vw_set_tx_pin(2);
    vw_setup(4000);// speed of data transfer Kbps
}

void loop() {
  if(digitalRead(SensorPin)==1){
    Serial.println("oi");
	controller="1"  ;
        vw_send((uint8_t *)controller, strlen(controller));
        vw_wait_tx(); // Wait until the whole message is gone
        digitalWrite(13,1);
        delay(2000);     
  }else{
     Serial.println("tchau");
    	controller="0"  ;
        vw_send((uint8_t *)controller, strlen(controller));
        vw_wait_tx(); // Wait until the whole message is gone
        digitalWrite(13,0);
        delay(2000);
  }
}
