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

#define liIonCellVolatgePin 39
#define acDetectionPin 25

// def for local control button read
#define LocalButtonPin 36                     // Local control bitton connection pin (analog pin in esp32)
#define LocalControlSwitchIntervelCount 150

#define FIREBASE_HOST "put yours"
#define FIREBASE_Authorization_key "put yours"

//def for statis LED Pins
#define btLedPin 33
#define wifiLedPin 23
#define internetLedPin 5
#define firebaseLedPin 19

//def for button Pins
#define btButtonPin 34

/////////////// output pin definitions for output device and its indication leds  //////////////////
#define room1FanOutputLedPin 26
#define room1FanOutputPin 18
#define room1ValveOutputLedPin 13
#define room1ValveOutputPin 17
#define room2FanOutputLedPin 14
#define room2FanOutputPin 16
#define room2ValveOutputLedPin 27
#define room2ValveOutputPin 4
#define outsidePumpOutputLedPin 12
#define outsidePumpOutputPin 15
#define buzzerPin 2

////////////// constant values /////////////////////////////////////
// def for constatnt values
#define autoResetTime 86400000 // 24 Hrs
//#define autoResetTime 180000 // for testing 3 min
#define firebaseErrorCount 2
#define maximumT 100
#define minimumT 5
#define maximumH 100
#define minimumH 10
#define maxNMinCounterValue 6
#define remoteControlSaftyTime 12000 // 12sec.
#define sensorDataUpdateFirebaseTime 10000 // 10sec.
#define maxWifiCounter 60 // maximum wifi failure counter value
#define maxSensorFailCount 5 // maximum sensor failure counter value
#define maxWiFiFailCountForReset 25 //maximum wifi failure for master reset counter value


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
boolean localSwitchRoom1Fan = false;
boolean localSwitchRoom1Valve = false;
boolean localSwitchRoom2Fan = false;
boolean localSwitchRoom2Valve = false;
boolean localSwitchOutsidePump = false;
//boolean localSwitchCounter = true;
boolean localSwitchRoom1FanStateChange = false;
boolean localSwitchRoom1ValveStateChange = false;
boolean localSwitchRoom2FanStateChange = false;
boolean localSwitchRoom2ValveStateChange = false;
boolean localSwitchOutsidePumpStateChange = false;
boolean masterStateChange = false;
boolean oldLocalSwitchRoom1Fan = false;
boolean oldLocalSwitchRoom1Valve = false;
boolean oldLocalSwitchRoom2Fan = false;
boolean oldLocalSwitchRoom2Valve = false;
boolean oldLocalSwitchOutsidePump = false;

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
int room1SensorFailCount = 0;
boolean room1SensorStatus = false;
int room1SensorStatusInt = 0;
float room1Temp = 0;
float room1Humidity = 0;
float room1MaxTemp = 0;
float room1MinTemp = 200;
float room1MaxHumidity = 0;
float room1MinHumidity = 200;

// room2 sensor data variables
int room2SensorFailCount = 0;
boolean room2SensorStatus = false;
int room2SensorStatusInt = 0;
float room2Temp = 0;
float room2Humidity = 0;
float room2MaxTemp = 0;
float room2MinTemp = 200;
float room2MaxHumidity = 0;
float room2MinHumidity = 200;

// oustside sensor data variables
int outsideSensorFailCount = 0;
boolean outsideSensorStatus = false;
int outsideSensorStatusInt = 0;
float outsideTemp = 0;
float outsideHumidity = 0;
float outsideMaxTemp = 0;
float outsideMinTemp = 200;
float outsideMaxHumidity = 0;
float outsideMinHumidity = 200;
boolean sensorSatatusCounter = true;

//  counter for max and min value finding function
boolean maxAndMinValueCounter = true;

String lastUpdatedDateTime;

// variables for RTC and NTP server (time)
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;
const int   daylightOffset_sec = 0;

boolean powerStatus = false;

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

// variables for firebase success actions

