

/*..
   ....................................................................................................................................................................................

   ...................................................... LED Blinking class for blinking LED using millis fuction..................................................................
    ..................................................................Created by Yadukrishnan K M ................................................................................
      ....................................................................... Kerala, India....................................................................................
       .......................................................................... 23/12/2021..................................................................................

    ledStartState = starting state of led in boolean
    blinkPeriod = on time or off time in milliseconds
    ledPinNo = pin number of led in intiger
    ledStopState = define led on or off at ending of blinking in boolean

    calling exmple for this class.............................
    Ledblink led1; it is outside setup and loop
    led1.ledBlink(LOW,200,20; or led1.cancelLedBlink(LOW); inside setup or loop

*/

class Ledblink
{
    int ledBlinkPrgmCount = 0;
    boolean ledState;
    unsigned long previousMillis;
    unsigned long currentMillis;
    int ledPin;

  public:
    Ledblink(int ledPinNo) {
      ledPin = ledPinNo;
      pinMode(ledPin, OUTPUT);
    }
    void ledBlink (boolean ledStartState, unsigned long blinkPeriod) {

      if (ledBlinkPrgmCount == 0) {

        //Serial.println("in led blink prgm count 0");

        ledState = ledStartState;
        ledBlinkPrgmCount = ledBlinkPrgmCount + 1;
        digitalWrite(ledPin, ledState); // immediatly change led state
        previousMillis = millis();

       // Serial.println(ledBlinkPrgmCount);
      }

      currentMillis = millis();
      Serial.println(currentMillis);

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

    void cancelLedBlink (boolean ledStopState) {
      ledBlinkPrgmCount = 0;
      digitalWrite(ledPin, ledStopState);
    }

};

//   sample code for testing

/*
  Ledblink led1(32);

  void setup() {

  }
  void loop() {
  if (20000 <= millis()) {
    led1.cancelLedBlink(HIGH);
  }
  else led1.ledBlink(HIGH, 600);
  }*/
