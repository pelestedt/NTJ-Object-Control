void UpdateNeopixels() {
  
  // Scan through all LEDs
  // Transitions between aspects are handled by different status of the led
  // eher: 0 == off, 1 == on, 2 == blinking, 3 == Waiting to Fade to on, 4 fade to on, 5 == Waiting to Fade to off, 6 fade to off
  // Scan through all LEDs on the bus

  for (setLED = 0; setLED < Buslength ; setLED++) {

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
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, 0, 0));
        //goto EndRed;
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) currentstatus[setLED] = 1; //goto EndRed;
      if (currentstatus[setLED] == 1) pixels.setPixelColor(setLED, pixels.Color(255, 0, 0)); //goto EndRed;
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
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, 0, 0));
        //goto EndRed;
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) currentstatus[setLED] = 2; //goto EndRed;
      if (currentstatus[setLED] == 2) pixels.setPixelColor(setLED, pixels.Color(Fadevalue, 0, 0)); //goto EndRed;
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
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, 0, 0));
        //goto EndRed;
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) currentstatus[setLED] = 0; //goto EndRed;
      if (currentstatus[setLED] == 0) pixels.setPixelColor(setLED, pixels.Color(0, 0, 0)); //goto EndRed;
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
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, 0, 0));
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) currentstatus[setLED] = 2; //goto EndRed;
      if (currentstatus[setLED] == 2) pixels.setPixelColor(setLED, pixels.Color(Fadevalue, 0, 0)); //goto EndRed;
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
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, 0, 0));
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
EndRed:
    // Handle green LEDs
    if (LEDcolor[setLED] == 2) {
      // LED is off
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 0) {
        pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
        currentstatus[setLED] = 0;
        //goto EndGreen;
      }
      //

      // Transition from off to on
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 1 && go2off == 0) {
        currentstatus[setLED] = 3;
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 3 && intensityphase == 0) {
        currentstatus[setLED] = 4;
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 4) {
        pixels.setPixelColor(setLED, pixels.Color(0, Fadevalue, 0));
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) {
        currentstatus[setLED] = 1;
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 1) {
        pixels.setPixelColor(setLED, pixels.Color(0, 255, 0));
        //goto EndGreen;
      }
      //

      // Transition from off to blink
      if (currentstatus[setLED] == 0 && LEDstate[setLED] == 2) {
        currentstatus[setLED] = 3;
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 3 && intensityphase == 0) {
        currentstatus[setLED] = 4;
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 4) {
        pixels.setPixelColor(setLED, pixels.Color(0, Fadevalue, 0));
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) {
        currentstatus[setLED] = 2;
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 2) {
        pixels.setPixelColor(setLED, pixels.Color(0, Fadevalue, 0));
        //goto EndGreen;
      }
      //

      // Transition from on to off
      if (currentstatus[setLED] == 1 && LEDstate[setLED] == 0) {
        currentstatus[setLED] = 5;
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 5 && intensityphase == 99) {
        currentstatus[setLED] = 6;
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 6) {
        pixels.setPixelColor(setLED, pixels.Color(0, Fadevalue, 0));
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 0;
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 0) {
        pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
        //goto EndGreen;
      }
      //

      // Transition from on to blink
      if (currentstatus[setLED] == 1 && LEDstate[setLED] == 2) {
        currentstatus[setLED] = 5;
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 5 && intensityphase == 99) {
        currentstatus[setLED] = 6;
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 6) {
        pixels.setPixelColor(setLED, pixels.Color(0, Fadevalue, 0));
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 2;
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 2) {
        pixels.setPixelColor(setLED, pixels.Color(0, Fadevalue, 0));
        //goto EndGreen;
      }
      //

      // Transition from blink to off
      if (currentstatus[setLED] == 2 && LEDstate[setLED] == 0) {
        currentstatus[setLED] = 5;
        go2off = go2off + 1;
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 5 && intensityphase == 99) {
        currentstatus[setLED] = 6;
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 6) {
        pixels.setPixelColor(setLED, pixels.Color(0, Fadevalue, 0));
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 0;
        go2off = go2off - 1;
        //goto EndGreen;
      }
      if (currentstatus[setLED] == 0) pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
      //

    }
EndGreen:
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
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, Fadevalue, Fadevalue));
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) {
        currentstatus[setLED] = 1;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 1) {
        pixels.setPixelColor(setLED, pixels.Color(255, 255, 255));
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
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, Fadevalue, Fadevalue));
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) {
        currentstatus[setLED] = 2;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 2) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, Fadevalue, Fadevalue));
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
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, Fadevalue, Fadevalue));
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
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, Fadevalue, Fadevalue));
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 2;
        //goto EndWhite;
      }
      if (currentstatus[setLED] == 2) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, Fadevalue, Fadevalue));
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
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, Fadevalue, Fadevalue));
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
EndWhite:
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
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, Fadevalue, Fadevalue));
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) {
        currentstatus[setLED] = 1;
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 1) {
        pixels.setPixelColor(setLED, pixels.Color(240, 150, 25));
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
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, Fadevalue, Fadevalue / 5));
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 4 && intensityphase > 51) {
        currentstatus[setLED] = 2;
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 2) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, Fadevalue, Fadevalue / 5));
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
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, Fadevalue, Fadevalue / 5));
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 0; //goto EndYellow;
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
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, Fadevalue, Fadevalue / 5));
        //goto EndYellow;
      }

      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 2; //goto EndYellow;
      }
      if (currentstatus[setLED] == 2) {
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, Fadevalue, Fadevalue / 5));
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
        pixels.setPixelColor(setLED, pixels.Color(Fadevalue, Fadevalue, Fadevalue / 5));
        //goto EndYellow;
      }
      if (currentstatus[setLED] == 6 && intensityphase > 152) {
        currentstatus[setLED] = 0;
        go2off = go2off - 1;
        //goto EndYellow;
      }
EndYellow:
      if (currentstatus[setLED] == 0) pixels.setPixelColor(setLED, pixels.Color(0, 0, 0));
      //
    }

    // All LEDs scanned through
  }

  // End of function

}
