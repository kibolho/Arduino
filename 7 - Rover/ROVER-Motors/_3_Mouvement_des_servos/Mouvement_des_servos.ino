#include <Servo.h>
Servo gaucheAvant, gaucheArriere, droitAvant, droitArriere;

// Inicial Position of each Servo
int zeroDegreeGaucheAvant = 70;
int zeroDegreeGaucheArriere = 65;
int zeroDegreeDroitAvant = 90;
int zeroDegreeDroitArriere = 80;

void setup() {
  // put your setup code here, to run once:
// CONFIGURE SERVOS-------------------------------------------------
gaucheAvant.attach(29);
gaucheArriere.attach(28);
droitAvant.attach(30);
droitArriere.attach(31);

}

void loop() {
  // put your main code here, to run repeatedly:

gaucheAvant.write(20);
delay(1000);
gaucheAvant.write(40);
delay(1000);
gaucheAvant.write(60);
delay(1000);
gaucheAvant.write(80);
delay(1000);

droitAvant.write(20);
delay(1000);
droitAvant.write(40);
delay(1000);
droitAvant.write(60);
delay(1000);
droitAvant.write(80);
delay(1000);

gaucheArriere.write(20);
delay(1000);
gaucheArriere.write(40);
delay(1000);
gaucheArriere.write(60);
delay(1000);
gaucheArriere.write(80);
delay(1000);

droitArriere.write(20);
delay(1000);
droitArriere.write(40);
delay(1000);
droitArriere.write(60);
delay(1000);
droitArriere.write(80);
delay(1000);

}
