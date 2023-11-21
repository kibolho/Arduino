//Robo quer controlar termperatura do ambiente
//Tem um sensor de temperatura no pino A1
// 0 - 1023
// 0 = 0 graus
//1024 = 100 graus

//Pino 3 Aquecedor/resfriador
//0 -> Resfriando (max)
//50 -> Desligar
//100 -> aquecendo (max)

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

#define pSENSOR 	A1
#define pCONTROLE 	3

PID meuPID(1.0,0,0);

void setup()
{
	Serial.begin(9600);

	pinMode(pSENSOR, INPUT);
	pinMode(pCONTROLE, OUTPUT);
}

int controlePWM = 50;


void loop()
{
	//Le temperatura
	// 0 a 1023
	double temperature = map (analogRead(pSENSOR), 0, 1023, 0, 100);

	//Manda pro objeto meuPID
	meuPID.addNewSample(temperature);

 	//Converter Para Controle
 	controlePWM = meuPID.process() + 50;
	//Saida do controle
	analogWrite(pCONTROLE, controlePWM);
}
