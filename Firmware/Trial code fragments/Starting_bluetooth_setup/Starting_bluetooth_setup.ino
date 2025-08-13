#include <LedBlink.h>
#include "BluetoothSerial.h" //Header File for Serial Bluetooth, will be added by default into Arduino
#include <EEPROM.h>
#include <ESP32Ping.h>
#include "WiFi.h"
BluetoothSerial ESP_BT; //Object for Bluetooth

#define btLedPin 32
#define wifiLedPin 33
#define internetLedPin 35
#define firebaseLedPin 34
#define btButtonPin 13

// variables from btled timeout
unsigned long btButtonStartMillis;

// variables from settings
String bufferIn;
String bufferConfirmYesValue;
byte val;
int addr = 0;

// variables from eeprom reading
String Ssid;
String Password;

LedBlink btLed(btLedPin);
LedBlink wifiLed(wifiLedPin);
LedBlink internetLed(internetLedPin);
LedBlink firebaseLed(firebaseLedPin);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  EEPROM.begin(50);//Start Serial monitor in 9600
  Serial.println("Welcome to Xiotas Solar Dryer Automation Project");
  btLed.cancelLedBlink(HIGH);
  Serial.println("Press the button within 10 seconds to enter into settings");
  Serial.println("Otherwise it will atomatically exit and device will start booting");
  pinMode(btButtonPin, INPUT_PULLUP);
  btButtonStartMillis = millis();
  while (!btButton() == true) {
    boolean btButtonState = digitalRead(btButtonPin);
    if (btButtonState == LOW) {
      ESP_BT.begin("Xiotas Solar Dryer"); //Name of your Bluetooth Signal
      Serial.println("Bluetooth Device is Ready to Pair");
      while (!check_wifiUpdate() == true)
      {
        btLed.ledBlink (LOW, 800);
      }
    }
  }

  btLed.cancelLedBlink(LOW);
  Serial.println("Exited from settings. Booting started....");
  wifiConnection();

  internetLed.cancelLedBlink(HIGH);
  Serial.println("Testing Internet availability...");
  delay(100);
  internetLed.cancelLedBlink(LOW);

  if (Ping.ping("www.google.com")){
    Serial.println("Connected to Internet");
   internetLed.cancelLedBlink(HIGH);
  }
  else {
    Serial.println("No Internet");
    internetLed.cancelLedBlink(LOW);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}




boolean btButton() {
  unsigned long btSwitchCurrentMillis = millis();
  if ((btSwitchCurrentMillis - btButtonStartMillis) >= 10000) return true;
  else return false;
}
