/*
  Implementation for For WiFi control of points by UDP messages sent from NTJ UDP Transmitter connected to DCC-EX

  Change log:
  2024-12-29   ver 1.0 For one esp8266 per 4 SERVOS IN A DOUBLE SLIP POINTS turnout
  

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
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include "Config.h"
#include <WiFiClient.h>
#include <Servo.h>
#include <ArduinoOTA.h>
//#include <Dns.h>
#include <ESP_EEPROM.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

Servo points1;  // create servo object to control a servo
Servo points2;  // create servo object to control a servo
/*
Servo points3;  // create servo object to control a servo
Servo points4;  // create servo object to control a servo
*/
AsyncWebServer Webserver(80);

void setup() {
  Serial.begin(115200);
  Serial.println("");
  EEPROM.begin(50);
  EEPROM.get(0, VxID);
  if (0 == VxID) {
    EEPROM.put(0, InitialDCCaddress);
    EEPROM.commit();
  }
  EEPROM.get(0, VxID);
  HostID = "Vx" + String(VxID);  //create Hostname from read ID
  WiFi.setHostname(HostID.c_str());
  ArduinoOTA.setHostname(HostID.c_str());
  Serial.println(HostID.c_str());
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Udp.begin(localPort);
  Serial.println("");
  Serial.println("Startat");
  //attstarttime = millis();

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
    } else if (request->hasParam(PARAM_INPUT_3)) {
      inputMessage = request->getParam(PARAM_INPUT_3)->value();
      inputParam = PARAM_INPUT_3;
      if (inputMessage.startsWith("0")) {
        setPos1 = 1;
        setPos2 = 1;
      }
      if (inputMessage.startsWith("1")) {
        setPos1 = 0;
        setPos2 = 1;
      }
      if (inputMessage.startsWith("2")) {
        setPos1 = 0;
        setPos2 = 0;
      }
      if (inputMessage.startsWith("3")) {
        setPos1 = 1;
        setPos2 = 0;
      }

    } else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    //Serial.println(inputMessage);
    request->send(200, "text/html", "The parameter " + inputParam + " has been set to: " + inputMessage + "<br><a href=\"/\">Return to Home Page</a>");
  });
  //Webserver.onNotFound(notFound);
  Webserver.begin();
  EEPROM.get(10, CurveDirection);
  setPos = 1;

/*
  points1.attach(Servo1, 500, 2400);  // attaches the servo on pin D1 to the servo object
  points1.write(180);
  delay(400);
  points1.detach();
  points2.attach(Servo2, 500, 2400);  // attaches the servo on pin D1 to the servo object
  points2.write(180);
  delay(400);
  points2.detach();
  */
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
    //points1.attach(Servo1, 500, 2400);  // attaches the servo on pin D1 to the servo object
    //attstarttime = millis();
  }
bailout:
  answer = 0;
  if (VxID == id) {
    if (0 == pos) {
      setPos1 = 1;
      setPos2 = 1;
    }
    if (1 == pos) {
      setPos1 = 0;
      setPos2 = 1;
    }
  }
  if (VxID == id + 1) {
    if (0 == pos) {
      setPos1 = 0;
      setPos2 = 0;
    }
    if (1 == pos) {
      setPos1 = 1;
      setPos2 = 0;
    }
  }

  //setPos = pos;
  //if (CurveDirection == 1) setPos = 1 - setPos;
  //if (0 == setPos) {
  //setPos1 = 0;
  //setPos2 = 0;
  // } else {
  //  setPos1 = 1;
  //  setPos2 = 1;
  //  }

  answer = Seq.toInt();
  /* Serial.print("id= ");
    Serial.print(id);
    Serial.print("  pos= ");
    Serial.print(pos);*/
  if (answer > 0) {
    // IPAddress broadCast = WiFi.localIP();
    // broadCast[3] = 255;
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    //Udp.beginPacket(broadCast, 8888);
    Udp.print(answer);
    Udp.endPacket();
    Serial.print("  Skickat svar: ");
    Serial.println(answer);
    answer = 0;
    id = 0;
  }
  //Do timebased repetition of points movement
  if (millis() - 25 >= last25run) {
    last25run = millis();
    every25ms();
  }
}  // Slut loop
