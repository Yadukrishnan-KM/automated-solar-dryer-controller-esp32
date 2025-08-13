boolean check_wifiUpdate()
{
  if (ESP_BT.available()) {
    bufferIn = ESP_BT.readStringUntil('\n'); //Read what we recevive
    String bufferValue = bufferIn.substring(0, 5);
    Serial.print("Received : "); Serial.println(bufferIn);
    delay(20);
    if (bufferValue.equals("HELLO")) {
ssidsection: ESP_BT.println("Welcome to XIOTAS Solar Drayer Project");
      ESP_BT.println("Please send your WiFi SSID (WiFi Name)");
      Serial.println("Welcome to XIOTAS Solar Drayer Project");
      Serial.println("Please send your WiFi SSID (WiFi Name)");
      while (ssidRead() == false) {

        btLed.ledBlink (LOW, 400);
      }
      if (bufferConfirmYesValue != "YES") {
        ESP_BT.println("Going back to SSID window");
        Serial.println("Going back to SSID window");
        goto ssidsection;
      }
passwordsection: ESP_BT.println("Please send your WiFi Password");
      Serial.println("Please send your WiFi Password");

      while (passwordRead() == false) {

        btLed.ledBlink (LOW, 400);
      }
      if (bufferConfirmYesValue != "YES") {
        ESP_BT.println("Going back to password window");
        Serial.println("Going back to password window");
        goto passwordsection;
      }

      ESP_BT.println("Reading saved WiFi credentials...");
      Serial.println("Reading saved WiFi credentials...");
      eepromRead();
      ESP_BT.print("Your saved SSID is : "); ESP_BT.println(Ssid);
      ESP_BT.print("Your saved password is : "); ESP_BT.println(Password);
      Serial.print("Your saved SSID is : "); Serial.println(Ssid);
      Serial.print("Your saved password is : "); Serial.println(Password);
      ESP_BT.println("Completed.Configurations! *****/...THANK YOU.../****");
      ESP_BT.println("Bluetooth turning off...");
      Serial.println("Completed.Configurations! *****/...THANK YOU.../****");
      Serial.println("Bluetooth turning off...");
      ESP_BT.end();

      return true;
    }
    else {
      ESP_BT.println("Sorry wrong command");
      ESP_BT.println("Send the command HELLO");
      Serial.println("Sorry wrong command");
      Serial.println("Send the command HELLO");
      return false;
    }
  }
  else return false;
}

boolean ssidRead() {

  if (ESP_BT.available()) //Check if we receive anything from Bluetooth
  {
    bufferIn = ESP_BT.readStringUntil('\n'); //Read what we recevive
    Serial.print("Received : "); Serial.println(bufferIn);
    ESP_BT.print("Your given SSID is : "); ESP_BT.println(bufferIn);
    ESP_BT.println("If it is correct please send the command YES"); ESP_BT.println("Otherwise send any letter");
    delay(20);

    while (ssidSave() == false) {
      btLed.ledBlink (LOW, 200);

    }

    return true;

  }
  else return false;
}
boolean passwordRead() {

  if (ESP_BT.available()) //Check if we receive anything from Bluetooth
  {
    bufferIn = ESP_BT.readStringUntil('\n'); //Read what we recevive
    Serial.print("Received : "); Serial.println(bufferIn);
    ESP_BT.print("Your given password is : "); ESP_BT.println(bufferIn);
    ESP_BT.println("If it is correct please send the command YES"); ESP_BT.println("Otherwise send any letter");
    delay(20);

    while (passwordSave() == false) {
      btLed.ledBlink (LOW, 200);

    }
    return true;
  }

  else return false;

}

boolean ssidSave() {
  if (ESP_BT.available()) //Check if we receive anything from Bluetooth
  {
    String bufferConfirmYes = ESP_BT.readStringUntil('\n'); //Read what we recevive
    Serial.print("Received : "); Serial.println(bufferConfirmYes);
    bufferConfirmYesValue = bufferConfirmYes.substring(0, 3);
    delay(20);
    if (bufferConfirmYesValue.equals("YES")) {
      ESP_BT.println("Saving SSID to EEPROM...");
      Serial.println("Saving SSID to EEPROM...");
      for (int i = 0; i < bufferIn.length(); i++)
      { val = (byte)(bufferIn.charAt(i));
        EEPROM.write(addr, val);
        addr++;
      }
      EEPROM.write(addr, 10);
      addr++;
      EEPROM.commit();
      ESP_BT.println("SSID Stored Successfully");
      Serial.println("SSID Stored Successfully");
      return true;

    }
    else {
      ESP_BT.println("SSID not saved");
      Serial.println("SSID not saved");
      return true;
    }
  }
  else return false;
}

boolean passwordSave() {
  if (ESP_BT.available()) //Check if we receive anything from Bluetooth
  {
    String bufferConfirmYes = ESP_BT.readStringUntil('\n'); //Read what we recevive
    Serial.print("Received:"); Serial.println(bufferConfirmYes);
    bufferConfirmYesValue = bufferConfirmYes.substring(0, 3);
    delay(20);
    if (bufferConfirmYesValue.equals("YES")) {
      ESP_BT.println("Saving password to EEPROM...");
      Serial.println("Saving password to EEPROM...");
      for (int i = 0; i < bufferIn.length(); i++)
      { val = (byte)(bufferIn.charAt(i));
        EEPROM.write(addr, val);
        addr++;
      }
      EEPROM.write(addr, 10);
      addr++;
      EEPROM.commit();
      ESP_BT.println("password Stored Successfully");
      Serial.println("password Stored Successfully");
      return true;

    }
    else {
      ESP_BT.println("password not saved");
      Serial.println("password not saved");
      return true;
    }
  }
  else return false;
}
