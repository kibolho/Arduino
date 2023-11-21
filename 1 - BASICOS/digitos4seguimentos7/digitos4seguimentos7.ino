volatile int contador = 1234;

int buttonPin = 9;
int clock1 = 6;
int resetClock = 7;
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
void setup() 
{                
  //Configura os pinos digitais 2, 3, 4 e 5 como saída digital
  Serial.begin(9600);
  DDRD = B00111100; 
  pinMode(buttonPin, INPUT_PULLUP);
  PORTD = contador<<2; 
  pinMode(clock1, OUTPUT);
  pinMode(resetClock, OUTPUT);
  delay(10);
  digitalWrite(resetClock, HIGH);
    delay(10);
   digitalWrite(resetClock, LOW);
    delay(10);
}
void loop() 
{
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW) {
        if(contador<=0){
          contador=999;
        }else{
          Serial.println("Oi");
          contador--;
        } 
      }
    }
  }
  byte digito1 = contador%10;
  byte digito2 = ((contador%100)-digito1)/10; 
  byte digito3 = ((contador%1000)-digito1-digito2)/100;
  byte digito4 = (contador/1000); 

  PORTD = digito2<<2;  //Rotaciona 2 vezes para esq. o contador e manda para os pinos de saída 
  digitalWrite(clock1, HIGH);
  delay(50);
  digitalWrite(clock1, LOW);

  PORTD = digito3<<2;  //Rotaciona 2 vezes para esq. o contador e manda para os pinos de saída 
  digitalWrite(clock1, HIGH);
  delay(50);
  digitalWrite(clock1, LOW);

  PORTD = digito4<<2;  //Rotaciona 2 vezes para esq. o contador e manda para os pinos de saída 
  digitalWrite(clock1, HIGH);
  delay(50);
  digitalWrite(clock1, LOW);

  PORTD = digito1<<2;  //Rotaciona 2 vezes para esq. o contador e manda para os pinos de saída 
  digitalWrite(clock1, HIGH);
  delay(50);
  digitalWrite(clock1, LOW);

  digitalWrite(resetClock, HIGH);
    delay(10);
   digitalWrite(resetClock, LOW);
  
  lastButtonState = reading;
}

