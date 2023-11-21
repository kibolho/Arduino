//RoboClaw Packet Serial Test Commands 0 to 13.
//Switch settings: SW3=ON and SW5=ON.
#include "BMSerial.h"
#include "RoboClaw.h"
#define address 0x80
RoboClaw roboclaw(5,6,10000);
void setup() {
	roboclaw.begin(19200);
} 
void loop() { 
	roboclaw.ForwardM1(address,64); //Cmd 0 roboclaw.BackwardM2(address,64); //Cmd 5 delay(2000); roboclaw.BackwardM1(address,64); //Cmd 1 roboclaw.ForwardM2(address,64); //Cmd 6 delay(2000); roboclaw.ForwardBackwardM1(address,96); roboclaw.ForwardBackwardM2(address,32); delay(2000); roboclaw.ForwardBackwardM1(address,32); roboclaw.ForwardBackwardM2(address,96); delay(2000);
  //stop motors
  roboclaw.ForwardBackwardM1(address,0);
  roboclaw.ForwardBackwardM2(address,0);
  delay(10000);
  roboclaw.ForwardMixed(address, 64);
  delay(2000);
  roboclaw.BackwardMixed(address, 64);
  delay(2000);
  roboclaw.TurnRightMixed(address, 64);
  delay(2000);
  roboclaw.TurnLeftMixed(address, 64);
  delay(2000);
  roboclaw.ForwardBackwardMixed(address,
  delay(2000);
  roboclaw.ForwardBackwardMixed(address,
  delay(2000);
  roboclaw.LeftRightMixed(address, 32);
  delay(2000);
  roboclaw.LeftRightMixed(address, 96);
  delay(2000);
  //stop motors
  roboclaw.ForwardMixed(address, 0);
  delay(10000);
} 