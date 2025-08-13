/*
  LedBlink.h - Library for blinking LED at different time period.
  Created by Yadukrishnan K M, December 23, 2021.
  Released into the public domain.
*/
#ifndef LedBlink_h
#define LedBlink_h

#include "Arduino.h"

class LedBlink
{
  public:
    LedBlink(int ledPinNo);
    void ledBlink(boolean ledStartState, unsigned long blinkPeriod);
    void cancelLedBlink(boolean ledStopState);
  private:
    int ledBlinkPrgmCount = 0;
    boolean ledState;
    unsigned long previousMillis;
    unsigned long currentMillis;
    int ledPin;
};

#endif