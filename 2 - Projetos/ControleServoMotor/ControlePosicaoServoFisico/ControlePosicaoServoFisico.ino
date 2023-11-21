// ControlePosicaoServo.ino

#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd (8, 9, 4, 5, 6, 7);
int in1 = 13;
int in2 = 11;

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
#define encoder A2
#define positionSet A1
byte rowPins[ROWS] = {30, 31, 32, 33}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {34, 35, 36, 36}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int referencia, referenciaFinal;
void setup() {
    lcd.begin(16, 2);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	Serial.begin(9600); //set up serial port
  	delay(500);
    referencia = map(analogRead(encoder),0,1023,0,180);
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
  	lcd.clear();
	int encoderValue = map(analogRead(encoder),17,960,0,1023);
	int positionValue = analogRead(positionSet);
	lcd.setCursor(0, 0);
	lcd.print("ENCODER: ");
	lcd.print(map(encoderValue,0,1023,0,180));
	lcd.setCursor(0, 1);
	lcd.print("REF: ");
	lcd.print(referenciaFinal);
	lcd.print(" ");
	lcd.print(referencia);

	int erro = map(referenciaFinal,0,180,0,1023)-encoderValue;
	erro = map(erro,0,1023,0,255);
	erro=100*erro;
	if(erro>255){
		erro=255;
	}else if(erro<-255){
		erro=-255;
	}
	if(erro<0){
		erro = -erro;
		analogWrite(in1, 0);
		analogWrite(in2, erro);
	}else if(erro>0){
		erro = erro;
		analogWrite(in1, erro);
		analogWrite(in2, 0);
	}
	else{
		digitalWrite(in1, HIGH);
		digitalWrite(in2, HIGH);
	}
}

