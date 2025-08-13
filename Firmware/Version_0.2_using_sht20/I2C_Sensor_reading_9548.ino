
///////////////////////////////////////////////////////////////////////// I2C sensor read  //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void readingSensorData9548() {

  //////////////////////////////// reading from room1 sensor  /////////////////////////////////////////

  TCA9548A(0);
  if (room1Sensor.connected()) {
    room1SensorStatus = true;
    room1SensorStatusInt = 1;
    room1SensorFailCount = 0;
    float preRoom1Temp = room1Sensor.temperature();
    float preRoom1Humidity = room1Sensor.humidity();
    preRoom1Temp = DecimalRound(preRoom1Temp, 1);
    if (preRoom1Temp < maximumT && preRoom1Temp > minimumT) room1Temp = preRoom1Temp;
    preRoom1Humidity = DecimalRound(preRoom1Humidity, 1);
    if (preRoom1Humidity < maximumH && preRoom1Humidity > minimumH) room1Humidity = preRoom1Humidity;
  }
  else {
    room1SensorFailCount++;
    if (room1SensorFailCount == maxSensorFailCount) {
      room1SensorStatus = false;
      room1SensorStatusInt = 0;
      room1SensorFailCount = 0;
      room1Temp = 00.0;
      room1Humidity = 00;
      Serial.println("Room 1 sensor failed");
    }
  }

  //////////////////////////////// reading from room1 sensor  /////////////////////////////////////////

  TCA9548A(1);
  if (room2Sensor.connected()) {
    room2SensorStatus = true;
    room2SensorStatusInt = 1;
    room2SensorFailCount = 0;
    float preRoom2Temp = room2Sensor.temperature();
    float preRoom2Humidity = room2Sensor.humidity();
    preRoom2Temp = DecimalRound(preRoom2Temp, 1);
    if (preRoom2Temp < maximumT && preRoom2Temp > minimumT) room2Temp = preRoom2Temp;
    preRoom2Humidity = DecimalRound(preRoom2Humidity, 1);
    if (preRoom2Humidity < maximumH && preRoom2Humidity > minimumH) room2Humidity = preRoom2Humidity;
  }
  else {
    room2SensorFailCount++;
    if (room2SensorFailCount == maxSensorFailCount) {
      room2SensorStatus = false;
      room2SensorStatusInt = 0;
      room2SensorFailCount = 0;
      room2Temp = 00.0;
      room2Humidity = 00;
      Serial.println("Room 2 sensor failed");
    }
  }

  //////////////////////////////// reading from room1 sensor  /////////////////////////////////////////

  TCA9548A(2);
  if (outsideSensor.connected()) {
    outsideSensorStatus = true;
    outsideSensorStatusInt = 1;
    outsideSensorFailCount = 0;
    float preOutsideTemp = outsideSensor.temperature();
    float preOutsideHumidity = outsideSensor.humidity();
    preOutsideTemp = DecimalRound(preOutsideTemp, 1);
    if (preOutsideTemp < maximumT && preOutsideTemp > minimumT) outsideTemp = preOutsideTemp;
    preOutsideHumidity = DecimalRound(preOutsideHumidity, 1);
    if (preOutsideHumidity < maximumH && preOutsideHumidity > minimumH) outsideHumidity = preOutsideHumidity;
  }
  else {
    outsideSensorFailCount++;
    if (outsideSensorFailCount == maxSensorFailCount) {
      outsideSensorStatus = false;
      outsideSensorStatusInt = 0;
      outsideSensorFailCount = 0;
      outsideTemp = 00.0;
      outsideHumidity = 00;
      Serial.println("Room 3 sensor failed");
    }
  }
}

///////////////////////////////////////////////////////////////////////// mux code for ic9548  //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TCA9548A(uint8_t bus) {        // give the bus number here
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  //Serial.print(bus);
}

///////////////////////////////////////////////////////////////////////// decimal reduction code  //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


float DecimalRound(float input, int decimals)
{
  float scale = pow(10, decimals);
  return round(input * scale) / scale;
}
