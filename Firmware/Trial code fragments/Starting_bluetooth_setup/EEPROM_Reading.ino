void eepromRead() {
  String stream;
  byte val;
  byte indS = 0;
  byte indP = 0;
  for (int i = 0; i < 50; i++)
  { val = EEPROM.read(i);
    stream += (char)val;
    if ((val == 10) && (indS == 0)) indS = i;
    else if (val == 10 && indP == 0)
    {
      indP = i;
      break;
    }
  }
  Ssid = stream.substring(0, indS);
  Password = stream.substring(indS + 1, indP);

  //int i = preSsid.length();
  //int j = prePassword.length();
  //char ssid[i];
  //char password[j];
  //preSsid.toCharArray(ssid, i);
  //prePassword.toCharArray(password, j);
}
