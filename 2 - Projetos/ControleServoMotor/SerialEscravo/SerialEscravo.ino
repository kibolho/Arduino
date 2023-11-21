#include <Keypad.h>
#define encoder A0
#define positionSet A1

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int in1 = 10;
int in2 = 11;
int enable1 = 2;
int enable2 = 4;
int referencia, referenciaFinal, posicaoAtual;
int encoderValue;
int positionValue;
double resposta;
//how big should our messages be?
//in this case, 3 bytes
//1 for command
// then 1 for the value
//the next byte is optional, 
//if you want to send a 16 byte variable.
const int BUFFER_LIMIT = 5;

struct
{
  byte data[BUFFER_LIMIT]; //this is where we will store the data we receive from the serial
  byte curLoc; //this is the counter to keep track of how many bytes we've received
} dataPacket;

enum PACKET_DETAILS{ 
  HEADER = 0,
  KEY = 1,
  ITEM_1 = 2,
  ITEM_2 = 3,
  ITEM_3 = 4,
};
//this tracks the state of the current message
bool correctPacket = false;
 
//this is used for the timeout
//the arduino will reset its packet counter if it
//finds a gap of over 500ms between incoming bytes. 
unsigned long lastTimerHit;

void setup()
{
  dataPacket.curLoc = 0;
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(enable1, OUTPUT);
	pinMode(enable2, OUTPUT);
	Serial.begin(9600); //set up serial port
  delay(500);
  digitalWrite(enable1, HIGH); 
  posicaoAtual = map(map(analogRead(encoder),0,1023,-135,135),-135,135,-45,225);
  referenciaFinal = posicaoAtual;
}

void loop()
{
  if ( Serial1.available() > 0)
  {
    Serial.println("000000000000000000");
    lerSerial();
  }
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
  encoderValue = analogRead(encoder);
  positionValue = analogRead(positionSet);
  posicaoAtual = map(map(encoderValue,0,1023,-135,135),-135,135,-45,225);

	Serial.write(254);  // start LCD control mode before sending control instruction to it
	Serial.write(1);  delay(10);  // Clear LCD, delay is a must.
	Serial.println("Atual:");
	Serial.println(posicaoAtual);
	//Pula linha
	Serial.write(254);  // start LCD control mode before sending control instruction to it
	Serial.write(192);  delay(10);  // Clear LCD, delay is a must.
	Serial.println("Ref:");
	Serial.println(referenciaFinal);
	Serial.println(referencia);
	delay(165);  // Clear LCD, delay is a must.
	int erro = map(referenciaFinal,0,180,-90,90)-map(encoderValue,0,1023,-135,135);
	erro = map(erro,0,1023,0,255);
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
void lerSerial(){
  //check timeout, make sure there is not a large gap between bytes. 
  if ( (lastTimerHit + 500) < millis() )
  {
    //if here, we hit the timeout, reset the packet counter
    dataPacket.curLoc = 0; //reset counter
    correctPacket = false;
    //Serial.println("timeout hit");
  }
  lastTimerHit = millis();
  dataPacket.data[dataPacket.curLoc] = Serial.read();
  dataPacket.curLoc++;
  if(dataPacket.data[dataPacket.curLoc-1]==0){
     dataPacket.curLoc=0;
  }else if (dataPacket.data[dataPacket.curLoc-1]==255){
     dataPacket.curLoc=0;
  }else{
    //check if the counter read 3 bytes in quick sucession

    if ( dataPacket.curLoc == BUFFER_LIMIT)
    {
      //assume the packet is correct. 
      correctPacket = true;
      //reset the counter, can be here or at the end.
      dataPacket.curLoc = 0;
      //RECEBEDO REFERENCIA
      if(dataPacket.data[HEADER]==32){
        if(dataPacket.data[ITEM_1]>47 && dataPacket.data[ITEM_1]<58){
          resposta=(resposta*10)+(dataPacket.data[ITEM_1]-48);
        }
        if(dataPacket.data[ITEM_2]>47 && dataPacket.data[ITEM_2]<58){
          resposta=(resposta*10)+(dataPacket.data[ITEM_2]-48);
        }
        if(dataPacket.data[ITEM_3]>47 && dataPacket.data[ITEM_3]<58){
          resposta=(resposta*10)+(dataPacket.data[ITEM_3]-48);
        }
        if(map(resposta,0,180,0,9) == dataPacket.data[KEY]){
          referenciaFinal = resposta;
        }else{
          correctPacket = false;
          dataPacket.curLoc = 0; 
          Serial.println("Err!");
        }
      }
      //PEDIDO DE POSICAO ATUAL
      else if(dataPacket.data[HEADER]==33){
        if(dataPacket.data[KEY]==33){
          Serial1.write('0');
          //Header
          Serial1.write('32');
          //KEY
          Serial1.write(map(posicaoAtual,0,180,0,9));
          Serial1.write(String(posicaoAtual)[0]);
          Serial1.write(String(posicaoAtual)[1]);
          Serial1.write(String(posicaoAtual)[2]);
          //Final da mensagem
          Serial1.write('255');
        }
      }else{
        correctPacket = false;
        dataPacket.curLoc = 0; 
        Serial.println("Err!");
                
      }
      if (correctPacket == true )
      {
        Serial.print("Sucesso\n");
        correctPacket = false;
      }
    }
  }
}