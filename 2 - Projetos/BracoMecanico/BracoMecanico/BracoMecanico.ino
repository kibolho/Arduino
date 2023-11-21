#include <Servo.h>
 
Servo servo1;
 Servo servo2;
 Servo servo3;
 Servo servo4;

int Servo1 = 9;
int Servo2 = 10;
int Servo3 = 11;
int Servo4 = 12;
 
const char HEADER       = 'H';
const char MOUSE_TAG    = 'M';
const int  TOTAL_BYTES  = 10  ; // the total bytes in a message

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
servo1.attach(Servo1);
servo2.attach(Servo2);
servo3.attach(Servo3);
servo4.attach(Servo4);

servo1.write(0);
        servo2.write(0);
        servo3.write(90);
        servo4.write(90);
        
}
 
void loop()
{
  if (!servo1.attached()) servo1.attach(Servo1);
    if (!servo2.attached()) servo2.attach(Servo2);
    if (!servo3.attached()) servo3.attach(Servo3);
  if (!servo4.attached()) servo3.attach(Servo4);
  if ( Serial.available())
  {
      char tag = Serial.read();
      if(tag == MOUSE_TAG)
      {
        int x = Serial.read() * 256; 
        x = x + Serial.read();
        int w = Serial.read() * 256;
        w = w + Serial.read();
         int y = Serial.read() * 256; 
        y = y + Serial.read();
         int z = Serial.read() * 256; 
        z = z + Serial.read();
         Serial.print(x);
        servo1.write(x);
        servo2.write(w);
        servo3.write(y);
        servo4.write(z);
      }
      else
      {
        Serial.print("got message with unknown tag ");
        Serial.write(tag);
      }
    }
  }
    servo1.detach();
    servo2.detach();
    servo3.detach();
    servo4.detach();
}
