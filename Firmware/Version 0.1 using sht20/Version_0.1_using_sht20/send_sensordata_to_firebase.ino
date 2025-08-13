
///////////////////////////////////////////////  Sending sensor data to firebase database             //////////////////////////////////////

boolean writeSensordataFirebase() {

  // room1 old sensor data variables

  static boolean room1oldSensorStatus;
  static float room1oldTemp;
  static float room1oldHumidity;
  static float room1oldMaxTemp;
  static float room1oldMinTemp;
  static float room1oldMaxHumidity;
  static float room1oldMinHumidity;

  // room2 old sensor data variables

  static boolean room2oldSensorStatus;
  static float room2oldTemp;
  static float room2oldHumidity;
  static float room2oldMaxTemp;
  static float room2oldMinTemp;
  static float room2oldMaxHumidity;
  static float room2oldMinHumidity;

  // oustside old sensor data variables

  static boolean outsideoldSensorStatus;
  static float outsideoldTemp;
  static float outsideoldHumidity;
  static float outsideoldMaxTemp;
  static float outsideoldMinTemp;
  static float outsideoldMaxHumidity;
  static float outsideoldMinHumidity;

  if (room1oldSensorStatus != room1SensorStatus )Firebase.setInt(firebaseData, "/Dryer_Room_1/Sensor_Status", room1SensorStatusInt);
  if (room1SensorStatus) {
    if (room1oldTemp != room1Temp) Firebase.setFloat(firebaseData, "/Dryer_Room_1/Temperature", room1Temp);
    if (room1oldHumidity !=  room1Humidity) Firebase.setFloat(firebaseData, "/Dryer_Room_1/Humidity", room1Humidity);
    if (room1oldMaxTemp != room1MaxTemp) Firebase.setFloat(firebaseData, "/Dryer_Room_1/Temperature_Max", room1MaxTemp);
    if (room1oldMinTemp != room1MinTemp)Firebase.setFloat(firebaseData, "/Dryer_Room_1/Temperature_Min", room1MinTemp);
    if (room1oldMaxHumidity != room1MaxHumidity)Firebase.setFloat(firebaseData, "/Dryer_Room_1/Humidity_Max", room1MaxHumidity);
    if (room1oldMinHumidity != room1MinHumidity)Firebase.setFloat(firebaseData, "/Dryer_Room_1/Humidity_Min", room1MinHumidity);
    room1oldTemp = room1Temp;
    room1oldHumidity =  room1Humidity;
    room1oldMaxTemp = room1MaxTemp;
    room1oldMinTemp = room1MinTemp;
    room1oldMaxHumidity = room1MaxHumidity;
    room1oldMinHumidity = room1MinHumidity;
  }
  if (room2oldSensorStatus != room2SensorStatus )Firebase.setInt(firebaseData, "/Dryer_Room_2/Sensor_Status", room2SensorStatusInt);
  if (room2SensorStatus) {
    if (room2oldTemp != room2Temp) Firebase.setFloat(firebaseData, "/Dryer_Room_2/Temperature", room2Temp);
    if (room2oldHumidity !=  room2Humidity) Firebase.setFloat(firebaseData, "/Dryer_Room_2/Humidity", room2Humidity);
    if (room2oldMaxTemp != room2MaxTemp) Firebase.setFloat(firebaseData, "/Dryer_Room_2/Temperature_Max", room2MaxTemp);
    if (room2oldMinTemp != room2MinTemp)Firebase.setFloat(firebaseData, "/Dryer_Room_2/Temperature_Min", room2MinTemp);
    if (room2oldMaxHumidity != room2MaxHumidity)Firebase.setFloat(firebaseData, "/Dryer_Room_2/Humidity_Max", room2MaxHumidity);
    if (room2oldMinHumidity != room2MinHumidity)Firebase.setFloat(firebaseData, "/Dryer_Room_2/Humidity_Min", room2MinHumidity);
    room2oldTemp = room2Temp;
    room2oldHumidity =  room2Humidity;
    room2oldMaxTemp = room2MaxTemp;
    room2oldMinTemp = room2MinTemp;
    room2oldMaxHumidity = room2MaxHumidity;
    room2oldMinHumidity = room2MinHumidity;
  }
  if (outsideoldSensorStatus != outsideSensorStatus )Firebase.setInt(firebaseData, "/Outside/Sensor_Status", outsideSensorStatusInt);
  if (outsideSensorStatus) {
    if (outsideoldTemp != outsideTemp) Firebase.setFloat(firebaseData, "/Outside/Temperature", outsideTemp);
    if (outsideoldHumidity !=  outsideHumidity) Firebase.setFloat(firebaseData, "/Outside/Humidity", outsideHumidity);
    if (outsideoldMaxTemp != outsideMaxTemp) Firebase.setFloat(firebaseData, "/Outside/Temperature_Max", outsideMaxTemp);
    if (outsideoldMinTemp != outsideMinTemp)Firebase.setFloat(firebaseData, "/Outside/Temperature_Min", outsideMinTemp);
    if (outsideoldMaxHumidity != outsideMaxHumidity)Firebase.setFloat(firebaseData, "/Outside/Humidity_Max", outsideMaxHumidity);
    if (outsideoldMinHumidity != outsideMinHumidity)Firebase.setFloat(firebaseData, "/Outside/Humidity_Min", outsideMinHumidity);
    outsideoldTemp = outsideTemp;
    outsideoldHumidity =  outsideHumidity;
    outsideoldMaxTemp = outsideMaxTemp;
    outsideoldMinTemp = outsideMinTemp;
    outsideoldMaxHumidity = outsideMaxHumidity;
    outsideoldMinHumidity = outsideMinHumidity;
  }


  if (Firebase.setString(firebaseData, "/Others/Last_Updated", lastUpdatedDateTime)) {
    Serial.println("Writing data to firebase was successfull");
    return true;
  }
  else return false;

}

///////////////////////////////////////////////  Sending device feedback to firebase database             //////////////////////////////////////

boolean sendDeviceFeedbackFirebase() {
  if (!Firebase.setInt(firebaseData, "/Dryer_Room_1/Fan_Feedback", room1FanFeedback)) return false;
  if (!Firebase.setInt(firebaseData, "/Dryer_Room_1/Valve_Feedback", room1ValveFeedback)) return false;
  if (!Firebase.setInt(firebaseData, "/Dryer_Room_2/Fan_Feedback", room2FanFeedback)) return false;
  if (!Firebase.setInt(firebaseData, "/Dryer_Room_2/Valve_Feedback", room2ValveFeedback)) return false;
  if (!Firebase.setInt(firebaseData, "/Outside/Pump_Feedback", outsidePumpFeedback)) return false;
  else return true;
}
