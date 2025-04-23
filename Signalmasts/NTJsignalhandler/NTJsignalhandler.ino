/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This decoder implementation is currently for SWEDISH mainline signals with 2, 3, 4 and 5 lamps , 2&3 lamp distant signals.
// Shuntig signals might be added later.
//
// The DCC_signal_decoder emulates a number of decoder addresses where each address represents a signalhead/board
// as per the NMRA DCC standards for "Extended Accessory Decoder Control Packet Format". Each lamp in the signal
// head/board is realised with a neopixel RGB led on a serial line. Each decoder can handle up to 16 addresses (=signal boards).
//
// Addressing follows the DCC standards as follows:
// {preamble} 0 10AAAAAA 0 0AAA0AA1 0 000XXXXX 0 EEEEEEEE 1
//
// XXXXX is for a single head. A value of 00000 for XXXXX indicates the absolute stop aspect. All other aspects
// represented by the values for XXXXX are determined by the signaling system used and the prototype being //modeled.
//
// For each address a signal type is defined. The signals must be defined in the order they are connected
// on the data loop.
// Each signal type has a number of aspects defined ranging from 1 and up.
// DCC sets the aspect by addressing the signal with the required aspect identity.
// The type determines how many lamps there are in the signal and the sequence number the address of the neopixel LED's
// In an aspect a lamp can have one of three statuses, off, on or blinking.
// Each signal can have up to 11111 (31 DEC) aspects (the range of XXXXX above) Aspect 0 is signal in stop (most restrictive)
//
// The bottom (left to right) LED is the first LED on each board uness it has beed defined as rotated 180 degrees,
// wich could be the case if mounted on a gantry.
//
// The decoder has a digital input that, if low, sets the LED intensity to "Night".
//
// The DCC signal to be decoded shall be connected to GPIO 2
// Read more at https://rudysmodelrailway.wordpress.com/software/
//
// Version history
// V1.0 19-12-10 Fist version with all 10 signal types, excluding change of lamp color
// V1.1 19-12-12 Change of color on signal 10 added
// V3 Incoming aspect from 3 consecutive addresses added in "Packethandler"
// V4 Signal address includes aspect as last digit, ex sig 45 asect 3 has DCC address 453
// V5  24-11-08 Hantering av färgkontroll inlagt. signalbilder har diod 1 längst ner. Signalbild 5 rättad

#include "DCC_signal_Decoder.h"
#include <Adafruit_NeoPixel.h>
#include "Signaldefinitions.h"
#include <ESP_EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <String.h>

