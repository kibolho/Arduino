/*
Programa: DimmerPotenciometro
Acionamento de um dimmer com Triac e potenciômetro
*/
int triac = 3; // Triac: pino D3
int pot = A3;  // Potenciômetro: pino A4
int zc = 2;    // Detetor de zero: pino D2

// Tempo entre a detecção de zero e o acionamento do triac
volatile long time=125;
long tempo=0;
void setup()
{
  // Inicializa os pinos como entrada ou saída
  pinMode(triac, OUTPUT);
  pinMode(pot, INPUT);
  pinMode(zc, INPUT);
  Serial.begin(9600);
  // Associa a borda de descida do detetor de zero com
  //   a função dimmer(), que aciona o triac
  attachInterrupt(0, dimmer, CHANGE);
}

void loop()
{
  // Lê o valor do potenciômetro (de 0 a 1023) e converte
  //   para o delay de acionamento do triac (de 1 a 7331us).
 // t = analogRead(pot) * 7.1652 + 1;
 time = map(analogRead(pot),0,1023,30,80);
 /*if(millis()-tempo>2000){
   if(time<5000)
     time=time+500;
    else
     time=1000;
    tempo=millis();
 }
 */
  /*
  // Atualiza a variável "time", desabilitando as interrupções
  //   para que não haja conflito no acesso.
  noInterrupts();
  time = t;
  interrupts();
  */
}
/*
void dimmer()
{
  // Espera até o momento correto (variável "time") e aciona o triac
  delayMicroseconds(time);
  digitalWrite(triac, HIGH);
  
  // Gera a borda de descida do pulso do triac com largura de 200us
  delayMicroseconds(200);
  digitalWrite(triac, LOW);
}
*/
void dimmer(){
  if(time<110){
    delayMicroseconds(time*65); // delay the dim time 
    digitalWrite(triac, HIGH); // fire the Triac 
    delayMicroseconds(8.33); // pause briefly to ensure the triac turned on 
    digitalWrite(triac, LOW);

  } 
  else{ 
    digitalWrite(triac, LOW); // turn off the Triac gate (triac will not turn off until next zero cross) 
  } 
}
