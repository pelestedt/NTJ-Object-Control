//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Decoder Init
//
void ConfigureDecoder() {
  byte mem = Aspects_baseaddr;
  //För samtliga 32 möjliga aspekter
  for (byte signalboard = 0; signalboard < 32; signalboard++) {
    //Läs in address
    byte Hbyte = EEPROM.read(mem);
    mem = mem + 1;
    byte Lbyte = EEPROM.read(mem);
    gAddresses[signalboard].address = Hbyte * 256 + Lbyte;
   
    mem = mem + 1;
    //läs in typ av aspekt
    gAddresses[signalboard].Signaltype = EEPROM.read(mem);
    mem = mem + 1;
    //    läs in om den är roterad
    gAddresses[signalboard].Rotated = EEPROM.read(mem);
    // eventuell ändring av värde från icke roterad eller roterad
    //    if(Rotation[signalboard]==255)Rotation[signalboard]=0;
    mem = mem + 1;
    gAddresses[signalboard].Signalaspect = 0;  //Sätt signalen i stopp
  }

  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)

  //
  // Find out how many LEDs thare are on the bus
  //
  // Scan through all 32 possible signals
  for (int i = 0; i < 32; i++) {
    if (pgm_read_byte(&numleds[gAddresses[i].Signaltype]) > 0) {
      Signalqty = Signalqty + 1;
      Buslength = pgm_read_byte(&numleds[gAddresses[i].Signaltype]) + Buslength;
    }
    //Serial.println(gAddresses[i].Signaltype);
  }
    
  Dayintensity = EEPROM.read(adr_dayintensity);
  intensity = Dayintensity;
  setIntensity = Dayintensity;
  Nightintensity = EEPROM.read(adr_nightintensity);
  Intensityaddr = EEPROM.read(adr_DCChigh) * 256 + EEPROM.read(adr_DCClow);
  Blinkfrq = EEPROM.read(adr_periodhigh) * 256 + EEPROM.read(adr_periodlow);
  Blinkoff = (EEPROM.read(adr_dark) * fadesteps) / 200;
  Blinkramp = (EEPROM.read(adr_ramp) * fadesteps) / 200;
  /*
  Serial.print("Number of signals: ");
  Serial.println(Signalqty);
  Serial.print("Number of LEDs: ");
  Serial.println(Buslength);
  Serial.print("Blinkfrq ");
  Serial.println(Blinkfrq);
  Serial.print("Blinkoff ");
  Serial.println(Blinkoff);
  Serial.print("Blinkramp ");
  Serial.println(Blinkramp);
  //delay(5000);
*/
  ///////////////////////////////////////////////////////////////////////////////////////////
  /*                                rampupend         rampdownstart
 *                                     _________!_ _ _ _ _! 
 *                                    /         !         \
 *                                   /          !          \
 *                                  /           !           \
 * ________________________________/            !            \ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
 *                                 !            !             !             !                     !
 *          darkperiod        rampupstart   halfperiod   rampdownend    darkperiod           fullperiod=fadesteps                         
 * 
 */
  rampupstart = Blinkoff;
  rampupend = rampupstart + Blinkramp;
  rampdownstart = fadesteps - Blinkoff - Blinkramp;
  rampdownend = fadesteps - Blinkoff;
  ticspersec = EEPROM.read(450) * 256 + EEPROM.read(451);
  if (ticspersec < 300) ticspersec = 1000;
  timebetweensteps = (Blinkfrq / fadesteps) * ticspersec;  //borde vara 1000 och inte 795 men en ms är längre än 1ms
 /*
  Serial.print("rampupstart ");
  Serial.println(rampupstart);
  Serial.print("rampupend ");
  Serial.println(rampupend);
  Serial.print("rampdownstart ");
  Serial.println(rampdownstart);
  Serial.print("rampdownend ");
  Serial.println(rampdownend);
*/
  vitR = EEPROM.read(RGB_baseaddr);
  vitG = EEPROM.read(RGB_baseaddr + 1);
  vitB = EEPROM.read(RGB_baseaddr + 2);
  redR = EEPROM.read(RGB_baseaddr + 3);
  redG = EEPROM.read(RGB_baseaddr + 4);
  redB = EEPROM.read(RGB_baseaddr + 5);
  greenR = EEPROM.read(RGB_baseaddr + 6);
  greenG = EEPROM.read(RGB_baseaddr + 7);
  greenB = EEPROM.read(RGB_baseaddr + 8);
  orangeR = EEPROM.read(RGB_baseaddr + 9);
  ;
  orangeG = EEPROM.read(RGB_baseaddr + 10);
  orangeB = EEPROM.read(RGB_baseaddr + 11);
  //Serial.println("Konfigurering klar");
}