/*
typedef struct
{
  int address;     // Base address of the signal
  byte byte0 = 0;  // State of output 1=on, 0=off
  byte byte1 = 0;  // State of output 1=on, 0=off
  byte byte2 = 0;  // State of output 1=on, 0=off

} Baseaddress;
//Initiera Struct
Baseaddress Basadress[32];
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Setup
//
Adafruit_NeoPixel pixels(Maxpixels, Neopixelbus, NEO_GRB + NEO_KHZ800);
//SoftwareSerial DCCdat(rxPin, txPin);


WiFiServer server(44);
WiFiClient client;
WiFiUDP Udp;

void setup() {
  Serial.begin(4800);
  Serial.println("");

  EEPROM.begin(1024);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print("-");
  }
  Serial.println("");
  Serial.println("Connected");
  Udp.begin(localPort);

  // Configure the decoder by reading from EEprom endast om addr 400, 401 och 402 innehåller 123
  Serial.println("");


  //

  if (EEPROM.read(400) == 123 && EEPROM.read(401) == 123 && EEPROM.read(402) == 123) {
    ConfigureDecoder();
  } else {
    Serial.println("");
    Serial.println("Dekoder saknar värden");
  }
  //  Serial.println("GMJS Signal Decoder, ready");
  pixels.begin();
  // light all LEDs in sequence to check that all work
  Testall();

  inputString = "";
  //Serial.println("Setup klar");
}  //end setup

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Main loop
//
void loop() {
  getUDP();
  // Check for incoming message and decode action
  //inkommet på serieport
  if (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;

      //Serial.println(inputString);
    }
  }


  //om avslutat meddelande inkommit
  if (stringComplete) {
    //Serial.println(inputString);
    //Is it DCC data ?

    //Utvärdera inkommen data från DCCsniffer*********************************
    //uppdatera adressdata
    char testchar1 = inputString.charAt(0);
    char testchar2 = inputString.charAt(1);

    //Is it a request from Widows to connect ?

    //Serial.print("testchar1: ");Serial.println(testchar1);
    //Serial.print("testchar2: ");Serial.println(testchar2);
    if ('C' == testchar1) {
      Serial.println("Connected");
      goto bailout;
    }  //end string starts with "C"

    //Is it a request to program EEPROM with aspekts ?
    if ('P' == testchar1 && 'A' == testchar2) {
      SaveAspekts();
      goto bailout;
    }  //end string starts with "ASPEKTS"

    //Is it a request to send aspect configuration to EEPROM ?
    if ('S' == testchar1 && 'A' == testchar2) {
      sendAspects();
      goto bailout;
    }  //end string starts with "SENDASPEKTS"

    //Is it a request to save intesity settings ?
    if ('P' == testchar1 && 'I' == testchar2) {
      SaveIntensity();
      goto bailout;
    }  //end string starts with "INTENSITY"


    //Is it a request to send intensity settings ?
    if ('S' == testchar1 && 'I' == testchar2) {
      sendIntensity();
      goto bailout;
    }  //end string starts with "SENDINTENSITY"

    //Is it a request to save aspect RGB configuration to EEPROM ?
    if ('P' == testchar1 && 'R' == testchar2) {
      SaveRGB();
      goto bailout;
    }  //end string starts with "RGB"

    //Is it a request to send aspect RGB configuration ?
    if ('S' == testchar1 && 'R' == testchar2) {
      SendRGB();
      goto bailout;
    }  //end string starts with "SENDRGB"


    //Is it a request to calibrate timbase ?
    if ('T' == testchar1 && 'C' == testchar2) {
      Calibratetime();
      goto bailout;
    }  //end string starts with "TC"





    //Is it a request to disconnect ?
    if ('R' == testchar1 && 'E' == testchar2) {
      Serial.println("RESET");
      delay(300);
      resetFunc();  //call reset
    }               //end string starts with "RESET"


    // clear the string:
bailout:
    inputString = "";
    stringComplete = false;
  }  //end string complete
  //static int addr = 0;

  //Kolla om inkommet data är för intensitetsändring


  if (int(inadress / 10) == int(Intensityaddr / 10)) {
    if (0 == nyaspekt) {
      setIntensity = Nightintensity;
    }
    if (1 == nyaspekt) {
      setIntensity = Dayintensity;
    }
    pixels.setBrightness(intensity);
    inadress = 0;
    indata = 0;
    //Serial.println(setIntensity);
  }

  //stega intensitet till rätt värde
  if (millis() > lastintensitycheck + 100) {
    //Serial.print(setIntensity);Serial.print("/");Serial.println(intensity);
    lastintensitycheck = millis();
    if (setIntensity > intensity) {
      intensity = intensity + 1;
    }
    if (setIntensity < intensity) {
      intensity = intensity - 1;
    }
    pixels.setBrightness(intensity);
    pixels.show();
  }



  lastinadress = inadress;
  lastindata = indata;

  ////////////////////////////////////////////////////////////////
  // Handle the aspect of all signals
  //
  // Set the intensity for flashing lights and ramp up/down for lamps going on or off.
  // the intensity is set from off to off in 200 steps where
  //
  //Serial.print(Blinkoff); Serial.print(" / "); Serial.println(Blinkramp);

  // if (millis() > lastrun + (Blinkfrq / fadesteps)) { //each of the fadesteps steps shall take peak to peak time /fadesteps as there are fadesteps steps
  if (lastrun + timebetweensteps < micros()) {  //each of the fadesteps steps shall take peak to peak time /fadesteps as there are fadesteps steps

    // Serial.println(micros()-lastrun);
    stepcount++;
    if (stepcount < rampupstart) { Fadevalue = 0; }  //0 till Blinkoff
    if (stepcount == rampupstart) intensityphase = 0;
    if (stepcount > rampupstart && stepcount < rampupend) Fadevalue = Fadevalue + (255 / Blinkramp);
    if (stepcount > rampupend && stepcount < rampdownstart) Fadevalue = 255;  //full intensitet
    if (stepcount == rampupend) intensityphase = 52;
    if (stepcount > rampdownstart && stepcount < rampdownend) Fadevalue = Fadevalue - (255 / Blinkramp);
    if (stepcount == rampdownstart) intensityphase = 99;
    if (stepcount > rampdownend) Fadevalue = 0;
    if (stepcount == rampdownend) intensityphase = 153;
    if (stepcount == fadesteps) stepcount = 0;


    //Serial.print(stepcount);Serial.print(" / ");Serial.print(Fadevalue);Serial.print(" / ");Serial.println(intensityphase);
    UpdateNeopixels();
    pixels.show();
    //    lastrun = millis();
    lastrun = micros();
    // If intensity is to become 0 update aspects
    if (stepcount == fadesteps / 2) {  //Kolla om denna skall köras vid halvperiod
      LEDserial = 0;
      for (int Signal = 0; Signal < Signalqty; Signal++) {
        /*
          Scan trough all defined signals and LEDs
          Find out what color and status they should have
          Compre to current status to see if there is a change
          If there is a change, execute transition
        */
        // For each LED in the signal
        for (byte LED = 0; LED < pgm_read_byte(&numleds[gAddresses[Signal].Signaltype]); LED++) {
          LEDserial = LEDserial + 1;
          //Get the state the individual lamp should have according to aspect[board type][aspect][led]
          LEDstate[LEDserial - 1] = pgm_read_byte(&aspect[gAddresses[Signal].Signaltype][gAddresses[Signal].Signalaspect][LED]);
          LEDcolor[LEDserial - 1] = pgm_read_byte(&color[gAddresses[Signal].Signaltype][LED]);
          //Special handling of signal type 10, that changes color
          if (gAddresses[Signal].Signaltype == 10) {
            newaspect[LEDserial - 1] = gAddresses[Signal].Signalaspect;
            //Serial.print("newLEDcolor[LEDserial - 1]");Serial.println(newLEDcolor[LEDserial - 1]);
            //All LEDs in the signal scanned through
          }
        }
        // All signals scanned through
      }

    }  // end updating aspects
  }
}  // End of loop
