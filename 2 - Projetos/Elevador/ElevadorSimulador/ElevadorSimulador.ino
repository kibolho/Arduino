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
//INDICADOR DE PORTAS
int ind1porta1 = 38;
int ind1porta2 = 39;
int ind1porta3 = 40;

//ELEVADOR2
int motor2a=8;
int motor2b=9;
//LED SENTIDO;
int subindo2=10;
int descendo2=11;
//Display Andar 
int DOISdisplay1=12;
int DOISdisplay2=13;
//FINS DE CURSO
byte  DOISSensor1Andar = 37;
byte  DOISSensor2Andar = 36;
byte  DOISSensor3Andar = 35;
//INDICADOR DE PORTAS
int ind2porta1 = 41;
int ind2porta2 = 42;
int ind2porta3 = 43;

//BOTOES EXTERNOS
byte  primeiroAndar = 28;
byte  segundoAndarS = 27;
byte  segundoAndarD = 26;
byte  terceiroAndar = 25;

//LEDS DOS BOTOES EXTERNOS
int ledExt1 = 50;
int ledExt2 = 49;
int ledExt3 = 48;
int ledExt4 = 47;

//BOTOES INTERNOS ELEVADOR1
byte  UMInt1Andar = 24;
byte  UMInt2Andar = 23;
byte  UMInt3Andar = 22;

//LEDS DOS BOTOES INTERNOS ELEVADOR1
int led1Elev1=53;
int led1Elev2=52;
int led1Elev3=51;

//BOTOES INTERNOS ELEVADOR2
byte  DOISInt1Andar = 31;
byte  DOISInt2Andar = 30;
byte  DOISInt3Andar = 29;

//LEDS DOS BOTOES INTERNOS ELEVADOR2
int led2Elev1=46;
int led2Elev2=45;
int led2Elev3=44;

//COLOCANDO OS BOTÕES EM UM ARRAY PARA SIMPLIFICAR O SETUP
int buttonsOutput[]={motor1a,motor1b,motor2a,motor2b,
                    UMdisplay1,UMdisplay2, DOISdisplay1,DOISdisplay2, 
                    subindo1, descendo1, subindo2, descendo2,
                    led1Elev1,led1Elev2,led1Elev3,
                    led2Elev1,led2Elev2,led2Elev3,
                    ledExt1,ledExt2,ledExt3,ledExt4,
                    ind1porta1,ind1porta2,ind1porta3,
                    ind2porta1,ind2porta2,ind2porta3};

#define NUMOUTPUTS sizeof(buttonsOutput)


//Variavel que guarda os andares a serem atendidos 
//andaresParaAtender={0,0,0,1} = Atender 3 andar
//andaresParaAtender={0,1,0,0} = Atender 2 andar baixo
//andaresParaAtender={0,0,1,0} = Atender 2 andar cima
//andaresParaAtender={1,0,0,0} = Atender 1 andar
int andaresParaAtender[4]={0,0,0,0};
int andaresIndoAtender1[4]={0,0,0,0};
int andaresIndoAtender2[4]={0,0,0,0};

//Variavel que guarda os andares para entregar
//andaresParaEntregar={0,0,1} = Entregar 3 andar
//andaresParaEntregar={0,1,0} = Entregar 2 andar
//andaresParaEntregar={1,0,0} = Entregar 1 andar
int andaresParaEntregar1[3]={0,0,0};
int andaresParaEntregar2[3]={0,0,0};

//Guarda o andar atual do elevador
int andarAtualElevador1 =1;
int andarAtualElevador2 =1;

//Situação do elevador
int parado1=1;
int parado2=1;
/*
int elevador1ocupado = 0;
int elevador2ocupado = 0;
*/

//ESTADO DOS FINS DE CURSO
int andar1[3]={0,0,0};
int andar2[3]={0,0,0};
int x = 0;
int y = 0;

//Tempo de porta aberta do elevador
#define OpenTime 2000
long timeElevator1 = 0;
long timeElevator2 = 0;

