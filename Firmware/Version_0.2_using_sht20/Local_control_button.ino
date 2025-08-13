
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
  //Serial.println(localButtonControlCounter);

  buttonValue  = analogRead(LocalButtonPin);        // Reading potentiometer value
  //Serial.println(buttonValue);
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
  //Serial.print ("pump state is"); Serial.println (localSwitchOutsidePump);

}

void localButtonStateChangeDetection() {

  if (oldLocalSwitchRoom1Fan != localSwitchRoom1Fan) {
    room1FanStatus = !room1FanStatus;
    oldLocalSwitchRoom1Fan = localSwitchRoom1Fan;
    localSwitchRoom1FanStateChange = true;
  }
  if (oldLocalSwitchRoom1Valve != localSwitchRoom1Valve) {
    room1ValveStatus = !room1ValveStatus;
    oldLocalSwitchRoom1Valve = localSwitchRoom1Valve;
    localSwitchRoom1ValveStateChange = true;
  }
  if (oldLocalSwitchRoom2Fan != localSwitchRoom2Fan) {
    room2FanStatus = !room2FanStatus;
    oldLocalSwitchRoom2Fan = localSwitchRoom2Fan;
    localSwitchRoom2FanStateChange = true;
  }
  if (oldLocalSwitchRoom2Valve != localSwitchRoom2Valve) {
    room2ValveStatus = !room2ValveStatus;
    oldLocalSwitchRoom2Valve = localSwitchRoom2Valve;
    localSwitchRoom2ValveStateChange = true;
  }
  if (oldLocalSwitchOutsidePump != localSwitchOutsidePump) {
    outsidePumpStatus = !outsidePumpStatus;
    oldLocalSwitchOutsidePump = localSwitchOutsidePump;
    localSwitchOutsidePumpStateChange = true;
  }
  if (localSwitchRoom1FanStateChange || localSwitchRoom1ValveStateChange || localSwitchRoom2FanStateChange || localSwitchRoom2ValveStateChange || localSwitchOutsidePumpStateChange) masterStateChange = true;
  //Serial.print("masterStateChange on tssk");Serial.println(masterStateChange);

}
