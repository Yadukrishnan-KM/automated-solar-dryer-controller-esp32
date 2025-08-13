
//////////////////////// Reading device status data from firebase /////////////////////////////////

boolean readFirebase () {
  String state;

  if (!Firebase.get(firebaseData, "/Dryer_Room_1/Fan_Status")) return false;
  state = firebaseData.stringData();
  state =  state.substring(1, 2);
  if (state == "1") room1FanStatus = true;
  else if (state == "0") room1FanStatus = false;

  if (!Firebase.get(firebaseData, "/Dryer_Room_1/Valve_Status")) return false;
  state = firebaseData.stringData();
  state =  state.substring(1, 2);
  if (state == "1") room1ValveStatus = true;
  else if (state == "0") room1ValveStatus = false;

  if (!Firebase.get(firebaseData, "/Dryer_Room_2/Fan_Status")) return false;
  state = firebaseData.stringData();
  state =  state.substring(1, 2);
  if (state == "1") room2FanStatus = true;
  else if (state == "0") room2FanStatus = false;

  if (!Firebase.get(firebaseData, "/Dryer_Room_2/Valve_Status")) return false;;
  state = firebaseData.stringData();
  state =  state.substring(1, 2);
  if (state == "1") room2ValveStatus = true;
  else if (state == "0") room2ValveStatus = false;

  if (!Firebase.get(firebaseData, "/Outside/Pump_Status")) return false;
  state = firebaseData.stringData();
  state =  state.substring(1, 2);
  if (state == "1") outsidePumpStatus = true;
  else if (state == "0") outsidePumpStatus = false;
  Serial.println("Reading data from firebase was successfull");
  digitalWrite( firebaseLedPin, LOW);
  delay(50);
  digitalWrite( firebaseLedPin, HIGH);
  return true;
}


//////////////////////// Room 1 Device Control /////////////////////////////////

int room1FanOutputControl() {
  if (room1FanStatus && powerStatus) {
    if (room1FanCondition0) {
      if (room1FanCondition1) {
        room1FanCounter = millis();
        room1FanCondition1 = false;
      }
      unsigned long currentcount = millis();
      if ((currentcount - room1FanCounter) >= remoteControlSaftyTime ) {
        room1FanLed.cancelLedBlink(HIGH);
        //buzzer.cancelLedBlink(LOW);
        digitalWrite (room1FanOutputPin, HIGH);
        room1FanCondition0 = false;
        return 3;
      }
      else {
        //buzzer.ledBlink (HIGH, 500);
        room1FanLed.ledBlink (HIGH, 500);
        return 2;
      }
    }
    else {
      room1FanLed.cancelLedBlink(HIGH);
      //buzzer.cancelLedBlink(LOW);
      digitalWrite (room1FanOutputPin, HIGH);
      return 3;
    }

  }
  if (!room1FanStatus) {
    room1FanLed.cancelLedBlink(LOW);
    //buzzer.cancelLedBlink(LOW);
    digitalWrite (room1FanOutputPin, LOW);
    room1FanCondition1 = true;
    room1FanCondition0 = true;
    return 0;
  }
  if (!powerStatus) {
    room1FanLed.cancelLedBlink(LOW);
    //buzzer.cancelLedBlink(LOW);
    digitalWrite (room1FanOutputPin, LOW);
    room1FanCondition1 = true;
    room1FanCondition0 = true;
    return 4;
  }
}

int room1ValveOutputControl() {
  if (room1ValveStatus && powerStatus) {
    if (room1ValveCondition0) {
      if (room1ValveCondition1) {
        room1ValveCounter = millis();
        room1ValveCondition1 = false;
      }
      unsigned long currentcount = millis();
      if ((currentcount - room1ValveCounter) >= remoteControlSaftyTime ) {
        room1ValveLed.cancelLedBlink(HIGH);
        //buzzer.cancelLedBlink(LOW);
        digitalWrite (room1ValveOutputPin, HIGH);
        room1ValveCondition0 = false;
        return 3;
      }
      else {
        //buzzer.ledBlink (HIGH, 500);
        room1ValveLed.ledBlink (HIGH, 500);
        return 2;
      }
    }
    else {
      room1ValveLed.cancelLedBlink(HIGH);
      //buzzer.cancelLedBlink(LOW);
      digitalWrite (room1ValveOutputPin, HIGH);
      return 3;
    }

  }
  if (!room1ValveStatus) {
    room1ValveLed.cancelLedBlink(LOW);
    //buzzer.cancelLedBlink(LOW);
    digitalWrite (room1ValveOutputPin, LOW);
    room1ValveCondition1 = true;
    room1ValveCondition0 = true;
    return 0;
  }
  if (!powerStatus) {
    room1ValveLed.cancelLedBlink(LOW);
    //buzzer.cancelLedBlink(LOW);
    digitalWrite (room1ValveOutputPin, LOW);
    room1ValveCondition1 = true;
    room1ValveCondition0 = true;
    return 4;
  }
}

