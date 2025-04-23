void SaveRGB() {
  Serial.println("Startar lagring av RGBvarden");
  EEPROM.write(401, 123);
    delay(1);
    EEPROM.commit();
  //Extrahera datapost efter datapost och lagra
  int t = 2;
  String indata;
  byte RGBdata=0;
  for (int a = 0; a < 12; a++) {
    while (inputString.charAt(t) != ',') {
      indata += inputString.charAt(t);
      t++;
       }
           RGBdata = indata.toInt();
    indata = "";
    EEPROM.write(RGB_baseaddr+a, RGBdata);
       t++;
  }//RGBdata sparad
  EEPROM.commit();
} //Slut på rutin
