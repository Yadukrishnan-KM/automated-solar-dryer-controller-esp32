TaskHandle_t Task1;

const int led_1 = 26;
const int led_2 = 25;

void setup() {
  Serial.begin(115200); 
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);

  xTaskCreatePinnedToCore(Task1code,"Task1",10000,NULL,1,&Task1,0);                         
  delay(500); 
}



void loop() {
   Serial.print("Task1 is running on core ");
  Serial.println(xPortGetCoreID());
  digitalWrite(led_2, HIGH);
    delay(1000);
    digitalWrite(led_2, LOW);
    delay(1000);
}


void Task1code( void * parameter ){
  Serial.print("Task1 is running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    digitalWrite(led_1, HIGH);
    delay(500);
    digitalWrite(led_1, LOW);
    delay(500);
     Serial.print("Task1 is running on core ");
  Serial.println(xPortGetCoreID());
  } 
}
