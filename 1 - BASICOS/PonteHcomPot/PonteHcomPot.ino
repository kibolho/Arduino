#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd (8, 9, 4, 5, 6, 7);
int in1 = 5;
int in2 = 3;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.clear();
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):

  // print the number of seconds since reset:
  int analogIn = analogRead(A1);
  Serial.println("Pot:");
  Serial.println(analogIn);
    lcd.setCursor(0, 1);
  lcd.print(analogIn);

  if(analogIn<450){
  	horario(map(analogIn,0,450,255,0));
  }else if(analogIn>550){
	antihorario(map(analogIn,550, 1023,0,255));
  }
}

void horario(int pwm){
      lcd.setCursor(0, 0);
        Serial.println("PWM");
    lcd.print(pwm);
	analogWrite(in2, pwm);
        analogWrite(in1, 0);
}
void antihorario(int pwm){
      lcd.setCursor(0, 0);
      Serial.println("PWM");
      lcd.print(pwm);
      analogWrite(in2, 0);
      analogWrite(in1, pwm);
}
