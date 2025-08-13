void checkingInternetWifiNReconnecting() {
  // If firebase error happen then checking internet and wifi
  if (!firebaseStatus) {
    Serial.println("Firebase error checking Internet.... 1");
    internetLed.cancelLedBlink(HIGH);
    delay(100);
    internetLed.cancelLedBlink(LOW);
    if (Ping.ping("www.google.com")) {
      Serial.println("Internet OK 2");
      internetLed.cancelLedBlink(HIGH);
      wifiLed.cancelLedBlink(HIGH);
      internetStatus = true;
      firebaseReadSuccess = true;
      firebaseWriteSensorDataSuccess = true;
      firebaseWriteFeedbackDataSuccess = true;
      firebaseWriteLocalSwitchDataSuccess = true;
      // Reconnecting to firebase
      digitalWrite( firebaseLedPin, HIGH);
      Serial.println("Reconnecting to firebase... 3");
      delay(100);
      digitalWrite( firebaseLedPin, LOW);
      Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);
      Firebase.reconnectWiFi(true);
      firebaseStatus = true;
      wifiCounter = 0;
    }
    else {
      Serial.println("No Internet 4");
      internetLed.cancelLedBlink(LOW);
      firebaseStatus = false;
      internetStatus = false;
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi is connected 5");
        wifiLed.cancelLedBlink(HIGH);
        internetLed.cancelLedBlink(HIGH);
        Serial.println("Testing Internet availability... 6");
        delay(100);
        internetLed.cancelLedBlink(LOW);
        if (Ping.ping("www.google.com")) {
          Serial.println("Internet OK 7");
          internetLed.cancelLedBlink(HIGH);
          wifiLed.cancelLedBlink(HIGH);
          internetStatus = true;
          firebaseReadSuccess = true;
          firebaseWriteSensorDataSuccess = true;
          firebaseWriteFeedbackDataSuccess = true;
          firebaseWriteLocalSwitchDataSuccess = true;
          // Reconnecting to firebase
          digitalWrite( firebaseLedPin, HIGH);
          Serial.println("Reconnecting to firebase... 8");
          delay(100);
          digitalWrite( firebaseLedPin, LOW);
          Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);
          Firebase.reconnectWiFi(true);
          firebaseStatus = true;
        }
        else  {
          internetLed.cancelLedBlink(LOW);
          Serial.println("No Internet 9");
          firebaseReadSuccess = true;
          firebaseWriteSensorDataSuccess = true;
          firebaseWriteFeedbackDataSuccess = true;
          firebaseWriteLocalSwitchDataSuccess = true;
          firebaseStatus = false;
          internetStatus = false;
        }
        wifiCounter = 0;
        wififailresetcounter = 0;
      }
      else {
        wifiCounter++;
        Serial.print("wifi failure count is "); Serial.println(wifiCounter);
        Serial.println("WiFi connection Failed 10");
        Serial.println("Trying to Reconnect Wi Fi again 11");
        wifiLed.cancelLedBlink(LOW);
        WiFi.disconnect();
        delay(1000);
        wifiLed.cancelLedBlink(HIGH);
        delay(100);
        wifiLed.cancelLedBlink(LOW);
        if (wifiCounter == maxWifiCounter) {
          wififailresetcounter++;
          Serial.println("Initializing WiFi again 11.1");
          wifiConnection();
          wifiCounter = 0;
        }
        else WiFi.reconnect();
        delay(1000);
        if (WiFi.status() == WL_CONNECTED) {
          wififailresetcounter = 0;
          wifiLed.cancelLedBlink(HIGH);
          internetLed.cancelLedBlink(HIGH);
          Serial.println("Testing Internet availability... 12");
          delay(100);
          internetLed.cancelLedBlink(LOW);
          if (Ping.ping("www.google.com")) {
            Serial.println("Connected to Internet 13");
            internetLed.cancelLedBlink(HIGH);
            Serial.println("Reconnecting to firebase... 14");
            delay(100);
            digitalWrite( firebaseLedPin, LOW);
            Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);
            digitalWrite( firebaseLedPin, HIGH);
            Firebase.reconnectWiFi(true);
            firebaseReadSuccess = true;
            firebaseWriteSensorDataSuccess = true;
            firebaseWriteFeedbackDataSuccess = true;
            firebaseWriteLocalSwitchDataSuccess = true;
            firebaseStatus = true;
            internetStatus = true;
          }
          else {
            Serial.println("No Internet 15");
            internetLed.cancelLedBlink(LOW);
            firebaseReadSuccess = true;
            firebaseWriteSensorDataSuccess = true;
            firebaseWriteFeedbackDataSuccess = true;
            firebaseWriteLocalSwitchDataSuccess = true;
            firebaseStatus = false;
            internetStatus = false;
          }
          wifiCounter = 0;
        }
        else {
          Serial.println("WiFi connection Failed 16");
          wifiLed.cancelLedBlink(LOW);
        }
      }
    }
    if (wififailresetcounter == maxWiFiFailCountForReset) {
      Serial.println("Rebooting due to failure in wifi connection");
      ESP.restart(); // restart the esp for reconnecting to WiFi
    }
  }
  else {
    wififailresetcounter = 0;
    wifiCounter = 0;
  }
}
