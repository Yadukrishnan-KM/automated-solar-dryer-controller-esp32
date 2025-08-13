void minMaxValues(){
  
  static int room1HighTempCount;
  static int room1LowTempCount;
  static int room1HighHumdCount;
  static int room1LowHumdCount;
  static int room2HighTempCount;
  static int room2LowTempCount;
  static int room2HighHumdCount;
  static int room2LowHumdCount;
  static int outsideHighTempCount;
  static int outsideLowTempCount;
  static int outsideHighHumdCount;
  static int outsideLowHumdCount;
  
  if(maxAndMinValueCounter == 0){
    
  room1HighTempCount = 0;
  room1LowTempCount = 0;
  room1HighHumdCount = 0;
  room1LowHumdCount = 0;
  room2HighTempCount = 0;
  room2LowTempCount = 0;
  room2HighHumdCount = 0;
  room2LowHumdCount = 0;
  outsideHighTempCount = 0;
  outsideLowTempCount = 0;
  outsideHighHumdCount = 0;
  outsideLowHumdCount = 0;
    
  }
  
  maxAndMinValueCounter = 1;
  
  if(room1MaxTemp < room1Temp) room1HighTempCount++;
  else room1HighTempCount = 0;
  if(room1HighTempCount == 2){
    room1HighTempCount = 0;
    room1MaxTemp = room1Temp;
  }
  if(room1MinTemp > room1Temp)room1LowTempCount++;
  else room1LowTempCount = 0;
  if(room1LowTempCount == 2){
    room1LowTempCount = 0;
    room1MinTemp = room1Temp;
  }
  if(room1MaxHumidity < room1Humidity) room1HighHumdCount++;
  else room1HighHumdCount = 0;
  if(room1HighHumdCount == 2){
    room1HighHumdCount = 0;
    room1MaxHumidity = room1Humidity;
  }
  if(room1MinHumidity > room1Humidity) room1LowHumdCount++;
  else room1LowHumdCount = 0;
  if(room1LowHumdCount == 2){
    room1LowHumdCount = 0;
    room1MinHumidity = room1Humidity;
  }
  
  if(room2MaxTemp < room2Temp) room2HighTempCount++;
  else room2HighTempCount = 0;
  if(room2HighTempCount == 2){
    room2HighTempCount = 0;
    room2MaxTemp = room2Temp;
  }
  if(room2MinTemp > room2Temp) room2LowTempCount++;
  else room2LowTempCount = 0;
  if(room2LowTempCount == 2){
    room2LowTempCount = 0;
    room2MinTemp = room2Temp;
  }
  if(room2MaxHumidity < room2Humidity) room2HighHumdCount++;
  else room2HighHumdCount = 0;
  if(room2HighHumdCount == 2){
    room2HighHumdCount = 0;
    room2MaxHumidity = room2Humidity;
  }
  if(room2MinHumidity > room2Humidity) room2LowHumdCount++;
  else room2LowHumdCount = 0;
  if(room2LowHumdCount == 2){
    room2LowHumdCount = 0;
    room2MinHumidity = room2Humidity;
  }

  if(outsideMaxTemp < outsideTemp) outsideHighTempCount++;
  else outsideHighTempCount = 0;
  if(outsideHighTempCount == 2){
    outsideHighTempCount = 0;
    outsideMaxTemp = outsideTemp;
  }
  if(outsideMinTemp > outsideTemp) outsideLowTempCount++;
  else outsideLowTempCount = 0;
  if(outsideLowTempCount == 2){
    outsideLowTempCount = 0;
    outsideMinTemp = outsideTemp;
  }
  if(outsideMaxHumidity < outsideHumidity) outsideHighHumdCount++;
  else outsideHighHumdCount = 0;
  if(outsideHighHumdCount == 2){
    outsideHighHumdCount = 0;
    outsideMaxHumidity = outsideHumidity;
  }
  if(outsideMinHumidity > outsideHumidity) outsideLowHumdCount++;
  else outsideLowHumdCount = 0;
  if(outsideLowHumdCount == 2){
    outsideLowHumdCount = 0;
    outsideMinHumidity = outsideHumidity;
  }
}
