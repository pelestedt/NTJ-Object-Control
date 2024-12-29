void Kalibrera() {
  //Serial.print("Kalibrering startad, ");
  kalibreringsfas = 1;
  //om if (digitalRead(Zeropos) == HIGH) backa undan från givaren
  if (digitalRead(Zeropos) == HIGH) {
    Serial.println("Står på givaren, Backar undan");
    Direction = Moturs;    // Rotera negativ riktning
    setspeed = slowspeed;  //sätt hastighet före att backa
    while (digitalRead(Zeropos) == HIGH) {
      Speedhandling(setspeed);
      delay(1);
    }
    for (int a=0;a<100;a++) {
    Speedhandling(setspeed);
      delay(10);
    }
    setspeed = 0;               //Stoppa skivan
    while (currentspeed > 0) {  //Låt skivan stanna
      Speedhandling(setspeed);
      delay(1);
    }
  }  //Slut backat undan från givaren
  //Sök nollpunkten i framåtriktningen
  Direction = Medurs;  // Rotera positiv riktning
  setspeed = fullspeed;
  
  Serial.println("Sök givaren framåt i Full fart");
  while (digitalRead(Zeropos) == LOW) {
    Speedhandling(setspeed);
    delay(1);
  }
  Serial.println("nollpos hittad");
  setspeed = 0;               //stanna skivan
  while (currentspeed > 0) {  //Låt skivan stanna
    Speedhandling(setspeed);
    delay(1);
  }
  //Backa tillbaks
  Serial.println("Backar från givaren");
  Direction = Moturs;                   // Rotera negativ riktning
  setspeed = slowspeed;                 //sätt hastighet för att backa
  unsigned long backningstid = millis() + 3000;  //backa i tre sekunder
  while (millis() < backningstid) {
    Speedhandling(setspeed);
    delay(1);
  }
  setspeed = 0;               //Stoppa skivan
  while (currentspeed > 0) {  //Låt skivan stanna
    Speedhandling(setspeed);
    delay(1);
  }
  Direction = Medurs;  // Rotera positiv riktning
  //kryp famåt till nollpunkten
  setspeed = creepspeed;

  Serial.println("startar kryp framåt till givaren, ");
  seekzero = 1;
  while (digitalRead(Zeropos) == LOW) {
    Speedhandling(setspeed);
    delay(1);
  }
  //master_count = 0;
  setspeed = 0;               //stanna skivan
  while (currentspeed > 0) {  //Låt skivan stanna
    Speedhandling(setspeed);
    delay(1);
  }
  Serial.println("nollpos hittad kalibrering klar");
  set_tablepos = master_count;
  kalibreringsfas = 0;
}  //kalibrering färdig