boolean firebaseReadSuccess = false;
boolean firebaseWriteSensorDataSuccess = false;
boolean firebaseWriteFeedbackDataSuccess = false;
boolean firebaseWriteLocalSwitchDataSuccess = false;
boolean firebaseStatus = false;
boolean internetStatus = false;
unsigned long firebaseStartMillis = 0;
int firebaseErrorCounter = 0;
int firebaseopencounter = 0;

//esp autorest variable for time counting
unsigned long masterTime;

//battery percentage
int batteryPercent = 2;

// counter variable for wifi failure
int wifiCounter = 0;
int wififailresetcounter = 0;

/////////////////////////////////////////////////////////////////////////////////// Void Setup //////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600); // Start Serial monitor in 9600
  EEPROM.begin(50); // 50 bytes of data
  Serial.println("Welcome to Xiotas Solar Dryer Automation Project");
  buzzer.cancelLedBlink(HIGH);
  delay(500);
  buzzer.cancelLedBlink(LOW);
  btLed.cancelLedBlink(HIGH);
  Serial.println("Press the button within 10 seconds to enter into settings");
  Serial.println("Otherwise it will atomatically exit and device will start booting");
  pinMode(btButtonPin, INPUT);
  btButtonStartMillis = millis();
  while (!btButton() == true) {
    boolean btButtonState = digitalRead(btButtonPin);
    if (btButtonState == HIGH) {
      buzzer.cancelLedBlink(HIGH);
      delay(100);
      buzzer.cancelLedBlink(LOW);
      ESP_BT.begin("Xiotas Solar Dryer"); //Name of your Bluetooth Signal
      Serial.println("Bluetooth Device is Ready to Pair");
      while (!check_wifiUpdate() == true)
      {
        btLed.ledBlink (LOW, 800);
      }
    }
  }

  buzzer.cancelLedBlink(HIGH);
  delay(500);
  buzzer.cancelLedBlink(LOW);
  btLed.cancelLedBlink(LOW);
  Serial.println("Exited from settings. Booting started....");

  //Setting wifiname
  WiFi.setHostname("Xiotas Solar Dryer");

  //Initializing Wi Fi connection
  wifiConnection();

  // Checking Internet and Connecting to Firebase Server
  internetLed.cancelLedBlink(HIGH);
  Serial.println("Testing Internet availability...");
  delay(100);
  internetLed.cancelLedBlink(LOW);
  if (Ping.ping("www.google.com")) {
    Serial.println("Connected to Internet");
    Serial.println("Internet OK");
    internetLed.cancelLedBlink(HIGH);
    internetStatus = true;
    digitalWrite( firebaseLedPin, HIGH);
    Serial.println("Connecting to firebase...");
    delay(100);
    digitalWrite( firebaseLedPin, LOW);
    Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);
    Firebase.reconnectWiFi(true);
    Serial.println("Connected with firebase");
  }
  else {
    Serial.println("No Internet");
    internetLed.cancelLedBlink(LOW);
    internetStatus = false;
  }

  // Initializing i2c sensors
  Serial.println("Starting i2c sensors...");
  Wire.begin();
  TCA9548A(0);
  room1Sensor.begin();
  TCA9548A(1);
  room2Sensor.begin();
  TCA9548A(2);
  outsideSensor.begin();

  //init and get the time
  Serial.println("init and getting the time...");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  // Setting pinmodes for i/o pins
  Serial.println("Setting pinmode...");
  pinMode(acDetectionPin, INPUT);
  pinMode(liIonCellVolatgePin, INPUT);
  pinMode(room1FanOutputPin, OUTPUT);
  pinMode(room1ValveOutputPin, OUTPUT);
  pinMode(room2FanOutputPin, OUTPUT);
  pinMode(room2ValveOutputPin, OUTPUT);
  pinMode(outsidePumpOutputPin, OUTPUT);

  // Starting task2 on next core (using it for codes which need fast refreshing like input read)
  Serial.println("Starting task 2 on next core...");
  xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0);

  delay(3000);
  Serial.println("---------------------------------------------------- Setup completed and Going to loop ----------------------------------------------------");
}


