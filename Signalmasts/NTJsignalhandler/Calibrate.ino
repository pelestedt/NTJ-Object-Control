void Calibratetime() {
  byte t = 2;
  inputString.trim();
  String ct = "";
  ct.reserve(4);
  while (inputString.charAt(t) != ',') {
    ct += (inputString.charAt(t));
    t++;
  }
  Calibrationtime = ct.toInt();
  if (Calibrationtime > 0) {  //start calibration
    //Serial.println("Start calibration ");
    starttime=micros();
    Calibrationdata=Calibrationtime;
  }
int Calibrationend = ct.toInt();
  if (0 == Calibrationend) {  //end calibration
    //Serial.println("End Calibration ");
    endtime=micros();
    unsigned long time=endtime-starttime;
    time=time/Calibrationdata;
    ticspersec=time/1000;
    //Serial.println(time);
    //lagra intensity DCC address
  EEPROM.write(450, highByte(ticspersec));
  EEPROM.write(451, lowByte(ticspersec));
  }
}