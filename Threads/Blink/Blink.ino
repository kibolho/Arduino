#define LED1 2
#define LED2 3

#define LED1_TIMER 2000
#define LED2_TIMER 1000

long lastExecuteTimeLED1 = 0;
long lastExecuteTimeLED2 = 0;

void setup()
{
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	Serial.begin(9600);
}

void loop()
{
	if((millis()-lastExecuteTimeLED1)>= LED1_TIMER){
		digitalWrite(LED1, !digitalRead(LED1));
		lastExecuteTimeLED1=millis();
		Serial.println(lastExecuteTimeLED1);
	}
	if((millis()-lastExecuteTimeLED2)>= LED2_TIMER){
		digitalWrite(LED2, !digitalRead(LED2));
		lastExecuteTimeLED2=millis();
		Serial.println(lastExecuteTimeLED2);
	}
}
