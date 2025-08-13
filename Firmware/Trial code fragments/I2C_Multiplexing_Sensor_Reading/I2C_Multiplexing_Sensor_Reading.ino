#include "uFire_SHT20.h"
#include "Wire.h"

// sensor objects
uFire_SHT20 room1Sensor;
uFire_SHT20 room2Sensor;
uFire_SHT20 outsideSensor;

float room1Temp;
float room1Humidity;
float room2Temp;
float room2Humidity;
float outsideTemp;
float outsideHumidity;

boolean room1SensorStatus;
int room1SensorStatusInt;
boolean room2SensorStatus;
int room2SensorStatusInt;
boolean outsideSensorStatus;
int outsideSensorStatusInt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(32,35);
  TCA9548A(0);
  room1Sensor.begin();
  TCA9548A(1);
  room2Sensor.begin();
  TCA9548A(2);
  outsideSensor.begin();
}

void loop() {

  readingSensorData9548();
  Serial.println("Room1 values");
  Serial.println(room1Temp);
  Serial.println(room1Humidity);
  Serial.println(room1SensorStatusInt);

  Serial.println("Room2 values");
  Serial.println(room2Temp);
  Serial.println(room2Humidity);
  Serial.println(room2SensorStatusInt);

  Serial.println("Outside values");
  Serial.println(outsideTemp);
  Serial.println(outsideHumidity);
  Serial.println(outsideSensorStatusInt);

  delay(500);

}

void TCA9548A(uint8_t bus) {        // give the bus number here
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  //Serial.print(bus);
}

float DecimalRound(float input, int decimals)
{
  float scale = pow(10, decimals);
  return round(input * scale) / scale;
}
