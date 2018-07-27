/*
MorseCode.h - Library for writing in Morse code using servo on draw bot which also checks the motor speeds.
Morse code can be written out with a drawing bot with a pen attached to a servo, an LED, or a buzzer
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
static char mode;
static int altpin;

class MorseCode {
  public:
    void initServo(int pin, int errorValue);
    void initBuzzer(int pin, int errorValue);
    void initLED(int altpin, int errorValue);
    void translate(String sentence, int motorPower);
    void dot(char mode);
    void dash(char mode);
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
