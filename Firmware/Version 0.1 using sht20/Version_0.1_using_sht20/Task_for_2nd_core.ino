void Task1code( void * parameter ) {
  Serial.print("Task1 is running on core ");
  Serial.println(xPortGetCoreID());

  for (;;) {
    room1FanFeedback = room1FanOutputControl();
    room1ValveFeedback = room1ValveOutputControl();
    room2FanFeedback = room2FanOutputControl();
    room2ValveFeedback = room2ValveOutputControl();
    outsidePumpFeedback = outsidePumpOutputControl();
    if(room1FanFeedback == 2 || room1ValveFeedback == 2 || room2FanFeedback == 2 || room2ValveFeedback == 2 || outsidePumpFeedback == 2) buzzer.ledBlink (HIGH, 500);
    else buzzer.cancelLedBlink(LOW);
    localControlButtonRead();
    delay(16);
  }
}