//////////////////////// Room 2 Device Control /////////////////////////////////

int room2FanOutputControl() {
  if (room2FanStatus && powerStatus) {
    if (room2FanCondition0) {
      if (room2FanCondition1) {
        room2FanCounter = millis();
        room2FanCondition1 = false;
      }
      unsigned long currentcount = millis();
      if ((currentcount - room2FanCounter) >= remoteControlSaftyTime ) {
        room2FanLed.cancelLedBlink(HIGH);
        //buzzer.cancelLedBlink(LOW);
        digitalWrite (room2FanOutputPin, HIGH);
        room2FanCondition0 = false;
        return 3;
      }
      else {
        //buzzer.ledBlink (HIGH, 500);
        room2FanLed.ledBlink (HIGH, 500);
        return 2;
      }
    }
    else {
      room2FanLed.cancelLedBlink(HIGH);
      //buzzer.cancelLedBlink(LOW);
      digitalWrite (room2FanOutputPin, HIGH);
      return 3;
    }

  }
  if (!room2FanStatus) {
    room2FanLed.cancelLedBlink(LOW);
    //buzzer.cancelLedBlink(LOW);
    digitalWrite (room2FanOutputPin, LOW);
    room2FanCondition1 = true;
    room2FanCondition0 = true;
    return 0;
  }
  if (!powerStatus) {
    room2FanLed.cancelLedBlink(LOW);
    //buzzer.cancelLedBlink(LOW);
    digitalWrite (room2FanOutputPin, LOW);
    room2FanCondition1 = true;
    room2FanCondition0 = true;
    return 4;
  }
}

int room2ValveOutputControl() {
  if (room2ValveStatus && powerStatus) {
    if (room2ValveCondition0) {
      if (room2ValveCondition1) {
        room2ValveCounter = millis();
        room2ValveCondition1 = false;
      }
      unsigned long currentcount = millis();
      if ((currentcount - room2ValveCounter) >= remoteControlSaftyTime ) {
        room2ValveLed.cancelLedBlink(HIGH);
        //buzzer.cancelLedBlink(LOW);
        digitalWrite (room2ValveOutputPin, HIGH);
        room2ValveCondition0 = false;
        return 3;
      }
      else {
        //buzzer.ledBlink (HIGH, 500);
        room2ValveLed.ledBlink (HIGH, 500);
        return 2;
      }
    }
    else {
      room2ValveLed.cancelLedBlink(HIGH);
      //buzzer.cancelLedBlink(LOW);
      digitalWrite (room2ValveOutputPin, HIGH);
      return 3;
    }

  }
  if (!room2ValveStatus) {
    room2ValveLed.cancelLedBlink(LOW);
   // buzzer.cancelLedBlink(LOW);
    digitalWrite (room2ValveOutputPin, LOW);
    room2ValveCondition1 = true;
    room2ValveCondition0 = true;
    return 0;
  }
  if (!powerStatus) {
    room2ValveLed.cancelLedBlink(LOW);
    //buzzer.cancelLedBlink(LOW);
    digitalWrite (room2ValveOutputPin, LOW);
    room2ValveCondition1 = true;
    room2ValveCondition0 = true;
    return 4;
  }
}

//////////////////////// Outdoor Device Control /////////////////////////////////

int outsidePumpOutputControl() {
  if (outsidePumpStatus && powerStatus) {
    if (outsidePumpCondition0) {
      if (outsidePumpCondition1) {
        outsidePumpCounter = millis();
        outsidePumpCondition1 = false;
      }
      unsigned long currentcount = millis();
      if ((currentcount - outsidePumpCounter) >= remoteControlSaftyTime ) {
        outsidePumpLed.cancelLedBlink(HIGH);
       // buzzer.cancelLedBlink(LOW);
        digitalWrite (outsidePumpOutputPin, HIGH);
        outsidePumpCondition0 = false;
        return 3;
      }
      else {
       // buzzer.ledBlink (HIGH, 500);
        outsidePumpLed.ledBlink (HIGH, 500);
        return 2;
      }
    }
    else {
      outsidePumpLed.cancelLedBlink(HIGH);
      //buzzer.cancelLedBlink(LOW);
      digitalWrite (outsidePumpOutputPin, HIGH);
      return 3;
    }

  }
  if (!outsidePumpStatus) {
    outsidePumpLed.cancelLedBlink(LOW);
    //buzzer.cancelLedBlink(LOW);
    digitalWrite (outsidePumpOutputPin, LOW);
    outsidePumpCondition1 = true;
    outsidePumpCondition0 = true;
    return 0;
  }
  if (!powerStatus) {
    outsidePumpLed.cancelLedBlink(LOW);
    //buzzer.cancelLedBlink(LOW);
    digitalWrite (outsidePumpOutputPin, LOW);
    outsidePumpCondition1 = true;
    outsidePumpCondition0 = true;
    return 4;
  }
}
