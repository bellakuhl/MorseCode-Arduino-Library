// uses line finders and interrupts to run motors straight while spelling "me" (dash dash dot) with
// either servo, LED, or buzzer

#include <MorseCode.h>
#include <Servo.h>
#include "Grove_I2C_Motor_Driver.h"

// default I2C address is 0x0f
#define I2C_ADDRESS 0x0f

// create morse code object
MorseCode morse;

// set button pin
int buttonPin = 5;

void setup() {
  // initialize button as input
  pinMode(buttonPin, INPUT);

  // initialize the SERVO, LED, or BUZZER on pin 4 and the offset value as 7
  morse.initBuzzer(4, 7);
}

void loop() {
  // wait for button to be pressed
  if (digitalRead(buttonPin) == HIGH) {

    // The message to be translated and the power
    morse.translate("me", 45);

    // stop motors and wait again for button press
    Motor.stop(MOTOR1);
    Motor.stop(MOTOR2);
    return;
  }
}

