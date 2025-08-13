#include <Wire.h>
#include "SHT2x.h"


#define SDA_1 21
#define SCL_1 22

#define SDA_2 33
#define SCL_2 32
TwoWire I2Cone = TwoWire(0);
TwoWire I2Ctwo = TwoWire(1);

SHT2x sht1;
SHT2x sht2;

void setup()
{
Serial.begin(9600);

 I2Cone.begin(SDA_1, SCL_1, 100000); 
  I2Ctwo.begin(SDA_2, SCL_2, 100000);
  
Serial.println("SHT20 Example!");


delay(100);


sht1.begin(0x40, &I2Cone);  
  
sht2.begin(0x40, &I2Ctwo);  

  
  Serial.println();

}

void loop()
{

float humd = sht1.readHumidity(); // Read Humidity
float temp = sht1.readTemperature(); // Read Temperature
Serial.print("Temperature1:");
Serial.print(temp, 1);
Serial.print("C");
Serial.print(" Humidity1:");
Serial.print(humd, 1);
Serial.print("%");
Serial.println();
delay(1000);

float humd1 = sht2.readHumidity(); // Read Humidity
float temp1 = sht2.readTemperature(); // Read Temperature
Serial.print("Temperature2:");
Serial.print(temp, 1);
Serial.print("C");
Serial.print(" Humidity2:");
Serial.print(humd, 1);
Serial.print("%");
Serial.println();
delay(1000);
}
