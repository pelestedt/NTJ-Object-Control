void sendIntensity() {
  Serial.print(EEPROM.read(adr_dayintensity)); //Dayintensity
  Serial.print(",");
  Serial.print(EEPROM.read(adr_nightintensity)); //Nightintensity
  Serial.print(",");
  Serial.print(EEPROM.read(adr_DCChigh) * 256 + EEPROM.read(adr_DCClow)); //DCCadress
  Serial.print(",");
  Serial.print(EEPROM.read(adr_periodhigh) * 256 + EEPROM.read(adr_periodlow)); //Periodtid
  Serial.print(",");
  Serial.print(EEPROM.read(adr_dark)); //Mörkt
  Serial.print(",");
  Serial.print(EEPROM.read(adr_ramp)); //Ramp
  Serial.println(",");
}
