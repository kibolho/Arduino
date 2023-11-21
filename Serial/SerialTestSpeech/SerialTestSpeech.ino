#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

void setup() {

  delay(3000);

  Serial.begin(115200);

  mySerial.begin(9600);
  mySerial.println("Hello there!");
}
void loop() {
   Serial.println("Hello there!");
   delay(5000);
}
