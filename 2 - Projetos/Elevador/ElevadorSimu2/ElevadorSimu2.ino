//#include "Threads.h"
//#include "ThreadsController.h"
//ELEVADOR1
int motor1a=2;
int motor1b=3;
//LED SENTIDO;
int subindo1=4;
int descendo1=5;
//Display Andar 
int UMdisplay1=6;
int UMdisplay2=7;
//FINS DE CURSO
byte  UMSensor1Andar = 34;
byte  UMSensor2Andar = 33;
byte  UMSensor3Andar = 32;


//BOTOES EXTERNOS
byte  primeiroAndar = 28;
byte  segundoAndarS = 27;
byte  segundoAndarD = 26;
byte  terceiroAndar = 25;

int ledExt1 = 50;
int ledExt2 = 49;
int ledExt3 = 48;
int ledExt4 = 47;

//BOTOES INTERNOS ELEVADOR1
byte  UMInt1Andar = 24;
byte  UMInt2Andar = 23;
byte  UMInt3Andar = 22;

int led1Elev1=53;
int led1Elev2=52;
int led1Elev3=51;


int ledAndarAtual1=46;
int ledAndarAtual2=45;
int ledAndarAtual3=44;

int buttonsOutput[]={motor1a,motor1b,
                    UMdisplay1,UMdisplay2,
                    subindo1, descendo1,
                    led1Elev1,led1Elev2,led1Elev3,
                    ledExt1,ledExt2,ledExt3,ledExt4,
                    ledAndarAtual1,ledAndarAtual2,ledAndarAtual3};

#define NUMOUTPUTS sizeof(buttonsOutput)


//Variavel que guarda os andares a serem atendidos 
//andaresParaAtender={0,0,0,1} = Atender 3 andar
//andaresParaAtender={0,1,0,0} = Atender 2 andar baixo
//andaresParaAtender={0,0,1,0} = Atender 2 andar cima
//andaresParaAtender={1,0,0,0} = Atender 1 andar
int andaresParaAtender[4]={0,0,0,0};
int andaresParaEntregar1[3]={0,0,0};

int andarAtualElevador1 =1;

#define OpenTime 2000
long timeElevator1 = 0;

#define DEBOUNCE 10  // button debouncer, how many ms to debounce, 5+ ms is usually plenty

byte buttons[] = {UMSensor1Andar, UMSensor2Andar, UMSensor3Andar, 
                  primeiroAndar, segundoAndarS, segundoAndarD, terceiroAndar,
                  UMInt1Andar, UMInt2Andar, UMInt3Andar};
//determine how big the array up above is, by checking the size
#define NUMBUTTONS sizeof(buttons)

#define DEBOUNCE 10  // how many ms to debounce, 5+ ms is usually plenty
 
//track if a button is just pressed, just released, or 'currently pressed' 
byte pressed[NUMBUTTONS], justpressed[NUMBUTTONS], justreleased[NUMBUTTONS];
byte previous_keystate[NUMBUTTONS], current_keystate[NUMBUTTONS];
 
void setup(){
  byte i;
  Serial.begin(9600); //set up serial port
   delay(500);
  Serial.print("Button checker with ");
     delay(500);
  Serial.write(254);  // start LCD control mode before sending control instruction to it
  Serial.write(1);  delay(500);  // Clear LCD, delay is a must.
  Serial.print(NUMBUTTONS, DEC);
  Serial.println(" buttons");
  // Make input &amp; enable pull-up resistors on switch pins
  for (i=0; i< NUMBUTTONS; i++) {
    pinMode(buttons[i], INPUT);
    digitalWrite(buttons[i], HIGH);
  }
  for (i=0; i< NUMOUTPUTS; i++) {
    pinMode(buttonsOutput[i], OUTPUT);
  }
  displayElevador1(1);
  para1(1);
}
 
