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
// V4 Adressing changed to DCC Extended ress followed by 0-31

#include "DCC_signal_Decoder.h"
#include <Adafruit_NeoPixel.h>
#include "Signaldefinitions.h"
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
//#include "Config.h"
#include <WiFiClient.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Setup
//
Adafruit_NeoPixel pixels(Maxpixels, Neopixelbus, NEO_GRB + NEO_KHZ800);
//SoftwareSerial DCCdat(rxPin, txPin);

//tillfälliga variabler för att kolla exekveringstid
unsigned long lastexec = 0;
int exectime = 0;
int maxexectime = 0;
WiFiServer server(44);
WiFiClient client;
WiFiUDP Udp;


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(20);
  }
  Udp.begin(localPort);

  // Configure the decoder by reading from EEprom endast om addr 600, 6001 och 602 innehåller 123
  Serial.println("");
  if (EEPROM.read(95) == 123 && EEPROM.read(96) == 123 && EEPROM.read(97) == 123) {
    void ConfigDecoder();
  } else {
    Serial.println("");
    Serial.println("Dekoder saknar värden");
  }
  //  Serial.println("GMJS Signal Decoder Ver 4, ready");
  pixels.begin();
  // light all LEDs in sequence to check that all work
  void Testall();

  void getAspects();
  inputString = "";
  Serial.println("setup klar");

}  //end setup

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Main loop
//
void loop() {
  exectime = millis() - lastexec;
  //Serial.println(exectime);
  lastexec = millis();
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


    /*
    //Utvärdera inkommen data från DCCsniffer*********************************
    //uppdatera adressdata
    if (inputString.startsWith("A")) {
      DCCaddress = "";
      DCCdata = "";
      //Serial.println(inputString);
      //incoming message is DCC data, decode address and data
      byte t = 1; //börja läsa från andra karaktären
      while (inputString.charAt(t) != ',') {
        DCCaddress += inputString.charAt(t);
        t++;
      } // at this point we know it is a valid DCC address and we know the address
      // now we need to read the rest of the data to get the aspect number 0-31

      DCCdata = inputString.charAt(t + 1); //första tecknet efter ","
      DCCdata = DCCdata + inputString.charAt(t + 1); // andra tecknet efter ","
      //Serial.print("DCCadress/DCCdata "); Serial.print(DCCaddress); Serial.print("/"); Serial.println(DCCdata);
      inadress = DCCaddress.toInt();
      indata = DCCdata.toInt();
      //Check if it is the same data as last message, and if so ignore
      if (inadress == lastinadress && indata == lastindata) {
        inadress = 0; indata = 0;
      }
      goto bailout;
    }//Slut kolla tecken från DCCsniffer
*/
    //Is it a request from Widows to connect ?
    if (inputString.startsWith("C")) {
      Serial.println("Connected");
      goto bailout;
    }  //end string starts with "C"

    //Is it a request to program EEPROM with aspekts ?
    if (inputString.startsWith("PA")) {
      void SaveAspekts();
      goto bailout;
    }  //end string starts with "ASPEKTS"

    //Is it a request to send aspect configuration to EEPROM ?
    if (inputString.startsWith("SA")) {
      void sendAspects();
      goto bailout;
    }  //end string starts with "SENDASPEKTS"

    //Is it a request to save intesity settings ?
    if (inputString.startsWith("PI")) {
      void SaveIntensity();
      goto bailout;
    }  //end string starts with "INTENSITY"


    //Is it a request to send intensity settings ?
    if (inputString.startsWith("SI")) {
      void sendIntensity();
      goto bailout;
    }  //end string starts with "SENDINTENSITY"

    //Is it a request to save aspect RGB configuration to EEPROM ?
    if (inputString.startsWith("PR")) {
      void SaveRGB();
      goto bailout;
    }  //end string starts with "RGB"

    //Is it a request to send aspect RGB configuration ?
    if (inputString.startsWith("SR")) {
      void SendRGB();
      goto bailout;
    }  //end string starts with "SENDRGB"

    //Is it a request to disconnect ?
    if (inputString.startsWith("RESET")) {
      delay(300);
      resetFunc();  //call reset
    }               //end string starts with "RESET"


    // clear the string:
bailout:
    inputString = "";
    stringComplete = false;
  }  //end string complete
  static int addr = 0;

  //Kolla om inkommet data är för intensitetsändring


  if (inadress == Intensityaddr) {
    if (0 == indata) {
      setIntensity = Nightintensity;
    }
    if (1 == indata) {
      setIntensity = Dayintensity;
    }
    pixels.setBrightness(intensity);
    inadress = 0;
    indata = 0;
    //Serial.println(setIntensity);
  }

  //stega intensitet till rätt värde
  if (millis() > lastintensitycheck + 200) {
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
  //om det är en giltig adress (>1) kolla om den är till denna dekoder och i så fall uppdatera data.
  if (inadress > 1) {
    //Kontrollera om adressen finns på denna dekoder och i så fall sätt aspekten till DCCdata (indata)
    for (int a = 0; a < Signalqty; a++) {
      if (inadress == gAddresses[a].address) {
        gAddresses[a].Signalaspect = indata;
      }
      inadress = 1;
      indata = 0;
    }
  }
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
    if (stepcount < rampupstart) Fadevalue = 0;  //0 till Blinkoff
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
    void UpdateNeopixels();
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
          if (gAddresses[Signal].Signaltype == 10 && gAddresses[Signal].Signalaspect == 0) {
            LEDcolor[LEDserial - 1] = 1;
          }
          if (gAddresses[Signal].Signaltype == 10 && gAddresses[Signal].Signalaspect > 0) {
            LEDcolor[LEDserial - 1] = 2;
          }
          //All LEDs in the signal scanned through
        }
        // All signals scanned through
      }

    }  // end updating aspects
  }

}  // End of loop
