#include <VirtualWire.h>

#define RFData 12

// Sensors 
int Sensor1Data;

// RF Transmission container
char StringReceived[16]; 

int x = 512;
int y = 512;
int btn1 = 0;
int btn2 = 0;
int btnJoy = 0;

const int AIA = 3;  // (pwm) pino 9 conectado ao pino A-IA do Módulo
const int AIB = 5;  // (pwm) pino 5 conectado ao pino A-IB do Módulo
const int BIA = 6; // (pwm) pino 10 conectado ao pino B-IA do Módulo
const int BIB = 9;  // (pwm) pino 6 conectado ao pino B-IB do Módulo
byte speed = 255;  // Mude este valor (0-255) para controlar a velocidade dos motores

void setup(){
    Serial.begin(9600);
     
    pinMode(AIA, OUTPUT); // Colocando os pinos como saída
    pinMode(AIB, OUTPUT);
    pinMode(BIA, OUTPUT);
    pinMode(BIB, OUTPUT);
    digitalWrite(AIA, LOW); 
    digitalWrite(AIB, LOW);
    digitalWrite(BIA, LOW); 
    digitalWrite(BIB, LOW);
    // VirtualWire 
    // Initialise the IO and ISR
    // Required for DR3100
    vw_set_ptt_inverted(true); 
    vw_set_rx_pin(RFData);
    // Bits per sec
    vw_setup(2000);     
    
    // Start the receiver PLL running
    vw_rx_start();       
    Serial.println("ola");
} // END void setup

void loop(){
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    // Non-blocking
    if (vw_get_message(buf, &buflen)) 
    {    
      Serial.println("ola"); 
      
        // Message with a good checksum received, dump it. 
        for (int i = 0; i < buflen; i++)
        {            
          // Fill StringReceived Char array with corresponding 
          // chars from buffer.   
          StringReceived[i] = char(buf[i]);
        }
        
        sscanf(StringReceived, "%d,%d,%d,%d,%d",&x, &y,&btn1,&btn2, &btnJoy);
        Serial.println(StringReceived);
    }
    
    if(y>600)
        forward();
    else if(y<450)
        backward();
    else if(x>600)
        right();
    else if(x<450)
        left();
    else
        stop();
}


void backward()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}
 
void forward()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}
 
void left()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}
 
void right()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}
void stop()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
}


