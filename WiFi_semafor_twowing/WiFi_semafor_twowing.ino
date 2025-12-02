/*
  Implementation for For WiFi control of SEMAPHORES by UDP messages sent from NTJ UDP Transmitter connected to DCC-EX

  Change log:
  2025-11-19   ver 1.0 For one esp8266 per SEMAPHORE

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "Config.h"
#include <WiFiClient.h>
#include <Servo.h>
#include <ArduinoOTA.h>
#include <Dns.h>
#include <ESP_EEPROM.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "gluedebug.h"
#include <Adafruit_NeoPixel.h>

String Programversion = "Ver 1.0 251123";  //Curenmt software version

Servo wing1;  // create servo object to control a servo
Servo wing2;  // create servo object to control a servo
AsyncWebServer Webserver(80);
Adafruit_NeoPixel pixels(3, D3, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println(Programversion);
  EEPROM.begin(50);
  EEPROM.get(0, SigID);
  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  if (0 == SigID) {
    EEPROM.put(0, InitialDCCaddress);
    EEPROM.commit();
  }
  EEPROM.get(0, SigID);
  HostID = "Sig" + String(SigID);  //create Hostname from read ID
  Serial.println(HostID.c_str());
  WiFi.setHostname(HostID.c_str());
  ArduinoOTA.setHostname(HostID.c_str());
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Udp.begin(localPort);
  Serial.println("");
  Serial.println("Startat");

  //ArduinoOTA.setHostname(HostID);
  ArduinoOTA.setPassword(OTApassword);
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ver 1 Ready with OTA and Webserver");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Send web page with input fields to client
  Webserver.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  Webserver.on("/get", HTTP_GET, [](AsyncWebServerRequest* request) {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      //Add storage in EEprom here
      int DCCa = inputMessage.toInt();
      EEPROM.put(0, DCCa);
      EEPROM.commit();
      ESP.reset();
    } else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    //Serial.println(inputMessage);
    request->send(200, "text/html", "The parameter " + inputParam + " has been set to: " + inputMessage + "<br><a href=\"/\">Return to Home Page</a>");
  });
  //Webserver.onNotFound(notFound);
  Webserver.begin();
  aspekt = 0;
  actualupperwingPos = abs((UpperGo - UpperStop) / 2);
  actuallowerwingPos = abs((LowerSlow - LowerFull) / 2);
  if (999 == SigID) {
    //Motionera vingarna för test
  }
  wing1.attach(D1, 500, 2400);
  wing1.write(10);
  delay(3000);
  wing1.write(60);
  delay(3000);
  wing2.attach(D2, 500, 2400);
  wing2.write(170);
  delay(3000);
  wing2.write(160);
  wing1.detach();
  wing2.detach();

  pixels.setPixelColor(0, pixels.Color(0, 150, 0));
  pixels.setPixelColor(1, pixels.Color(0, 150, 0));
  pixels.setPixelColor(2, pixels.Color(150, 0, 0));

  pixels.show();  // Send the updated pixel colors to the hardware.
}

void loop() {
  ArduinoOTA.handle();
  //Check if there is UDP message to process
  // if there's data available, red a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    //Serial.println(packetSize);
    int n = Udp.read(UDPincoming, 20);
    UDPincoming[n] = 0;
    Serial.println(UDPincoming);
    char inledning = UDPincoming[0];
    String Inledning(inledning);
    if (Inledning != "S") {
      goto bailout;  // skip if invalid message
    }
    //Separate out id, pos and seq
    Sid = "";
    int t = 1;
    for (int c = 1; c < 9; c++) {
      Sid = Sid + UDPincoming[t];
      t++;
      if (UDPincoming[t] == ',') {
        goto faspekt;
      }
    }
faspekt:
    t = t + 1;
    Saspekt = UDPincoming[t];
    Seq = "";
    t = t + 2;
    for (int c = 1; c < 9; c++) {
      Seq = Seq + UDPincoming[t];
      //Serial.println(Seq);
      t++;
      if (UDPincoming[t] == 0) {
        //Serial.println("null hittat");
        goto qend;
      }
    }
qend:
    id = Sid.toInt();
    aspekt = Saspekt.toInt();
    
  }
bailout:
  answer = 0;
  
  if (SigID == id) {
    
    //ställ in rätt aspekt
    wing1.attach(UpperWing, 500, 2400);  // attach the servo to the servo object
    wing2.attach(LowerWing, 500, 2400);  // attach the servo to the servo object
    answer = Seq.toInt();
    if (0 == aspekt) {
      setupperwingpos = UpperStop;
      setlowerwingpos = LowerFull;
    }
    if (1 == aspekt) {
      setupperwingpos = UpperGo;
      setlowerwingpos = LowerSlow;
    }
    if (2 == aspekt) {
      setupperwingpos = UpperGo;
      setlowerwingpos = LowerFull;
    }
   // Serial.print("Aspekt satt till ");
    //Serial.println(aspekt);
    if (answer > 0) {
      // IPAddress broadCast = WiFi.localIP();
      // broadCast[3] = 255;
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      //Udp.beginPacket(broadCast, 8888);
      Udp.print(answer);
      Udp.endPacket();
      //Serial.print("  Skickat svar: ");
      //Serial.println(answer);
      answer = 0;
      id = 0;
    }
  }

  //Do timebased repetition of points movement
  if (millis() - 75 >= last25run) {
    last25run = millis();
    every25ms();
  }
}  // Slut loop
