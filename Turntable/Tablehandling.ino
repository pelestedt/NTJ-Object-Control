void Tablehandling() {
  // Hitta vilken position vändskivan skall ha
  // faktiskt läge fins i master_count
  // Önskat läge finns i set_tablepos
  //Serial.println(Lastrotation);
  if (set_tablepos != master_count) {
    //räkna ut hur många pulser det tar att rotera till ny position
    //digitalWrite(Warninglamp, HIGH);
    distance = set_tablepos - master_count;
    distance = abs(distance);
/*
    if (distance < 2) {
      Serial.print("Distans ");
      Serial.print(distance);
      Serial.print(" / ");
      Serial.print(master_count);
      Serial.print(" / ");
      Serial.println(set_tablepos);
    }
    //Serial.print(" / ");
    */
    //räkna ut vilket håll bordet skall rotera och hur många pulser det är kvar att rotera
    if (set_tablepos > master_count && distance < halfturn && distance > 100) {
      Rotation = 1;
      Direction = Medurs;  // Rotera positiv riktning
    }
    if (set_tablepos > master_count && distance > halfturn && distance > 100) {
      Rotation = 0;
      Direction = Moturs;  // Rotera negativ riktning
      distance = fullturn - distance;
    }
    if (master_count > set_tablepos && distance < halfturn && distance > 100) {
      Rotation = 0;
      Direction = Moturs;  // Rotera negativ riktning
    }
    if (master_count > set_tablepos && distance > halfturn && distance > 100) {
      Rotation = 1;
      Direction = Medurs;  // Rotera positiv riktning
      distance = fullturn - distance;
    }

    //rotera uträknat antal pulser

    //Justera för glapp i växellåda

    if (Rotation == 1 && Lastrotation == 0 && distance > 500) {
      master_count = master_count - adjustm;
      Serial.println("Dragit bort justering");
    }
    if (Rotation == 0 && Lastrotation == 1 && distance > 500) {
      master_count = master_count + adjustm;
      Serial.println("Lagt till justering");
    }
    Lastrotation = Rotation;
    if (distance > 2000) {
      setspeed = fullspeed;
      //digitalWrite(Warninglamp, HIGH);
      //Lastrotation = Rotation;
    }
    if (distance <= 2000 && distance > 1500) {
      setspeed = mediumspeed;
      //digitalWrite(Warninglamp, HIGH);
    }
    if (distance <= 1500 && distance > 1000) {
      setspeed = slowspeed;
      //digitalWrite(Warninglamp, HIGH);
    }
    if (distance <= 1000 && distance > 500) {
      setspeed = slowspeed;
      //digitalWrite(Warninglamp, HIGH);
    }
    if (distance <= 500) {
      setspeed = creepspeed;
      //digitalWrite(Warninglamp, HIGH);
    }


    //if (master_count == set_tablepos && distance < 3) {

    if (distance < 3) {
      setspeed = 0;
      set_tablepos = master_count;
      //digitalWrite(Warninglamp, LOW);
      /*Serial.print("Rotation/Lastrotation ");
      Serial.print(Rotation);
      Serial.print("/");
      Serial.println(Lastrotation);*/
    }
    //styr hastigheten mot det nya värdet, Sätt "setspeed" till värde som passar mot kvarvarande distans
    //1 varv på skivan är många pulser. Max hastighet på motorn är 100pulser per sekund
    //minhastigheten torde vara ca 10pulser/sekund
    //hastighet sätts till pulser/sekund
    //setspeed=0;

    //När setspeed == 0 Sätt rätt polaritet på spåret



  }  //slut på hantering av rörelse

}  //Slut på subrutin
