#include <RFremote.h>

SignalPatternParams params;
RFrecv rfrecv;

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
      Serial.println("1");
  }
  
}

