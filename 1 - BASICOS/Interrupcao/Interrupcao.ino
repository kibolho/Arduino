
volatile int state = LOW;

void setup()
{
  //attachInterrupt(digitalPinToInterrupt(3), blink, CHANGE);
    Serial.begin(9600);
}

void loop()
{
  Serial.println(digitalRead(3));
}

void blink()
{
    Serial.println("oi");
}

