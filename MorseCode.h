/*
MorseCode.h - Library for writing in Morse code using servo on draw bot which also checks the motor speeds.
Created by Isabella Kuhl July 2018
Released into public domain
*/

#ifndef MorseCode_h
#define MorseCode_h

#include "Arduino.h"
#include "Servo.h"
#include "Grove_I2C_Motor_Driver.h"

void begin();
void countLeft();
void countRight();
static int lcount;
static int rcount;
static int leftPower;
static int rightPower;
static int error;

class MorseCode {
  public:
    void init(int pin, int errorValue);
    void translate(String sentence, int motorPower);
    void dot();
    void dash();
    void drive(int leftPower, int rightPower);
    void countLeft();
    void countRight();

    static const int encoderL = 3;
    static const int encoderR = 2;
    volatile unsigned int encoderLPos = 1;
    volatile unsigned int encoderRPos = 0;
  private:
    int _pin;
    Servo myservo;
};

#endif
