void SaveIntensity() {
  Serial.println("Startar lagring av intensitetsinstallningar");
  EEPROM.write(402, 123);
  delay(1);
  EEPROM.commit();
  //Extrahera datapost efter datapost och lagra
  int t = 2;
  inputString.trim();
  Serial.println(inputString);
  int part[6];
  for (int a = 0; a < 6; a++) {
    // String in= "";
    //in.reserve(5);
    while (inputString.charAt(t) != ',') {
      in += inputString.charAt(t);
      t++;
    }
    //Serial.println("");
    t++;
    part[a] = in.toInt();
    in = "";
  }
  //lagra day intensity
  EEPROM.write(adr_dayintensity, part[0]);
  //lagra night intensity
  EEPROM.write(adr_nightintensity, part[1]);
  //lagra intensity DCC address
  EEPROM.write(adr_DCChigh, highByte(part[2]));
  EEPROM.write(adr_DCClow, lowByte(part[2]));
  //lagra periodtid
  EEPROM.write(adr_periodhigh, highByte(part[3]));
  EEPROM.write(adr_periodlow, lowByte(part[3]));
  //lagra mörk del
  EEPROM.write(adr_dark, part[4]);
  //lagra ramp
  EEPROM.write(adr_ramp, part[5]);
  Serial.println("sparat intensitet");
  for (int p = 0; p < 6; p++) Serial.println(part[p]);
EEPROM.commit();
}  //Slut på rutin
