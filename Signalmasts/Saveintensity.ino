void SaveIntensity() {
  Serial.println("Startar lagring av intensitetsinställningar");
    EEPROM.write(96, 123);
    delay(1);
  //Extrahera datapost efter datapost och lagra
  int t = 2;
  String in="";
  int part[6];
  for (int a = 0; a < 6; a++) {
    while (inputString.charAt(t) != ',') {
      in += inputString.charAt(t);
            t++;
          }
          Serial.print(" ");
          t++;
     part[a]=in.toInt(); 
        in="";
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
  
  } //Slut på rutin
