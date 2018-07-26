/*
MorseCode.h - Library for writing in Morse code using servo on draw bot which also checks the motor speeds.
Created by Isabella Kuhl July 2018
Released into public domain
*/

#include "Arduino.h"
#include "MorseCode.h"
#include <Servo.h>
#include "Grove_I2C_Motor_Driver.h"


#define DOT 75           // Duration of a dot
#define DASH 375         // Duration of a dash
#define INNER_PAUSE 125  // Duration of pause between dot and dash in a character 
#define CHAR_BREAK 250   // Duration of pause between characters
#define WORD_BREAK 375   // Duration of pause between words (spaces, punctuation, etc)

#define LEFT MOTOR2      // Change if motor orientation is different
#define RIGHT MOTOR1

// default I2C address is 0x0f
#define I2C_ADDRESS 0x0f

void countLeft() {
  lcount++;
}

void countRight() {
  rcount++;
}

void begin() {
  attachInterrupt(1, countLeft, CHANGE);
  attachInterrupt(0, countRight, CHANGE);
}

void MorseCode::init(int pin, int errorValue) {
  myservo.attach(pin);
  _pin = pin;
  error = errorValue;
  Motor.begin(I2C_ADDRESS);
  pinMode(encoderL,INPUT);
  pinMode(encoderR,INPUT);
  begin();
  myservo.write(65);
}

void MorseCode::dot() {
  myservo.write(85);
  delay(DOT);
  myservo.write(65);
  delay(INNER_PAUSE);
}

void MorseCode::dash() {
  myservo.write(85);
  delay(DASH);
  myservo.write(65);
  delay(INNER_PAUSE);
}

void MorseCode::translate(String sentence, int motorPower) {
 leftPower = motorPower;
 rightPower = motorPower;
 MorseCode::drive(leftPower, rightPower);
 for(char& c : sentence) {
  c = toupper(c);
  switch (c) {
    case 'A':
      MorseCode::dot(); MorseCode::dash();
      break;
    case 'B':
      MorseCode::dash(); MorseCode::dot();
      MorseCode::dot(); MorseCode::dot();
      break;
    case 'C':
      MorseCode::dash(); MorseCode::dot();
      MorseCode::dash(); MorseCode::dot();
      break;
    case 'D':
      MorseCode::dash(); MorseCode::dot();
      MorseCode::dot();
      break;
    case 'E':
      MorseCode::dot();
      break;
    case 'F':
      MorseCode::dot(); MorseCode::dot();
      MorseCode::dash(); MorseCode::dot();
      break;
    case 'G':
      MorseCode::dash(); MorseCode::dash();
      MorseCode::dot();
      break;
    case 'H':
      MorseCode::dot(); MorseCode::dot();
      MorseCode::dot(); MorseCode::dot();
      MorseCode::drive(leftPower, rightPower);
      break;
    case 'I':
      MorseCode::dot(); MorseCode::dot();
      MorseCode::drive(leftPower, rightPower);
      break;
    case 'J':
      MorseCode::dot(); MorseCode::dash();
      MorseCode::dash(); MorseCode::dash();
      break;
    case 'K':
      MorseCode::dash(); MorseCode::dot();
      MorseCode::dash();
      break;
    case 'L':
      MorseCode::dot(); MorseCode::dash();
      MorseCode::dot();  MorseCode::dot();
      break;
    case 'M':
      MorseCode::dash(); MorseCode::dash();
      break;
    case 'N':
      MorseCode::dash();  MorseCode::dot();
      break;
    case 'O':
      MorseCode::dash(); MorseCode::dash();
      MorseCode::dash();
      break;
    case 'P':
      MorseCode::dot(); MorseCode::dash();
      MorseCode::dash();  MorseCode::dot();
      break;
    case 'Q':
      MorseCode::dash(); MorseCode::dash();
      MorseCode::dot(); MorseCode::dash();
      break;
    case 'R':
      MorseCode::dot(); MorseCode::dash();
      MorseCode::dot();
      break;
    case 'S':
      MorseCode::dot();  MorseCode::dot();
      MorseCode::dot();
      break;
    case 'T':
      MorseCode::dash();
      break;
    case 'U':
      MorseCode::dot();  MorseCode::dot();
      MorseCode::dash();
      MorseCode::drive(leftPower, rightPower);
      break;
    case 'V':
      MorseCode::dot();  MorseCode::dot();
      MorseCode::dot(); MorseCode::dash();
      break;
    case 'W':
      MorseCode::dot(); MorseCode::dash();
      MorseCode::dash();
      break;
    case 'X':
      MorseCode::dash();  MorseCode::dot();
      MorseCode::dot(); MorseCode::dash();
      break;
    case 'Y':
      MorseCode::dash();  MorseCode::dot();
      MorseCode::dash(); MorseCode::dash();
      break;
    case 'Z':
      MorseCode::dash(); MorseCode::dash();
      MorseCode::dot();  MorseCode::dot();
      MorseCode::drive(leftPower, rightPower);
      break;
    default:
      myservo.write(65);
      MorseCode::drive(leftPower, rightPower);
      break;
   }
   delay(CHAR_BREAK);
}
}

// function to move robot forward or backward
void MorseCode::drive(int leftPower, int rightPower) {

  // variables to save tick counts
  long prevLcount, prevRcount, lDiff, rDiff;

  // Reset the tick counts to zero each time
  lcount = 0;
  rcount = 0;
    
    Motor.speed(LEFT, leftPower);   
    Motor.speed(RIGHT, rightPower);
    
    // Calculates the difference in previous and current tick counts
    lDiff = (lcount - prevLcount);
    rDiff = (rcount - prevRcount);
  
    // Saves the current tick count
    prevLcount = lcount;
    prevRcount = rcount;
  
    // if power is positive...
    if (leftPower > 0) {
  
      // If right motor is slow, it adds the error to the right motor power
      // and slows down the left motor
      if (lDiff > rDiff) {
        leftPower = leftPower - error;
        rightPower = rightPower + error;
      }
      
      // If left motor is slow, it adds the error to the left motor power
      // and slows down the right motor
      else if (lDiff < rDiff) {
        leftPower = leftPower + error;
        rightPower = rightPower - error;
      }
    }
    // if motor power is negative, do the opposite operations
    if (leftPower < 0) {
      if (lDiff > rDiff) {
        leftPower = leftPower + error;
        rightPower = rightPower - error;
      }
      else if (lDiff < rDiff) {
        leftPower = leftPower - error;
        rightPower = rightPower + error;
      }
    }
    Motor.speed(LEFT, leftPower);   
    Motor.speed(RIGHT, rightPower);
    // Give the motors a chance to respond   
    delay(50);
}
