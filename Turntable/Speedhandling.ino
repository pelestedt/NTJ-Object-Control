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

/*
void Speedhandling(byte set) {
  sampletime = 50;
  if (set == Minspeed) sampletime = 50;
  currentspeed = 1000000 / pulsetime;
  if (millis() - lastsamp > sampletime) {
    //currentspeed = 1000000 / pulsetime;
    if (currentspeed > 1000) currentspeed = 0;
    //Serial.print(pulsetime); Serial.print("  "); Serial.print(10 * set); Serial.print("  "); Serial.println(currentspeed);
    //Serial.println(master_count-lastcount);
    //Serial.println(master_count);
    if (lastcount == master_count && set > 0) {
      standstill++;
      pwm++;
    }
    if (standstill > 5) {
      standstill = 0;
      currentspeed = 0;
      pulsetime = 50000;
      //Serial.println("Stannat");
    }

    //Serial.print(pulsetime); Serial.print("  /  "); Serial.print(currentspeed); Serial.print("  /  "); Serial.println(pwm);
    lastcount = master_count;
    lastsamp = millis();
    int error = 1;
    if (abs(currentspeed - (10 * set)) > 4) error = 2;
    if (abs(currentspeed - (10 * set)) > 20) error = 4;
    if (abs(currentspeed - (10 * set)) > 40) error = 6;
    if (abs(currentspeed - (10 * set)) > 60) error = 8;
    if (abs(currentspeed - (10 * set)) > 80) error = 14;
    if (abs(currentspeed - (10 * set)) > 1000) error = 1;
    if (currentspeed < set * 10) pwm = pwm + error;
    if (currentspeed > set * 10 && pwm > minpwm) {
      pwm = pwm - error;
      standstill = 0;
    }
    if (pwm > 254) {
      pwm = 254;
      pwmatmax++;
    }
    /*if (pwmatmax > 5) {
      pwm = 0;
      while (1) {
        delay(1000);
        Serial.println("Stalled");
      }
    }*/
    /*
    if(pwm<254)pwmatmax=0;
    /*if (set > 0 && pwm <= minpwm ) {
      pwm = minpwm;
      }*/
      /*
    if (set > 0 && standstill == 0) {
      pwm = pwm + 3;

      //Serial.println(" pwm ökat 3");
    }
    if (set == 0) {
      pwm = 0;
      error = 0;
      currentspeed = 0;
    }4
    analogWrite(PWM, pwm);
    //if(currentspeed>0)Serial.println(currentspeed);
    //Serial.println(currentspeed);
  }
}  //Slut rutin
