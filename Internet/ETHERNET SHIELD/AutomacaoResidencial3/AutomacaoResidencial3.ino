#include <SPI.h>
#include <Ethernet.h>  //inclui blibioteca Ethernet
#include <ArdOSC.h>  //inclui blibioteca ArdOSC



//Pinos usados no Ethernet Shield D4(apenas para o SD), D10, D11, D12, D13, alimentacao e o conector ICSP
//Pinos usados no LCD Shield A0 (Buttons), D4, D5, D6, D7, D8, D9, D10

byte myMac[]={
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; //define MAC para shield Ethernet
byte myIP[]={
  192,168,0,120}; //define IP da central automação
byte destIP[]={
  192,168,0,111}; //define IP do dispositivo de comando OSC
int serverPort=5000; //define a porta de recepção do comando OSC
int destPort=4000; //define a porta de envio do comando OSC

//Portao garagem
int led1Pin=7; //define a porta do arduino associada ao led 1

//Quarto Abilio
int led3Pin=5; //define a porta do arduino associada ao led 3

//Buzzer
int sound = 4; //Alarm

//Variaveis
boolean alarme = false;
long counting = 10000;  // the last time the output pin was toggled
long counting2 = 10000;  // the last time the output pin was toggled

OSCServer server; //inicializa o servidor OSC (serviço que trata a recepção de mensagem OSC)
OSCClient client; //inicializa o cliente OSC (serviço que trata o envio de mensagem OSC)


void setup(){
  Serial.begin(9600); 
  
  pinMode(sound,OUTPUT); //define a porta digital 9 (ledPin2) do Arduino como saida
    pinMode(led1Pin,OUTPUT); //define a porta digital 9 (ledPin2) do Arduino como saida
  pinMode(led3Pin,OUTPUT); //define a porta digital 9 (ledPin2) do Arduino como saida
  
  //Ethernet.begin(myMac,myIP); //inicializa a interface ethernet
  if (Ethernet.begin(myMac) == 0){//inicializa a interface ethernet
    Serial.print("erro"); 
    Ethernet.begin(myMac, myIP);
  }
  server.begin(serverPort); //inicializa o servidor OSC definindo a porta de RX
  
   server.addCallback("/ard/led1",&func1); //define que a rotina "func1" será executada para o comando OSC "/ard/led1"
  server.addCallback("/ard/led3",&func3); //define que a rotina "func2" será executada para o comando OSC "/ard/led3"
  server.addCallback("/ard/alarm",&func15);
}


void loop(){
  Serial.print("1");  
  if(server.aviableCheck()>0){ //verifica se existe alguma mensagem OSC disponível para leitura
    Serial.print("Chegou");  
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

//Garagem
void func1(OSCMessage *_mes){ //rotina que trata comando OSC "/ard/led1" recebido do ANDROID/IPAD/IPHONE/IPOD
  counting2 = millis();
  Serial.print(counting2-counting); 

  if((counting2-counting) >= 5000){
    Serial.print("Portao Mensagem");    
    digitalWrite(led1Pin,HIGH); //muda estado da porta digital 8 (ledPin1) conforme argumento OSC recebido
    delay(1000);
    digitalWrite(led1Pin,LOW); //muda estado da porta digital 8 (ledPin1) conforme argumento OSC recebido
    counting = millis();
  }
}

//Alarme
void func15(OSCMessage *_mes){ 
  int value=(int)_mes->getArgFloat(0); //armazena em "value" o argumento do comando OSC "/ard/led2"
  if(value){
    Serial.print("ALARME");  
    alarme = true;
    alarm();
  }
  else{
    Serial.print("NOALARME");  
    alarme = false;
  }
}
void func3(OSCMessage *_mes){ //rotina que trata comando OSC "/ard/led2" recebido do ANDROID/IPAD/IPHONE/IPOD
  int value=(int)_mes->getArgFloat(0); //armazena em "value" o argumento do comando OSC "/ard/led3"
  digitalWrite(led3Pin,value); //muda estado da porta digital 9 (ledPin2) conforme argumento OSC recebido
    Serial.print("QUARTO ABILIO"); 
}
