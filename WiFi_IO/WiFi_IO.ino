/*
  Implementation for For WiFi control of points by UDP messages sent from modified DCC++EX command station

  Change log:
  2023-02-05   ver 1.0

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
#include <ESP8266mDNS.h>  // Include the mDNS library

//Main loop declarations
unsigned long last25run = 0;
int id = 0;
String Sid = "256";
int pos = 0;
String Spos = "0";
byte IOID[9] = { 0, Out1, Out2, Out3, Out4, Out5, Out6, Out7, Out8 };
byte setPos[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
byte actualPos[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
bool stringComplete = false;  // whether the string is complete
int IOpin[9] = { 0, Outp1, Outp2, Outp3, Outp4, Outp5, Outp6, Outp7, Outp8 };

unsigned long answer = 0;
unsigned long pulsstart[5];
String Seq;

WiFiServer server(44);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(20);
  }
  Udp.begin(localPort);
  MDNS.begin("OCC1");

  for (int GPIO = 1; GPIO < 9; GPIO++) {
    pinMode(IOpin[GPIO], OUTPUT);
    digitalWrite(IOpin[GPIO], LOW);
    setPos[GPIO] = 2;  //tillse att inga  omslag görs vid uppstarft
  }
  Serial.println("");
  Serial.println("Startat");
}

void loop() {
  //Check if there is UDP message to process
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    
    int n = Udp.read(UDPincoming, 20);
    UDPincoming[n] = 0;
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
  for (int c = 1; c < 9; c++) {  //scan all IDs on this controler to see if it is here
    if (IOID[c] == id) {
      setPos[c] = pos;
      answer = Seq.toInt();


      if (answer > 0) {
       // IPAddress broadCast = WiFi.localIP();
       // broadCast[3] = 255;
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        //Udp.beginPacket(broadCast, 8888);
        Udp.print(answer);
        Udp.endPacket();
        Serial.print("Skickat svar: ");
        Serial.println(answer);
        answer = 0;
        id = 0;
      }
    }
  }
  /* //if answer (sequence number >0 send sequence number on UDP)
  if (answer > 0) {
    IPAddress broadCast = WiFi.localIP();
    broadCast[3] = 255;
    Udp.beginPacket(broadCast, 8888);
    Udp.print(answer);
    Udp.endPacket();
    answer = 0;
    id = 0;
  }
*/
  //Do timebased repetition of points movement
  if (millis() >= last25run + 100) {
    last25run = millis();
    every25ms();
  }
}  // Slut loop

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
