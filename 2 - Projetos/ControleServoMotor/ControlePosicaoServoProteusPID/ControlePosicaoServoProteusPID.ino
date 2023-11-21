// ControlePosicaoServo.ino

#include <Keypad.h>
#define encoder A0


class PID{
public:
	
	double error;
	double sample;
	double lastSample;
	double kP, kI, kD;      
	double P, I, D;
	double pid;
	
	double setPoint;
	long lastProcess;
	
	PID(double _kP, double _kI, double _kD){
		kP = _kP;
		kI = _kI;
		kD = _kD;
	}
	
	void addNewSample(double _sample){
		sample = _sample;
	}
	
	void setSetPoint(double _setPoint){
		setPoint = _setPoint;
	}
	
	double process(){
		// Implementação P ID
		error = setPoint - sample;
		float deltaTime = (millis() - lastProcess) / 1000.0;
		lastProcess = millis();
		
		//P
		P = error * kP;
		
		//I
		I = I + (error * kI) * deltaTime;
		
		//D
		D = (lastSample - sample) * kD / deltaTime;
		lastSample = sample;
		
		// Soma tudo
		pid = P + I + D;
		
		return pid;
	}
};

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
int encoderValue;
int posicaoAtual;
int erro;

PID meuPid(1.0, 0, 0);

void setup() {
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(enable1, OUTPUT);
	pinMode(enable2, OUTPUT);
	Serial.begin(9600); //set up serial port
  	delay(500);
  	digitalWrite(enable1, HIGH); 
  	encoderValue = analogRead(encoder);
    referenciaFinal = map(map(encoderValue,0,1023,-135,135),-135,135,-45,225);
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
	encoderValue = analogRead(encoder);
	posicaoAtual = map(map(encoderValue,0,1023,-135,135),-135,135,-45,225);
	Serial.write(254);  // start LCD control mode before sending control instruction to it
	Serial.write(1);  delay(10);  // Clear LCD, delay is a must.
	Serial.println("Atual:");
	Serial.println(posicaoAtual);
	//Pula linha
	Serial.write(254);  // start LCD control mode before sending control instruction to it
	Serial.write(192);  delay(10);  // Clear LCD, delay is a must.
	Serial.println("Ref:");
	Serial.println(referenciaFinal);
	Serial.println(referencia);
	delay(165);  // Clear LCD, delay is a must.
	// Envia a amostra
	meuPid.addNewSample(posicaoAtual); //0 a 180
	// Envia a referencia
	meuPid.setSetPoint(referenciaFinal); //0 a 180
	// Converte para controle
	erro = (meuPid.process());
	erro = map(erro,0,180,0,255);
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