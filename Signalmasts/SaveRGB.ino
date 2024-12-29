void SaveRGB() {
  Serial.println("Startar lagring av RGBvärden");
  EEPROM.write(97, 123);
    delay(1);
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
} //Slut på rutin
