#include <Flasher.h>

int ledPin = 13;
int slowDuration = 300;
int fastDuration = 100;

Flasher slowFlasher(ledPin, slowDuration);
Flasher fastFlasher(ledPin, fastDuration);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  slowFlasher.flash(5);
  delay(1000);
  fastFlasher.flash(10);
  delay(1000);
}
