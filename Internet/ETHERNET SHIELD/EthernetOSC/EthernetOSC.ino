#include <SPI.h>
#include <Ethernet.h>  //inclui blibioteca Ethernet
#include <ArdOSC.h>  //inclui blibioteca ArdOSC


byte myMac[]={0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; //define MAC para shield Ethernet
byte myIP[]={192,168,0,120}; //define IP da central automação
byte destIP[]={127,0,0,1}; //define IP do dispositivo de comando OSC
int serverPort=5000; //define a porta de recepção do comando OSC
int destPort=4000; //define a porta de envio do comando OSC
int led1Pin=8; //define a porta do arduino associada ao led 1 (vermelho)
int led2Pin=13; //define a porta do arduino associada ao led 2 (verde)
int sw1Pin=6; //define a porta do arduino associada ao botão 1 (esquerdo)
int sw2Pin=7; //define a porta do arduino associada ao botão 2 (direito)
OSCServer server; //inicializa o servidor OSC (serviço que trata a recepção de mensagem OSC)
OSCClient client; //inicializa o cliente OSC (serviço que trata o envio de mensagem OSC)
void setup(){
    Serial.begin(9600); 
   Serial.print("Hello World"); 
  //Ethernet.begin(myMac,myIP); //inicializa a interface ethernet
  if (Ethernet.begin(myMac) == 0){//inicializa a interface ethernet
       Serial.print("erro"); 
       Ethernet.begin(myMac, myIP);
  }
  server.begin(serverPort); //inicializa o servidor OSC definindo a porta de RX
  server.addCallback("/ard/led1",&func1); //define que a rotina "func1" será executada para o comando OSC "/ard/led1"
  server.addCallback("/ard/led2",&func2); //define que a rotina "func2" será executada para o comando OSC "/ard/led2"
  pinMode(led1Pin,OUTPUT); //define a porta digital 8 (ledPin1) do Arduino como saida
  pinMode(led2Pin,OUTPUT); //define a porta digital 9 (ledPin2) do Arduino como saida
  digitalWrite(sw1Pin,HIGH); //ativa PULL-UP interno do ATMEGA na porta digital 6(sw1)
  digitalWrite(sw2Pin,HIGH); //ativa PULL-UP interno do ATMEGA na porta digital 7(sw2)
}
void loop(){
     
  if(server.aviableCheck()>0){ //verifica se existe alguma mensagem OSC disponível para leitura
    Serial.print("Chegou");  
  }
    
  if(digitalRead(sw1Pin)==LOW){ //verifica se o botao sw1 foi pressionado
    int state=digitalRead(sw1Pin); //armazena em "state" o estado atual do led 1
    OSCMessage txMes; //cria uma nova menssagem OSC
    txMes.setAddress(destIP,destPort); //define o endereço e porta do destino da mensagem OSC
    txMes.beginMessage("/ard/led1"); //define comando OSC
    txMes.addArgFloat(!state); //define no estado do led 1 que será enviado no argumento OSC para ANDROID/IPAD/IPHONE/IPOD
    client.send(&txMes); //envia mensagem OSC para atualizar novo estado do led 1 no ANDROID/IPAD/IPHONE/IPOD
    digitalWrite(led1Pin,!state); //modifica estado da porta digital 8 (ledPin1)
    delay(300); //delay de 300ms
  }
  if(digitalRead(sw2Pin)==LOW){ //verifica se o botao sw2 foi pressionado
    int state=digitalRead(sw2Pin); //armazena em "state" o estado atual do led 2
    OSCMessage txMes; //cria uma nova menssagem OSC
    txMes.setAddress(destIP,destPort); //define o endereço e porta do destino da mensagem OSC
    txMes.beginMessage("/ard/led2"); //define comando OSC
    txMes.addArgFloat(!state); //define no estado do led 2 que será enviado no argumento OSC para ANDROID/IPAD/IPHONE/IPOD
    client.send(&txMes); //envia mensagem OSC para atualizar novo estado do led 2 no ANDROID/IPAD/IPHONE/IPOD
    digitalWrite(led2Pin,!state); //modifica estado da porta digital 9 (ledPin2)
    delay(300); //delay de 300ms
  }
}

void func1(OSCMessage *_mes){ //rotina que trata comando OSC "/ard/led1" recebido do ANDROID/IPAD/IPHONE/IPOD
  int value=(int)_mes->getArgFloat(0); //armazena em "value" o argumento do comando OSC "/ard/led1"
  digitalWrite(led1Pin,HIGH); //muda estado da porta digital 8 (ledPin1) conforme argumento OSC recebido
}
void func2(OSCMessage *_mes){ //rotina que trata comando OSC "/ard/led2" recebido do ANDROID/IPAD/IPHONE/IPOD
  int value=(int)_mes->getArgFloat(0); //armazena em "value" o argumento do comando OSC "/ard/led2"
  digitalWrite(led2Pin,value); //muda estado da porta digital 9 (ledPin2) conforme argumento OSC recebido
}
  