//DEBOUNCE DE TODOS OS PINOS DE INPUT
#define DEBOUNCE 10  // button debouncer, how many ms to debounce, 5+ ms is usually plenty

byte buttons[] = {UMSensor1Andar, UMSensor2Andar, UMSensor3Andar, 
                  DOISSensor1Andar, DOISSensor2Andar, DOISSensor3Andar, 
                  primeiroAndar, segundoAndarS, segundoAndarD, terceiroAndar,
                  UMInt1Andar, UMInt2Andar, UMInt3Andar,
                  DOISInt1Andar, DOISInt2Andar, DOISInt3Andar};
//determine how big the array up above is, by checking the size
#define NUMBUTTONS sizeof(buttons)
 
//track if a button is just pressed, just released, or 'currently pressed' 
byte pressed[NUMBUTTONS], justpressed[NUMBUTTONS], justreleased[NUMBUTTONS];
byte previous_keystate[NUMBUTTONS], current_keystate[NUMBUTTONS];
 
void setup(){
  byte i;
  Serial.begin(9600); //set up serial port
  delay(500);
  Serial.write(254);  // start LCD control mode before sending control instruction to it
  Serial.write(1);  delay(500);  // Clear LCD, delay is a must.
  Serial.print(NUMBUTTONS, DEC);
  Serial.println(" buttons");
  Serial.write(254);  // start LCD control mode before sending control instruction to it
  Serial.write(1);  delay(500);  // Clear LCD, delay is a must.
  Serial.println("Elevadores");
  Serial.write(254);  // start LCD control mode before sending control instruction to it
  Serial.write(192);  delay(500);  // Clear LCD, delay is a must.
  Serial.println("Inteligentes S.A.");
  // Make input &amp; enable pull-up resistors on switch pins
  for (i=0; i< NUMBUTTONS; i++) {
    pinMode(buttons[i], INPUT);
    digitalWrite(buttons[i], HIGH);
  }
  for (i=0; i< NUMOUTPUTS; i++) {
    pinMode(buttonsOutput[i], OUTPUT);
  }
  if(!digitalRead(UMSensor1Andar)){
    displayElevador1(1);
    para1(1);
  }
  else if(!digitalRead(UMSensor2Andar)){
    displayElevador1(2);
    para1(21);
    para1(22);
  }
  else if(!digitalRead(UMSensor3Andar)){
    displayElevador1(3);
    para1(3);
  }
  if(!digitalRead(DOISSensor1Andar)){
    displayElevador2(1);
    para2(1);
  }
  else if(!digitalRead(DOISSensor2Andar)){
    displayElevador2(2);
    para2(21);
    para2(22);
  }
  else if(!digitalRead(DOISSensor3Andar)){
    displayElevador2(3);
    para2(3);
  }
}
 
