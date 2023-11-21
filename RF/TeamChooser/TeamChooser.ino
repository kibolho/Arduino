#include <RFremote.h>

SignalPatternParams params;
RFrecv rfrecv;

char *code1 = "0110110100100100100100100100110110100110100110110110110110110100100110110100110100110";
char *code2 = "0110100110110100110110100100110100110100100110100100100110110110100100110100110100110";
char *code3 = "0110110100100100110110110100100110110110110110100110110110110100100110110100110100110";
char *code4 = "0"; //"0110110100100100100100100100110110100110100110110110110110110100100110100100110100110";
char *code5 = "0";  //"0110110100100100100100100100110110100110100110110110110110110100100100110100110100110";

void setup()
{
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  
  Serial.begin(9600);
  delay(500);
  Serial.println("INICIADO!");
  
   
  /* EMTECO remote
  params.spaceMin = 4500;
  params.spaceMax = 4800;
  params.dotMin = 300;
  params.dotMax = 400;
  params.traceMin = 650;
  params.traceMax = 750;
  params.skipFirst = 1;
  params.skipLast = 1;
  */
  
  
  /* PPA TOK
  params.spaceMin = 10000;
  params.spaceMax = 15000;
  params.dotMin = 450;
  params.dotMax = 550;
  params.traceMin = 950;
  params.traceMax = 1050;
  params.skipFirst = 0;
  params.skipLast = 0;
  */
// Padrao
  params.spaceMin = 10000;
  params.spaceMax = 13000;
  params.dotMin = 400;
  params.dotMax = 600;
  params.traceMin = 850;
  params.traceMax = 1050;
  params.skipFirst = 0;
  params.skipLast = 0;
  
  rfrecv = RFrecv(&params);
  rfrecv.begin();
}

void loop()
{
  if (rfrecv.available())
  {
    //Serial.println("RECEBIDO!");
    Serial.println((char*)rfrecv.cmd);
    char *code = (char*)rfrecv.cmd;
     //Serial.println(code);
      //Serial.println(code1);
    if(strcmp(code,code1)==0){
      Serial.println("1");
    }
     if(strcmp(code,code2)==0){
             Serial.println("2");
    }
     if(strcmp(code,code3)==0){
             Serial.println("3");
    }
     if(strcmp(code,code4)==0){
             Serial.println("4");
    }
     if(strcmp(code,code5)==0){
             Serial.println("5");
    }
    
  }
  
}

