#define echoPin 12 //Pino 13 recebe o pulso do echo  
#define trigPin 11 //Pino 12 envia o pulso para gerar o echo    

#include <TimerOne.h>   // inclui biblioteca Timer1
 
#define triacApin 3 // Define que o Dimmer será comandado pelo pino 4
int frequencia = 60;
int stateTriacA = 0;
int power = 0;  //inicializa variavel que controla potencia na lampada com 0 (lampada apagada)
volatile long  distancia=0;
void setup()  
{  
   Serial.begin(9600); //inicia a porta serial  
   pinMode(echoPin, INPUT); // define o pino 13 como entrada (recebe)  
   pinMode(trigPin, OUTPUT); // define o pino 12 como saida (envia) 

pinMode(triacApin, OUTPUT);
digitalWrite(triacApin, LOW); 
Timer1.initialize(); // Initialize TimerOne library for the freq we need
// Attach the interrupt 0 to pin 2 for the detection of zero crossing (Zero Cross Detection)
attachInterrupt(0, zero_cross_detect, CHANGE); // Atta
}  
  
void loop()  
{  
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
   int distanciaAtual = duration /29 / 2 ;  
    if(distanciaAtual>40){
    }
    else{
      distancia = distanciaAtual;
    }
Serial.print("Distancia em CM: ");  
Serial.println(distancia);  
delay(1000); //espera 1 segundo para fazer a leitura novamente  
}  

 
void zero_cross_detect()
{
if(distancia >=0 &&distancia<=30){
long dimtime = int(map(distancia,0,30,5600,1000));  // calcula o tempo de delay para o disparo do TRIAC 7950,100
Timer1.attachInterrupt(gateTRIAC, dimtime);  //associa a funcao gateTRIAC com Interrupcao do TIMER1
Timer1.start();  // inicia contagem TIMER1
}else{
digitalWrite(triacApin, LOW);   // mantem gate do TRIAC desativado.
Timer1.stop();
}
}
 
void gateTRIAC ()
{  // trata interrupcao do TIMER1 gerando pulso no gate do TRIAC
digitalWrite(triacApin, HIGH);  // dispara o Triac
delayMicroseconds(5);  // aguarda 5 microsegundos para garantir disparo do TRIAC
digitalWrite(triacApin, LOW);   // desabibilta gate do TRIAC
Timer1.stop();
}
