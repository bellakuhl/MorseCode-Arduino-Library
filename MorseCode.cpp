/*
MorseCode.h - Library for writing in Morse code using servo on draw bot.
Created by Isabella Kuhl July 2018
Released into public domain
*/

#include "Arduino.h"
#include "MorseCode.h"
#include <Servo.h>

//Servo myservo;

void MorseCode::init(int pin) {
  myservo.attach(pin);
  _pin = pin;
}

void MorseCode::dot() {
  myservo.write(65);
  delay(250);
  myservo.write(85);
  delay(250);
}

void MorseCode::dash() {
  myservo.write(65);
  delay(1000);
  myservo.write(85);
  delay(250);
}

void MorseCode::letter(char c) {
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
      break;
    case 'I':
      MorseCode::dot(); MorseCode::dot();
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
      break;
    default:
      MorseCode::dash();
      break;
    }
}
