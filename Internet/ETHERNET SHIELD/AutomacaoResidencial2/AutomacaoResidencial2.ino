#include <SPI.h>
#include <Ethernet.h>  //inclui blibioteca Ethernet
#include <ArdOSC.h>  //inclui blibioteca ArdOSC
#include <IRremote.h>



/*
irSend sketch
 this code needs an IR LED connected to pin 3
 */

// Power ON/OFF
unsigned int S_pwr[68]={
  4600,4350,700,1550,650,1550,650,1600,650,450,650,450,650,450,650,450,700,400,700,1550,650,1550,650,1600,650,450,650,450,650,450,700,450,650,450,650,450,650,1550,700,450,650,450,650,450,650,450,650,450,700,400,650,1600,650,450,650,1550,650,1600,650,1550,650,1550,700,1550,650,1550,650};

// channel up
unsigned int S_pup[68]={
  4600,4350,700,1500,700,1500,700,1550,700,450,650,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,450,650,450,700,400,700,400,700,400,700,400,700,1550,700,400,700,400,700,1550,650,450,700,400,700,400,700,1550,650,450,650,1600,650,1550,650,450,700,1500,700,1500,700,1550,650};

// channel down
unsigned int S_pdown[68]={
  4650,4300,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,700,400,700,400,700,400,700,450,650,450,650,1550,700,400,700,450,650,400,700,1550,700,1500,700,1550,700,1500,700,400,700,1550,650,1550,700,1500,700};

// volume up
unsigned int S_vup[68]={
  4600,4350,650,1550,700,1500,700,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,450,700,400,700,400,700,400,700,450,650,450,650,450,650,1550,700,1500,700,1550,700,1500,700,1550,650};

// volume down
unsigned int S_vdown[68]={
  4600,4350,700,1550,650,1550,700,1500,700,450,650,450,700,400,700,400,700,400,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,450,650,1550,700,400,700,400,700,450,700,400,700,400,700,400,700,1550,700,400,700,1500,700,1500,700,1550,700,1500,700};

IRsend irsend;

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

//Porta 
int sw1port=6; //define a porta do arduino associada a entrada do sinal portao fechada/aberta

//Infravermelho
int IRledPin=9;

// Quarto joao
int led2Pin=8; //define a porta do arduino associada ao led 2 

//Portao garagem
int led1Pin=7; //define a porta do arduino associada ao led 1

//Quarto Abilio
int led3Pin=5; //define a porta do arduino associada ao led 3

//Buzzer
int sound = 4; //Alarm


boolean alarme = false;
long oldDistancia = 0;

//Ultrasom 
int echoPin = 3; //Pino 3 recebe o pulso do echo  
int trigPin = 2; //Pino 2 envia o pulso para gerar o echo  

long counting = 10000;  // the last time the output pin was toggled
long counting2 = 10000;  // the last time the output pin was toggled

OSCServer server; //inicializa o servidor OSC (serviço que trata a recepção de mensagem OSC)
OSCClient client; //inicializa o cliente OSC (serviço que trata o envio de mensagem OSC)

int check = 1;

void setup(){
  Serial.begin(9600); 
  
  pinMode(led1Pin,OUTPUT); //define a porta digital 8 (ledPin1) do Arduino como saida
  pinMode(led2Pin,OUTPUT); //define a porta digital 9 (ledPin2) do Arduino como saida
  pinMode(led3Pin,OUTPUT); //define a porta digital 9 (ledPin2) do Arduino como saida
  pinMode(sw1port,INPUT); //define a porta digital 9 (ledPin2) do Arduino como saida
  pinMode(IRledPin, OUTPUT); //IR

  pinMode(echoPin, INPUT); // define o pino 13 como entrada (recebe)  
  pinMode(trigPin, OUTPUT); // define o pino 12 como saida (envia) 
  
  //Ethernet.begin(myMac,myIP); //inicializa a interface ethernet
  if (Ethernet.begin(myMac) == 0){//inicializa a interface ethernet
    Serial.print("erro"); 
    Ethernet.begin(myMac, myIP);
  }
  server.begin(serverPort); //inicializa o servidor OSC definindo a porta de RX
  server.addCallback("/ard/led1",&func1); //define que a rotina "func1" será executada para o comando OSC "/ard/led1"
  server.addCallback("/ard/led2",&func2); //define que a rotina "func2" será executada para o comando OSC "/ard/led2"
  server.addCallback("/ard/led3",&func3); //define que a rotina "func2" será executada para o comando OSC "/ard/led3"

  server.addCallback("/ard/power",&func4); //define que a rotina "func2" será executada para o comando OSC "/ard/led3"
  server.addCallback("/ard/volup",&func5); //define que a rotina "func2" será executada para o comando OSC "/ard/led3"
  server.addCallback("/ard/voldown",&func6); //define que a rotina "func2" será executada para o comando OSC "/ard/led3"
  server.addCallback("/ard/chanup",&func7); //define que a rotina "func2" será executada para o comando OSC "/ard/led3"
  server.addCallback("/ard/chandown",&func8); //define que a rotina "func2" será executada para o comando OSC "/ard/led3"

  server.addCallback("/ard/powerLG",&func9);
  server.addCallback("/ard/powerNET",&func10);
  server.addCallback("/ard/chanUPNET",&func11);
  server.addCallback("/ard/chanDOWNNET",&func12);
  server.addCallback("/ard/volUPNET",&func13);
  server.addCallback("/ard/volDOWNNET",&func14);

  server.addCallback("/ard/alarm",&func15);
}


