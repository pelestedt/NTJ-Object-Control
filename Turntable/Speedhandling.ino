void Speedhandling(int set) {

  if (set > 0) {
    sampletime = 50;
    if (set == creepspeed) sampletime = 50;
    currentspeed = pulsetime;
    if (millis() - lastsamp > sampletime) {
      //currentspeed = 1000000 / pulsetime;
      //if (currentspeed > 100000) currentspeed = 0;
      //Serial.print(pulsetime); Serial.print("  "); Serial.print(10 * set); Serial.print("  "); Serial.println(currentspeed);
      //Serial.println(master_count-lastcount);

      if (lastcount == master_count && set > 0) {
        standstill++;
        pwm++;
      }
      if (standstill > 5) {
        standstill = 0;
        currentspeed = 0;
        pulsetime = 50000;
        Serial.println("Stannat");
      }

      lastcount = master_count;
      lastsamp = millis();
      int error = 1;
      if (abs(currentspeed - set) < 100) error = 1;
      if (abs(currentspeed - set) > 100) error = 2;
      if (abs(currentspeed - set) > 500) error = 3;
      if (abs(currentspeed - set) > 1000) error = 5;
      if (abs(currentspeed - set) > 1500) error = 7;
      if (abs(currentspeed - set) > 2000) error = 10;

      /*
      Serial.print(currentspeed);
      Serial.print(" / ");
      Serial.print(set);
      Serial.print(" / ");
      Serial.print(pwm);
      Serial.print(" / ");
      Serial.println(currentspeed - set);
      */
      if (currentspeed < set) pwm = pwm - error;
      if (currentspeed > set) {
        pwm = pwm + error;
        standstill = 0;
      }
      if (pwm > 1024) pwm = 1024;
      if (set > 0 && pwm <= minpwm) {
        pwm = minpwm;
      }

      //Serial.println(pwm);
      /*
    if (pwm > 1024) pwm = 1024;
    if (set > 0 && pwm <= minpwm ) {
      pwm = minpwm;
      }
    if (set > 0 && standstill == 0) {
      pwm = pwm + 3;

      //Serial.println(" pwm ökat 3");
    }
    if (set == 0) {
      pwm = 0;
      error = 0;
      currentspeed = 0;
    }
    */
      if (Medurs == Direction) {
        digitalWrite(REW, LOW);
        analogWrite(FWD, pwm);
      }
      if (Moturs == Direction) {
        digitalWrite(FWD, LOW);
        analogWrite(REW, pwm);
      }

      //if(currentspeed>0)Serial.println(currentspeed);
      //Serial.println(currentspeed);
    }
  }
  if (set == 0) {
    digitalWrite(FWD, LOW);
    digitalWrite(REW, LOW);
    pwm = 0;
    if(pulsetime>10000)currentspeed=0;
  }
}  //Slut rutin
