//simple Tx on pin D12
//Written By : Mohannad Rawashdeh
// 3:00pm , 13/6/2013
//http://www.genotronex.com/
//..................................
#include <VirtualWire.h>
char *controller;

#define echoPin 8 //Pino 13 recebe o pulso do echo  
#define trigPin 9 //Pino 12 envia o pulso para gerar o echo  
long olddistancia;

void setup() {
     Serial.begin(9600); //inicia a porta serial  
     
     pinMode(echoPin, INPUT); // define o pino 13 como entrada (recebe)  
     pinMode(trigPin, OUTPUT); // define o pino 12 como saida (envia)  
    pinMode(13,OUTPUT);
    vw_set_ptt_inverted(true); //
    vw_set_tx_pin(12);
    vw_setup(4000);// speed of data transfer Kbps
}

void loop(){
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
    delay(200); //espera 1 segundo para fazer a leitura novamente   
    digitalWrite(13,0);
    if ((olddistancia-distancia)>20){
        controller="1"  ;
        vw_send((uint8_t *)controller, strlen(controller));
        vw_wait_tx(); // Wait until the whole message is gone
        digitalWrite(13,1);
        delay(2000);
    }/*else{
      
    controller="0"  ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13,0);
    delay(2000);
    }
    */
    olddistancia = distancia;
    
           controller="1"  ;
        vw_send((uint8_t *)controller, strlen(controller));
        vw_wait_tx(); // Wait until the whole message is gone
        digitalWrite(13,1);
        delay(2000);
        
         controller="0"  ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13,0);
    delay(2000);
}