void loop(){
  //Serial.print("Chegou");  
  if(server.aviableCheck()>0){ //verifica se existe alguma mensagem OSC disponível para leitura
    Serial.print("Chegou");  
  }

  if(digitalRead(sw1port)==LOW){ //verifica se a porta esta aberta
    if(check==2){
      OSCMessage txMes; //cria uma nova menssagem OSC
      txMes.setAddress(destIP,destPort); //define o endereço e porta do destino da mensagem OSC
      txMes.beginMessage("/ard/port2"); //define comando OSC
      txMes.addArgFloat(0); //define no estado do led 1 que será enviado no argumento OSC para ANDROID/IPAD/IPHONE/IPOD
      client.send(&txMes); //envia mensagem OSC para atualizar novo estado do led 1 no ANDROID/IPAD/IPHONE/IPOD
      delay(300); //delay de 300ms

      Serial.print("Porta Fechada");

      OSCMessage txMes1; //cria uma nova menssagem OSC
      txMes1.setAddress(destIP,destPort); //define o endereço e porta do destino da mensagem OSC
      txMes1.beginMessage("/ard/port1"); //define comando OSC
      txMes1.addArgFloat(1); //define no estado do led 1 que será enviado no argumento OSC para ANDROID/IPAD/IPHONE/IPOD
      client.send(&txMes1); //envia mensagem OSC para atualizar novo estado do led 1 no ANDROID/IPAD/IPHONE/IPOD
      delay(300); //delay de 300ms
      check = 1;
    }
  }
  if(digitalRead(sw1port)==HIGH){ //verifica se a porta esta aberta
    if(check == 1){
      if(alarme){
        alarm();
      }
      OSCMessage txMes; //cria uma nova menssagem OSC
      txMes.setAddress(destIP,destPort); //define o endereço e porta do destino da mensagem OSC
      txMes.beginMessage("/ard/port1"); //define comando OSC
      txMes.addArgFloat(0); //define no estado do led 1 que será enviado no argumento OSC para ANDROID/IPAD/IPHONE/IPOD
      client.send(&txMes); //envia mensagem OSC para atualizar novo estado do led 1 no ANDROID/IPAD/IPHONE/IPOD
      delay(300); //delay de 300ms

      Serial.print("Porta Aberta");

      OSCMessage txMes1; //cria uma nova menssagem OSC
      txMes1.setAddress(destIP,destPort); //define o endereço e porta do destino da mensagem OSC
      txMes1.beginMessage("/ard/port2"); //define comando OSC
      txMes1.addArgFloat(1); //define no estado do led 1 que será enviado no argumento OSC para ANDROID/IPAD/IPHONE/IPOD
      client.send(&txMes1); //envia mensagem OSC para atualizar novo estado do led 1 no ANDROID/IPAD/IPHONE/IPOD
      delay(300); //delay de 300ms
      check = 2;
    }
  }
  //
  // ultrassom
  //
  if(alarme){
    Serial.print("AlarmeAtivado");  
    //seta o pino 12 com um pulso baixo "LOW" ou desligado ou ainda 0  
    digitalWrite(trigPin, LOW);  
    // delay de 2 microssegundos  
    delayMicroseconds(2);  
    //seta o pino 12 com pulso alto "HIGH" ou ligado ou ainda 1  
    digitalWrite(trigPin, HIGH);  
    //delay de 10 microssegundos  
    delayMicroseconds(10);  
    //seta o pino 12 com pulso baixo novamente  
    digitalWrite(trigPin, LOW);  
    //pulseInt lê o tempo entre a chamada e o pino entrar em high  
    long duration = pulseIn(echoPin,HIGH);  
    //Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado  
    //porque é o tempo de ida e volta do ultrassom  
    long distancia = duration /29 / 2 ; 
    Serial.print("Distancia em CM: ");  
    Serial.println(distancia);
    if((oldDistancia-distancia)>20){
      alarm();
    }
    oldDistancia = distancia;
    delay(500); //espera 1 segundo para fazer a leitura novamente  
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
void func1(OSCMessage *_mes){ //rotina que trata comando OSC "/ard/led1" recebido do ANDROID/IPAD/IPHONE/IPOD
  counting2 = millis();
  Serial.print(counting2-counting); 

  if((counting2-counting) >= 5000){
    Serial.print("Portao Mensagem");    
    digitalWrite(led1Pin,HIGH); //muda estado da porta digital 8 (ledPin1) conforme argumento OSC recebido
    delay(300);
    digitalWrite(led1Pin,LOW); //muda estado da porta digital 8 (ledPin1) conforme argumento OSC recebido
    counting = millis();
  }
}

void func2(OSCMessage *_mes){ //rotina que trata comando OSC "/ard/led2" recebido do ANDROID/IPAD/IPHONE/IPOD
  int value=(int)_mes->getArgFloat(0); //armazena em "value" o argumento do comando OSC "/ard/led2"
  digitalWrite(led2Pin,value); //muda estado da porta digital 9 (ledPin2) conforme argumento OSC recebido
  Serial.print("Quarto JOAO");  
}

void func3(OSCMessage *_mes){ //rotina que trata comando OSC "/ard/led2" recebido do ANDROID/IPAD/IPHONE/IPOD
  int value=(int)_mes->getArgFloat(0); //armazena em "value" o argumento do comando OSC "/ard/led3"
  digitalWrite(led3Pin,value); //muda estado da porta digital 9 (ledPin2) conforme argumento OSC recebido
    Serial.print("QUARTO ABILIO"); 
}

//
// TV Samsung
//

void func4(OSCMessage *_mes){ //rotina que trata comando OSC "/ard/led2" recebido do ANDROID/IPAD/IPHONE/IPOD
  Serial.print("Power");   
  irsend.sendRaw(S_pwr,68,38);
}
void func5(OSCMessage *_mes){ //rotina que trata comando OSC "/ard/led2" recebido do ANDROID/IPAD/IPHONE/IPOD
  irsend.sendRaw(S_vup,68,38);
}
void func6(OSCMessage *_mes){ //rotina que trata comando OSC "/ard/led2" recebido do ANDROID/IPAD/IPHONE/IPOD
  irsend.sendRaw(S_vdown,68,38);
}
void func7(OSCMessage *_mes){ //rotina que trata comando OSC "/ard/led2" recebido do ANDROID/IPAD/IPHONE/IPOD
  irsend.sendRaw(S_pup,68,38);
}
void func8(OSCMessage *_mes){ //rotina que trata comando OSC "/ard/led2" recebido do ANDROID/IPAD/IPHONE/IPOD
  irsend.sendRaw(S_pdown,68,38);
}

//
// TV LG
//  
void func9(OSCMessage *_mes){ //rotina que trata comando OSC "/ard/led2" recebido do ANDROID/IPAD/IPHONE/IPOD
  irsend.sendNEC(0x20df10ef, 32);
}


//
// Modem NET
//  

// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait

  cli();  // this turns off any background interrupts

  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
    digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
    delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
    digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
    delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working

    // so 26 microseconds altogether
    microsecs -= 26;
  }

  sei();  // this turns them back on
}


