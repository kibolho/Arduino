#define PINO_ZC 2
#define PINO_DIM 9

volatile long luminosidade = 0;  // 0 a 100 
 
void zeroCross()  {
  if (luminosidade>100) luminosidade=100;
  if (luminosidade<0) luminosidade=0;
  long t1 = 8200L * (100L - luminosidade) / 100L;      
  delayMicroseconds(t1);   
  digitalWrite(PINO_DIM, HIGH);  
  delayMicroseconds(6);      // t2
  if (luminosidade<100)
  digitalWrite(PINO_DIM, LOW);   
}
 
void setup() {
  pinMode(PINO_DIM, OUTPUT);
  attachInterrupt(0, zeroCross, RISING);
}
 
void loop() {
  for (byte i=0; i<100; i++) {
    luminosidade=i;
    delay(150);     
  }
   for (byte i=100; i>0; i--) {
    luminosidade=i;
    delay(150);     
  }
}
