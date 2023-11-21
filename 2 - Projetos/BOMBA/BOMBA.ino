//Contador regressivo com display de 7 segmentos
volatile int contador = 70;

int buttonPin = 9;
int digit1 = 10;
int digit2 = 11;
int digit3 = 12;
int digit4 = 13;

int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
long time = 0;
long tempo =0;
void setup() 
{                
  //Configura os pinos digitais 2, 3, 4 e 5 como saída digital
  Serial.begin(19200);
  DDRD = B00111100; 
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  PORTD = contador<<2; 
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, LOW);
  digitalWrite(digit3, LOW);
  digitalWrite(digit4, LOW);
}
void loop() 
{
   // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
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
        time = millis();
        contador=0;
        while(millis()-time<=5000){
          digitalWrite(digit1, LOW);
          digitalWrite(digit2, LOW);
          digitalWrite(digit3, LOW);
          digitalWrite(digit4, LOW);
          PORTD = contador<<2;  //Rotaciona 2 vezes para esq. o contador e manda para os pinos de saída 
          delay(500);
          digitalWrite(digit1, HIGH);
          digitalWrite(digit2, HIGH);
          digitalWrite(digit3, HIGH);
          digitalWrite(digit4, HIGH);
          delay(500);
          
        }
      }
      contador=70;
    }
  }
  
  if(millis()-tempo>=100){
    tempo=millis();
    if(contador<=0)
     contador=70;
    else
      contador--;
  }
  if(contador<=50)
    Serial.print(contador);
     digitalWrite(digit1, LOW);
      digitalWrite(digit2, HIGH);
        digitalWrite(digit3, HIGH);
          digitalWrite(digit4, HIGH);
  byte digito1 = contador%10;

  PORTD = digito1<<2;  //Rotaciona 2 vezes para esq. o contador e manda para os pinos de saída 
  delay(5);
    digitalWrite(digit1, HIGH);
      digitalWrite(digit2, LOW);
        digitalWrite(digit3, HIGH);
          digitalWrite(digit4, HIGH);
  byte digito2 = ((contador%100)-digito1)/10; 
    Serial.print(digito2);       
  PORTD = digito2<<2;  //Rotaciona 2 vezes para esq. o contador e manda para os pinos de saída 
    delay(5);
   digitalWrite(digit1, HIGH);
      digitalWrite(digit2, HIGH);
        digitalWrite(digit3, LOW);
          digitalWrite(digit4, HIGH);
  byte digito3 = ((contador%1000)-digito1-digito2)/100;  
  PORTD = digito3<<2;  //Rotaciona 2 vezes para esq. o contador e manda para os pinos de saída 
    delay(5);
   digitalWrite(digit1, HIGH);
      digitalWrite(digit2, HIGH);
        digitalWrite(digit3, HIGH);
          digitalWrite(digit4, LOW);
  byte digito4 = (contador/1000);          
  PORTD = digito4<<2;  //Rotaciona 2 vezes para esq. o contador e manda para os pinos de saída 
    delay(5);
  lastButtonState = reading;
	
}