void func10(OSCMessage *_mes){ //rotina que trata comando OSC "/ard/led2" recebido do ANDROID/IPAD/IPHONE/IPOD
  // ON, OFF
  pulseIR(8840);
  delayMicroseconds(4380);
  pulseIR(540);
  delayMicroseconds(1640);
  pulseIR(540);
  delayMicroseconds(1640);
  pulseIR(540);
  delayMicroseconds(1660);
  pulseIR(520);
  delayMicroseconds(560);
  pulseIR(520);
  delayMicroseconds(580);
  pulseIR(520);
  delayMicroseconds(560);
  pulseIR(520);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(520);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(520);
  delayMicroseconds(1660);
  pulseIR(520);
  delayMicroseconds(1680);
  pulseIR(520);
  delayMicroseconds(1660);
  pulseIR(520);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(520);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(520);
  delayMicroseconds(560);
  pulseIR(540);
  delayMicroseconds(560);
  pulseIR(520);
  delayMicroseconds(1660);
  pulseIR(520);
  delayMicroseconds(580);
  pulseIR(520);
  delayMicroseconds(560);
  pulseIR(520);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(520);
  delayMicroseconds(560);
  pulseIR(520);
  delayMicroseconds(1680);
  pulseIR(520);
  delayMicroseconds(1660);
  pulseIR(520);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(520);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(520);
  delayMicroseconds(38980);
  pulseIR(8740);
  delayMicroseconds(2220);
  pulseIR(520);
}

