//RoboClaw Packet Serial Mode.
//Switch settings: SW3=ON, SW4=ON, SW5=ON
#include "BMSerial.h"
#include "RoboClaw.h"
#define address 0x80
#define Kp 0x00010000 
#define Ki 0x00008000 
#define Kd 0x00004000 
#define qpps 44000
BMSerial terminal(0,1); 
RoboClaw roboclaw(5,6,10000);
void setup() { 
  terminal.begin(38400); 
  roboclaw.begin(38400);
  roboclaw.SetM1Constants(address,Kd,Kp,Ki,qpps); 
  roboclaw.SetM2Constants(address,Kd,Kp,Ki,qpps);
} 
void displayspeed(void)
{ 
  uint8_t status; bool valid;
  uint32_t enc1= roboclaw.ReadEncM1(address, &status, &valid); 
  if(valid){
    terminal.print("Encoder1:"); 
    terminal.print(enc1,DEC); 
    terminal.print(" "); 
    terminal.print(status,HEX);
    terminal.print(" ");
  } 
  uint32_t enc2 = roboclaw.ReadEncM2(address, &status, &valid); 
  if(valid){
    terminal.print("Encoder2:"); 
    terminal.print(enc2,DEC); 
    terminal.print(" "); 
    terminal.print(status,HEX);
    terminal.print(" ");
  } 
  uint32_t speed1 = roboclaw.ReadSpeedM1(address, &status, &valid); 
  if(valid){
    terminal.print("Speed1:");
    terminal.print(speed1,DEC);
    terminal.print(" "); 
  } 
  uint32_t speed2 = roboclaw.ReadSpeedM2(address, &status, &valid); 
  if(valid){
    terminal.print("Speed2:");
    terminal.print(speed2,DEC); 
    terminal.print(" ");
  } 
  terminal.println();
} 
void loop() { 
  roboclaw.SpeedAccelDistanceM1(address,12000,12000,48000); 
  uint8_t depth1,depth2;
  do{
    displayspeed(); 
    roboclaw.ReadBuffers(address,depth1,depth2);
  }while(depth1); 
  roboclaw.SpeedAccelDistanceM1(address,12000,-12000,48000);
  do{
    displayspeed(); 
    roboclaw.ReadBuffers(address,depth1,depth2);
  }while(depth1); 
}