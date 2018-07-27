// this code simply runs through preset drawing images - circle, square, and spiral

#include "Grove_I2C_Motor_Driver.h"
#include <Servo.h>

// default I2C address is 0x0f
#define I2C_ADDRESS 0x0f

int buttonPin = 5;

Servo servo;

void setup() {
  servo.attach(4);
  Motor.begin(I2C_ADDRESS);
  pinMode(buttonPin, INPUT);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    delay(500);
    circle();
    delay(2000);
    square();
    delay(2000);
    spiral();
    delay(2000);
  }

}

void circle() {
  servo.write(85);
  Motor.speed(MOTOR1, 50);
  delay(2200);
  Motor.stop(MOTOR1);
  servo.write(65);
}

void square() {
  for (int i = 0; i <= 3; i++) {
    // put down pen, draw first side of square
    servo.write(85);
    Motor.speed(MOTOR1, 40);
    Motor.speed(MOTOR2, 40);
    delay(800);
    Motor.stop(MOTOR1);
    Motor.stop(MOTOR2);
    delay(1000);
    
    // lift up pen, turn, and put pen back down
    servo.write(65);
    Motor.speed(MOTOR1, 50);
    delay(450);
    Motor.stop(MOTOR1);
    delay(1000);
  }
 // put pen up 
 servo.write(65);
}

void spiral() {
  // put pen down
  servo.write(85);
  for (int n = 0; n <= 5; n++) {
    Motor.speed(MOTOR1, 50);
    delay(2200);
    Motor.speed(MOTOR2, 50);
    delay(100);
    Motor.stop(MOTOR2);
  }
  Motor.stop(MOTOR1);
  // put pen up 
  servo.write(65);
}

