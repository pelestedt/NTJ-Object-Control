/*
   Config.h
*/

const char* PARAM_INPUT_1 = "DCCaddress";
const char* PARAM_INPUT_2 = "Curve direction";

// HTML web page to handle 2 input fields 

 const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <br>
  <br>
  <br>
  <br>
  <form action="/get">
    DCC address: <input type="text" name="DCCaddress">
   <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    Left or Right: <input type="text" name="Curve direction">
    <input type="submit" value="Submit">
  </form><br>
 </body></html>)rawliteral";

//void notFound(AsyncWebServerRequest* request) {   request->send(404, "text/plain", "Not found");}
//Node configuration

//#define VxID  999  //DCC address 
int VxID;
String HostID;

//String STASSID = "NTJ";
//String STAPSK = "NTJNTJ01";
String STASSID = "Lundsholm2G";
String STAPSK = "CrUtu4rA";

int packetSize = 0;
String Configstring = "";  // a String to hold incoming data
boolean configmode = false;
int Inaddr;
String Configuration;
byte CurveDirection=0;

//getUDPdata declarations
unsigned int localPort = 8888;  // local port to listen on
String inputString = "";        // a String to hold incoming data

// buffer for sending data
//char packetBuffer[20 + 1];  //buffer to hold incoming packet,
char UDPincoming[20 + 1];   //buffer to hold incoming packet,
//boolean UDPavailable;
WiFiUDP Udp;

int port = 44;


//define points ID in DCC++EX, the number that represents the points on this controller


//Define the outpust on the Arduino that controls the outputs setting the points
#define Servo1 D1
#define InitialDCCaddress 999

//Main loop declarationsInitialDCCaddress
unsigned long last25run = 0;
int id = 9999;
String Sid = "256";
int pos = 0;
String Spos = "0";
//byte VXID = VxID;
byte setPos = 0 ;
byte actualPos= {0 };
bool stringComplete = false;  // whether the string is complete
byte pointsID = VxID;
byte anglePos;
unsigned long answer = 0;
String Seq;
byte restarted = 0;
unsigned long attstarttime = 0;
byte att = 0;

WiFiServer server(44);
WiFiClient client;

 
