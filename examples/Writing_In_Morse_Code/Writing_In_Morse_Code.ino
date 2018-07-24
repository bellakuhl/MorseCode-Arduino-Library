#include <MorseCode.h>
#include <Servo.h>

// create morse code object
MorseCode morse;

void setup() {
  // initialize the servo on pin 4
  morse.init(4);
}

void loop() {
  morse.letter('H');
  morse.letter('I');
}
