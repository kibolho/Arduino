//simple Tx on pin D12
//Written By : Mohannad Rawashdeh
// 3:00pm , 13/6/2013
//http://www.genotronex.com/
//..................................
#include <VirtualWire.h>

int sound = 9;
void setup()
{
       Serial.begin(9600); //inicia a porta serial  
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_set_rx_pin(2);
    vw_setup(4000);  // Bits per sec
    pinMode(13, OUTPUT);
    vw_rx_start();       // Start the receiver PLL running
}
    void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      if(buf[0]=='1'){
            Serial.print("Recebeu"); 
        digitalWrite(13,1);
        alarm();         
      }  
   if(buf[0]=='0'){
      digitalWrite(13,0);
    }

}
}
 void alarm(void){
  Serial.print("SOUND");  
  tone (sound, 400);
  delay (500);
  tone (sound, 1000);
  delay (500);
  noTone (sound);
}