void loop() {
  byte thisSwitch=thisSwitch_justPressed();
  switch(thisSwitch){  
    //ELEVADOR1 CHEGOU ANDAR 1
    case 0: 
      displayElevador1(1); 
      //PRECISA ENTREGAR ALGUEM NESSE ANDAR OU ALGUEM CHAMOU NESSE ANDAR?
      if(andaresParaEntregar1[0]==1||andaresParaAtender[0]==1){
        para1(1);
      }
    break;
    //ELEVADOR1 CHEGOU ANDAR 2
    case 1: 
      displayElevador1(2); 
      //PRECISA ENTREGAR ALGUEM NESSE ANDAR?
      if(andaresParaEntregar1[1]==1){
        para1(2);
  
      }
      //PRECISA PEGAR ALGUEM NESSE ANDAR e A PESSOA VAI SUBIR E NÃO TEM NINGUEM PEDINDO PRA DESCER
      else if( (andaresParaAtender[2]==1) && (andaresParaEntregar1[0]==0) ){
        para1(2);
      }
      //PRECISA PEGAR ALGUEM NESSE ANDAR e A PESSOA VAI DESCER E NÃO TEM NINGUEM PEDINDO PRA SUBIR
      else if( (andaresParaAtender[1]==1) && (andaresParaEntregar1[2]==0) ){
        para1(2);
      }
    break;
    //ELEVADOR1 CHEGOU ANDAR 3
    case 2: 
      displayElevador1(3); 
      //PRECISA ENTREGAR ALGUEM NESSE ANDAR OU ALGUEM CHAMOU NESSE ANDAR?
      if(andaresParaEntregar1[2]==1||andaresParaAtender[3]==1){
        para1(3);
      }
    break;

    //CHAMOU EXTERNO ANDAR1
    case 3: 
      andaresParaAtender[0]=1;
    break; 
    //CHAMOU EXTERNO ANDAR2 DESCE
    case 4: 
      andaresParaAtender[1]=1;
    break; 
    //CHAMOU EXTERNO ANDAR2 SOBE
    case 5: 
      andaresParaAtender[2]=1;
    break; 
    //CHAMOU EXTERNO ANDAR3
    case 6: 
      andaresParaAtender[3]=1;
    break;       

    //ELEV1 MANDOU INTERNO ANDAR1
    case 7: 
      andaresParaEntregar1[0]=1;
    break;       
    //ELEV1 MANDOU INTERNO ANDAR2
    case 8: 
      andaresParaEntregar1[1]=1;
    break;       
    //ELEV1 MANDOU INTERNO ANDAR3
    case 9: 
      andaresParaEntregar1[2]=1;
    break;     
  }
  
  if(millis()-timeElevator1>OpenTime){
    //Esta no primeiro
    if(andarAtualElevador1==1){
      //precisa entregar no segundo ou terceiro
      if(andaresParaEntregar1[1]==1||andaresParaEntregar1[2]==1){
        sobe1();
      }
      //Alguem chamou no segundo ou terceiro
      else if(andaresParaAtender[1]==1||andaresParaAtender[2]==1||andaresParaAtender[3]==1){
        sobe1();
      }
    }
    //Esta no segundo
    else if(andarAtualElevador1==2){
      //precisa entregar no primeiro
      if(andaresParaEntregar1[0]==1){
        desce1();
      }
      //precisa entregar no terceiro
      else if(andaresParaEntregar1[2]==1){
        sobe1();
      }
      //Alguem chamou no primeiro
      else if(andaresParaAtender[0]==1){
        desce1();
      }
      //Alguem chamou no terceiro
      else if(andaresParaAtender[3]==1){
        sobe1();
      }
    }
    //Esta no terceiro
    else if(andarAtualElevador1==3){
      //precisa entregar no primeiro ou segundo
      if(andaresParaEntregar1[0]==1||andaresParaEntregar1[1]==1){
        desce1();
      }
      //Alguem chamou no primeiro ou segundo
      else if(andaresParaAtender[0]==1||andaresParaAtender[1]==1||andaresParaAtender[2]==1){
        desce1();
      }
    }
  }

  if(andarAtualElevador1==1){
    digitalWrite(ledAndarAtual1, HIGH);
      digitalWrite(ledAndarAtual2, LOW);
            digitalWrite(ledAndarAtual3, LOW);
  }else if(andarAtualElevador1==2){
    digitalWrite(ledAndarAtual2, HIGH);
          digitalWrite(ledAndarAtual1, LOW);
                digitalWrite(ledAndarAtual3, LOW);
  }else if(andarAtualElevador1==3){
      digitalWrite(ledAndarAtual3, HIGH);
            digitalWrite(ledAndarAtual1, LOW);
                  digitalWrite(ledAndarAtual2, LOW);
  }
  digitalWrite(led1Elev1, andaresParaEntregar1[0]);
  digitalWrite(led1Elev2, andaresParaEntregar1[1]);
  digitalWrite(led1Elev3, andaresParaEntregar1[2]);

  digitalWrite(ledExt1, andaresParaAtender[0]);
  digitalWrite(ledExt2, andaresParaAtender[1]);
  digitalWrite(ledExt3, andaresParaAtender[2]);
  digitalWrite(ledExt4, andaresParaAtender[3]);

}
 
