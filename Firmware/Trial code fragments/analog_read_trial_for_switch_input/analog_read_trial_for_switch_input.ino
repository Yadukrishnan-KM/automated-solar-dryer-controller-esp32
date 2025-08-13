// def for local control button read
#define LocalButtonPin 34                     // Local control bitton connection pin (analog pin in esp32)
#define LocalControlSwitchIntervelCount 150

// variable for local control button read
int buttonValue = 0;
int buttonThreshold = 200;
boolean localButtonControlCounter = true;
boolean localSwitchRoom1Fan;
boolean localSwitchRoom1Valve;
boolean localSwitchRoom2Fan;
boolean localSwitchRoom2Valve;
boolean localSwitchOutsidePump;

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(33, OUTPUT);
}

void loop() {
  localControlButtonRead();
  
  if(localSwitchRoom1Fan)digitalWrite(25, HIGH);
  else digitalWrite(25, LOW);
  if(localSwitchRoom1Valve)digitalWrite(26, HIGH);
  else digitalWrite(26, LOW);
  if(localSwitchRoom2Fan)digitalWrite(33, HIGH);
  else digitalWrite(33, LOW);

    /*if(localSwitchRoom2Valve){
    digitalWrite(26, HIGH);
    digitalWrite(33, HIGH);}
    else {
    digitalWrite(26, LOW);
    digitalWrite(33, LOW);}

    if(localSwitchOutsidePump){
      digitalWrite(26, HIGH);
    digitalWrite(25, HIGH);}
    else {
      digitalWrite(26, LOW);
    digitalWrite(25, LOW);}*/
    delay(20);

}