//
//Channel UP
//
void func11(OSCMessage *_mes){ //rotina que trata comando OSC "/ard/led2" recebido do ANDROID/IPAD/IPHONE/IPOD
  // CHANNEL UP
  pulseIR(8860);
  delayMicroseconds(4360);
  pulseIR(560);
  delayMicroseconds(1640);
  pulseIR(540);
  delayMicroseconds(1640);
  pulseIR(540);
  delayMicroseconds(1660);
  pulseIR(520);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(1720);
  pulseIR(460);
  delayMicroseconds(620);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(620);
  pulseIR(480);
  delayMicroseconds(1700);
  pulseIR(480);
  delayMicroseconds(1720);
  pulseIR(460);
  delayMicroseconds(1720);
  pulseIR(480);
  delayMicroseconds(1720);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(1760);
  pulseIR(440);
  delayMicroseconds(1740);
  pulseIR(440);
  delayMicroseconds(1740);
  pulseIR(440);
  delayMicroseconds(39060);
  pulseIR(8740);
  delayMicroseconds(2200);
  pulseIR(560);
}


//
//Channel DOWN
//
void func12(OSCMessage *_mes){ 
  pulseIR(8820);
  delayMicroseconds(4400);
  pulseIR(520);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(480);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(38980);
  pulseIR(8740);
  delayMicroseconds(2240);
  pulseIR(500);
  delayMicroseconds(29384);
  pulseIR(8760);
  delayMicroseconds(2220);
  pulseIR(500);
}


//
//Volume UP
//

void func13(OSCMessage *_mes){ 
  pulseIR(8840);
  delayMicroseconds(4360);
  pulseIR(560);
  delayMicroseconds(1640);
  pulseIR(540);
  delayMicroseconds(1660);
  pulseIR(520);
  delayMicroseconds(1660);
  pulseIR(520);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(600);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(480);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(480);
  delayMicroseconds(39000);
  pulseIR(8740);
  delayMicroseconds(2220);
  pulseIR(500);
}

//
//VOLUME DOWN
//
void func14(OSCMessage *_mes){ 
  pulseIR(8820);
  delayMicroseconds(4380);
  pulseIR(540);
  delayMicroseconds(1660);
  pulseIR(520);
  delayMicroseconds(1660);
  pulseIR(520);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(520);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(500);
  delayMicroseconds(580);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(520);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(1680);
  pulseIR(500);
  delayMicroseconds(1700);
  pulseIR(480);
  delayMicroseconds(620);
  pulseIR(460);
  delayMicroseconds(1720);
  pulseIR(480);
  delayMicroseconds(600);
  pulseIR(480);
  delayMicroseconds(620);
  pulseIR(460);
  delayMicroseconds(1740);
  pulseIR(460);
  delayMicroseconds(1720);
  pulseIR(460);
  delayMicroseconds(1740);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(460);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(460);
  delayMicroseconds(1740);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(660);
  pulseIR(440);
  delayMicroseconds(640);
  pulseIR(440);
  delayMicroseconds(1760);
  pulseIR(420);
  delayMicroseconds(1760);
  pulseIR(420);
  delayMicroseconds(1780);
  pulseIR(420);
  delayMicroseconds(1780);
  pulseIR(400);
}