void check_switches()
{
  static byte previousstate[NUMBUTTONS];
  static byte currentstate[NUMBUTTONS];
  static long lasttime;
  byte index;
  if (millis() < lasttime) {
    // we wrapped around, lets just try again
    lasttime = millis();
  }
  if ((lasttime + DEBOUNCE) > millis()) {
    // not enough time has passed to debounce
    return; 
  }
  // ok we have waited DEBOUNCE milliseconds, lets reset the timer
  lasttime = millis();
  for (index = 0; index < NUMBUTTONS; index++) {
    justpressed[index] = 0;       //when we start, we clear out the "just" indicators
    justreleased[index] = 0;
    currentstate[index] = digitalRead(buttons[index]);   //read the button
    if (currentstate[index] == previousstate[index]) {
      if ((pressed[index] == LOW) && (currentstate[index] == LOW)) {
        // just pressed
        justpressed[index] = 1;
      }
      else if ((pressed[index] == HIGH) && (currentstate[index] == HIGH)) {
        justreleased[index] = 1; // just released
      }
      pressed[index] = !currentstate[index];  //remember, digital HIGH means NOT pressed
    }
    previousstate[index] = currentstate[index]; //keep a running tally of the buttons
  }
}
 
byte thisSwitch_justPressed() {
  byte thisSwitch = 255;
  check_switches();  //check the switches &amp; get the current state
  for (byte i = 0; i < NUMBUTTONS; i++) {
    current_keystate[i]=justpressed[i];
    if (current_keystate[i] != previous_keystate[i]) {
      if (current_keystate[i]) 
        thisSwitch=i;
    }
    previous_keystate[i]=current_keystate[i];
  }  
  return thisSwitch;
}

void sobe1(){
  //ELEVADOR1
  digitalWrite(motor1a,HIGH);
  digitalWrite(motor1b, LOW);
  digitalWrite(subindo1, HIGH);
  digitalWrite(descendo1, LOW);
}
void desce1(){
  //ELEVADOR1
  digitalWrite(motor1a,LOW);
  digitalWrite(motor1b,HIGH);
  digitalWrite(subindo1, LOW);
  digitalWrite(descendo1, HIGH);
}
void para1(int andar){
  //ELEVADOR1
  timeElevator1 = millis();
  digitalWrite(motor1a,LOW);
  digitalWrite(motor1b,LOW);
  digitalWrite(subindo1, LOW);
  digitalWrite(descendo1, LOW);
  if(andar==1){
    andarAtualElevador1=1;
    andaresParaEntregar1[0]=0;
    andaresParaAtender[0]=0;
  }else if(andar==2){
    andarAtualElevador1=2;
    andaresParaEntregar1[1]=0;
    andaresParaAtender[1]=0;
    andaresParaAtender[2]=0;
  }else if(andar==3){
    andarAtualElevador1=3;
    andaresParaAtender[3]=0;
    andaresParaEntregar1[2]=0;
  }
}
void displayElevador1(int andar){
  switch (andar) {
      case 1:
        digitalWrite(UMdisplay1, HIGH);
        digitalWrite(UMdisplay2, LOW);
        break;
      case 2:
        digitalWrite(UMdisplay1, LOW);
        digitalWrite(UMdisplay2, HIGH);
        break;
      case 3:
        digitalWrite(UMdisplay1, HIGH);
        digitalWrite(UMdisplay2, HIGH);
        break;
      default:
        digitalWrite(UMdisplay1, LOW);
        digitalWrite(UMdisplay2, LOW);
  }
}


