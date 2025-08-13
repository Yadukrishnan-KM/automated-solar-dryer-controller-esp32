void readingSensorData9548() {

  //////////////////////////////// reading from room1 sensor  /////////////////////////////////////////

  TCA9548A(0);
  if (room1Sensor.connected()) {
    room1SensorStatus = true;
    room1SensorStatusInt = 1;
    room1Temp = room1Sensor.temperature();
    room1Humidity = room1Sensor.humidity();
    room1Temp = DecimalRound(room1Temp, 1);
    room1Humidity = DecimalRound(room1Humidity, 1);

  }
  else {
    room1SensorStatus = false;
    room1SensorStatusInt = 0;
  }
  
  //////////////////////////////// reading from room1 sensor  /////////////////////////////////////////

  TCA9548A(1);
  if (room2Sensor.connected()) {
    room2SensorStatus = true;
    room2SensorStatusInt = 1;
    room2Temp = room2Sensor.temperature();
    room2Humidity = room2Sensor.humidity();
    room2Temp = DecimalRound(room2Temp, 1);
    room2Humidity = DecimalRound(room2Humidity, 1);

  }
  else {
    room2SensorStatus = false;
    room2SensorStatusInt = 0;
  }
  
  //////////////////////////////// reading from room1 sensor  /////////////////////////////////////////

  TCA9548A(2);
  if (outsideSensor.connected()) {
    outsideSensorStatus = true;
    outsideSensorStatusInt = 1;
    outsideTemp = outsideSensor.temperature();
    outsideHumidity = outsideSensor.humidity();
    outsideTemp = DecimalRound(outsideTemp, 1);
    outsideHumidity = DecimalRound(outsideHumidity, 1);

  }
  else {
    outsideSensorStatus = false;
    outsideSensorStatusInt = 0;
  }
}
