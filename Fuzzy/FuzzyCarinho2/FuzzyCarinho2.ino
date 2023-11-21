/*
Exemplo de uso para a ponte H L9110 com arduino
Visite nosso site: www.msseletronica.com
*/

 #define echoPin 12 //Pino 13 recebe o pulso do echo  
#define trigPin 11 //Pino 12 envia o pulso para gerar o echo  
 
const int AIA = 3;  // (pwm) pino 9 conectado ao pino A-IA do Módulo
const int AIB = 5;  // (pwm) pino 5 conectado ao pino A-IB do Módulo
const int BIA = 6; // (pwm) pino 10 conectado ao pino B-IA do Módulo
const int BIB = 9;  // (pwm) pino 6 conectado ao pino B-IB do Módulo
 
byte speed = 130;  // Mude este valor (0-255) para controlar a velocidade dos motores
 
void setup() {
  Serial.begin(9600); //inicia a porta serial  
   
   
pinMode(echoPin, INPUT); // define o pino 13 como entrada (recebe)  
pinMode(trigPin, OUTPUT); // define o pino 12 como saida (envia)  

  pinMode(AIA, OUTPUT); // Colocando os pinos como saída
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
}
 
void loop() {//O programa ficará em loop, girando um motor para um lado, depois para o outro e depois troca de motor e repete
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

    if (distancia > 10){
      speed = map(distancia, 10, 200, 120, 255);   
      Serial.print("FRENTE: ");  
      Serial.println(speed);
      backward();
  
    } else if (distancia < 10){
      speed = map(distancia, 10, 0, 120, 255); 
      Serial.print("Tras: ");  
      Serial.println(speed);  
      forward();
       
    }else{
      stop();
    }
    delay(1000);
}

void backward()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}
 
void forward()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}
 
void left()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}
 
void right()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}
void stop()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
}
