/*
  Implementation for For WiFi control of points by UDP messages sent from modified DCC++EX command station

  Change log:
  2023-02-05   ver 1.0
  2024-07-27   ver 2.0 For one esp8266 per turnout

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
//#include "Turntable.h"
#include <WiFiClient.h>
#include <ArduinoOTA.h>
#include <Dns.h>
#include <ESP_EEPROM.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer Webserver(80);

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("NTJ Vändskivekontroll 1.0 OTA");

  //Initiera IO
  pinMode(FWD, OUTPUT);
  pinMode(REW, OUTPUT);
  pinMode(D5, OUTPUT);
  digitalWrite(D5, HIGH);
  pinMode(Zeropos, INPUT_PULLUP);
  pinMode(CHA, INPUT_PULLUP);  //Encoder channel A
  pinMode(CHB, INPUT_PULLUP);  //Encoder channel B
  attachInterrupt(CHA, ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(Zeropos), zeroISR, FALLING);
  analogWriteFreq(10000);


  // hämta upp positionsadresser och värden
  EEPROM.begin(50);

  HostID = "Turntable";  //create Hostname from read ID
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
  attstarttime = millis();

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
    if (request->hasParam(PARAM_INPUT_1)) {  //Spår nummer
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      //Add storage in EEprom here
      int Track = inputMessage.toInt();
      //Serial.println(Track);
      pos = Track;
    }
    if (request->hasParam(PARAM_INPUT_2)) {  //DCC adress för spåret
      inputMessage = request->getParam(PARAM_INPUT_2)->value();
      inputParam = PARAM_INPUT_2;
      //Add storage in EEprom here
      int DCCa = inputMessage.toInt();
      EEPROM.put(((Track - 1) * 6), DCCa);
      EEPROM.commit();
      //Serial.println(DCCa);
      id = DCCa;
    }
    if (request->hasParam(PARAM_INPUT_3)) {  //Encodervärde posion 0
      inputMessage = request->getParam(PARAM_INPUT_3)->value();
      inputParam = PARAM_INPUT_3;
      //Add storage in EEprom here
      int P0 = inputMessage.toInt();
      EEPROM.put(((Track - 1) * 6) + 2, P0);
      EEPROM.commit();
      //Serial.println(P0);
    }
    if (request->hasParam(PARAM_INPUT_4)) {  //Encodervärde posion 1
      inputMessage = request->getParam(PARAM_INPUT_4)->value();
      inputParam = PARAM_INPUT_4;
      //Add storage in EEprom here
      int P1 = inputMessage.toInt();
      EEPROM.put(((Track - 1) * 6) + 4, P1);
      EEPROM.commit();
      //Serial.println(P1);
    }

    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    //Serial.println(inputMessage);
    request->send(200, "text/html", "The parameters have been saved!"
                                    "<br><a href=\"/\">Return to Home Page</a>");
  });
  //Webserver.onNotFound(notFound);

  //initiera vändskivans position
  Kalibrera();
  Webserver.begin();
  delay(2000);
  //set_tablepos = 3000;
}

void loop() {
  Tablehandling();  // Move turntable if not in position
  Speedhandling(setspeed);
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
    if (Inledning != "V") {  //V för vändskiva
      goto bailout;          // skip if invalid message
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

  //Kontrollera inkommen adress och positionsbegäran
  for (int posi = 0; posi < 10; posi++) {
    if (position[posi][0] == id) {
      if (pos == 0) {
        set_tablepos = position[posi][1];
        Serial.print("addr ");
        Serial.print(position[posi][0]);
        id = 0;
        Serial.print("   pos ");
        Serial.println(position[posi][1]);
      }
      if (pos == 1) {
        set_tablepos = position[posi][2];
        Serial.print("addr ");
        Serial.print(position[posi][0]);
        id = 0;
        Serial.print("   pos ");
        Serial.println(position[posi][2]);
      }
      Serial.println(set_tablepos);
    }
  }

  //delay(1000);
  //sätt positionen till rätt encodervärde



  //kör skivan till den nya positionen
  //}


}  // Slut loop

ICACHE_RAM_ATTR void ISR() {

  if (micros() - lastpulse > 300) {  //filtrera bort flera pulser på samma flank
    pulsetime = micros() - lastpulse;
    lastpulse = micros();
    //Serial.println(master_count);

    // add 1 to count for CW
    if (digitalRead(CHA) && !digitalRead(CHB)) {
      master_count++;
    }
    // subtract 1 from count for CCW
    if (digitalRead(CHA) && digitalRead(CHB)) {
      master_count--;
      if (master_count == -1 && Direction == Moturs) { master_count = fullturn - 1; }
    }
  }
}


ICACHE_RAM_ATTR void zeroISR() {
  if (0 == kalibreringsfas && Direction == Medurs) {
    if (master_count > 5000) {
      
      if (master_count >= fullturn){ master_count = 0;
      detachInterrupt(digitalPinToInterrupt(Zeropos));
      Serial.println("nollställt helvarv");}
    }
    Serial.println(micros());
  }

  if (1 == seekzero) {
    master_count = 0;
    seekzero = 3;
    Serial.println("sz 2");
  }

  if (2 == seekzero) {
    prelcount = master_count;
    seekzero = 0;
    Serial.println("sz 2");
  }
  if (3 == seekzero && currentdir == FWD && master_count > 2000) {
    master_count = 0;
    Serial.println("sz 3");
  }
  if (3 == seekzero && currentdir == REW && master_count < 2000) {
    master_count = fullturn + paddlelength;
    Serial.println("neg sz 3");
  }
  
}
