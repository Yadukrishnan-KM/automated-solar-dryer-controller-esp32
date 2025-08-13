TaskHandle_t Task1;

////////////////------------------------------------------        Essential Library Files         ---------------------------------------------///////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LedBlink.h>
#include "BluetoothSerial.h" //Header File for Serial Bluetooth, will be added by default into Arduino
#include <EEPROM.h>
#include <ESP32Ping.h>
#include "WiFi.h"
#include <FirebaseESP32.h>
#include "Wire.h"
#include "uFire_SHT20.h"
#include "time.h"

////////////////------------------------------------------        Definitions       ---------------------------------------------///////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define liIonCellVolatgePin 32
#define acDetectionPin 39

// def for local control button read
#define LocalButtonPin 34                     // Local control bitton connection pin (analog pin in esp32)
#define LocalControlSwitchIntervelCount 150

#define FIREBASE_HOST "put yours"
#define FIREBASE_Authorization_key "put yours"

//def for statis LED Pins
#define btLedPin 32
#define wifiLedPin 33
#define internetLedPin 25
#define firebaseLedPin 26

#define btButtonPin 23

/////////////// output pin definitions for output device and its indication leds  //////////////////
#define remoteControlSaftyTime 10000
#define room1FanOutputLedPin 27
#define room1FanOutputPin 4
#define room1ValveOutputLedPin 14
#define room1ValveOutputPin 16
#define room2FanOutputLedPin 12
#define room2FanOutputPin 17
#define room2ValveOutputLedPin 13
#define room2ValveOutputPin 5
#define outsidePumpOutputLedPin 15
#define outsidePumpOutputPin 18
#define buzzerPin 2

////////////////------------------------------------------        Object Creation        ---------------------------------------------///////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Object for Bluetooth
BluetoothSerial ESP_BT;

// sensor objects
uFire_SHT20 room1Sensor;
uFire_SHT20 room2Sensor;
uFire_SHT20 outsideSensor;

//////  objects for connection status LED  ////////
LedBlink btLed(btLedPin);
LedBlink wifiLed(wifiLedPin);
LedBlink internetLed(internetLedPin);
LedBlink firebaseLed(firebaseLedPin);

//////  objects for outside device control LED and Buzzer  ////////
LedBlink buzzer(buzzerPin);
LedBlink room1FanLed(room1FanOutputLedPin);
LedBlink room1ValveLed(room1ValveOutputLedPin);
LedBlink room2FanLed(room2FanOutputLedPin);
LedBlink room2ValveLed(room2ValveOutputLedPin);
LedBlink outsidePumpLed(outsidePumpOutputLedPin);

//////  Firebase Objects     //////////
FirebaseData firebaseData;

////////////////------------------------------------------       Global Variables       ---------------------------------------------////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// variable for local control button read
int buttonValue = 0;
int buttonThreshold = 200;
boolean localButtonControlCounter = true;
boolean localSwitchRoom1Fan;
boolean localSwitchRoom1Valve;
boolean localSwitchRoom2Fan;
boolean localSwitchRoom2Valve;
boolean localSwitchOutsidePump;

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

// room1 sensor data variables
boolean room1SensorStatus = false;
int room1SensorStatusInt = 0;
float room1Temp = 0;
float room1Humidity = 0;
float room1MaxTemp = 0;
float room1MinTemp = 200;
float room1MaxHumidity = 0;
float room1MinHumidity = 200;

// room2 sensor data variables
boolean room2SensorStatus = false;
int room2SensorStatusInt = 0;
float room2Temp = 0;
float room2Humidity = 0;
float room2MaxTemp = 0;
float room2MinTemp = 200;
float room2MaxHumidity = 0;
float room2MinHumidity = 200;

// oustside sensor data variables
boolean outsideSensorStatus = false;
int outsideSensorStatusInt = 0;
float outsideTemp = 0;
float outsideHumidity = 0;
float outsideMaxTemp = 0;
float outsideMinTemp = 200;
float outsideMaxHumidity = 0;
float outsideMinHumidity = 200;

String lastUpdatedDateTime;


// variables for RTC and NTP server (time)
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;
const int   daylightOffset_sec = 0;

//  counter for max and min value finding function
int maxAndMinValueCounter = 0;

boolean powerStatus = true;

// variables for output control of room1
boolean room1FanCondition0 = true;
boolean room1FanCondition1 = true;
unsigned long room1FanCounter;
int room1FanFeedback = 0;

boolean room1ValveCondition0 = true;
boolean room1ValveCondition1 = true;
unsigned long room1ValveCounter;
int room1ValveFeedback = 0;

// variables for output control of room2
boolean room2FanCondition0 = true;
boolean room2FanCondition1 = true;
unsigned long room2FanCounter;
int room2FanFeedback = 0;

boolean room2ValveCondition0 = true;
boolean room2ValveCondition1 = true;
unsigned long room2ValveCounter;
int room2ValveFeedback = 0;

// variables for output control of outside
boolean outsidePumpCondition0 = true;
boolean outsidePumpCondition1 = true;
unsigned long outsidePumpCounter;
int outsidePumpFeedback = 0;

// variables for reading data from firebase
boolean room1FanStatus;
boolean room1ValveStatus;
boolean room2FanStatus;
boolean room2ValveStatus;
boolean outsidePumpStatus;


void setup() {

  Serial.begin(9600); // Start Serial monitor in 9600
  EEPROM.begin(50); // 50 bytes of data
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

  if (Ping.ping("www.google.com")) {
    Serial.println("Connected to Internet");
    internetLed.cancelLedBlink(HIGH);
  }
  else {
    Serial.println("No Internet");
    internetLed.cancelLedBlink(LOW);
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);
  Firebase.reconnectWiFi(true);

  Wire.begin();
  TCA9548A(0);
  room1Sensor.begin();
  TCA9548A(1);
  room2Sensor.begin();
  TCA9548A(2);
  outsideSensor.begin();

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);
  Firebase.reconnectWiFi(true);

  pinMode(room1FanOutputPin, OUTPUT);
  pinMode(room1ValveOutputPin, OUTPUT);
  pinMode(room2FanOutputPin, OUTPUT);
  pinMode(room2ValveOutputPin, OUTPUT);
  pinMode(outsidePumpOutputPin, OUTPUT);

  xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0);
  delay(500);

}

void loop() {
  printLocalTime();
readingSensorData9548();

  minMaxValues();
  writeSensordataFirebase();

  readFirebase ();

  sendDeviceFeedbackFirebase();
  Serial.print("void loop is running on core ");
  Serial.println(xPortGetCoreID());
delay(20);
}




boolean btButton() {
  unsigned long btSwitchCurrentMillis = millis();
  if ((btSwitchCurrentMillis - btButtonStartMillis) >= 10000) return true;
  else return false;
}
