#include <SoftwareSerial.h>

SoftwareSerial Laser(7,8);//RX TX
char b;
char c;

void setup() {
  Serial.begin(9600);
  Laser.begin(19200);
  Serial.println("Arduino A : je suis pret a recevoir/emettre");
}

void loop() {
  if (Serial.available()) {
    b=Serial.read();
    Laser.print(b);}

  if (Laser.available()) {
    c=Laser.read();
    Serial.print(c);}
}
