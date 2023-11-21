/*
irSend sketch
this code needs an IR LED connected to pin 3
and 5 switches connected to pins 4 - 8
*/
// Power ON/OFF
unsigned int S_pwr[68]={4600,4350,700,1550,650,1550,650,1600,650,450,650,450,650,450,650,450,700,400,700,1550,650,1550,650,1600,650,450,650,450,650,450,700,450,650,450,650,450,650,1550,700,450,650,450,650,450,650,450,650,450,700,400,650,1600,650,450,650,1550,650,1600,650,1550,650,1550,700,1550,650,1550,650};

// channel 1 
unsigned int S_1[68]={4650,4300,700,1550,700,1550,650,1550,700,400,700,400,700,400,700,450,700,400,700,1500,700,1500,700,1550,700,450,650,400,700,450,650,450,700,400,700,400,700,450,650,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,450,650,1550,700,1550,650,1550,700,1500,700,1550,650};

// channel 2
unsigned int S_2[68]={4600,4350,650,1550,700,1500,700,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1500,700,1550,700,400,700,450,650,450,700,400,700,400,700,1500,700,400,700,1550,700,400,700,400,700,450,650,450,700,400,700,400,700,1550,650,450,700,1500,700,1550,650,1550,700,1500,700,1550,650};

// channel 3
unsigned int S_3[68]={4600,4350,700,1500,700,1550,650,1600,650,400,700,450,700,400,700,400,700,400,700,1550,650,1550,700,1500,700,400,700,450,700,400,700,400,700,400,700,400,700,1550,700,1500,700,450,650,450,700,400,700,400,700,400,700,1550,700,400,700,400,700,1550,650,1550,700,1500,700,1550,700,1500,700};

// channel 4
unsigned int S_4[68]={4600,4350,650,1550,700,1500,700,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,450,650,450,700,400,700,400,700,400,700,400,700,450,650,1550,700,400,700,400,700,450,700,400,700,1500,700,1550,650,1550,700,400,700,1550,650,1550,700,1500,700,1550,650};

// channel 5
unsigned int S_5[68]={4650,4350,700,1500,700,1550,650,1550,700,400,700,450,700,400,700,400,700,400,700,1500,700,1550,700,1500,700,450,650,450,700,400,700,400,700,400,700,1550,700,400,700,400,650,1550,700,450,650,450,700,400,700,450,650,450,650,1550,650,1550,700,400,700,1550,700,1500,700,1500,700,1550,700};

// channel 6
unsigned int S_6[68]={4600,4350,650,1550,700,1500,700,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,450,700,400,700,400,700,400,700,400,700,1550,700,400,700,1500,700,450,650,450,700,400,700,400,700,1550,650,450,650,1550,700,400,700,1550,650,1550,700,1500,700,1550,650};
 
// channel 7
unsigned int S_7[68]={4600,4350,700,1500,700,1550,650,1550,700,400,700,450,700,400,700,400,700,400,700,1550,650,1550,700,1500,700,400,700,450,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,450,700,400,700,400,700,450,650,1550,650,1550,700,450,650,400,700,1550,700,1500,700,1550,650,1550,700};
 
// channel 8
unsigned int S_8[68]={4600,4350,650,1600,650,1500,700,1550,700,400,700,400,700,400,700,450,700,400,700,1500,700,1550,650,1550,700,400,700,450,650,450,700,400,700,400,700,1550,650,450,650,1550,700,1500,700,450,700,400,700,400,700,400,700,400,700,1550,700,400,700,450,650,1550,650,1550,700,1500,700,1550,650};
 
// channel 9
unsigned int S_9[68]={4600,4350,700,1500,700,1550,650,1550,700,400,700,450,650,450,650,450,700,400,700,1500,700,1550,700,1550,650,400,700,450,700,400,700,400,700,400,700,450,650,1550,650,1600,650,1550,650,450,700,400,700,400,700,400,700,1550,700,400,700,400,700,400,700,1550,700,1500,700,1500,700,1550,700};
 
// channel 0
unsigned int S_0[68]={4650,4300,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1550,650,1550,700,400,700,400,700,400,700,450,700,400,700,1550,650,400,700,450,700,400,650,1550,700,400,700,450,700,400,700,400,700,1500,700,1550,700,1500,700,400,700,1550,650,1550,700,1500,700};
 
