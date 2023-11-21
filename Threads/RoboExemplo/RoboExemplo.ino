//Cria as Threads
#include "Thread.h"
//Agrupa as Threads
#include "ThreadController.h"

ThreadController cpu;


Thread leituraDeSensores;
int distancia1 = 0;
bool sensorToque = false;
void fazLeituras(){
 	distancia1 = analogRead(A1);
 	sensorToque = digitalRead(9);
}
Thread controlaRobo;
void robo(){
	if(distancia1>10){
		robo.vaiPraFrente();
	}else{
		if(distancia1<20)
	}
}

Thread debugSerial;
void doDebug(){
	Serial.println("Distancia: %d ", distancia1);
	Serial.println("Toque: %s ", distancia1 ? "Pressionado" : "Despressionado");
}

void setup(){
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);

  leituraDeSensores.setInterval(2000);
  leituraDeSensores.onRun(fazLeituras);
  controlaRobo.setInterval(1000);
  controlaRobo.onRun(robo);
  debugSerial.setInterval(3000);
  debugSerial.onRun(doDebug);
  cpu.add(&leituraDeSensores);
  cpu.add(&controlaRobo);
  cpu.add(&debugSerial);
}

void loop(){
  //Ele faz o shouldRun para todas as Threads adicionadas
  cpu.run();
  
}
