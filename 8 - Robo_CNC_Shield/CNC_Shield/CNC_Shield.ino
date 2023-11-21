#define EN        8  

//Direction pin
#define X_DIR     5 
#define Y_DIR     6
#define Z_DIR     7
#define A_DIR     12 
//Step pin
#define X_STP     2
#define Y_STP     3 
#define Z_STP     4 
#define A_STP     13


//DRV8825
int delayTime=2000; //Delay between each pause (uS)
int stps=400;// Steps to move


void step(boolean dir, byte dirPin, byte stepperPin, int steps)

{

  digitalWrite(dirPin, dir);

  delay(100);

  for (int i = 0; i < steps; i++) {

    digitalWrite(stepperPin, HIGH);

    delayMicroseconds(delayTime); 

    digitalWrite(stepperPin, LOW);

    delayMicroseconds(delayTime); 

  }

}

void setup(){

  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);

  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);

  pinMode(Z_DIR, OUTPUT); pinMode(Z_STP, OUTPUT);
  
  //pinMode(A_DIR, OUTPUT); pinMode(A_STP, OUTPUT);

  pinMode(EN, OUTPUT);

  digitalWrite(EN, LOW);

}

void loop(){
  step(false, X_DIR, X_STP, stps); //Y, Clockwise
  step(false, Y_DIR, Y_STP, stps); //Y, Clockwise
  step(false, Z_DIR, Z_STP, stps); //Y, Clockwise
    digitalWrite(EN, HIGH);
  delay(1000);
 digitalWrite(EN, LOW);
  step(true, X_DIR, X_STP, stps); //Y, Counterclockwise
  step(true, Y_DIR, Y_STP, stps); //Y, Clockwise
  step(true, Z_DIR, Z_STP, stps); //Y, Clockwise
  digitalWrite(EN, HIGH);
  delay(1000);
 digitalWrite(EN, LOW);
}