// source
unsigned int S_scr[68]={4600,4350,700,1550,650,1550,700,1500,700,450,650,450,700,400,700,400,700,400,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,400,700,400,700,1550,700,400,700,450,650,450,650,450,700,400,700,400,700,400,700,450,650,1550,700,1500,700,1550,650,1550,700,1500,700,1550,700,1500,700};
 
// channel up
unsigned int S_pup[68]={4600,4350,700,1500,700,1500,700,1550,700,450,650,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,450,650,450,700,400,700,400,700,400,700,400,700,1550,700,400,700,400,700,1550,650,450,700,400,700,400,700,1550,650,450,650,1600,650,1550,650,450,700,1500,700,1500,700,1550,650};
 
// channel down
unsigned int S_pdown[68]={4650,4300,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,700,400,700,400,700,400,700,450,650,450,650,1550,700,400,700,450,650,400,700,1550,700,1500,700,1550,700,1500,700,400,700,1550,650,1550,700,1500,700};
 
// volume up
unsigned int S_vup[68]={4600,4350,650,1550,700,1500,700,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,450,700,400,700,400,700,400,700,450,650,450,650,450,650,1550,700,1500,700,1550,700,1500,700,1550,650};

// volume down
unsigned int S_vdown[68]={4600,4350,700,1550,650,1550,700,1500,700,450,650,450,700,400,700,400,700,400,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,450,650,1550,700,400,700,400,700,450,700,400,700,400,700,400,700,1550,700,400,700,1500,700,1500,700,1550,700,1500,700};

// TV/DTV
unsigned int S_tv[68]={4600,4350,650,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,700,400,700,1500,700,1500,700,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,700,400,700,400,700,400,700,400,700,1550,700,400,700,400,700,400,700,1550,700,1500,700,1550,650,1550,700,400,700,1500,700};
 
// guide
unsigned int S_guide[68]={4600,4350,700,1500,700,1550,700,1500,700,450,650,450,700,400,700,400,700,400,700,1550,650,1550,700,1500,700,450,650,450,700,400,700,400,700,400,700,1550,700,1500,700,1550,650,1550,700,400,700,400,700,1550,700,400,700,400,700,400,700,450,700,400,650,1550,700,1550,650,450,700,1500,700};

// exit
unsigned int S_exit[68]={4650,4300,700,1550,650,1550,700,1550,700,400,700,400,700,450,650,450,650,450,650,1550,700,1500,700,1550,700,450,650,400,700,450,650,450,700,400,700,1500,700,400,700,1550,700,1500,700,400,700,1550,700,450,650,400,700,450,650,1550,700,400,700,400,700,1550,650,450,650,1550,700,1500,700};
 
// mute
unsigned int S_mute[68]={4650,4350,650,1550,650,1550,700,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,1550,700,400,700,450,650,400,700,450,700,400,700,1500,700,1550,650,1550,700,1500,700,450,700,400,700,400,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,1500,700};

#include <IRremote.h>
// IR remote control library
const int numberOfKeys = 3;
const int firstKey = 4;
// the first pin of the 5 sequential pins connected to buttons
boolean buttonState[numberOfKeys];
boolean lastButtonState[numberOfKeys];
long irKeyCodes[numberOfKeys] = {
0x18E758A7, //0 key
};
IRsend irsend;
void setup()
{
  for (int i = 0; i < numberOfKeys; i++){
    buttonState[i]=true;
    lastButtonState[i]=true;
    int physicalPin=i + firstKey;
    pinMode(physicalPin, INPUT);
    digitalWrite(physicalPin, HIGH); // turn on pull-ups
  }
  Serial.begin(9600);
}
void loop() {
  for (int keyNumber=0; keyNumber<numberOfKeys; keyNumber++)
  {
    int physicalPinToRead=keyNumber+4;
    buttonState[keyNumber] = digitalRead(physicalPinToRead);
    if (buttonState[keyNumber] != lastButtonState[keyNumber])
    {
     if (buttonState[keyNumber] == LOW)
      {
        if (keyNumber == 0)
        {
            irsend.sendRaw(S_pwr,68,38);
            Serial.println("Sending");
        }
         if (keyNumber == 1)
        {
            irsend.sendRaw(S_vup,68,38);
            Serial.println("Sending");
        }
         if (keyNumber == 2)
        {
            irsend.sendRaw(S_vdown,68,38);
            Serial.println("Sending");
        }
      }
      lastButtonState[keyNumber] = buttonState[keyNumber];
    }
  }
}
