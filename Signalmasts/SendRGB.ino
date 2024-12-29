void SendRGB() {
  //Serial.println("Startar Sändning av RGBvärden");
     for (int a = 0; a < 12; a++) {
    Serial.print(EEPROM.read(RGB_baseaddr + a)); 
    Serial.print(",");
  }
  Serial.println("");
  
  //RGBdata skickad
  Serial.println("sparat RGB");
} //Slut på rutin
