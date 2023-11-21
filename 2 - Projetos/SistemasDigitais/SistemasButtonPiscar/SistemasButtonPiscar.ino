const int buttonPin = 2;
const int ledButton = 13;

int ledState=HIGH;
int buttonAtual;
int onoroff = HIGH;

void setup()
{
	pinMode(ledButton, OUTPUT);
	pinMode(buttonPin, INPUT_PULLUP);
	attachInterrupt(buttonPin-2, actionButton, FALLING);
	Serial.begin(9600);

}
void actionButton(){
  onoroff=!onoroff;
  Serial.println(onoroff);
  while(digitalRead(buttonPin)==0){
  	digitalWrite(ledButton, onoroff);
  }
}
void loop()
{ 
	digitalWrite(ledButton, ledState);
	delay(1000);
    ledState=!ledState;		    
}

/*
const int buttonPin = 2;
const int ledButton = 13;

int ledState=HIGH;
int buttonAtual;
int buttonAnterior= HIGH;
long debounceAnterior = 0;
long debounceTempo = 100;
int onoroff = 0;

void setup()
{
	pinMode(ledButton, OUTPUT);
	pinMode(buttonPin, INPUT_PULLUP);
	Serial.begin(9600);
}

void loop()
{
  //
	int leitura=digitalRead(buttonPin);
	//Estado do botão alterou?
	if(leitura!=buttonAnterior){
		//Guarda o tempo
		debounceAnterior=millis();
	}

	//Já passou o tempo de debounce para prossegir?
	if ((millis() - debounceAnterior) > debounceTempo) {
		//A leitura é diferente do estado atual?
    	  if(leitura!=buttonAtual){
    	  	//Altera o estado atual
    		buttonAtual=leitura;
        
        }
}
    buttonAnterior=leitura;
    if (buttonAtual == LOW) {
    	if(onoroff){
    		digitalWrite(ledButton, HIGH);
    	}else{
    		digitalWrite(ledButton, LOW);
    	}
      	onoroff = !onoroff;
    }else{
    	digitalWrite(ledButton, ledState);
		delay(1000);
    	ledState=!ledState;	
	}
  //
  
	while(digitalRead(buttonPin)){
		digitalWrite(ledButton, ledState);
		delay(1000);
        ledState=!ledState;		
	}
    while(digitalRead(buttonPin)==0){
		digitalWrite(ledButton, LOW);
    }
	while(digitalRead(buttonPin)){
		digitalWrite(ledButton, ledState);
		delay(1000);
        ledState=!ledState;		
	}
    while(digitalRead(buttonPin)==0){
	  digitalWrite(ledButton, HIGH);
    }
    
}
*/