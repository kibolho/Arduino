//RX
void setup()
{
	Serial.begin(57600);
}

void loop()
{
	if(Serial.available()>0){
		int chegou = Serial.read();
		if(chegou){
			//Pressionado
		}else{
			//Despressionado
		}
	}
}