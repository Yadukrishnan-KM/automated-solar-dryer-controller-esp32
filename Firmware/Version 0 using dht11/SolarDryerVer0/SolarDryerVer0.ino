
#include <FirebaseESP32.h>
#include  <WiFi.h>
#include "DHT.h"

#define WIFI_SSID "put yours" // Change the name of your WIFI
#define WIFI_PASSWORD "put yours" // Change the password of your WIFI
#define FIREBASE_HOST "put yours"
#define FIREBASE_Authorization_key "put yours"

#define DHTPIN 33

#define DHTTYPE DHT11
bool Fan_Status_1 = false;
bool Light_Status_1 = false;
DHT dht(DHTPIN, DHTTYPE);

FirebaseData firebaseData;
//FirebaseJson json;

void setup()
{
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  Serial.begin(115200);
  dht.begin();
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
  Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);
  Firebase.reconnectWiFi(true);

}

void loop()
{

  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(hum) || isnan(temp)  ) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("°C");
  Serial.print(" Humidity: ");
  Serial.print(hum);
  Serial.print("%");
  Serial.println();

  Firebase.setFloat(firebaseData, "/Dryer_Room_1/Temperature", temp);
  Firebase.setFloat(firebaseData, "/Dryer_Room_1/Humidity", hum);
  Firebase.getBool(firebaseData, "/Dryer_Room_1/Fan_Status");
  Fan_Status_1 = firebaseData.boolData();
  Firebase.getBool(firebaseData, "/Dryer_Room_1/Light_Status");
  Light_Status_1 = firebaseData.boolData();

  if (Fan_Status_1 == true) digitalWrite (26, HIGH);
  else if (Fan_Status_1 == false) digitalWrite (26, LOW);
  if (Light_Status_1 == true) digitalWrite (25, HIGH);
  else if (Light_Status_1 == false) digitalWrite (25, LOW);
  Serial.print(Fan_Status_1);
  Serial.print(Light_Status_1);
  Serial.println();
  delay(500);
}
