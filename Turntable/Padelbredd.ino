void padelbredd(){
  //om på givaren backa undan
  for (byte a = 0; a < 100; a++) {
    if (digitalRead(Zeropos) == HIGH) {
      Serial.println("Står på givaren, Backar undan");
      Direction = Moturs;    // Rotera negativ riktning
      setspeed = slowspeed;  //sätt hastighet före att backa
      while (digitalRead(Zeropos) == HIGH) {
        Speedhandling(setspeed);
        delay(1);
      }
      for (int a = 0; a < 50; a++) {  //backa lite till
        Speedhandling(setspeed);
        delay(10);
      }
      setspeed = 0;               //Stoppa skivan
      while (currentspeed > 0) {  //Låt skivan stanna
        Speedhandling(setspeed);
        delay(1);
      }
    }  //Slut backat undan från givaren
    //hitta början på paddel
    Direction = Medurs;     // Rotera positiv riktning
    setspeed = creepspeed;  //sätt hastighet 
    while (digitalRead(Zeropos) == LOW) {
      Speedhandling(setspeed);
    }
    master_count = 0;
    for (int a = 0; a < 5; a++) {  //kör lite till
      Speedhandling(setspeed);
      delay(2);
    }
    while (digitalRead(Zeropos) == HIGH) {
      Speedhandling(setspeed);
    }
    int padellength = master_count;
    Serial.println(padellength);
    for (int a = 0; a < 100; a++) {  //kör lite till
      Speedhandling(setspeed);
      delay(1);
    }
    setspeed = 0;
    Speedhandling(setspeed);
  }



}