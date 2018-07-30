/*
MorseCode.cpp - Library for writing in Morse code using servo on draw bot which also checks the motor speeds.
Morse code can be written out with a drawing bot with a pen attached to a servo, an LED, or a buzzer
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

void MorseCode::initServo(int pin, int errorValue) {
  mode = 's';
  myservo.attach(pin);
  _pin = pin;
  error = errorValue;
  Motor.begin(I2C_ADDRESS);
  pinMode(encoderL,INPUT);
  pinMode(encoderR,INPUT);
  begin();
  myservo.write(65);
}

void MorseCode::initBuzzer(int pin, int errorValue) {
  mode = 'b';
  altpin = pin;
  pinMode(pin, OUTPUT);
  _pin = pin;
  error = errorValue;
  Motor.begin(I2C_ADDRESS);
  pinMode(encoderL,INPUT);
  pinMode(encoderR,INPUT);
  begin();
  digitalWrite(altpin, LOW);
}

void MorseCode::initLED(int pin, int errorValue) {
  mode = 'l';
  altpin = pin;
  pinMode(pin, OUTPUT);
  _pin = pin;
  error = errorValue;
  Motor.begin(I2C_ADDRESS);
  pinMode(encoderL,INPUT);
  pinMode(encoderR,INPUT);
  begin();
  digitalWrite(altpin, LOW);
}
  

void MorseCode::dot(char mode) {
 switch (mode) {
  case 'l':
    digitalWrite(altpin, HIGH);
    delay(DOT);
    digitalWrite(altpin, LOW);
    delay(INNER_PAUSE);
    MorseCode::drive(leftPower, rightPower); // call drive func to check that wheels are same speed
    break;
  case 'b':
    digitalWrite(altpin, HIGH);
    delay(500);
    digitalWrite(altpin, LOW);
    delay(500);  // need to use a longer delay for buzzer
    MorseCode::drive(leftPower, rightPower);
    break;
  case 's':
    myservo.write(85); // 85 puts pen down
    delay(DOT);
    myservo.write(65); // 65 is lifting pen up
    delay(INNER_PAUSE);
    MorseCode::drive(leftPower, rightPower);
    break;
 }
}

void MorseCode::dash(char mode) {
 switch (mode) {
  case 'l':
    digitalWrite(altpin, HIGH);
    delay(DASH);
    digitalWrite(altpin, LOW);
    delay(INNER_PAUSE);
    MorseCode::drive(leftPower, rightPower);
    break;
  case 'b':
    digitalWrite(altpin, HIGH);
    delay(1500);
    digitalWrite(altpin, LOW);
    delay(500);
    MorseCode::drive(leftPower, rightPower);
    break;
  case 's':
    myservo.write(85);
    delay(DASH);
    myservo.write(65);
    delay(INNER_PAUSE);
    MorseCode::drive(leftPower, rightPower);
    break;
 }
}

void MorseCode::translate(String sentence, int motorPower) {
 leftPower = motorPower;
 rightPower = motorPower;
 MorseCode::drive(leftPower, rightPower);
 for(char& c : sentence) { // runs through each letter of sentence
  c = toupper(c);
  switch (c) {
    case 'A':
      MorseCode::dot(mode); MorseCode::dash(mode);
      break;
    case 'B':
      MorseCode::dash(mode); MorseCode::dot(mode);
      MorseCode::dot(mode); MorseCode::dot(mode);
      break;
    case 'C':
      MorseCode::dash(mode); MorseCode::dot(mode);
      MorseCode::dash(mode); MorseCode::dot(mode);
      break;
    case 'D':
      MorseCode::dash(mode); MorseCode::dot(mode);
      MorseCode::dot(mode);
      break;
    case 'E':
      MorseCode::dot(mode);
      break;
    case 'F':
      MorseCode::dot(mode); MorseCode::dot(mode);
      MorseCode::dash(mode); MorseCode::dot(mode);
      break;
    case 'G':
      MorseCode::dash(mode); MorseCode::dash(mode);
      MorseCode::dot(mode);
      break;
    case 'H':
      MorseCode::dot(mode); MorseCode::dot(mode);
      MorseCode::dot(mode); MorseCode::dot(mode);
      break;
    case 'I':
      MorseCode::dot(mode); MorseCode::dot(mode);
      MorseCode::drive(leftPower, rightPower);
      break;
    case 'J':
      MorseCode::dot(mode); MorseCode::dash(mode);
      MorseCode::dash(mode); MorseCode::dash(mode);
      break;
    case 'K':
      MorseCode::dash(mode); MorseCode::dot(mode);
      MorseCode::dash(mode);
      break;
    case 'L':
      MorseCode::dot(mode); MorseCode::dash(mode);
      MorseCode::dot(mode);  MorseCode::dot(mode);
      break;
    case 'M':
      MorseCode::dash(mode); MorseCode::dash(mode);
      break;
    case 'N':
      MorseCode::dash(mode);  MorseCode::dot(mode);
      break;
    case 'O':
      MorseCode::dash(mode); MorseCode::dash(mode);
      MorseCode::dash(mode);
      break;
    case 'P':
      MorseCode::dot(mode); MorseCode::dash(mode);
      MorseCode::dash(mode);  MorseCode::dot(mode);
      break;
    case 'Q':
      MorseCode::dash(mode); MorseCode::dash(mode);
      MorseCode::dot(mode); MorseCode::dash(mode);
      break;
    case 'R':
      MorseCode::dot(mode); MorseCode::dash(mode);
      MorseCode::dot(mode);
      break;
    case 'S':
      MorseCode::dot(mode);  MorseCode::dot(mode);
      MorseCode::dot(mode);
      break;
    case 'T':
      MorseCode::dash(mode);
      break;
    case 'U':
      MorseCode::dot(mode);  MorseCode::dot(mode);
      MorseCode::dash(mode);
      break;
    case 'V':
      MorseCode::dot(mode);  MorseCode::dot(mode);
      MorseCode::dot(mode); MorseCode::dash(mode);
      break;
    case 'W':
      MorseCode::dot(mode); MorseCode::dash(mode);
      MorseCode::dash(mode);
      break;
    case 'X':
      MorseCode::dash(mode);  MorseCode::dot(mode);
      MorseCode::dot(mode); MorseCode::dash(mode);
      break;
    case 'Y':
      MorseCode::dash(mode);  MorseCode::dot(mode);
      MorseCode::dash(mode); MorseCode::dash(mode);
      break;
    case 'Z':
      MorseCode::dash(mode); MorseCode::dash(mode);
      MorseCode::dot(mode);  MorseCode::dot(mode);
      break;
    default:
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
