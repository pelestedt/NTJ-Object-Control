/*
  Implementation for For WiFi control of points by UDP messages sent from modified DCC++EX command station

  Change log:
  2023-02-05   ver 1.0
  2024-07-27   ver 2.0 For one esp8266 per turnoutwifi turout 3
  2024-09-07   ver baserad på wifi turout 3

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

Servo Door1;  // create servo object to control a
Servo Door2;
Servo Door3;
Servo Door4;
Servo Door5;
AsyncWebServer Webserver(80);

void setup() {
  Serial.begin(115200);
  Serial.println("");
  EEPROM.begin(50);
  EEPROM.get(0, Door1ID);
  Door2ID = Door1ID + 1;
  Door3ID = Door1ID + 2;
  Door4ID = Door1ID + 3;
  Door5ID = Door1ID + 4;

  HostID = "Lokstall";
  WiFi.setHostname(HostID.c_str());
  ArduinoOTA.setHostname(HostID.c_str());
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Udp.begin(localPort);

  //ArduinoOTA.setHostname(HostID);
  ArduinoOTA.setPassword("NTJNTJ01");
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
  Serial.println("Ver 3 Ready with OTA and Webserver");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("DCC address: ");
  Serial.println(Door1ID);

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
    }
    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage = request->getParam(PARAM_INPUT_2)->value();
      inputParam = PARAM_INPUT_2;

      if (inputMessage.startsWith("l") || inputMessage.startsWith("L")) {
        EEPROM.put(10, 1);
        CurveDirection = 1;
      }
      if (inputMessage.startsWith("r") || inputMessage.startsWith("R")) {
        EEPROM.put(10, 0);
        CurveDirection = 0;
      }
      EEPROM.commit();
    } else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    //Serial.println(inputMessage);
    request->send(200, "text/html", "The parameter " + inputParam + " has been set to: " + inputMessage + "<br><a href=\"/\">Return to Home Page</a>");
  });
  //Webserver.onNotFound(notFound);
  Webserver.begin();
}

void loop() {
  ArduinoOTA.handle();
  //Check if there is UDP message to process
  // if there's data available, red a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.println(packetSize);
    int n = Udp.read(UDPincoming, 20);
    UDPincoming[n] = 0;
    Serial.println(UDPincoming);
    char inledning = UDPincoming[0];
    String Inledning(inledning);
    if (Inledning != "T") {
      goto bailout;  // skip if invalid message
    }
    //Separate out id, pos and seq
    Sid = "";
    int t = 1;
    for (int c = 1; c < 9; c++) {
      Sid = Sid + UDPincoming[t];
      t++;
      if (UDPincoming[t] == 'P') {
        goto fpos;
      }
    }
fpos:
    t = t + 1;
    Spos = UDPincoming[t];
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
    pos = Spos.toInt();
  }
bailout:
  answer = 0;
  if (Door1ID == id) {
    Door1.attach(Servo1, 500, 2400);  // attach the servo to the servo object
    if (0 == pos) setPos1 = Dooropen;
    if (1 == pos) setPos1 = Doorclosed; 
    Serial.print("Dörr 1 satt till "); Serial.println(setPos1);
    answer = Seq.toInt();
    if (answer > 0) {
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.print(answer);
      Udp.endPacket();
      id = 0;
    }
  }
  if (Door2ID == id) {
    Door2.attach(Servo2, 500, 2400);  // attach the servo to the servo object
    if (0 == pos) setPos2 = Dooropen;
    if (1 == pos) setPos2 = Doorclosed;
    Serial.print("Dörr 2 satt till "); Serial.println(setPos2);
    answer = Seq.toInt();
    if (answer > 0) {
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.print(answer);
      Udp.endPacket();
      id = 0;
    }
  }
  if (Door3ID == id) {
    Door3.attach(Servo3, 500, 2400);  // attach the servo to the servo object
    if (0 == pos) setPos3 = Dooropen;
    if (1 == pos) setPos3 = Doorclosed;
    Serial.print("Dörr 3 satt till "); Serial.println(setPos3);
    answer = Seq.toInt();
    if (answer > 0) {
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.print(answer);
      Udp.endPacket();
      id = 0;
    }
  }
  if (Door4ID == id) {
    Door4.attach(Servo4, 500, 2400);  // attach the servo to the servo object
    if (0 == pos) setPos4 = Dooropen;
    if (1 == pos) setPos4 = Doorclosed;
    Serial.print("Dörr 4 satt till "); Serial.println(setPos4);
    answer = Seq.toInt();
    if (answer > 0) {
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.print(answer);
      Udp.endPacket();
      id = 0;
    }
  }
  if (Door5ID == id) {
    Door5.attach(Servo5, 500, 2400);  // attach the servo to the servo object
    if (0 == pos) setPos5 = Dooropen;
    if (1 == pos) setPos5 = Doorclosed;
    Serial.print("Dörr 5 satt till "); Serial.println(setPos5);
    answer = Seq.toInt();
    if (answer > 0) {
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.print(answer);
      Udp.endPacket();
      id = 0;
    }
  }

  //Do timebased repetition of points movement
  if (millis() - 75 >= last25run) {
    last25run = millis();
    every25ms();
  }
}  // Slut loop
