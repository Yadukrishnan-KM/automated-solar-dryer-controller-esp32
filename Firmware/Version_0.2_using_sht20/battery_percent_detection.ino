int batteryPercetDetection(){
  int voltage;
  voltage = analogRead(liIonCellVolatgePin);
  if (voltage >= 4066) batteryPercent = 100;
  else if (voltage >= 4018) batteryPercent = 95;
  else if (voltage >= 3824) batteryPercent = 90;
  else if (voltage >= 3756) batteryPercent = 80;
  else if (voltage >= 3679) batteryPercent = 70;
  else if (voltage >= 3621) batteryPercent = 60;
  else if (voltage >= 3582) batteryPercent = 50;
  else if (voltage >= 3543) batteryPercent = 40;
  else if (voltage >= 3514) batteryPercent = 30;
  else if (voltage >= 3485) batteryPercent = 20;
  else if (voltage >= 3389) batteryPercent = 10;
  else if (voltage >= 3195) batteryPercent = 5;
  else if (voltage >= 2904) batteryPercent = 1;
}
