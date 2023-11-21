#include <MFRC522.h>
#include <RFID.h>

#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);

int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;

void setup(){
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}

void loop(){
  if(rfid.isCard()){
    if(rfid.readCardSerial()){
      if(rfid.serNum[0] != serNum0
        ||rfid.serNum[1] != serNum1
        ||rfid.serNum[2] != serNum2
        ||rfid.serNum[3] != serNum3
        ||rfid.serNum[4] != serNum4
       ){
         Serial.print(" ");
         Serial.print("Card Found");
         serNum0 = rfid.serNum[0];
         serNum1 = rfid.serNum[1];
         serNum2 = rfid.serNum[2];
         serNum3 = rfid.serNum[3];
         serNum4 = rfid.serNum[4];
         
         Serial.print("Card Number:");
         Serial.print("DEC:");
         Serial.print(rfid.serNum[0], DEC);
         Serial.print(", ");
                Serial.print(rfid.serNum[1], DEC);
         Serial.print(", ");
                Serial.print(rfid.serNum[2], DEC);
         Serial.print(", ");
                Serial.print(rfid.serNum[3], DEC);
         Serial.print(", ");
                Serial.print(rfid.serNum[4], DEC);

       }else{
          Serial.print(".");
       }
    }
  }
  rfid.halt();
}