void loop() {
  byte thisSwitch=thisSwitch_justPressed();
  switch(thisSwitch){  
    //ELEVADOR1 CHEGOU ANDAR 1
    case 0: 
      displayElevador1(1);
      desligarIndicadores1(); 
      //andarAtualElevador1=1;
      //PRECISA ENTREGAR ALGUEM NESSE ANDAR OU ALGUEM CHAMOU NESSE ANDAR?
      //if(andaresParaEntregar1[0]==1||andaresParaAtender[0]==1){
        para1(1);
      //}
    break;
    //ELEVADOR1 CHEGOU ANDAR 2
    case 1: 
      displayElevador1(2); 
      desligarIndicadores1(); 
      //andarAtualElevador1=2;
      //PRECISA ENTREGAR ALGUEM NESSE ANDAR?
      if(andaresParaEntregar1[1]==1){
        para1(21);
      }
      //PRECISA PEGAR ALGUEM NESSE ANDAR e A PESSOA VAI SUBIR E NÃO TEM NINGUEM PEDINDO PRA DESCER
      else if( (andaresParaAtender[2]==1) && (andaresParaEntregar1[0]==0) && (andaresIndoAtender1[0]==0)){
        para1(22);
      }
      //PRECISA PEGAR ALGUEM NESSE ANDAR e A PESSOA VAI DESCER E NÃO TEM NINGUEM PEDINDO PRA SUBIR
      else if( (andaresParaAtender[1]==1) && (andaresParaEntregar1[2]==0) && (andaresIndoAtender1[3]==0)){
        para1(21);
      }
    break;
    //ELEVADOR1 CHEGOU ANDAR 3
    case 2: 
      displayElevador1(3); 
      desligarIndicadores1(); 
      //andarAtualElevador1=3;
      //PRECISA ENTREGAR ALGUEM NESSE ANDAR OU ALGUEM CHAMOU NESSE ANDAR?
      //if(andaresParaEntregar1[2]==1||andaresParaAtender[3]==1){
        para1(3);
      //}
    break;

    //ELEVADOR2 CHEGOU ANDAR 1
    case 3: 
      displayElevador2(1); 
      desligarIndicadores2(); 
      //andarAtualElevador2=1;
      //PRECISA ENTREGAR ALGUEM NESSE ANDAR OU ALGUEM CHAMOU NESSE ANDAR?
      //if(andaresParaEntregar2[0]==1||andaresParaAtender[0]==1){
        para2(1);
      //}
    break;

    //ELEVADOR2 CHEGOU ANDAR 2
    case 4: 
      displayElevador2(2); 
      desligarIndicadores2(); 
      //andarAtualElevador2=2;
      //TEM ALGUEM PARA ENTREGAR
      if(andaresParaEntregar2[1]==1){
        para2(21);
      }
      //PRECISA PEGAR ALGUEM NESSE ANDAR e A PESSOA VAI SUBIR E NÃO TEM NINGUEM PEDINDO PRA DESCER
      else if( (andaresParaAtender[2]==1) && (andaresParaEntregar2[0]==0) && (andaresIndoAtender2[0]==0)){
        para2(22);
      }
      //PRECISA PEGAR ALGUEM NESSE ANDAR e A PESSOA VAI DESCER E NÃO TEM NINGUEM PEDINDO PRA SUBIR
      else if( (andaresParaAtender[1]==1) && (andaresParaEntregar2[2]==0) && (andaresIndoAtender2[3]==0)){
        para2(21);
      }
    break;

    //ELEVADOR2 CHEGOU ANDAR 3
    case 5: 
      displayElevador2(3); 
      desligarIndicadores2(); 
      //andarAtualElevador2=3;
      //PRECISA ENTREGAR ALGUEM NESSE ANDAR OU ALGUEM CHAMOU NESSE ANDAR?
      //if(andaresParaEntregar2[2]==1||andaresParaAtender[3]==1){
        para2(3);
      //}
    break; 

    //CHAMOU EXTERNO ANDAR1
    case 6: 
      andaresParaAtender[0]=1;
    break; 
    //CHAMOU EXTERNO ANDAR2 DESCE
    case 7: 
      andaresParaAtender[1]=1;
    break; 
    //CHAMOU EXTERNO ANDAR2 SOBE
    case 8: 
      andaresParaAtender[2]=1;
    break; 
    //CHAMOU EXTERNO ANDAR3
    case 9: 
      andaresParaAtender[3]=1;
    break;       

    //ELEV1 MANDOU INTERNO ANDAR1
    case 10: 
      andaresParaEntregar1[0]=1;
    break;       
    //ELEV1 MANDOU INTERNO ANDAR2
    case 11: 
      andaresParaEntregar1[1]=1;
    break;       
    //ELEV1 MANDOU INTERNO ANDAR3
    case 12: 
      andaresParaEntregar1[2]=1;
    break;     


     //ELEV2 MANDOU INTERNO ANDAR1
    case 13: 
      andaresParaEntregar2[0]=1;
    break;       
    //ELEV2 MANDOU INTERNO ANDAR2
    case 14: 
      andaresParaEntregar2[1]=1;
    break;       
    //ELEV2 MANDOU INTERNO ANDAR3
    case 15: 
      andaresParaEntregar2[2]=1;
    break;       
  }
  /*
  if(andaresParaEntregar1[0]||andaresParaEntregar1[1]||andaresParaEntregar1[2])
    elevador1ocupado=1;
  }else{
    elevador1ocupado=0;
  }
  if(andaresParaEntregar2[0]||andaresParaEntregar2[1]||andaresParaEntregar2[2])
    elevador2ocupado=1;
  }else{
    elevador2ocupado=0;
  }
  */
  //ELEVADOR1
  if(millis()-timeElevator1>OpenTime){
    desligarIndicadores1(); 
    //Esta no primeiro
    if(andarAtualElevador1==1){
      //Precisa abrir a porta
      if(andaresParaEntregar1[0]==1||andaresParaAtender[0]==1){
        andaresIndoAtender1[0]=1;
        if(pressed[0])
          para1(1);
      }
      //precisa entregar no segundo ou terceiro
      else if(andaresParaEntregar1[1]==1||andaresParaEntregar1[2]==1){
        sobe1();
      }
      //Alguem chamou no segundo pra descer
      else if((andaresParaAtender[1]==1)&&(andaresIndoAtender2[1]==0)&&(andaresIndoAtender1[2]==0)){
        sobe1();
        andaresIndoAtender1[1]=1;
      }
      //Alguem chamou no segundo pra subir
      else if((andaresParaAtender[2]==1)&&(andaresIndoAtender2[2]==0)&&(andaresIndoAtender1[1]==0)){
        sobe1();
        andaresIndoAtender1[2]=1;
      }
      //Alguem chamou no terceiro
      else if((andaresParaAtender[3]==1)&&
              (andaresIndoAtender2[3]==0)&&
              (andarAtualElevador1==andarAtualElevador2)){
        sobe1();
        andaresIndoAtender1[3]=1;
      }
    }
    //Esta no segundo
    else if(andarAtualElevador1==2){
      if((andaresParaEntregar1[1]==1||andaresParaAtender[1]==1)&&andaresIndoAtender2[1]==0){
        andaresIndoAtender1[1]=1;
        if(pressed[1])
          para1(21);
      }
      else if(andaresParaAtender[2]==1&&andaresIndoAtender2[2]==0){
        andaresIndoAtender1[2]=1;
        if(pressed[1])
          para1(22);
      }
      //precisa entregar no primeiro
      else if(andaresParaEntregar1[0]==1){
        desce1();
      }
      //precisa entregar no terceiro
      else if(andaresParaEntregar1[2]==1){
        sobe1();
      }
      //Alguem chamou no primeiro
      else if((andaresParaAtender[0]==1)&&
              (andaresIndoAtender2[0]==0)&&
              (andarAtualElevador1<=andarAtualElevador2)){
        desce1();
        andaresIndoAtender1[0]=1;
      }
      //Alguem chamou no terceiro
      else if((andaresParaAtender[3]==1)&&
              (andaresIndoAtender2[3]==0)&&
              (andarAtualElevador1>=andarAtualElevador2)){
        sobe1();
        andaresIndoAtender1[3]=1;
      }
    }
    //Esta no terceiro
    else if(andarAtualElevador1==3){
      if(andaresParaEntregar1[2]==1||andaresParaAtender[3]==1){
        andaresIndoAtender1[3]=1;
        if(pressed[2])
          para1(3);
      }
       //precisa entregar no segundo ou terceiro
      else if((andaresParaEntregar1[0]==1)||(andaresParaEntregar1[1]==1)){
        desce1();
      }
      //Alguem chamou no segundo pra descer
      else if((andaresParaAtender[1]==1)&&(andaresIndoAtender2[1]==0)&&(andaresIndoAtender1[2]==0)){
        desce1();
        andaresIndoAtender1[1]=1;
      }
      //Alguem chamou no segundo pra subir
      else if((andaresParaAtender[2]==1)&&(andaresIndoAtender2[2]==0)&&(andaresIndoAtender1[1]==0)){
        desce1();
        andaresIndoAtender1[2]=1;
      }
      //Alguem chamou no primeiro
      else if((andaresParaAtender[0]==1)&&
              (andaresIndoAtender2[0]==0)&&
              (andarAtualElevador1==andarAtualElevador2)){
        desce1();
        andaresIndoAtender1[0]=1;
      }
    }
  }
  //ELEVADOR2
  if(millis()-timeElevator2>OpenTime){
    desligarIndicadores2(); 
    //Esta no primeiro
    if(andarAtualElevador2==1){
      //Alguem chamou no primeiro
      if(andaresParaEntregar2[0]==1||andaresParaAtender[0]==1){
        andaresIndoAtender2[0]=1;
        if(pressed[3])
          para2(1);
      }
      //precisa entregar no segundo ou terceiro
      else if((andaresParaEntregar2[1]==1)||(andaresParaEntregar2[2]==1)){
        sobe2();
      }
      //Alguem chamou no terceiro
      else if((andaresParaAtender[3]==1)&&(andaresIndoAtender1[3]==0)){
        sobe2();
        andaresIndoAtender2[3]=1;
      }
      //Alguem chamou no segundo pra descer
      else if((andaresParaAtender[1]==1)&&(andaresIndoAtender1[1]==0)&&(andaresIndoAtender2[2]==0)){
        sobe2();
        andaresIndoAtender2[1]=1;
      }
      //Alguem chamou no segundo pra subir
      else if((andaresParaAtender[2]==1)&&(andaresIndoAtender1[2]==0)&&(andaresIndoAtender2[1]==0)){
        sobe2();
        andaresIndoAtender2[2]=1;
      }
    }
    //Esta no segundo
    else if(andarAtualElevador2==2){
      //Alguem chamou no segundo
      if((andaresParaEntregar2[1]==1||andaresParaAtender[2]==1)&&andaresIndoAtender1[2]==0){
        andaresIndoAtender2[2]=1;
        if(pressed[4])
          para2(22);
      }
      else if(andaresParaAtender[1]==1&&andaresIndoAtender1[1]==0){
        andaresIndoAtender2[1]=1;
        if(pressed[4])
          para2(21);
      }
      //precisa entregar no primeiro
      else if(andaresParaEntregar2[0]==1){
        desce2();
      }
      //precisa entregar no terceiro
      else if(andaresParaEntregar2[2]==1){
        sobe2();
      }
      //Alguem chamou no terceiro
      else if((andaresParaAtender[3]==1)&&
              (andaresIndoAtender1[3]==0)&&
              (andarAtualElevador2>andarAtualElevador1)){
        sobe2();
        andaresIndoAtender2[3]=1;
      }
       //Alguem chamou no primeiro
      else if((andaresParaAtender[0]==1)&&
              (andaresIndoAtender1[0]==0)&&
              (andarAtualElevador2<andarAtualElevador1)){
        desce2();
        andaresIndoAtender2[0]=1;
      }
    }
    //Esta no terceiro
    else if(andarAtualElevador2==3){
      //Alguem chamou no terceiro
      if(andaresParaEntregar2[2]==1||andaresParaAtender[3]==1){
        andaresIndoAtender2[3]=1;
        if(pressed[5])
          para2(3);
      }
       //precisa entregar no segundo ou terceiro
      else if(andaresParaEntregar2[0]==1||andaresParaEntregar2[1]==1){
        desce2();
      }
       //Alguem chamou no primeiro
      else if((andaresParaAtender[0]==1)&&
              (andaresIndoAtender1[0]==0)){
        desce2();
        andaresIndoAtender2[0]=1;
      }
      //Alguem chamou no segundo pra subir
      else if((andaresParaAtender[2]==1)&&(andaresIndoAtender1[2]==0)&&(andaresIndoAtender2[1]==0)){
        desce2();
        andaresIndoAtender2[2]=1;
      }
      //Alguem chamou no segundo pra descer
      else if((andaresParaAtender[1]==1)&&(andaresIndoAtender1[1]==0)&&(andaresIndoAtender2[2]==0)){
        desce2();
        andaresIndoAtender2[1]=1;
      }
     
    }
  }


  //ELEVADOR1
  //Todos os andares estão com problema no fim de curso
  if(pressed[0]&&pressed[1]&&pressed[2]){
    if(x==0){
      erro1(1);
      x++;
    }else if(x==1){
      erro1(2);
      x++;
    }else{
      erro1(3);
      x=0;
    }
  }
  //Primeiro e Segundo estão com problema
  else if(pressed[0]&&pressed[1]){
    if(x==0){
      erro1(1);
      x++;
    }else{
      erro1(2);
      x=0;
    }
  }
  //Segundo e Terceiro estão com problema
  else if(pressed[1]&&pressed[2]){
    if(x==0){
      erro1(2);
      x++;
    }else{
      erro1(3);
      x=0;
    }
  }
  //Primeiro e Terceiro estão com problema
  else if(pressed[0]&&pressed[2]){ 
    if(x==0){
      erro1(1);
      x++;
    }else{
      erro1(3);
      x=0;
    }
  }
  //Problema resolvivo
  else if(pressed[0]&&justreleased[1]||
          pressed[1]&&justreleased[0]||
          pressed[0]&&justreleased[2]||
          pressed[2]&&justreleased[0]||
          pressed[1]&&justreleased[2]||
          pressed[2]&&justreleased[1]){
    zerarComandos(1);
    if(pressed[0]){
      para1(1);
    }else if(pressed[1]){
      para1(21);
      para1(22);
    }else if(pressed[2]){
      para1(3);
    }
  }
  //Nenhum fim de curso acionado
  if(!pressed[0]&&!pressed[1]&&!pressed[2]){
    desligarIndicadores1();
    if(parado1){
      switch (andarAtualElevador1) {
          case 1:
            sobe1();
            break;
          case 2:
            sobe1();
            break;
          case 3:
            desce1();
            break;
          default:
            break;
      }
    }
  }  
  //ELEVADOR2
  //Todos os andares estão com problema no fim de curso
  if(pressed[3]&&pressed[4]&&pressed[5]){
    if(y==0){
      erro2(1);
      y++;
    }
    else if(y==1){
      erro2(2);
      y++;
    }else{
      erro2(3);
      y=0;
    }
  }
  //Primeiro e Segundo estão com problema
  else if(pressed[3]&&pressed[4]){
    if(y==0){
      erro2(1);
      y++;
    }else{
      erro2(2);
      y=0;
    }
  }
  //Segundo e terceiro estão com problema
  else if(pressed[4]&&pressed[5]){
    if(y==0){
      erro2(2);
      y++;
    }else{
      erro2(3);
      y=0;
    }
  }
  //Primeiro e terceiro estão com problema
  else if(pressed[3]&&pressed[5]){ 
    if(y==0){
      erro2(1);
      y++;
    }else{
      erro2(3);
      y=0;
    }
  } 
  //Problema resolvivo
  else if(pressed[3]&&justreleased[4]||
          pressed[4]&&justreleased[3]||
          pressed[3]&&justreleased[5]||
          pressed[5]&&justreleased[3]||
          pressed[4]&&justreleased[5]||
          pressed[5]&&justreleased[4]){
    zerarComandos(2);
    if(pressed[3]){
      para2(1);
    }else if(pressed[4]){
       para2(21);
       para2(22);
    }else if(pressed[5]){
       para2(3);
    }
  }
  //Nenhum fim de curso acionado
  if(!pressed[3]&&!pressed[4]&&!pressed[5]){
    desligarIndicadores2();
    if(parado2){
      switch (andarAtualElevador2) {
          case 1:
            sobe2();
            break;
          case 2:
            sobe2();
            break;
          case 3:
            desce2();
            break;
          default:
            break;
      }
    }
  }  

  digitalWrite(led1Elev1, andaresParaEntregar1[0]);
  digitalWrite(led1Elev2, andaresParaEntregar1[1]);
  digitalWrite(led1Elev3, andaresParaEntregar1[2]);

  digitalWrite(led2Elev1, andaresParaEntregar2[0]);
  digitalWrite(led2Elev2, andaresParaEntregar2[1]);
  digitalWrite(led2Elev3, andaresParaEntregar2[2]);

  digitalWrite(ledExt1, andaresParaAtender[0]);
  digitalWrite(ledExt2, andaresParaAtender[1]);
  digitalWrite(ledExt3, andaresParaAtender[2]);
  digitalWrite(ledExt4, andaresParaAtender[3]);

}
 
