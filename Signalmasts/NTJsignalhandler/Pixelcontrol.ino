void UpdateNeopixels() {
  // Scan through all LEDs
  // Transitions between aspects are handled by different status of the led
  // eher: 0 == off, 1 == on, 2 == blinking, 3 == Waiting to Fade to on, 4 fade to on, 5 == Waiting to Fade to off, 6 fade to off
  // Scan through all LEDs on the bus

  for (setLED = 0; setLED < Buslength; setLED++) {
    //Serial.print("2, ");
    // Handle red LEDs
    if (LEDcolor[setLED] == 1) {
      // LED is off
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 0) {
        pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
        currentstatus[setLED] = 0;
        //goto EndRed;
      }
      //
      // Transition from off to on
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 1) {
        currentstatus[setLED] = 3;
        ////goto EndRed;
      }
      if (currentstatus[setLED] == 3 && intensityphase == 0) {
        currentstatus[setLED] = 4;
        //goto EndRed;
      }
      if (currentstatus[setLED] == 4) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * redR / 255, Fadevalue * redG / 255, Fadevalue * redB / 255));
        //goto EndRed;
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) currentstatus[setLED] = 1;              //goto EndRed;
      if (currentstatus[setLED] == 1) pixels.setPixelColor(setLED, pixels.Color(redR, redG, redB));  //goto EndRed;
      //

      // Transition from off to blink
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 2) {
        currentstatus[setLED] = 3;
        //goto EndRed;
      }
      if (currentstatus[setLED] == 3 && intensityphase == 0) {
        currentstatus[setLED] = 4;
        //goto EndRed;
      }
      if (currentstatus[setLED] == 4) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * redR / 255, Fadevalue * redG / 255, Fadevalue * redB / 255));
        //goto EndRed;
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) currentstatus[setLED] = 2;                                                                    //goto EndRed;
      if (currentstatus[setLED] == 2) pixels.setPixelColor(setLED, pixels.Color(Fadevalue * redR / 255, Fadevalue * redG / 255, Fadevalue * redB / 255));  //goto EndRed;
      //

      // Transition from on to off
      if (currentstatus[setLED] == 1 && LEDstate[setLED] == 0) {
        currentstatus[setLED] = 5;
        //goto EndRed;
      }
      if (currentstatus[setLED] == 5 && intensityphase == 99) {
        currentstatus[setLED] = 6;
        //goto EndRed;
      }
      if (currentstatus[setLED] == 6) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * redR / 255, Fadevalue * redG / 255, Fadevalue * redB / 255));
        //goto EndRed;
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) currentstatus[setLED] = 0;    //goto EndRed;
      if (currentstatus[setLED] == 0) pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));  //goto EndRed;
      //

      // Transition from on to blink
      if (currentstatus[setLED] == 1 && LEDstate[setLED] == 2) {
        currentstatus[setLED] = 5;
        //goto EndRed;
      }
      if (currentstatus[setLED] == 5 && intensityphase == 99) {
        currentstatus[setLED] = 6;
        //goto EndRed;
      }
      if (currentstatus[setLED] == 6) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * redR / 255, Fadevalue * redG / 255, Fadevalue * redB / 255));
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) currentstatus[setLED] = 2;                                                                   //goto EndRed;
      if (currentstatus[setLED] == 2) pixels.setPixelColor(setLED, pixels.Color(Fadevalue * redR / 255, Fadevalue * redG / 255, Fadevalue * redB / 255));  //goto EndRed;
      //

      // Transition from blink to off
      if (currentstatus[setLED] == 2 && LEDstate[setLED] == 0) {
        currentstatus[setLED] = 5;
        go2off = go2off + 1;
        //goto EndRed;
      }
      if (currentstatus[setLED] == 5 && intensityphase == 99) {
        currentstatus[setLED] = 6;
        //goto EndRed;
      }
      if (currentstatus[setLED] == 6) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * redR / 255, Fadevalue * redG / 255, Fadevalue * redB / 255));
        //goto EndRed;
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 0;
        go2off = go2off - 1;
        //goto EndRed;
      }
      if (currentstatus[setLED] == 0) pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
      //
    }
    //EndRed:
    // Handle green LEDs
    if (LEDcolor[setLED] == 2) {
      // LED is off
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 0) {
        pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
        currentstatus[setLED] = 0;
      }
      // Transition from off to on
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 1 && go2off == 0) {
        currentstatus[setLED] = 3;
      }
      if (currentstatus[setLED] == 3 && intensityphase == 0) {
        currentstatus[setLED] = 4;
      }
      if (currentstatus[setLED] == 4) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * greenR / 255, Fadevalue * greenG / 255, Fadevalue * greenB / 255));
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) {
        currentstatus[setLED] = 1;
      }
      if (currentstatus[setLED] == 1) {
        pixels.setPixelColor(setLED, pixels.Color(greenR, greenG, greenB));
      }
      //

      // Transition from off to blink
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 2) {
        currentstatus[setLED] = 3;
      }
      if (currentstatus[setLED] == 3 && intensityphase == 0) {
        currentstatus[setLED] = 4;
      }
      if (currentstatus[setLED] == 4) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * greenR / 255, Fadevalue * greenG / 255, Fadevalue * greenB / 255));
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) {
        currentstatus[setLED] = 2;
      }
      if (currentstatus[setLED] == 2) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * greenR / 255, Fadevalue * greenG / 255, Fadevalue * greenB / 255));
      }

      // Transition from on to off
      if (currentstatus[setLED] == 1 && LEDstate[setLED] == 0) {
        currentstatus[setLED] = 5;
      }
      if (currentstatus[setLED] == 5 && intensityphase == 99) {
        currentstatus[setLED] = 6;
      }
      if (currentstatus[setLED] == 6) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * greenR / 255, Fadevalue * greenG / 255, Fadevalue * greenB / 255));
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 0;
      }
      if (currentstatus[setLED] == 0) {
        pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
      }
      //

      // Transition from on to blink
      if (currentstatus[setLED] == 1 && LEDstate[setLED] == 2) {
        currentstatus[setLED] = 5;
      }
      if (currentstatus[setLED] == 5 && intensityphase == 99) {
        currentstatus[setLED] = 6;
      }
      if (currentstatus[setLED] == 6) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * greenR / 255, Fadevalue * greenG / 255, Fadevalue * greenB / 255));
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 2;
      }
      if (currentstatus[setLED] == 2) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * greenR / 255, Fadevalue * greenG / 255, Fadevalue * greenB / 255));
      }
      //

      // Transition from off to blink
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 2) {
        currentstatus[setLED] = 3;
      }
      if (currentstatus[setLED] == 3 && intensityphase == 0) {
        currentstatus[setLED] = 4;
      }
      if (currentstatus[setLED] == 4) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * greenR / 255, Fadevalue * greenG / 255, Fadevalue * greenB / 255));
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) {
        currentstatus[setLED] = 2;
      }
      if (currentstatus[setLED] == 2) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * greenR / 255, Fadevalue * greenG / 255, Fadevalue * greenB / 255));
      }
    }
    //EndGreen:
    // Handle White LEDs
    if (LEDcolor[setLED] == 3) {
      // LED is off
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 0) {
        pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
        currentstatus[setLED] = 0;
        //goto EndWhite;
      }
      //

      // Transition from off to on
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 1) {
        currentstatus[setLED] = 3;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 3 && intensityphase == 0) {
        currentstatus[setLED] = 4;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 4) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * vitR / 255, Fadevalue * vitG / 255, Fadevalue * vitB / 255));
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) {
        currentstatus[setLED] = 1;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 1) {
        pixels.setPixelColor(setLED, pixels.Color(vitR, vitG, vitB));
        //goto EndWhite;
      }
      //

      // Transition from off to blink
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 2 && go2off == 0) {
        currentstatus[setLED] = 3;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 3 && intensityphase == 0) {
        currentstatus[setLED] = 4;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 4) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * vitR / 255, Fadevalue * vitG / 255, Fadevalue * vitB / 255));
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) {
        currentstatus[setLED] = 2;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 2) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * vitR / 255, Fadevalue * vitG / 255, Fadevalue * vitB / 255));
        //goto EndWhite;
      }
      //

      // Transition from on to off
      if (currentstatus[setLED] == 1 && LEDstate[setLED] == 0) {
        currentstatus[setLED] = 5;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 5 && intensityphase == 99) {
        currentstatus[setLED] = 6;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 6) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * vitR / 255, Fadevalue * vitG / 255, Fadevalue * vitB / 255));
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 0;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 0) {
        pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
        //goto EndWhite;
      }
      //

      // Transition from on to blink
      if (currentstatus[setLED] == 1 && LEDstate[setLED] == 2) {
        currentstatus[setLED] = 5;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 5 && intensityphase == 99) {
        currentstatus[setLED] = 6;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 6) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * vitR / 255, Fadevalue * vitG / 255, Fadevalue * vitB / 255));
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 2;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 2) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * vitR / 255, Fadevalue * vitG / 255, Fadevalue * vitB / 255));
        //goto EndWhite;
      }
      //

      // Transition from blink to off
      if (currentstatus[setLED] == 2 && LEDstate[setLED] == 0) {
        currentstatus[setLED] = 5;
        go2off = go2off + 1;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 5 && intensityphase == 99) {
        currentstatus[setLED] = 6;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 6) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * vitR / 255, Fadevalue * vitG / 255, Fadevalue * vitB / 255));
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 0;
        go2off = go2off - 1;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 0) pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));

      //
    }
    //EndWhite:


    // Handle Bright yellow LEDs
    if (LEDcolor[setLED] == 4) {
      // LED is off
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 0) {
        pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
        currentstatus[setLED] = 0;
        //goto EndYellow;
      }
      //

      // Transition from off to on
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 1) {
        currentstatus[setLED] = 3;
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 3 && intensityphase == 0) {
        currentstatus[setLED] = 4;
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 4) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * orangeR / 255, Fadevalue * orangeG / 255, Fadevalue * orangeB / 255));
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) {
        currentstatus[setLED] = 1;
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 1) {
        pixels.setPixelColor(setLED, pixels.Color(orangeR, orangeG, orangeB));
        //goto EndYellow;
      }
      //

      // Transition from off to blink
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 2 && go2off == 0) {
        currentstatus[setLED] = 3;
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 3 && intensityphase == 0) {
        currentstatus[setLED] = 4;
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 4) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * orangeR / 255, Fadevalue * orangeG / 255, Fadevalue * orangeB / 255));
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) {
        currentstatus[setLED] = 2;
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 2) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * orangeR / 255, Fadevalue * orangeG / 255, Fadevalue * orangeB / 255));
        //goto EndYellow;
      }
      //

      // Transition from on to off
      if (currentstatus[setLED] == 1 && LEDstate[setLED] == 0) {
        currentstatus[setLED] = 5;
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 5 && intensityphase == 99) {
        currentstatus[setLED] = 6;
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 6) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * orangeR / 255, Fadevalue * orangeG / 255, Fadevalue * orangeB / 255));
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 0;  //goto EndYellow;
      }
      if (currentstatus[setLED] == 0) {
        pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
        //goto EndYellow;
      }
      //

      // Transition from on to blink
      if (currentstatus[setLED] == 1 && LEDstate[setLED] == 2) {
        currentstatus[setLED] = 5;
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 5 && intensityphase == 99) {
        currentstatus[setLED] = 6;
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 6) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * orangeR / 255, Fadevalue * orangeG / 255, Fadevalue * orangeB / 255));
        //goto EndYellow;
      }

      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 2;  //goto EndYellow;
      }
      if (currentstatus[setLED] == 2) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * orangeR / 255, Fadevalue * orangeG / 255, Fadevalue * orangeB / 255));
        //goto EndYellow;
      }
      //

      // Transition from blink to off
      if (currentstatus[setLED] == 2 && LEDstate[setLED] == 0) {
        currentstatus[setLED] = 5;
        go2off = go2off + 1;
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 5 && intensityphase == 99) {
        currentstatus[setLED] = 6;
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 6) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue * orangeR / 255, Fadevalue * orangeG / 255, Fadevalue * orangeB / 255));
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 0;
        go2off = go2off - 1;
        //goto EndYellow;
      }
      //EndYellow:
      if (currentstatus[setLED] == 0) pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
      //
    }

    // Handle red/green LEDs
    if (LEDcolor[setLED] == redgreen) {
      //TÄND RÖD
      if (0 == setaspect[setLED] && 0 == newaspect[setLED]) {
        LEDstate[setLED] = 1;  //hantera uppstart
        //LEDcolor[setLED] = 1;
        pixels.setPixelColor(setLED, pixels.Color(redR, redG, redB));
      }

      //red to green fixed
      //Släck röd
      if (0 == setaspect[setLED] && 2 == newaspect[setLED]) {
        //Serial.print("red to green fixed green aspekt 2");
        //släck röd
        // Transition from on to off
        if (0 == currentstatus[setLED]) currentstatus[setLED] = 1;
        if (currentstatus[setLED] == 1 && intensityphase == 99) {
          currentstatus[setLED] = 2;
        }
        if (currentstatus[setLED] == 2) {
          pixels.setPixelColor(setLED, pixels.Color(Fadevalue * redR / 255, Fadevalue * redG / 255, Fadevalue * redB / 255));
          if (currentstatus[setLED] == 2 && intensityphase > 152) {
            currentstatus[setLED] = 3;
            pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
          }
        }
        //tänd grön
        if (currentstatus[setLED] == 3 && LEDstate[setLED] == 1) {
          currentstatus[setLED] = 4;
        }
        if (currentstatus[setLED] == 4 && intensityphase == 0) {
          currentstatus[setLED] = 5;
        }
        if (currentstatus[setLED] == 5) {
          pixels.setPixelColor(setLED, pixels.Color(Fadevalue * greenR / 255, Fadevalue * greenG / 255, Fadevalue * greenB / 255));
        }
        if (currentstatus[setLED] == 5 && intensityphase > 51) {
          currentstatus[setLED] = 6;
        }
        if (currentstatus[setLED] == 6) {
          pixels.setPixelColor(setLED, pixels.Color(greenR, greenG, greenB));
          setaspect[setLED] = 2;
          currentstatus[setLED] = 0;
        }
      }

      //Röd till grön blink
      if (0 == setaspect[setLED] && 1 == newaspect[setLED]) {
        //Serial.println("red to green blink aspekt 1");
        //släck röd
        // Transition from on to off
        if (0 == currentstatus[setLED]) {
          currentstatus[setLED] = 1;
        }
        if (currentstatus[setLED] == 1 && intensityphase == 99) {
          currentstatus[setLED] = 2;
        }
        if (currentstatus[setLED] == 2) {
          pixels.setPixelColor(setLED, pixels.Color(Fadevalue * redR / 255, Fadevalue * redG / 255, Fadevalue * redB / 255));
          if (currentstatus[setLED] == 2 && intensityphase > 152) {
            currentstatus[setLED] = 3;
            pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
          }
        }
        //tänd grön blink
        if (currentstatus[setLED] == 3) {
          currentstatus[setLED] = 4;
        }
        if (currentstatus[setLED] == 4 && intensityphase == 0) {
          currentstatus[setLED] = 5;
        }
        if (currentstatus[setLED] == 5) {
          pixels.setPixelColor(setLED, pixels.Color(Fadevalue * greenR / 255, Fadevalue * greenG / 255, Fadevalue * greenB / 255));
        }
        if (currentstatus[setLED] == 5 && intensityphase == 52) {
          currentstatus[setLED] = 6;
        }
        if (currentstatus[setLED] == 6) {
          pixels.setPixelColor(setLED, pixels.Color(greenR, greenG, greenB));
          setaspect[setLED] = 1;
          currentstatus[setLED] = 0;
          LEDstate[setLED] = blinking;
        }
      }
      //grön fast till röd
      if (2 == setaspect[setLED] && 0 == newaspect[setLED]) {
        //släck grön
        if (currentstatus[setLED] == 0) {
          currentstatus[setLED] = 1;
        }
        if (currentstatus[setLED] == 1 && intensityphase == 99) {
          currentstatus[setLED] = 2;
        }
        if (currentstatus[setLED] == 2) {
          pixels.setPixelColor(setLED, pixels.Color(Fadevalue * greenR / 255, Fadevalue * greenG / 255, Fadevalue * greenB / 255));
        }
        if (currentstatus[setLED] == 2 && intensityphase == 153) {
          currentstatus[setLED] = 3;
        }

        if (currentstatus[setLED] == 3 && intensityphase == 0) {
          currentstatus[setLED] = 4;
        }
        if (currentstatus[setLED] == 4) {
          pixels.setPixelColor(setLED, pixels.Color(Fadevalue * redR / 255, Fadevalue * redG / 255, Fadevalue * redB / 255));
        }
        if (currentstatus[setLED] == 4 && intensityphase == 52) {
          currentstatus[setLED] = 0;
          setaspect[setLED] = 0;
        }
        //
      }
/*
      #define startrampup 0
      #define fullintensity 52
#define startrampdown 99
#define endrampdown 153
*/
      //grön blink till röd
      if (1 == setaspect[setLED] && 0 == newaspect[setLED]) {
        //släck grön BLINK
        if (currentstatus[setLED] == 0) {
          currentstatus[setLED] = 1;
        }
        if (currentstatus[setLED] == 1 && intensityphase == endrampdown) {
          pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
          currentstatus[setLED] = 2;
        }
        
        if (currentstatus[setLED] == 2 ) {
          pixels.setPixelColor(setLED, pixels.Color(Fadevalue * redR / 255, Fadevalue * redG / 255, Fadevalue * redB / 255));
        }

        if (currentstatus[setLED] == 2 && intensityphase == fullintensity) {
          currentstatus[setLED] = 0;
          setaspect[setLED] = 0;
          pixels.setPixelColor(setLED, pixels.Color(redR, redG, redB));
        }
      }
      //Grön fast till grön blink
      if (2 == setaspect[setLED] && 1 == newaspect[setLED]) {
        //tänd grön blink
        if (intensityphase == fullintensity) {
          setaspect[setLED] = 1;
        }
      }

      //grön blink till grön fast
      if (1 == setaspect[setLED] && 2 == newaspect[setLED]) {
        //tänd grön blink
        if (intensityphase == fullintensity) {
          setaspect[setLED] = 2;
        }
      }
    }
    //Hantera grönt blink
    if (1 == setaspect[setLED] && 0!=newaspect[setLED]) {
      pixels.setPixelColor(setLED, pixels.Color(Fadevalue * greenR / 255, Fadevalue * greenG / 255, Fadevalue * greenB / 255));
    }
  }  //alla LEDar scannade

}  //slut rutin
