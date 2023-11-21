#include <Wire.h>
#include <Keypad.h>
#define SLAVE_ADDRESS 0x60

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {31, 33, 35, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {39, 41, 43, 45}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int referencia, referenciaFinal, posicaoAtual;

void setup()
{
  Serial.begin(9600);  
  //posicaoAtual = 90;
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
          Serial.print("Sent: ");
          Serial.print(referenciaFinal);
          Serial.print("\n");
          Wire.beginTransmission(0x60);   
          Wire.write((char)referenciaFinal);                
          Wire.endTransmission();   
          //delay(500);
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
    /*
    Serial.println("Atual:");
    Serial.println(posicaoAtual);
    //Pula linha
    Serial.println("Ref:");
    Serial.println(referenciaFinal);
    Serial.println(referencia);
    delay(165);  // Clear LCD, delay is a must.
    */
    /*
    Serial.print("Sent: ");
    Serial.print(x, HEX);
    Serial.print("\n");
    */
    //Serial.println("Requesting Data"); 
    Wire.requestFrom(SLAVE_ADDRESS, 1);
    int bytes = Wire.available();
    /*
    Serial.print("Slave sent ");
    Serial.print(bytes);
    Serial.print(" of information\n");
    */
    for(int i = 0; i< bytes; i++)
    {
      posicaoAtual = int(Wire.read());
      Serial.print("Slave Sent: ");
      Serial.print(posicaoAtual);
      Serial.print("\n");
    }  
}