void check_switches(){
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

void erro1(int andar){
  desligarIndicadores1();
  digitalWrite(subindo1, HIGH);
  digitalWrite(descendo1, HIGH);
  switch (andar) {
      case 1:
        displayElevador1(1);
        break;
      case 2:
        displayElevador1(2);
        break;
      case 3:
        displayElevador1(3);
        break;
      default:
         break;
  }
}

void erro2(int andar){
  desligarIndicadores2();
  digitalWrite(subindo2, HIGH);
  digitalWrite(descendo2, HIGH);

  switch (andar) {
      case 1:
        displayElevador2(1);
        break;
      case 2:
        displayElevador2(2);
        break;
      case 3:
        displayElevador2(3);
        break;
      default:
         break;
  }
}
void sobe1(){
  parado1=0;
  //ELEVADOR1
  digitalWrite(motor1a,HIGH);
  digitalWrite(motor1b, LOW);
  digitalWrite(subindo1, HIGH);
  digitalWrite(descendo1, LOW);
  desligarIndicadores1();
}
void sobe2(){
  parado2=0;
  //ELEVADOR2
  digitalWrite(motor2a,HIGH);
  digitalWrite(motor2b, LOW);
  digitalWrite(subindo2, HIGH);
  digitalWrite(descendo2, LOW);
  desligarIndicadores2();
}
void desce1(){
  parado1=0;
  //ELEVADOR1
  digitalWrite(motor1a,LOW);
  digitalWrite(motor1b,HIGH);
  digitalWrite(subindo1, LOW);
  digitalWrite(descendo1, HIGH);
  desligarIndicadores1();
}
void desce2(){
  parado2=0;
  //ELEVADOR2
  digitalWrite(motor2a,LOW);
  digitalWrite(motor2b,HIGH);
  digitalWrite(subindo2, LOW);
  digitalWrite(descendo2, HIGH);
  desligarIndicadores2();
}
void desligarIndicadores1(){
    digitalWrite(ind1porta1, LOW);
    digitalWrite(ind1porta2, LOW);
    digitalWrite(ind1porta3, LOW);
}
void desligarIndicadores2(){
    digitalWrite(ind2porta1, LOW);
    digitalWrite(ind2porta2, LOW);
    digitalWrite(ind2porta3, LOW);
}
void zerarComandos(int elevador){
  if(elevador==1){
    andaresParaEntregar1[0]=0;
    andaresParaEntregar1[1]=0;
    andaresParaEntregar1[2]=0;
    andaresParaAtender[0]=0;
    andaresParaAtender[1]=0;
    andaresParaAtender[2]=0;
    andaresParaAtender[3]=0;
  }else if(elevador==2){
    andaresParaEntregar2[0]=0;
    andaresParaEntregar2[1]=0;
    andaresParaEntregar2[2]=0;
    andaresParaAtender[0]=0;
    andaresParaAtender[1]=0;
    andaresParaAtender[2]=0;
    andaresParaAtender[3]=0;
  }
}
void para1(int andar){
  //ELEVADOR1
  parado1=1;
  timeElevator1 = millis();
  digitalWrite(motor1a,LOW);
  digitalWrite(motor1b,LOW);
  digitalWrite(subindo1, LOW);
  digitalWrite(descendo1, LOW);
  if(andar==1){
    if(andaresParaEntregar1[0]==1||andaresParaAtender[0]==1)
      digitalWrite(ind1porta1, HIGH);
    displayElevador1(1); 
    andarAtualElevador1=1;

    andaresParaEntregar1[0]=0;

    andaresParaAtender[0]=0;

    andaresIndoAtender1[0]=0;
  }else if(andar==21){
     if(andaresParaEntregar1[1]==1||andaresParaAtender[1]==1||andaresParaAtender[2]==1)
      digitalWrite(ind1porta2, HIGH);

    displayElevador1(2); 
    andarAtualElevador1=2;

    andaresParaEntregar1[1]=0;

    andaresParaAtender[1]=0;

    andaresIndoAtender1[1]=0;
   
  }else if(andar==22){
     if(andaresParaEntregar1[1]==1||andaresParaAtender[1]==1||andaresParaAtender[2]==1)
      digitalWrite(ind1porta2, HIGH);

    displayElevador1(2); 
    andarAtualElevador1=2;

    andaresParaEntregar1[1]=0;

    andaresParaAtender[2]=0;

    andaresIndoAtender1[2]=0;
   
  }else if(andar==3){
    if(andaresParaEntregar1[2]==1||andaresParaAtender[3]==1)
      digitalWrite(ind1porta3, HIGH);
    displayElevador1(3); 
    andarAtualElevador1=3;
    andaresParaEntregar1[2]=0;
    andaresParaAtender[3]=0;

    andaresIndoAtender1[3]=0;
  }
}
void para2(int andar){
  parado2=1;
  //ELEVADOR2
  timeElevator2 = millis();
  digitalWrite(motor2a,LOW);
  digitalWrite(motor2b,LOW);
  digitalWrite(subindo2, LOW);
  digitalWrite(descendo2, LOW);
  if(andar==1){
    if(andaresParaEntregar2[0]==1||andaresParaAtender[0]==1)
      digitalWrite(ind2porta1, HIGH);
    displayElevador2(1); 
    andarAtualElevador2=1;

    andaresParaEntregar2[0]=0;

    andaresParaAtender[0]=0;

    andaresIndoAtender2[0]=0;
  }else if(andar==21){
    if(andaresParaEntregar2[1]==1||andaresParaAtender[1]==1||andaresParaAtender[2]==1)
      digitalWrite(ind2porta2, HIGH);
    displayElevador2(2); 
    andarAtualElevador2=2;

    andaresParaEntregar2[1]=0;

    andaresParaAtender[1]=0;

    andaresIndoAtender2[1]=0;
  }else if(andar==22){
    if(andaresParaEntregar2[1]==1||andaresParaAtender[1]==1||andaresParaAtender[2]==1)
      digitalWrite(ind2porta2, HIGH);
    displayElevador2(2); 
    andarAtualElevador2=2;

    andaresParaEntregar2[1]=0;

    andaresParaAtender[2]=0;

    andaresIndoAtender2[2]=0;
  }else if(andar==3){
    if(andaresParaEntregar2[2]==1||andaresParaAtender[3]==1)
      digitalWrite(ind2porta3, HIGH);

    displayElevador2(3); 
    andarAtualElevador2=3;
    andaresParaEntregar2[2]=0;
    andaresParaAtender[3]=0;

    andaresIndoAtender2[3]=0;
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
void displayElevador2(int andar){
  switch (andar) {
      case 1:
        digitalWrite(DOISdisplay1, HIGH);
        digitalWrite(DOISdisplay2, LOW);
        break;
      case 2:
        digitalWrite(DOISdisplay1, LOW);
        digitalWrite(DOISdisplay2, HIGH);
        break;
      case 3:
        digitalWrite(DOISdisplay1, HIGH);
        digitalWrite(DOISdisplay2, HIGH);
        break;
      //Erro
      default:
        digitalWrite(DOISdisplay1, LOW);
        digitalWrite(DOISdisplay2, LOW);
  }
}