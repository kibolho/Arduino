
int i=0;

void setup() {

	for (int i=2;i<=7;i++){//pwm
	pinMode(i,OUTPUT);}

	for (int i=8;i<=13;i++){//dir
	pinMode(i,OUTPUT);}


	//SETUP MOTORS-------------------------------------------------
	for (int i=8;i<=10;i++){//dir gauche
	digitalWrite(i,HIGH);}

	for (int i=11;i<=13;i++){//dir droit
	digitalWrite(i,HIGH);}
}

void loop() {
	//TURN ON MOTORS-------------------------------------------------
	for (int i=2;i<=7;i++){//pwm
	analogWrite(i,40);}

	delay(1000);

	//TURN OFF MOTORS-------------------------------------------------
	for (int i=2;i<=7;i++){//pwm
	analogWrite(i,0);}

	delay(3000);
}
