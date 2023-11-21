#include <FuzzyRule.h>
#include <FuzzyComposition.h>
#include <Fuzzy.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzyOutput.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzySet.h>
#include <FuzzyRuleAntecedent.h>
 
// Passo 1 -  Instanciando um objeto da biblioteca
Fuzzy* fuzzy = new Fuzzy();
 
 #define echoPin 12 //Pino 13 recebe o pulso do echo  
#define trigPin 11 //Pino 12 envia o pulso para gerar o echo  
 const int AIA = 3;  // (pwm) pino 9 conectado ao pino A-IA do Módulo
const int AIB = 5;  // (pwm) pino 5 conectado ao pino A-IB do Módulo
const int BIA = 6; // (pwm) pino 10 conectado ao pino B-IA do Módulo
const int BIB = 9;  // (pwm) pino 6 conectado ao pino B-IB do Módulo

byte speed = 255;  // Mude este valor (0-255) para controlar a velocidade dos motores

void setup(){
 Serial.begin(9600);


pinMode(echoPin, INPUT); // define o pino 13 como entrada (recebe)  
pinMode(trigPin, OUTPUT); // define o pino 12 como saida (envia)  

pinMode(AIA, OUTPUT); // Colocando os pinos como saída
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);

 // Passo 2 - Criando o FuzzyInput distancia
 FuzzyInput* distance = new FuzzyInput(1);// Como parametro seu ID
 
 // Criando os FuzzySet que compoem o FuzzyInput distancia
 FuzzySet* small = new FuzzySet(0, 10, 20, 40); // Distancia pequena
 distance->addFuzzySet(small); // Adicionando o FuzzySet small em distance
 FuzzySet* safe = new FuzzySet(30, 40, 50, 60); // Distancia segura
 distance->addFuzzySet(safe); // Adicionando o FuzzySet safe em distance
 FuzzySet* big = new FuzzySet(50, 60, 80, 80); // Distancia grande
 distance->addFuzzySet(big); // Adicionando o FuzzySet big em distance
 
 fuzzy->addFuzzyInput(distance); // Adicionando o FuzzyInput no objeto Fuzzy
 
 // Passo 3 - Criando o FuzzyOutput velocidade
 FuzzyOutput* velocity = new FuzzyOutput(1);// Como parametro seu ID
 
 // Criando os FuzzySet que compoem o FuzzyOutput velocidade
 FuzzySet* slow = new FuzzySet(0, 10, 20, 30); // Velocidade lenta
 velocity->addFuzzySet(slow); // Adicionando o FuzzySet slow em velocity
 FuzzySet* average = new FuzzySet(30, 40, 50, 60); // Velocidade normal
 velocity->addFuzzySet(average); // Adicionando o FuzzySet average em velocity
 FuzzySet* fast = new FuzzySet(60, 70, 80, 90); // Velocidade alta
 velocity->addFuzzySet(fast); // Adicionando o FuzzySet fast em velocity
 
 fuzzy->addFuzzyOutput(velocity); // Adicionando o FuzzyOutput no objeto Fuzzy
 
 //Passo 4 - Montando as regras Fuzzy
 // FuzzyRule "SE distancia = pequena ENTAO velocidade = lenta"
 FuzzyRuleAntecedent* ifDistanceSmall = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expresso
 ifDistanceSmall->joinSingle(small); // Adicionando o FuzzySet correspondente ao objeto Antecedente
 FuzzyRuleConsequent* thenVelocitySlow = new FuzzyRuleConsequent(); // Instancinado um Consequente para a expressao
 thenVelocitySlow->addOutput(slow);// Adicionando o FuzzySet correspondente ao objeto Consequente
 // Instanciando um objeto FuzzyRule
 FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifDistanceSmall, thenVelocitySlow); // Passando o Antecedente e o Consequente da expressao
  
 fuzzy->addFuzzyRule(fuzzyRule01); // Adicionando o FuzzyRule ao objeto Fuzzy
  
 // FuzzyRule "SE distancia = segura ENTAO velocidade = normal"
 FuzzyRuleAntecedent* ifDistanceSafe = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expresso
 ifDistanceSafe->joinSingle(safe); // Adicionando o FuzzySet correspondente ao objeto Antecedente
 FuzzyRuleConsequent* thenVelocityAverage = new FuzzyRuleConsequent(); // Instancinado um Consequente para a expressao
 thenVelocityAverage->addOutput(average); // Adicionando o FuzzySet correspondente ao objeto Consequente
 // Instanciando um objeto FuzzyRule
 FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifDistanceSafe, thenVelocityAverage); // Passando o Antecedente e o Consequente da expressao
  
 fuzzy->addFuzzyRule(fuzzyRule02); // Adicionando o FuzzyRule ao objeto Fuzzy
  
 // FuzzyRule "SE distancia = grande ENTAO velocidade = alta"
 FuzzyRuleAntecedent* ifDistanceBig = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expresso
 ifDistanceBig->joinSingle(big); // Adicionando o FuzzySet correspondente ao objeto Antecedente
 FuzzyRuleConsequent* thenVelocityFast = new FuzzyRuleConsequent(); // Instancinado um Consequente para a expressao
 thenVelocityFast->addOutput(fast);// Adicionando o FuzzySet correspondente ao objeto Consequente
 // Instanciando um objeto FuzzyRule
 FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifDistanceBig, thenVelocityFast); // Passando o Antecedente e o Consequente da expressao
  
 fuzzy->addFuzzyRule(fuzzyRule03); // Adicionando o FuzzyRule ao objeto Fuzzy
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
	if(distancia>180){
	  distancia=180;
	}
 int dist = map(distancia, 0,180,0,100);

 Serial.print("INPUT: ");  
 Serial.println(dist);
// Passo 5 - Informar o valor das entradas, passando seu ID e valor
fuzzy->setInput(1, dist); 
 // Passo 6 - Executar a fuzzyficação
 fuzzy->fuzzify(); 
 // Passo 7 - Executar a desfuzzyficação para cada saída, passando seu ID
 int output = fuzzy->defuzzify(1);
  Serial.print("output: ");  
Serial.println(output);  

 speed = map(output, 0, 100, 0, 255);
 if(speed<120 && speed>0){
  speed=120;
  forward();
}else{
backward();
}

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



