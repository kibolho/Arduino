char b;
char c;

void setup() {
  Serial.begin(9600);
  Serial2.begin(19200);
  Serial.println("Arduino A : je suis pret a recevoir/emettre");
}

void loop() {
  if (Serial.available()) {
    b=Serial.read();
    Serial2.print(b); //'D'
   }

  if (Serial2.available()) {
    c=Serial2.read();
    Serial.print(c);
    }
}