////////////////////////////////////////////////////////////////////////  Void Setup Completed Next Void Loop  ///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {

  // Getting time, reading sensor data and processing it
  printLocalTime();
  readingSensorData9548();
  minMaxValues();
  
Serial.print("wififailresetcounter : ");Serial.println(wififailresetcounter);
Serial.print("wifiCounter : ");Serial.println(wifiCounter);
  
  // Checking battery (8.4v li-ion) voltage and printing it
  batteryPercetDetection();
  Serial.print("Battery Percentage : "); Serial.print(batteryPercent); Serial.println("%");

  // Printing sensor data
  Serial.print("Room1 temp: "); Serial.print(room1Temp); Serial.print(" || Room1 humidity: "); Serial.print(room1Humidity); Serial.print(" || Room2 temp: "); Serial.print(room2Temp);
  Serial.print(" || Room2 humidity: "); Serial.print(room2Humidity); Serial.print(" || Outside temp: "); Serial.print(outsideTemp); Serial.print(" || Outside humidity: ");
  Serial.println(outsideHumidity);

  // Communication with fireabse (up/down) which happen only when internet is available
  if (internetStatus) {
    unsigned long firebaseCurrentMillis = millis();                          // Sending sensor data only in every 6 sec
    if ((firebaseCurrentMillis - firebaseStartMillis) >= sensorDataUpdateFirebaseTime) {
      firebaseStartMillis = firebaseCurrentMillis;
      if (writeSensordataFirebase()) firebaseWriteSensorDataSuccess = true;
      else firebaseWriteSensorDataSuccess = false;
    }
    if (!masterStateChange) {
      if (readFirebase ()) firebaseReadSuccess = true;
      else firebaseReadSuccess = false;
    }
    else if (masterStateChange) {
      if (sendLocalSwitchDtataChange()) {
        masterStateChange = false;
        firebaseWriteLocalSwitchDataSuccess = true;
      }
      else firebaseWriteLocalSwitchDataSuccess = false;
    }
    if (sendDeviceFeedbackFirebase()) firebaseWriteFeedbackDataSuccess = true;
    else firebaseWriteFeedbackDataSuccess = false;
    sendBatteryPercentage();
  }

  // Detecting firebase error
  if (firebaseReadSuccess && firebaseWriteFeedbackDataSuccess && firebaseWriteSensorDataSuccess &&  firebaseWriteLocalSwitchDataSuccess && internetStatus) {
    firebaseStatus = true;
    firebaseErrorCounter = 0;
  }
  else {
    firebaseErrorCounter++;                          // Only detect firebase error after some no. of error
    firebaseReadSuccess = true;
    firebaseWriteSensorDataSuccess = true;
    firebaseWriteFeedbackDataSuccess = true;
    firebaseWriteLocalSwitchDataSuccess = true;
    if (firebaseErrorCounter == firebaseErrorCount) {
      firebaseStatus = false;
      firebaseErrorCounter = 0;
    }
    //else firebaseStatus = true;
  }

  // Ensuring the LED status are correct
  digitalWrite( firebaseLedPin, firebaseStatus);
  digitalWrite( internetLedPin, internetStatus);
  if (internetStatus)digitalWrite( wifiLedPin, HIGH);

  // If firebase getting error checking internet and wifi connection and reconnecting again
  checkingInternetWifiNReconnecting();

  // Software auto restet after preset time
  masterTime = millis();
  Serial.print("------------------ Master Reset will happen in (Sec.) ------------------"); Serial.println((autoResetTime - masterTime) / 1000);
  if (masterTime >= autoResetTime) ESP.restart();

  delay(20);

  //Serial.print("void loop is running on core loop");
  // Serial.println(xPortGetCoreID());
  //Serial.print("masterStateChange2");Serial.println(masterStateChange);
}
