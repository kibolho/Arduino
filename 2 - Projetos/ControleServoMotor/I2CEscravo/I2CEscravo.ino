#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#define encoder A2
#define SLAVE_ADDRESS 0x60

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
LiquidCrystal lcd (8, 9, 4, 5, 6, 7);

byte rowPins[ROWS] = {31, 33, 35, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {39, 41, 43, 45}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int in1 = 10;
int in2 = 11;
int enable1 = 2;
int enable2 = 4;
int referencia, referenciaFinal, posicaoAtual;
long lastClearLCD;
int encoderValue;

void setup()
{
   lcd.begin(16, 2);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  Serial.begin(9600); //set up serial port
  delay(500);
  digitalWrite(enable1, HIGH); 
  encoderValue = map(analogRead(encoder),17,960,0,1023);
  posicaoAtual = map(encoderValue,0,1023,0,180);
  referenciaFinal = posicaoAtual;
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  lastClearLCD = millis();
  Serial.print("Ola");
}

void loop()
{
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
  if((millis() - lastClearLCD)>200){
        lcd.clear();
        lastClearLCD = millis();
  }
  encoderValue = map(analogRead(encoder),17,960,0,1023);
  posicaoAtual = map(encoderValue,0,1023,0,180);
  lcd.setCursor(0, 0);
  lcd.print("ENCODER: ");
  lcd.print(posicaoAtual);
  lcd.setCursor(0, 1);
  lcd.print("REF: ");
  lcd.print(referenciaFinal);
  lcd.print(" ");
  lcd.print(referencia);
  //Serial.print(referenciaFinal);
  //delay(165);  // Clear LCD, delay is a must.
  int erro = referenciaFinal - posicaoAtual;
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

void requestEvent() 
{
   Serial.print("Request from Master. Sending: ");
   Serial.print(posicaoAtual, HEX);
   Serial.print("\n");
  Wire.write((char)posicaoAtual);
}

void receiveEvent(int bytes)
{
  if(Wire.available() != 0)
  {
    for(int i = 0; i< bytes; i++)
    {
      referenciaFinal = int(Wire.read());
      Serial.print("Received: ");
      Serial.print(referenciaFinal);
      Serial.print("\n");
    }
  }
}

