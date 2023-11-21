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
//Buzzer
int sound = 9; //Alarm

void setup(){
	Serial.begin(9600);


	pinMode(echoPin, INPUT); // define o pino 13 como entrada (recebe)  
	pinMode(trigPin, OUTPUT); // define o pino 12 como saida (envia)  
	pinMode(sound,OUTPUT); //define a porta digital 9 (ledPin2) do Arduino como saida

	// Passo 2 - Criando o FuzzyInput distancia
	FuzzyInput* distance = new FuzzyInput(1);// Como parametro seu ID

	// Criando os FuzzySet que compoem o FuzzyInput distancia
	FuzzySet* small = new FuzzySet(0, 5, 5, 10); // Distancia pequena
	distance->addFuzzySet(small); // Adicionando o FuzzySet small em distance
	FuzzySet* safe = new FuzzySet(5, 50, 50, 60); // Distancia segura
	distance->addFuzzySet(safe); // Adicionando o FuzzySet safe em distance
	FuzzySet* big = new FuzzySet(50, 70, 70, 100); // Distancia grande
	distance->addFuzzySet(big); // Adicionando o FuzzySet big em distance

	fuzzy->addFuzzyInput(distance); // Adicionando o FuzzyInput no objeto Fuzzy

	// Passo 3 - Criando o FuzzyOutput velocidade
	FuzzyOutput* velocity = new FuzzyOutput(1);// Como parametro seu ID

	// Criando os FuzzySet que compoem o FuzzyOutput velocidade
	FuzzySet* slow = new FuzzySet(0, 30, 30, 40); // Velocidade lenta
	velocity->addFuzzySet(slow); // Adicionando o FuzzySet slow em velocity
	FuzzySet* average = new FuzzySet(30, 50, 50, 70); // Velocidade normal
	velocity->addFuzzySet(average); // Adicionando o FuzzySet average em velocity
	FuzzySet* fast = new FuzzySet(60, 80, 80, 100); // Velocidade alta
	velocity->addFuzzySet(fast); // Adicionando o FuzzySet fast em velocity

	fuzzy->addFuzzyOutput(velocity); // Adicionando o FuzzyOutput no objeto Fuzzy

	//Passo 4 - Montando as regras Fuzzy
	// FuzzyRule "SE distancia = pequena ENTAO velocidade = alta"
	FuzzyRuleAntecedent* ifDistanceSmall = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expresso
	ifDistanceSmall->joinSingle(small); // Adicionando o FuzzySet correspondente ao objeto Antecedente
	FuzzyRuleConsequent* thenVelocityFast = new FuzzyRuleConsequent(); // Instancinado um Consequente para a expressao
	thenVelocityFast->addOutput(fast);// Adicionando o FuzzySet correspondente ao objeto Consequente
	// Instanciando um objeto FuzzyRule
	FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifDistanceSmall, thenVelocityFast); // Passando o Antecedente e o Consequente da expressao

	fuzzy->addFuzzyRule(fuzzyRule01); // Adicionando o FuzzyRule ao objeto Fuzzy

	// FuzzyRule "SE distancia = segura ENTAO velocidade = normal"
	FuzzyRuleAntecedent* ifDistanceSafe = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expresso
	ifDistanceSafe->joinSingle(safe); // Adicionando o FuzzySet correspondente ao objeto Antecedente
	FuzzyRuleConsequent* thenVelocityAverage = new FuzzyRuleConsequent(); // Instancinado um Consequente para a expressao
	thenVelocityAverage->addOutput(average); // Adicionando o FuzzySet correspondente ao objeto Consequente
	// Instanciando um objeto FuzzyRule
	FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifDistanceSafe, thenVelocityAverage); // Passando o Antecedente e o Consequente da expressao

	fuzzy->addFuzzyRule(fuzzyRule02); // Adicionando o FuzzyRule ao objeto Fuzzy

	// FuzzyRule "SE distancia = grande ENTAO velocidade = baixa"
	FuzzyRuleAntecedent* ifDistanceBig = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expresso
	ifDistanceBig->joinSingle(big); // Adicionando o FuzzySet correspondente ao objeto Antecedente
	FuzzyRuleConsequent* thenVelocitySlow = new FuzzyRuleConsequent(); // Instancinado um Consequente para a expressao
	thenVelocitySlow->addOutput(slow);// Adicionando o FuzzySet correspondente ao objeto Consequente
	// Instanciando um objeto FuzzyRule
	FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifDistanceBig, thenVelocitySlow); // Passando o Antecedente e o Consequente da expressao

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

    Serial.println(distancia);
    // Passo 5 - Informar o valor das entradas, passando seu ID e valor
    fuzzy->setInput(1, dist); 
    // Passo 6 - Executar a fuzzyficação
    fuzzy->fuzzify(); 
    // Passo 7 - Executar a desfuzzyficação para cada saída, passando seu ID
    int output = fuzzy->defuzzify(1);
 
    int soundvalue = map(distancia, 0,100,0,500);
    //Serial.print("Input: ");  
    //Serial.print(dist);  
    Serial.print(" Output: ");
    Serial.print(output); 
    Serial.print("\n");  
    if (output<30){
         noTone(sound);
         delay (500);
    }else if(output>70){
      tone (sound, 500);
    }else{
         tone (sound, 500);
         delay (distancia*10+10);
         noTone(sound);
         delay (distancia*10+10);
    }
 
    

}
