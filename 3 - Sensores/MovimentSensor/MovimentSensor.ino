#define SoundPin 7
#define SensorPin 8
//Pinos pra baixo: Negativo Sinal Positivo

void setup()
{
	pinMode(SensorPin, INPUT);
	pinMode(SoundPin, OUTPUT);
	Serial.begin(9600);
}
void loop()
{
	Serial.println(digitalRead(SensorPin));
	if(digitalRead(SensorPin)==1){
		tone(SoundPin, 244);
	}else{
		noTone(SoundPin);
	}
}
