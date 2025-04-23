void sendAspects() {
  //Serial.println("Skickar aspekter");
  int m = Aspects_baseaddr;
  String utdata;
  for (int s = 0; s < 32 ; s++) {
    Serial.print(EEPROM.read(m) * 256 + EEPROM.read(m + 1));
    m = m + 2;
    Serial.print(",");
    Serial.print(EEPROM.read(m));
    m++;
    Serial.print(",");
    Serial.print(EEPROM.read(m));
    Serial.print("$");
    m++;
  }
Serial.println("");
}
