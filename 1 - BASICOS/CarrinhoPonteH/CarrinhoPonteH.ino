/*
Exemplo de uso para a ponte H L9110 com arduino
Visite nosso site: www.msseletronica.com
*/
 
const int AIA = 3;  // (pwm) pino 9 conectado ao pino A-IA do Módulo
const int AIB = 5;  // (pwm) pino 5 conectado ao pino A-IB do Módulo
const int BIA = 6; // (pwm) pino 10 conectado ao pino B-IA do Módulo
const int BIB = 9;  // (pwm) pino 6 conectado ao pino B-IB do Módulo
 
byte speed = 255;  // Mude este valor (0-255) para controlar a velocidade dos motores
 
void setup() {
  Serial.begin(9600); //inicia a porta serial  
   
  pinMode(AIA, OUTPUT); // Colocando os pinos como saída
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
}
 
void loop() {//O programa ficará em loop, girando um motor para um lado, depois para o outro e depois troca de motor e repete
      backward();
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
