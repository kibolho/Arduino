
#include <Servo.h>

Servo gaucheAvant, gaucheArriere, droitAvant, droitArriere; 
 
// Inicial Position of each Servo
int zeroDegreeGaucheAvant = 70; 
int zeroDegreeGaucheArriere = 65;
int zeroDegreeDroitAvant = 90;
int zeroDegreeDroitArriere = 80;

// Fonction to have the HOVER rotating 
void rotate(int speed=100,int time=1000, int degree=45){

  //Positioning Servo
  gaucheAvant.write(zeroDegreeGaucheAvant+degree);
  gaucheArriere.write(zeroDegreeGaucheArriere-degree);
  droitAvant.write(zeroDegreeDroitAvant+degree);
  droitArriere.write(zeroDegreeDroitArriere-degree);

  //SETUP MOTORS
  speed = 2,54*speed;
   for (int i=8;i<=10;i++){//dir gauche 
    digitalWrite(i,HIGH);
  }      
   for (int i=11;i<=13;i++){//dir droit
    digitalWrite(i,HIGH);
  }     

   //TURN ON MOTORS
  for (int i=2;i<=7;i++){//pwm
   analogWrite(i,speed);
  }
  //Keep motors ON for TIME ms
  delay(time);

   //TURN OFF MOTORS
  for (int i=2;i<=7;i++){//pwm
    analogWrite(i,0);
  }
}

void left(int degree=45){
  //Positioning Servo
  gaucheAvant.write(zeroDegreeGaucheAvant+degree);
  gaucheArriere.write(zeroDegreeGaucheArriere+degree);
  droitAvant.write(zeroDegreeDroitAvant+degree);
  droitArriere.write(zeroDegreeDroitArriere+degree);
}
void right(int degree=45){
   //Positioning Servo
  gaucheAvant.write(zeroDegreeGaucheAvant-degree);
  gaucheArriere.write(zeroDegreeGaucheArriere-degree);
  droitAvant.write(zeroDegreeDroitAvant-degree);
  droitArriere.write(zeroDegreeDroitArriere-degree);
}

void backward(int speed=100,int time=10000){
  //SETUP MOTORS
  speed = 2,55*speed;
   for (int i=8;i<=10;i++){//dir gauche 
    digitalWrite(i,HIGH);
  }      
   for (int i=11;i<=13;i++){//dir droit
    digitalWrite(i,LOW);
  }        

  //TURN ON MOTORS
  for (int i=2;i<=7;i++){//pwm
   analogWrite(i,speed);
  }
  //Keep motors ON for TIME ms
  delay(time);

  //TURN OFF MOTORS
  for (int i=2;i<=7;i++){//pwm
    analogWrite(i,0);
  }
}
void forward(int speed=100,int time=10000){
   //SETUP MOTORS
  speed = 2,55*speed;
   for (int i=8;i<=10;i++){//dir gauche 
    digitalWrite(i,LOW);
  }      
   for (int i=11;i<=13;i++){//dir droit
    digitalWrite(i,HIGH);
  }        
   //TURN ON MOTORS
  for (int i=2;i<=7;i++){//pwm
   analogWrite(i,speed);
  }
  //Keep motors ON for TIME ms
  delay(time);//même vitesse pendant time secondes

   //TURN OFF MOTORS
  for (int i=2;i<=7;i++){//pwm
    analogWrite(i,0);
  }
}



void setup(){

  // CONFIGURE SERVOS
  gaucheAvant.attach(28);
  gaucheArriere.attach(29);
  droitAvant.attach(30);
  droitArriere.attach(31); 
  gaucheAvant.write(0);
  gaucheArriere.write(0);
  droitAvant.write(0);
  droitArriere.write(0);

  
  // CONFIGURE MOTORS
  for (int i=2;i<=7;i++){//pwm
    pinMode(i,OUTPUT);
  }
  for (int i=22;i<=27;i++){//GND
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
  for (int i=8;i<=13;i++){//dir
    pinMode(i,OUTPUT);
  }
}

void loop(){
  // POSICAO INICIAL SERVOS
  rotate(100,10000,45); // SPEED (0-100), TIME (ms) and DEGREES (0-80);
  //right(45); //DEGREES (0-80);
  //left(45);   //DEGREES (0-80);
  //delay(1000);
  forward(100,10000); // SPEED (0-100), TIME (ms).
}

