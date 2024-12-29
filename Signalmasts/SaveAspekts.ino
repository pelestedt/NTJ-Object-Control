void SaveAspekts() {
  Serial.println("Startar programmering av EEPROM");
  //skriv 123 i addr 600 för att markera att den programmerats
  EEPROM.write(95, 123);
  delay(1);
  //Extrahera datapost efter datapost och lagra
  int t = 2;
  int mem = Aspects_baseaddr;
  String nr;
  String adr;
  String asp;
  String rot;
  Serial.println(inputString);
  while (inputString.charAt(t) != ',') {
    nr += inputString.charAt(t);
    t++;
  }
  Serial.println(nr);
  t++;
  while (inputString.charAt(t) != ',') {
    adr += inputString.charAt(t);
    t++;
  }
  Serial.println(adr);
  t++;
  while (inputString.charAt(t) != ',') {
    asp += inputString.charAt(t);
    t++;
  }
  Serial.println(asp);
  t++;
  while (inputString.charAt(t) != '$') {
    rot += inputString.charAt(t);
    t++;
  }
  Serial.println(rot);
  t++;
  byte nummer = nr.toInt();
  int address = adr.toInt();
  byte typ = asp.toInt();
  byte rotated = rot.toInt();


  //Serial.print(address); Serial.print("/"); Serial.print(typ); Serial.print("/"); Serial.println(rotated);
  mem = (Aspects_baseaddr - 4) + (nummer * 4);
  EEPROM.write(mem, highByte(address));
  mem++;
  EEPROM.write(mem, lowByte(address));
  mem++;
  EEPROM.write(mem, typ);
  mem++;
  EEPROM.write(mem, rotated);

  Serial.println("sparat Aspekt");

} //Slut på rutin*/
