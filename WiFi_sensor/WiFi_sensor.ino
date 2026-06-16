/*
  Implementation for For WiFi control of SEMAPHORES by UDP messages sent from NTJ UDP Transmitter connected to DCC-EX

  Change log:
  2025-11-19   ver 1.0 For one esp8266 per up to 9 sensors

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
#include <ArduinoOTA.h>
#include <Dns.h>
#include <ESP_EEPROM.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "gluedebug.h"

String Programversion = "Ver 1.0 260615";  //Curenmt software version

AsyncWebServer Webserver(80);

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println(Programversion);
  EEPROM.begin(50);
  
  for (byte mem = 1; mem < 9; mem++) {
    EEPROM.get(mem, SensorID[mem]);
  }

  HostID = "SensorID" + String(SensorID[1]);  //create Hostname from read ID
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
  bCast = WiFi.localIP();
  IPAddress subnet = WiFi.subnetMask();
  for (int l = 0; l < 4; l++) {
    bCast[l] = bCast[l] | (255 - subnet[l]);
  }
  Serial.print("Broadcast IP: ");
  Serial.println(bCast);
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
    request->send_P(200, "text/html", index_html, processor);
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
      int sensoraddress = inputMessage.toInt();
      EEPROM.put(1, sensoraddress);
      EEPROM.commit();
      SensorID[1]=sensoraddress;      
    } 
    if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage = request->getParam(PARAM_INPUT_2)->value();
      inputParam = PARAM_INPUT_2;
      //Add storage in EEprom here
      int sensoraddress = inputMessage.toInt();
      EEPROM.put(2, sensoraddress);
      EEPROM.commit();
       SensorID[2]=sensoraddress;  
    } 
if (request->hasParam(PARAM_INPUT_3)) {
      inputMessage = request->getParam(PARAM_INPUT_3)->value();
      inputParam = PARAM_INPUT_3;
      //Add storage in EEprom here
      int sensoraddress = inputMessage.toInt();
      EEPROM.put(3, sensoraddress);
      EEPROM.commit();
      SensorID[3]=sensoraddress;      
    } 
    if (request->hasParam(PARAM_INPUT_4)) {
      inputMessage = request->getParam(PARAM_INPUT_4)->value();
      inputParam = PARAM_INPUT_4;
      //Add storage in EEprom here
      int sensoraddress = inputMessage.toInt();
      EEPROM.put(4, sensoraddress);
      EEPROM.commit();
       SensorID[4]=sensoraddress;  
    } 
if (request->hasParam(PARAM_INPUT_5)) {
      inputMessage = request->getParam(PARAM_INPUT_5)->value();
      inputParam = PARAM_INPUT_5;
      //Add storage in EEprom here
      int sensoraddress = inputMessage.toInt();
      EEPROM.put(5, sensoraddress);
      EEPROM.commit();
      SensorID[5]=sensoraddress;      
    } 
    if (request->hasParam(PARAM_INPUT_6)) {
      inputMessage = request->getParam(PARAM_INPUT_6)->value();
      inputParam = PARAM_INPUT_6;
      //Add storage in EEprom here
      int sensoraddress = inputMessage.toInt();
      EEPROM.put(6, sensoraddress);
      EEPROM.commit();
       SensorID[6]=sensoraddress;  
    } 
if (request->hasParam(PARAM_INPUT_7)) {
      inputMessage = request->getParam(PARAM_INPUT_7)->value();
      inputParam = PARAM_INPUT_7;
      //Add storage in EEprom here
      int sensoraddress = inputMessage.toInt();
      EEPROM.put(7, sensoraddress);
      EEPROM.commit();
      SensorID[7]=sensoraddress;      
    } 
    if (request->hasParam(PARAM_INPUT_8)) {
      inputMessage = request->getParam(PARAM_INPUT_8)->value();
      inputParam = PARAM_INPUT_8;
      //Add storage in EEprom here
      int sensoraddress = inputMessage.toInt();
      EEPROM.put(8, sensoraddress);
      EEPROM.commit();
       SensorID[8]=sensoraddress;  
    } 
















        
    else {
      inputMessage = " ";
      inputParam = " ";
    }
    //Serial.println(inputMessage);
    request->send(200, "text/html", "Sensoridentiteten har uppdaterats! " + inputParam + "  " + inputMessage + "<br><a href=\"/\">Tillbaks till hemsidan</a>");
  });
  //Webserver.onNotFound(notFound);
  Webserver.begin();
  for (byte p = 1; p < 9; p++) {
    pinMode(sensorport[p], INPUT_PULLUP);
  }
}

void loop() {
  ArduinoOTA.handle();
  //Check IO status
  for (int s = 1; s < 9; s++) {
    int status = digitalRead(sensorport[s]);
    status = abs(status - 1);
    if (status != currentstatus[s]) {
      currentstatus[s] = status;
      String sendmsg = 'S' + String(SensorID[s]) + ',' + String(status);
      //Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.beginPacket(bCast, 8888);
      Udp.print(sendmsg);
      Udp.endPacket();
      Serial.print("Skickat: ");
      Serial.println(sendmsg);
      sendmsg = 0;
    }
  }
}  // Slut loop
