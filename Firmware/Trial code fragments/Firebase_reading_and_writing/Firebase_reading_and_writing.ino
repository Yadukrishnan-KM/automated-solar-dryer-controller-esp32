
TaskHandle_t Task1;

#include <FirebaseESP32.h>
#include  <WiFi.h>
#include "Wire.h"
#include "uFire_SHT20.h"
#include "time.h"
#include <LedBlink.h>

#define FIREBASE_HOST "solar-dryer-automation-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_Authorization_key "w0FW9qpx3Ek3nkafO4zEyRVAyfzuy6FnYeK8ig7s"

#define WIFI_SSID "Kuzhiyadithazhath" // Change the name of your WIFI
#define WIFI_PASSWORD "geethuyadu1991" // Change the password of your WIFI

/////////////// output pin definitions for output device and its indication leds  //////////////////
#define remoteControlSaftyTime 10000
#define room1FanOutputLedPin 26
#define room1FanOutputPin 25
#define room1ValveOutputLedPin 23
#define room1ValveOutputPin 19
#define room2FanOutputLedPin 18
#define room2FanOutputPin 5
#define room2ValveOutputLedPin 4
#define room2ValveOutputPin 2
#define outsidePumpOutputLedPin 15
#define outsidePumpOutputPin 13
#define buzzerPin 33

FirebaseData firebaseData;
uFire_SHT20 sht20;

//////  objects for outside device control  ////////
LedBlink buzzer(buzzerPin);
LedBlink room1FanLed(room1FanOutputLedPin);
LedBlink room1ValveLed(room1ValveOutputLedPin);
LedBlink room2FanLed(room2FanOutputLedPin);
LedBlink room2ValveLed(room2ValveOutputLedPin);
LedBlink outsidePumpLed(outsidePumpOutputLedPin);

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


void setup()
{
  Serial.begin(115200);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);
  Firebase.reconnectWiFi(true);

  Wire.begin();
  sht20.begin();

  pinMode(room1FanOutputPin, OUTPUT);
  pinMode(room1ValveOutputPin, OUTPUT);
  pinMode(room2FanOutputPin, OUTPUT);
  pinMode(room2ValveOutputPin, OUTPUT);
  pinMode(outsidePumpOutputPin, OUTPUT);

  xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0);
  delay(500);

}

void loop()
{
  printLocalTime();
  float humd = sht20.humidity();
  float temp = sht20.temperature();

  humd = DecimalRound(humd, 1);
  temp = DecimalRound(temp, 1);

  Serial.println(humd);
  Serial.println(temp);

  room1SensorStatus = true;
  room1SensorStatusInt = 1;
  room1Temp = temp;
  room1Humidity = humd;

  room2SensorStatus = true;
  room2SensorStatusInt = 1;
  room2Temp = temp;
  room2Humidity = humd;

  outsideSensorStatus = true;
  outsideSensorStatusInt = 1;
  outsideTemp = temp;
  outsideHumidity = humd;

  minMaxValues();
  writeSensordataFirebase();

  readFirebase ();
  
  sendDeviceFeedbackFirebase();
  Serial.print("void loop is running on core ");
  Serial.println(xPortGetCoreID());
}



float DecimalRound(float input, int decimals)
{
  float scale = pow(10, decimals);
  return round(input * scale) / scale;
}

void Task1code( void * parameter ) {
  Serial.print("Task1 is running on core ");
  Serial.println(xPortGetCoreID());

  for (;;) {
    room1FanFeedback = room1FanOutputControl();
    room1ValveFeedback = room1ValveOutputControl();
    room2FanFeedback = room2FanOutputControl();
    room2ValveFeedback = room2ValveOutputControl();
    outsidePumpFeedback = outsidePumpOutputControl();
    if(room1FanFeedback == 2 || room1ValveFeedback == 2 || room2FanFeedback == 2 || room2ValveFeedback == 2 || outsidePumpFeedback == 2) buzzer.ledBlink (HIGH, 500);
    else buzzer.cancelLedBlink(LOW);
    delay(16);
  }
}
