//Cria as Threads
#include "Thread.h"
//Agrupa as Threads
#include "ThreadController.h"

#define LED1 2
#define LED2 3

#define LED1_TIMER 2000
#define LED2_TIMER 1000

void piscaLED1(){
  digitalWrite(LED1, !digitalRead(LED1));
}
void piscaLED2(){
  digitalWrite(LED2, !digitalRead(LED2));
}

ThreadController cpu;

Thread threadDoLED1;
Thread threadDoLED2;

void setup(){
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);

  threadDoLED1.setInterval(LED1_TIMER);
  threadDoLED1.onRun(piscaLED1);
  threadDoLED2.setInterval(LED2_TIMER);
  threadDoLED2.onRun(piscaLED2);
  
  cpu.add(&threadDoLED1);
  cpu.add(&threadDoLED2);
}

void loop(){
  /*Isso
  if(threadDoLED1.shouldRun()){
    threadDoLED1.run();
  }
    if(threadDoLED2.shouldRun()){
    threadDoLED2.run();
  }
  */
  //Ou isso
  //Ele faz o shouldRun para todas as Threads adicionadas
  cpu.run();
  
}
