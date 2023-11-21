#include <RFremote.h>
 #include <IRremote.h> 
 
SignalPatternParams params;
RFrecv rfrecv;

char *code1 = "0110110100100100100100100100110110100110100110110110110110110100100110110100110100110";
char *code2 = "0110100110110100110110100100110100110100100110100100100110110110100100110100110100110";
char *code3 = "0110110100100100110110110100100110110110110110100110110110110100100110110100110100110";
char *code4 = "0"; //"0110110100100100100100100100110110100110100110110110110110110100100110100100110100110";
char *code5 = "0";  //"0110110100100100100100100100110110100110100110110110110110110100100100110100110100110";

//Buzzer
int sound = 4; //Alarm

int RECV_PIN = 10;  
 float armazenavalor; 
 
int led = 12;
int led2 = 11;

IRrecv irrecv(RECV_PIN);  
decode_results results;  
 
void setup()
{
   pinMode(led, OUTPUT);
     pinMode(led2, OUTPUT);
    pinMode(sound, OUTPUT);
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
  irrecv.enableIRIn(); // Inicializa o receptor IR  
}

void loop()
{
  if (irrecv.decode(&results))  
  {  
  Serial.print("Valor lido : ");  
  Serial.println(results.value, HEX); 
   armazenavalor = (results.value);  
  if (armazenavalor == 0) //Verifica se a tecla 1 foi pressionada  
  {  
             Serial.println(digitalRead(led2));
             if(digitalRead(led2)==0){
               digitalWrite(led2, HIGH);
             }else{
               digitalWrite(led2, LOW);
             }
             Serial.print("SOUND");  
        tone (sound, 400);
          delay (500);
          tone (sound, 1000);
          delay (500);
          noTone (sound);
  }
   irrecv.resume(); //Le o próximo valor  
  }
  if (rfrecv.available())
  {
    //Serial.println("RECEBIDO!");
    Serial.println((char*)rfrecv.cmd);
    char *code = (char*)rfrecv.cmd;
     //Serial.println(code);
      //Serial.println(code1);
    if(strcmp(code,code3)==0){
      Serial.println("3");
    }
     if(strcmp(code,code2)==0){
             Serial.println("2");
    }
     if(strcmp(code,code1)==0){
             Serial.println("1");
             //Serial.println(digitalRead(led2));
             if(digitalRead(led)==0){
               digitalWrite(led, HIGH);
             }else{
               digitalWrite(led, LOW);
             }
               
        tone (sound, 500);
          delay (500);
          tone (sound, 1000);
          delay (500);
          noTone (sound);
    }
     if(strcmp(code,code4)==0){
             Serial.println("4");
    }
     if(strcmp(code,code5)==0){
             Serial.println("5");
    }
    
  }
  
}

