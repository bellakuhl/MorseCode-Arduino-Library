/*
MorseCode.h - Library for writing in Morse code using servo on draw bot.
Created by Isabella Kuhl July 2018
Released into public domain
*/

#ifndef MorseCode_h
#define MorseCode_h

#include "Arduino.h"
#include "Servo.h"

class MorseCode {
  public:
    void init(int pin);
    void letter(char c);
    void dot();
    void dash();
  private:
    int _pin;
    Servo myservo;
};

#endif
