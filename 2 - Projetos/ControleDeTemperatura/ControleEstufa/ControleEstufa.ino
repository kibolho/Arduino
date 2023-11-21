//André Kuhn - Automation
//Código para o Dimmer ser controlado pelos botões

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd (8, 9, 4, 5, 6, 7);
#define NUMREADINGS 10

int readings[NUMREADINGS];                // qtde de amostras
int index = 0;                            // índice da leitura atual
int total = 0;                            // total móvel
int average = 0;                          // média

int loadR = 3;
volatile int power = 100;
float tempC;
int reading;
int tempPin = 8;
int temperaturaDesejada = 50;
int tempo=0;

class PID {
  public:
  double error;
  double sample;
  double lastSample;

  double P;
  double kP;

  double I;
  double kI;

  double D;
  double kD;

  double PIDreturn = 0;

  double setPoint;
  long lastProcess;

  PID(double _kP,  double _kI, double _kD){
    kP = _kP;
    kI = _kI;
    kD = _kD;
  }
  void addNewSample(double _sample){
    sample = _sample;
  }
  void setSetPoint (double _setPoint){
    setPoint = _setPoint;
  }
  double process(){
    //Implementação P I D
    error = setPoint - sample;
    
    float deltaTime = (millis() - lastProcess) /1000.0;
    lastProcess = millis();
    //P
    P = error * kP;
    //I
    I += (error * kI) *deltaTime;
    //D
    D = (lastSample- sample) * kD * deltaTime; 
    lastSample = sample;
    //PID
    PIDreturn = P + I + D;
    return PIDreturn;
  }
  
};

PID meuPID(2.0,0.1,0.2);

void setup() 
{
	pinMode(loadR, OUTPUT);
        
  //Inicializa interrupção. O número zero indica a porta 2 do arduino,
  //zero_cross_int é a função que será chamada toda vez que pino 2 do Aeduino,
  //"subir" (RISING) de valor de 0 para 1.
  attachInterrupt(0, zero_cross_int, RISING);
  tempo=millis();
   // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
   // Print a message to the LCD.
  lcd.print("hello, world!");
  
    Serial.begin(9600);
   for (int i = 0; i < NUMREADINGS; i++)
    readings[i] = 0;                      // inicializa todas as leituras com 0
}


void loop() 
{
  lcd.clear();
  lcd.print("LM35 ");
  
//  int botao;  
//  botao = analogRead (0);  //Leitura do valor da porta analógica A0
//  if (botao < 200) {  
//    temperaturaDesejada+=1;
//  }else if (botao < 400){  
//    temperaturaDesejada-=1; 
//  }  
  lcd.print("Set TC= ");
  lcd.print(temperaturaDesejada,1);

  //int reading = analogRead(tempPin);
  total -= readings[index];               // subtrair a última leitura
  readings[index] = analogRead(tempPin); // ler do sensor
  total += readings[index];               // adicionar leitura ao total
  index = (index + 1);                    // avançar ao próximo índice

  if (index >= NUMREADINGS)               // se estiver no fim do vetor...
    index = 0;                            // ...meia-volta ao início

  reading = total / NUMREADINGS;          // calcular a média
  
  tempC=(reading*5)/(1024*0.01) ;  

  lcd.setCursor(0,1);
  lcd.print("TC="); 
  lcd.print(tempC,1);
  lcd.print(" P=");
  lcd.print(power/3);
  delay(50);
  if (millis()-tempo>1000){
    tempo=millis();
    Serial.println(tempC);
  }
  meuPID.setSetPoint(temperaturaDesejada);
  meuPID.addNewSample(tempC);
  power = meuPID.process()*5;
 if(power > 300)
  {
      power=300;
  }else if (power<0){
      power=0;
  } 
}

void zero_cross_int()
{

	//Cálculo do ângulo de disparo: 60Hz -> 8,33ms (1/2 ciclo)
	//(8333us - 8,33us) / 333 = 25 (aproximadamente)
        int powertime = (25*(333-power));
        if(powertime <= 325)
        {
          digitalWrite(loadR, HIGH);
        }	

        else if(powertime >= 8325)
        {
          digitalWrite(loadR, LOW);
        }
        
        else if((powertime > 0) && (powertime < 8325))
        {       
          //Mantém o circuito desligado por powertime microssegundos
      	  delayMicroseconds(powertime);
      	
      	  //Envia sinal ao TRIAC para que ele passe a conduzir
      	  digitalWrite(loadR, HIGH);
      	
      	  //Espera alguns microssegundos para que o TRIAC perceba o pulso
      	  delayMicroseconds(8.33);
              
                //Desliga o pulso
      	  digitalWrite(loadR, LOW);
        }        
}


