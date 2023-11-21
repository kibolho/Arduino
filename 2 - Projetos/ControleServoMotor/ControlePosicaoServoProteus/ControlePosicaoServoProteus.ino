// ControlePosicaoServo.ino

#include <Keypad.h>
#define encoder A0
#define positionSet A1


const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int in1 = 10;
int in2 = 11;
int enable1 = 2;
int enable2 = 4;
int referencia, referenciaFinal;
void setup() {
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(enable1, OUTPUT);
	pinMode(enable2, OUTPUT);
	Serial.begin(9600); //set up serial port
  	delay(500);
  	digitalWrite(enable1, HIGH); 
    referenciaFinal = map(map(analogRead(encoder),0,1023,-135,135),-135,135,-45,225);
}

void loop() {
  char key = keypad.getKey();
  if(referencia>180){
  	referencia=0000;
  }
  if (key != NO_KEY){
  	if(key == '#'){
  		if(referencia<=180){
   			referenciaFinal = referencia;
   		}
   		referencia = 0;
  	}else{
  		int multiplicador;
  		switch (key) {
  			case '0':
  		      multiplicador = 0;
  		      break;
  		    case '1':
  		      multiplicador = 1;
  		      break;
  		    case '2':
  		  	  multiplicador = 2;
  		      break;
  		    case '3':
		  	  multiplicador = 3;
  		      break;
  		    case '4':
		  	  multiplicador = 4;
  		      break;
  		    case '5':
		  	  multiplicador = 5;
  		      break;
  		    case '6':
		  	  multiplicador = 6;
  		      break;
  		    case '7':
		  	  multiplicador = 7;
  		    break;
  		    case '8':
		  	  multiplicador = 8;
  		    break;
  		    case '9':
		  	  multiplicador = 9;
  		    break;
  		    default:
  		      break;
  		}
  		if(referencia<1){
  			referencia=multiplicador;
  		}else if(referencia<100){
  		   	referencia=referencia*10+multiplicador;
  		}
  	}
  }
	int encoderValue = analogRead(encoder);
	int positionValue = analogRead(positionSet);
	Serial.write(254);  // start LCD control mode before sending control instruction to it
	Serial.write(1);  delay(10);  // Clear LCD, delay is a must.
	Serial.println("Atual:");
	Serial.println(map(map(encoderValue,0,1023,-135,135),-135,135,-45,225));
	//Pula linha
	Serial.write(254);  // start LCD control mode before sending control instruction to it
	Serial.write(192);  delay(10);  // Clear LCD, delay is a must.
	Serial.println("Ref:");
	Serial.println(referenciaFinal);
	Serial.println(referencia);
	delay(165);  // Clear LCD, delay is a must.
	/*
	//Sentido Negativo Anti-Horário
	if(encoderValue<positionValue+3){
		//int erro = map(positionValue-encoderValue,0,1023,0,255);
		int erro = (positionValue-encoderValue)/4;
		analogWrite(in1, erro);
		analogWrite(in2, 0);
	//Sentido Positivo Horário
	}else if(encoderValue+3>positionValue){
	analogWrite(in1, 0);
	//int erro = map(encoderValue-positionValue,0,1023,0,255);
	int erro = (encoderValue-positionValue)/4;
		analogWrite(in2, erro);
	}else{
		digitalWrite(in1, HIGH);
		digitalWrite(in2, HIGH);
	}*/
	int erro = map(referenciaFinal,0,180,-90,90)-map(encoderValue,0,1023,-135,135);
	erro = map(erro,0,1023,0,255);
	erro=10*erro;
	if(erro>255){
		erro=255;
	}else if(erro<-255){
		erro=-255;
	}
	if(erro<0){
		erro = -erro/4;
		analogWrite(in1, 0);
		analogWrite(in2, erro);
	}else if(erro>0){
		erro = erro/4;
		analogWrite(in1, erro);
		analogWrite(in2, 0);
	}
	else{
		digitalWrite(in1, HIGH);
		digitalWrite(in2, HIGH);
	}
}

