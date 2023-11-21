#include <Servo.h>
Servo gaucheAvant, gaucheArriere, droitAvant, droitArriere;

// Inicial Position of each Servo
int zeroDegreeGaucheAvant = 70;
int zeroDegreeGaucheArriere = 65;
int zeroDegreeDroitAvant = 90;
int zeroDegreeDroitArriere = 80;

// Fonction to have the ROVER rotating *********************************************************************************
void rotateGauche(int speed=100,int time=10000, int degree=45){
  
//Positioning Servo
gaucheAvant.write(zeroDegreeGaucheAvant-degree);
gaucheArriere.write(zeroDegreeGaucheArriere+degree);
droitAvant.write(zeroDegreeDroitAvant+degree);
droitArriere.write(zeroDegreeDroitArriere-degree);
delay(3000);

//SETUP MOTORS-------------------------------------------------
for (int i=8;i<=10;i++){//dir gauche
digitalWrite(i,HIGH);
}
for (int i=11;i<=13;i++){//dir droit
digitalWrite(i,HIGH);
}

//TURN ON MOTORS-------------------------------------------------
for (int i=2;i<=7;i++){//pwm
analogWrite(i,speed);
}
//Keep motors ON for TIME ms
delay(time);

//TURN OFF MOTORS-------------------------------------------------
for (int i=2;i<=7;i++){//pwm
analogWrite(i,0);
}
}

// Fonction to have the HOVER rotating*********************************************************************************
void rotateDroit(int speed=100,int time=10000, int degree=45){
  
//Positioning Servo-------------------------------------------------
gaucheAvant.write(zeroDegreeGaucheAvant-degree);
gaucheArriere.write(zeroDegreeGaucheArriere+degree);
droitAvant.write(zeroDegreeDroitAvant+degree);
droitArriere.write(zeroDegreeDroitArriere-degree);
delay(3000);

//SETUP MOTORS-------------------------------------------------
for (int i=8;i<=10;i++){//dir gauche
digitalWrite(i,LOW);

}
for (int i=11;i<=13;i++){//dir droit
digitalWrite(i,LOW);
}

//TURN ON MOTORS-------------------------------------------------
for (int i=2;i<=7;i++){//pwm
analogWrite(i,speed);
}

//Keep motors ON for TIME ms-------------------------------------------------
delay(time);

//TURN OFF MOTORS-------------------------------------------------
for (int i=2;i<=7;i++){//pwm
analogWrite(i,0);
}
}

//*********************************************************************************
void rotateZero(){
  
//Positioning Servo-------------------------------------------------
gaucheAvant.write(zeroDegreeGaucheAvant);
gaucheArriere.write(zeroDegreeGaucheArriere);
droitAvant.write(zeroDegreeDroitAvant);
droitArriere.write(zeroDegreeDroitArriere);
delay(1000);
}

//*********************************************************************************
void left(int degree=45){
  
//Positioning Servo-------------------------------------------------
gaucheAvant.write(zeroDegreeGaucheAvant+degree);
gaucheArriere.write(zeroDegreeGaucheArriere-degree);
droitAvant.write(zeroDegreeDroitAvant+degree);
droitArriere.write(zeroDegreeDroitArriere-degree);
}

//*********************************************************************************
void right(int degree=45){
  
//Positioning Servo-------------------------------------------------
gaucheAvant.write(zeroDegreeGaucheAvant-degree);
gaucheArriere.write(zeroDegreeGaucheArriere+degree);
droitAvant.write(zeroDegreeDroitAvant-degree);
droitArriere.write(zeroDegreeDroitArriere+degree);
}

//*********************************************************************************
void backward(int speed=100,int time=10000){
  
//SETUP MOTORS-------------------------------------------------
for (int i=8;i<=10;i++){//dir gauche
digitalWrite(i,HIGH);
}
for (int i=11;i<=13;i++){//dir droit
digitalWrite(i,LOW);
}

//TURN ON MOTORS-------------------------------------------------
for (int i=2;i<=7;i++){//pwm
file:///C|/Users/Pascal/AppData/Local/Temp/MainSoftware.ino.txt[02/11/2017 18:28:17]
analogWrite(i,speed);
}

//Keep motors ON for TIME ms-------------------------------------------------
delay(time);

//TURN OFF MOTORS-------------------------------------------------
for (int i=2;i<=7;i++){//pwm
analogWrite(i,0);
}
}

//*********************************************************************************
void forward(int speed=100,int time=10000){
  
//SETUP MOTORS-------------------------------------------------
for (int i=8;i<=10;i++){//dir gauche
digitalWrite(i,LOW);
}
for (int i=11;i<=13;i++){//dir droit
digitalWrite(i,HIGH);
}

//TURN ON MOTORS-------------------------------------------------
for (int i=2;i<=7;i++){//pwm
analogWrite(i,speed);
}

//Keep motors ON for TIME ms-------------------------------------------------
delay(time);//mÃªme vitesse pendant time secondes

//TURN OFF MOTORS-------------------------------------------------
for (int i=2;i<=7;i++){//pwm
analogWrite(i,0);
}
}

//*********************************************************************************
void setup(){
  
// CONFIGURE SERVOS-------------------------------------------------
gaucheAvant.attach(29);
gaucheArriere.attach(28);
droitAvant.attach(30);
droitArriere.attach(31);
gaucheAvant.write(0);
gaucheArriere.write(0);
droitAvant.write(0);
droitArriere.write(0);

// CONFIGURE MOTORS-------------------------------------------------
for (int i=2;i<=7;i++){//pwm
pinMode(i,OUTPUT);}

for (int i=22;i<=27;i++){//GND
pinMode(i,OUTPUT);
digitalWrite(i,LOW);}

for (int i=8;i<=13;i++){//dir
pinMode(i,OUTPUT);}
}

void loop(){
// POSICAO INICIAL SERVOS
//rotateZero();
//ROTATE
//rotateGauche(100,10000,45);
//rotateDroit(150,10000,45);
//TEST FORWARD
//forward(250,10000);//PWM MAXIMO
//TEST BACKWARD
//backward(250,10000);
// POSICAO ROTATE SERVOS
//TEST RIGHT
//right(45); // SPEED (0-100), TIME (ms) and DEGREES (0-80);
//forward(250,10000); // SPEED (0-100), TIME (ms).
//TEST LEFT
//left(45); //DEGREES (0-80);
//forward(250,10000); // SPEED (0-100), TIME (ms).
//TRAJET00000
//rotateDroit(250,40000,45);
//rotateDroit(250,6000,45);
//rotateZero!();
//delay(1000);
//forward(250,10000);//PWM MAXIMO
//rotateDroit(250,13000,45);
rotateZero();
forward(250,10000);//PWM MAXIMO
delay(3000);
//rotateZero();
//delay(2000);
//forward(250,10000);//PWM MAXIMO
//backward(250,10000);
//right(45); // SPEED (0-100), TIME (ms) and DEGREES (0-80);
//forward(250,10000); // SPEED (0-100), TIME (ms).
//left(45); //DEGREES (0-80);
//forward(250,10000); // SPEED (0-100), TIME (ms).
}
