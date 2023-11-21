#include <FuzzyRule.h>
#include <FuzzyComposition.h>
#include <Fuzzy.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzyOutput.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzySet.h>
#include <FuzzyRuleAntecedent.h>


int iluminacao_saida = 0;
int numOfReadings = 10;
int readings[10];
int LDR = 5;// Sensor de iluminacao

int initPin = 9;


unsigned long pulseTime = 0;

// Instanciando um objeto da biblioteca
Fuzzy* fuzzy = new Fuzzy();

void setup(){
  Serial.begin(9600);
 
  // set init pin as output
  pinMode(initPin, OUTPUT);
  // set sensor lm35 como entrada


  // create array loop to iterate over every item in the array
  for (int thisReading = 0; thisReading < numOfReadings; thisReading++) {
    readings[thisReading] = 0;
  }
 
  // Criando o FuzzyInput iluminacao
 
  FuzzyInput* iluminacao = new FuzzyInput(1);

  // Criando os FuzzySet que compoem o FuzzyInput iluminacao
 
  FuzzySet* escuro = new FuzzySet(0, 40, 40, 65); // iluminacao escuro 15° 35°
  iluminacao->addFuzzySet(escuro); // Adicionando o FuzzySet escuro em iluminacao

  FuzzySet* normal = new FuzzySet(30, 50, 50, 70); // iluminacao normal
  iluminacao->addFuzzySet(normal); // Adicionando o FuzzySet normal em iluminacao

  FuzzySet* Iluminado = new FuzzySet(60, 80, 80, 100); // iluminacao muito normal
  iluminacao->addFuzzySet(Iluminado); // Adicionando o FuzzySet Iluminado em iluminacao
 
  fuzzy->addFuzzyInput(iluminacao); // Adicionando o FuzzyInput no objeto Fuzzy
 
 
  // Criando o FuzzyOutput Brilho da LED
 
  FuzzyOutput* brilho = new FuzzyOutput(1);
   
    // Criando os FuzzySet que compoem o FuzzyOutput Brilho do LED
   
    FuzzySet* baixo = new FuzzySet(0, 80, 80, 130); // Brilho do LED baixo
    brilho->addFuzzySet(baixo); // Adicionando o FuzzySet baixo em brilho
   
    FuzzySet* medio = new FuzzySet(70, 150, 150, 200); // Brilho do LED normal
    brilho->addFuzzySet(medio); // Adicionando o FuzzySet medio em brilho
   
    FuzzySet* elevado = new FuzzySet(150, 190, 255, 255); // Brilho do LED elevado
    brilho->addFuzzySet(elevado); // Adicionando o FuzzySet elevado em brilho
 
    fuzzy->addFuzzyOutput(brilho); // Adicionando o FuzzyOutput no objeto Fuzzy
 
  //-------------------- Montando as regras Fuzzy
 
  // FuzzyRule "SE iluminacao = escuro ENTAO Brilho do LED = Elevado"
 
  FuzzyRuleAntecedent* ifiluminacaoescuro = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expresso
  ifiluminacaoescuro->joinSingle(escuro); // Adicionando o FuzzySet correspondente ao objeto Antecedente
 

    FuzzyRuleConsequent* thenbrilhoelevado = new FuzzyRuleConsequent(); // Instancinado um Consenormal para a expressao
  thenbrilhoelevado->addOutput(elevado);// Adicionando o FuzzySet correspondente ao objeto Consenormal
 
 
  // Instanciando um objeto FuzzyRule
  FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifiluminacaoescuro, thenbrilhoelevado); // Passando o Antecedente e o Consenormal da expressao
  fuzzy->addFuzzyRule(fuzzyRule01); // Adicionando o FuzzyRule ao objeto Fuzzy
 
  // FuzzyRule "SE iluminacao = normal ENTAO Brilho do LED = medio"
  FuzzyRuleAntecedent* ifiluminacaonormal = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expresso
  ifiluminacaonormal->joinSingle(normal); // Adicionando o FuzzySet correspondente ao objeto Antecedente
 
  FuzzyRuleConsequent* thenbrilhomedio = new FuzzyRuleConsequent(); // Instancinado um Consenormal para a expressao
  thenbrilhomedio->addOutput(medio);// Adicionando o FuzzySet correspondente ao objeto Consenormal
 
  // Instanciando um objeto FuzzyRule
  FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifiluminacaonormal, thenbrilhomedio); // Passando o Antecedente e o Consenormal da expressao
  fuzzy->addFuzzyRule(fuzzyRule02); // Adicionando o FuzzyRule ao objeto Fuzzy
 
  // FuzzyRule "SE iluminacao = Iluminado ENTAO Brilho do LED = baixo"
 
  FuzzyRuleAntecedent* ifiluminacaoIluminado = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expresso
  ifiluminacaoIluminado->joinSingle(Iluminado); // Adicionando o FuzzySet correspondente ao objeto Antecedente


   FuzzyRuleConsequent* thenbrilhobaixo = new FuzzyRuleConsequent(); // Instancinado um Consenormal para a expressao
  thenbrilhobaixo->addOutput(baixo);// Adicionando o FuzzySet correspondente ao objeto Consenormal
 
  // Instanciando um objeto FuzzyRule
 
  FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifiluminacaoIluminado, thenbrilhobaixo); // Passando o Antecedente e o Consenormal da expressao
  fuzzy->addFuzzyRule(fuzzyRule03); // Adicionando o FuzzyRule ao objeto Fuzzy
}

void loop(){
  // send 10 microsecond pulse
  digitalWrite(initPin, HIGH);
  // wait 10 microseconds before turning off
  delayMicroseconds(10);
  // stop sending the pulse
  digitalWrite(initPin, LOW);
 

  float iluminacao_medida = (analogRead(LDR))*0.09765;
 
  fuzzy->setInput(1,iluminacao_medida  );
     
  fuzzy->fuzzify();

  int output = fuzzy->defuzzify(1);
   analogWrite(initPin,output);

  Serial.print(" iluminacao: ");
  Serial.print(iluminacao_medida);
  Serial.print(" Brilho do LED: ");
  Serial.println(output*0.39215);
  Serial.print(" % ");
  // wait 100 milli seconds before looping again
  delay(100);
}

