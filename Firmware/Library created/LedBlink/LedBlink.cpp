/*
   LedBlink.h - Library for blinking LED at different time period.
  Created by Yadukrishnan K M, December 23, 2021.
  Released into the public domain.
*/

#include "Arduino.h"
#include "LedBlink.h"

LedBlink::LedBlink(int ledPinNo) 
{
   ledPin = ledPinNo;
   pinMode(ledPin, OUTPUT);
}
void LedBlink::ledBlink (boolean ledStartState, unsigned long blinkPeriod) 
{

      if (ledBlinkPrgmCount == 0) {

        //Serial.println("in led blink prgm count 0");

        ledState = ledStartState;
        ledBlinkPrgmCount = ledBlinkPrgmCount + 1;
        digitalWrite(ledPin, ledState); // immediatly change led state
        previousMillis = millis();

       // Serial.println(ledBlinkPrgmCount);
      }

      currentMillis = millis();
      //Serial.println(currentMillis);

      if (currentMillis - previousMillis >= blinkPeriod) {
        previousMillis = currentMillis;

        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }

        digitalWrite(ledPin, ledState);

        //Serial.println(ledPin);
        //Serial.println(ledState);
      }

}

void LedBlink::cancelLedBlink (boolean ledStopState) 
{
    ledBlinkPrgmCount = 0;
    digitalWrite(ledPin, ledStopState);
}
