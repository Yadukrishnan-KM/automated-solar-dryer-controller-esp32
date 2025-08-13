
void localControlButtonRead() {

  static int button1Count;
  static int button2Count;
  static int button3Count;
  static int button4Count;
  static int button5Count;

  if (localButtonControlCounter) {
    button1Count = 0;
    button2Count = 0;
    button3Count = 0;
    button4Count = 0;
    button5Count = 0;
    localButtonControlCounter = false;
  }
  Serial.println(localButtonControlCounter);

  buttonValue  = analogRead(LocalButtonPin);        // Reading potentiometer value
  Serial.println(buttonValue);
  if (abs(buttonValue) < buttonThreshold) button1Count++;
  else button1Count = 0;
  if (abs(buttonValue - 410) < buttonThreshold) button2Count++;
  else button2Count = 0;
  if (abs(buttonValue - 1160) < buttonThreshold) button3Count++;
  else button3Count = 0;
  if (abs(buttonValue - 1860) < buttonThreshold) button4Count++;
  else button4Count = 0;
  if (abs(buttonValue - 2770) < buttonThreshold) button5Count++;
  else button5Count = 0;
  if (button1Count == LocalControlSwitchIntervelCount) localSwitchRoom1Fan = !localSwitchRoom1Fan;
  if (button2Count == LocalControlSwitchIntervelCount) localSwitchRoom1Valve = !localSwitchRoom1Valve;
  if (button3Count == LocalControlSwitchIntervelCount) localSwitchRoom2Fan = !localSwitchRoom2Fan;
  if (button4Count == LocalControlSwitchIntervelCount) localSwitchRoom2Valve = !localSwitchRoom2Valve;
  if (button5Count == LocalControlSwitchIntervelCount) localSwitchOutsidePump = !localSwitchOutsidePump;

}
