void wifiConnection() {
  Serial.println("Reading data from EEPROM...");
  eepromRead();
  int i = Ssid.length();
  int j = Password.length();
  char ssid[i];
  char password[j];
  Ssid.toCharArray(ssid, i);
  Password.toCharArray(password, j);
  Serial.print("Your saved SSID is : "); Serial.println(ssid);
  Serial.print("Your saved password is : "); Serial.println(password);
  WiFi.mode(WIFI_STA);
  Serial.println("Connecting to WiFi...");
  wifiLed.cancelLedBlink(HIGH);
  delay (100);
  WiFi.begin(ssid, password);
  wifiLed.cancelLedBlink(LOW);
  delay (100);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi connection Failed");
    wifiLed.cancelLedBlink(LOW);
  }
  else
  {
    Serial.print("Wifi Connected to : "); Serial.print(WiFi.SSID()); Serial.print(" ,RSSI : "); Serial.println(WiFi.RSSI());
    Serial.print("IP Address is : "); Serial.println(WiFi.localIP());
    wifiLed.cancelLedBlink(HIGH);
  }
}
