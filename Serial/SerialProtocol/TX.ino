
//TX
#define SENSOR_TOQUE 10

void setup(){
	Serial.begin(57600);
	pinMode(SENSOR_TOQUE, INPUT);
}
void loop()
{
	Serial.write(digitalRead(SENSOR_TOQUE));
}