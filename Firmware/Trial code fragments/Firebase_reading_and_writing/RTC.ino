void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  char dateTime[26];
  strftime(dateTime, 26 , "%d %b %Y %r", &timeinfo);
  //Serial.println(dateTime);
  lastUpdatedDateTime = String(dateTime);
  //Serial.println(&timeinfo, "%d %b %Y %r");
}
