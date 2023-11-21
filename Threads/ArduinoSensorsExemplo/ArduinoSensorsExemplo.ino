//Cria as Threads
#include "Thread.h"
//Agrupa as Threads
#include "ThreadController.h"

#include "ArduinoSensors.h"
#include "sensorsHMC6352.h"

ThreadController cpu;
ThreadController sensors;
HMC6352 bussola(0x32);
SharpMedium sensorDeDistancia(A0);

Thread controlaRobo;
void robo(){
	if(distancia1>10){
		robo.vaiPraFrente();
	}else{
		if(distancia1<20)
	}
}

void setup(){

  Serial.begin(9600);
  sensors.setInterval(0);
  //bussula.setInterval(50);
  sensors.add(&bussula);
  
  controlaRobo.setInterval(1000);
  controlaRobo.onRun(robo);
  
  cpu.add(&sensors);
  cpu.add($controller); 

}

bool roboParado = true;
void loop(){

  if(roboParado) sensors.enable = false;
  else sensors.enable = true;

  cpu.run();
  bussola.getAngle();
  
}
