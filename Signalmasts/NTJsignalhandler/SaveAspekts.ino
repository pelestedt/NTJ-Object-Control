void SaveAspekts() {
  //Serial.println("Startar lagring av aspekter");
 
  //skriv 123 i addr 400 för att markera att den programmerats
  if(EEPROM.read(400) !=123)EEPROM.write(400, 123);
  delay(1);
  EEPROM.commit();
  //Extrahera datapost efter datapost och lagra
  byte t = 2;
  int mem = Aspects_baseaddr;
 
  inputString.trim();
  //Serial.print("inputString ");
  //Serial.println(inputString);
 
  String nr = "";
  nr.reserve(2);
  while (inputString.charAt(t) != ',') {
    nr += (inputString.charAt(t));
    t++;
  }
  //Serial.println(nr);
  //Serial.println("----------------------------------------------------");
  t++;
  
   String adr = "";
  adr.reserve(5);
  while (inputString.charAt(t) != ',') {
    adr += inputString.charAt(t);    
    t++;
  }
  //Serial.print("adr ");
  //Serial.println(adr);
  //Serial.println("----------------------------------------------------");
  t++;

  String asp = "";
  asp.reserve(2);
  while (inputString.charAt(t) != ',') {
    asp += inputString.charAt(t);
    //Serial.println(inputString.charAt(t));
    t++;
  }
  //Serial.print("taveltyp ");
  //Serial.println(asp);
  //Serial.println("----------------------------------------------------");
  t++;
  
   String rot = "";
  rot.reserve(1);
  while (inputString.charAt(t) != '$') {
    rot += inputString.charAt(t);
   t++;
  }
  //Serial.print("rotation ");
  //Serial.println(rot);
  //Serial.println("----------------------------------------------------");
  byte nummer = nr.toInt();
  int address = adr.toInt();
  byte typ = asp.toInt();
  byte rotated = rot.toInt();



  //Serial.print(address); Serial.print("/"); Serial.print(typ); Serial.print("/"); Serial.println(rotated);
  mem = (Aspects_baseaddr - 4) + (nummer * 4);
  EEPROM.write(mem, highByte(address));
  EEPROM.commit();
  mem++;
  EEPROM.write(mem, lowByte(address));
  EEPROM.commit();
  mem++;
  EEPROM.write(mem, typ);
  EEPROM.commit();
  mem++;
  EEPROM.write(mem, rotated);
EEPROM.commit();

}  //Slut på rutin*/
