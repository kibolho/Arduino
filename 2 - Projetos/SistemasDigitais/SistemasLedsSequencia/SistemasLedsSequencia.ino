const int buttonPin = 2;
const int leds[3] = {11,12,13};

volatile int buttonAtual;
volatile int buttonAnterior= HIGH;
volatile long debounceAnterior = 2;
volatile long debounceTempo = 1000;
volatile int sentido = 1;
int proximoLed=0;
long ledTempo=1000;
long ledTempoExecutado=0;
void setup()
{
	for(int x=0; x<3; x++){
	   pinMode(leds[x], OUTPUT);
	}
	pinMode(buttonPin, INPUT_PULLUP);
	Serial.begin(9600);
	attachInterrupt(buttonPin-2, actionButton, CHANGE);
}
void actionButton(){
  if(debounceAnterior-millis()>debounceTempo){
      if (digitalRead(buttonPin) == LOW) {
    	 sentido=!sentido;
         Serial.println("Inverteu");
      }      
  }
  debounceAnterior=millis();
}
void loop()
{
    if((millis()-ledTempoExecutado)>ledTempo){
	    if(sentido){
	    	ledTempoExecutado =millis();
	    	digitalWrite(leds[proximoLed], LOW);
	    	if(proximoLed==2)
	    		proximoLed=0;
	    	else
	    		proximoLed++;
	        digitalWrite(leds[proximoLed], HIGH);    
	    }else{
	    	ledTempoExecutado =millis();
	    	digitalWrite(leds[proximoLed], LOW);
	    	if(proximoLed==0)
	    		proximoLed=2;
	    	else
	    		proximoLed--;
	        digitalWrite(leds[proximoLed], HIGH);
	    }
    }
}
//Sem Interrupção

/* 
void setup()
{
	for(int x=0; x<3;x++){
		pinMode(leds[x], OUTPUT);
	}
	pinMode(buttonPin, INPUT_PULLUP);
	Serial.begin(9600);
}
void loop()
{
 	int leitura=digitalRead(buttonPin);
       
	//Estado do botão alterou?
	if(leitura!=buttonAnterior){
                Serial.println(leitura);
		//Guarda o tempo
		debounceAnterior=millis();
	}

	//Já passou o tempo de debounce para prossegir?
	if ((millis() - debounceAnterior) > debounceTempo) {
			//A leitura é diferente do estado atual?
    	    if(leitura!=buttonAtual){
    			//Altera o estado atual
    		    buttonAtual=leitura;
   				//Botão está em estado BAIXO
    	        if (buttonAtual == LOW) {
    		 		 sentido=!sentido;
    	        }
    	    }
    }
    buttonAnterior=leitura;
    if((millis()-ledTempoExecutado)>ledTempo){
	    if(sentido){
	    	ledTempoExecutado =millis();
	    	digitalWrite(leds[proximoLed], LOW);
	    	if(proximoLed==2)
	    		proximoLed=0;
	    	else
	    		proximoLed++;
	        digitalWrite(leds[proximoLed], HIGH);    
	    }else{
	    	ledTempoExecutado =millis();
	    	digitalWrite(leds[proximoLed], LOW);
	    	if(proximoLed==0)
	    		proximoLed=2;
	    	else
	    		proximoLed--;
	        digitalWrite(leds[proximoLed], HIGH);
	    }
    }
}
*/





